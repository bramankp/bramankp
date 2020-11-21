#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <CBET_FFT.h>
#include <CBET.h>
#include <decimate.h>
#include <FFT_Flt_3KR4.h>
#include <FFT_Flt_4KR4.h>
#include <N2_FFT.h>
#include <N2M.h>
#include <N6_FFT.h>
#include <N6M.h>
#include <UEG.h>
#include <Win_Hann_N256.h>

enum { SAMPLES_8K = 256, SAMPLES_16K = 512, SAMPLES_24K = 768, SAMPLES_48K = 1536 };

static struct {
    struct {
        float dec48to24[DECIMATE_2_OFFSET + SAMPLES_48K];
        float dec48to16[DECIMATE_3_OFFSET + SAMPLES_48K];
        float dec16to8[DECIMATE_2_OFFSET + SAMPLES_16K];
    } src;
    struct {
        struct {
            float samples[CBET_FFT_SIZE];
            int count;
        } cb;
        struct {
            float samples[N2_FFT_SIZE];
            int count;
        } n2;
        struct {
            float samples[N6_FFT_SIZE];
            int count;
        } n6;
    } fft;
    struct {
        CBET_ControlBlock_t cb;
        N2M_ControlBlock_t n2;
        N6M_ControlBlock_t n6;
        UEG_ControlBlock_t ueg;
    } ctx;
} uegtest;

static int milliseconds;

static void CBCallback(void *UserSpacePtr, const CBET_Detection_t *Detection)
{
    (void)UserSpacePtr;
    int s = milliseconds - Detection->age_of_first_symbol_in_milliseconds;
    int e = milliseconds - Detection->age_of_last_symbol_in_milliseconds;
    printf("%8d          %8d ", s, e);
    printf("CB layer:%d id:%u time:%u\n", (int)Detection->layer, (unsigned)Detection->id, (unsigned)Detection->time);
    UEG_Process_CBET_Detection(Detection, &uegtest.ctx.ueg);
}

static void N2Callback(void *UserSpacePtr, const N2M_Detection_t *Detection)
{
    (void)UserSpacePtr;
    int s = milliseconds - Detection->age_of_first_symbol_in_milliseconds;
    int e = milliseconds - Detection->age_of_last_symbol_in_milliseconds;
    printf("%8d          %8d ", s, e);
    printf("N2 layer:%d id:%u time:%d dist:%d dst:%u\n", (int)Detection->layer, (unsigned)Detection->wm.id, (int)Detection->wm.time, (int)Detection->wm.dist, (unsigned)Detection->wm.dst);
    UEG_Process_N2M_Detection(Detection, &uegtest.ctx.ueg);
}

static void N6Callback(void *UserSpacePtr, const N6M_Detection_t *Detection)
{
    (void)UserSpacePtr;
    int s = milliseconds - Detection->age_of_first_symbol_in_milliseconds;
    int e = milliseconds - Detection->age_of_last_symbol_in_milliseconds;
    printf("%8d          %8d ", s, e);
    printf("N6 layer:%d id:%u time:%d dist:%d dst:%u trans:%d\n", (int)Detection->layer, (unsigned)Detection->wm.id, (int)Detection->wm.time, (int)Detection->wm.dist, (unsigned)Detection->wm.dst, (int)Detection->wm.trans);
    UEG_Process_N6M_Detection(Detection, &uegtest.ctx.ueg);
}

static void ProgCallback(void *UserSpacePtr, const UEG_Event_Prog_t *Event)
{
    (void)UserSpacePtr;
    int s = milliseconds - Event->age_of_start_in_milliseconds;
    int d = Event->duration_in_milliseconds;
    int e = s + d;
    printf("%8d %8d %8d ", s, d, e);
    printf("UW type:%d reason:%d age:%d duration:%d cb:{ id:%u time:%d layer:%u detections:%u } n2:{ id:%u time:%d dst:%d detections:%u } n6:{ id:%u time:%d dst:%d trans:%d detections:%u }\n", (int)Event->type, (int)Event->reason, (int)Event->age_of_start_in_milliseconds, (int)Event->duration_in_milliseconds, (unsigned)Event->cbet_id, (int)Event->cbet_encoded_time, (unsigned)Event->cbet_layer, (unsigned)Event->cbet_detection_count, (unsigned)Event->n2_id, (int)Event->n2_encoded_time, (int)Event->n2_dst, (unsigned)Event->n2_detection_count, (unsigned)Event->n6_id, (int)Event->n6_encoded_time, (int)Event->n6_dst, (int)Event->n6_trans, (unsigned)Event->n6_detection_count);
}

static void CommCallback(void *UserSpacePtr, const UEG_Event_Comm_t *Event)
{
    (void)UserSpacePtr;
    (void)Event;
}

