* Path, Component, Release: cmhv7sf/rel/HSPICE/models/hvnwres.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *********************************************************************
*
*>  HV NWell Resistor
*
*
* *********************************************************************
.subckt	 hvnwres d b s
+        w=4.0e-6 l=100.0e-6 dtemp=0
.param
+ mmw_hvnwr = agauss(0,1,1)
+ dmat  = 'mmw_hvnwr*(1.41e-08/sqrt(l*w))'
+ pdelt = 'temper+dtemp-25.0'
 
jhvnwres  d b s	 jfetinsub dtemp=dtemp

.model jfetinsub  njf level=1
+ beta='(beta_hvnwr*(1+dmat)*(w-(wd_hvnwr))/(l-(-1.021e-06))/(1+(5.1490e-03+(1.4770e-05*pdelt))*pdelt))'
+ vto='(-78.74+(1.515e-04/(w-(wd_hvnwr)))+(3.679e-03)*pdelt)'
+ lambda='(-3.500e-07/(l-(-1.021e-06)))'
+ rs=1.0000e+00	 rd=1.0000e+00
+ pb=6.5700e-01	 mj=4.5790e-01
+ n=1.0400e+00
+ is='(5.7350e-07*w*l+5.1480e-12*(w+l))'
+ xti=9.0460e-01
+ cgs='(cgsa_hvnwr*w*l+cgsp_hvnwr*(w+l))'
+ cgd='(cgda_hvnwr*w*l+cgdp_hvnwr*(w+l))'
.ends hvnwres
