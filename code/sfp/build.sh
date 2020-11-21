gcc -std=c11 -Wall -Wextra -O3 -o sfptest \
    -Ifft/ -Isfpsig/ -Isfpsig/Signature_Compression \
    sfptest.c \
    fft/FFT_Flt_4KR4.c \
    fft/FFT_Flt_Combine.c \
    fft/FFT_FLT_COS_4096.c \
    fft/FFT_Flt_R4_W0.c \
    fft/FFT_Flt_R4_WM_WL.c \
    fft/FFT_Flt_R8_W0.c \
    fft/FFT_R2_BIT_REV.c \
    sfpsig/SFP_Ema8.c \
    sfpsig/SFP_Freq_Scaling_F.c \
    sfpsig/SFP_Sort_F.c \
    sfpsig/SFP_U8.c \
    sfpsig/Signature_Compression/SFP_Compress.c \
    -lm
