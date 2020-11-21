#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <FFT_Flt_4KR4.h>
#include <SFP_Compress.h>
#include <SFP.h>
#include <SFP_Window.h>

enum { BLOCK_SIZE = 256, SFP_SIG_BUFLEN = 512 };

typedef struct {
    SFP_Ema82X_CB_t signature;
    SFP_comp_cb_t compression;
} Context;

typedef struct {
    int frames;
    int bytes;
    uint8_t buffer[SFP_SIG_BUFLEN];
} Signature;

static Signature signature;

static void FlushSFP(Context *context)
{
    if (signature.frames > 0)
    {
        if ((signature.bytes = SFP_compress_finalize(&context->compression)) == 0)
        {
            fputs("SFP_compress_finalize failed\n", stderr);
        }
        else
        {
            printf("SFP event frames:%d bytes:%d\n", signature.frames, signature.bytes);
        }
    }
    signature = (Signature){0};
    SFP_compress_init(&context->compression, signature.buffer, sizeof(signature.buffer));
}

static void CallbackSFP(void *UserSpacePtr, SFP_Signature_t *Signature)
{
    puts("SFP frame");
    Context *context = (Context*)UserSpacePtr;
    uint8_t result = SFP_compress(&context->compression, Signature->BinNum);
    switch (result)
    {
    case SFP_COMP_OK:
        signature.frames += 1;
        break;
    case SFP_COMP_OVER:
        FlushSFP(context);
        if ((result = SFP_compress(&context->compression, Signature->BinNum)) == SFP_COMP_OK)
        {
            signature.frames += 1;
            break;
        }
        // fall through
    default:
        fputs("SFP_compress failed\n", stderr);
        FlushSFP(context);
        break;
    }
}

int main()
{
    struct {
        int16_t samples[SFP_FFT_SIZE];
        int count;
    } fft = {.count = 0};

    Context context;

    SFP_Ema8_Init(SFP_MODE_QRY, SFP_RATE_2X, CallbackSFP, &context, &context.signature);
    FlushSFP(&context);

    int16_t samples[BLOCK_SIZE];
    while (fread(samples, sizeof(int16_t), BLOCK_SIZE, stdin) == BLOCK_SIZE)
    {
        for (int i = 0; i != BLOCK_SIZE; ++i)
        {
            fft.samples[fft.count] = samples[i];
            if (++fft.count == SFP_FFT_SIZE)
            {
                float bins[SFP_FFT_SIZE];
                FFT_Flt_4KR4_RealIn_MagOut_Win_Scale_IF(SFP_FFT_SIZE, fft.samples, SFP_WINDOW, bins, SFP_SCALE_OUT, SFP_FFT_FIRST_COMPUTED_BIN);
                SFP_Ema8_Process(bins, &context.signature);
                memmove(fft.samples, fft.samples + SFP_FFT_SLIDE_2X, (SFP_FFT_SIZE - SFP_FFT_SLIDE_2X) * sizeof(int16_t));
                fft.count -= SFP_FFT_SLIDE_2X;
            }
        }
    }
    FlushSFP(&context);
    return 0;
}
