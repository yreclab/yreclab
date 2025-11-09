/* radsub06.f -- translated by f2c (version 20061008).
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
    doublereal esact, eos[10];
} eeos06_;

#define eeos06_1 eeos06_

struct {
    doublereal zz[5];
    integer iri[10], index[10], nta[169], nra[197];
} beos06_;

#define beos06_1 beos06_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     RADSUB06 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int radsub06_(integer *irad, doublereal *t6, doublereal *
	density, doublereal *moles, doublereal *tmass)
{
    /* Initialized data */

    static doublereal sigmacc = .0018914785;
    static doublereal aprop = 83.1451;

    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    static doublereal er, et, pt, pr, st, sr, gam1t_norad__, rat, 
	    gam2pt_norad__, gam3pt_norad__, chir, cvtt, gam1t, chitt, gam2pt, 
	    gam3pt, dedrho, molenak;

/*       real*8 moles,k,molenak,Na  ! KC 2025-05-31 */
/* KC 2025-05-30 reordered common block elements */
/*       common/beos06/ iri(10),index(10),nta(nr),zz(mx),nra(nt) */
/*       data Na/6.0221367D+23/, k/1.380658D-16/, unitf/0.9648530D0/, */
/*      x unitfold/0.965296D0/, c/2.9979245D10/, sigma/5.67051D-5/ */
/*      x , sigmac/1.8914785D-15/, sigmacc/1.8914785D-3/ */
/*      x , aprop/83.14510D0/  ! KC 2025-05-31 */
/* Physical constants */
/*       Na=6.0221367e+23 */
/*       k =1.380658e-16 !   erg/degree K */
/*       Na*k=6.0221367E+23*1.380658e-16 erg/degree K=8.314510E+7 erg/degree K */
/*           =8.314510e+7*11604.5 erg/eV=0.9648575E+12 erg/eV */
/*           Define unitf= Na*k/e+12=0.9648575 */
/*           unitf=0.9648530  ! obtained with latest physical constants */
/*           unitfold=0.965296   ! old units- still used in the EOS code */
/*           In these units energy/density is in units of Mb-CC/gm */
/*           Pressure is in units of E+12 bars=Mb */
/*       sigma is the Stefan-Boltzmann constant */
/*       sigma=5.67051E-5 !   erg /(s*cm**2*K**4) */
/*       c=2.99792458E+10 !   cm/sec */
/*     rat=sigma/c    ! dyne/(cm**2*K**4) */
/*     rat=rat*1.e+24  !   Convert degrees K to units 10**6 K (T replaced with T6) */
    rat = sigmacc;
    molenak = *moles * aprop;
/* -----Calculate EOS without radiation correction */
/* Mb-cc/unit T6 */
    pt = eeos06_1.eos[beos06_1.iri[0] - 1];
    et = eeos06_1.eos[beos06_1.iri[1] - 1];
    st = eeos06_1.eos[beos06_1.iri[2] - 1];
    dedrho = eeos06_1.eos[beos06_1.iri[3] - 1];
    chir = eeos06_1.eos[beos06_1.iri[5] - 1] * eeos06_1.eos[beos06_1.iri[0] - 
	    1] / pt;
    chitt = eeos06_1.eos[beos06_1.iri[0] - 1] * eeos06_1.eos[beos06_1.iri[6] 
	    - 1] / pt;
    cvtt = eeos06_1.eos[beos06_1.iri[4] - 1] * molenak / *tmass;
    gam3pt_norad__ = pt * chitt / (cvtt * *density * *t6);
    gam1t_norad__ = chir + chitt * gam3pt_norad__;
    gam2pt_norad__ = gam1t_norad__ / gam3pt_norad__;
/* ---- End  no radiation calculation */
    if (*irad != 0) {
/* ---- Calculate EOS with radiation calculation */
/* Computing 4th power */
	d__1 = *t6, d__1 *= d__1;
	pr = rat * 1.3333333333333333 * (d__1 * d__1);
/* Mb */
	er = pr * 3. / *density;
/* Mb-cc/gm */
	sr = er * 1.3333333333333333 / *t6;
/* Mb-cc/(gm-unit T6) */
	pt = eeos06_1.eos[beos06_1.iri[0] - 1] + pr;
	et = eeos06_1.eos[beos06_1.iri[1] - 1] + er;
	st = eeos06_1.eos[beos06_1.iri[2] - 1] + sr;
	dedrho = eeos06_1.eos[beos06_1.iri[3] - 1] - er / *density;
	chir = eeos06_1.eos[beos06_1.iri[5] - 1] * eeos06_1.eos[beos06_1.iri[
		0] - 1] / pt;
	chitt = (eeos06_1.eos[beos06_1.iri[0] - 1] * eeos06_1.eos[
		beos06_1.iri[6] - 1] + pr * 4.) / pt;
/*     gam1t(jcs,i)=(p(jcs,i)*gam1(jcs,i)+4D0/3D0*pr)/pt(jcs,i) */
/*     gam2pt(jcs,i)=(gam2p(jcs,i)*p(jcs,i)+4D0*pr)/pt(jcs,i) */
/*     gam3pt(jcs,i)=gam1t(jcs,i)/gam2pt(jcs,i) */
	cvtt = eeos06_1.eos[beos06_1.iri[4] - 1] * molenak / *tmass + er * 4. 
		/ *t6;
	gam3pt = pt * chitt / (cvtt * *density * *t6);
/* DIRECT */
	gam1t = chir + chitt * gam3pt;
/* eq 16.16 Landau_Lifshitz (Stat. Mech) ! DIRECT */
	gam2pt = gam1t / gam3pt;
/*     normalize cvt to 3/2 when gas is ideal,non-degenerate, */
/*     fully-ionized, and has no radiation correction */
/*     cvt=(eos(5)*molenak/tmass+4.*er/t6) */
/*    x  /molenak */
/* -----Add difference between EOS with and without radiation.  cvtt */
/*       calculation is not accurate enough to give accurate results using */
/*       eq. 16.16 Landau&Lifshitz (SEE line labeled DIRECT) */
/* DIRECT */
	eeos06_1.eos[beos06_1.iri[7] - 1] = eeos06_1.eos[beos06_1.iri[7] - 1] 
		+ gam1t - gam1t_norad__;
	eeos06_1.eos[beos06_1.iri[8] - 1] = eeos06_1.eos[beos06_1.iri[8] - 1] 
		+ gam2pt - gam2pt_norad__;
/*     eos(iri(10))=eos(iri(10))+gam3pt-gam3pt_norad */
    }
/* -----End EOS calculations with radiation */
/*     normalize cvt to 3/2 when gas is ideal,non-degenerate, */
/*     fully-ionized, and has no radiation correction */
/*     cvt=(eos(5)*molenak/tmass+4.*er/t6) */
/*    x  /molenak */
    eeos06_1.eos[beos06_1.iri[0] - 1] = pt;
    eeos06_1.eos[beos06_1.iri[1] - 1] = et;
    eeos06_1.eos[beos06_1.iri[2] - 1] = st;
    eeos06_1.eos[beos06_1.iri[3] - 1] = dedrho;
    eeos06_1.eos[beos06_1.iri[4] - 1] = cvtt;
    eeos06_1.eos[beos06_1.iri[5] - 1] = chir;
    eeos06_1.eos[beos06_1.iri[6] - 1] = chitt;
    return 0;
} /* radsub06_ */

