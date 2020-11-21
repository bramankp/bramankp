#gcc -std=c11 -Wall -Wextra -O3 -o uegnano-old \
#    -Iaudio-downsampler-2.4.8/ \
#    -Icbet-decoder-s-2.1.2/ \
#    -Ifft-1.4.3/ -Ifft-1.4.3/Window/ \
#    -Igeneral-algorithms-1.0.6/ -Igeneral-algorithms-1.0.6/Reed-Solomon/ \
#    -Inaes2-decoder-4.1.1/ \
#    -Inaes6-decoder-4.1.3/ \
#    -Iunified-event-generator-2.3.1/ -Iunified-event-generator-2.3.1/Mapping/ \
#    uegnano.c \
#    audio-downsampler-2.4.8/decimate.c \
#    audio-downsampler-2.4.8/Resample_2to3_Int.c \
#    cbet-decoder-s-2.1.2/CBET_BinSnr.c \
#    cbet-decoder-s-2.1.2/CBET.c \
#    cbet-decoder-s-2.1.2/CBET_SymSnr.c \
#    fft-1.4.3/FFT_Flt_3KR4.c \
#    fft-1.4.3/FFT_Flt_4KR4.c \
#    fft-1.4.3/FFT_Flt_Combine.c \
#    fft-1.4.3/FFT_FLT_COS_3072.c \
#    fft-1.4.3/FFT_FLT_COS_4096.c \
#    fft-1.4.3/FFT_Flt_R3_W0.c \
#    fft-1.4.3/FFT_Flt_R4_W0.c \
#    fft-1.4.3/FFT_Flt_R4_WM_WL.c \
#    fft-1.4.3/FFT_Flt_R6_W0.c \
#    fft-1.4.3/FFT_Flt_R8_W0.c \
#    fft-1.4.3/FFT_R2_BIT_REV.c \
#    fft-1.4.3/Window/Win_Hann_N256.c \
#    general-algorithms-1.0.6/CircData.c \
#    general-algorithms-1.0.6/NoRepeat.c \
#    general-algorithms-1.0.6/Reed-Solomon/RS_11_7_Tables.c \
#    general-algorithms-1.0.6/Reed-Solomon/RS_15_9_Tables.c \
#    general-algorithms-1.0.6/Reed-Solomon/RS_7_5_Tables.c \
#    general-algorithms-1.0.6/Reed-Solomon/RS.c \
#    naes2-decoder-4.1.1/N2_BitSnr.c \
#    naes2-decoder-4.1.1/N2M.c \
#    naes2-decoder-4.1.1/N2S.c \
#    naes2-decoder-4.1.1/N2_SymSnr.c \
#    naes6-decoder-4.1.3/N6_BinSnr.c \
#    naes6-decoder-4.1.3/N6M.c \
#    naes6-decoder-4.1.3/N6S.c \
#    naes6-decoder-4.1.3/N6_SymSnr.c \
#    unified-event-generator-2.3.1/UEG.c \
#    unified-event-generator-2.3.1/Mapping/CMap_Lookup_TAMPA_1.c \
#    -lm

