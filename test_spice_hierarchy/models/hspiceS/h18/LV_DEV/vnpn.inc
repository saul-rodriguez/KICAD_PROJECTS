* Path, Component, Release: cmhv7sf/rel/HSPICE/models/vnpn.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV Bipolar: VNPN
*
* *****************************************************************************
.subckt	 vnpn c b e s  area=1.0 par=1 dtemp=0
.param
+ mis_hvnpn   = agauss(0,1,1)
+ ismat	      = 'mis_hvnpn*0.04/sqrt(par)'
+ misei_hvnpn = agauss(0,1,1)
+ ibeimat     = 'misei_hvnpn*0.05/sqrt(par)'
+ mise_hvnpn  = agauss(0,1,1)
+ ibenmat     = 'mise_hvnpn*0.20/sqrt(par)'
*
+ pxre = -1.405e+00
+ ptdegk = 'temper+dtemp+273'
+ ret_hvnpn = 're_hvnpn*((ptdegk/298)**pxre)'

qvnpn c b e s npninsub area=1.0	dtemp=dtemp

* Intrinsic bipolar transistor model
.model npninsub npn level=4
+   rcx=rcx_hvnpn
+   rci=rci_hvnpn	vo=2.0000e+00
+  gamm=5.5560e-12    hrcf=1.0000e+00
+   rbx=rbx_hvnpn       rbi=rbi_hvnpn
+    re=ret_hvnpn	rs=2.0480e+01	  rbp=4.2870e+01
+    is='is_hvnpn*(1.0+ismat)'
+    nf=1.0000e+00
+    nr=1.0000e+00	fc=7.5000e-01
+  cbeo=0.0000e+00     cje=cje_hvnpn
+    pe=7.1100e-01	me=9.1110e-01
+   aje=0.0000e+00    cbco=0.0000e+00
+   cjc=2.0510e-15     qco=0.0000e+00
+  cjep=cjep_hvnpn	pc=7.0200e-01
+    mc=4.3920e-01     ajc=0.0000e+00
+  cjcp=5.2850e-14	ps=4.7000e-01
+    ms=3.5390e-01     ajs=0.0000e+00
+  ibei='ibei_hvnpn*(1.0+ibeimat)'
+   wbe=1.0000e+00
+   nei=1.0310e+00    iben='iben_hvnpn*(1.0+ibenmat)'
+   nen=1.7860e+00    ibci=6.9180e-21
+   nci=9.9970e-01    ibcn=2.5640e-16
+   ncn=1.4740e+00    avc1=9.9920e-01
+  avc2=avc2_hvnpn      isp=3.8890e-17
+   wsp=1.0000e+00     nfp=1.0000e+00
+ ibeip=9.5990e-19   ibenp=1.0000e-22
+ ibcip=3.1100e-15    ncip=1.0000e+00
+ ibcnp=0.0000e+00    ncnp=2.0000e+00
+   vef=vef_hvnpn       ver=3.1000e+00
+   ikf=5.3050e-05     ikr=4.0000e-05
+   ikp=2.0110e-05	tf=tf_hvnpn
+   qtf=6.6100e-05     xtf=1.9180e+00
+   vtf=4.8060e+00     itf=4.0700e-06
+    tr=1.0000e-09	td=0.0000e+00
+   kfn=2.0000e-15
+   afn=1.0000e+00
+   xre=0.0000e+00
+   xrb=2.3850e-01     xrc=0.0000e+00
+   xrs=0.0000e+00     xvo=0.0000e+00
+    ea=1.1670e+00    eaie=1.0940e+00
+  eaic=1.1890e+00    eais=1.1890e+00
+  eane=1.0840e+00    eanc=1.1890e+00
+  eans=1.1890e+00     xis=2.5480e+00	  xii=3.4060e+00
+   xin=4.9010e+00     tnf=0.0000e+00
+  tavc=2.1500e-04     rth=0.0000e+00
+   cth=0.0000e+00    tref=2.500000001e+01
.ends vnpn
