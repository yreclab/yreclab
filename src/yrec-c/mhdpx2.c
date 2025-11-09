/* mhdpx2.f -- translated by f2c (version 20061008).
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
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    doublereal tdvr1a[27840]	/* was [16][87][20] */, tlog1[16];
    integer nt1, nr1;
    doublereal drh1;
} tab1a_;

#define tab1a_1 tab1a_

struct {
    doublereal tdvr2a[33180]	/* was [79][21][20] */, tlog2[79];
    integer nt2, nr2;
    doublereal drh2;
} tab2a_;

#define tab2a_1 tab2a_

struct {
    doublereal tdvr1b[27840]	/* was [16][87][20] */;
} tab1b_;

#define tab1b_1 tab1b_

struct {
    doublereal tdvr2b[33180]	/* was [79][21][20] */;
} tab2b_;

#define tab2b_1 tab2b_

struct {
    doublereal tdvr1c[27840]	/* was [16][87][20] */;
} tab1c_;

#define tab1c_1 tab1c_

struct {
    doublereal tdvr2c[33180]	/* was [79][21][20] */;
} tab2c_;

#define tab2c_1 tab2c_

struct {
    doublereal atwta[6], abuna[6], abfrca[6], gasma;
} chea_;

#define chea_1 chea_

struct {
    doublereal atwtb[6], abunb[6], abfrcb[6], gasmb;
} cheb_;

#define cheb_1 cheb_

struct {
    doublereal atwtc[6], abunc[6], abfrcc[6], gasmc;
} chec_;

#define chec_1 chec_

struct {
    doublereal tdvrx1[5250]	/* was [10][21][25] */, tlogx[10];
    integer ntx, nrx;
    doublereal drhx;
} tabx1_;

#define tabx1_1 tabx1_

struct {
    doublereal tdvrx2[5250]	/* was [10][21][25] */;
} tabx2_;

#define tabx2_1 tabx2_

struct {
    doublereal tdvrx3[5250]	/* was [10][21][25] */;
} tabx3_;

#define tabx3_1 tabx3_

struct {
    doublereal tdvrx4[5250]	/* was [10][21][25] */;
} tabx4_;

#define tabx4_1 tabx4_

struct {
    doublereal tdvrx5[5250]	/* was [10][21][25] */;
} tabx5_;

#define tabx5_1 tabx5_

struct {
    doublereal atwt1[6], abun1[6], abfrc1[6], gasm1;
} che1_;

#define che1_1 che1_

struct {
    doublereal atwt2[6], abun2[6], abfrc2[6], gasm2;
} che2_;

#define che2_1 che2_

struct {
    doublereal atwt3[6], abun3[6], abfrc3[6], gasm3;
} che3_;

#define che3_1 che3_

struct {
    doublereal atwt4[6], abun4[6], abfrc4[6], gasm4;
} che4_;

#define che4_1 che4_

struct {
    doublereal atwt5[6], abun5[6], abfrc5[6], gasm5;
} che5_;

#define che5_1 che5_

/* Table of constant values */

static integer c__25 = 25;
static integer c__16 = 16;
static integer c__87 = 87;
static integer c__20 = 20;
static integer c__79 = 79;
static integer c__21 = 21;
static integer c__10 = 10;




