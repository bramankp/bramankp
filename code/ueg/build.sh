gcc -std=c11 -Wall -Wextra -O3 -o uegnano \
    -Iaudio-downsampler/ \
    -Icbet-decoder-s/ \
    -Ifft/ -Ifft/Window/ \
    -Igeneral-algorithms/ -Igeneral-algorithms/Reed-Solomon/ \
    -Inaes2-decoder/ \
    -Inaes6-decoder/ \
    -Iunified-event-generator/ -Iunified-event-generator/Mapping/ \
    uegnano.c \
    audio-downsampler/decimate.c \
    audio-downsampler/Resample_2to3_Int.c \
    cbet-decoder-s/CBET_BinSnr.c \
    cbet-decoder-s/CBET.c \
    cbet-decoder-s/CBET_SymSnr.c \
    fft/FFT_Flt_3KR4.c \
    fft/FFT_Flt_4KR4.c \
    fft/FFT_Flt_Combine.c \
    fft/FFT_FLT_COS_3072.c \
    fft/FFT_FLT_COS_4096.c \
    fft/FFT_Flt_R3_W0.c \
    fft/FFT_Flt_R4_W0.c \
    fft/FFT_Flt_R4_WM_WL.c \
    fft/FFT_Flt_R6_W0.c \
    fft/FFT_Flt_R8_W0.c \
    fft/FFT_R2_BIT_REV.c \
    fft/Window/Win_Hann_N256.c \
    general-algorithms/CircData.c \
    general-algorithms/NoRepeat.c \
    general-algorithms/Reed-Solomon/RS_11_7_Tables.c \
    general-algorithms/Reed-Solomon/RS_15_9_Tables.c \
    general-algorithms/Reed-Solomon/RS_7_5_Tables.c \
    general-algorithms/Reed-Solomon/RS.c \
    naes2-decoder/N2_BitSnr.c \
    naes2-decoder/N2M.c \
    naes2-decoder/N2S.c \
    naes2-decoder/N2_SymSnr.c \
    naes6-decoder/N6_BinSnr.c \
    naes6-decoder/N6M.c \
    naes6-decoder/N6S.c \
    naes6-decoder/N6_SymSnr.c \
    unified-event-generator/UEG.c \
    unified-event-generator/Mapping/CMap_Lookup_TAMPA_1.c \
    -lm

#gcc -std=c11 -Wall -Wextra -Wno-unused-function -O3 -o uegnano \
#    -Iaudio-downsampler/ \
#    -Icbet-decoder-s/ \
#    -Ifft/ -Ifft/Window/ \
#    -Igeneral-algorithms/ -Igeneral-algorithms/Reed-Solomon/ \
#    -Inaes2-decoder/ -Inaes2-decoder/Nano \
#    -Inaes6-decoder/ \
#    -Iunified-event-generator/ \
#    uegnano.c \
#    audio-downsampler/decimate.c \
#    audio-downsampler/Resample_2to3_Int.c \
#    cbet-decoder-s/CBET_BinSnr.c \
#    cbet-decoder-s/CBET.c \
#    cbet-decoder-s/CBET_SymSnr.c \
#    fft/FFT_Flt_3KR4.c \
#    fft/FFT_Flt_4KR4.c \
#    fft/FFT_Flt_Combine.c \
#    fft/FFT_FLT_COS_3072.c \
#    fft/FFT_FLT_COS_4096.c \
#    fft/FFT_Flt_R3_W0.c \
#    fft/FFT_Flt_R4_W0.c \
#    fft/FFT_Flt_R4_WM_WL.c \
#    fft/FFT_Flt_R6_W0.c \
#    fft/FFT_Flt_R8_W0.c \
#    fft/FFT_R2_BIT_REV.c \
#    fft/Window/Win_Hann_N256.c \
#    general-algorithms/CircData.c \
#    general-algorithms/NoRepeat.c \
#    general-algorithms/Reed-Solomon/RS_11_7_Tables.c \
#    general-algorithms/Reed-Solomon/RS_15_9_Tables.c \
#    general-algorithms/Reed-Solomon/RS_7_5_Tables.c \
#    general-algorithms/Reed-Solomon/RS.c \
#    naes2-decoder/N2_BitSnr.c \
#    naes2-decoder/N2M.c \
#    naes2-decoder/N2S.c \
#    naes2-decoder/N2_SymSnr.c \
#    naes2-decoder/Nano/Nano_Bin_Adjust.c \
#    naes6-decoder/N6_BinSnr.c \
#    naes6-decoder/N6M.c \
#    naes6-decoder/N6S.c \
#    naes6-decoder/N6_SymSnr.c \
#    unified-event-generator/UEG.c \
#    -lm

