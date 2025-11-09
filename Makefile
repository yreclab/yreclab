# yreclab makefile
# ================

NAME          = yrec
YREC_SRC_DIR  = src/yrec-c
BUILD         = build
BIN           = bin
STATIC_DIR    = src/static

# Emscripten toolchain
CC            = emcc
AR            = emar

# Compiler + linker flags
CFLAGS   = -O3 -fcommon -fno-lto -ICLAPACK-3.2.1/INCLUDE -emit-llvm -c
# Optional flag for speedups
CFLAGS  += -ffast-math -fno-math-errno
LDFLAGS  = -O3 -s WASM=1 \
           -s INITIAL_MEMORY=134217728 -s TOTAL_MEMORY=134217728 \
           -s EXPORTED_FUNCTIONS='["_MAIN__"]' \
           -fno-lto -s ALLOW_MEMORY_GROWTH=1 \
           --post-js src/build-resources/export.js \
           --embed-file src/build-resources/yrec8.nml1@yrec8.nml1 --embed-file src/build-resources/yrec8.nml2@yrec8.nml2 \
           --embed-file src/build-resources/input@input --embed-file src/build-resources/output@output

# Library source directories
CLAPACK_DIR = CLAPACK-3.2.1
LIBF2C_DIR  = $(CLAPACK_DIR)/F2CLIBS/libf2c
LAPACK_DIR  = $(CLAPACK_DIR)/SRC
BLAS_DIR    = $(CLAPACK_DIR)/BLAS/SRC

# Sources:

YREC_SRCS := $(addprefix $(YREC_SRC_DIR)/, \
  yrec_c_defs.c alex06tab.c alfilein.c alprint.c alsurfp.c \
  altabinit.c alx8th.c alxtbl.c alxztab.c amcalc.c bandw.c \
  blkdta000.c boole.c bsrotmix.c bsstep.c bursmix.c calcad.c \
  cases.c ccoeft.c checkc.c checkj.c chkcal.c chkscal.c choose.c \
  codiff.c coefft.c condopacp.c condopacpint.c convec.c cowind.c \
  crrect.c cspline.c ctridi.c dadcoeft.c dburn.c dburnm.c dcoeft.c \
  deutrate.c engeb.c entime.c envint.c eq2mod.c eqbound01.c \
  eqbound06.c eqbound.c eqburn.c eqrelv.c eqsaha.c eqscve.c eqscvg.c \
  eqstat2.c eqstat.c equal_to_model.c esac01.c esac06.c esac.c \
  findex.c findsh.c fpft.c func.c getalex06.c getfc.c getgrid.c \
  get_imp_diffco.c getmodel2.c getnewenv.c getopac.c getopal95.c \
  getqua.c getrot.c gettau.c getw.c getyrec7.c gmass01.c gmass06.c \
  gmass.c grsett.c gtlaol2.c gtlaol.c gtpurz.c hpoint.c hra.c \
  hsolve.c hsubp.c htimer.c ifermi12.c inter3.c interp.c intmom.c \
  intpol.c intpt.c intrp2.c kcsurfp.c kemcom.c kspline.c ksplint.c \
  kurucz2.c kurucz.c lax_wendrof1.c lax_wendrof2.c liburn2.c liburn.c \
  lirate88.c lir.c ll4th.c ll95tbl.c locate.c lubksb.c ludcmp.c main.c \
  massloss.c mcowind.c mdot.c meqos.c meval.c mhdpx1.c mhdpx2.c \
  mhdpx.c mhdst1.c mhdst.c mhdtbl.c microdiff.c microdiff_cod.c \
  microdiff_etm.c microdiff_mte.c microdiff_run.c microdiff_setup.c \
  midmod.c mix.c mixcom.c mixcz.c mixgrid.c mmid.c model_to_equal.c \
  momi.c mu.c mwind.c ndifcom.c neutrino.c nulosses.c oeqos01.c \
  oeqos06.c oeqos.c op952d.c op953d.c op954d.c op95xtab.c op95ztab.c \
  osplin.c oversh.c ovrot.c parmin.c pdist.c physic.c pindex.c \
  polint.c ptime.c putmodel2.c putstore.c putyrec7.c qatm.c qenv.c \
  qgauss.c quad.c quadeos01.c quadeos06.c quint.c rabu.c radsub01.c \
  radsub06.c radsub.c rates.c ratext.c rdlaol.c rdzlaol.c readalex06.c \
  readco.c readcoeos01.c readcoeos06.c reduce.c remap.c rhoofp01.c \
  rhoofp06.c rhoofp.c rotgrid.c rotmix.c rscale.c rtab.c sconvec.c \
  search.c seculr.c setcal.c setkrz.c setllo.c setscal.c setscv.c \
  setup_grsett.c setupopac.c setups.c setupv.c shape.c simeqc.c \
  slopes.c sneut.c solid.c splinc.c spline.c splinj.c splinnr.c \
  splint.c splintd2.c splnr.c starin.c stitch.c sulaol.c surfbc.c \
  surfopac.c surfp.c t6rinteos01.c t6rinteos06.c t6rinterp.c taucal.c \
  tauint.c tauintnew.c thdiff.c tpgrad.c trapzd.c tridia.c \
  tridiag_gs.c vcirc.c viscos.c wcz.c wczimp.c wind.c wrthead.c \
  wrtlst.c wrtmil.c wrtmod.c wrtmonte.c wrtout.c wtime.c xrng4.c \
  xtime.c yalo3d.c ykoeff.c yllo2d2.c yllo2d.c yllo3d2.c yllo3d.c \
  ylloc.c ysplin.c ytime.c zero.c zfermim12.c zsulaol.c)

