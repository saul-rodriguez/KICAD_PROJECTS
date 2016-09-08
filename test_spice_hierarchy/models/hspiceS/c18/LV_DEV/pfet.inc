* Path, Component, Release: cmos7base/rel/HSPICE/models/pfet.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL	 pfet	1.8V PFET subcircuit
*
***************************************************************************
*
*  SYNTAX:  xxx ( d g s b ) pfet l=nnn w=nnn
*
*  REQUIRED:
*	     +	      w = nnn  <- Design width of RX (meters)
*	     +	      l = nnn  <- Design length of PC (meters)
*  OPTIONAL:
*	     +	     as = 0    <- Source diffusion area (meters^2)
*	     +	     ad = 0    <- Drain diffusion area (meters^2)
*	     +	     ps = 0    <- Source diffusion perimeter in (meters)
*	     +	     pd = 0    <- Drain diffusion perimeter in (meters)
*	     +	    nrd = 0    <- Number of squares of drain diffusion
*	     +	    nrs = 0    <- Number of squares of source diffusion
*	     +	  dtemp = 0    <- Device temp rise from ambient (deg C)
*	     +	     nf = 1    <- number of gate stripes or "fingers" in device
*	     +	m (par) = 1    <- number of parallel instances (multiplicity)
*	     +	   gcon = 1    <- Gate connection switch (1->single-ended,
*							  2->double-ended)
*	     +	    rsx = 50   <- body resistance
*	     +	     rf = 0    <- RF device flag (0-> pfet pcell
*						  1-> pfet_rf pcell)
*            +      gns = 0    <- ESD hierarchical cell layout option
*                                 (0-> silicided gate, 1-> non-silicided gate)
*
*  NOTES:
*
*  1. If nrd or nrs are not passed to the model they will default to 0.
*     This will result in 0 ohms of silicided S/D resistance being placed
*     in series with the device model.
*
*  2. Intrinsic FET model includes PC bounded perimeter only.
*
* SUBCIRCUIT SCHEMATIC:
*
*		cwgd		 drain
*	  _______| |_______________O__
*	 |	 | |		   |  |
*	 |			   |  |
*	 |			   /  |
*	 |		    rdext  \  |	 Ddb (Includes internal FET drain area
*	 |			   /  |	      and STI bounded perimeter)
*	 |		       d1  |__|___|\|__________
*	 |			   |  |	  |/|	       |
*	 |			   |  |		       |
*	 |			   |  |		       |
*	 |		       ____|  |		       |
*    gate|		g1  | |	      |	       |  b1   |	    bulk
*	 O-------\/\/\/-----| |	     ---       |-------o---\/\/\/----O
*	 |	  rgate	    | |____  --- cwds  |       |     rsb
*	 |			   |  |		       |
*	 |			   |  |		       |
*	 |			   |  |		       |
*	 |		       s1  |__|___|\|__________|
*	 |			   |  |	  |/|
*	 |			   \  |
*	 |		    rsext  /  |	 Dsb (Includes internal FET source area
*	 |			   \  |	      and STI bounded perimeter)
*	 |			   |  |
*	 |_______| |_______________|__|
*		 | |		   O
*		cwgs		 source
*
*
***************************************************************************
.subckt pfet  d g s b  w=0 l=0 nf=1 as=0 ad=0 ps=0 pd=0 nrd=0 nrs=0
+		       gcon=1 rsx=50 dtemp=0 rf=0 par=1 gns=0
*
.param
+  zad=ad zas=as znrd=nrd znrs=nrs zpd=pd zps=ps
* Gate bounded perimeter (identical for source and drain)
+  pgate = '(w+ndelrx)'
*
* STI S/D bounded perimeter (subtract gate bounded from total passed in)
+  pstis = 'max(0,(zps-pgate))'
+  pstid = 'max(0,(zpd-pgate))'
*
* Mis-match calculations: function of w, l, nf and multiplicity (par)
+  kvt = 0.7135e-8  kvtw =  0.06u   kvtl = 0.121u
+  kmb = 2.3072e-6  kmbw = -1.36u   kmbl = -3.155u
+  sigvth='kvt/sqrt((w-kvtw)*nf*par*(l-kvtl))'
+  sigbeta='kmb/sqrt((w-kmbw)*nf*par*(l-kmbl))'
+  mmvth0=agauss(0,sigvth,3)	    $ vth0 mis-match
+  mmbeta=agauss(0,sigbeta,3)	    $ beta mis-match
+  mmbody=0
*
* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+  noi_scale='noistdp-min(log(sqrt(w*l*nf*par/noidevap)),0)'
+  noi_mul='exp(dnoip*noi_scale)'
*
* Gate resistance calculation for all cases (function of w, l and nf)
+  rge1='((pcrsi*(1-gns)+oppcrsf*gns)/(nf*gcon))*((0.42u+w/(3*gcon))/(l+lwbpc))'
+  rgw1='(27.227*(((w-2*wint_p)*nf*1e6)**(-0.55)))'
+  rgl1='(10e6*(l-2*lint_p)+0.1324)/1.665'
*
* Gate capacitance calculation for rf=1 case (function of w, l and nf)
+  cgw1='1.2*(85.5e-12*w*nf+0.4135e-15)'
+  cgl1='(23426e-12*l+12.428e-15)/14.09e-15'
*
* Drain-Source Capacitance Calculation for rf=1 case (function of w, l and nf)
+  cdsw1='0.2*(6e-12*w*nf + 0.03e-15)'
+  cdsl1='(0.1029e-12/(l**2) - 0.1228e-6/l + 15.011)'
*
* Substrate resistance calculation for rf=1 case (function of w, l and nf)
+  rsw1='0.3*(1062.3*(((w-2*wint_p)*nf*1e6)**(-0.7)))'
+  rsl1='(11e6*(l-2*lint_p)+28.42)/30.307'
*
* External resistance term calculation for rf=1 case (function of w, l and nf)
+  rxw1='(27.132*((w*nf*1e6)**(-0.6064)))'
+  rxl1='(3.078e6*l+0.8425)/1.25'
*
m0 d1 g1 s1 b1 pch     w=w l=l as=1e-15 ad=1e-15 ps=pgate pd=pgate
+		       nrd=0 nrs=0 m=nf dtemp=dtemp
rdext  d1   d r='(znrd*rsh_p/nf)+ rf*(rxw1*rxl1)'
rsext  s1   s r='(znrs*rsh_p/nf)+ rf*(rxw1*rxl1)'
rgate  g1   g r='(rge1+rgw1*rgl1)'
rsb	b  b1 r='((1-rf)*rsx + rf*rsl1*rsw1)'
cwgd	g   d c='1e-18+rf*(cgw1*cgl1)'
cwgs	g   s c='1e-18+rf*(cgw1*cgl1)'
cwds	d   s c='1e-18+rf*(cdsw1*cdsl1)'
ddb    d1  b1 pdio area=zad pj=pstid m=nf dtemp=dtemp
dsb    s1  b1 pdio area=zas pj=pstis m=nf dtemp=dtemp
***************************************************************************
* PFET BSIM3v3.2.4 Model
***************************************************************************
.model pch pmos (	  level	  = 49		   version = 3.24
+tnom	 = 25		  tox	  = tox_p	   mobmod  = 1
+xj	 = 2e-7		  nch	  = 3e17	   vth0	   = 'vth0_p+mmvth0'
+k1	 = 0.669593	  k2	  = -0.0372971	   k3	   = -4.13281
+k3b	 = 5		  w0	  = 4.12017e-8	   nlx	   = 1.82384e-8
+dvt0w	 = 0.443837	  dvt1w	  = 9.98979e6	   dvt2w   = 0.0839596
+dvt0	 = 0.444071	  dvt1	  = 0.90259	   dvt2	   = -1.2310
+wk3b	 = 0		  u0	  = 'u0_p+mmbeta'  ua	   = 1.44199e-10
+ub	 = 1.4409e-18	  uc	  = -1.476e-10	   vsat	   = 1.89e5
+a0	 = 1.045	  ags	  = 0.4095	   b0	   = 1.9e-6
+b1	 = 4.877e-6	  keta	  = -0.0581015	   a1	   = 0.004582
+a2	 = 0.42		  rdsw	  = rdsw_p	   prwg	   = 4.441e-17
+prwb	 = 0.263712	  wr	  = 1		   wint	   = wint_p
+lint	 = lint_p	  lvsat	  = -4.441e-10	   dwg	   = -1.687e-8
+dwb	 = -4.441e-10	  voff	  = -0.132145	   nfactor = 0.9
+cit	 = 0		  cdsc	  = 0		   cdscd   = 0.001698
+cdscb	 = 0.000871	  eta0	  = 0.335	   etab	   = -0.1
+dsub	 = 1.15		  pclm	  = 1.55	   pdiblc1 = 0.003
+pdiblc2 = 0.001343	  pdiblcb = -0.6	   drout   = 0.04647
+pscbe1	 = 3e8		  pscbe2  = 3.6085e-7	   pvag	   = 4.967
+delta	 = 0.005655	  ngate	  = 1e20	   alpha0  = 2.19e-9
+alpha1	 = 0.03013	  beta0	  = 14.4	   lrdsw   = -45.874
+wuc	 = -2.15e-11	  wketa	  = 0.01	   wu0	   = -7.246
+wl	 = -9.14843e-16	  wln	  = 1		   pags	   = 0
+ww	 = -7.04235e-15	  wwn	  = 1.00521	   wwl	   = 1.65e-21
+ll	 = 0		  lln	  = 0		   lw	   = -6.32538e-22
+lwn	 = 0		  lwl	  = 0		   lua	   = 1e-15
+lub	 = 4.207e-20	  luc	  = 3.625e-11	   lu0	   = -0.9
+lags	 = 0.1887	  paramchk= 0		   binunit = 1
*
***************************************************************************
* Source/Drain Diode Parameters
***************************************************************************
+acm	 = 2		  tlev	  = 0		   tlevc   = 1
+eg	 = 1.17		  gap1	  = 4.73E-4	   gap2	   = 636
+cj	 = cj_p		  pb	  = pb_p	   mj	   = mj_p
+cjsw	 = cjsg_p	  php	  = pbsg_p	   mjsw	   = mjsg_p
+cjgate	 = cjsg_p	  xti	  = 3		   n	   = n_p
+js	 = js_p		  jsw	  = jsw_p	   hdif	   = 0
+rsh	 = 0		  tcjswg  = tcjsg_p	   tpbswg  = tpbsg_p
*
***************************************************************************
* Capacitance-Voltage (CV) Parameters
***************************************************************************
+capmod = 2		  xpart	  = 0		  acde	  = 1.2
+cgso	= cgso_p	  cgdo	  = cgdo_p	  cgbo	  = 4.062e-11
+cgsl	= cgsl_p	  cgdl	  = cgdl_p	  ckappa  = 4.3221
+cf	= 0		  dlc = 'lint_p+2.8e-8'	  dwc	  = wint_p
+llc	= 0		  lwc	  = 0		  lwlc	  = 0
+wlc	= 0		  wwc	  = 0		  wwlc	  = 0
*
***************************************************************************
* Jds/Vt Temperature Parameters
***************************************************************************
+prt	 = 0		  at	  = 4e4		   lute	   = 0.07
+ute	 = -1.81	  kt1	  = -0.308882	   kt1l	   = 1.56523e-8
+kt2	 = -0.0529747	  ua1	  = -6.10084e-10   ub1	   = -1.7637e-18
+uc1	 = 5.57702e-12	  wute	  = -0.05349
*
***************************************************************************
* Flicker Noise Parameters
***************************************************************************
+noimod = 2		   noia = '9.62e+18*noi_mul'  noib = '1.38e6*noi_mul'
+noic = '9.86e-12*noi_mul' em	  = 1.17e+8	      af   = 1
+ef	= 1.265		   kf	  = 0	  )
*
***************************************************************************
* Extrinsic Source/Drain Diode Model
***************************************************************************
.model pdio    d (	  level	  = 1		   tref	   = 25
+xti	 = 3		  tlev	  = 0		   tlevc   = 1
+eg	 = 1.17		  gap1	  = 4.73E-4	   gap2	   = 636
+js	 = js_p		  jsw	  = jsw_p	   n	   = n_p
+cj	 = cj_p		  pb	  = pb_p	   mj	   = mj_p
+cjsw	 = cjsw_p	  php	  = pbsw_p	   mjsw	   = mjsw_p
+rs	 = 120p		  cta	  = cta_p	   ctp	   = ctp_p
+tpb	 = pta_p	  tphp	  = ptp_p )
*
***************************************************************************
.ends pfet
