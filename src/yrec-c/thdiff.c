/* thdiff.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static integer c__42 = 42;

/* ************************************************************* */
/* This routine was written by Anne A. Thoul, at the Institute */
/* for Advanced Study, Princeton, NJ 08540. */
/* See Thoul et al., Ap.J. 421, p. 828 (1994) */
/* The subroutines LUBKSB and LUDCMP are from Numerical Recipes. */
/* ************************************************************* */
/* This routine inverses the burgers equations. */

/* The system contains N equations with N unknowns. */
/* The equations are: the M momentum equations, */
/*                    the M energy equations, */
/*                    two constraints: the current neutrality */
/*                                     the zero fluid velocity. */
/* The unknowns are: the M diffusion velocities, */
/*                   the M heat fluxes, */
/*                   the electric field E */
/*                   the gravitational force g. */

/* ************************************************** */
/* Subroutine */ int thdiff_(integer *m, doublereal *a, doublereal *z__, 
	doublereal *x, doublereal *cl, doublereal *ap, doublereal *at, 
	doublereal *ax)
{
    /* System generated locals */
    integer ax_dim1, ax_offset, cl_dim1, cl_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal c__[20], d__;
    static integer i__, j;
    static doublereal k[400]	/* was [20][20] */;
    static integer l, n;
    static doublereal y[400]	/* was [20][20] */, ac, cc, ga[42], ko, nu[42]
	    , xx[400]	/* was [20][20] */, yy[400]	/* was [20][20] */;
    static integer indx[42];
    static doublereal temp, gamma[1764]	/* was [42][42] */, alpha[42], delta[
	    1764]	/* was [42][42] */;
    extern /* Subroutine */ int lubksb_(doublereal *, integer *, integer *, 
	    integer *, doublereal *), ludcmp_(doublereal *, integer *, 
	    integer *, integer *, doublereal *);

/* The parameter M is the number of species considered. */

/* Fluid 1 is the hydrogen */
/* Fluid 2 is the helium */
/* Fluids 3 to M-1 are the heavy elements */
/* Fluid M is the electrons */

/* The vectors A,Z and X contain the atomic mass numbers, */
/* the charges (ionization), and the mass fractions, of the elements. */
/* NOTE: Since M is the electron fluid, its mass and charge must be */
/*      A(M)=m_e/m_u */
/*      Z(M)=-1. */

/* The array CL contains the values of the Coulomb Logarithms. */
/* The vector AP, AT, and array AX contains the results for the diffusion */
/* coefficients. */
/*      INTEGER M,N,I,J,L,MMAX,NMAX */
/* The vectors C and GRADC contain the concentrations and the */
/* concentration gradients; */
/* CC is the total concentration: CC=sum(C_s) */
/* AC is proportional to the mass density: AC=sum(A_s C_s) */
/* The arrays XX,Y,YY and K are various parameters which appear in */
/* Burgers equations. */
/* The vectors and arrays ALPHA, NU, GAMMA, DELTA, and GA represent */
/* the "right- and left-hand-sides" of Burgers equations, and later */
/* the diffusion coefficients. */
/* Initialize parameters: */
    /* Parameter adjustments */
    ax_dim1 = *m;
    ax_offset = 1 + ax_dim1;
    ax -= ax_offset;
    --at;
    --ap;
    cl_dim1 = *m;
    cl_offset = 1 + cl_dim1;
    cl -= cl_offset;
    --x;
    --z__;
    --a;

    /* Function Body */
    ko = 2.;
    n = (*m << 1) + 2;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	c__[i__ - 1] = 0.;
    }
    cc = 0.;
    ac = 0.;
/* Calculate concentrations from mass fractions: */
    temp = 0.;
    i__1 = *m - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	temp += z__[i__] * x[i__] / a[i__];
    }
    i__1 = *m - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	c__[i__ - 1] = x[i__] / a[i__] / temp;
    }
    c__[*m - 1] = 1.;
/* Calculate CC and AC: */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	cc += c__[i__ - 1];
	ac += a[i__] * c__[i__ - 1];
    }
/* Calculate the mass fraction of electrons: */
    x[*m] = a[*m] / ac;
