# Open Questions

## 22.08.2019 Build submodule from cmake

At the moment it works, but it builds on every `make`. Most likely I need to change the OUTPUT parameter.

## 19.07.2019 External Dependencies (follow up)

Works fine so far with subrepositories.

## 15.07.2019 Using gcc-8 with cmake (follow up)

Clean VM Setup has no problems. gcc-8 has the problem on my system:

~~~sh
$ gcc-8 test.c
gcc-8: internal compiler error: Segmentation fault signal terminated program cc1
Please submit a full bug report,
with preprocessed source if appropriate.
See <file:///usr/share/doc/gcc-8/README.Bugs> for instructions.
~~~

where `test.c` is just

~~~C
int main() { return 0; }
~~~

which works fine with `gcc-7`.

## 07.07.2019 External Dependencies

- What is a good choice for the place to put them/avoid giving a global path?
  - Use Build dir again?
- But how to avoid downloading/compiling them too often?

## 06.07.2019 Using gcc-8 with cmake (37)

So far I used gcc-7, but filesystem is not included. Everything works with clang-7.
I didn't get gcc-8 to work:

~~~sh
cmake -DCMAKE_C_COMPILER=/usr/bin/clang-7 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-7 ../ #works
cmake -DCMAKE_C_COMPILER=/usr/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/bin/g++-8 ../ #doesn't work
~~~

It stalls and never finishes to run.
Compiling on the commandline works fine:

~~~sh
g++-8 -std=c++17 ../37_finding_files/finding_files.cpp -lstdc++fs -o finding_files
~~~

Since cmake and g++-8 work I guess that it is some setup problem. Will be continued.