#gcc -std=c11 -Wall -Wextra -O3 -o uegnano-new \
#    -Iaudio-downsampler-2.4.8/ \
#    -Icbet-decoder-s-2.1.3/ \
#    -Ifft-1.4.3/ -Ifft-1.4.3/Window/ \
#    -Igeneral-algorithms-1.0.7/ -Igeneral-algorithms-1.0.7/Reed-Solomon/ \
#    -Inaes2-decoder-4.1.3/ \
#    -Inaes6-decoder-4.1.4/ \
#    -Iunified-event-generator-2.3.3/ -Iunified-event-generator-2.3.3/Mapping/ \
#    uegnano.c \
#    audio-downsampler-2.4.8/decimate.c \
#    audio-downsampler-2.4.8/Resample_2to3_Int.c \
#    cbet-decoder-s-2.1.3/CBET_BinSnr.c \
#    cbet-decoder-s-2.1.3/CBET.c \
#    cbet-decoder-s-2.1.3/CBET_SymSnr.c \
#    fft-1.4.3/FFT_Flt_3KR4.c \
#    fft-1.4.3/FFT_Flt_4KR4.c \
#    fft-1.4.3/FFT_Flt_Combine.c \
#    fft-1.4.3/FFT_FLT_COS_3072.c \
#    fft-1.4.3/FFT_FLT_COS_4096.c \
#    fft-1.4.3/FFT_Flt_R3_W0.c \
#    fft-1.4.3/FFT_Flt_R4_W0.c \
#    fft-1.4.3/FFT_Flt_R4_WM_WL.c \
#    fft-1.4.3/FFT_Flt_R6_W0.c \
#    fft-1.4.3/FFT_Flt_R8_W0.c \
#    fft-1.4.3/FFT_R2_BIT_REV.c \
#    fft-1.4.3/Window/Win_Hann_N256.c \
#    general-algorithms-1.0.7/CircData.c \
#    general-algorithms-1.0.7/NoRepeat.c \
#    general-algorithms-1.0.7/Reed-Solomon/RS_11_7_Tables.c \
#    general-algorithms-1.0.7/Reed-Solomon/RS_15_9_Tables.c \
#    general-algorithms-1.0.7/Reed-Solomon/RS_7_5_Tables.c \
#    general-algorithms-1.0.7/Reed-Solomon/RS.c \
#    naes2-decoder-4.1.3/N2_BitSnr.c \
#    naes2-decoder-4.1.3/N2M.c \
#    naes2-decoder-4.1.3/N2S.c \
#    naes2-decoder-4.1.3/N2_SymSnr.c \
#    naes6-decoder-4.1.4/N6_BinSnr.c \
#    naes6-decoder-4.1.4/N6M.c \
#    naes6-decoder-4.1.4/N6S.c \
#    naes6-decoder-4.1.4/N6_SymSnr.c \
#    unified-event-generator-2.3.3/UEG.c \
#    unified-event-generator-2.3.3/Mapping/CMap_Lookup_TAMPA_1.c \
#    -lm

gcc -std=c11 -Wall -Wextra -O3 -o uegnano-new \
    -Iaudio-downsampler-2.4.8/ \
    -Icbet-decoder-s-2.1.3/ \
    -Ifft-1.4.3/ -Ifft-1.4.3/Window/ \
    -Igeneral-algorithms/ -Igeneral-algorithms/Reed-Solomon/ \
    -Inaes2-decoder-4.1.3/ \
    -Inaes6-decoder-4.1.4/ \
    -Iunified-event-generator-2.3.3/ -Iunified-event-generator-2.3.3/Mapping/ \
    uegnano.c \
    audio-downsampler-2.4.8/decimate.c \
    audio-downsampler-2.4.8/Resample_2to3_Int.c \
    cbet-decoder-s-2.1.3/CBET_BinSnr.c \
    cbet-decoder-s-2.1.3/CBET.c \
    cbet-decoder-s-2.1.3/CBET_SymSnr.c \
    fft-1.4.3/FFT_Flt_3KR4.c \
    fft-1.4.3/FFT_Flt_4KR4.c \
    fft-1.4.3/FFT_Flt_Combine.c \
    fft-1.4.3/FFT_FLT_COS_3072.c \
    fft-1.4.3/FFT_FLT_COS_4096.c \
    fft-1.4.3/FFT_Flt_R3_W0.c \
    fft-1.4.3/FFT_Flt_R4_W0.c \
    fft-1.4.3/FFT_Flt_R4_WM_WL.c \
    fft-1.4.3/FFT_Flt_R6_W0.c \
    fft-1.4.3/FFT_Flt_R8_W0.c \
    fft-1.4.3/FFT_R2_BIT_REV.c \
    fft-1.4.3/Window/Win_Hann_N256.c \
    general-algorithms/CircData.c \
    general-algorithms/NoRepeat.c \
    general-algorithms/Reed-Solomon/RS_11_7_Tables.c \
    general-algorithms/Reed-Solomon/RS_15_9_Tables.c \
    general-algorithms/Reed-Solomon/RS_7_5_Tables.c \
    general-algorithms/Reed-Solomon/RS.c \
    naes2-decoder-4.1.3/N2_BitSnr.c \
    naes2-decoder-4.1.3/N2M.c \
    naes2-decoder-4.1.3/N2S.c \
    naes2-decoder-4.1.3/N2_SymSnr.c \
    naes6-decoder-4.1.4/N6_BinSnr.c \
    naes6-decoder-4.1.4/N6M.c \
    naes6-decoder-4.1.4/N6S.c \
    naes6-decoder-4.1.4/N6_SymSnr.c \
    unified-event-generator-2.3.3/UEG.c \
    unified-event-generator-2.3.3/Mapping/CMap_Lookup_TAMPA_1.c \
    -lm
