* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfeti_rf.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  pfeti_rf     1.8V PFET in HV well RF subcircuit w/diodes
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b sx  pfeti_rf l=nnn w=nnn
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
*            +      adn = 0    <- DN to substrate diode area (meters^2)
*            +      pdn = 0    <- DN to substrate diode perimeter (meters)
*            +    vdnsx = 50   <- DN/SX max voltage option (50V or 120V)
*
*
*  Model is a subcircuit containing the estimated parasitic diode for
*  the isolation to substrate.
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
*        |              g   | |        b1          b    | /|  sx       |
*   gate o--------------o---| |  |------o---\/\/---o----|< |--o	       |
*        |                  | |_____         rsb        | \|	       |
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
.subckt pfeti_rf d g s b sx w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrs=0 nrd=0
+                           gcon=2 rsx=50 par=1 dtemp=0 adn=0 pdn=0 vdnsx=50
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
x2     sx  b  diodednsx area=adn perimeter=pdn vdnsx=vdnsx

.ends pfeti_rf