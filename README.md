# moder_cpp_challenge

Implementing problems from "The Modern C++ Challenge" by Marius Bancila

[Git repo with solutions](https://github.com/PacktPublishing/The-Modern-Cpp-Challenge)

Clean build with g++-8:

~~~sh
CURRENT_DIR=$(pwd)
mkdir -p build
cd build
rm -rf *
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/bin/g++-8 ../
make
~~~

Clean build with clang-7:

~~~sh
CURRENT_DIR=$(pwd)
mkdir -p build
cd build
rm -rf *
cmake -DCMAKE_C_COMPILER=/usr/bin/clang-7 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-7 ../
make
~~~
