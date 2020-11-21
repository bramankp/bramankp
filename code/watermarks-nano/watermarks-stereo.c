#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <altfixdec_fft.h>
#include <cbet_decode_top.h>
#include <cbetd.h>
#include <decimate.h>
#include <N2_A.h>
#include <N6_A.h>
#include <N6_Sfft_Flt.h>
#include <naesflt.h>
#include <Resample_2to3_Int.h>

enum { SAMPLE_RATE = 16000 };
enum { AUDIO_BLOCK_8K = 256, AUDIO_BLOCK_16K = 512, AUDIO_BLOCK_24K = 768 };

static struct {
    NaesFlt_Context_t cb;
    NaesFlt_Context_t n2;
    NaesFlt_Context_t n6;
} filter;

static time_t seconds;

static void IncrementClock()
{
    static unsigned counter;
    counter += AUDIO_BLOCK_16K;
    if (counter >= SAMPLE_RATE)
    {
        seconds += 1;
        naesflt_filter_time(&filter.cb, seconds);
        naesflt_filter_time(&filter.n2, seconds);
        naesflt_filter_time(&filter.n6, seconds);
        counter -= SAMPLE_RATE;
    }
}

static void ProcessAudioBlock(const int16_t *frames16K);
static void PerformSampleRateConversionLeft(int16_t *samples8K, const int16_t *samples16K, int16_t *samples24K);
static void PerformSampleRateConversionRight(int16_t *samples8K, const int16_t *samples16K, int16_t *samples24K);
static void DecodeCB(const int16_t *samplesL, const int16_t *samplesR);
static void DecodeN2(const int16_t *samples);
static void DecodeN6(const int16_t *samplesL, const int16_t *samplesR);
static void CallbackCB(unsigned layer, unsigned qualityCode, unsigned id, unsigned timestamp, unsigned diffsnr, unsigned raw_timestamp, unsigned detBlkCnt, unsigned curBlkCnt);
static void CallbackN2(void *UserSpacePtr, N2_A_Result_t *Result);
static void CallbackN6(void *UserSpacePtr, N6_A_Result_t *Result);
static void EventCallback(Naesflt_Event_t *result);

int main()
{
    naesflt_create_stream(&filter.cb, NAESFLT_EVENT_CBET, 57, 300, EventCallback, NULL);
    naesflt_create_stream(&filter.n2, NAESFLT_EVENT_NAES2, 57, 300, EventCallback, NULL);
    naesflt_create_stream(&filter.n6, NAESFLT_EVENT_NAES6, 57, 300, EventCallback, NULL);
    int16_t frames[2 * AUDIO_BLOCK_16K];
    while (fread(frames, (2 * sizeof(int16_t)), AUDIO_BLOCK_16K, stdin) == (size_t)AUDIO_BLOCK_16K)
    {
        ProcessAudioBlock(frames);
        IncrementClock();
    }
    naesflt_flush_stream(&filter.cb, seconds);
    naesflt_flush_stream(&filter.n2, seconds);
    naesflt_flush_stream(&filter.n6, seconds);
    return 0;
}

void ProcessAudioBlock(const int16_t *frames16K)
{
    struct {
        int16_t left[AUDIO_BLOCK_8K];
        int16_t right[AUDIO_BLOCK_8K];
    } samples8K;

    struct {
        int16_t left[AUDIO_BLOCK_16K];
        int16_t right[AUDIO_BLOCK_16K];
    } samples16K;

    struct {
        int16_t left[AUDIO_BLOCK_24K];
        int16_t right[AUDIO_BLOCK_24K];
    } samples24K;

    int16_t *sample = frames16K;
    for (int i = 0; i != AUDIO_BLOCK_16K; ++i)
    {
        samples16K.left[i] = *sample++;
        samples16K.right[i] = *sample++;
    }

    PerformSampleRateConversionLeft(samples8K.left, samples16K.left, samples24K.left);
    PerformSampleRateConversionRight(samples8K.right, samples16K.right, samples24K.right);
    DecodeCB(samples8K.left, samples8K.right);
    DecodeN2(samples24K.left);
    DecodeN6(samples16K.left, samples16K.right);
}

