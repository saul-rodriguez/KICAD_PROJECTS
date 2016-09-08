* Path, Component, Release: cmrf7sf/rel/HSPICE/models/diodenwx.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
*
*>  CMRF7SF  diodenwx   Nwell to Substrate Junction Diode
*
***********************************************************************
*
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines junction parasitic capacitance
*  per node.
*
*                  o  nwell (nw)
*                  |------------+
*                  |            |
*                ----          / \
*                 /\   Dnwx   /   \ Gleak
*                /  \         \   /  Diode includes junction capacitance
*                ----          \ /   and forward bias current parameters.
*                  |            |
*                  |------------+
*                  o  substrate (sx)
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter:
*              xxx  nw sx  diodenwx (area=1p  perim=4u)
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
.subckt diodenwx  nw sx  area=1p  perim=4u  dtemp=0

dnwa   sx  nw  dnwx  area=area  pj=perim  dtemp=dtemp
gleak  nw  sx  cur='5e-5*(sinh(0.5*v(nw,sx))*area)'

* NW to SX Diode
*
.model dnwx d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.15
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+     n = n_nw
+    js = js_nw
+   jsw = jsw_nw
+    cj = cj_nw
+    pb = pb_nw
+    mj = mj_nw
+   cjp = cjsw_nw
+   php = pbsw_nw
+  mjsw = mjsw_nw
+   cta = cta_nw
+   tpb = pta_nw
+   ctp = ctp_nw
+  tphp = ptp_nw
+    vb = 10.0

.ends diodenwx
