 
.param
+ distox = 0
+ s_ntox = 0
+ tox_n      = '4.45n + 0.3n*distox + s_ntox'

+ dnvth0 = 0
* fixcnr = 0 for typical corner!!!
+ fixcnr = 0
+ s_ntox = 0
+ cvth_n = 0
+ s_nvtl = 0
+ vtol_n = '0.045*dnvth0 + (tox_n-4.45n-s_ntox)*7.09E7*(1-fixcnr)'
+ vth0_n = '0.3423 + vtol_n + cvth_n + s_nvtl'
+ mmvth0 = 0

+ dnu0 = 0
+ cu0_n = 0
+ s_nu0 = 0
+ u0_n = 'exp(6.196 + 0.15*dnu0) + cu0_n + s_nu0'

+ mmbeta = 0
+ dnvsat = 0
+ vsat_n = 'exp(11.81258+0.123*dnvsat)' 

+ dnrdsw = 0
+ crds_n = 0
+ rdsw_n = '221.6 + 22.2*dnrdsw + crds_n'    $ Base series res (ohm-um)

+ wtol_n = 0
+ cxw_n = 0
+ cwrx_n = 0
+ wint_n = '0.01u + wtol_n + cxw_n + cwrx_n'         $ Delta W (one side)

+ ltol_n = 0
+ cxl_n = 0
+ clpc_n = 0
+ s_ndel = 0
+ lint_n     = '0.0175u + ltol_n + cxl_n + clpc_n + s_ndel' $ Delta L (one side)

* Stress disabled
+ stipclm = 0
+ stist = 0
+ stipdiblc1 = 0
+ stipdiblc2 = 0
+ stilu0     = 0

* PMOS
+ s_ntox
+ distox = 0
+ tox_p  = '4.6n + 0.3n*distox + s_ntox'

+ dpvth0 = 0
+ cvth_p = 0
+ s_pvtl = 0
+ vtol_p     = '0.045*dpvth0 - (tox_p-4.6n-s_ntox)*7.49E7*(1-fixcnr)'
+ vth0_p     = '-0.4143 + vtol_p + cvth_p - s_pvtl'

+ s_pu0 = 0
+ cu0_p = 0
+ dpu0 = 0
+ u0_p       = 'exp(4.591 + 0.12*dpu0) + cu0_p + s_pu0'  $ Base mobility (cm**2/Vsec)

+ crds_p = 0
+ dprdsw = 0
+ rdsw_p     = '319.9 + 32.0*dprdsw + crds_p'    $ Base series res (ohm-um)

+ cwrx_p = 0
+ cxw_p = 0
+ wtol_p = 0
+ wint_p     = '-0.015u + wtol_p + cxw_p + cwrx_p'       $ Delta W (one side)

+ ltol_p = 0
+ cxl_p = 0
+ clpc_p = 0
+ s_pdel = 0
+ lint_p     = '0.0175u + ltol_p + cxl_p + clpc_p + s_pdel' $ Delta L (one side)

* Flicker noise: statistics function of w, l, nf and multiplicity (par)
+ dnoin = 0
+ noidevan = 1.8e-11               $ Area, 1/f statistics (meter*2)
*+ noistdn = 1.0500                 $ 3-sigma log noise distribution
*+  noi_scale='noistdn-min(log(sqrt(w*l*nf*par/noidevan)),0)'
*+  noi_mul='exp(dnoin*noi_scale)'
+ noi_mul = 1

+ cgdo_n = 330p 
+ cgso_n = 330p
+ n_spec = 1
+ s_novc = 0
+ dncgov = 0
+ cgsl_n     = '330p*n_spec + s_novc + 40p*dncgov'   $ G/S covlp at 0V (F/m)
+ s_novc = 0
+ dncgov = 0
+ cgdl_n     = '330p*n_spec + s_novc + 40p*dncgov'   $ G/D covlp at 0V (F/m)

+   cgso_p     = 17p                         $ G/S overlap cap offset (F/meter)
+   cgdo_p     = 17p                         $ G/D overlap cap offset (F/meter)
+   s_povc = 0
+   dpcgov = 0
+   cgsl_p     = '333p*n_spec + s_povc + 40p*dpcgov'   $ G/S covlp at 0V (F/m)
+   cgdl_p     = '333p*n_spec + s_povc + 40p*dpcgov'   $ G/D covlp at 0V (F/m)

+   js_n       = 80n                         $ N+ Area Sat Cur (A/meter**2)
+   jsw_n      = 50f                         $ N+ Sidewall Sat Cur (A/meter)
+   n_n        = 1.02                        $ Ideality
+   cj_nstd    = '0.85m*n_spec + 0'       $ N+ Diode Cap (F/m**2)
+   cj_n       = 'cj_nstd'
+   pb_n       = '0.61'        $ Voltage dependence
+   mj_n       = '0.43'
+   cjsw_n     = '145p' $ N+ STI Sidewall Cap (F/meter)
+   pbsw_n     = '0.42'      $ Voltage dependence
+   mjsw_n     = '0.32'
+   cjsg_n     = '435p'        $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_n     = 1.0                         $ Voltage dependence
+   mjsg_n     = 0.63
+   cta_n      = 1.0m                        $ Cap temperature dependence
+   pta_n      = 0.7m
+   ctp_n      = 1.6m
+   ptp_n      = 0.3m
+   tcjsg_n    = 0.9m






