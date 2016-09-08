* Path, Component, Release: cmos7base/rel/HSPICE/models/mosvarm.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  mosvarm   Triple Gate (5.0V) nMOS Varactor
*
*******************************************************************************
*
*  Syntax:  xxx (g sd sx) mosvarm
*            +     l = 2u    <- length (m)
*            +     w = 2u    <- width  (m)
*            +  xrep = 1     <- number of gates per individual RX diffusion
*            +  yrep = 1     <- number of individual RX diffusion shapes
*            + dtemp = 0     <- temp rise from ambient (deg C)
*            +   rsx = 50    <- Substrate resistance
*
*                            .--------------------.
*                            |                    |
*                            |<-------- l-------->|
*                            |                    |
*                       .----|--------------------|-----.
*                       |    |          ^         |     | RX
*                       |  s |          |         |  d  |
*                       |    |          w         |     |
*                       |    |          |         |     |
*                       |    |          v         |     |
*                        ----|--------------------|-----
*                            |                    |
*                            |          PC        |
*                            |                    |
*                             --------------------
*
* NOTES:
*
*  1. Model assumes source and drain are shorted and dual side PC
*     contacts are shorted.
*
* 
*                    (g)           rtop          
*                     o-----------/\/\/\----(g1)
*                                             |
*                                             /
*                                        rpc  \
*                                             /
*                                             |
*                                      +-----(1)
*                                      |      |
*                                      |      |
*                                      |  ca  = 
*                                      |      |
*                                      |      |
*                                      |    (11)
*                                      |      |
*                                  cf  =      |
*                                      |      |
*                                      |      /
*                                      | rrx  \
*                                      |      /
*                                      |      |
*                                      |      |
*                                      +----(s1)--/\/\/\------------o (sd)
*                                             |    rbot
*                                             |
*                                           - - -
*                                            / \
*                                        dcx - -
*                                             |
*                                             |
*                                        (sx) o (substrate)
*
*
*  These models were developed using the Spectre (TM) circuit simulator.
*
*
********************************************************************************
.subckt mosvarm (g sd sx)  l=2 w=2 xrep=1 yrep=1 dtemp=0 rsx=50 
*
*---- Drawn Geometry ----------------------------------------------
+ pl = 'max(l,0.6u)'
+ pw = 'max(w,0.5u)'
*
*---- Drawn Geometry + Mask Bias ----------------------------------
+ plf  = 'pl + lwbpc'
+ pwf  = 'pw + delrx'
*
*---- Area/Perimeter Calculations ---------------------------------
*  Device values
+ ngdiff   = 'max(1,xrep)'
+ ndiff    = 'max(1,yrep)'
+ par      = 'ngdiff*ndiff'
+ pareac   = 'plf * pwf * par'
*  Nwell values
+ lnw      = '(2 * 2.6u) + ((ngdiff-1) * 0.80u) + (ngdiff * pl)'
+ wnw      = '(2 * 2.6u) + ((ndiff-1)  * 1.20u) + (ndiff * pw)'
+ areanw   = 'lnw * wnw'
+ perimnw  = '2 * (lnw + wnw)'
*---- RX and PC Fringe cap ----------------------------------------
+ prxfrng = 0.20n
+ pcapof  = 0.14n
+ pmetf   = 0.20f
+ pcof    = 'par * (2 * pwf * pcapof + 2 * plf * prxfrng + pmetf)'
*---- Main area Capacitance ---------------------------------------
*    Calculated in Verilog-A component mosvarcap
*---- NW resistance -----------------------------------------------
+ prnw   = '(0.9 * nwrs) * (0.5 * plf + 0.80u) / (6 * pwf) + (0.5 * 250p) / (2 * 0.80u * pwf)'
*---- Gate resistance ---------------------------------------------
+ prgate = 'pcrsi * pwf / (12 * plf) + (exp(oppcrenf)-97) * 0.62p / (pwf * plf)'
*
*---- Metal line resistances ----------------------
*     value below is M1 sheet resistance and thickness
*     Gates (with W = 0.60 um)
+ prtop = '(m1rsi / .60u) * (plf + .80u) * ngdiff / 3'
*     Source/Drains 
+ prbot = 'm1rs * (plf + 0.80u) * ngdiff / (3*(pwf/2-0.02u))'
*
*  Subcircuit
rtop  g  g1  r='prtop/(ndiff+1)' dtemp=dtemp tc1=tm1rs 
rpc  g1   1  r='prgate / par'    dtemp=dtemp tc1=tpcrsi 
xca   1  11  mosvarcap
+    pl_va = plf 
+    pw_va = pwf 
+   pnf_va = par 
+    co_va = co_mv50 
+    qs_va = 'qs_mv50 + 20p/plf'
+    qp_va = qp_mv50
+   pon_va = '2m + 1.0n/plf'
+   vbi_va = 0.05
+   cot_va = 0.1m
+  pont_va = 0m
+  vbit_va = 0.5m
+  deltemp = 'temper+dtemp-25'
rrx  11  s1  r='prnw / par'  dtemp=dtemp tc1=tnwrs 
rbot s1  sd  r='prbot/ndiff' dtemp=dtemp tc1=tm1rs 
* 
cfr   1  s1  c=pcof
* 
dsx  sx  s1  nwsxd  area=areanw pj=perimnw dtemp=dtemp
*
*---- NWell-to-Sub Diode ---------------------------------------
.model nwsxd d
+ level = 1
+  dcap = 2
+  tlev = 2
+ tlevc = 1
+  tref = 25
+    eg = 1.12
+   xti = 3.0
+  gap1 = 473u
+  gap2 = 636
+    rs = 'rsx*areanw'
+     n = 1.023
+    js = 1.037u
+   jsw = 2.873p
+    cj = 0.18m
+    pb = 4.0
+     m = 1.2
+   cjp = 0.4n
+   php = 0.1
+  mjsw = 1.2 
+    vb = 15
* 
.ends mosvarm
