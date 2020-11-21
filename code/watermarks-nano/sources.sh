git archive 2.4.2 --remote git@gitlab.com:nielsen-media/eng/core-algorithms/audio-downsampler.git --prefix audio-downsampler-2.4.2/ | tar --extract --touch --no-same-owner --file -
git archive 3.0.2 --remote git@gitlab.com:nielsen-media/eng/core-algorithms/naes2-decoder.git --prefix naes2-decoder-3.0.2/ | tar --extract --touch --no-same-owner --file -
git archive 3.0.6 --remote git@gitlab.com:nielsen-media/eng/core-algorithms/naes6-decoder.git --prefix naes6-decoder-3.0.6/ | tar --extract --touch --no-same-owner --file -
git archive v2.1.3 --remote git@gitlab.com:nielsen-media/eng/core-algorithms/watermark-filter.git --prefix watermark-filter-2.1.3/ | tar --extract --touch --no-same-owner --file -
git archive 4.9 --remote git@gitlab.com:nielsen-media/eng/meters/nano/nano.git --prefix cbet-decoder/ | tar --extract --touch --no-same-owner --file -
mv cbet-decoder/Sources/lib/cbet/CBET/ cbet-decoder-nano/
mv cbet-decoder/Sources/lib/cbet/cbet_decode_top.h cbet-decoder-nano/
rm -rf cbet-decoder