/* Calculate the coefficients of the burgers equations */
/*      do I = 1,M */
/*         DO J = 1,M */
/*            CL(I,J) = 2.2D0 */
/*         END DO */
/*      END DO */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    xx[i__ + j * 20 - 21] = a[j] / (a[i__] + a[j]);
	    y[i__ + j * 20 - 21] = a[i__] / (a[i__] + a[j]);
	    yy[i__ + j * 20 - 21] = y[i__ + j * 20 - 21] * 3. + xx[i__ + j * 
		    20 - 21] * 1.3 * a[j] / a[i__];
/* Computing 2nd power */
	    d__1 = z__[i__];
/* Computing 2nd power */
	    d__2 = z__[j];
	    k[i__ + j * 20 - 21] = cl[i__ + j * cl_dim1] * 1. * sqrt(a[i__] * 
		    a[j] / (a[i__] + a[j])) * c__[i__ - 1] * c__[j - 1] * (
		    d__1 * d__1) * (d__2 * d__2);
	}
    }
/* Write the burgers equations and the two constraints as */
/* alpha_s dp + nu_s dT + sum_t(not 2 or M) gamma_st dC_t */
/*                     = sum_t delta_st w_t */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	alpha[i__ - 1] = c__[i__ - 1] / cc;
	nu[i__ - 1] = 0.;
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    gamma[i__ + j * 42 - 43] = 0.;
	}
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    if (j != 2 && j != *m) {
		gamma[i__ + j * 42 - 43] = -c__[j - 1] / cc + c__[1] / cc * 
			z__[j] * c__[j - 1] / z__[2] / c__[1];
		if (j == i__) {
		    gamma[i__ + j * 42 - 43] += 1.;
		}
		if (i__ == 2) {
		    gamma[i__ + j * 42 - 43] -= z__[j] * c__[j - 1] / z__[2] /
			     c__[1];
		}
		gamma[i__ + j * 42 - 43] = gamma[i__ + j * 42 - 43] * c__[i__ 
			- 1] / cc;
	    }
	}
	i__2 = n;
	for (j = *m + 1; j <= i__2; ++j) {
	    gamma[i__ + j * 42 - 43] = 0.;
	}
    }
    i__1 = n - 2;
    for (i__ = *m + 1; i__ <= i__1; ++i__) {
	alpha[i__ - 1] = 0.;
	nu[i__ - 1] = c__[i__ - *m - 1] * 2.5 / cc;
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    gamma[i__ + j * 42 - 43] = 0.;
	}
    }
    alpha[n - 2] = 0.;
    nu[n - 2] = 0.;
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
	gamma[n - 1 + j * 42 - 43] = 0.;
    }
    alpha[n - 1] = 0.;
    nu[n - 1] = 0.;
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
	gamma[n + j * 42 - 43] = 0.;
    }
    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = n;
	for (j = 1; j <= i__2; ++j) {
	    delta[i__ + j * 42 - 43] = 0.;
	}
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    if (j == i__) {
		i__3 = *m;
		for (l = 1; l <= i__3; ++l) {
		    if (l != i__) {
			delta[i__ + j * 42 - 43] -= k[i__ + l * 20 - 21];
		    }
		}
	    } else {
		delta[i__ + j * 42 - 43] = k[i__ + j * 20 - 21];
	    }
	}
	i__2 = n - 2;
	for (j = *m + 1; j <= i__2; ++j) {
	    if (j - *m == i__) {
		i__3 = *m;
		for (l = 1; l <= i__3; ++l) {
		    if (l != i__) {
			delta[i__ + j * 42 - 43] += xx[i__ + l * 20 - 21] * 
				.6 * k[i__ + l * 20 - 21];
		    }
		}
	    } else {
		delta[i__ + j * 42 - 43] = y[i__ + (j - *m) * 20 - 21] * -.6 *
			 k[i__ + (j - *m) * 20 - 21];
	    }
	}
	delta[i__ + (n - 1) * 42 - 43] = c__[i__ - 1] * z__[i__];
	delta[i__ + n * 42 - 43] = -c__[i__ - 1] * a[i__];
    }
    i__1 = n - 2;
    for (i__ = *m + 1; i__ <= i__1; ++i__) {
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    if (j == i__ - *m) {
		i__3 = *m;
		for (l = 1; l <= i__3; ++l) {
		    if (l != i__ - *m) {
			delta[i__ + j * 42 - 43] += xx[i__ - *m + l * 20 - 21]
				 * 1.5 * k[i__ - *m + l * 20 - 21];
		    }
		}
	    } else {
		delta[i__ + j * 42 - 43] = xx[i__ - *m + j * 20 - 21] * -1.5 *
			 k[i__ - *m + j * 20 - 21];
	    }
	}
	i__2 = n - 2;
	for (j = *m + 1; j <= i__2; ++j) {
	    if (j - *m == i__ - *m) {
		i__3 = *m;
		for (l = 1; l <= i__3; ++l) {
		    if (l != i__ - *m) {
			delta[i__ + j * 42 - 43] -= y[i__ - *m + l * 20 - 21] 
				* k[i__ - *m + l * 20 - 21] * (xx[i__ - *m + 
				l * 20 - 21] * 1.6 + yy[i__ - *m + l * 20 - 
				21]);
		    }
		}
		delta[i__ + j * 42 - 43] -= k[i__ - *m + (i__ - *m) * 20 - 21]
			 * .8;
	    } else {
		delta[i__ + j * 42 - 43] = k[i__ - *m + (j - *m) * 20 - 21] * 
			2.7 * xx[i__ - *m + (j - *m) * 20 - 21] * y[i__ - *m 
			+ (j - *m) * 20 - 21];
	    }
	}
	delta[i__ + (n - 1) * 42 - 43] = 0.;
	delta[i__ + n * 42 - 43] = 0.;
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	delta[n - 1 + j * 42 - 43] = c__[j - 1] * z__[j];
    }
    i__1 = n;
    for (j = *m + 1; j <= i__1; ++j) {
	delta[n - 1 + j * 42 - 43] = 0.;
    }
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	delta[n + j * 42 - 43] = c__[j - 1] * a[j];
    }
    i__1 = n;
    for (j = *m + 1; j <= i__1; ++j) {
	delta[n + j * 42 - 43] = 0.;
    }
