* Path, Component, Release: cmhv7sf/rel/HSPICE/models/diodendpw.inc, 7hv_models, pcad_7hv_V121x
* CMVC Revision: 1.3 12/12/04 08:03:55
*
* *********************************************************************
*
*>  IBM CMHV7SF	 HV ND/PW Parasitic Diode
*
* IBM CONFIDENTIAL
* (C) 2012 IBM Corporation
*
* Licensed Materials - Property of IBM
* US Government Users Restricted Rights - Use, duplication or disclosure
* restricted by GSA ADP Schedule contract with IBM Corporation.
*
* *********************************************************************
.subckt	 diodendpw (a c) area=1p perimeter=1u dtemp=0

ddiodendpw a c diodeinsub area=area pj=perimeter dtemp=dtemp
gleak  c a  cur='lka_ndpw*(sinh(vlka_ndpw*v(c,a))*area) + lkp_ndpw*(sinh(vlkp_ndpw*v(c,a))*perimeter)'

.model diodeinsub d
+  level = 1
+  tlev  = 2
+  tref  = 25
+  eg    = 1.12
+  xti   = 3.0
+  gap1  = 473u
+  gap2  = 636
+  js    = js_ndpw
+  jsw   = jsw_ndpw
+  n     = n_ndpw
+  cj    = cj_diodendpw
+  cjsw  = cjsw_diodendpw
+  m     = 0.3652
+  mjsw  = 0.3652
+  vj    = 0.4463
+  php   = 0.4463
+  tt    = 0.0
+  fc    = 0.0
+  af    = 1.0
+  kf    = 0.0
+  vb    = 9.0
.ends diodendpw
