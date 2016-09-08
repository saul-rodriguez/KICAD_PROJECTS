* Path, Component, Release: cmhv7sf/rel/HSPICE/models/sbdi.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
*>  sbdi          Schottky Barrier Diode
*
*******************************************************************************
*
*  SYNTAX:  Specify anode width, length, and # anodes
*
*           xxx ( a c s ) sbdi     <- Default:  5.0u x 5.0u anode
*            +         w = 5.0u    <- Drawn anode width  (anode only)
*            +         l = 5.0u    <-   "     "   length      "
*            +        nf = 1       <- # anode stripes
*            +       rsx = 50      <- Substrate resistance
*            +         m = 1       <- Device implicit multiplicity
*	     +       par = 1       <- Explicit device multiplicity.
*            +     dtemp = 0       <- Device temperature difference with respect to
*                                     the simulated circuit temperature (deg C).
*            +     vdnsx = 50      <- DN/SX max voltage option (50V or 120V)
*
* NOTES:
*
*  1. Each Anode has a wrap-around cathode.
*
* SUBCIRCUIT SCHEMATIC:
*
*               gleak
*                / \
*            +--/   \---+
*            |  \   /   |
*            |   \ /    |
*            |          |
*            |   |\ |   |
*            +---| >|---+            ci              bot              c
*            |   |/ |   +-------------+--\/\/\-------+-------\/\/\----0 
* a       top|   dsbd                 |   rcov                rmc
* O-\/\/\----+                        |                       
*    rma     |                        |                      
*            |                        |
*            +--------------O         |
*                           |         |                 
*                           |         |      
*                            \ |      |         
*                             \|      |  
*                              |------O      
*                             /|                       
*                            / |qgr                
*                           |               
*                           |
*                           O s
*
*
********************************************************************************
.subckt sbdi a c s
*--- Default Geometry = 5.0u x 5.0u anode, wrap-around cathode
+         w = 5.0u                             $ Anode design width 
+         l = 5.0u                             $ Anode design length
+        nf = 1                                $ # of Anode stripes
+       rsx = 50                               $ Substrate resistance
+       par = 1                                $ Explicit Multiplicity
+     dtemp = 0                                $ Device Temp rise from ambient
+     vdnsx = 50                               $ DN/SX max voltage option
*
.param
*---- Drawn Geometry ----------------------------------------------------------
+   nspaces = 'nf - 1'
+       rxw = 'w + 1.20u'                      $ Anode rx design width
+       rxl = 'l + 1.20u'                      $ Anode rx design length
+       rnw = 0.60u                            $ RT rx design width (fixed)
+      rnol = 'rxl + 2.80u'                    $ RT rx design outer length
+      rnow = 'rxw + 2.80u'                    $ RT rx design outer width
+     rn2pd = 1.40u                            $ RT rx to BN space (fixed)
+     rn2rx = 0.80u                            $ RT rx to Anode rx space 
+       dnw = 'rnow*nf - ((nf-1)*rnw) + 4.3u'  $ DN design width
+       dnl = 'rnol + 4.3u'                    $ DN design length
*
*---- Drawn Geometry + Mask Bias ----------------------------------------------
+        wx = 'w + delbn'
+        lx = 'l + delbn'
+      rnwx = 'rnw + delrx'
+      rxwx = 'rxw + delrx'
+      rxlx = 'rxl + delrx'
+     rnowx = 'rnow + delrx'
+     rnolx = 'rnol + delrx'
+    rn2pdx = 'rn2rx - (delbn + delrx)/2'
+    rn2rxx = 'rn2rx - delrx'
+      dnwx = dnw
+      dnlx = dnl
*
*---- Area/Perimeter Calculations ---------------------------------------------
+    arearx = 'rxwx*rxlx*nf'                   $ Total anode rx area
+   perimrx = '2*(rxwx+rxlx)*nf'               $ Total anode rx perim
+    areaan = 'wx*lx*nf'                       $ Total anode area
+   periman = '2*(w+1.0u+delrx+l+1.0u+delrx)*nf'$ Total anode perim
+    areagr = 'arearx-areaan'                  $ Total guardring area
+   perimgr = '2*(w+l)*nf'                     $ Total guardring inside perim
+    areadn = 'dnwx*dnlx'                      $ Total DN area (parasitic)
+   perimdn = '2*(dnwx+dnlx)'                  $ Total DN perim (parasitic)
+    areacp = 'l * w * nf'
+   perimcp = '2* (l + w + 0.88u) * nf'
*
*---- SBD Diode Parameters ----------------------------------------------------
+     mmsbd = agauss(0,1,3)
+     mmphi = '0.7071*sqrt(3f/areaan)'
+  msbdphib = 'sbdphib + mmphi*mmsbd/sqrt(par)'          $ Include mis-match
+     sbdis = '1.18*120e4*(pow((temper+dtemp+273),2))*exp(-38.922872*msbdphib)' $ SBD Is (A/m**2)
*
*---- Unit Resistance Calculations --------------------------------------------
+       rci = 'nvepi/(w*l)'                    $ Ver under anode
+     rcigr = 'nvepigr/(rxwx*rxlx-wx*lx)'      $ Ver under guardring
+       lsc = 'max(wx,lx)'
+       wsc = 'min(wx,lx)'
+      rchl = 'nwrs*((rn2pd+(wsc/8))/(rnolx-(lsc-(wsc/4))))*log(rnolx/(lsc-(wsc/4)))'
+      rchw = 'nwrs*((rn2pd+(wsc/8))/(rnowx-(wsc-(wsc/4))))*log(rnowx/(wsc-(wsc/4)))'
+      rcxl = 'nrnw/(rnwx*rnolx)'              $ Ver under cathode, length
+      rcxw = 'nrnw/(rnwx*rnowx)'              $ Ver under cathode, width
+     rccom = '(rchl/2)+rcxl'                  $ L side res. (common side)
+       rcl = 'rchl+rcxl'                      $ L side res. (non-common side)
+       rcw = 'rchw+rcxw'                      $ W side res.
*
*---- Model Resistance Calculations -------------------------------------------
+       rav = 'rci/nf'                            $ Ver under anode
+     ravgr = 'rcigr/nf'                          $ Ver under guardring
+      rm1a = '(((rxlx/(rxwx-0.2u))/3)/nf)*m1rs'  $ Pcell M1 res. anode
+      rm1c = '((((rnolx-rnw)/0.52u)/3)/(nf+1))*m1rs' $ Pcell M1 res. cathode
+     rrcov = '1/((nf*2/rcw)+(2/rcl)+((nf-1)/rccom))' $ Tot feol cathode res.
*
*---- Temperature Compensation for Reverse Leakage ----------------------------
+   pdeltat = 'temper-25+dtemp'
+  ptkelvin = 'pdeltat + 298.15'
+  lkprefac = 'sbdlk*exp(-6.853e3/ptkelvin)'
*
.model xsbd d
+ level = 1
+  dcap = 1
+  tlev = 0
+ tlevc = 1
+  tref = 25
+    eg = 0.62
+   xti = 2.0
+    js = 'sbdis*areaan'
+     n = 1.04
+    rs = rav
+   trs = 0.01
+    cj = 'nsbdcj*areacp'
+   cta = .62m
+    pb = 0.351
+   tpb = 0.5m
+    mj = 0.42
+    vb = 17.5

