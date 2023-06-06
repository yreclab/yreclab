/* setllo.f -- translated by f2c (version 20100827).
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
    integer ifirst, irun, istand, ifermi, iopmod, iopenv, iopatm, idyn, 
	    illdat, isnu, iscomp, ikur;
} lunum_;

#define lunum_1 lunum_

struct {
    char flast[256], ffirst[256], frun[256], fstand[256], ffermi[256], fdebug[
	    256], ftrack[256], fshort[256], fmilne[256], fmodpt[256], fstor[
	    256], fpmod[256], fpenv[256], fpatm[256], fdyn[256], flldat[256], 
	    fsnu[256], fscomp[256], fkur[256], fmhd1[256], fmhd2[256], fmhd3[
	    256], fmhd4[256], fmhd5[256], fmhd6[256], fmhd7[256], fmhd8[256];
} lufnm_;

#define lufnm_1 lufnm_

struct {
    doublereal gridt[50], gridx[3], grhot3[17];
} gllot_;

#define gllot_1 gllot_

struct {
    doublereal opacity[2550]	/* was [150][17] */;
    integer numxm, numtm;
} llot_;

#define llot_1 llot_

struct {
    doublereal gridt2[50], gridx2[3], grhot32[17];
} gllot2_;

#define gllot2_1 gllot2_

struct {
    doublereal opacity2[2550]	/* was [150][17] */;
    integer numxm2, numtm2;
} llot2_;

#define llot2_1 llot2_

struct {
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
    char flaol2[256], fopal2[256];
} zramp_;

#define zramp_1 zramp_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

/* Table of constant values */

