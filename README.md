# libsutil

This is sudo200's utility library, originally developed just for fun, \
it kind of became a kitchen-sink library for everything from argument parsing, file handling \
to entire data structures.

# Current features

* Unopinionated dynamic memory managment.
* Short- and long option argument parsing, with \
  support for optional or required arguments.
* Arraylist (fast random access to stored elements).
* Linked list (fast random element insertion and removal).
* Queue and Stack in capped and uncapped versions.
* Threadsafe queue (mutex locking)
* Hashmap
* Hashset
* Minimal logging framework with seven verbosity levels \
  (TRACE, DEBUG, INFO, NOTICE, WARNING, ERROR, FATAL).
* String functions with dynamic (re)allocation.
* Various file funcions.
* Various other utility functions.

# File structure

```
+- .gitignore
|
+- README.md
|
+- UNLICENSE
|
+- Makefile
|
+- src/ (C-Sourcefiles)
|
+- include/ (C-Headers)
|
+- test/ ("Unit-tests" for library parts)
```

# Building

***NOTICE***: This library is only aimed at POSIX compliant systems \
and was as of now only tested on Linux.

You have to have `binutils`, `make` and a C compiler (e.g. `clang`) installed on your system.

1. Clone this repo and cd into it: \
`$ git clone https://github.com/sudo200/libsutil.git` \
`$ cd libsutil`
2. Run `make`:
`$ make`

*Note*: If make says it cannot find cc, \
you have to do this:
`$ make CC='<your compiler-name here>'`

# Contributing

![YES](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fi.imgflip.com%2F4qqr9i.jpg&f=1&nofb=1)

