* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfeti4_rf.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  pfeti4_rf     1.8V PFET in HV well RF subcircuit (4 node)
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b  pfeti4_rf l=nnn w=nnn
*
*  REQUIRED:
*            +        w = nnn  <- Design width of RX (meters)
*            +        l = nnn  <- Design length of PC (meters)
*  OPTIONAL:
*            +       as = 0    <- Source diffusion area (meters^2)
*            +       ad = 0    <- Drain diffusion area (meters^2)
*            +       ps = 0    <- Source diffusion perimeter in (meters)
*            +       pd = 0    <- Drain diffusion perimeter in (meters)
*            +      nrd = 0    <- Number of squares of drain diffusion
*            +      nrs = 0    <- Number of squares of source diffusion
*            +    dtemp = 0    <- Device temp rise from ambient (deg C)
*            +       nf = 1    <- Number of gate stripes or "fingers" in device
*            +  m (par) = 1    <- Number of parallel instances (multiplicity)
*            +     gcon = 2    <- Gate connection switch (1->single-ended,
*                                                         2->double-ended)
*            +      rsx = 50   <- Body resistance
*            +    vdnsx = 50   <- DN/SX max voltage option (50V or 120V)
*
*  NOTES:
*
*  1. If nrd or nrs are not passed to the model they will default to 0.
*     This will result in 0 ohms of silicided S/D resistance being placed
*     in series with the device model.
*
*  2. Calculations assume input design width represents width of each
*     finger.
*
*  3. Calculations based on PCELL scaling rules and assume that for a device
*     with an even number of fingers, the source is the outer diffusion.
*  
* SUBCIRCUIT SCHEMATIC:
*
*                cwgd
*                 | |             drain
*        o--------| |---------------o----------------------------------o
*        |        | |               |                                  |
*        |                          |                                  |
*        |                          /                                  |
*        |                   rdext  \                                  |
*        |                          /                                  |
*        |                          |                                ----- cwds
*        |                      d1  |                                -----
*        |                          o                   	       |
*        |                          |               	               |
*        |                    |_____|                   	       |
*        |              g   | |        b1          b                   |
*   gate o--------------o---| |  |------o---\/\/---o           	       |
*        |                  | |_____         rsb                       |
*        |                    |     |                   	       |
*        |                          |                   	       |
*        |                          o              	               |
*        |                      s1  | 	                               |
*        |                          |                                  |
*        |                          \                                  |
*        |                   rsext  /                                  |
*        |                          \                                  |
*        |                          |                                  |
*        |        | |               |                                  |
*        o--------| |---------------o----------------------------------o
*                 | |             source
*                cwgs
*
*
***********************************************************************
.subckt pfeti4_rf d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrs=0 nrd=0
+                          gcon=2 rsx=50 par=1 dtemp=0 vdnsx=50
*
.param
+  znrd=nrd znrs=nrs
*
* Gate-S/D wire capacitance calculation (function of w, l and nf)
+  cgw1='(1.2*(85.5e-12*w*nf+0.4135e-15))'
+  cgl1='(23426e-12*l+12.428e-15)/14.09e-15'
*
* Drain-Source wire capacitance calculation (function of w, l and nf)
+  cds= '(nf)*(2500e-18 + l*100e-12 + w*100e-12)'
*
* Drain resistance calculation (function of l and nf)
+  rd = '1 + (nf-2)*(0.0010)'
*
* Source resistance calculation (function of l and nf)
+  rs = '1 + (nf)*(0.0010)'
*
* Substrate resistance calculation (function of w, l and nf)
+  rsw1='(0.8812*(((w-2*wint_p)*nf)**(-0.5491)))/99.43'
+  rsl1='2*(0.0012*(l-2*lint_p)**(-0.7192))'

x1  d1 g s1 b1  pfeti4  w=w l=l as=as ad=ad ps=ps pd=pd nrs=nrs nrd=nrd
+                       gcon=gcon par=par nf=nf dtemp=dtemp rf=1 vdnsx=vdnsx
rdext  d1  d  r='(znrd*rsh_p/nf)+rd'
rsext  s1  s  r='(znrs*rsh_p/nf)+rs'
rsb    b  b1  r='rsw1*rsl1'
cwgd   g   d  c='0.38*(cgw1*cgl1)'
cwgs   g   s  c='cgw1*cgl1'
cwds   d   s  c=cds

.ends pfeti4_rf
