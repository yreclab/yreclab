/* reduce.f -- translated by f2c (version 20061008).
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
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* REDUCE */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int reduce_(integer *i__, doublereal *hha, doublereal *hhb, 
	doublereal *hl, doublereal *hmax, doublereal *hp, doublereal *hr, 
	doublereal *hs, doublereal *ht, doublereal *qp0, doublereal *qp, 
	doublereal *qpr0, doublereal *qpr, doublereal *qpp0, doublereal *qpp, 
	doublereal *qt0, doublereal *qt, doublereal *qtr0, doublereal *qtr, 
	doublereal *qtl0, doublereal *qtl, doublereal *qtp0, doublereal *qtp, 
	doublereal *qtt0, doublereal *qtt, doublereal *qr0, doublereal *qr, 
	doublereal *qrr0, doublereal *qrr, doublereal *qrp0, doublereal *qrp, 
	doublereal *qrt0, doublereal *qrt, doublereal *ql0, doublereal *ql, 
	doublereal *qlp0, doublereal *qlp, doublereal *qlt0, doublereal *qlt)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Local variables */
    static integer j;
    static doublereal q[16]	/* was [4][4] */, sd05, div, pivot, pivotb;

/* DEFINE R.H.S */
    /* Parameter adjustments */
    --ht;
    --hs;
    --hr;
    --hp;
    --hmax;
    --hl;
    hhb -= 5;
    hha -= 13;

    /* Function Body */
    sd05 = (hs[*i__] - hs[*i__ - 1]) * .5;
    hhb[(*i__ << 2) + 1] = sd05 * (*qp0 + *qp) - (hp[*i__] - hp[*i__ - 1]);
/* Computing MAX */
    d__2 = hmax[1], d__3 = (d__1 = hhb[(*i__ << 2) + 1], abs(d__1));
    hmax[1] = max(d__2,d__3);
    hhb[(*i__ << 2) + 2] = sd05 * (*qt0 + *qt) - (ht[*i__] - ht[*i__ - 1]);
/* Computing MAX */
    d__2 = hmax[2], d__3 = (d__1 = hhb[(*i__ << 2) + 2], abs(d__1));
    hmax[2] = max(d__2,d__3);
    hhb[(*i__ << 2) + 3] = sd05 * (*qr0 + *qr) - (hr[*i__] - hr[*i__ - 1]);
/* Computing MAX */
    d__2 = hmax[3], d__3 = (d__1 = hhb[(*i__ << 2) + 3], abs(d__1));
    hmax[3] = max(d__2,d__3);
    hhb[(*i__ << 2) + 4] = sd05 * (*ql0 + *ql) - (hl[*i__] - hl[*i__ - 1]);
/* Computing MAX */
    d__2 = hmax[4], d__3 = (d__1 = hhb[(*i__ << 2) + 4], abs(d__1));
    hmax[4] = max(d__2,d__3);
    sd05 *= const1_1.cln;
/* ELIMINATE COLUMNS 1 AND 2 */
    pivot = -sd05 * *qpr0;
    q[0] = -1. - sd05 * *qpp0 - pivot * hha[((*i__ - 1 << 1) + 1 << 2) + 3];
    q[4] = -pivot * hha[((*i__ - 1 << 1) + 2 << 2) + 3];
    hhb[(*i__ << 2) + 1] -= pivot * hhb[(*i__ - 1 << 2) + 3];
    pivot = -sd05 * *qtr0;
    pivotb = -sd05 * *qtl0;
    q[1] = -sd05 * *qtp0 - pivot * hha[((*i__ - 1 << 1) + 1 << 2) + 3] - 
	    pivotb * hha[((*i__ - 1 << 1) + 1 << 2) + 4];
    q[5] = -1. - sd05 * *qtt0 - pivot * hha[((*i__ - 1 << 1) + 2 << 2) + 3] - 
	    pivotb * hha[((*i__ - 1 << 1) + 2 << 2) + 4];
    hhb[(*i__ << 2) + 2] = hhb[(*i__ << 2) + 2] - pivot * hhb[(*i__ - 1 << 2) 
	    + 3] - pivotb * hhb[(*i__ - 1 << 2) + 4];
    pivot = -1. - sd05 * *qrr0;
    q[2] = -sd05 * *qrp0 - pivot * hha[((*i__ - 1 << 1) + 1 << 2) + 3];
    q[6] = -sd05 * *qrt0 - pivot * hha[((*i__ - 1 << 1) + 2 << 2) + 3];
    hhb[(*i__ << 2) + 3] -= pivot * hhb[(*i__ - 1 << 2) + 3];
    q[3] = -sd05 * *qlp0 + hha[((*i__ - 1 << 1) + 1 << 2) + 4];
    q[7] = -sd05 * *qlt0 + hha[((*i__ - 1 << 1) + 2 << 2) + 4];
    hhb[(*i__ << 2) + 4] += hhb[(*i__ - 1 << 2) + 4];