void PerformSampleRateConversionLeft(int16_t *samples8K, const int16_t *samples16K, int16_t *samples24K)
{
    static struct {
        int16_t decimation[DECIMATE_2_OFFSET + AUDIO_BLOCK_16K];
        Resample_2to3_Int_ControlBlock_t resampler;
    } context;

    if (context.resampler == NULL)
    {
        context.resampler = malloc(Resample_2to3_Int_Bytes_In_Control_Block());
        Resample_2to3_Int_Init(context.resampler);
    }

    memcpy(context.decimation + DECIMATE_2_OFFSET, samples16K, (sizeof(int16_t) * AUDIO_BLOCK_16K));
    decimate2(context.decimation + DECIMATE_2_OFFSET, samples8K, AUDIO_BLOCK_8K, 1);

    Resample_2to3_Int(samples16K, samples24K, AUDIO_BLOCK_16K, context.resampler);
}

void PerformSampleRateConversionRight(int16_t *samples8K, const int16_t *samples16K, int16_t *samples24K)
{
    static struct {
        int16_t decimation[DECIMATE_2_OFFSET + AUDIO_BLOCK_16K];
        Resample_2to3_Int_ControlBlock_t resampler;
    } context;

    if (context.resampler == NULL)
    {
        context.resampler = malloc(Resample_2to3_Int_Bytes_In_Control_Block());
        Resample_2to3_Int_Init(context.resampler);
    }

    memcpy(context.decimation + DECIMATE_2_OFFSET, samples16K, (sizeof(int16_t) * AUDIO_BLOCK_16K));
    decimate2(context.decimation + DECIMATE_2_OFFSET, samples8K, AUDIO_BLOCK_8K, 1);

    Resample_2to3_Int(samples16K, samples24K, AUDIO_BLOCK_16K, context.resampler);
}

void DecodeCB(const int16_t *samplesL, const int16_t *samplesR)
{
    static void *context;

    if (context == NULL)
    {
        context = malloc(CBET_getMinMemBytes());
        CBET_initDecode(context, CBET_getMinMemBytes(), NULL);
    }

    static struct {
        int16_t left[FFT_SIZE];
        int16_t right[FFT_SIZE];
    } buffer;
    static unsigned index;

    for (int i = 0; i != AUDIO_BLOCK_8K; ++i)
    {
        buffer.left[index] = samplesL[i];
        buffer.right[index] = samplesR[i];
        if (++index == FFT_SIZE)
        {
            uint32_t temp[FFT_SIZE / 2];
            ALTFIXFFT_Fix16CalcFft2048(buffer.left, temp, START_POSITION, END_POSITION);
            unsigned powers[FFT_SIZE / 2];
            for (int i = 0; i != (FFT_SIZE / 2); ++i) { powers[i] = temp[i]; }
            ALTFIXFFT_Fix16CalcFft2048(buffer.right, temp, START_POSITION, END_POSITION);
            for (int i = 0; i != (FFT_SIZE / 2); ++i) { powers[i] += temp[i]; }
            CBET_decode(context, powers);
            unsigned results[8] = {0};
            if (CBET_getMsg2(context, results))
            {
                CallbackCB(results[0], results[1], results[2], results[3], results[4], results[5], results[6], results[7]);
            }
            memmove(buffer.left, buffer.left + OVERLAP_PTS, (sizeof(int16_t) * (FFT_SIZE - OVERLAP_PTS)));
            memmove(buffer.right, buffer.right + OVERLAP_PTS, (sizeof(int16_t) * (FFT_SIZE - OVERLAP_PTS)));
            index -= OVERLAP_PTS;
        }
    }
}

