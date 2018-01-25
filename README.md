# `#define EVIL`
*It's amazing what you can do with macros if you don't have any morals.*

## What is this?
There's one thing everyone can agree on, macros in C++ are evil. At first glance, they're a quick-and-dirty way of defining constants, but take a closer look, and you'll find a disturbing truth. Macros can consume arbitrary numbers of arguments, expand to other macros, perform logic and almost-sorta-kinda be recursive, all with complete disregard of the syntactic correctness of the code they are expanding to. Welcome to a world where everything could be anything and nothing is as it seems. Welcome to `#define EVIL`.

## No, actually, what is this?
It's an MIT licensed collection of clean, modular, well documented macro hacks with full unit test coverage.

## Why?
It is not advisable to use these (or any) complex macros in 'normal' production code, but they could be useful in specific cases. For example, suppose you need a domain specific language, but are too lazy to build one properly. You could use `#define EVIL` macros to construct a language that is technically C++ (gets compiled by any C++ compiler) but looks and feels quite different. An extreme example of this is [Python++](https://github.com/wmww/Python-plus-plus), where many of these ideas originated. `#define EVIL` was created to split out and clean up the reusable bits of Python++.

## Files
* [define_EVIL.h](define_EVIL.h): most of the macros
* [autogen.h](autogen.h): auto generated macros (if you see a macro starting with `_AG_`, its in this file).
* [autogen.sh](autogen.sh): a shell script that generates autogen.h
* [tests.cpp](tests.cpp): unit tests for all macros

## Running tests
To run the tests, just clone this repo, `cd` into it and run `make && ./tests_bin`. Make will run autogen.sh if needed.

## Using
Before incorporating into another project, you may want to copy the contents of autogen.h into define_EVIL.h, so you only have to manage one file. You may even want to only copy the macros you want from define\_EVIL.h, just make sure you also grab all helpers (macros starting with `_` directly below the ones you want to use) and all the ones they depend on recursively (the dependencies for each macro should be documented)