#gcc -std=c11 -Wall -Wextra -Wno-unused-function -O3 -o uegtest \
#    -Iaudio-downsampler/ \
#    -Icbet-decoder-s/ \
#    -Ifft/ -Ifft/Window/ \
#    -Igeneral-algorithms/ -Igeneral-algorithms/Reed-Solomon/ \
#    -Inaes2-decoder/ \
#    -Inaes6-decoder/ \
#    -Iunified-event-generator/ \
#    uegtest.c \
#    audio-downsampler/decimate.c \
#    cbet-decoder-s/CBET_BinSnr.c \
#    cbet-decoder-s/CBET.c \
#    cbet-decoder-s/CBET_SymSnr.c \
#    fft/FFT_Flt_3KR4.c \
#    fft/FFT_Flt_4KR4.c \
#    fft/FFT_Flt_Combine.c \
#    fft/FFT_FLT_COS_3072.c \
#    fft/FFT_FLT_COS_4096.c \
#    fft/FFT_Flt_R3_W0.c \
#    fft/FFT_Flt_R4_W0.c \
#    fft/FFT_Flt_R4_WM_WL.c \
#    fft/FFT_Flt_R6_W0.c \
#    fft/FFT_Flt_R8_W0.c \
#    fft/FFT_R2_BIT_REV.c \
#    fft/Window/Win_Hann_N256.c \
#    general-algorithms/CircData.c \
#    general-algorithms/NoRepeat.c \
#    general-algorithms/Reed-Solomon/RS_11_7_Tables.c \
#    general-algorithms/Reed-Solomon/RS_15_9_Tables.c \
#    general-algorithms/Reed-Solomon/RS_7_5_Tables.c \
#    general-algorithms/Reed-Solomon/RS.c \
#    naes2-decoder/N2_BitSnr.c \
#    naes2-decoder/N2M.c \
#    naes2-decoder/N2S.c \
#    naes2-decoder/N2_SymSnr.c \
#    naes6-decoder/N6_BinSnr.c \
#    naes6-decoder/N6M.c \
#    naes6-decoder/N6S.c \
#    naes6-decoder/N6_SymSnr.c \
#    unified-event-generator/UEG.c \
#    -lm

#gcc -std=c11 -Wall -Wextra -pedantic -O3 -o WavToUEG \
#    -Iaudio-downsampler/ \
#    -Ifft/ \
#    -Ifft/Window/ \
#    -Igeneral-algorithms/ -Igeneral-algorithms/Reed-Solomon/ -Igeneral-algorithms/Test/ \
#    -Icbet-decoder-s/ \
#    -Inaes2-decoder/ \
#    -Inaes2-decoder/Nano/ \
#    -Inaes6-decoder/ \
#    -Iunified-event-generator/ -Iunified-event-generator/Mapping/ \
#    audio-downsampler/decimate.c \
#    audio-downsampler/Resample_2to3_Flt.c \
#    fft/FFT_Flt_3KR4.c \
#    fft/FFT_Flt_4KR4.c \
#    fft/FFT_Flt_Combine.c \
#    fft/FFT_FLT_COS_3072.c \
#    fft/FFT_FLT_COS_4096.c \
#    fft/FFT_Flt_R3_W0.c \
#    fft/FFT_Flt_R4_W0.c \
#    fft/FFT_Flt_R4_WM_WL.c \
#    fft/FFT_Flt_R6_W0.c \
#    fft/FFT_Flt_R8_W0.c \
#    fft/FFT_R2_BIT_REV.c \
#    fft/Window/Win_Hann_N256.c \
#    general-algorithms/CircData.c \
#    general-algorithms/NoRepeat.c \
#    general-algorithms/Reed-Solomon/RS_11_7_Tables.c \
#    general-algorithms/Reed-Solomon/RS_15_9_Tables.c \
#    general-algorithms/Reed-Solomon/RS_7_5_Tables.c \
#    general-algorithms/Reed-Solomon/RS.c \
#    general-algorithms/Test/wav.c \
#    cbet-decoder-s/CBET.c \
#    cbet-decoder-s/CBET_BinSnr.c \
#    cbet-decoder-s/CBET_SymSnr.c \
#    naes2-decoder/N2M.c \
#    naes2-decoder/N2S.c \
#    naes2-decoder/N2_BitSnr.c \
#    naes2-decoder/N2_SymSnr.c \
#    naes2-decoder/Nano/Nano_Bin_Adjust.c \
#    naes6-decoder/N6M.c \
#    naes6-decoder/N6S.c \
#    naes6-decoder/N6_BinSnr.c \
#    naes6-decoder/N6_SymSnr.c \
#    unified-event-generator/UEG.c \
#    unified-event-generator/Mapping/CMap_Lookup_TAMPA_1.c \
#    unified-event-generator/Test/WavToUEG.c \
#    -lm
