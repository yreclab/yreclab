/* setkrz.f -- translated by f2c (version 20100827).
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
    doublereal gridt[60];
} gkrz_;

#define gkrz_1 gkrz_

struct {
    doublereal gridt2[60];
} gkrz2_;

#define gkrz2_1 gkrz2_

struct {
    doublereal opacity[3000]	/* was [60][50] */, rho[3000]	/* was [60][
	    50] */;
    integer numtm;
} krz_;

#define krz_1 krz_

struct {
    doublereal opacity2[3000]	/* was [60][50] */, rho2[3000]	/* was [60][
	    50] */;
    integer numtm2;
} krz2_;

#define krz2_1 krz2_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct {
    integer ikur2;
    char fkur2[256];
    integer icondopacp;
    doublereal fcondopacp;
    logical lcondopacp;
} miscopac_;

#define miscopac_1 miscopac_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b22 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* SETKRZ */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int setkrz_(void)
{
    /* Format strings */
    static char fmt_1[] = "(2f5.2,5f7.3,3f9.5,f8.3)";

    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), e_rsfe(void), do_fio(integer *,
	     char *, ftnlen);
    /* Subroutine */ int s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);
    integer f_clos(cllist *);

    /* Local variables */
    static integer i__, id;
    static doublereal dens, dumm, pres;
    static integer iput;
    static doublereal tout, denna, denne, toutk, okuru0, okuru1, okuru2, 
	    okuru4, okuru8;
    extern /* Subroutine */ int ykoeff_(void);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, "(/)", 0 };
    static cilist io___5 = { 1, 0, 1, fmt_1, 0 };
    static cilist io___18 = { 0, 0, 0, "(/)", 0 };
    static cilist io___19 = { 1, 0, 1, fmt_1, 0 };


/* MHP 10/02 missing comma after IDYN */
/* GRID ENTRIES FOR TEMPERATURE, AND ABUNDANCE (X) */
/* LOS ALAMOS OPACITY */
/* OPACITY COMMON BLOCKS - modified 3/09 */

    i__ = 1;
/* L1: */
/*     OPEN TABLE */
    o__1.oerr = 0;
    o__1.ounit = lunum_1.ikur;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.fkur;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    io___2.ciunit = lunum_1.ikur;
    s_rsfe(&io___2);
    e_rsfe();

    iput = 0;
    toutk = 0.;
L110:
    io___5.ciunit = lunum_1.ikur;
    i__1 = s_rsfe(&io___5);
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&tout, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&pres, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&okuru0, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&okuru1, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&okuru2, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&okuru4, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&okuru8, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&denne, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&denna, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&dens, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = do_fio(&c__1, (char *)&dumm, (ftnlen)sizeof(doublereal));
    if (i__1 != 0) {
	goto L100001;
    }
    i__1 = e_rsfe();
L100001:
    if (i__1 < 0) {
	goto L120;
    }
    if (i__1 > 0) {
	goto L110;
    }
    if (toutk != tout) {
	++iput;
	if (iput > 60) {
	    s_stop(" KURUCZ INPUT ERROR", (ftnlen)19);
	}
	gkrz_1.gridt[iput - 1] = tout;
	toutk = tout;
	id = 1;
    }
    if (iput < 1) {
	s_stop(" KURUCZ INPUT ERROR", (ftnlen)19);
    }
    krz_1.rho[iput + id * 60 - 61] = dens;
    krz_1.opacity[iput + id * 60 - 61] = pow_dd(&c_b22, &okuru0);
    ++id;
    goto L110;

L120:
    krz_1.numtm = iput;
/*     CLOSE THE TABLE WE HAVE READ */
    cl__1.cerr = 1;
    cl__1.cunit = lunum_1.ikur;
    cl__1.csta = 0;
    i__1 = f_clos(&cl__1);
    if (i__1 != 0) {
	goto L99;
    }



/* DBG 12/95 read in second Z table if requested */
    if (newopac_1.l2z) {
/*     OPEN TABLE */
	o__1.oerr = 0;
	o__1.ounit = miscopac_1.ikur2;
	o__1.ofnmlen = 256;
	o__1.ofnm = miscopac_1.fkur2;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	io___18.ciunit = miscopac_1.ikur2;
	s_rsfe(&io___18);
	e_rsfe();

	iput = 0;
	toutk = 0.;
L210:
	io___19.ciunit = miscopac_1.ikur2;
	i__1 = s_rsfe(&io___19);
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&tout, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&pres, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&okuru0, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&okuru1, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&okuru2, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&okuru4, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&okuru8, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&denne, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&denna, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&dens, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = do_fio(&c__1, (char *)&dumm, (ftnlen)sizeof(doublereal));
	if (i__1 != 0) {
	    goto L100002;
	}
	i__1 = e_rsfe();
L100002:
	if (i__1 < 0) {
	    goto L220;
	}
	if (i__1 > 0) {
	    goto L210;
	}
	if (toutk != tout) {
	    ++iput;
	    if (iput > 60) {
		s_stop(" KURUCZ INPUT ERROR", (ftnlen)19);
	    }
	    gkrz2_1.gridt2[iput - 1] = tout;
	    toutk = tout;
	    id = 1;
	}
	if (iput < 1) {
	    s_stop(" KURUCZ INPUT ERROR", (ftnlen)19);
	}
	krz2_1.rho2[iput + id * 60 - 61] = dens;
	krz2_1.opacity2[iput + id * 60 - 61] = pow_dd(&c_b22, &okuru0);
	++id;
	goto L210;
L220:
	krz2_1.numtm2 = iput;
/* CLOSE THE TABLE WE HAVE READ */
	cl__1.cerr = 1;
	cl__1.cunit = miscopac_1.ikur2;
	cl__1.csta = 0;
	i__1 = f_clos(&cl__1);
	if (i__1 != 0) {
	    goto L99;
	}
    }
    ykoeff_();
    return 0;
L99:
    s_stop("ERROR IN FILE CLOSING", (ftnlen)21);
    return 0;
} /* setkrz_ */

