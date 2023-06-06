/* htimer.f -- translated by f2c (version 20100827).
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
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    logical lptime;
} ct3_;

#define ct3_1 ct3_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal endage[50], setdt[50];
    logical lendag[50], lsetdt[50];
} sett_;

#define sett_1 sett_

/* Table of constant values */

static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* HTIMER */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int htimer_(doublereal *delts, doublereal *deltsh, integer *
	m, doublereal *hd, doublereal *hl, doublereal *hs1, doublereal *hs2, 
	doublereal *ht, logical *lc, doublereal *hcomp, integer *jcore, 
	integer *jxmid, doublereal *tlumx, doublereal *dage, doublereal *
	ddage, doublereal *qdt, doublereal *qdp, integer *nk, doublereal *hp, 
	doublereal *hr, doublereal *omega, doublereal *dwmax, integer *jxbeg)
{
    /* Format strings */
    static char fmt_100[] = "(\002LPTIME SET FALSE - TC \002,f7.4,\002 EGR"
	    "AV \002,e10.2)";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal eg[6], hf1[5000], hf2[5000], hr1[5000], hr2[5000], hr3[
	    5000], hr4[5000], hr5[5000], hr6[5000], hr7[5000], hr8[5000], hr9[
	    5000], hr10[5000], hr11[5000], hr12[5000], hr13[5000], pdelt;
    extern /* Subroutine */ int ptime_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, integer *, doublereal *);
    static doublereal tleft;
    extern /* Subroutine */ int wtime_(doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *), xtime_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *), ytime_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *);
    static doublereal deltsw, hydlum, deltsy;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_100, 0 };


/*  HTIMER DETERMINES THE TIMESTEP FOR THE NEXT MODEL. */
/*  THERE ARE SEVERAL POSSIBLE MEANS OF DETERMINING THE TIMESTEP; IT CHOOSES */
/*  THE MOST STRINGENT ONE. */
/*  FIRST OF ALL, THE TIMESTEP MAY NOT BE MORE THAN ATIME(13) TIMES THE */
/*       PREVIOUS ONE. */
/*  IN SR PTIME, THE TIMESTEP BASED ON STRUCTURE CHANGES FROM ONE */
/*       MODEL TO THE NEXT IS COMPUTED IF DESIRED(PDELT). */
/*  IN SR WTIME, THE TIMESTEP BASED ON CHANGES IN THE ANGULAR VELOCITY */
/*       FROM ONE MODEL TO THE NEXT IS COMPUTED(ROTATING MODELS ONLY)(DELTSW). */
/*  IN SR XTIME, THE TIMESTEP BASED ON HYDROGEN BURNING IS COMPUTED.(DELTSH). */
/*  IN SR YTIME, THE TIMESTEP BASED ON HELIUM BURNING IS COMPUTED(DELTSY). */
/*  DETAILS OF THE COMPUTATION OF THESE TIMESTEPS CAN BE FOUND IN THE */
/*       APPROPRIATE SUBROUTINES. */
/*  THE FINAL TIMESTEP (DELTS) IS THE MINIMUM OF THE ABOVE TIMESTEPS. */
/*  **NOTE : IF A CRITERION IS INAPPLICABLE OR TURNED OFF BY USER PARAMETERS */
/*       THEN THE 'TIMESTEP' FOR THAT CRITERION IS ARBITRARILY SET TO A */
/*       LARGE NUMBER. */
/*  IF A FIXED TIMESTEP IS BEING ENFORCED (LSETDT=T), THE ABOVE CRITERIA ARE */
/*  SHORT-CIRCUITED AND A TIMESTEP(SETDT) IS ENFORCED. CAVEAT USER. */
/*  IF THE MODEL IS BEING EVOLVED TO A FIXED AGE(LENDAG=T), THE TIMESTEP WILL BE */
/*  REDUCED IF THE ONE USED WOULD PUT THE MODEL PAST THE DESIRED AGE(ENDAGE). */

