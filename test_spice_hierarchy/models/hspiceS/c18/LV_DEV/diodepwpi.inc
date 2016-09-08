* Path, Component, Release: cmos7base/rel/HSPICE/models/diodepwpi.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*> 7RF/7WL  diodepwpi  Pwell to N-isolation (PI) Junction Diode
*
***********************************************************************
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines junction parasitic capacitance
*  per node.
*
*                  o  pwell (1)
*                  |
*                  |
*                ----
*                \  /  Dpwpi
*                 \/          Diode includes junction capacitance,
*                ----         resistance and sat current parameters.
*                  |
*                  |
*                  o   n-iso (ni)
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter:
*              xxx  1 ni  diodepwp1 (area=100p  perim=40u)
*
*
*  NOTES:
*
*  1. Node order must be as specified.
*
*  2. Units for input parameters are meters**2 (area) and meters (perim).
*
*
*
***********************************************************************
* 
.SUBCKT diodepwpi  1 ni  area=1p  perim=1u   dtemp=0
*
dpn   n  ni  dpwpi area=area  pj=perim  dtemp=dtemp
rpw   1  n   r='500p/area'

* P well to N-isolation Diode
*
.model dpwpi d (
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+    js = js_pwi
+   jsw = jsw_pwi
+     n = n_pwi
+    cj = cj_pwi
+    pb = pb_pwi
+    mj = mj_pwi
+  cjsw = cjsw_pwi
+   php = pbsw_pwi
+  mjsw = mjsw_pwi
+   cta = cta_pwi
+   tpb = pta_pwi
+   ctp = ctp_pwi
+  tphp = ptp_pwi
+    vb = 10.0 )

.ENDS diodepwpi
