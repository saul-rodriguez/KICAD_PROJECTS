* Path, Component, Release: cmhv7sf/rel/HSPICE/models/pfet50m.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
* *****************************************************************************
*
*>  HV MOSFET: PFET50M
*
*
* *****************************************************************************
.subckt	 pfet50m d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(1.50e-06/l+7.2490e-04)'
+ mv_pfet50m = agauss(0,1,1)
+ mu_pfet50m = agauss(0,1,1)
+ dvthmat = 'mv_pfet50m*(5.862e-09/sqrt(l*w*mult))'
+ dumat = 'mu_pfet50m*(4.525e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
+ rdsw_eff = 'max(0,(8350*(pdelt/298.0)))'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.3
+  noideva   = 7.2e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dpf50mnoi*noi_scale)'
+  noib_mul  = 'exp(dpf50mnoi*noi_scale/2)'
+  noic_mul  = 'exp(dpf50mnoi*noi_scale/4)'
*
mpfet50m  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_pfet50m/(w+(1.4350e-06)))'  tc1=4.3018e-03  tc2=1.0000e-10  dtemp=dtemp
xj1  d gj d1  pfet50mjfet1 w=w dtemp=dtemp
xj2  d gj d1  pfet50mjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_pfet50m*w)'  dtemp=dtemp
*
xqpnp  sub b d	pfet50mpnp  area=1  w=w l=l dtemp=dtemp
xdcbx  sub b	pfet50mdcbx area=1  w=w dtemp=dtemp
*
.model mosinsub pmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_pfet50m
+  k2=k2_pfet50m      k3=2.6430e+00
+  k3b=-3.247e-01     nch=1.0230e+17	 vth0='vth0_pfet50m+dvthmat'
+  voff=-1.034e-01    dvt0=dvt0_pfet50m	 dvt1=6.7850e-01
+  dvt2=0.0000e+00    keta=-2.251e-02
+  pscbe1=1.0000e+09  pscbe2=1.0000e-09
+  alpha0=0.0000e+00  beta0=1.6000e+02
+  dvt0w=2.7210e-02   dvt1w=2.4470e+04	 dvt2w=-2.005e-05
+  ua=2.4880e-12      ub=2.4810e-18	 uc=-1.225e-10
+  u0='uo_pfet50m*(1+dumat)'
+  dsub=1.0000e+00    eta0=5.6670e-06	 etab=-1.561e-06
+  nfactor=2.7790e-01 em=4.1000e+07	 pclm=2.2010e+00
+  drout=4.9650e-01   a0=8.1480e-01	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_pfet50m
+  ags=1.0560e-01     b0=0.0000e+00	 b1=0.0000e+00
+  pdiblcb=0.0000e+00 pdiblc1=5.5470e-03 pdiblc2=1.0000e-05
+  delta=1.0000e-03   w0=2.5000e-09	 dlc=dlc_pfet50m
+  dwc=2.8960e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=-3.415e+04	     ute=-1.278e+00
+  kt1=-3.929e-01     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=0.0000e+00     ub1=0.0000e+00	 uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_pfet50m  cgdo=1.0000e-12	 cgbo=1.0000e-09
+  cgdl=1.0860e-10    cgsl=1.0000e-10	 ckappa=2.9970e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=5.0000e-01   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=rdsw_eff
+  cdsc=0.0000e+00    cdscb=0.0000e+00	 cdscd=4.6460e-08
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_pfet50m    ngate=0.0000e+00	 nlx=1.0000e-08
+  xl=xl_pfet50m      xw=xw_pfet50m
+  af=1.3812e+00      kf=1.0138e-26	 ef=1.0000e+00
+  noia='3.0163e+18*noia_mul'
+  noib='1.8284e+04*noib_mul'
+  noic='3.5502e-13*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=1.4000e+02
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=9.2960e-09
+  wint=2.8960e-07    ldif=0.000e+00	 hdif=0.0000e+00
+  xj=3.0000e-07      js=4.4690e-07	 is=0.0
+  n=1.0000e+00	      tlev=0		 tlevc=1
+  jsw=0.0000e+00     cj=cj_pfet50m	 cjsw=0.0000e+00
+  fc=0.000e+00	      xti=3.5650e-01
+  pb=1.0000e+00      pbsw=1.0000e+00
.ends pfet50m
*
* HV-jfet 1
*
.subckt	 pfet50mjfet1 d b s
.param w=1e-6  dtemp=0
jpfet50mjfet1 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta1_pfet50m/(1+(3.6272e-03)*pdelt)*(w+(1.4350e-06))/(1+(4.3018e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth1_pfet50m*(1+(3.6272e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet50mjfet1
*
* HV-jfet 2
*
.subckt	 pfet50mjfet2 d b s
.param w=1e-6  dtemp=0
jpfet50mjfet2 d b s rnjfetinsub
.model rnjfetinsub  pjf level=1
+ beta='beta2_pfet50m/(1+(3.6272e-03)*pdelt)*(w+(1.4350e-06))/(1+(4.3018e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth2_pfet50m*(1+(3.6272e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends pfet50mjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 pfet50mpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qpfet50mpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='5.000e-06*w*1e-06+1.000e-18*w*l+8.152e-17*exp(-7.045e-15/(l*1e-06))'
+ ise='2.535e-06*w*1e-06+1.000e-16*w*l+5.200e-17*exp(-1.000e-15/(l*1e-06))'
+ ikf='5.922e+05*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.483e+05*w*1e-06'  isc=1.000e-18
+ bf='8.154e+01*exp(5.831e-12/(w*1e-06))+2.871e+01*exp(-3.246e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.000e-07/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+6.715e-10/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.290e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=1.315e+00
+ cje='((2.591e-04*((w+7.5e-06)*(l+3.57e-06))+5.672e-10*(2*((w+7.5e-06)+l+3.57e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+14e-06)*(l+6.8e-06))+7.569e-10*(2*((l+6.8e-06)+(w+14e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.3812e+00	 kf=0.000e+00	fc=7.500e-01
.ends pfet50mpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 pfet50mdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dpfet50mdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='3.733e-15+1.235e-05*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends pfet50mdcbx