/*  A NEGATIVE TIMESTEP INDICATES THAT A MODEL IS BEING RELAXED */
/*  AND NOT EVOLVED.  CHECK FOR NEGATIVE DT AND EXIT IF FOUND. */
    /* Parameter adjustments */
    --omega;
    --hr;
    --hp;
    --tlumx;
    hcomp -= 16;
    --lc;
    --ht;
    --hs2;
    --hs1;
    --hl;
    --hd;

    /* Function Body */
    if (*delts < 0.) {
	goto L310;
    }
/* IF USER IS FIXING TSTEP, SET DT TO GIVEN VALUE AND EXIT */
    if (sett_1.lsetdt[*nk - 1]) {
	*deltsh = sett_1.setdt[*nk - 1] * const3_1.csecyr;
	*delts = *deltsh;
	goto L310;
    }
/* MHP 9/01  TURN OFF STRUCTURE-BASED TIMESTEP SETTING ABOVE A CRITICAL */
/*           TEMPERATURE; THIS IS DONE WHEN */
    if (ct3_1.lptime) {
	if (ht[1] > 7.1 && tlumx[7] < 0.) {
	    s_wsfe(&io___1);
	    do_fio(&c__1, (char *)&ht[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlumx[7], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    ct3_1.lptime = FALSE_;
	}
    }
/*  FIND TIMESTEP BASED ON CHANGES IN STRUCTURE VARIABLES FROM */
/*       ONE MODEL TO THE NEXT. */
/*  NOTE THAT THIS RETURNS THE TIMESTEP STORED IN THE MODEL ON THE */
/*       FIRST CALL TO HTIMER FOR EACH KIND CARD. */
    if (ct3_1.lptime) {
	ptime_(delts, &hl[1], &hp[1], &hr[1], &ht[1], m, &pdelt);
    } else {
	pdelt = 1e20;
    }
/*  MHP 6/90 A ZERO TIMESTEP IN THE MODEL WILL FRITZ OUT THE CODE, SO */
/*  AVOID THIS BY SETTING THE STRUCTURE TIMESTEP ARBITRARILY LARGE. */
    if (pdelt < 1.) {
	pdelt = 1e20;
    }
/*  FIND TIMESTEP FOR ROTATING MODELS BASED ON CHANGES IN ANGULAR VELOCITY */
/*       FROM ONE MODEL TO THE NEXT. */
/*  THIS SR ALSO RETURNS THE MAXIMUM CHANGE IN OMEGA FROM THE PREVIOUS */
/*       MODEL TO THE CURRENT ONE, WHICH IS USED IN THE DIFFUSION ROUTINE */
/*       TO DETERMINE THE NUMBER OF DIFFUSION TIMESTEPS REQUIRED. */
/*  NOTE THAT THIS RETURNS THE TIMESTEP STORED IN THE MODEL ON THE */
/*       FIRST CALL TO HTIMER FOR EACH KIND CARD. */
    if (rot_1.lrot) {
	wtime_(delts, m, &omega[1], &deltsw, dwmax);
    } else {
	deltsw = 1e20;
    }
/*  MHP 6/90 A ZERO TIMESTEP IN THE MODEL WILL FRITZ OUT THE CODE, SO */
/*  AVOID THIS BY SETTING THE ROTATION TIMESTEP ARBITRARILY LARGE. */
    if (deltsw < 1.) {
	deltsw = 1e20;
    }
/*  FIND THE TIMESTEP BASED ON HYDROGEN BURNING. */
/*  DETERMINE THE TOTAL LUMINOSITY DUE TO HYDROGEN BURNING (IN SOLAR UNITS). */
    hydlum = tlumx[1] + tlumx[2] + tlumx[3] + tlumx[4];
/*  SKIP H-BURNING TIMESTEP CRITERIA FOR STARS WITHOUT H BURNING. */
    if (hydlum > 1e-34) {
	xtime_(&hd[1], &hcomp[16], &hl[1], &hs1[1], &hs2[1], &ht[1], &hydlum, 
		jcore, jxmid, m, deltsh, hr1, hr2, hr3, hr4, hr5, hr6, hr7, 
		hr8, hr9, hr10, hr11, hr12, hr13, hf1, hf2, jxbeg);
    } else {
	*deltsh = 1e20;
    }
/*  FIND THE TIMESTEP BASED ON HELIUM BURNING. */
/*  SKIP FOR STARS WITHOUT HE BURNING. */
    if (tlumx[5] > 1e-34) {
	ytime_(eg, &hcomp[16], &hd[1], &hl[1], &hs1[1], &ht[1], jcore, m, &
		deltsy, hr1, hr2, hr3, hr4, hr5, hr6, hr7, hr8, hr9, hr10, 
		hr11, hr12, hr13, hf1, hf2, qdp, qdt, jxbeg);
    } else {
	deltsy = 1e20;
    }
/*     LIMIT INCREASE IN TIME STEP FROM ONE MODEL TO THE NEXT FOR MODELS */
/*     WITH A NON-ZERO TIMESTEP. */
/*      write(*,299)PDELT,DELTSW,DELTSH,DELTSY,DELTS */
/* 299  format('P ',E10.5,' W ',E10.5,' H ',E10.5,' He ',E10.5,' prev. ', */
/*     * E10.5) */
/*         WRITE(*,*)'H time ',DELTSH/CSECYR,'   He Time ',DELTSY/CSECYR */
    if (*delts > 1.) {
	*delts = ctlim_1.atime[12] * *delts;
/*  NOW SET THE TIMESTEP TO BE THE MINIMUM OF THE ENTROPY BASED TIMESTEP, */
/*  THE NUCLEAR BURNING TIMESTEPS, AND THE PREVIOUS TIMESTEP*ATIME(13). */
/* Computing MIN */
	d__1 = min(*delts,*deltsh), d__1 = min(d__1,deltsy), d__1 = min(d__1,
		deltsw);
	*delts = min(d__1,pdelt);
    } else {
/*  SET THE TIMESTEP TO BE THE MINIMUM OF THE THE ABOVE TIMESTEPS, */
/*  BUT NEGLECT THE PREVIOUS TIMESTEP. */
/* Computing MIN */
	d__1 = min(*deltsh,deltsy), d__1 = min(d__1,deltsw);
	*delts = min(d__1,pdelt);
    }
/* ******** Grant added ******** */
/*      IF(TLUMX(5).GT.1.0D-2) THEN */
/*         ATIME(6)=0.000025 */
/*         ATIME(5)=0.01 */
/*       IF(TLUMX(5).GT.5.0D-1) THEN */
/*         ATIME(6)=0.0000075 */
/*         ATIME(5)=0.003 */
/*       IF(TLUMX(5).GT.5.0D0) THEN */
/*         ATIME(6)=0.00000075 */
/*         ATIME(5)=0.0003 */
/*       IF(TLUMX(5).GT.5.0D01) THEN */
/*         ATIME(6)=0.000000025 */
/*         ATIME(5)=0.00001 */
/*       IF(TLUMX(5).GT.5.0D02) THEN */
/*         ATIME(6)=0.000000005 */
/*         ATIME(5)=0.000005 */
/*       IF(TLUMX(5).GT.2.0D03) THEN */
/*         ATIME(6)=0.0000000005 */
/*         ATIME(5)=0.0000005 */
/*         ENDIF */
/*         ENDIF */
/*         ENDIF */
/*         ENDIF */
/*         ENDIF */
/*      ENDIF */
/* ***************************** */
    *deltsh = *delts;
L310:
    *delts = abs(*delts);
    *ddage = *delts / const3_1.csecyr;
/*  IF EVOLVING TO A GIVEN AGE, ENSURE AGE NOT EXCEEDED */
    if (sett_1.lendag[*nk - 1]) {
	tleft = sett_1.endage[*nk - 1] - *dage * 1e9;
	if (tleft < *ddage) {
	    *ddage = tleft;
	    *deltsh = *ddage * const3_1.csecyr;
	    *delts = *deltsh;
	}
    }
    return 0;
} /* htimer_ */

