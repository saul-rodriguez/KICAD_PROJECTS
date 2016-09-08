* Path, Component, Release: cmhv7sf/rel/HSPICE/models/vpnp.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *****************************************************************************
*
*>  IBM CMHV7SF	   HV Bipolar: VPNP
*
*
* *****************************************************************************
.subckt	 vpnp c b e  area=1.0 par=1 dtemp=0
.param
+ mis_hvpnp  = agauss(0,1,1)
+ ismat	     = 'mis_hvpnp*0.001166/sqrt(par)'
+ mise_hvpnp = agauss(0,1,1)
+ isemat     = 'mise_hvpnp*0.0144/sqrt(par)'

qvpnp  c b e  bjtinsub dtemp=dtemp

* Intrinsic bipolar transistor model
.model bjtinsub pnp
+    is='is_hvpnp*(1+ismat)'
+   irb=4.3650e-04     ikf=ikf_hvpnp
+    bf=bf_hvpnp
+    nf=1.0000e+00     ise='1.2960e-14*(1+isemat)'
+    ne=1.6500e+00     vaf=vaf_hvpnp
+   ikr=4.5000e-03	br=1.0000e+00
+    nr=1.0000e+00     isc=5.1630e-15
+    nc=1.0000e+00     var=1.5280e+01
+   rbm=rbm_hvpnp
+    rb=rb_hvpnp
+    re=re_hvpnp	af=1.1300e+00
+    rc=7.1000e+00	kf=1.1149e-15
+    tf=tf_hvpnp       xtf=7.0110e+00
+   itf=1.2310e-01     vtf=2.3900e+01
+   ptf=0.0000e+00	tr=5.0000e-08
+  xcjc=1.0000e+00	eg=1.1100e+00
+   xti=5.5000e+00     xtb=1.4160e+00
+    fc=7.5000e-01     cje=cje_hvpnp
+   vje=5.7000e-01     mje=3.5000e-01
+   cjc=cjc_hvpnp       vjc=6.8140e-01
+   mjc=3.5000e-01     cjs=0.0000e+00
+   vjs=6.2000e-01     mjs=3.8000e-01
+  tref=2.5000e+01
.ends vpnp