/*      WRITE(*,911)((DELTA(II,JJ),II=1,N),JJ=1,N),(C(JJ),JJ=1,M) */
/* 911  FORMAT(1P10E10.2) */
/* Inverse the system for each possible right-hand-side, i.e., */
/* if alpha is the r.h.s., we obtain the coefficient A_p */
/* if nu    ---------------------------------------- A_T */
/* if gamma(i,j) ----------------------------------- A_Cj */

/* If I=1, we obtain the hydrogen diffusion velocity */
/* If I=2, ------------- helium   ------------------ */
/* If I=3,M-1, --------- heavy element ------------- */
/* If I=M, ------------- electrons ----------------- */
/* For I=M,2M, we get the heat fluxes */
/* For I=N-1, we get the electric field */
/* For I=N, we get the gravitational force g */
    ludcmp_(delta, &n, &c__42, indx, &d__);
    lubksb_(delta, &n, &c__42, indx, alpha);
    lubksb_(delta, &n, &c__42, indx, nu);
    i__1 = n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ga[i__ - 1] = gamma[i__ + j * 42 - 43];
	}
	lubksb_(delta, &n, &c__42, indx, ga);
	i__2 = n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    gamma[i__ + j * 42 - 43] = ga[i__ - 1];
	}
    }
/* The results for the coefficients must be multiplied by p/K_0: */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	alpha[i__ - 1] = alpha[i__ - 1] * ko * ac * cc;
	nu[i__ - 1] = nu[i__ - 1] * ko * ac * cc;
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    gamma[i__ + j * 42 - 43] = gamma[i__ + j * 42 - 43] * ko * ac * 
		    cc;
	}
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ap[i__] = alpha[i__ - 1];
	at[i__] = nu[i__ - 1];
	i__2 = *m;
	for (j = 1; j <= i__2; ++j) {
	    ax[i__ + j * ax_dim1] = gamma[i__ + j * 42 - 43];
	}
    }
    return 0;
} /* thdiff_ */

