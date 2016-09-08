* Path, Component, Release: cmhv7sf/rel/HSPICE/models/esdfdi50.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *********************************************************************
*
*>  50V ESD N+/PWell Forward Diode
*
*
* *********************************************************************
.subckt esdfdi50 (a c sub) area=1 perimeter=1 w=1e-06 dtemp=0
.param
+ areaw = 'w*2.4e-6'
+ perimeterw = '2*(w+2.4e-6)'
*
* leakage current
+ lk10 = 25p
+ lk1a = 720.4u
+ lk1p = 1.567n
+ lkt  = 15
*
+ lk1  = '(lk10 + lk1a*areaw + lk1p*perimeterw)*pow((temper+273)/298,lkt)'

gleak     a c  cur='0.07*lk1*pwr(v(a,c),1)'
desdfdi50 a c diodeinsub area=areaw pj=0 dtemp=dtemp

.model diodeinsub d
+  level = 1
+  tlev  = 2
+  tref  = 25
+  eg    = 1.12
+  xti   = 5.0
+  gap1  = 473u
+  gap2  = 636
+  is    = 5.180e-06
+  n     = 1.020
+  nbv   = 4.780
+  ik    = 1.132e+06
+  rs    = rs_esdfdi50
+  cj    = cj_esdfdi50
+  vj    = 0.9620
+  m     = 0.5408
+  cjsw  = 0.0
+  php   = 1.0
+  mjsw  = 0.33
+  fc    = 0.50
+  bv    = bv_esdfdi50
+  tcv   = -0.00075
+  ibv   = 3.000e+02
+  expli = 1.000e+12
.ends esdfdi50
