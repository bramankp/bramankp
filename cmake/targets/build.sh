rm -rf build-gtam && mkdir build-gtam
( cd build-gtam && cmake -DCMAKE_TOOLCHAIN_FILE=../gtam.cmake .. && cmake --build . )
rm -rf build-gtlt && mkdir build-gtlt
( cd build-gtlt && cmake -DCMAKE_TOOLCHAIN_FILE=../gtlt.cmake .. && cmake --build . )
