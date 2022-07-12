CONFIG="Release"

mkdir -p build_osx && cd build_osx
cmake -DCMAKE_BUILD_TYPE=$CONFIG -GXcode ../
cd ..
cmake --build build_osx --config $CONFIG
