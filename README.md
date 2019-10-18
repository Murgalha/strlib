# strlib

## About
I decided to write this simple library after getting tired of rewriting the same piece of code over and over again on my university projects. The library contains functions that create, delete, join and split dynamic strings. 


## Compilation
To compile, run the `make` command on the root of this repo.


## Installation
### Local install
Use `make` to compile the library into a .so file. If you want to use the lib this way, copy the generated file to your desired folder and compile your project with `-L<dir>`, being `<dir>` the location of the library. 

### System-wide install
To install it system-wide, compile it with `make`, then, run `make install` to install it.


