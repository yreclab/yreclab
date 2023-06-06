/* convec.f -- translated by f2c (version 20100827).
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
    doublereal dpenv, alphac, alphae, alpham;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* CONVEC */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int convec_(doublereal *hcomp, doublereal *hd, doublereal *
	hp, doublereal *hr, doublereal *hs, doublereal *ht, logical *lc, 
	integer *m, integer *mrzone, integer *mxzone, integer *mxzon0, 
	integer *jcore, integer *jenv, integer *nrzone, integer *nzone, 
	integer *nzone0)
{
    /* Format strings */
    static char fmt_661[] = "(\002 -----TOO MANY MIX ZONES\002)";
    static char fmt_93[] = "(2x,\002CONVECTION ZONES MERGED DUE TO OVERSHOO"
	    "T\002/2x,\002OLD\002,2(\002[\002,i3,\002-\002,i3,\002]\002),\002"
	    " NEW\002,\002[\002,i3,\002-\002,i3,\002]\002)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, i1, k1, j2;
    static logical lcc;
    extern /* Subroutine */ int oversh_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_661, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_93, 0 };


/* CONVEC DETERMINES THE BOUNDARIES OF CONVECTIVE REGIONS WITH AND */
/*    WITHOUT OVERSHOOT. */
/* *IMPORTANT NOTE* */
/* IN THE EVOLUTION CODE, OVERSHOOT IS ASSUMED TO BE OVERMIXING : */
/*    SHELLS IN THE OVERSHOOT REGION ARE MIXED WITH THE ADJACENT CONVECTION */
/*    ZONE, BUT STILL USE THE RADIATIVE TEMPERATURE GRADIENT. */

/* INPUT VARIABLES : */

/* HCOMP,HD,HP,HR,HS,HT : MASS FRACTIONS OF SPECIES, AND RUN OF */
/*    DENSITY,PRESSURE,RADIUS, MASS, AND TEMPERATURE RESPECTIVELY. */
/*    USED TO DETERMINE THE EXTENT OF OVERSHOOT REGIONS. */
/* LC : FLAG THAT IS T IF A SHELL IS CONVECTIVE AND F IF IT IS RADIATIVE. */
/* LOVSTC,LOVSTE,LOVSTM : FLAGS SET T IF OVERSHOOT IS TO BE COMPUTED FOR */
/*    CENTRAL, SURFACE, AND INTERMEDIATE CONVECTION ZONES RESPECTIVELY. */
/* M : NUMBER OF SHELLS IN THE MODEL. */

/* OUTPUT VARIABLES : */

/* JCORE, JENV : IDS OF THE EDGES OF THE SURFACE AND CENTRAL CONVECTION */
/*    ZONES RESPECTIVELY. JCORE=1 AND JENV=M IF THE ZONES IN QUESTION */
/*    DON'T EXIST. */
/* MXZON0,MXZONE : ARRAYS GIVING THE STARTING AND ENDING SHELLS IN MIXED */
/*    REGIONS.  MXZON0 REFERS TO THE BOUNDARIES WITHOUT OVERSHOOT, AND */
/*    MXZONE REFERS TO THE BOUNDARIES WITH OVERSHOOT.  THE ZONES ARE STORED */
/*    IN PAIRS, I.E. ELEMENTS (3,1) AND (3,2) ARE THE FIRST AND LAST */
/*    MIXED SHELLS IN THE THIRD CONVECTION ZONE OUT FROM THE CENTER. */
/* NZONE,NZONE0 : NUMBER OF DISTINCT MIXED REGIONS WITH AND WITHOUT */
/*    OVERSHOOT.  THEY CAN BE DIFFERENT BECAUSE OVERSHOOT CAN CAUSE TWO */
/*    NEARBY CONVECTION ZONES TO MERGE. */
/* MRZONE,NRZONE : THE LOCATIONS OF RADIATIVE REGIONS AND THE NUMBER OF */
/*    CONTIGUOUS RADIATIVE REGIONS.  NEEDED BECAUSE MIX TREATS BURNING */
/*    IN RADIATIVE AND CONVECTIVE REGIONS DIFFERENTLY.  THESE ARE DEFINED IN */
/*    THE SAME WAY AS THE ANALOGOUS CONVECTIVE VARIABLES. */

/* LOCATE BOUNDARIES OF STANDARD CONVECTION ZONES */
    /* Parameter adjustments */
    mxzon0 -= 13;
    mxzone -= 13;
    mrzone -= 14;
    --lc;
    --ht;
    --hs;
    --hr;
    --hp;
    --hd;
    hcomp -= 16;

    /* Function Body */
    j = 1;
    lcc = FALSE_;
    lc[*m + 1] = FALSE_;
    i__1 = *m + 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (! lc[i__]) {
	    goto L10;
	}
/* CONVECTION ZONE */
	if (lcc) {
	    goto L11;
	}
/* START OF CONVECTION ZONE */
	lcc = TRUE_;
	i1 = i__;
	goto L11;
L10:
	if (! lcc) {
	    goto L11;
	}
