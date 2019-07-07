# Open Questions

## 07.07.2019 External Dependencies

- What is a good choice for the place to put them/avoid giving a global path?
  - Use Build dir again?
- But how to avoid downloading/compiling them too often?

## 06.07.2019 Using gcc-8 with cmake (37)

So far I used gcc-7, but filesystem is not included. Everything works with clang-7.
I didn't get gcc-8 to work:

~~~sh
cmake -DCMAKE_C_COMPILER=/usr/bin/clang-7 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-7 ../ #works
cmake -DCMAKE_C_COMPILER=gcc-8 -DCMAKE_CXX_COMPILER=g++-8 ../ #doesn't work
~~~

It stalls and never finishes to run.
Compiling on the commandline works fine:

~~~sh
g++-8 -std=c++17 ../37_finding_files/finding_files.cpp -lstdc++fs -o finding_files
~~~

Since cmake and g++-8 work I guess that it is some setup problem. Will be continued.
