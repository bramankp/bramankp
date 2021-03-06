#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sfendian.h>
#include <sndfile.h>

#include <decimate.h>

static void OutputSamples(int16_t *samples)
{
    assert(fwrite(samples, sizeof(int16_t), 512, stdout) == 512);
}

static void ProcessFile48000(SNDFILE *sndfile, SF_INFO sfinfo)
{
    sf_count_t BLOCK = 1536;
    int16_t context[DECIMATE_3_OFFSET + BLOCK];
    memset(context, 0, sizeof(context));
    int16_t samples16000[BLOCK / 3];
    short frames[sfinfo.channels * BLOCK];
    sf_count_t count;
    while ((count = sf_readf_short(sndfile, frames, BLOCK)) == BLOCK)
    {
        int16_t *samples48000 = context + DECIMATE_3_OFFSET;
        short *frame = frames;
        for (sf_count_t i = 0; i != BLOCK; ++i)
        {
            samples48000[i] = frame[0];
            frame += sfinfo.channels;
        }
        decimate3_i16_i16(samples48000, samples16000, BLOCK / 3, 1);
        OutputSamples(samples16000);
    }
}

static void ProcessFile16000(SNDFILE *sndfile, SF_INFO sfinfo)
{
    sf_count_t BLOCK = 512;
    short frames[sfinfo.channels * BLOCK];
    sf_count_t count;
    while ((count = sf_readf_short(sndfile, frames, BLOCK)) == BLOCK)
    {
        int16_t samples[BLOCK];
        short *frame = frames;
        for (sf_count_t i = 0; i != BLOCK; ++i)
        {
            samples[i] = frame[0];
            frame += sfinfo.channels;
        }
        OutputSamples(samples);
    }
}

static bool ProcessFile(SNDFILE *sndfile, SF_INFO sfinfo)
{
    switch (sfinfo.samplerate)
    {
    case 48000:
        ProcessFile48000(sndfile, sfinfo);
        return true;
    case 16000:
        ProcessFile16000(sndfile, sfinfo);
        return true;
    default:
        fprintf(stderr, "error: unhandled sample rate: %d\n", sfinfo.samplerate);
        break;
    }
    return false;
}


int main(int argc, char *argv[])
{
    assert(sizeof(short) == sizeof(int16_t));

    if (argc != 2)
    {
        fputs("usage: sndfile <filename>\n", stderr);
        return -1;
    }
    const char *filename = argv[1];

    SF_INFO sfinfo = { .format = 0 };
    SNDFILE *sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if (sndfile == NULL)
    {
        fprintf(stderr, "error: sf_open: %s: %s\n", filename, sf_strerror(NULL));
        return -1;
    }
    if (!ProcessFile(sndfile, sfinfo))
    {
        return -1;
    }
    if (sf_close(sndfile) != 0)
    {
        fprintf(stderr, "error: sf_close: %s\n", sf_strerror(NULL));
        return -1;
    }

    return 0;
}
