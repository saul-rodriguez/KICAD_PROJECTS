* Path, Component, Release: cmhv7sf/rel/HSPICE/models/nfeti50t.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  HV MOSFET: NFETI50T
*
*
* *****************************************************************************
.subckt	 nfeti50t d g s b sub
+        w=1.0e-6 l=1.0e-6 nrd=0 nrs=0 ad=0 as=0 pd=0 ps=0 mult=1 dtemp=0
.param
+ gv = '(0.0/l+1.6036e+00)'
+ mv_nfeti50t = agauss(0,1,1)
+ mu_nfeti50t = agauss(0,1,1)
+ dvthmat = 'mv_nfeti50t*(3.974e-09/sqrt(l*w*mult))'
+ dumat = 'mu_nfeti50t*(7.778e-09/sqrt(l*w*mult))'
+ pdelt = 'temper+dtemp-25.0'
*
* Flicker Noise: statistics function of w, l and multiplicity (mult)
+  noistd    = 2.0
+  noideva   = 2.4e-11
+  noi_scale = 'noistd-min(log(sqrt(w*l*mult/noideva)),0)'
+  noia_mul  = 'exp(dnfi50tnoi*noi_scale)'
+  noib_mul  = 'exp(dnfi50tnoi*noi_scale/2)'
+  noic_mul  = 'exp(dnfi50tnoi*noi_scale/4)'
*
mnfeti50t  d1 g s b  mosinsub w=w l=l nrd=0 nrs=nrs ad=0 as=as pd=0 ps=ps dtemp=dtemp
rd d1 d r='(rj_nfeti50t/(w+(5.5430e-06)))'  tc1=6.3480e-03  tc2=1.0000e-05  dtemp=dtemp
xj1  d gj d1  nfeti50tjfet1 w=w dtemp=dtemp
xj2  d gj d1  nfeti50tjfet2 w=w dtemp=dtemp
e1  d1 gj d1 s	 gv
cgdx g d  c='(cgdx1_nfeti50t*w)'  dtemp=dtemp
*
xqpnp  sub d b	nfeti50tpnp  area=1 w=w l=l dtemp=dtemp
xdcbx  sub d	nfeti50tdcbx area=1 w=w dtemp=dtemp
*
.model mosinsub nmos level=49 version=3.3  capmod=2
+  mobmod=2  nqsmod=0  noimod=3
+  k1=k1_nfeti50t
+  k2=k2_nfeti50t     k3=2.0000e+01
+  k3b=1.8881e+00     nch=4.2365e+17	 vth0='vth0_nfeti50t+dvthmat'
+  voff=-9.748e-02    dvt0=dvt0_nfeti50t dvt1=3.9767e-01
+  dvt2=2.9419e-01    keta=-4.700e-02
+  pscbe1=4.2400e+08  pscbe2=1.0000e-12
+  alpha0=0.0000e+00  beta0=3.0000e+01
+  dvt0w=0.0000e+00   dvt1w=5.3000e+06	 dvt2w=-3.200e-02
+  ua=3.0000e-13      ub=2.1550e-18	 uc=-2.519e-10
+  u0='uo_nfeti50t*(1+dumat)'
+  dsub=1.0000e+00    eta0=0.0000e+00	 etab=0.0000e+00
+  nfactor=9.6936e-01 em=4.1000e+07	 pclm=5.0000e+00
+  drout=5.0000e-01   a0=1.1234e+00	 a1=0.0000e+00
+  a2=1.0000e+00      pvag=0.0000e+00	 vsat=vsat_nfeti50t
+  ags=4.0927e-01     b0=1.0000e-09	 b1=1.0000e-09
+  pdiblcb=-1.000e-06 pdiblc1=0.0000e+00 pdiblc2=1.0000e-05
+  delta=2.2545e-03   w0=1.0000e-07	 dlc=dlc_nfeti50t
+  dwc=8.0820e-08     dwb=0.0000e+00	 dwg=0.0000e+00
+  ll=0.0000e+00      lw=0.0000e+00	 lwl=0.0000e+00
+  lln=1.0000e+00     lwn=1.0000e+00	 wl=0.0000e+00
+  ww=0.0000e+00      wwl=0.0000e+00	 wln=1.0000e+00
+  wwn=1.0000e+00     tnom=2.5000e+01	 at=3.3000e+04	     ute=-1.944e+00
+  kt1=-3.033e-01     kt2=0.0000e+00	 kt1l=-4.979e-08
+  ua1=1.4093e-09     ub1=-5.546e-18	 uc1=0.0000e+00
+  prt=0.0000e+00
+  cgso=cgso_nfeti50t cgdo=1.0000e-12	 cgbo=0.0000e+00
+  cgdl=9.2410e-10    cgsl=2.4660e-10	 ckappa=3.0000e+00
+  elm=5.0000e+00
+  xpart=5.0000e-01
+  rdsw=0.0000e+00
+  cdsc=1.0000e-03    cdscb=0.0000e+00	 cdscd=0.0000e+00
+  prwb=0.0000e+00    prwg=0.0000e+00	 cit=0.0000e+00
+  tox=tox_nfeti50t   ngate=0.0000e+00	 nlx=3.6340e-07
+  xl=xl_nfeti50t     xw=xw_nfeti50t
+  af=1.4496e+00      kf=6.8551e-26 	 ef=1.0000e+00
+  noia='8.6001e+19*noia_mul'
+  noib='3.3715e+05*noib_mul'
+  noic='-9.324e-12*noic_mul'
+  rd=0.0000e+00      rs=0.0000e+00	 rsh=0.0000e+00
+  rdc=0.0000e+00     rsc=0.0000e+00	 lint=-2.836e-07
+  wint=8.0820e-08    ldif=0.000e+00	 hdif=8.0000e-07
+  xj=3.0000e-07      js=5.4920e-08	 is=0.0
+  n=1.0000e+00	      tlev=0		 tlevc=1
+  jsw=0.0000e+00     cj=cj_nfeti50t	 cjsw=0.0000e+00
+  fc=0.0000e+00      xti=3.0130e+00
+  mj=3.6520e-01      mjsw=3.6520e-01
+  pb=4.4630e-01      pbsw=4.4630e-01
.ends nfeti50t
*
* HV-jfet 1
*
.subckt	 nfeti50tjfet1 d b s
.param w=1e-6  dtemp=0
jnfeti50tjfet1 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta1_nfeti50t/(1+(4.3481e-03)*pdelt)*(w+(5.5430e-06))/(1+(6.3480e-03)*pdelt+(1.0000e-05)*pdelt**2)'
+ vto='vth1_nfeti50t*(1+(4.3481e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti50tjfet1
*
* HV-jfet 2
*
.subckt	 nfeti50tjfet2 d b s
.param w=1e-6  dtemp=0
jnfeti50tjfet2 d b s rnjfetinsub
.model rnjfetinsub  njf level=1
+ beta='beta2_nfeti50t/(1+(4.3481e-03)*pdelt)*(w+(5.5430e-06))/(1+(6.3480e-03)*pdelt+(1.0000e-05)*pdelt**2)'
+ vto='vth2_nfeti50t*(1+(4.3481e-03)*pdelt)'
+ lambda=0.0000e+00
+ is=0.0000e+00	 pb=5.0000e-01
+ cgs=0.0000e+00 rs=0.0000e+00
+ cgd=0.0000e+00 rd=0.0000e+00
.ends nfeti50tjfet2
*
* Parasitic Bipolar
* WAREA = W*1e-6 LAREA=L*1e-6
*
.subckt	 nfeti50tpnp c b e
.param area=1.0	 w=1e-6	 l=1e-6	 dtemp=0
qnfeti50tpnp  c b e  bjtinsub area=area dtemp=dtemp
.model bjtinsub pnp
+ is='4.586e-06*w*1e-06+6.310e-07*w*l+1.859e-16*exp(-2.548e-13/(l*1e-06))'
+ ise='3.583e-05*w*1e-06+1.000e-06*w*l+2.228e-15*exp(-5.129e-13/(l*1e-06))'
+ ikf='2.254e+06*w*1e-06+1.000e-15*l*1e-06'
+ ikr='1.483e+05*w*1e-06'  isc=1.000e-18
+ bf='8.154e+01*exp(4.831e-12/(w*1e-06))+2.871e+01*exp(-3.246e-12/(w*1e-06))'
+ irb=0.000e+00	 br=2.500e+00
+ rb='1.000e-02+1.793e-11/(w*1e-06)'  rbm=1.000e-02
+ re='5.000e+00+2.208e-09/(w*1e-06)'
+ rc='2.000e+01+5.000e-10/(w*1e-06)'
+ nf=1.000e+00	 ne=1.500e+00	nc=1.100e+00
+ nr=1.000e+00	 vaf=1.000e+02	var=1.000e+02
+ tf=1.000e-10	 xtf=3.139e+01
+ itf='1.000e-03+2.515e+10*w*1e-06'
+ vtf=2.000e+01	 ptf=0.000e+00	tr=1.000e-09
+ eg=1.110e+00	 xti=5.000e+00	xtb=1.315e+00
+ cje='((3.486e-04*((w+3.0e-06)*(l+0.95e-06))+6.075e-10*(2*((w+3.0e-06)+l+0.95e-06))))'
+ vje=1.090e+00	 mje=6.500e-01
+ cjc='((6.932e-05*((w+20e-06)*(l+8.45e-06))+7.569e-10*(2*((l+8.45e-06)+(w+20e-06)))))'
+ vjc=9.000e-01	 mjc=3.900e-01	xcjc=5.000e-01
+ cjs=1.000e-19	 vjs=6.600e-01	mjs=1.800e-01
+ tref=2.500e+01
+ af=1.4496e+00	 kf=0.000e+00	fc=7.500e-01
.ends nfeti50tpnp
*
* Parasitic DIODE
* only surface current is modeled
*
.subckt	 nfeti50tdcbx a c
.param area=1.0e-12  w=1e-06  dtemp=0
dnfeti50tdcbx  a c  diodeinsub area=area pj=0  dtemp=dtemp
.model diodeinsub d level=1
+ is='3.733e-15+1.235e-05*w*1e-06'  n=1.000e+00
+ expli=1.000e+12
+ cj=0.000e+00	 m=5.000e-01
+ vj=8.000e-01	 tt=0.000e+00
+ af=1.000e+00	 kf=0.000e+00
+ xti=3.000e+00	 rs=9.419e+01
+ tref=2.500e+01
.ends nfeti50tdcbx
