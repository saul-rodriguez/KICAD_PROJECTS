* Path, Component, Release: cmhv7sf/rel/HSPICE/models/diodepwdn.inc, 7hv_models, pcad_7hv_V121x
* CMVC Revision: 1.3 12/12/04 08:04:02
*
* *********************************************************************
*
*>  IBM CMHV7SF	 HV PW/DN Parasitic Diode
*
* IBM CONFIDENTIAL
* (C) 2012 IBM Corporation
*
* Licensed Materials - Property of IBM
* US Government Users Restricted Rights - Use, duplication or disclosure
* restricted by GSA ADP Schedule contract with IBM Corporation.
*
* *********************************************************************
.subckt	 diodepwdn (a c) area=1p perimeter=1u dtemp=0

ddiodepwdn a c diodeinsub area=area pj=perimeter dtemp=dtemp
gleak  c a  cur='lka_pwdn*(sinh(vlka_pwdn*v(c,a))*area) + lkp_pwdn*(sinh(vlkp_pwdn*v(c,a))*perimeter)'

.model diodeinsub d
+  level = 1
+  tlev  = 2
+  tref  = 25
+  eg    = 1.12
+  xti   = 3.0
+  gap1  = 473u
+  gap2  = 636
+  js    = js_pwdn
+  jsw   = jsw_pwdn
+  n     = n_pwdn
+  cj    = cj_diodepwdn
+  cjsw  = cjsw_diodepwdn
+  m     = 0.5358
+  mjsw  = 0.2701
+  vj    = 0.9706
+  php   = 0.5449
+  tt    = 0.0
+  fc    = 0.0
+  af    = 1.0
+  kf    = 0.0
+  vb    = 11.5
.ends diodepwdn
