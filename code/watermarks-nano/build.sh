gcc -std=c11 -Wall -Wextra -O3 -o watermarks-mono watermarks-mono.c \
    -Iaudio-downsampler-2.4.2/ \
        audio-downsampler-2.4.2/decimate.c \
        audio-downsampler-2.4.2/Resample_2to3_Int.c \
    -Icbet-decoder-nano/ -Icbet-decoder-nano/dat/ -Icbet-decoder-nano/dec/ \
        -D_EMBED_LAYER_INFO_ -D_SHOW_ALL_CODES_ \
        cbet-decoder-nano/dec/altfixdec_fft.c \
        cbet-decoder-nano/dec/bocdec_softdecode.c \
        cbet-decoder-nano/dec/bocdec_softmetric.c \
        cbet-decoder-nano/dec/cbet_decode_top.c \
        cbet-decoder-nano/dec/sft_calcsnr.c \
    -Inaes2-decoder-3.0.2/ \
        naes2-decoder-3.0.2/N2_A.c \
        naes2-decoder-3.0.2/N2_Sfft_Core_Flt.c \
        naes2-decoder-3.0.2/N2_Sfft_Flt.c \
    -Inaes6-decoder-3.0.6/ \
        naes6-decoder-3.0.6/N6_A.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt_Core.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt_Normalize.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt_Sum_Normalize.c \
    -Iwatermark-filter-v2.1.3/ \
        watermark-filter-v2.1.3/naesAnalyzerFilter.c

gcc -std=c11 -Wall -Wextra -O3 -o watermarks-stereo watermarks-stereo.c \
    -Iaudio-downsampler-2.4.2/ \
        audio-downsampler-2.4.2/decimate.c \
        audio-downsampler-2.4.2/Resample_2to3_Int.c \
    -Icbet-decoder-nano/ -Icbet-decoder-nano/dat/ -Icbet-decoder-nano/dec/ \
        -D_EMBED_LAYER_INFO_ -D_SHOW_ALL_CODES_ \
        cbet-decoder-nano/dec/altfixdec_fft.c \
        cbet-decoder-nano/dec/bocdec_softdecode.c \
        cbet-decoder-nano/dec/bocdec_softmetric.c \
        cbet-decoder-nano/dec/cbet_decode_top.c \
        cbet-decoder-nano/dec/sft_calcsnr.c \
    -Inaes2-decoder-3.0.2/ \
        naes2-decoder-3.0.2/N2_A.c \
        naes2-decoder-3.0.2/N2_Sfft_Core_Flt.c \
        naes2-decoder-3.0.2/N2_Sfft_Flt.c \
    -Inaes6-decoder-3.0.6/ \
        naes6-decoder-3.0.6/N6_A.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt_Core.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt_Normalize.c \
        naes6-decoder-3.0.6/N6_Sfft_Flt_Sum_Normalize.c \
    -Iwatermark-filter-v2.1.3/ \
        watermark-filter-v2.1.3/naesAnalyzerFilter.c
