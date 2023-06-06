/* getyrec7.f -- translated by f2c (version 20100827).
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
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b94 = 10.;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/* GETY7 - Read a YREC7 format stellar model file into memory */

/* llp  4/16/03 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int getyrec7_(doublereal *bl, doublereal *cfenv, doublereal *
	cmixl, doublereal *dage, doublereal *ddage, doublereal *ftri, 
	doublereal *hcomp, doublereal *hd, doublereal *hl, doublereal *hp, 
	doublereal *hr, doublereal *hs, doublereal *hstot, doublereal *ht, 
	integer *iread, integer *ishort, integer *jcore, integer *jenv, 
	logical *lc, logical *lexcom, logical *lrot, integer *m, integer *
	model, doublereal *omega, doublereal *ps, doublereal *rs, doublereal *
	smass, doublereal *teffl, doublereal *tlumx, doublereal *tril, 
	doublereal *trit, doublereal *ts, char *atm, char *eos, char *hik, 
	logical *ldify, logical *ldifz, logical *ldisk, logical *linstb, 
	logical *ljdot0, char *lok, logical *lovstc, logical *lovste, logical 
	*lovstm, logical *lpurez, logical *lsemic, char *compmix, doublereal *
	pdisk, doublereal *tdisk, doublereal *wmax, ftnlen atm_len, ftnlen 
	eos_len, ftnlen hik_len, ftnlen lok_len, ftnlen compmix_len)
{
    /* Format strings */
    static char fmt_10[] = "(a4,1x,2i5,3f8.5,1x,f14.10,f13.9,f13.0)";
    static char fmt_30[] = "(2(l1,1x),5x,2i4,f7.3)";
    static char fmt_40[] = "(10x,7e10.3)";
    static char fmt_70[] = "(3x,i2,f7.5,4f8.5,3e12.5)";
    static char fmt_100[] = "(0pf13.10,f10.7,1pe14.7,0pf10.7,2f10.7,l1,2i6)";
    static char fmt_1000[] = "(1x,39(\002>\002),40(\002<\002)/1x,\002RUN STO"
	    "PPED\002)";
    static char fmt_1050[] = "(\002 ERROR IN SUBROUTINE GETY7\002/1x,\002GLI"
	    "TCH IN SHELL\002,i3,\002, SHELL MASS LESS THAN ZERO OR GREATER T"
	    "HAN STAR MASS\002)";
    static char fmt_200[] = "(8(1pe9.3,1x))";
    static char fmt_300[] = "(4(1pe9.3,1x))";
    static char fmt_500[] = "(0p8f10.7)";
    static char fmt_9998[] = "(2a)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;
    alist al__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer f_rew(alist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j, k, ii, io, kt, ix, iz;
    static char atemp[4];
    static doublereal cccmax, omegal[5000];

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___13 = { 0, 0, 0, fmt_1000, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_1050, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___16 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___17 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___18 = { 0, 0, 0, fmt_300, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_300, 0 };
    static cilist io___23 = { 0, 0, 1, fmt_500, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_9998, 0 };


/* First three lines above are YREC7 inputs */
/* Last two lines are MODEL2 add-ons */
/* Initialization */
/* Zero the composition arrays (HCOMP) and the OMEGA array. */
/* This is agreed upon protection in case they are inadvertently used in the program, */
/* but not present in the old YREC input data. */
    /* Parameter adjustments */
    --ts;
    --trit;
    --tril;
    --tlumx;
    --rs;
    --ps;
    --omega;
    --lc;
    --ht;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;
    --cfenv;

    /* Function Body */
    for (i__ = 1; i__ <= 5000; ++i__) {
	omega[i__] = 0.;
	for (j = 1; j <= 15; ++j) {
	    hcomp[j + i__ * 15] = 0.;
	}
    }
/*  Set Model2-sspecific strings to "?" */
    s_copy(atm, " ? ", (ftnlen)4, (ftnlen)3);
    s_copy(eos, " ? ", (ftnlen)6, (ftnlen)3);
    s_copy(hik, " ? ", (ftnlen)4, (ftnlen)3);
    s_copy(lok, " ? ", (ftnlen)4, (ftnlen)3);
    s_copy(compmix, "AG93", (ftnlen)4, (ftnlen)4);
/* Set Model2-specific flags false */
    *ldify = FALSE_;
    *ldifz = FALSE_;
    *ldisk = FALSE_;
    *linstb = FALSE_;
    *ljdot0 = FALSE_;
    *lovstc = FALSE_;
    *lovste = FALSE_;
    *lovstm = FALSE_;
    *lpurez = FALSE_;
    *lsemic = FALSE_;
/* Set Model2-specific constants to default */
    *pdisk = 7.2722e-6;
    *tdisk = 0.;
    *wmax = 3e-4;
/* End of initialization */
/* Read in an input model from the LU IREAD file in YREC7 Format */
    al__1.aerr = 0;
    al__1.aunit = *iread;
    f_rew(&al__1);
/* get the header record */
    io___3.ciunit = *iread;
    s_rsfe(&io___3);
    do_fio(&c__1, atemp, (ftnlen)4);
    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
    e_rsfe();
/* Get the flags describing the input physics and the information that */
/* is stored in the model (rotating or not?, extendec compotition, etc.) */
    io___5.ciunit = *iread;
    s_rsfe(&io___5);
    do_fio(&c__1, (char *)&(*lrot), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lexcom), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*cmixl), (ftnlen)sizeof(doublereal));
    e_rsfe();
