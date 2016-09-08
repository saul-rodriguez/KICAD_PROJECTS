* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfet25m.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
* *****************************************************************************
*
*>  HV MOSFET: PFET25M
*
*
* *****************************************************************************
.subckt	 pfet25m d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(1.50e-06/l+5.0820e-07)'
+ mv_pfet25m = agauss(0,1,1)
+ mu_pfet25m = agauss(0,1,1)
+ dvthmat = 'mv_pfet25m*(6.187e-09/sqrt(l*w*mult))'
+ dumat = 'mu_pfet25m*(5.586e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
+ rdsw_eff = 'max(0,(8350*(pdelt/298.0)))'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.3
+  noideva   = 7.2e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dpf25mnoi*noi_scale)'
+  noib_mul  = 'exp(dpf25mnoi*noi_scale/2)'
+  noic_mul  = 'exp(dpf25mnoi*noi_scale/4)'
*
mpfet25m  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_pfet25m/(w+(-1.502e-07)))'  tc1=3.1819e-03  tc2=1.0000e-10  dtemp=dtemp
xj1  d gj d1  pfet25mjfet1 w=w dtemp=dtemp
xj2  d gj d1  pfet25mjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_pfet25m*w)'  dtemp=dtemp
*
xqpnp  sub b d	pfet25mpnp  area=1  w=w l=l dtemp=dtemp
xdcbx  sub b	pfet25mdcbx area=1  w=w dtemp=dtemp
*
.model mosinsub pmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_pfet25m
+  k2=k2_pfet25m      k3=2.6170e+00
+  k3b=8.7240e-01     nch=1.0250e+17	 vth0='vth0_pfet25m+dvthmat'
+  voff=-1.041e-01    dvt0=dvt0_pfet25m	 dvt1=8.7660e-01
+  dvt2=0.0000e+00    keta=-1.188e-02
+  pscbe1=1.0000e+09  pscbe2=1.0000e-09
+  alpha0=0.0000e+00  beta0=1.6000e+02
+  dvt0w=5.2450e-02   dvt1w=9.9680e+04	 dvt2w=-1.985e-05
+  ua=9.5710e-11      ub=2.2950e-18	 uc=-7.008e-11
+  u0='uo_pfet25m*(1+dumat)'
+  dsub=1.0000e+00    eta0=2.0340e-06	 etab=-8.403e-07
+  nfactor=2.1350e-02 em=4.1000e+07	 pclm=2.1730e+00
+  drout=4.9650e-01   a0=8.9030e-01	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_pfet25m
+  ags=1.2900e-01     b0=0.0000e+00	 b1=0.0000e+00
+  pdiblcb=0.0000e+00 pdiblc1=3.8950e-02 pdiblc2=1.0000e-05
+  delta=5.7380e-03   w0=2.5000e-09	 dlc=dlc_pfet25m
+  dwc=3.0640e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=-3.789e+04	     ute=-1.473e+00
+  kt1=-3.821e-01     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=4.3217e-10     ub1=-3.102e-18	 uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_pfet25m  cgdo=1.0000e-12	 cgbo=0.0000e+00
+  cgdl=8.9100e-11    cgsl=3.0000e-10	 ckappa=3.0000e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=5.0000e-01   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=rdsw_eff
+  cdsc=0.0000e+00    cdscb=0.0000e+00	 cdscd=3.0930e-07
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_pfet25m    ngate=0.0000e+00	 nlx=1.0000e-08
+  xl=xl_pfet25m      xw=xw_pfet25m
+  af=1.4349e+00      kf=1.3915e-26	 ef=1.0000e+00
+  noia='1.8255e+18*noia_mul'
+  noib='1.2815e+04*noib_mul'
+  noic='6.7166e-13*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=1.4000e+02
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=2.7830e-08
+  wint=3.0640e-07    ldif=0.000e+00	 hdif=0.0000e+00
+  xj=3.0000e-07      js=4.4690e-07	 is=0.0
+  n=1.0000e+00	      tlev=0		 tlevc=1
+  jsw=0.0000e+00     cj=cj_pfet25m	 cjsw=0.0000e+00
+  fc=0.000e+00	      xti=3.5650e-01
+  pb=1.0000e+00      pbsw=1.0000e+00
.ends pfet25m
*
* HV-jfet 1
*
.subckt	 pfet25mjfet1 d b s
.param w=1e-6  dtemp=0
jpfet25mjfet1 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta1_pfet25m/(1+(3.4013e-03)*pdelt)*(w+(-1.502e-07))/(1+(3.1819e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth1_pfet25m*(1+(3.4013e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet25mjfet1
*
* HV-jfet 2
*
.subckt	 pfet25mjfet2 d b s
.param w=1e-6  dtemp=0
jpfet25mjfet2 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta2_pfet25m/(1+(3.4013e-03)*pdelt)*(w+(-1.502e-07))/(1+(3.1819e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth2_pfet25m*(1+(3.4013e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet25mjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 pfet25mpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qpfet25mpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='2.600e-06*w*1e-06+1.000e-18*w*l+3.849e-17*exp(-1.045e-15/(l*1e-06))'
+ ise='3.535e-06*w*1e-06+1.000e-18*w*l+1.306e-17*exp(-1.000e-15/(l*1e-06))'
+ ikf='9.400e+05*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.500e+06*w*1e-06'  isc=1.000e-18
+ bf='3.054e+01*exp(6.831e-12/(w*1e-06))+8.750e+01*exp(-3.246e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.466e-07/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+1.000e-15/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.290e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=3.315e+00
+ cje='((2.591e-04*((w+1.5e-06)*(l+1.1e-06))+5.672e-10*(2*((w+1.5e-06)+l+1.1e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+6.7e-06)*(l+4.7e-06))+7.569e-10*(2*((l+4.7e-06)+(w+6.7e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.4349e+00	 kf=0.000e+00	fc=7.500e-01
.ends pfet25mpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 pfet25mdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dpfet25mdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='2.733e-15+4.350e-06*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends pfet25mdcbx