/* REDUCE 4*4 MATRIX */
/* PIVOT ON ROW-4 AND COLUMN-6 */
    hha[((*i__ << 1) + 1 << 2) + 4] = -sd05 * *qlp;
    hha[((*i__ << 1) + 2 << 2) + 4] = -sd05 * *qlt;
    pivot = -sd05 * *qtl;
    q[1] -= pivot * q[3];
    q[5] -= pivot * q[7];
    hhb[(*i__ << 2) + 2] -= pivot * hhb[(*i__ << 2) + 4];
    hha[((*i__ << 1) + 1 << 2) + 2] = -sd05 * *qtp - pivot * hha[((*i__ << 1) 
	    + 1 << 2) + 4];
    hha[((*i__ << 1) + 2 << 2) + 2] = 1. - sd05 * *qtt - pivot * hha[((*i__ <<
	     1) + 2 << 2) + 4];
/* PIVOT ON ROW-3 AND COLUMN-5 */
    div = 1. / (1. - sd05 * *qrr);
    q[2] *= div;
    q[6] *= div;
    hhb[(*i__ << 2) + 3] *= div;
    div = -sd05 * div;
    hha[((*i__ << 1) + 1 << 2) + 3] = div * *qrp;
    hha[((*i__ << 1) + 2 << 2) + 3] = div * *qrt;
    pivot = -sd05 * *qpr;
    q[0] -= pivot * q[2];
    q[4] -= pivot * q[6];
    hhb[(*i__ << 2) + 1] -= pivot * hhb[(*i__ << 2) + 3];
    hha[((*i__ << 1) + 1 << 2) + 1] = 1. - sd05 * *qpp - pivot * hha[((*i__ <<
	     1) + 1 << 2) + 3];
    hha[((*i__ << 1) + 2 << 2) + 1] = -pivot * hha[((*i__ << 1) + 2 << 2) + 3]
	    ;
    pivot = -sd05 * *qtr;
    q[1] -= pivot * q[2];
    q[5] -= pivot * q[6];
    hhb[(*i__ << 2) + 2] -= pivot * hhb[(*i__ << 2) + 3];
    hha[((*i__ << 1) + 1 << 2) + 2] -= pivot * hha[((*i__ << 1) + 1 << 2) + 3]
	    ;
    hha[((*i__ << 1) + 2 << 2) + 2] -= pivot * hha[((*i__ << 1) + 2 << 2) + 3]
	    ;
/* PIVOT ON ROW-2 AND COLUMN-4 */
    div = 1. / q[5];
    q[1] *= div;
    hhb[(*i__ << 2) + 2] *= div;
    hha[((*i__ << 1) + 1 << 2) + 2] *= div;
    hha[((*i__ << 1) + 2 << 2) + 2] *= div;
    for (j = 1; j <= 4; ++j) {
	if (j == 2) {
	    goto L2;
	}
	q[j - 1] -= q[j + 3] * q[1];
	hhb[j + (*i__ << 2)] -= q[j + 3] * hhb[(*i__ << 2) + 2];
	hha[j + ((*i__ << 1) + 1 << 2)] -= q[j + 3] * hha[((*i__ << 1) + 1 << 
		2) + 2];
	hha[j + ((*i__ << 1) + 2 << 2)] -= q[j + 3] * hha[((*i__ << 1) + 2 << 
		2) + 2];
L2:
	;
    }
/* PIVOT ON ROW-1 AND COLUMN-3 */
    div = 1. / q[0];
    hhb[(*i__ << 2) + 1] *= div;
    hha[((*i__ << 1) + 1 << 2) + 1] *= div;
    hha[((*i__ << 1) + 2 << 2) + 1] *= div;
    for (j = 2; j <= 4; ++j) {
	hhb[j + (*i__ << 2)] -= q[j - 1] * hhb[(*i__ << 2) + 1];
	hha[j + ((*i__ << 1) + 1 << 2)] -= q[j - 1] * hha[((*i__ << 1) + 1 << 
		2) + 1];
	hha[j + ((*i__ << 1) + 2 << 2)] -= q[j - 1] * hha[((*i__ << 1) + 2 << 
		2) + 1];
/* L4: */
    }
    return 0;
} /* reduce_ */

