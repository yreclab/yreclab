/* chkcal.f -- translated by f2c (version 20100827).
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
    doublereal rescal[200]	/* was [4][50] */;
    integer nmodls[50], iresca[50];
    logical lfirst[50];
    integer numrun;
} ckind_;

#define ckind_1 ckind_

struct {
    doublereal endage[50], setdt[50];
    logical lendag[50], lsetdt[50];
} sett_;

#define sett_1 sett_

struct {
    doublereal xenv0a[50], zenv0a[50], cmixla[50];
    logical lsenv0a[50];
    doublereal senv0a[50];
} newxym_;

#define newxym_1 newxym_

struct {
    doublereal dldx, drdx, dlda, drda, blp, rlp, dx, da;
    logical lsol;
} calsun_;

#define calsun_1 calsun_

struct {
    doublereal toll, tolr;
    logical lcals;
} cals2_;

#define cals2_1 cals2_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;

/* $$$$$$ */
/* Subroutine */ int chkcal_(doublereal *bl, doublereal *rl, integer *n)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, 0, 0 };
    static cilist io___2 = { 0, 0, 0, 0, 0 };
    static cilist io___3 = { 0, 0, 0, 0, 0 };
    static cilist io___4 = { 0, 0, 0, 0, 0 };
    static cilist io___5 = { 0, 0, 0, 0, 0 };
    static cilist io___6 = { 0, 0, 0, 0, 0 };
    static cilist io___7 = { 0, 0, 0, 0, 0 };


/*     ONLY CALLED FOR EVEN NK, ASSUMES RESCALING ON ODD NK AND EVOLVING */
/*     ON EVEN NK */
/* MHP 10/02 MISSING LOGICAL UNIT IOWR ADDED */
/*     DATA TOLL,TOLR/1.0D-5,1.0D-4/ */
/* CHECK TO SEE IF THE MODEL IS A CALIBRATED SOLAR MODEL. */
/* IF NOT, ESTIMATE CORRECTIONS TO X AND ALPHA. */
    if (abs(*bl) < cals2_1.toll && abs(*rl) < cals2_1.tolr) {
/* CALIBRATED SOLAR MODEL.  SET UP OUTPUT FLAGS AND EXIT */
	calsun_1.lsol = TRUE_;
	goto L9999;
    }
/* Added code to use pre-determined partial derivatives    LLP  6/28/09 */
    calsun_1.dldx = -3.78;
/* empirical result:  -3.783    RMS error .070 */
    calsun_1.drdx = -.89;
/* empirical result:  -0.890    RMS error .048 */
    calsun_1.dlda = .0139;
/* empirical result:  +0.139    RMS error .0022 */
    calsun_1.drda = -.05;
/* empirical result:  -0.0504   RMS error .0059 */
    goto L1234;