void DecodeN2(const int16_t *samples)
{
    static struct {
        N2_Sfft_Flt_ControlBlock_t fft;
        N2_A_ControlBlock_t dec;
    } context;

    if (context.fft == NULL)
    {
        context.fft = malloc(N2_Sfft_Flt_Bytes_In_Control_Block());
        context.dec = malloc(N2_A_Bytes_In_Control_Block());
        N2_Sfft_Flt_Init(context.fft);
        N2_A_Init(CallbackN2, NULL, context.dec);
    }

    float buffer[N2_SFFT_NUM_SAMPLES];
    unsigned blocks = AUDIO_BLOCK_24K / N2_SFFT_NUM_SAMPLES;
    while (blocks--)
    {
        for (int i = 0; i != N2_SFFT_NUM_SAMPLES; ++i)
        {
            buffer[i] = *samples++;
        }
        N2_Sfft_FftBinPowers_t powers;
        N2_Sfft_Flt(buffer, powers, context.fft);
        N2_A_Program_Decode(powers, context.dec);
    }
}

void DecodeN6(const int16_t *samplesL, const int16_t *samplesR)
{
    static struct {
        struct {
            N6_Sfft_Flt_ControlBlock_t left;
            N6_Sfft_Flt_ControlBlock_t right;
        } fft;
        N6_A_ControlBlock_t dec;
    } context;

    if (context.dec == NULL)
    {
        context.fft.left = malloc(N6_Sfft_Flt_Bytes_In_Control_Block());
        context.fft.right = malloc(N6_Sfft_Flt_Bytes_In_Control_Block());
        context.dec = malloc(N6_A_Bytes_In_Control_Block());
        N6_Sfft_Flt_Init(context.fft.left);
        N6_Sfft_Flt_Init(context.fft.right);
        N6_A_Init(CallbackN6, NULL, context.dec);
    }

    unsigned blocks = AUDIO_BLOCK_16K / N6_SFFT_NUM_SAMPLES;
    while (blocks--)
    {
        struct {
            N6_Sfft_Flt_Discard_t left;
            N6_Sfft_Flt_Discard_t right;
        } discard;
        N6_Sfft_FftBinPowers_t powers;
        N6_Sfft_Flt_Program_Stereo(samplesL, samplesR, discard.left, discard.right, powers, context.fft.left, context.fft.right);
        N6_A_Program_Decode(powers, context.dec);
        N6_Sfft_Flt_Commercial_Stereo(discard.left, discard.right, powers, context.fft.left, context.fft.right);
        N6_A_Commercial_Decode(powers, context.dec);
        samplesL += N6_SFFT_NUM_SAMPLES;
        samplesR += N6_SFFT_NUM_SAMPLES;
    }
}

void CallbackCB(unsigned layer, unsigned qualityCode, unsigned id, unsigned timestamp, unsigned diffsnr, unsigned raw_timestamp, unsigned detBlkCnt, unsigned curBlkCnt)
{
    time_t currentTime = seconds;
    time_t age = curBlkCnt - detBlkCnt;
    time_t newTimestamp = currentTime - ((age * 100 + 499) / 1000);

    printf("CB timestamp:%u layer:%u id:%u quality:%u\n", (unsigned)newTimestamp, layer, id, qualityCode);

    NaesCode_t code = {0};
    code.sysTime = newTimestamp;
    code.sid = id;
    code.payload = timestamp;
    code.block = detBlkCnt;
    code.level = SET_LAYER(layer) | LEVEL_CODETYPE_CBET;
    switch (layer)
    {
    case 1:
    case 2:
    case 5:
        if ((timestamp == 65534) || (timestamp == 65535))
        {
            code.level |= LEVEL_NO_PAYLOAD | LEVEL_STACKED_BIT;
        }
        if ((qualityCode == 6) || (qualityCode == 7))
        {
            code.level |= LEVEL_STACKED_BIT;
        }
        break;
    case 3:
        break;
    case 4:
        if ((11 <= qualityCode) && (qualityCode <= 13))
        {
            code.level |= LEVEL_STACKED_BIT;
        }
        break;
    default:
        break;
    }

    naesflt_filter_code(&filter.cb, &code);
}

