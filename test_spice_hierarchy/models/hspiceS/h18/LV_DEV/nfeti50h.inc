* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfeti50h.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV MOSFET: NFETI50H
*
*
* *****************************************************************************
.subckt	 nfeti50h d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(4.6930e-07/l+5.7020e-01)'
+ mv_nfeti50h = agauss(0,1,1)
+ mu_nfeti50h = agauss(0,1,1)
+ dvthmat = 'mv_nfeti50h*(2.574e-08/sqrt(l*w*mult))'
+ dumat = 'mu_nfeti50h*(3.606e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
+ rdsw_eff = 'max(0,(8350*(pdelt/298.0)))'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 1.8
+  noideva   = 6.0e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dnfi50hnoi*noi_scale)'
+  noib_mul  = 'exp(dnfi50hnoi*noi_scale/2)'
+  noic_mul  = 'exp(dnfi50hnoi*noi_scale/4)'
*
mnfeti50h  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_nfeti50h/(w+(5.6090e-06)))'  tc1=4.8835e-03  tc2=1.0000e-10  dtemp=dtemp
xj1  d gj d1  nfeti50hjfet1 w=w dtemp=dtemp
xj2  d gj d1  nfeti50hjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_nfeti50h*w)'  dtemp=dtemp
*
xqpnp  sub d b	nfeti50hpnp  area=1 w=w l=l dtemp=dtemp
xdcbx  sub d	nfeti50hdcbx area=1 w=w dtemp=dtemp
*
.model mosinsub nmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_nfeti50h
+  k2=k2_nfeti50h     k3=2.1820e+01
+  k3b=2.5555e+00     nch=8.3510e+16	 vth0='vth0_nfeti50h+dvthmat'
+  voff=-1.572e-01    dvt0=dvt0_nfeti50h dvt1=1.0030e+00
+  dvt2=0.0000e+00    keta=-6.708e-04
+  pscbe1=1.0000e+09  pscbe2=1.0000e-09
+  alpha0=0.0000e+00  beta0=1.6000e+02
+  dvt0w=5.4390e-01   dvt1w=5.8980e+03	 dvt2w=-9.797e-05
+  ua=1.1170e-09      ub=7.1280e-20	 uc=-1.075e-10
+  u0='uo_nfeti50h*(1+dumat)'
+  dsub=4.6650e-09    eta0=5.5620e-08	 etab=-2.298e-10
+  nfactor=1.0370e+00 em=4.1000e+07	 pclm=2.4080e+00
+  drout=4.9650e-01   a0=1.1290e+00	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_nfeti50h
+  ags=2.8060e-02     b0=0.0000e+00	 b1=0.0000e+00
+  pdiblcb=0.0000e+00 pdiblc1=2.7530e-01 pdiblc2=1.0000e-05
+  delta=1.0000e-03   w0=2.5000e-09	 dlc=dlc_nfeti50h
+  dwc=4.4410e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=-4.847e+04	     ute=-1.863e+00
+  kt1=-9.899e-01     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=0.0000e+00     ub1=0.0000e+00	 uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_nfeti50h cgdo=1.0000e-12	 cgbo=5.0000e-09
+  cgdl=2.5000e-10    cgsl=9.8760e-11	 ckappa=3.0000e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=5.0000e-01   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=rdsw_eff
+  cdsc=0.0000e+00    cdscb=0.0000e+00	 cdscd=9.3940e-08
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_nfeti50h   ngate=0.0000e+00	 nlx=5.4520e-07
+  xl=xl_nfeti50h     xw=xw_nfeti50h
+  af=1.2878e+00      kf=1.9604e-26 	 ef=0.9000e+00
+  noia='2.2247e+21*0.3*noia_mul'
+  noib='4.4304e+05*0.2*noib_mul'
+  noic='-1.000e-13*0.3*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=1.4000e+02
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=-1.927e-07
+  wint=4.4410e-07    ldif=0.000e+00	 hdif=0.0000e+00
+  xj=3.0000e-07      js=7.1660e-08	 is=0.0
+  n=1.0200e+00	      tlev=0		 tlevc=1
+  jsw=0.0000e+00     cj=cj_nfeti50h	 cjsw=0.0000e+00
+  fc=0.0000e+00      xti=3.6530e+00
+  pb=6.1170e-01      pbsw=6.1170e-01
.ends nfeti50h
*
* HV-jfet 1
*
.subckt	 nfeti50hjfet1 d b s
.param w=1e-6  dtemp=0
jnfeti50hjfet1 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta1_nfeti50h/(1+(4.0986e-03)*pdelt)*(w+(5.6090e-06))/(1+(4.8835e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth1_nfeti50h*(1+(4.0986e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti50hjfet1
*
* HV-jfet 2
*
.subckt	 nfeti50hjfet2 d b s
.param w=1e-6  dtemp=0
jnfeti50hjfet2 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta2_nfeti50h/(1+(4.0986e-03)*pdelt)*(w+(5.6090e-06))/(1+(4.8835e-03)*pdelt+(1.0000e-10)*pdelt**2)'
+ vto='vth2_nfeti50h*(1+(4.0986e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti50hjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 nfeti50hpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qnfeti50hpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='4.291e-06*w*1e-06+6.047e-07*w*l+1.884e-16*exp(-8.064e-13/(l*1e-06))'
+ ise='6.125e-06*w*1e-06+1.739e-06*w*l+6.626e-16*exp(-3.337e-11/(l*1e-06))'
+ ikf='2.254e+06*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.000e+06*w*1e-06'  isc=1.000e-18
+ bf='7.600e+01*exp(2.750e-12/(w*1e-06))+2.173e+02*exp(-6.699e-13/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.793e-11/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+9.977e-10/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.350e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=1.315e+00
+ cje='((2.591e-04*((w+4e-06)*(l+0.65e-06))+5.672e-10*(2*((w+4e-06)+l+0.65e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+25e-06)*(l+9e-06))+7.569e-10*(2*((l+9e-06)+(w+25e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.2878e+00	 kf=0.000e+00	fc=7.500e-01
.ends nfeti50hpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 nfeti50hdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dnfeti50hdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='5.003e-15+1.052e-05*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends nfeti50hdcbx
