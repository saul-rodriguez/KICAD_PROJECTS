* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pcapim.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  pcapim   pMOS Varactor (Thick oxide)
*
*******************************************************************************
*
*  Syntax:  xxx (g sd dn) pcapim
*            +     l = 2u    <- length (m)
*            +     w = 2u    <- width  (m)
*            +  xrep = 1     <- number of gates per individual RX diffusion
*            +  yrep = 1     <- number of individual RX diffusion shapes
*            + dtemp = 0     <- temp rise from ambient (deg C)
*            +   rsx = 50    <- Substrate resistance
*            + vdnsx = 50    <- DN/SX max voltage option (50V or 120V)
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
*                                       dpdn - -
*                                             |
*                                             |
*                                        (dn) o (DN&NW)
*
*
********************************************************************************
.subckt pcapim (g sd dn)  l=2u w=2u xrep=1 yrep=1 dtemp=0 rsx=50 vdnsx=50
*
*---- Drawn Geometry ----------------------------------------------
+ pl = 'max(l,0.18u)'
+ pw = 'max(w,0.4u)'
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
+ pareac   = '(plf-0.0u) * pwf * par'
+ pedgec   = '0.0u * pwf * par'
*  Pwell values
+ lpw      = '(2 * 1.82u) + ((ngdiff-1) * 0.80u) + (ngdiff * pl)'
+ wpw      = '(2 * 2.56u) + ((ndiff-1) * 1.20u) + (ndiff * pw)'
+ areapw   = 'lpw * wpw'
+ perimpw  = '2 * (lpw + wpw)'
*---- RX and PC Fringe cap ----------------------------------------
+ prxfrng = 0.18n
+ pcapof  = 0.12n
+ pmetf   = 0.22f
+ pcof    = 'par * (2 * pwf * pcapof + 2 * plf * prxfrng + pmetf)'
*---- PW resistance -----------------------------------------------
+ prpw   = '0.9 * pwirs  * (plf + 2*0.8u) / (12 * pwf) + prvpw / (2 * 0.8u * pwf)'
*---- Gate resistance ---------------------------------------------
+ prgate = 'pcrsi * pwf / (12 * plf) + 20p / (pwf * plf)'
*
*---- Metal line resistances ----------------------
*     value below is M1 sheet resistance and thickness
*     Gates (with W = 0.60 um), delm1 is image bias
+ prtop = '(m1rsi / (.60u+delm1)) * (plf + .80u) * ngdiff / 3'
*     Source/Drain 
+ prbot = 'm1rs * (plf + 0.80u) * ngdiff / (3*pwf/2)'
*
*  Subcircuit
rtop  g  g1  r='prtop/(ndiff+1)'  dtemp=dtemp tc1=tm1rs 
rpc  g1   1  r='prgate / par'  dtemp=dtemp tc1=tpcrsi 
xca   1  s1  pvarcap
+    pareac = pareac
+    co_pva = 'co_tpmv + 50p/pl - 50p/pw'
+   cot_pva = 0.1m
+    qs_pva = 'qs_tpmv+50p/pl'
+    qp_pva =  qp_tpmv
+   vbi_pva = '-.055u/pl + 0.07u/pw'
+  vbit_pva = -0.7m
+   pon_pva = '-1.33m +1.33n/pl'
+   deltemp = 'temper+dtemp-25'
+   wellres = 'prpw*(1 + tnwrs*(temper+dtemp-25))/par'
+    accres = 2.0
+    depres = 1.53
rbot s1  sd  r='prbot/ndiff'  dtemp=dtemp tc1=tm1rs 
* 
cfr   1  s1  c=pcof
* 
xdpdn s1 dn  diodepwdn  area=areapw  perimeter=perimpw
*
.ends pcapim
