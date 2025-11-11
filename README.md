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
WebAssembly using f2c and emscripten. Using a virtual file system, runs
are performed locally on a web browser, and models downloadable during
and between execution steps.

The yreclab ecosystem is designed for reproducibility; it ingests and
generates self-contained archive files consisting of namelists,
structure files, track files, and an included run manifest file. In this
way, stellar structure model runs can be easily shared, debugged, and
published.

Documentation for the usage of YREC can be found at:
[https://yrec.readthedocs.io/](https://yrec.readthedocs.io/).

# Live Usage

A permanent static hosted version of this repository lives at
[https://yreclab.github.io/](https://yreclab.github.io/).

# Editing & Building

Although the current stable version of yreclab can be downloaded
directly from [https://github.com/yreclab/yreclab.github.io](https://github.com/yreclab/yreclab.github.io)
and self-hosted, it may be useful at times to make custom modifications
to the YREC internals and compile a new version.

## Installing Emscripten

Emscripten is required for compiling and linking the C sources to wasm.

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install 4.0.19
./emsdk activate 4.0.19
source ./emsdk_env.sh
```

## Compilation

To build, simply `make clean; make all`. Binaries will be found in the
`bin/` folder, and intermediate build products in the `build/` folder.

As a C and WebAssembly code, YREC can also be compiled natively as a C
framework or to target Node.js as well.

## Differences from stock YREC (v. 5.1) or `f2c`'ed output

Original YREC source files for the current distribution of yreclab are
found in `src/yrec-f`. Most of these source files are converted to C via
the `f2c` utility, and placed in `src/yrec-c`. However, modifications
are made to source files to preserve proper type definitions with `f2c`. 

Making modifications to yreclab locally is possible by editing the C
code in `src/yrec-c` and recompiling. Some notable differences between
the stable versions of yreclab and YREC currently include:

- `yrec-f/step.f`: an alternative driver for YREC which does a single
timestep.
- `yrec-c/step.c`: modified from `step.f` with return values to indicate
run status.
- `src/yrec_c_defs.c`: defines common blocks for linking with `emcc`
- variable length arrays are not supported (`boole.f` and `splinj.f`)

In some cases, `f2c` will incorrectly emit the wrong type during
translation, which will lead to a
`warning: function signature mismatch`.
In these cases, it is easiest to edit the C file directly.

# Self-hosting

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

## Running yreclab in Node.js

In the `bin/` directory after compilation, or by downloading the
prebuilt `yrec.js` and `yrec.wasm` binaries from
[https://github.com/yreclab/yreclab.github.io](https://github.com/yreclab/yreclab.github.io),
the base code can be initialized as follows:

```
const YREC = require('./yrec.js');

const config = {
	onRuntimeInitialized() {
	    console.info("YREC initialized.");
	},
};

var yrec_run = await YREC(config);
```

Thereafter, the run can be performed to completion without interactivity
with:
```
yrec_run._MAIN__();
```

Or, individual steps can be taken with:
```
yrec_run._step_();
```

The virtual file system can then be accessed with the `yrec_run.FS`
object. For instance, to write `data` to a new namelist at the default
`yrec8.nml1` location:
```
yrec_run.FS.writeFile("yrec8.nml1", new TextEncoder().encode(data));
```

Or to read a file at `output.track`:
```
TextDecoder().decode(yrec_run.FS.readFile("output.track"));
```

To list the contents of the current directory:
```
yrec_run.FS.readdir('.')
```

# Contributions

Contributions are welcome!

This repository accepts contributions and issues involving the yreclab
ecosystem, modules, and scripts only. For contributions to the main YREC
Fortran code, please open an issue at [https://github.com/yreclab/yrec](https://github.com/yreclab/yrec).