void CallbackN2(void *UserSpacePtr, N2_A_Result_t *Result)
{
    time_t currentTime = seconds;
    time_t age = Result->emission_time_in_blocks - Result->detection_time_in_blocks;
    time_t newTimestamp = currentTime - ((age * N2_A_BLOCK_TIME_IN_MS + 499) / 1000);

    char *qualityString[] = {"N", "S", "P"};
    printf("N2 timestamp:%u band:%d dist:%d id:%u quality:%s\n", (unsigned)newTimestamp, (int)Result->band, (int)Result->distribution_type, (unsigned)Result->sid, qualityString[Result->code_type]);

    NaesCode_t code = {0};
    code.sysTime = newTimestamp;
    code.sid = Result->sid;
    code.payload = Result->timestamp;
    code.block = Result->detection_time_in_blocks;
    code.level = Result->distribution_type | LEVEL_CODETYPE_NAES2;
    switch (Result->code_type)
    {
    case N2_A_CODE_NORMAL:
        break;
    case N2_A_CODE_STACKED_FULL:
        code.level |= LEVEL_STACKED_BIT;
        break;
    case N2_A_CODE_STACKED_PARTIAL:
        code.level |= LEVEL_NO_PAYLOAD | LEVEL_STACKED_BIT | LEVEL_NT;
        break;
    default:
        break;
    }
    if (Result->dst)
    {
        code.level | LEVEL_DSTBRK_BIT;
    }

    naesflt_filter_code(&filter.n2, &code);
}

void CallbackN6(void *UserSpacePtr, N6_A_Result_t *Result)
{
    time_t currentTime = seconds;
    time_t age = Result->emission_time_in_blocks - Result->detection_time_in_blocks;
    time_t newTimestamp = currentTime - ((age * N6_A_BLOCK_TIME_IN_MS + 499) / 1000);

    char *qualityString[] = {"N", "S", "P"};
    printf("N6 timestamp:%u band:%d dist:%d id:%u, quality:%s\n", (unsigned)newTimestamp, (int)Result->band, (int)Result->distribution_type, (unsigned)Result->sid, qualityString[Result->code_type]);

    NaesCode_t code = {0};
    code.sysTime = newTimestamp;
    code.sid = Result->sid;
    code.payload = Result->timestamp_or_payload;
    code.block = Result->detection_time_in_blocks;
    code.level = Result->distribution_type | LEVEL_CODETYPE_NAES6;
    switch (Result->code_type)
    {
    case N6_A_CODE_NORMAL:
        break;
    case N6_A_CODE_STACKED_FULL:
        code.level |= LEVEL_STACKED_BIT;
        break;
    case N6_A_CODE_STACKED_PARTIAL:
        code.level |= LEVEL_NO_PAYLOAD | LEVEL_STACKED_BIT | LEVEL_NT;
        break;
    default:
        break;
    }
    if (Result->band)
    {
        code.level |= LEVEL_ALT_BIT;
    }
    if (Result->transmission_type)
    {
        code.level | LEVEL_TIC_BIT;
    }
    if (Result->dst_or_breakout)
    {
        code.level | LEVEL_DSTBRK_BIT;
    }

    naesflt_filter_code(&filter.n6, &code);
}

void EventCallback(Naesflt_Event_t *result)
{
    switch (result->event_category)
    {
    case NAESFLT_EVENT_CBET:
        printf("CB startTime:%u duration:%u band:%u sid:%u payload:%u\n", (unsigned)result->system_timestamp, (unsigned)result->duration_seconds, (unsigned)GET_LAYER(result->level), (unsigned)result->station_id, (unsigned)result->encoded_start_time);
        break;
    case NAESFLT_EVENT_NAES2:
        printf("N2 startTime:%u duration:%u level:%u sid:%u dst:%d payload:%u\n", (unsigned)result->system_timestamp, (unsigned)result->duration_seconds, (unsigned)(result->level & 0x3), (unsigned)result->station_id, (result->dst ? 1 : 0), (unsigned)result->encoded_start_time);
        break;
    case NAESFLT_EVENT_NAES6:
        printf("N6 startTime:%u duration:%u band:%d sid:%u dist:%u trans:%d dstbrk:%d payload:%u\n", (unsigned)result->system_timestamp, (unsigned)result->duration_seconds, (IS_N6_ALTBAND(result->level) ? 1 : 0), (unsigned)result->station_id, (unsigned)(result->level & 0x3), (IS_N6_TIC(result->level) ? 1 : 0), (result->dst ? 1 : 0), (unsigned)result->encoded_start_time);
        break;
    default:
        break;
    }
}
