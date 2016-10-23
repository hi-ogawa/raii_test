# Resource Allocation is Initialization (non-gc memory management)

```
$ clang++-3.8 --version
clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
$ g++ --version
g++ (Ubuntu 5.4.0-6ubuntu1~16.04.2) 5.4.0 20160609
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ make
g++ main.cc -o main_gnu -std=c++11
main.cc: In function ‘PointC* SomeInit0()’:
main.cc:17:10: warning: address of local variable ‘p0’ returned [-Wreturn-local-addr]
   PointC p0(3, 4);
          ^
clang++-3.8 main.cc -o main_clang -std=c++11
main.cc:18:11: warning: address of stack memory associated with local
      variable 'p0' returned [-Wreturn-stack-address]
  return &p0; // warning -Wreturn-local-addr
          ^~
1 warning generated.
$ ./main_gnu
p: 7
p: 7
q: 7
q: 7
r0: 5
r1: 5
r0: 5
s0: 7
s1: 7
s0: 7
t0: 7
t1: 7
t0: 7
u0: 7
Segmentation fault (core dumped)
$ ./main_clang
p: 7
p: 7
q: 7
q: 7
r0: 5
r1: 5
r0: 5
s0: 7
s1: 7
s0: 7
t0: 7
t1: 7
t0: 7
u0: 7
v0: 7
```

---

- c++
- rust

- smart pointers
  - unique pointer
  - shared pointer
  - weak pointer

- implement unique, shared, weak pointer (or at least look at implementation)

# References

- http://open-std.org/JTC1/SC22/WG21/docs/papers/2016/n4606.pdf
  - 1 General
    - 1.8 The C++ object model
    - 1.9 Program execution
  - 3 Basic concepts
    - 3.6.4 Termination (when destructor is called for each storage pattern)
    - 3.7 storage duration
  - 7 Declarations
    - 7.1.1 Storage class specifiers
  - 8 Declarators
  - 12 Special member functions
  - 15 Exception handling
- http://www.chromium.org/developers/smart-pointer-guidelines
- https://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization
- https://en.wikipedia.org/wiki/Smart_pointer
- https://msdn.microsoft.com/en-us/library/hh279674.aspx
- http://www.wellho.net/mouth/3069_Strings-Garbage-Collection-and-Variable-Scope-in-C-.html
- http://stackoverflow.com/questions/228620/garbage-collection-in-c-why