int main()
{
    CBET_Init(CBCallback, NULL, &uegtest.ctx.cb);
    N2M_Init(N2Callback, NULL, &uegtest.ctx.n2);
    N6M_Init(N6Callback, NULL, &uegtest.ctx.n6);
    UEG_Init(ProgCallback, CommCallback, NULL, UEG_BRIDGE_TIME_NON_ACOUSTIC, NULL, NULL, &uegtest.ctx.ueg);
    int16_t samples[SAMPLES_48K];
    while (fread(samples, sizeof(int16_t), SAMPLES_48K, stdin) == SAMPLES_48K)
    {
        float samples48K[SAMPLES_48K];
        for (int i = 0; i != SAMPLES_48K; ++i)
        {
            samples48K[i] = samples[i];
        }

        float samples24K[SAMPLES_24K];
        memcpy(uegtest.src.dec48to24 + DECIMATE_2_OFFSET, samples48K, SAMPLES_48K * sizeof(float));
        decimate2_f32_f32(uegtest.src.dec48to24 + DECIMATE_2_OFFSET, samples24K, SAMPLES_24K, 1.0F);

        float samples16K[SAMPLES_16K];
        memcpy(uegtest.src.dec48to16 + DECIMATE_3_OFFSET, samples48K, SAMPLES_48K * sizeof(float));
        decimate3_f32_f32(uegtest.src.dec48to16 + DECIMATE_3_OFFSET, samples16K, SAMPLES_16K, 1.0F);

        float samples8K[SAMPLES_8K];
        memcpy(uegtest.src.dec16to8 + DECIMATE_2_OFFSET, samples16K, SAMPLES_16K * sizeof(float));
        decimate2_f32_f32(uegtest.src.dec16to8 + DECIMATE_2_OFFSET, samples8K, SAMPLES_8K, 1.0F);

        for (int i = 0; i != SAMPLES_8K; ++i)
        {
            uegtest.fft.cb.samples[uegtest.fft.cb.count] = samples8K[i];
            if (++uegtest.fft.cb.count == CBET_FFT_SIZE)
            {
                float powers[CBET_FFT_SIZE];
                FFT_Flt_4KR4_RealIn_PowerOut_FF(CBET_FFT_SIZE, uegtest.fft.cb.samples, powers, CBET_FFT_FIRST_COMPUTED_BIN);
                CBET_Decode(powers, &uegtest.ctx.cb);
                memmove(uegtest.fft.cb.samples, uegtest.fft.cb.samples + CBET_FFT_SLIDE, (CBET_FFT_SIZE - CBET_FFT_SLIDE) * sizeof(float));
                uegtest.fft.cb.count -= CBET_FFT_SLIDE;
            }
        }

        for (int i = 0; i != SAMPLES_24K; ++i)
        {
            uegtest.fft.n2.samples[uegtest.fft.n2.count] = samples24K[i];
            if (++uegtest.fft.n2.count == N2_FFT_SIZE)
            {
                float powers[N2_FFT_SIZE];
                FFT_Flt_4KR4_RealIn_PowerOut_Win_FF(N2_FFT_SIZE, uegtest.fft.n2.samples, WIN_HANN_N256, powers, N2_FFT_FIRST_COMPUTED_BIN);
                N2M_Decode(powers, &uegtest.ctx.n2);
                memmove(uegtest.fft.n2.samples, uegtest.fft.n2.samples + N2_FFT_SLIDE, (N2_FFT_SIZE - N2_FFT_SLIDE) * sizeof(float));
                uegtest.fft.n2.count -= N2_FFT_SLIDE;
            }
        }

        for (int i = 0; i != SAMPLES_16K; ++i)
        {
            uegtest.fft.n6.samples[uegtest.fft.n6.count] = samples16K[i];
            if (++uegtest.fft.n6.count == N6_FFT_SIZE)
            {
                float powers[N6_FFT_SIZE];
                FFT_Flt_3KR4_RealIn_PowerOut_FF(N6_FFT_SIZE, uegtest.fft.n6.samples, powers, N6_FFT_FIRST_COMPUTED_BIN);
                N6M_Decode(powers, &uegtest.ctx.n6);
                memmove(uegtest.fft.n6.samples, uegtest.fft.n6.samples + N6_FFT_SLIDE, (N6_FFT_SIZE - N6_FFT_SLIDE) * sizeof(float));
                uegtest.fft.n6.count -= N6_FFT_SLIDE;
            }
        }

        UEG_Increment_Time(32, &uegtest.ctx.ueg);
        milliseconds += 32;
    }
    UEG_Flush(&uegtest.ctx.ueg);
    return 0;
}
