* Path, Component, Release: cmhv7sf/rel/HSPICE/models/esdtdi25.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *********************************************************************
*
*>  25V ESD Trigger Diode
*
*
* *********************************************************************
.subckt	esdtdi25 (a c sub) area=1 perimeter=1 w=1e-06 dtemp=0
.param
+ areaw = 'w*2.4e-6'
+ perimeterw = '2*(w+2.4e-6)'
*
* leakage current
+ lk10 = 125p
+ lk1a = 720.4u
+ lk1p = 1.567n
+ lkt  = 10
*
+ lk1  = '(lk10 + lk1a*areaw + lk1p*perimeterw)*pow((temper+273)/298,lkt)'

gleak     a c  cur='0.1*lk1*pwr(v(a,c),1)'
desdtdi25 a c diodeinsub area=areaw pj=0 dtemp=dtemp

.model diodeinsub d
+  level = 1
+  tlev  = 2
+  tref  = 25
+  eg    = 1.12
+  xti   = 5.0
+  gap1  = 473u
+  gap2  = 636
+  is    = 20u
+  n     = 1.034
+  nbv   = 3.0
+  ik    = 2.004e+06
+  rs    = rs_esdtdi25
+  cj    = cj_esdtdi25
+  vj    = 0.8745
+  m     = 0.4638
+  cjsw  = 0.0
+  php   = 1.0
+  mjsw  = 0.33
+  fc    = 0.50
+  bv    = bv_esdtdi25
+  tcv   = -0.0018
+  ibv   = 1.500e+02
+  expli = 1.000e+12
.ends esdtdi25
