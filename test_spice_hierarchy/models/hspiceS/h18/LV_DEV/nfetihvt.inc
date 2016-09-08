* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfetihvt.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  nfetihvt     1.8V HVTNFET in HV well subcircuit w/diodes
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b dn sx  nfetihvt l=nnn w=nnn
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
*            +     gcon = 1    <- Gate connection switch (1->single-ended,
*                                                         2->double-ended)
*            +    lstis = 1    <- Instance flag to control STI stress effects
*                                 on a local level in conjunction with gstis
*                                 global flag (0-> no STI stress effects,
*                                              1-> w/ STI stress effects)
*            +       sa = 0    <- Distance from PC to RX (STI) edge (meters)
*            +       sb = 0    <- Distance from PC to RX (STI) edge (meters)
*            +       sd = 0    <- Finger to finger spacing for NF>1 (meters)
*            +      rsx = 50   <- Body resistance
*            +      adn = 0    <- DN to substrate diode area (meters^2)
*            +      adp = 0    <- PW to DN diode area (meters^2)
*            +      pdn = 0    <- DN to substrate diode perimeter (meters)
*            +      pdp = 0    <- PW to DN diode perimeter (meters)
*            +    vdnsx = 50   <- DN/SX max voltage option (50V or 120V)
*
*
*  Model is a subcircuit containing the estimated parasitic diodes for
*  the Pwell to isolation and the isolation to substrate.  
*  
* SUBCIRCUIT SCHEMATIC:
*                           d
*                           o
*                           |
*                           |
*                         __|          d1           d2
*                       ||      b    |\     dn    /|
*              g o------||  ----o----| >|---o---|< |----o sx
*                       ||__         |/           \|
*                           |     
*                           |     
*                           |    
*                           o   
*                           s
*
*
***********************************************************************
.subckt nfetihvt d g s b dn sx  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                               gcon=1 rsx=50 par=1 lstis=1 sa=0 sb=0 sd=0 dtemp=0
+                               adn=0 pdn=0 adp=0 pdp=0 vdnsx=50
*
x1 d g s b nfetihvt4  w=w l=l nf=nf as=as ad=ad ps=ps pd=pd nrd=nrd nrs=nrs
+                     gcon=gcon rsx=rsx par=par lstis=lstis sa=sa sb=sb sd=sd
+                     dtemp=dtemp vdnsx=vdnsx
x2   b  dn diodepwdn area=adp perimeter=pdp 
x3   sx dn diodednsx area=adn perimeter=pdn vdnsx=vdnsx
*
.ends nfetihvt
