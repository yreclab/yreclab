yreclab
=======

The Yale Rotating Evolution Code (YREC) laboratory.

YREC is a public stellar evolution code optimized for the study of stars
from the pre-main sequence to the helium burning phase of evolution. It
natively incorporates physics relevant to stellar rotation, internal
mixing, angular momentum loss, and magnetic starspots with modern
microphysics.

yreclab is a modern reinterpretation of YREC on the web, as a framework
to interactively run, pause, monitor, upload, batch, and evolve stellar
structure models. In order to accomplish this, the underlying YREC
code, with custom hooks to enable interactivity, is compiled to
WebAssembly using f2c and emscripten. Using a virtual file system, 
Interactive scripts, hooks, and test suite cases are 

This repository accepts contributions and issues involving the yreclab
ecosystem, modules, and scripts only. For contributions to the main YREC
Fortran code, please open an issue at [https://github.com/yreclab/yrec](https://github.com/yreclab/yrec).

# Building

The original YREC source files for the current distribution of yreclab
are found in `src/yrec-f`. Most of these source files are converted to C
via the `f2c` utility, and placed in `src/yrec-c`. However, several
modifications are made to source files to preserve proper type
definitions with `f2c`.

## Installing Emscripten

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install 4.0.19
./emsdk activate 4.0.19
source ./emsdk_env.sh
```

## Obtaining CLAPACK

A copy of CLAPACK-3.2.1 and the associated f2c library are included
in this repository for reproducibility between builds.

## Compilation

To build, simply `make clean; make all`. Binaries will be 

As a C and WebAssembly code, YREC can also be compiled natively as a C
framework or to target Node.js as well.

# Usage

In order to run yreclab in the web context, start a web server in the
`bin/` directory; for instance, using node, you can install the
`http-server` package:

```
npm install http-server -g
```

And subsequently serve the static folder:

```
http-server -p 8080 bin/
```