/* mhp 5/96 added change to compute solar calibration for 3 kind cards */
/* Bypass partial derivative code */
    if (*n == 3) {
/*     SET UP RUN TO DETERMINE DERIVATIVE OF L AND R WITH RESPECT TO X. */

/*     3.7 is empirical average dL/dX, so trial DX is BL / (dL/dX)   ! llp 6/18/09 */
/*         DX = BL/3.7D0 */
/*         DX = +.01 */
	ckind_1.rescal[(*n + 1 << 2) - 3] = ckind_1.rescal[1] + calsun_1.dx;
/* STORE PREVIOUS L AND R. */
	newxym_1.xenv0a[*n] = ckind_1.rescal[(*n + 1 << 2) - 3];
	newxym_1.xenv0a[*n + 1] = newxym_1.xenv0a[*n];
	newxym_1.xenv0a[*n + 2] = newxym_1.xenv0a[*n];
	calsun_1.blp = *bl;
	calsun_1.rlp = *rl;
	goto L9999;
    } else if (*n == 6) {
/*     EVALUATE DERIVATIVE OF L AND R WITH RESPECT TO X. */
/*         DLDX = (BL - BLP)/DX */
/*         DRDX = (RL - RLP)/DX */
/*         WRITE(IOWR,*) "DX,DLDX,BL,BLP,DRDX,RL,RLP: ", */
/*     *      DX,DLDX,BL,BLP,DRDX,RL,RLP */
/*     SET UP RUN TO DETERMINE DERIVATIVE OF L AND R WITH RESPECT TO ALPHA. */
/*     .042 is typical average dR/dA, so trial DA is RL / (dR/dA)   ! llp 6/18/09 */
/*         DA = RL/0.042D0 */
	newxym_1.cmixla[*n] = newxym_1.cmixla[0] + calsun_1.da;
	newxym_1.cmixla[*n + 1] = newxym_1.cmixla[*n];
	newxym_1.cmixla[*n + 2] = newxym_1.cmixla[*n];
	ckind_1.rescal[(*n + 1 << 2) - 3] = ckind_1.rescal[1];
	newxym_1.xenv0a[*n] = newxym_1.xenv0a[0];
	newxym_1.xenv0a[*n + 1] = newxym_1.xenv0a[*n];
	newxym_1.xenv0a[*n + 2] = newxym_1.xenv0a[*n];
	calsun_1.blp = *bl;
	calsun_1.rlp = *rl;
	goto L9999;
    } else if (*n == 9) {
/*     EVALUATE DERIVATIVE OF L AND R WITH RESPECT TO ALPHA. */
	calsun_1.dlda = (*bl - calsun_1.blp) / calsun_1.da;
	calsun_1.drda = (*rl - calsun_1.rlp) / calsun_1.da;
	io___1.ciunit = luout_1.iowr;
	s_wsle(&io___1);
	do_lio(&c__9, &c__1, "DA,DLDA,BL,BLP,DRDA,RL,RLP: ", (ftnlen)28);
	do_lio(&c__5, &c__1, (char *)&calsun_1.da, (ftnlen)sizeof(doublereal))
		;
	do_lio(&c__5, &c__1, (char *)&calsun_1.dlda, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&calsun_1.blp, (ftnlen)sizeof(doublereal)
		);
	do_lio(&c__5, &c__1, (char *)&calsun_1.drda, (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&calsun_1.rlp, (ftnlen)sizeof(doublereal)
		);
	e_wsle();
/*     USE DERIVATIVES OF L AND R WITH RESPECT TO X AND ALPHA TO */
/*     GET IMPROVED GUESSES FOR ALPHA AND X. */
	calsun_1.da = (*bl * calsun_1.drdx / calsun_1.dldx - *rl) / (
		calsun_1.drda - calsun_1.dlda * calsun_1.drdx / calsun_1.dldx)
		;
	calsun_1.dx = -(*bl + calsun_1.dlda * calsun_1.da) / calsun_1.dldx;
	newxym_1.cmixla[*n] = newxym_1.cmixla[0] + calsun_1.da;
	newxym_1.cmixla[*n + 1] = newxym_1.cmixla[*n];
	newxym_1.cmixla[*n + 2] = newxym_1.cmixla[*n];
	ckind_1.rescal[(*n + 1 << 2) - 3] = ckind_1.rescal[1] + calsun_1.dx;
	newxym_1.xenv0a[*n] = ckind_1.rescal[(*n + 1 << 2) - 3];
	newxym_1.xenv0a[*n + 1] = ckind_1.rescal[(*n + 1 << 2) - 3];
	newxym_1.xenv0a[*n + 2] = ckind_1.rescal[(*n + 1 << 2) - 3];
	calsun_1.blp = *bl;
	calsun_1.rlp = *rl;
	io___2.ciunit = luout_1.iowr;
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, "New X, Old X, Calc DX: ", (ftnlen)23);
	do_lio(&c__5, &c__1, (char *)&ckind_1.rescal[(*n + 1 << 2) - 3], (
		ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&ckind_1.rescal[1], (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&calsun_1.dx, (ftnlen)sizeof(doublereal))
		;
	e_wsle();
	io___3.ciunit = luout_1.iowr;
	s_wsle(&io___3);
	do_lio(&c__9, &c__1, "New A, Old A, Calc DA: ", (ftnlen)23);
	do_lio(&c__5, &c__1, (char *)&newxym_1.cmixla[*n], (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&newxym_1.cmixla[0], (ftnlen)sizeof(
		doublereal));
	do_lio(&c__5, &c__1, (char *)&calsun_1.da, (ftnlen)sizeof(doublereal))
		;
	e_wsle();
	goto L9999;
/*      ELSE */
    }
/* terrminate old partial derivative code */
L1234:
/*     USE DERIVATIVES OF L AND R WITH RESPECT TO X AND ALPHA TO */
/*     GET IMPROVED GUESSES FOR ALPHA AND X. */
    calsun_1.da = (*bl * calsun_1.drdx / calsun_1.dldx - *rl) / (
	    calsun_1.drda - calsun_1.dlda * calsun_1.drdx / calsun_1.dldx);
    calsun_1.dx = -(*bl + calsun_1.dlda * calsun_1.da) / calsun_1.dldx;
    newxym_1.cmixla[*n] = newxym_1.cmixla[*n - 3] + calsun_1.da;
    newxym_1.cmixla[*n + 1] = newxym_1.cmixla[*n];
    newxym_1.cmixla[*n + 2] = newxym_1.cmixla[*n];
    ckind_1.rescal[(*n + 1 << 2) - 3] = ckind_1.rescal[(*n - 2 << 2) - 3] + 
	    calsun_1.dx;
    newxym_1.xenv0a[*n] = ckind_1.rescal[(*n + 1 << 2) - 3];
    newxym_1.xenv0a[*n + 1] = ckind_1.rescal[(*n + 1 << 2) - 3];
    newxym_1.xenv0a[*n + 2] = ckind_1.rescal[(*n + 1 << 2) - 3];
    io___4.ciunit = luout_1.iowr;
    s_wsle(&io___4);
    do_lio(&c__9, &c__1, "New BL, Old BL, Delta BL: ", (ftnlen)26);
    do_lio(&c__5, &c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&calsun_1.blp, (ftnlen)sizeof(doublereal));
    d__1 = *bl - calsun_1.blp;
    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    e_wsle();
    io___5.ciunit = luout_1.iowr;
    s_wsle(&io___5);
    do_lio(&c__9, &c__1, "New RL, Old RL, Delta RL: ", (ftnlen)26);
    do_lio(&c__5, &c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&calsun_1.rlp, (ftnlen)sizeof(doublereal));
    d__1 = *rl - calsun_1.rlp;
    do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
    e_wsle();
    io___6.ciunit = luout_1.iowr;
    s_wsle(&io___6);
    do_lio(&c__9, &c__1, "New X, Old X, DX: ", (ftnlen)18);
    do_lio(&c__5, &c__1, (char *)&ckind_1.rescal[(*n + 1 << 2) - 3], (ftnlen)
	    sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&ckind_1.rescal[(*n - 2 << 2) - 3], (ftnlen)
	    sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&calsun_1.dx, (ftnlen)sizeof(doublereal));
    e_wsle();
    io___7.ciunit = luout_1.iowr;
    s_wsle(&io___7);
    do_lio(&c__9, &c__1, "New A, Old A, DA: ", (ftnlen)18);
    do_lio(&c__5, &c__1, (char *)&newxym_1.cmixla[*n], (ftnlen)sizeof(
	    doublereal));
    do_lio(&c__5, &c__1, (char *)&newxym_1.cmixla[*n - 3], (ftnlen)sizeof(
	    doublereal));
    do_lio(&c__5, &c__1, (char *)&calsun_1.da, (ftnlen)sizeof(doublereal));
    e_wsle();
    calsun_1.blp = *bl;
    calsun_1.rlp = *rl;
    goto L9999;
/*      ENDIF */
L9999:
    return 0;
} /* chkcal_ */

