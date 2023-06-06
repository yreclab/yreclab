/* getmodel2.f -- translated by f2c (version 20100827).
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


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/* GETMODEL2 - Read a Model2 format stellar model file into memory */

/* llp  4/16/03 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int getmodel2_(doublereal *bl, doublereal *cfenv, doublereal 
	*cmixl, doublereal *dage, doublereal *ddage, doublereal *ftri, 
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
    static char fmt_10[] = "(a5,2i8,5f16.12,1pe18.10,0p2f16.12)";
    static char fmt_30[] = "(2i8,f16.10,1x,a6,1x,3(a4,1x),l1,1x,a4,1x,11(l1,"
	    "1x),3(1pe18.10))";
    static char fmt_40[] = "(10x,1p7e17.9)";
    static char fmt_50[] = "(3x,i2,5f16.12,1p3e20.12)";
    static char fmt_60[] = "(i6,0p2f18.14,1pe24.16,0p3f18.14,1pe24.16,1x,l1,"
	    "3(0pf12.9),12(0pe16.8))";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;
    alist al__1;

    /* Builtin functions */
    integer f_rew(alist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_rsle(cilist *), e_rsle(void);

    /* Local variables */
    static integer i__, j, k, io;
    static char atemp[5];
    static doublereal cccmax;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___4 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___11 = { 0, 0, 0, 0, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };
    static cilist io___13 = { 0, 0, 0, fmt_60, 0 };


/* First three lines above are YREC7 inputs */
/* Last two lines are MODEL2 add-ons */
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
    al__1.aerr = 0;
    al__1.aunit = *iread;
    f_rew(&al__1);
/* get the header record */
    io___1.ciunit = *iread;
    s_rsfe(&io___1);
    do_fio(&c__1, atemp, (ftnlen)5);
    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
    e_rsfe();
/* Get the flags describing the input physics and the information that */
/* is stored in the model (rotating or not?, extendec compotition, etc.) */
    io___3.ciunit = *iread;
    s_rsfe(&io___3);
    do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*cmixl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, eos, (ftnlen)6);
    do_fio(&c__1, atm, (ftnlen)4);
    do_fio(&c__1, lok, (ftnlen)4);
    do_fio(&c__1, hik, (ftnlen)4);
    do_fio(&c__1, (char *)&(*lpurez), (ftnlen)sizeof(logical));
    do_fio(&c__1, compmix, (ftnlen)4);
    do_fio(&c__1, (char *)&(*lexcom), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ldify), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ldifz), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lsemic), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lovstc), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lovste), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lovstm), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*lrot), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*linstb), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ljdot0), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*ldisk), (ftnlen)sizeof(logical));
    do_fio(&c__1, (char *)&(*tdisk), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pdisk), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*wmax), (ftnlen)sizeof(doublereal));
    e_rsfe();
/* Get the  LUMINOSITIES---PP(1-2-3)-CNO-HE-NU-GRAV */
/* CONVERT TO SOLAR LUMINOSITIES */
    io___4.ciunit = *iread;
    s_rsfe(&io___4);
    for (j = 1; j <= 7; ++j) {
	do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
/*   40 FORMAT('TLUMX',5X,1P7E17.9) */
/* If TLUMX are in ergs, convert to solar units.  Decide by */
/* comparing to 10**20.  IF larger, divide by CLSUN. */
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
	    do_fio(&c__1, (char *)&cfenv[i__ * 3 - 3 + j], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
	if (io < 0) {
	    *ftri = -1.;
	}
    }
/*   50 FORMAT('ENV',I2,5F16.12,1P3E20.12) */
/* Skip over column headings for per-shell data */
    io___10.ciunit = *iread;
    s_rsle(&io___10);
    e_rsle();
    io___11.ciunit = *iread;
    s_rsle(&io___11);
    e_rsle();
    io___12.ciunit = *iread;
    s_rsle(&io___12);
    e_rsle();
/* Read per-shell data (HENYEY POINGS) */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	io___13.ciunit = *iread;
	s_rsfe(&io___13);
	do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(logical));
	for (j = 1; j <= 15; ++j) {
	    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
    }
    return 0;
} /* getmodel2_ */