/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHDPX2 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mhdpx2_(doublereal *pl, doublereal *tl, integer *itbl, 
	doublereal *varout, doublereal *xcomp, integer *ndimt)
{
    /* System generated locals */
    integer varout_dim1, varout_offset;

    /* Local variables */
    static integer i__;
    static doublereal vy[25], varo[25];
    extern /* Subroutine */ int zero_(doublereal *, integer *);
    static doublereal vvar1[100]	/* was [25][4] */, vvar2[100]	/* 
	    was [25][4] */;
    extern /* Subroutine */ int intpt_(doublereal *, doublereal *, doublereal 
	    *, integer *, integer *, integer *, doublereal *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *)
	    ;

/*     ZAMS TABLES (LABELLED BY A,B,C) */
/*     CENTRE TABLES (LABELLED BY 1,2,3,4,5) */
/*     NOMENCLATURE FOR ACCESSING THE TABLES */
/*     ZAMS TABLES */
/*     ITBL = -1   : TDVR1A */
/*     ITBL =  1   : TDVR2A */
/*     ITBL = -2   : TDVR1B */
/*     ITBL =  2   : TDVR2B */
/*     ITBL = -3   : TDVR1C */
/*     ITBL =  3   : TDVR2C */
/*     CONTRAL (VARIABLE X) TABLES */
/*     ITBL =  4   : TDVRX1 */
/*     ITBL =  5   : TDVRX2 */
/*     ITBL =  6   : TDVRX3 */
/*     ITBL =  7   : TDVRX4 */
/*     ITBL =  8   : TDVRX5 */
/*     NOTE: THE SAME OUTPUT VARIABLES VAROUT(ITBL,.) IS USED */
/*           FOR ITBL=1 AND -1, 2 AND -2, 3 AND -3, RESPECTIVELY. */
/*     IRANGE = 1 */
    /* Parameter adjustments */
    --xcomp;
    varout_dim1 = *ndimt;
    varout_offset = 1 + varout_dim1;
    varout -= varout_offset;

    /* Function Body */
    zero_(varo, &c__25);
/*     MAIN SELECTION OF TABLES */
/*     ZAMS TABLES */
    if (*itbl == -1) {
	intpt_(pl, tl, tab1a_1.tdvr1a, &c__16, &c__87, &c__20, tab1a_1.tlog1, 
		&tab1a_1.nt1, &tab1a_1.nr1, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 20; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 20       VAROUT(1,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 1] = varo[i__ - 1];
/* L20: */
	}
	xcomp[1] = chea_1.abfrca[0];
    } else if (*itbl == 1) {
	intpt_(pl, tl, tab2a_1.tdvr2a, &c__79, &c__21, &c__20, tab2a_1.tlog2, 
		&tab2a_1.nt2, &tab2a_1.nr2, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 20; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 30       VAROUT(1,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 1] = varo[i__ - 1];
/* L30: */
	}
	xcomp[1] = chea_1.abfrca[0];
    } else if (*itbl == -2) {
	intpt_(pl, tl, tab1b_1.tdvr1b, &c__16, &c__87, &c__20, tab1a_1.tlog1, 
		&tab1a_1.nt1, &tab1a_1.nr1, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 20; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 40       VAROUT(2,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 2] = varo[i__ - 1];
/* L40: */
	}
	xcomp[2] = cheb_1.abfrcb[0];
    } else if (*itbl == 2) {
	intpt_(pl, tl, tab2b_1.tdvr2b, &c__79, &c__21, &c__20, tab2a_1.tlog2, 
		&tab2a_1.nt2, &tab2a_1.nr2, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 20; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 50       VAROUT(2,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 2] = varo[i__ - 1];
/* L50: */
	}
	xcomp[2] = cheb_1.abfrcb[0];
    } else if (*itbl == -3) {
	intpt_(pl, tl, tab1c_1.tdvr1c, &c__16, &c__87, &c__20, tab1a_1.tlog1, 
		&tab1a_1.nt1, &tab1a_1.nr1, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 20; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 60       VAROUT(3,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 3] = varo[i__ - 1];
/* L60: */
	}
	xcomp[3] = chec_1.abfrcc[0];
    } else if (*itbl == 3) {
	intpt_(pl, tl, tab2c_1.tdvr2c, &c__79, &c__21, &c__20, tab2a_1.tlog2, 
		&tab2a_1.nt2, &tab2a_1.nr2, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 20; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 70       VAROUT(3,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 3] = varo[i__ - 1];
/* L70: */
	}
	xcomp[3] = chec_1.abfrcc[0];
/*     CENTER TABLES */
    } else if (*itbl == 4) {
	intpt_(pl, tl, tabx1_1.tdvrx1, &c__10, &c__21, &c__25, tabx1_1.tlogx, 
		&tabx1_1.ntx, &tabx1_1.nrx, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 25; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 100      VAROUT(4,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 4] = varo[i__ - 1];
/* L100: */
	}
	xcomp[4] = che1_1.abfrc1[0];
    } else if (*itbl == 5) {
	intpt_(pl, tl, tabx2_1.tdvrx2, &c__10, &c__21, &c__25, tabx1_1.tlogx, 
		&tabx1_1.ntx, &tabx1_1.nrx, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 25; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 110      VAROUT(5,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 5] = varo[i__ - 1];
/* L110: */
	}
	xcomp[5] = che2_1.abfrc2[0];
    } else if (*itbl == 6) {
	intpt_(pl, tl, tabx3_1.tdvrx3, &c__10, &c__21, &c__25, tabx1_1.tlogx, 
		&tabx1_1.ntx, &tabx1_1.nrx, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 25; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 120      VAROUT(6,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 6] = varo[i__ - 1];
/* L120: */
	}
	xcomp[6] = che3_1.abfrc3[0];
    } else if (*itbl == 7) {
	intpt_(pl, tl, tabx4_1.tdvrx4, &c__10, &c__21, &c__25, tabx1_1.tlogx, 
		&tabx1_1.ntx, &tabx1_1.nrx, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 25; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 130      VAROUT(7,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 7] = varo[i__ - 1];
/* L130: */
	}
	xcomp[7] = che4_1.abfrc4[0];
    } else if (*itbl == 8) {
	intpt_(pl, tl, tabx5_1.tdvrx5, &c__10, &c__21, &c__25, tabx1_1.tlogx, 
		&tabx1_1.ntx, &tabx1_1.nrx, vvar1, vvar2, vy, varo);
	for (i__ = 1; i__ <= 25; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 140      VAROUT(8,I) = VARO(I) */
	    varout[i__ * varout_dim1 + 8] = varo[i__ - 1];
/* L140: */
	}
	xcomp[8] = che5_1.abfrc5[0];
    }
/*     END SELECTION OF TABLES */
    return 0;
/*   999 RETURN */
} /* mhdpx2_ */

