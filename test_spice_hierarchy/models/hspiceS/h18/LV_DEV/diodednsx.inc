* Path, Component, Release: cmhv7sf/rel/HSPICE/models/diodednsx.inc, 7hv_models, pcad_7hv_V121x
* CMVC Revision: 1.4 12/12/04 08:03:48
*
* *********************************************************************
*
*>  IBM CMHV7SF	 HV DN/SX Parasitic Diode
*
* IBM CONFIDENTIAL
* (C) 2012 IBM Corporation
*
* Licensed Materials - Property of IBM
* US Government Users Restricted Rights - Use, duplication or disclosure
* restricted by GSA ADP Schedule contract with IBM Corporation.
*
* *********************************************************************
.subckt	 diodednsx (a c) area=1p perimeter=1u dtemp=0 vdnsx=50

ddiodednsx a c diodeinsub area=area pj=perimeter dtemp=dtemp
gleak  c a  cur='lka_dnsx*(sinh(vlka_dnsx*v(c,a))*area) + lkp_dnsx*(sinh(vlkp_dnsx*v(c,a))*perimeter)'

.model diodeinsub d
+  level = 1
+  tlev  = 2
+  tref  = 25
+  eg    = 1.12
+  xti   = 3.0
+  gap1  = 473u
+  gap2  = 636
+  js    = js_dnsx
+  jsw   = jsw_dnsx
+  n     = n_dnsx
+  cj    = cj_diodednsx
+  cjsw  = cjsw_diodednsx
+  m     = 0.410
+  mjsw  = 0.310
+  vj    = 0.450
+  php   = 0.550
+  tt    = 0.0
+  fc    = 0.0
+  af    = 1.0
+  kf    = 0.0
+  vb    = vdnsx
.ends diodednsx
