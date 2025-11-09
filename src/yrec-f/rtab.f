C------------------------    GROUP: SR_ALL   -------------------------------
C
C
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
C RTAB
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
      SUBROUTINE RTAB(IR,NTM,NRM,IVAR,NT,NR,TL,TDVAR)
      IMPLICIT REAL*8 (A-H,O-Z)
      IMPLICIT LOGICAL*4(L)

C     NT IS INPUT; NR,TL,TDVAR ARE OUTPUT
      DIMENSION TL(NTM),TDVAR(NTM,NRM,IVAR)
      COMMON/CCOUT2/LDEBUG,LCORR,LMILNE,LTRACK,LSTPCH
      SAVE
      DO 10 N = 1, NT
C     READ(IR,1001) NRR,TL(N)
      READ(IR     ) NRR,TL(N)
      IF(N.EQ.1) NR=NRR
C     CHECK LIMITS AND NUMBER OF DENSITIY POINTS OF TABLE
      IF ( NT.GT.NTM .OR.  NR.GT.NRM ) THEN
         STOP
      END IF
      IF ( N.GT.1 .AND. NRR.NE.NR ) THEN
         STOP
      END IF
C     END CHECK ....................................................
C KC 2025-05-30 fixed "Shared DO termination label"
C       DO 10 J = 1, NR
      DO 11 J = 1, NR
C     READ(IR,1002) (TDVAR(N,J,IV),IV=1,IVAR)
      READ(IR     ) (TDVAR(N,J,IV),IV=1,IVAR)
11    CONTINUE
10    CONTINUE
      RETURN
C 1001  FORMAT(I5,E16.8)
C 1002  FORMAT(5E16.8)
C 1011  FORMAT(I5,1PE16.8)
C 1012  FORMAT(1P5E16.8)
C 9001  FORMAT(' ERROR IN RTAB. TOO SMALL PARAMETERS: ',
C      1 /' NT,NR,NTM,NRM = ',4I5)
C 9011  FORMAT(' ERROR IN RTAB. WRONG DENSITY CONSTRUCTION: ',
C      1 /' N,NR,NRR = ',3I5)
      END
