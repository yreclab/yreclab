/* mu.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MU */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mu_(doublereal *t, doublereal *p, doublereal *d__, 
	doublereal *x, doublereal *z__, doublereal *rmu, doublereal *amu, 
	doublereal *emu, doublereal *beta)
{
    /* Initialized data */

    static doublereal atomwt[4] = { .9921,.24975,.08322,.4995 };

    static doublereal ee, dfx1, dfx4, dfx12;

/* SET UP FRACTIONAL ABUNDANCES */
    dfx1 = *x - comp_1.xenv;
    dfx12 = *z__ - comp_1.zenv;
    if (abs(dfx1) + abs(dfx12) < 1e-5) {
/* USE ENVELOPE ABUNDANCES */
	*amu = comp_1.amuenv;
    } else {
	dfx1 *= atomwt[0];
	dfx12 *= atomwt[2];
	dfx4 = (comp_1.xenv + comp_1.zenv - *x - *z__) * atomwt[1];
/* ASSUME EXCESS Z(METALS) IS IN THE FORM OF CARBON(12) */
	*amu = comp_1.amuenv + dfx1 + dfx4 + dfx12;
    }
    ee = *beta * *p / (*d__ * *t * const2_1.cgas * *amu) - 1.;
    *emu = ee * *amu;
    *rmu = const2_1.cgas * (*amu + *emu);
    return 0;
} /* mu_ */