# libf2c runtime
LIBF2C_SRCS := $(addprefix $(LIBF2C_DIR)/, \
  c_abs.c c_div.c c_sqrt.c cabs.c close.c ctype.c \
  d_cnjg.c d_imag.c d_lg10.c d_sign.c endfile.c err.c exit_.c \
  f77_aloc.c fmt.c fmtlib.c i_dnnt.c i_nint.c open.c pow_ci.c \
  pow_dd.c pow_di.c pow_ii.c pow_ri.c pow_zi.c r_cnjg.c r_imag.c \
  r_lg10.c r_sign.c s_cat.c s_cmp.c s_copy.c sfe.c sig_die.c \
  util.c wsfe.c wref.c wrtfmt.c z_abs.c z_div.c z_sqrt.c rdfmt.c \
  xwsne.c lwrite.c rsne.c typesize.c s_paus.c s_rnge.c s_stop.c \
  wsle.c dolio.c lread.c rsfe.c rewind.c d_mod.c iio.c sue.c uio.c \
  i_indx.c wsne.c getarg_.c)

LAPACK_SRCS := $(wildcard $(LAPACK_DIR)/*.c)
BLAS_SRCS   := $(filter-out $(BLAS_DIR)/xerbla.c,$(wildcard $(BLAS_DIR)/*.c))

# Bitcode paths:

YREC_BC    := $(patsubst $(YREC_SRC_DIR)/%.c,   $(BUILD)/yrec-c/%.bc, $(YREC_SRCS))
LIBF2C_BC  := $(patsubst $(LIBF2C_DIR)/%.c,$(BUILD)/libf2c/%.bc,        $(LIBF2C_SRCS))
LAPACK_BC  := $(patsubst $(LAPACK_DIR)/%.c,$(BUILD)/lapack/%.bc,        $(LAPACK_SRCS))
BLAS_BC    := $(patsubst $(BLAS_DIR)/%.c,  $(BUILD)/blas/%.bc,          $(BLAS_SRCS))

LIBF2C_LIB := $(BUILD)/libf2c.a
LAPACK_LIB := $(BUILD)/lapack.a
BLAS_LIB   := $(BUILD)/blas.a

# Targets
.SUFFIXES: .c .bc

all: $(BIN)/$(NAME).html

# Ensure directory structure exists
$(BUILD):
	mkdir -p $(BUILD) $(BUILD)/yrec-c $(BUILD)/libf2c $(BUILD)/lapack \
	$(BUILD)/blas $(BIN)

# Compile .c to .bc
	
$(BUILD)/yrec-c/%.bc: $(YREC_SRC_DIR)/%.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/libf2c/%.bc: $(LIBF2C_DIR)/%.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/lapack/%.bc: $(LAPACK_DIR)/%.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/blas/%.bc: $(BLAS_DIR)/%.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# Archive bitcode into static libraries (.a)
$(LIBF2C_LIB): $(LIBF2C_BC)
	$(AR) rcs $@ $^

$(LAPACK_LIB): $(LAPACK_BC)
	$(AR) rcs $@ $^

$(BLAS_LIB): $(BLAS_BC)
	$(AR) rcs $@ $^

# Final link into WebAssembly
$(BIN)/$(NAME).html: $(YREC_BC) $(LIBF2C_LIB) $(LAPACK_LIB) $(BLAS_LIB)
	$(CC) $^ $(LDFLAGS) -o $@; cp -r $(STATIC_DIR)/* $(BIN)

# Clean
clean:
	rm -rf $(BUILD); rm -rf $(BIN)