/* get the LUMINOSITIES---PP(1-2-3)-CNO-HE-NU-GRAV */
    io___6.ciunit = *iread;
    s_rsfe(&io___6);
    for (j = 1; j <= 7; ++j) {
	do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
/* If TLUMX are in ergs, convert to solar units.  Decide by */
/* comparing to 10**20. If larger, divide by CLSUN. */
/* Computing MAX */
    d__1 = max(tlumx[1],tlumx[2]), d__1 = max(d__1,tlumx[3]), d__1 = max(d__1,
	    tlumx[4]), d__1 = max(d__1,tlumx[5]), d__2 = abs(tlumx[6]), d__1 =
	     max(d__1,d__2);
    cccmax = max(d__1,tlumx[7]);
    if (cccmax > 1e20) {
	for (j = 1; j <= 7; ++j) {
	    tlumx[j] /= const_1.clsun;
	}
    }
/* Get the ENVELOPE DATA */
/* FTRI is 1,normally.  It is set to -1  if any of the record numbers */
/* for the envelope triangle records was set to -1 by WRTLST. */
    *ftri = 1.;
    for (i__ = 1; i__ <= 3; ++i__) {
	io___8.ciunit = *iread;
	s_rsfe(&io___8);
	do_fio(&c__1, (char *)&io, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&trit[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tril[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ps[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ts[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rs[i__], (ftnlen)sizeof(doublereal));
	for (j = 1; j <= 3; ++j) {
	    do_fio(&c__1, (char *)&cfenv[i__ + i__ + i__ - 3 + j], (ftnlen)
		    sizeof(doublereal));
	}
	e_rsfe();
	if (io < 0) {
	    *ftri = -1.;
	}
/* L80: */
    }
/* READ IN HENYEY POINTS IN 4 PARTS */

/* Read FIRST PART:M,R,L,P,T,RHO,CONV(T/F),X,Y,AND Z - one line per shell */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___10.ciunit = *iread;
	s_rsfe(&io___10);
	do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&ix, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&iz, (ftnlen)sizeof(integer));
	e_rsfe();
	if (hs[i__] < 0. || hs[i__] > *hstot) {
	    io___13.ciunit = *ishort;
	    s_wsfe(&io___13);
	    e_wsfe();
	    io___14.ciunit = *ishort;
	    s_wsfe(&io___14);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
	hcomp[i__ * 15 + 1] = (doublereal) ix * 1e-6;
	hcomp[i__ * 15 + 3] = (doublereal) iz * 1e-6;
/* L110: */
    }
/* Read SECOND PART:ELEMENT ABUNDANCES: HE3,CNO CYCLE ELEMENTS. */
/* ABUNDANCES IN SURFACE AND CENTRAL CONVECTION ZONES STORED WITH 1 */
/* VALUE PER ZONE RATHER THAN 1 VALUE PER SHELL */
    if (*jenv <= *jcore) {
	io___15.ciunit = *iread;
	s_rsfe(&io___15);
	for (i__ = 4; i__ <= 11; ++i__) {
	    do_fio(&c__1, (char *)&hcomp[i__ + *jcore * 15], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
	io___16.ciunit = *iread;
	s_rsfe(&io___16);
	for (i__ = 4; i__ <= 11; ++i__) {
	    do_fio(&c__1, (char *)&hcomp[i__ + *jenv * 15], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
    } else {
	i__1 = *jenv;
	for (j = *jcore; j <= i__1; ++j) {
	    io___17.ciunit = *iread;
	    s_rsfe(&io___17);
	    for (i__ = 4; i__ <= 11; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + j * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    e_rsfe();
/* L210: */
	}
    }
    if (*jcore > 1) {
/* CONVECTIVE CORE- ASSIGN FIRST COMPOSITION VALUE TO SHELLS 1-JCORE */
	i__1 = *jcore - 1;
	for (j = 1; j <= i__1; ++j) {
	    for (i__ = 4; i__ <= 11; ++i__) {
		hcomp[i__ + j * 15] = hcomp[i__ + *jcore * 15];
/* L220: */
	    }
/* L230: */
	}
    }
    if (*jenv < *m) {
/* CONVECTIVE SURFACE- ASSIGN LAST COMPOSITION TO SHELLS JENV-M */
	i__1 = *m;
	for (j = *jenv + 1; j <= i__1; ++j) {
	    for (i__ = 4; i__ <= 11; ++i__) {
		hcomp[i__ + j * 15] = hcomp[i__ + *jenv * 15];
/* L240: */
	    }
/* L250: */
	}
    }
/* DEFINE HE4 = 1 - X - Z - HE3. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 3] 
		- hcomp[i__ * 15 + 4];
/* L260: */
    }
/* READ IN H2,LI6,LI7,BE9 (EXTENDED COMPOSITION) */
    if (*lexcom) {
	if (*jenv == 1) {
/* FULLY CONVECTIVE MODEL */
	    io___18.ciunit = *iread;
	    s_rsfe(&io___18);
	    for (i__ = 12; i__ <= 15; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + 15], (ftnlen)sizeof(
			doublereal));
	    }
	    e_rsfe();
	    i__1 = *m;
	    for (j = 1; j <= i__1; ++j) {
		for (i__ = 12; i__ <= 15; ++i__) {
		    hcomp[i__ + j * 15] = hcomp[i__ + 15];
/* L305: */
		}
/* L310: */
	    }
	} else {
/* GENERAL CASE */
/* THESE ABUNDANCES ARE READ IN WITH 2 SHELLS PER LINE */
	    i__1 = *jenv - 1;
	    for (k = *jcore; k <= i__1; k += 2) {
		io___20.ciunit = *iread;
		s_rsfe(&io___20);
		i__2 = k + 1;
		for (j = k; j <= i__2; ++j) {
		    for (i__ = 12; i__ <= 15; ++i__) {
			do_fio(&c__1, (char *)&hcomp[i__ + j * 15], (ftnlen)
				sizeof(doublereal));
		    }
		}
		e_rsfe();
/* L315: */
	    }
/* IF AN ODD NUMBER OF ABUNDANCES STORED, READ IN LAST VALUE */
	    kt = *jenv - 1 - *jcore;
	    if (kt % 2 != 0) {
		io___22.ciunit = *iread;
		s_rsfe(&io___22);
		for (i__ = 12; i__ <= 15; ++i__) {
		    do_fio(&c__1, (char *)&hcomp[i__ + k * 15], (ftnlen)
			    sizeof(doublereal));
		}
		e_rsfe();
	    }
	    if (*jcore > 1) {
/* CONVECTIVE CORE- ASSIGN FIRST VALUE TO SHELLS 1-JCORE */
		i__1 = *jcore - 1;
		for (j = 1; j <= i__1; ++j) {
		    for (i__ = 12; i__ <= 15; ++i__) {
			hcomp[i__ + j * 15] = hcomp[i__ + *jcore * 15];
/* L320: */
		    }
/* L330: */
		}
	    }
	    if (*jenv < *m) {
/* CONVECTIVE SURFACE- ASSIGN LAST VALUE TO SHELLS JENV - M */
		i__1 = *m;
		for (j = *jenv + 1; j <= i__1; ++j) {
		    for (i__ = 12; i__ <= 15; ++i__) {
			hcomp[i__ + j * 15] = hcomp[i__ + *jenv * 15];
/* L340: */
		    }
/* L350: */
		}
	    }
	}
    }
/* Read in FOURTH PART:  - LOG J/M STORED , 8 SHELLS PER LINE */
    if (*lrot) {
/* READ OMEGA IN. If OMEGA records are missing go to OMEGA BYPASS below */
	io___23.ciunit = *iread;
	i__1 = s_rsfe(&io___23);
	if (i__1 != 0) {
	    goto L9999;
	}
	i__2 = *m;
	for (ii = 1; ii <= i__2; ++ii) {
	    i__1 = do_fio(&c__1, (char *)&omegal[ii - 1], (ftnlen)sizeof(
		    doublereal));
	    if (i__1 != 0) {
		goto L9999;
	    }
	}
	i__1 = e_rsfe();
	if (i__1 != 0) {
	    goto L9999;
	}
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (omegal[i__ - 1] < 58.9) {
		d__1 = -omegal[i__ - 1];
		omega[i__] = pow_dd(&c_b94, &d__1);
	    } else {
		omega[i__] = 0.;
	    }
/* L510: */
	}
    }
/* KEEP IREAD OPEN */
    al__1.aerr = 0;
    al__1.aunit = *iread;
    f_rew(&al__1);
    return 0;
/*  OMEGA BYPASS */
/* Come here if OMEGA records are missing -- Can happen if */
/* a new omega file is being generated (LWNEW is true in STARIN) */
L9999:
    io___26.ciunit = *ishort;
    s_wsfe(&io___26);
    do_fio(&c__1, "GETYREC7: OMEGA records are missing from ", (ftnlen)41);
    do_fio(&c__1, " input model file - OMEGA array zeroed", (ftnlen)38);
    e_wsfe();
    for (i__ = 1; i__ <= 5000; ++i__) {
	omega[i__] = 0.;
    }
/* KEEP IREAD OPEN */
    al__1.aerr = 0;
    al__1.aunit = *iread;
    f_rew(&al__1);
    return 0;
} /* getyrec7_ */

