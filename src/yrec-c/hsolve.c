/* hsolve.f -- translated by f2c (version 20061008).
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



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* HSOLVE */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int hsolve_(integer *m, doublereal *hha, doublereal *hhb, 
	doublereal *hsrf)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, im;
    static doublereal div, qqqp, qqqt, qtemp, pivot, pstore, tstore;

    /* Parameter adjustments */
    --hsrf;
    hhb -= 5;
    hha -= 13;

    /* Function Body */
    div = 1. / (hsrf[1] - hha[((*m << 1) + 1 << 2) + 3]);
    pivot = (hsrf[4] - hha[((*m << 1) + 1 << 2) + 4]) * div;
    hhb[5] = hsrf[3] - hhb[(*m << 2) + 3];
    hhb[6] = hsrf[6] - hhb[(*m << 2) + 4] - pivot * hhb[5];
    qtemp = hsrf[2] - hha[((*m << 1) + 2 << 2) + 3];
    qqqt = hhb[6] / (hsrf[5] - hha[((*m << 1) + 2 << 2) + 4] - pivot * qtemp);
    qqqp = div * (hhb[5] - qqqt * qtemp);
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	im = *m + 2 - i__;
	pstore = hhb[(im << 2) + 1] - qqqp * hha[((im << 1) + 1 << 2) + 1] - 
		qqqt * hha[((im << 1) + 2 << 2) + 1];
	tstore = hhb[(im << 2) + 2] - qqqp * hha[((im << 1) + 1 << 2) + 2] - 
		qqqt * hha[((im << 1) + 2 << 2) + 2];
	hhb[(im << 2) + 3] = hhb[(im << 2) + 3] - qqqp * hha[((im << 1) + 1 <<
		 2) + 3] - qqqt * hha[((im << 1) + 2 << 2) + 3];
	hhb[(im << 2) + 4] = hhb[(im << 2) + 4] - qqqp * hha[((im << 1) + 1 <<
		 2) + 4] - qqqt * hha[((im << 1) + 2 << 2) + 4];
	hhb[(im << 2) + 1] = qqqp;
	hhb[(im << 2) + 2] = qqqt;
	qqqp = pstore;
	qqqt = tstore;
/* L10: */
    }
    hhb[5] = qqqp;
    hhb[6] = qqqt;
    hhb[7] = hhb[7] - qqqp * hha[15] - qqqt * hha[19];
    hhb[8] = hhb[8] - qqqp * hha[16] - qqqt * hha[20];
    return 0;
} /* hsolve_ */

