C*  COMMON /GWC1/ KF(10),UF(13,76),KX(10),UX(13,76)                    *
C*     KF     IV  HEADER RECORD VALUES FOR FOF2 COEFFICIENTS IN URSI   *
C*     UF     RA  FOURIER SERIES COEFFICIENTS FOR FOF2 IN URSI         *
C*     UF0    RA  FOURIER SERIES COEFFICIENTS FOR FOF2 AT SSN=0        *
C*     UF100  RA  FOURIER SERIES COEFFICIENTS FOR FOF2 AT SSN = 100    *
C*     KX     IV  HEADER RECORD VALUES FOR M3000 COEFFICIENTS IN URSI  *
C*     UX     RA  FOURIER SERIES COEFFICIENTS FOR M3000 IN URSI        *
C*                                                                     *
      INTEGER KF(10),KX(10)
      REAL UF(13,76),UX(13,76),UF100(13,76),UF0(13,76),FM3(9,49,2)
      COMMON/GWC1/KF,UF,KX,UX,UF0,UF100,FM3
C
C
C
C
