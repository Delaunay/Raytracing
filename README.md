project_test
============

This is a skeleton of a C++ project.
The project is using the following tools:

* Test Framework: Google Test
* Documentation Gen: Sphinx
* Build Tool: CMake
* Version Control System: Git
* Dependencies: CMake + [(Git & gitmodules)(*)]
* Performance: Hayai(**)

(\*) (**) subject to change in a near future

(**) Hayai print too much redundant information

(*) because of Code redundancy. Most people will use the latest working
version which means there is no need for each projects to have their own
gtest(or else) repo (10 projects = 10 identical copies of gtest ? Noway.
But it does make a lot of pain go away)


# Configuration

## Directory Layout

    src/          : Project Code source
    cmake/        : CMake Scripts (FindXXX.cmake)
    tests/        : Tests files (***_test.cpp)
    benchmark/    : Performance tests (***_bench.cpp)
    docs/         : Doxygen or Sphinx files
    data/         : Data (Used to store Performance results for each git commit)
    build/        : git ignored folder in which you can build the project
    dependencies/ : Dependencies source code

## Benchmark

(NOT IMPLEMENTED)
When checking your application performance you may want to check against previous
performance. This is why `Benchmark` save execution time per commit so performance
evolution can be easily tracked. Since performance is linked to your machine
performance information is not saved inside the repository.

# How to

## Create a library/executable

* create a new folder `src/new_library` or `src/new_exec`
* add `src/new_library/src/CMakeLists.txt`
* create library files (`.cpp` and `.h`)
* create new CMake variable with library's files

	 	SET(MY_LIBRARY_SRC
		    file1.h
		    file1.cpp
		    file2.h
		    file2.cpp
		)

* Add the compile command:

	    ADD_LIBRARY(my_library ${MY_LIBRARY_SRC})
		SET_PROPERTY(TARGET my_library PROPERTY CXX_STANDARD 11)

				OR

	    ADD_EXECUTABLE(my_exec ${MY_LIBRARY_SRC})
	    TARGET_LINK_LIBRARIES(my_exec dependencies)
	    SET_PROPERTY(TARGET my_exec PROPERTY CXX_STANDARD 11)

## Add test header

* create file `stuff_test.h`
* add `#include "stuff_test.h"` to the `**_test.cpp`

## Add test executable

* create a new file `my_newtest_test.cpp`
* add `TEST_MACRO(my_newtest)` at the end of the file `tests/CMakeLists.txt`

## Add Benchmark

* create a new file `my_newbench_bench.cpp`
* add `TEST_BENCH(my_newbench)` at the end of the file `benchmark/CMakeLists.txt`

## Add (to be compiled) Dependency

* open git bash
* go to the project repo
* `git submodule add url_to_dependency_repo dependencies/library_name`

Example: add `opencv` to the project

    git submodule add https://github.com/Itseez/opencv.git dependencies/opencv
    git submodule add https://github.com/google/googletest.git dependencies/gtest

## Add pre-compiled Dependencies

* Add `FindXXX.cmake` script in the `cmake/` folder
* Add `FIND_PACKAGE(XXX)` in `./CMakeLists.txt`  (pre-compiled section)


    	FIND_PACKAGE(openCV)

# Requirement

* C++ Compiler
* Python (gtest)
* CMake
* Git
* [Sphinx, Doxygen] (*)

(*) Optional


TODO
====

* How to
* Valgrind utils/Sanitizer Command/debbuger

        # Need to find a better way
        # Hardcoded:
        SET(LEAK_FLAG " -Werror -fsanitize=leak ") # this for clang
        SET(CMAKE_CXX_FLAGS ${LEAK_FLAG})

        # would be nice to have something like:
        # for each target "xyz" we have a
            - make san/leak/xyz
            - make san/thread/xyz
            - make lld/xyz
            - make format
            - make tidy
        # need to check how much caching is done between each exec version

* Profiling
* Goole Perf ?
* Nonius ? <== Need to be updated
* hayai ?
* Configuration files
* Generated files
* Empirical Complexity Analysis would be nice

Bug
===

* `gtest` does not compile with `MinGW`. This a` MinGW` bug. You need to deactivate
pthreads for it to work (`-Dgtest_disable_pthreads=ON`)

* travis gcc compiler has some trouble with C++11 and CMake (CXX_STANDARD 11)
`final` was not recognized in one of my project. I do use GCC by default on
all my projects but I use clang for travis because of that.
