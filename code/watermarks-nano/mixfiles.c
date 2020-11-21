#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *channel1 = fopen(argv[1], "rb");
    FILE *channel2 = fopen(argv[2], "rb");
    FILE *channel3 = fopen(argv[3], "rb");
    FILE *channel4 = fopen(argv[4], "rb");
    int16_t samples1[512];
    int16_t samples2[512];
    int16_t samples3[512];
    int16_t samples4[512];
#ifdef TBD
    int16_t frames[2048];
#else
    int16_t frames[1024];
#endif // TBD
    while (fread(samples1, sizeof(int16_t), 512, channel1) == 512)
    {
        fread(samples2, sizeof(int16_t), 512, channel2);
        fread(samples3, sizeof(int16_t), 512, channel3);
        fread(samples4, sizeof(int16_t), 512, channel4);
        int16_t *src1 = samples1;
        int16_t *src2 = samples2;
#ifdef TBD
        int16_t *src3 = samples3;
        int16_t *src4 = samples4;
#endif // TBD
        int16_t *dst = frames;
        for (int i = 0; i != 512; ++i)
        {
            *dst++ = *src1++;
            *dst++ = *src2++;
#ifdef TBD
            *dst++ = *src3++;
            *dst++ = *src4++;
#endif // TBD
        }
#ifdef TBD
        fwrite(frames, sizeof(int16_t), 2048, stdout);
#else
        fwrite(frames, sizeof(int16_t), 1024, stdout);
#endif // TBD
    }
    return 0;
}
