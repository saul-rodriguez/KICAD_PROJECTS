* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfet20mh.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV MOSFET: NFET20MH
*
*
* *****************************************************************************
.subckt	 nfet20mh d g s b
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(1.7552e-07/l+8.1023e-01)'
+ mv_nfet20mh = agauss(0,1,1)
+ mu_nfet20mh = agauss(0,1,1)
+ dvthmat = 'mv_nfet20mh*(7.849e-09/sqrt(l*w*mult))'
+ dumat = 'mu_nfet20mh*(4.667e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.1
+  noideva   = 4.8e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dnf20mhnoi*noi_scale)'
+  noib_mul  = 'exp(dnf20mhnoi*noi_scale/2)'
+  noic_mul  = 'exp(dnf20mhnoi*noi_scale/4)'
*
mnfet20mh  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_nfet20mh/(w+(6.6706e-07)))'  tc1=3.4591e-03  tc2=1.0690e-05  dtemp=dtemp
xj1  d gj d1  nfet20mhjfet1 w=w dtemp=dtemp
xj2  d gj d1  nfet20mhjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_nfet20mh*w)'  dtemp=dtemp
*
xdsub  b d  nfet20mhnwd area='((w+3.7e-06)*1.95e-06)' perimeter='(2*((w+3.7e-06)+1.95e-06))' dtemp=dtemp
*
.model mosinsub nmos level=49 version=3.3  capmod=2
+  mobmod=1  nqsmod=0  noimod=3
+  k1=k1_nfet20mh
+  k2=k2_nfet20mh     k3=9.2737e+00
+  k3b=-8.475e+00     nch=3.4911e+17	 vth0='vth0_nfet20mh+dvthmat'
+  voff=-8.502e-02    dvt0=dvt0_nfet20mh dvt1=2.8509e-01
+  dvt2=1.0762e-01    keta=0.0000e+00
+  pscbe1=4.2400e+08  pscbe2=1.0000e-12
+  alpha0=0.0000e+00  beta0=3.0000e+01
+  dvt0w=3.3546e+00   dvt1w=7.9099e+04	 dvt2w=-5.000e-02
+  ua=-4.120e-11      ub=2.3139e-18	 uc=1.9805e-10
+  u0='uo_nfet20mh*(1+dumat)'
+  dsub=5.0000e-01    eta0=2.9384e-02	 etab=-4.419e-02
+  nfactor=7.6812e-01 em=4.1000e+07	 pclm=5.0000e-01
+  drout=5.0000e-01   a0=1.0013e+00	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_nfet20mh
+  ags=1.5239e-01     b0=0.0000e+00	 b1=0.0000e+00
+  pdiblcb=-5.000e-06 pdiblc1=0.0000e+00 pdiblc2=5.0000e-06
+  delta=1.0000e-02   w0=1.0000e-10	 dlc=dlc_nfet20mh
+  dwc=3.0253e-07     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=3.3000e+04	    ute=-1.900e+00
+  kt1=-4.200e-01     kt2=0.0000e+00	 kt1l=0.0000e+00
+  ua1=4.2512e-21     ub1=-8.282e-19	 uc1=-3.437e-17
+  prt=0.0000e+00
+  cgso=cgso_nfet20mh cgdo=1.0000e-12	 cgbo=0.0000e+00
+  cgdl=3.0000e-10    cgsl=3.3070e-10	 ckappa=2.8300e+00
+  cf=0.0000e+00      elm=5.0000e+00
+  xpart=5.0000e-01   clc=1.0000e-15	 cle=6.0000e-01
+  rdsw=1.1313e+02
+  cdsc=0.0000e+00    cdscb=-1.000e-04	 cdscd=0.0000e+00
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_nfet20mh   ngate=0.0000e+00	 nlx=5.8229e-07
+  xl=xl_nfet20mh     xw=xw_nfet20mh
+  af=1.4265e+00      kf=6.9526e-26 	 ef=1.0000e+00
+  noia='2.4576e+20*noia_mul'
+  noib='7.9094e+05*noib_mul'
+  noic='-4.199e-11*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=6.8440e+01
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=-1.627e-07
+  wint=3.0253e-07    ldif=0.000e+00	 hdif=8.0000e-07
+  xj=3.0000e-07      js=6.4880e-08	 is=0.0
+  n=1.0000e+00	      tlev=0		 tlevc=1
+  jsw=0.0000e+00     cj=cj_nfet20mh	 cjsw=0.0000e+00
+  fc=0.0000e+00      xti=3.2090e+00
+  mj=2.6600e-01      mjsw=2.6600e-01
+  pb=4.5360e-01      pbsw=4.5360e-01
.ends nfet20mh
*
* HV-jfet 1
*
.subckt	 nfet20mhjfet1 d b s
.param w=1e-6  dtemp=0
jnfet20mhjfet1 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta1_nfet20mh/(1+(2.5022e-03)*pdelt)*(w+(6.6706e-07))/(1+(3.4591e-03)*pdelt+(1.0690e-05)*pdelt**2)'
+ vto='vth1_nfet20mh*(1+(2.5022e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfet20mhjfet1
*
* HV-jfet 2
*
.subckt	 nfet20mhjfet2 d b s
.param w=1e-6  dtemp=0
jnfet20mhjfet2 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta2_nfet20mh/(1+(2.5022e-03)*pdelt)*(w+(6.6706e-07))/(1+(3.4591e-03)*pdelt+(1.0690e-05)*pdelt**2)'
+ vto='vth2_nfet20mh*(1+(2.5022e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfet20mhjfet2
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 nfet20mhnwd a c
.param area=1.0e-12  perimeter=1e-06  dtemp=0
dnfet20mhnwd  a c  diodeinsub area=area pj=perimeter dtemp=dtemp
.model diodeinsub d level=1
+ js=1.147e-06   jsw=5.148e-12
+ n=1.040e+00
+ cj=1.125e-04	 cjsw=4.025e-10
+ m=4.579e-01	 mjsw=9.554e-02
+ vj=6.570e-01	 php=3.237e-01
+ af=1.000e+00	 kf=0.000e+00
+ xti=9.046e-01	 tt=0.000e+00
+ expli=1.000e+12
+ tref=2.500e+01
.ends nfet20mhnwd
