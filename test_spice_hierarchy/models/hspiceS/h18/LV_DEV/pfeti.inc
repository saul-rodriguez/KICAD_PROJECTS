* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfeti.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  pfeti     1.8V PFET in HV well subcircuit w/diodes
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b sx  pfeti l=nnn w=nnn
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
*            +      rsx = 50   <- Body resistance
*            +       rf = 0    <- RF device flag (0-> pfeti pcell
*                                                 1-> pfeti_rf pcell)
*            +      adn = 0    <- DN to substrate diode area (meters^2)
*            +      pdn = 0    <- DN to substrate diode perimeter (meters)
*            +      gns = 0    <- ESD hierarchical cell layout option
*                                 (0-> silicided gate, 1-> non-silicided gate)
*            +    vdnsx = 50   <- DN/SX max voltage option (50V or 120V)
*
*
*  Model is a subcircuit containing the estimated parasitic diode for
*  the isolation to substrate.  
*  
* SUBCIRCUIT SCHEMATIC:
*                           d
*                           o
*                           |
*                           |
*                         __|       d1
*                       ||      b    /|
*              g o------||  ----o--|< |----o sx
*                       ||__         \|
*                           |     
*                           |     
*                           |    
*                           o   
*                           s
*
*
***********************************************************************
.subckt pfeti d g s b sx  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0 gcon=1
+                         rsx=50 rf=0 par=1 dtemp=0 adn=0 pdn=0 gns=0 vdnsx=50
*
x1 d g s b pfeti4  w=w l=l nf=nf as=as ad=ad ps=ps pd=pd nrd=nrd nrs=nrs
+                  gcon=gcon rsx=rsx rf=rf par=par dtemp=dtemp gns=gns vdnsx=vdnsx
x2   sx  b diodednsx area=adn perimeter=pdn vdnsx=vdnsx
*
.ends pfeti