.model qgrd pnp
+ level=1
+ tlev=2
+ dcap=1
+ tlevc=1
+ tref=25
+ subs=1
+ eg=1.12
+ xti=3.0
+ gap1=473u
+ gap2=636
+ xtb=0
+ trb=tnwrs
+ trc=0.0038
+ is='7*js_p*areagr'
+ iss=0
+ nf=1
+ nr=1
+ ne=2
+ nc=2
+ ns=1
+ bf=0.3
+ ikf=2.0e7
+ re=ravgr
+ cje='nsbdcjp*perimcp'
+ vje=0.531
+ mje=0.2
+ cjc='cj_diodednsx*areadn + cjsw_diodednsx*perimdn'
+ vjc=4.561e-01
+ mjc=3.127e-01
+ cjs=0
+ cte=0.72m
+ tvje=2m
+ expli=10

rma   a   top  r=rm1a  dtemp=dtemp tc1=tm1rs
dsbd  top ci   xsbd    dtemp=dtemp area=1 pj=0
qgr   s ci top qgrd    dtemp=dtemp area=1 areab=1
gleak top ci   cur='lkprefac*(sinh(0.2*v(top,ci))*areaan)'
rcov  ci  bot  r=rrcov dtemp=dtemp tc1=0.00205
rmc   bot c    r=rm1c  dtemp=dtemp tc1=tm1rs

.ends sbdi
