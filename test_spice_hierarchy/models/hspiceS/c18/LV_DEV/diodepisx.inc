* Path, Component, Release: cmos7base/rel/HSPICE/models/diodepisx.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*> 7RF/7WL  diodepisx  N-isolation (PI) to Sub (SX) Junction Diode
*
***********************************************************************
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines junction parasitic capacitance
*  per node.
*
*                  o  n-iso (ni)
*                  |------------+
*                  |            |
*                ----          / \
*                 /\  Dpisx   /   \ Gleak
*                /  \         \   /  Diode includes junction capacitance
*                ----          \ /   and forward bias current parameters.
*                  |            |
*                  |------------+
*                  o  substrate (sx)
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter:
*              xxx  sx ni  diodepisx (area=100p  perim=40u)
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
.subckt diodepisx  sx ni  area=1p  perim=1u   dtemp=0
*
.param
dpn   s  ni dpisx area=area  pj=perim  dtemp=dtemp
rsx   sx s  r='500p/area'
gleak ni sx cur='5e-2*(sinh(0.001*v(ni,sx))*area) + 11e-8*(sinh(0.005*v(ni,sx))*perim)'

* N-isolation to SX Diode
*
.model dpisx d (
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+    js = js_pix
+   jsw = jsw_pix
+     n = n_pix
+    cj = cj_pix
+    pb = pb_pix
+    mj = mj_pix
+  cjsw = cjsw_pix
+   php = pbsw_pix
+  mjsw = mjsw_pix
+   cta = cta_pix
+   tpb = pta_pix
+   ctp = ctp_pix
+  tphp = ptp_pix
+    vb = 10.0 )

.ends diodepisx
