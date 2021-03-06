* Path, Component, Release: cmos7base/rel/HSPICE/models/diodenx.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  diodenx    N+ to Substrate Junction Diode
*
***********************************************************************
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines junction parasitic capacitance
*  per node.
*
*                  o  n+ (nd)
*                  |------------+
*                  |            |
*                ----          / \
*                 /\   Dnsx   /   \ Gleak
*                /  \         \   /  Diode includes junction capacitance
*                ----          \ /   and forward bias current parameters.
*                  |            |
*                  |------------+
*                  o  substrate (sx)
*
***********************************************************************
*
*  SYNTAX:     Specify both area and perimeter:
*              xxx  1 sx  diodenx (area=1p  perim=4u)
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
.subckt diodenx  nd sx  area=1p  perim=4u  dtemp=0

dnsa  sx nd  dnsx  area=area  pj=perim  dtemp=dtemp
gleak nd sx  cur='2e-4*(sinh(0.5*v(nd,sx))*area)'

* N+ to SX Diode
*
.model dnsx d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+    js = js_n
+   jsw = jsw_n
+     n = n_n
+    cj = cj_n
+    pb = pb_n
+    mj = mj_n
+   cjp = cjsw_n
+   php = pbsw_n
+  mjsw = mjsw_n
+   cta = cta_n
+   tpb = pta_n
+   ctp = ctp_n
+  tphp = ptp_n
+    vb = '15.0*(esd_event == 0) + 100*(esd_event != 0)'

.ends diodenx
