* Path, Component, Release: cmhv7sf/rel/HSPICE/models/diodepnw.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
*>  diodepnw   P+ Diffusion to Nwell Junction Diode
*
***********************************************************************
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines junction parasitic capacitance
*  per node.
*
*                  o  p+ (pd)
*                  |
*                  |
*                ----
*                \  /   Dpnw
*                 \/          Diode includes junction capacitance
*                ----         and forward bias current parameters.
*                  |
*                  |
*                  o  n well (nw)
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter:
*              xxx  pd nw  diodepnw (area=1p  perim=4u)
*
*
*  NOTES:
*
*  1. Node order must be as specified.
*
*  2. Units for input parameters are meters**2 (area), meters (perim).
*
*
*                                
***********************************************************************
*
.subckt diodepnw  (pd  nw) area=1p  perim=4u  res=0  dtemp=0

dpda   pd  nw  dpnw  area=area  pj=perim  dtemp=dtemp

* P+ to Nwell Diode
*
.model dpnw d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+     n = n_p
+    js = js_p
+   jsw = jsw_p
+    rs = res
+    cj = cj_p
+    pb = pb_p
+    mj = mj_p
+   cjp = cjsw_p
+   php = pbsw_p
+  mjsw = mjsw_p
+   cta = cta_p
+   tpb = pta_p
+   ctp = ctp_p
+  tphp = ptp_p
+    vb = 10.5

.ends diodepnw