/*   END OF CONVECTION ZONE */
	lcc = FALSE_;
	if (i1 != i__ - 1) {
	    mxzone[j + 12] = i1;
	    mxzone[j + 24] = i__ - 1;
	    ++j;
	}
	if (j < 12) {
	    goto L11;
	}
	io___5.ciunit = luout_1.ishort;
	s_wsfe(&io___5);
	e_wsfe();
	goto L12;
L11:
	;
    }
L12:
/* MHP 5/91 LOGIC CHANGE TO AVOID PROBLEMS IF NO CZ IN MODEL(NZONE=0) */
/* SKIP REST OF SR IF THERE ARE NO CONVECTION ZONES. */
    if (j == 1) {
	*jcore = 1;
	*jenv = *m;
	*nzone0 = 0;
	*nzone = 0;
	*nrzone = 1;
	mrzone[14] = 1;
	mrzone[27] = *m;
	goto L9999;
    }
    *nzone = j - 1;
    i__1 = *nzone;
    for (i__ = 1; i__ <= i__1; ++i__) {
	mxzon0[i__ + 12] = mxzone[i__ + 12];
	mxzon0[i__ + 24] = mxzone[i__ + 24];
/* L20: */
    }
    *nzone0 = *nzone;
/* FIND OUTER EDGE OF THE CONVECTIVE CORE (JCORE) AND INNER EDGE OF THE */
/* CONVECTIVE ENVELOPE (JENV) BEFORE OVERSHOOT. */
    if (mxzone[13] == 1) {
/* CENTRAL CONVECTION ZONE EXISTS IF TRUE. */
	if (mxzone[25] == *m) {
/* FULLY CONVECTIVE STAR IF TRUE. */
	    *jcore = 1;
	    *jenv = 1;
	    *nrzone = 0;
	    goto L9999;
	} else {
	    *jcore = mxzone[25];
	}
    } else {
	*jcore = 1;
    }
    if (mxzone[*nzone + 24] == *m) {
/* SURFACE CONVECTION ZONE EXISTS IF TRUE. */
	*jenv = mxzone[*nzone + 12];
    } else {
	*jenv = *m;
    }
/*  ADD CONVECTIVE OVERSHOOT IF NEEDED; THE SIZE OF THE OVERSHOOT REGION IS */
/*  COMPUTED AND THE EDGES IN MXZONE ARE MOVED TO THE EDGES OF THE */
/*  OVERSHOOT REGIONS. */
    if (! dpmix_1.lovstc && ! dpmix_1.lovste && ! dpmix_1.lovstm) {
	goto L100;
    }
    oversh_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], m, &mxzone[13]
	    , &mxzon0[13], nzone);
/*  CHECK FOR MERGERS OF NEARBY CONVECTION ZONES CAUSED BY OVERSHOOT. */
    if (*nzone == 1) {
	goto L100;
    }
    j = 1;
L85:
/*  CHECK IF 'TOP' OF ONE REGION IS ABOVE 'BOTTOM' OF THE NEXT ONE. */
    if (mxzone[j + 24] >= mxzone[j + 13]) {
/*  IF THIS OCCURS, TWO CONVECTION ZONES HAVE MERGED. */
	io___6.ciunit = luout_1.ishort;
	s_wsfe(&io___6);
	i__1 = j + 1;
	for (k = j; k <= i__1; ++k) {
	    for (k1 = 1; k1 <= 2; ++k1) {
		do_fio(&c__1, (char *)&mxzone[k + k1 * 12], (ftnlen)sizeof(
			integer));
	    }
	}
	do_fio(&c__1, (char *)&mxzone[j + 12], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&mxzone[j + 25], (ftnlen)sizeof(integer));
	e_wsfe();
	mxzone[j + 13] = mxzone[j + 12];
	i__1 = *nzone - 1;
	for (k = j; k <= i__1; ++k) {
	    for (j2 = 1; j2 <= 2; ++j2) {
		mxzone[k + j2 * 12] = mxzone[k + 1 + j2 * 12];
/* L95: */
	    }
/* L90: */
	}
	--(*nzone);
	if (j <= *nzone - 1) {
	    goto L85;
	} else {
	    goto L100;
	}
    }
    ++j;
    if (j <= *nzone - 1) {
	goto L85;
    }
L100:
/* NOW DETERMINE THE NUMBER OF RADIATIVE REGIONS. */
/* CHECK FOR A RADIATIVE REGION BELOW THE FIRST CONVECTION ZONE. */
    if (mxzone[13] > 1) {
	*nrzone = 1;
	mrzone[14] = 1;
	mrzone[27] = mxzone[13] - 1;
    } else {
	*nrzone = 0;
    }
/* LOCATE ALL RADIATIVE REGIONS BETWEEN CONVECTION ZONES. */
    if (*nzone > 1) {
	i__1 = *nzone - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ++(*nrzone);
	    mrzone[*nrzone + 13] = mxzone[i__ + 24] + 1;
	    mrzone[*nrzone + 26] = mxzone[i__ + 13] - 1;
/* L110: */
	}
    }
/* CHECK FOR A RADIATIVE REGION ABOVE THE LAST CONVECTION ZONE. */
    if (mxzone[*nzone + 24] < *m) {
	++(*nrzone);
	mrzone[*nrzone + 13] = mxzone[*nzone + 24] + 1;
	mrzone[27] = *m;
    }
L9999:
    return 0;
} /* convec_ */

