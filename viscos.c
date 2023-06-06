/* viscos.f -- translated by f2c (version 20100827).
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

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal cp[5000], hamu[5000], sqdt[5000], thdif[5000], visc[5000];
} temp_;

#define temp_1 temp_

/* $$$$$$ */
/* Subroutine */ int viscos_(doublereal *hcomp, doublereal *hd, doublereal *
	ht, logical *lc, integer *m)
{
    /* Initialized data */

    static doublereal amu = 1.6605655e-24;
    static doublereal weight[11] = { 1.007825,4.0026,1.,3.01603,12.,13.00335,
	    14.00307,15.0011,15.99491,16.99491,17.99491 };
    static doublereal z__[11] = { 1.,2.,0.,2.,6.,6.,7.,7.,8.,8.,8. };

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal), log(doublereal), sqrt(doublereal);

    /* Local variables */
    static doublereal c__;
    static integer i__, j;
    static doublereal o, t, t2;
    static integer im;
    static doublereal zf, con, rho, sum, visc2, elecn, compn[11], viscr, 
	    viscx[11], viscy[11], lambd1, viscr2, vismo2, factor, comsum, 
	    vismol;

    /* Parameter adjustments */
    --lc;
    --ht;
    --hd;
    hcomp -= 16;

    /* Function Body */
/*  SKIP CONVECTIVE ZONES */
    i__1 = *m;
    for (im = 1; im <= i__1; ++im) {
/*  COMPUTE THE KINEMATIC MICROSCOPIC VISCOSITY DUE TO RADIATION AND IONS */
/*  CONVERT TO NUMBER DENSITIES AND FIND MEAN CHARGE PER ION(ZF) AND NE. */
	o = scrtch_1.so[im - 1];
	zf = 0.;
	comsum = 0.;
	for (i__ = 1; i__ <= 11; ++i__) {
	    compn[i__ - 1] = hcomp[i__ + im * 15] / weight[i__ - 1];
	    comsum += compn[i__ - 1];
	    zf += compn[i__ - 1] * z__[i__ - 1];
/* L10: */
	}
	zf /= comsum;
	t = exp(const1_1.cln * ht[im]);
/* Computing 2nd power */
	d__1 = t;
	t2 = d__1 * d__1;
	rho = exp(const1_1.cln * hd[im]);
	elecn = zf * rho / amu;
/*  RADIATIVE DYNAMIC VISCOSITY (ELECTRON SCATTERING ONLY): */
/*  METHOD USED(VISCR) IS FROM LEDOUX,1958,HANDBUCH DER PHYSIK VOL.LI,P.445 */
/*  ENDAL-SOFIA(VISCR2) METHOD REF. THOMAS,L.H. 1930,QUART.J.MATH,1,237 */
/*  ENDAL-SOFIA VALUES CALCULATED FOR COMPARISON ONLY. */
/* Computing 2nd power */
	d__1 = rho;
	viscr = t2 * 6.7282653e-26 * t2 / (o * (d__1 * d__1));
/* Computing 2nd power */
	d__1 = rho;
	viscr2 = t2 * 3.36e-25 * t2 / (hcomp[im * 15 + 1] + 1.) / (d__1 * 
		d__1);
/*  MOLECULAR DYNAMIC VISCOSITY */
/*  REF. SPITZER,1962,PHYSICS OF FULLY IONIZED GASES */
/*  AGAIN, ENDAL-SOFIA METHOD STORED IN VISMO2 FOR COMPARISON PURPOSES. */
/*  ACTUAL MOLECULAR VISCOSITY USED STORED IN VISMOL. */
/* Computing MIN */
	d__1 = 1., d__2 = 4.2e5 / t;
	factor = min(d__1,d__2);
/* Computing 2nd power */
	d__1 = zf;
	lambd1 = log(t2 * t * factor / (elecn * (d__1 * d__1))) * .5 + 
		9.424536845;
	c__ = sqrt(t) * 3.125e-15 * t2;
	vismol = 0.;
/*  VISCX(I) IS THE MOLECULAR VISCOSITY OF SPECIES I. */
	for (i__ = 1; i__ <= 11; ++i__) {
	    if (i__ == 3) {
		goto L30;
	    }
/* Computing 2nd power */
	    d__1 = z__[i__ - 1];
	    con = c__ * compn[i__ - 1] * sqrt(weight[i__ - 1]) / ((lambd1 - 
		    log(z__[i__ - 1])) * (d__1 * d__1));
	    sum = 0.;
	    for (j = 1; j <= 11; ++j) {
		if (j == 3) {
		    goto L20;
		}
/* Computing 2nd power */
		d__1 = z__[j - 1];
		sum += compn[j - 1] * (d__1 * d__1) * sqrt((weight[i__ - 1] + 
			weight[j - 1]) / weight[j - 1]);
L20:
		;
	    }
	    if (abs(sum) < 1e-38) {
		goto L30;
	    }
	    viscx[i__ - 1] = con / sum;
	    if (viscx[i__ - 1] > 0.) {
		vismol += viscx[i__ - 1];
	    }
L30:
	    ;
	}
	vismol /= rho;
	temp_1.visc[im - 1] = viscr + vismol;
/*  NOW COMPUTE USING ENDAL-SOFIA METHOD */
	vismo2 = 0.;
	con = sqrt(t) * 2.21e-15 * t2;
	for (i__ = 1; i__ <= 11; ++i__) {
	    if (i__ == 3) {
		goto L40;
	    }
/* Computing 4th power */
	    d__1 = z__[i__ - 1], d__1 *= d__1;
	    viscy[i__ - 1] = con * hcomp[i__ + im * 15] / (sqrt(weight[i__ - 
		    1]) * (d__1 * d__1) * (lambd1 - log(z__[i__ - 1])));
	    if (viscy[i__ - 1] > 0.) {
		vismo2 += viscy[i__ - 1];
	    }
L40:
	    ;
	}
	vismo2 = vismo2 / rho / comsum;
	visc2 = viscr2 + vismo2;
/*  THERMAL DIFFUSIVITY(THDIF) DUE TO RADIATION IS CALCULATED */
/*  COMPONENT DUE TO THERMAL CONDUCTION OF MATTER IS NEGLECTED */
/*  RADIATIVE DIFFUSIVITY = K*T**3/(O*RHO**2*CP) */
/* Computing 2nd power */
	d__1 = rho;
	temp_1.thdif[im - 1] = const1_1.cc13 * 16. * 5.669e-5 * t * t2 / (o * 
		(d__1 * d__1) * temp_1.cp[im - 1]);
/* L100: */
    }
    return 0;
} /* viscos_ */

