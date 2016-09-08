* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfet_rf.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  nfet_rf     1.8V NFET in SX RF subcircuit
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b   nfet_rf l=nnn w=nnn
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
*            +    lstis = 1    <- Instance flag to control STI stress effects
*                                 on a local level in conjunction with gstis
*                                 global flag (0-> no STI stress effects,
*                                              1-> w/ STI stress effects)
*            +       sa = 0    <- Distance from PC to RX (STI) edge (meters)
*            +       sb = 0    <- Distance from PC to RX (STI) edge (meters)
*            +       sd = 0    <- Finger to finger spacing for NF>1 (meters)
*            +      rsx = 50   <- Body resistance
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
*        |                          |                   	       |
*        |                          |               	               |
*        |                    |_____|                   	       |
*        |                  | |         b1            	   bulk        |
*   gate o------------------| |  |------o---/\/\/\----------o  	       |
*        |                  | |_____          rsb     	               |
*        |                    |     |                   	       |
*        |                          |                   	       |
*        |                          |              	               |
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
.subckt nfet_rf d g s b    w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                          gcon=2 rsx=50 par=1 lstis=1 sa=0 sb=0 sd=0 dtemp=0
.param
+  zad=ad zas=as znrd=nrd znrs=nrs zpd=pd zps=ps
*
* Gate-S/D wire capacitance calculation (function of w, l and nf)
+  cgw1='(1.36*(45.3e-12*w*nf+0.6e-15))'
+  cgl1='(47233e-12*l+5.9772e-15)/14.048e-15'
*
* Drain-Source wire capacitance calculation (function of w, l and nf)
+  cdsw1='(2*((20e-5*(1e+6*w*nf)**2 + 8.87e-2*(1e+6*w*nf) + 0.4703)*1.0e-15))'
+  cdsl1='(1.6432e-6/l+8.4)/17.53'
*
* Substrate resistance calculation (function of w, l and nf)
+  rsw1='(0.8812*(((w-2*wint_n)*nf)**(-0.5491)))/99.43'
+  rsl1='(0.0012*(l-2*lint_n)**(-0.7192))'
 
x1 d1 g s1 b1 nfet  w=w l=l as=as ad=ad ps=ps pd=pd nrs=nrs nrd=nrd
+                   gcon=gcon par=par nf=nf dtemp=dtemp rf=1
+                   lstis=lstis sa=sa sb=sb sd=sd
rdext  d1  d  r='znrd*rsh_n/nf'
rsext  s1  s  r='znrs*rsh_n/nf'
rsb    b  b1  r='rsl1*rsw1'
cwgd   g   d  c='cgw1*cgl1'
cwgs   g   s  c='cgw1*cgl1'
cwds   d   s  c='cdsw1*cdsl1'

.ends nfet_rf