static integer c__1 = 1;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* SETLLO */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int setllo_(void)
{
    /* Format strings */
    static char fmt_190[] = "(33x,f7.4,2x,f7.4)";
    static char fmt_200[] = "(6x,17f7.1)";
    static char fmt_196[] = "(18f7.3)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void);
    double d_lg10(doublereal *);
    integer f_clos(cllist *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, k, id;
    static doublereal gridy[3], gridz[3];
    extern /* Subroutine */ int ylloc_(void);
    static doublereal gridtk;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 1, fmt_190, 0 };
    static cilist io___5 = { 0, 0, 0, "()", 0 };
    static cilist io___6 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___9 = { 0, 0, 1, fmt_196, 0 };
    static cilist io___11 = { 0, 0, 1, fmt_190, 0 };
    static cilist io___12 = { 0, 0, 0, "()", 0 };
    static cilist io___13 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___14 = { 0, 0, 1, fmt_196, 0 };


/* DBG 5/94 Modified to read in second opacity table at different Z */
/* GRID ENTRIES FOR TEMPERATURE, AND ABUNDANCE (X) */
/* LL OPACITY */
/* DBG 5/94 for different Z */

/* OPACITY COMMON BLOCKS - modified 3/09 */
/* C OPEN TABLE */
    o__1.oerr = 0;
    o__1.ounit = lunum_1.illdat;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.flldat;
    o__1.orl = 0;
    o__1.osta = 0;
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    for (i__ = 1; i__ <= 3; ++i__) {
/* C READ GRID POINT FOR ABUNDANCE */
/* C READ NUMBER OF GRIDS FOR DENSITY, AND TEMPERATURE */
	io___2.ciunit = lunum_1.illdat;
	i__1 = s_rsfe(&io___2);
	if (i__1 != 0) {
	    goto L97;
	}
	i__1 = do_fio(&c__1, (char *)&gllot_1.gridx[i__ - 1], (ftnlen)sizeof(
		doublereal));
	if (i__1 != 0) {
	    goto L97;
	}
	i__1 = do_fio(&c__1, (char *)&gridz[i__ - 1], (ftnlen)sizeof(
		doublereal));
	if (i__1 != 0) {
	    goto L97;
	}
	i__1 = e_rsfe();
	if (i__1 != 0) {
	    goto L97;
	}
	gridy[i__ - 1] = 1. - gllot_1.gridx[i__ - 1] - gridz[i__ - 1];
	io___5.ciunit = lunum_1.illdat;
	s_rsfe(&io___5);
	e_rsfe();
/* C READ  LOG(DENSITY/TEMPERATURE**3) */
	io___6.ciunit = lunum_1.illdat;
	s_rsfe(&io___6);
	for (id = 1; id <= 17; ++id) {
	    do_fio(&c__1, (char *)&gllot_1.grhot3[id - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
/*         READ(ILLDAT,'()') */
/* C READ GRID VALUES FOR TEMPERATURE, AND OPACITY TABLE */
	for (k = 1; k <= 50; ++k) {
	    io___9.ciunit = lunum_1.illdat;
	    i__1 = s_rsfe(&io___9);
	    if (i__1 != 0) {
		goto L93;
	    }
	    i__1 = do_fio(&c__1, (char *)&gridtk, (ftnlen)sizeof(doublereal));
	    if (i__1 != 0) {
		goto L93;
	    }
	    for (id = 1; id <= 17; ++id) {
		i__1 = do_fio(&c__1, (char *)&llot_1.opacity[k + (i__ - 1) * 
			50 + id * 150 - 151], (ftnlen)sizeof(doublereal));
		if (i__1 != 0) {
		    goto L93;
		}
	    }
	    i__1 = e_rsfe();
	    if (i__1 != 0) {
		goto L93;
	    }
	    gllot_1.gridt[k - 1] = d_lg10(&gridtk);
/* L20: */
	}
L93:
	llot_1.numtm = k - 1;
/*         READ(ILLDAT,'()') */

/* L10: */
    }
/* C CLOSE THE TABLE WE HAVE READ */
L97:
    cl__1.cerr = 1;
    cl__1.cunit = lunum_1.illdat;
    cl__1.csta = 0;
    i__1 = f_clos(&cl__1);
    if (i__1 != 0) {
	goto L99;
    }
    llot_1.numxm = i__ - 1;

/* DBG 5/94 Second Opacity Table read here */
    if (newopac_1.l2z) {
	o__1.oerr = 0;
	o__1.ounit = zramp_1.ioopal2;
	o__1.ofnmlen = 256;
	o__1.ofnm = zramp_1.fopal2;
	o__1.orl = 0;
	o__1.osta = 0;
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	for (i__ = 1; i__ <= 3; ++i__) {
	    io___11.ciunit = zramp_1.ioopal2;
	    i__1 = s_rsfe(&io___11);
	    if (i__1 != 0) {
		goto L597;
	    }
	    i__1 = do_fio(&c__1, (char *)&gllot2_1.gridx2[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    if (i__1 != 0) {
		goto L597;
	    }
	    i__1 = do_fio(&c__1, (char *)&gridz[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    if (i__1 != 0) {
		goto L597;
	    }
	    i__1 = e_rsfe();
	    if (i__1 != 0) {
		goto L597;
	    }
	    gridy[i__ - 1] = 1. - gllot2_1.gridx2[i__ - 1] - gridz[i__ - 1];
	    io___12.ciunit = zramp_1.ioopal2;
	    s_rsfe(&io___12);
	    e_rsfe();
	    io___13.ciunit = zramp_1.ioopal2;
	    s_rsfe(&io___13);
	    for (id = 1; id <= 17; ++id) {
		do_fio(&c__1, (char *)&gllot2_1.grhot32[id - 1], (ftnlen)
			sizeof(doublereal));
	    }
	    e_rsfe();
	    for (k = 1; k <= 50; ++k) {
		io___14.ciunit = zramp_1.ioopal2;
		i__1 = s_rsfe(&io___14);
		if (i__1 != 0) {
		    goto L593;
		}
		i__1 = do_fio(&c__1, (char *)&gridtk, (ftnlen)sizeof(
			doublereal));
		if (i__1 != 0) {
		    goto L593;
		}
		for (id = 1; id <= 17; ++id) {
		    i__1 = do_fio(&c__1, (char *)&llot2_1.opacity2[k + (i__ - 
			    1) * 50 + id * 150 - 151], (ftnlen)sizeof(
			    doublereal));
		    if (i__1 != 0) {
			goto L593;
		    }
		}
		i__1 = e_rsfe();
		if (i__1 != 0) {
		    goto L593;
		}
		gllot2_1.gridt2[k - 1] = d_lg10(&gridtk);
/* L520: */
	    }
L593:
	    llot2_1.numtm2 = k - 1;
/* L510: */
	}
L597:
	cl__1.cerr = 1;
	cl__1.cunit = zramp_1.ioopal2;
	cl__1.csta = 0;
	i__1 = f_clos(&cl__1);
	if (i__1 != 0) {
	    goto L99;
	}
	llot2_1.numxm2 = i__ - 1;
    }

    ylloc_();
    return 0;
L99:
    s_stop("ERROR IN FILE CLOSING", (ftnlen)21);
    return 0;
} /* setllo_ */

