* Path, Component, Release: cmos7base/rel/HSPICE/models/nfetmtw.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  nfetmtw  5.0V Triple-well NFET subcircuit
*
***********************************************************************
*
*  SYNTAX:     xxx  d g s b tw sx  nfetmtw l=nnn w=nnn
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
*            +       nf = 1    <- number of gate stripes or "fingers" in device
*            +  m (par) = 1    <- number of parallel instances (multiplicity)
*            +     gcon = 1    <- Gate connection switch (1->single-ended,
*                                                         2->double-ended)
*            +      rsx = 50   <- body resistance
*            +       rf = 0    <- RF device flag (not used)
*            +      gns = 0    <- ESD hierarchical cell layout option
*                                 (0-> silicided gate, 1->non-silicided gate)
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
*                       ||      b    |\     tw    /|
*              g o------||  ----o----| >|---o---|< |----o sx
*                       ||__         |/           \|
*                           |     
*                           |     Area and perimeter for both PI diodes 
*                           |     are calculated based on inside N-well 
*                           o     edge of the isolation ring.
*                           s
*
*
*
***********************************************************************
*
.subckt nfetmtw d g s b tw sx w=0 l=0 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+                              dtemp=0 nf=1 gcon=1 rsx=50 rf=0 par=1 gns=0
*
.param
+  warea  = '(nf*l+(nf-1)*0.76u+2*0.58u+4.64u)*(w+5.8u)'
+  wperim = '2*(nf*l+(nf-1)*0.76u+2*0.58u+4.64u)+2*(w+5.8u)'
*
x1 d g s b nfetm w=w l=l as=as ad=ad ps=ps pd=pd nrd=nrd nrs=nrs 
+                 dtemp=dtemp nf=nf gcon=gcon rsx=rsx rf=rf par=par gns=gns
x2   b  tw diodepwpi area=warea perim=wperim dtemp=dtemp
x3   sx tw diodepisx area=warea perim=wperim dtemp=dtemp
x4   tw sx diodenwx area='wperim*0.1u' perim=wperim dtemp=dtemp
*
.ends nfetmtw