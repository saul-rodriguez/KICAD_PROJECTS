* Path, Component, Release: cmhv7sf/rel/HSPICE/models/process_hv.inc, 7hv_models, pcad_7hv_V121x
* CMVC Revision: 1.14 12/12/05 12:41:44
*
***********************************************************************
*
*>  IBM CMHV7SF	 Process / Device Parameters Defintions
*		 High Voltage MOSFET and Parasitic Devices
*
* IBM CONFIDENTIAL
* (C) 2012 IBM Corporation
* Licensed Materials - Property of IBM
* US Government Users Restricted Rights - Use, duplication or disclosure
* restricted by GSA ADP Schedule contract with IBM Corporation.
*
***********************************************************************
.lib hvstats
*
.param
***********************************************************************
*
* Statistical and Corner Analysis Selections
*     Note: Corners and Monte Carlo mutually exclusive
* Translate Corner Value to Distribution "Sigma" ( divide by 3 )
*
***********************************************************************
*
+  cnr_hv_nfet	= '(1-mc_sw) * (cor_hv_nmos*(1-fixcnrhv))/3'
+  cnr_hv_pfet	= '(1-mc_sw) * (cor_hv_pmos*(1-fixcnrhv))/3'
+  cnr_hv_res	= '(1-mc_sw) * (cor_hv_res*(1-fixcnrhvr))/3'
+  cnr_hv_bip	= '(1-mc_sw) * (cor_hv_bip*(1-fixcnrhvb))/3'
+  cnr_hv_diode = '(1-mc_sw) * cor_hv_diode/3'
*
+  cnr_hv_noin  = '(1-mc_sw) * cor_hv_noin/3'
+  cnr_hv_noip  = '(1-mc_sw) * cor_hv_noip/3'
*
***********************************************************************
*
* Link LV and HV Gate Oxide Parameters
*
***********************************************************************
+  deltgoxn = '3.0e-10 * distoxt * (1-fixcnrhv)'
+  deltgoxp = '3.0e-10 * distoxt * (1-fixcnrhv)'
+  deltmoxn = '8.0e-10 * distoxm * (1-fixcnrhv)'
+  deltmoxp = '8.0e-10 * distoxm * (1-fixcnrhv)'
+  delthoxn = '4.0e-09 * distoxh * (1-fixcnrhv)'
+  delthoxp = '4.0e-09 * distoxh * (1-fixcnrhv)'
*
***********************************************************************
*
* BSIM3 Device Models
*
***********************************************************************
*
*					    NFETI20T
.param
+  xnfi20txw	= agauss(cnr_hv_nfet,1,3)
+  dnfi20txw	= xnfi20txw
+  xnfi20tvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20tvth0	= xnfi20tvth0
+  xnfi20tvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnfi20tvt0 	= xnfi20tvt0
+  xnfi20tcgso	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20tcgso	= xnfi20tcgso
+  xnfi20tcgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnfi20tcgdx1 = xnfi20tcgdx1
+  xnfi20tbeta	= agauss(cnr_hv_nfet,1,3)
+  dnfi20tbeta	= xnfi20tbeta
+  dnfi20tvth1	= '-dnfi20tbeta'
+  dnfi20tvth2	= '-dnfi20tbeta'
+  dnfi20tbeta1 = dnfi20tbeta
+  dnfi20tbeta2 = dnfi20tbeta
+  dnfi20trj	= '-dnfi20tbeta'
+  xnfi20tcj	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20tcj	= xnfi20tcj
+  xnfi20tdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20tdlc	= xnfi20tdlc
+  xnfi20tk1	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20tk1	= xnfi20tk1
+  xnfi20tk2	= agauss(cnr_hv_nfet,1,3)
+  dnfi20tk2	= xnfi20tk2
+  xnfi20tvsat	= agauss(cnr_hv_nfet,1,3)
+  dnfi20tvsat	= xnfi20tvsat
+  xnfi20tuo	= agauss(cnr_hv_nfet,1,3)
+  dnfi20tuo	= xnfi20tuo
+  xnfi20txl	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20txl	= xnfi20txl
+  xnfi20tnoi	= agauss('-cnr_hv_noin',1,3)
+  dnfi20tnoi	= xnfi20tnoi
*
+  tox_nfeti20t	  = '4.4500e-09 + deltgoxn + dtox_nfeti20t_fc'
+  vth0_nfeti20t  = '3.3897e-01 + 3.390e-02*dnfi20tvth0 + 11.03e+7*(tox_nfeti20t-4.45n) + dvth0_nfeti20t_fc'
+  dvt0_nfeti20t  = '4.7500e+01 + 14.7124*dnfi20tvt0 + ddvt0_nfeti20t_fc'
+  cgso_nfeti20t  = '1.7070e-10 + 2.0500e-11*dnfi20tcgso + dcgso_nfeti20t_fc'
+  dlc_nfeti20t	  = '-7.720e-07 + 1.6625e-07*dnfi20tdlc + ddlc_nfeti20t_fc'
+  k1_nfeti20t	  = '0.7982 + 0*dnfi20tk1 + dk1_nfeti20t_fc'
+  k2_nfeti20t	  = '-1.338e-01 + 0*dnfi20tk2 + dk2_nfeti20t_fc'
+  vsat_nfeti20t  = '1.1945e+05 + 23.89e+03*dnfi20tvsat + dvsat_nfeti20t_fc'
+  cj_nfeti20t	  = '9.0520e-04 + 1.0870e-04*dnfi20tcj + dcj_nfeti20t_fc'
+  rj_nfeti20t	  = '1.3498 + 4.050e-02*dnfi20trj + drj_nfeti20t_fc'
+  cgdx1_nfeti20t = '3.75e-10 + 4.50e-11*dnfi20tcgdx1 + dcgdx1_nfeti20t_fc'
+  beta1_nfeti20t = '16.359 + 1.636*dnfi20tbeta1 + dbeta1_nfeti20t_fc'
+  beta2_nfeti20t = '4.6923 + 0.4692*dnfi20tbeta2 + dbeta2_nfeti20t_fc'
+  vth1_nfeti20t  = '-3.011 + 4.517e-01*dnfi20tvth1 + dvth1_nfeti20t_fc'
+  vth2_nfeti20t  = '-5.210 + 2.605e-01*dnfi20tvth2 + dvth2_nfeti20t_fc'
+  uo_nfeti20t	  = '385.32 + 11.559*dnfi20tuo + duo_nfeti20t_fc'
+  xl_nfeti20t	  = '0 + 0*dnfi20txl + dxl_nfeti20t_fc'
+  xw_nfeti20t	  = '0 + 0*dnfi20txw + dxw_nfeti20t_fc'
*
*					    PFET20T
.param
+  xpf20txw    = agauss(cnr_hv_pfet,1,3)
+  dpf20txw    = xpf20txw
+  xpf20tvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf20tvth0  = xpf20tvth0
+  xpf20tvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf20tvt0   = xpf20tvt0
+  xpf20tcgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf20tcgso  = xpf20tcgso
+  xpf20tcgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf20tcgdx1 = xpf20tcgdx1
+  xpf20tbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf20tbeta  = xpf20tbeta
+  dpf20tvth1  = '-dpf20tbeta'
+  dpf20tvth2  = '-dpf20tbeta'
+  dpf20tbeta1 = dpf20tbeta
+  dpf20tbeta2 = dpf20tbeta
+  dpf20trj    = '-dpf20tbeta'
+  xpf20tcj    = agauss('-cnr_hv_pfet',1,3)
+  dpf20tcj    = xpf20tcj
+  xpf20tdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf20tdlc   = xpf20tdlc
+  xpf20tk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf20tk1    = xpf20tk1
+  xpf20tk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf20tk2    = xpf20tk2
+  xpf20tvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf20tvsat  = xpf20tvsat
+  xpf20tuo    = agauss(cnr_hv_pfet,1,3)
+  dpf20tuo    = xpf20tuo
+  xpf20txl    = agauss('-cnr_hv_pfet',1,3)
+  dpf20txl    = xpf20txl
+  xpf20tnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf20tnoi   = xpf20tnoi
*
+  tox_pfet20t	 = '4.6000e-09 + deltgoxp + dtox_pfet20t_fc'
+  vth0_pfet20t	 = '-3.736e-01 + 5.2696e-02*dpf20tvth0 - 3.4e+7*(tox_pfet20t-4.6n) + dvth0_pfet20t_fc'
+  dvt0_pfet20t  = '1.2893 + 0.1758*dpf20tvt0 + ddvt0_pfet20t_fc'
+  cgso_pfet20t	 = '1.0690e-10 + 1.2815e-11*dpf20tcgso + dcgso_pfet20t_fc'
+  cgdx1_pfet20t = '2.50e-10 + 3.00e-11*dpf20tcgdx1 + dcgdx1_pfet20t_fc'
+  vth1_pfet20t	 = '-1.000e+01 + 1.50*dpf20tvth1 + dvth1_pfet20t_fc'
+  vth2_pfet20t	 = '-1.219e+01 + 3.657*dpf20tvth2 + dvth2_pfet20t_fc'
+  beta1_pfet20t = '2.1136 + 0.2114*dpf20tbeta1 + dbeta1_pfet20t_fc'
+  beta2_pfet20t = '8.6055e-01 + 4.303e-02*dpf20tbeta2 + dbeta2_pfet20t_fc'
+  rj_pfet20t	 = '3.1463 + 9.439e-01*dpf20trj + drj_pfet20t_fc'
+  cj_pfet20t	 = '1.1670e-03 + 1.40e-04*dpf20tcj + dcj_pfet20t_fc'
+  dlc_pfet20t	 = '-3.208e-07 + 8.25e-08*dpf20tdlc + ddlc_pfet20t_fc'
+  k1_pfet20t	 = '9.3422e-01 + 7.840e-02*dpf20tk1 + dk1_pfet20t_fc'
+  k2_pfet20t	 = '-1.758e-01 + 1.505e-02*dpf20tk2 + dk2_pfet20t_fc'
+  vsat_pfet20t	 = '1.1404e+05 + 0*dpf20tvsat + dvsat_pfet20t_fc'
+  uo_pfet20t	 = '102.36 + 7.165*dpf20tuo + duo_pfet20t_fc'
+  xl_pfet20t	 = '0 + 0*dpf20txl + dxl_pfet20t_fc'
+  xw_pfet20t	 = '0 + 0*dpf20txw + dxw_pfet20t_fc'
*
*					    NFETI50T
.param
+  xnfi50txw	= agauss(cnr_hv_nfet,1,3)
+  dnfi50txw	= xnfi50txw
+  xnfi50tvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50tvth0	= xnfi50tvth0
+  xnfi50tvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnfi50tvt0 	= xnfi50tvt0
+  xnfi50tcgso	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50tcgso	= xnfi50tcgso
+  xnfi50tcgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnfi50tcgdx1 = xnfi50tcgdx1
+  xnfi50tbeta	= agauss(cnr_hv_nfet,1,3)
+  dnfi50tbeta	= xnfi50tbeta
+  dnfi50tvth1	= '-dnfi50tbeta'
+  dnfi50tvth2	= '-dnfi50tbeta'
+  dnfi50tbeta1 = dnfi50tbeta
+  dnfi50tbeta2 = dnfi50tbeta
+  dnfi50trj	= '-dnfi50tbeta'
+  xnfi50tcj	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50tcj	= xnfi50tcj
+  xnfi50tdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50tdlc	= xnfi50tdlc
+  xnfi50tk1	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50tk1	= xnfi50tk1
+  xnfi50tk2	= agauss(cnr_hv_nfet,1,3)
+  dnfi50tk2	= xnfi50tk2
+  xnfi50tvsat	= agauss(cnr_hv_nfet,1,3)
+  dnfi50tvsat	= xnfi50tvsat
+  xnfi50tuo	= agauss(cnr_hv_nfet,1,3)
+  dnfi50tuo	= xnfi50tuo
+  xnfi50txl	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50txl	= xnfi50txl
+  xnfi50tnoi	= agauss('-cnr_hv_noin',1,3)
+  dnfi50tnoi	= xnfi50tnoi
*
+  tox_nfeti50t	  = '4.4500e-09 + deltgoxn + dtox_nfeti50t_fc'
+  vth0_nfeti50t  = '3.3520e-01 + 3.1198e-02*dnfi50tvth0 + 11.88e+7*(tox_nfeti50t-4.45n) + dvth0_nfeti50t_fc'
+  dvt0_nfeti50t  = '1.5006e+02 + 53.224*dnfi50tvt0 + ddvt0_nfeti50t_fc'
+  cgso_nfeti50t  = '2.1490e-10 + 2.5800e-11*dnfi50tcgso + dcgso_nfeti50t_fc'
+  dlc_nfeti50t	  = '-8.063e-07 + 1.7700e-07*dnfi50tdlc + ddlc_nfeti50t_fc'
+  k1_nfeti50t	  = '0.84736 + 0*dnfi50tk1 + dk1_nfeti50t_fc'
+  k2_nfeti50t	  = '-1.572e-01 + 0*dnfi50tk2 + dk2_nfeti50t_fc'
+  vsat_nfeti50t  = '1.9314e+05 + 0*dnfi50tvsat + dvsat_nfeti50t_fc'
+  cj_nfeti50t	  = '9.0520e-04 + 1.0870e-04*dnfi50tcj + dcj_nfeti50t_fc'
+  rj_nfeti50t	  = '3.8884 + 1.9442e-01*dnfi50trj + drj_nfeti50t_fc'
+  cgdx1_nfeti50t = '6.25e-10 + 7.50e-11*dnfi50tcgdx1 + dcgdx1_nfeti50t_fc'
+  beta1_nfeti50t = '3.9911 + 0.7513*dnfi50tbeta1 + dbeta1_nfeti50t_fc'
+  beta2_nfeti50t = '0.57046 + 5.705e-02*dnfi50tbeta2 + dbeta2_nfeti50t_fc'
+  vth1_nfeti50t  = '-4.285 + 9.6250e-02*dnfi50tvth1 + dvth1_nfeti50t_fc'
+  vth2_nfeti50t  = '-14.88 + 6.6696e-01*dnfi50tvth2 + dvth2_nfeti50t_fc'
+  uo_nfeti50t	  = '383.78 + 15.3512*dnfi50tuo + duo_nfeti50t_fc'
+  xl_nfeti50t	  = '0 + 0*dnfi50txl + dxl_nfeti50t_fc'
+  xw_nfeti50t	  = '0 + 0*dnfi50txw + dxw_nfeti50t_fc'
*
*					    PFET50T
.param
+  xpf50txw    = agauss(cnr_hv_pfet,1,3)
+  dpf50txw    = xpf50txw
+  xpf50tvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf50tvth0  = xpf50tvth0
+  xpf50tvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf50tvt0   = xpf50tvt0
+  xpf50tcgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf50tcgso  = xpf50tcgso
+  xpf50tcgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf50tcgdx1 = xpf50tcgdx1
+  xpf50tbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf50tbeta  = xpf50tbeta
+  dpf50tvth1  = '-dpf50tbeta'
+  dpf50tvth2  = '-dpf50tbeta'
+  dpf50tbeta1 = dpf50tbeta
+  dpf50tbeta2 = dpf50tbeta
+  dpf50trj    = '-dpf50tbeta'
+  xpf50tcj    = agauss('-cnr_hv_pfet',1,3)
+  dpf50tcj    = xpf50tcj
+  xpf50tdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf50tdlc   = xpf50tdlc
+  xpf50tk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf50tk1    = xpf50tk1
+  xpf50tk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf50tk2    = xpf50tk2
+  xpf50tvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf50tvsat  = xpf50tvsat
+  xpf50tuo    = agauss(cnr_hv_pfet,1,3)
+  dpf50tuo    = xpf50tuo
+  xpf50txl    = agauss('-cnr_hv_pfet',1,3)
+  dpf50txl    = xpf50txl
+  xpf50tnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf50tnoi   = xpf50tnoi
*
+  tox_pfet50t	 = '4.6000e-09 + deltgoxp + dtox_pfet50t_fc'
+  vth0_pfet50t	 = '-3.881e-01 + 5.0453e-02*dpf50tvth0 - 5.4e+7*(tox_pfet50t-4.6n) + dvth0_pfet50t_fc'
+  dvt0_pfet50t  = '1.2300 + 0.1625*dpf50tvt0 + ddvt0_pfet50t_fc'
+  cgso_pfet50t	 = '1.6290e-10 + 1.9500e-11*dpf50tcgso + dcgso_pfet50t_fc'
+  cgdx1_pfet50t = '5.50e-10 + 6.60e-11*dpf50tcgdx1 + dcgdx1_pfet50t_fc'
+  vth1_pfet50t	 = '-8.916 + 0.6554*dpf50tvth1 + dvth1_pfet50t_fc'
+  vth2_pfet50t	 = '-1.095e+01 + 2.19*dpf50tvth2 + dvth2_pfet50t_fc'
+  beta1_pfet50t = '1.2058 + 8.441e-02*dpf50tbeta1 + dbeta1_pfet50t_fc'
+  beta2_pfet50t = '4.8743e-01 + 2.4385e-02*dpf50tbeta2 + dbeta2_pfet50t_fc'
+  rj_pfet50t	 = '6.1857 + 1.8557*dpf50trj + drj_pfet50t_fc'
+  cj_pfet50t	 = '1.1670e-03 + 1.40e-04*dpf50tcj + dcj_pfet50t_fc'
+  dlc_pfet50t	 = '-3.296e-07 + 8.45e-08*dpf50tdlc + ddlc_pfet50t_fc'
+  k1_pfet50t	 = '9.1941e-01 + 9.369e-02*dpf50tk1 + dk1_pfet50t_fc'
+  k2_pfet50t	 = '-1.729e-01 + 1.825e-02*dpf50tk2 + dk2_pfet50t_fc'
+  vsat_pfet50t	 = '6.2629e+04 + 0*dpf50tvsat + dvsat_pfet50t_fc'
+  uo_pfet50t	 = '102.13 + 6.128*dpf50tuo + duo_pfet50t_fc'
+  xl_pfet50t	 = '0 + 0*dpf50txl + dxl_pfet50t_fc'
+  xw_pfet50t	 = '0 + 0*dpf50txw + dxw_pfet50t_fc'
*
*					    NFET20MH
.param
+  xnf20mhxw	= agauss(cnr_hv_nfet,1,3)
+  dnf20mhxw	= xnf20mhxw
+  xnf20mhvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnf20mhvth0	= xnf20mhvth0
+  xnf20mhvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnf20mhvt0 	= xnf20mhvt0
+  xnf20mhcgso	= agauss('-cnr_hv_nfet',1,3)
+  dnf20mhcgso	= xnf20mhcgso
+  xnf20mhcgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnf20mhcgdx1 = xnf20mhcgdx1
+  xnf20mhbeta	= agauss(cnr_hv_nfet,1,3)
+  dnf20mhbeta	= xnf20mhbeta
+  dnf20mhvth1	= '-dnf20mhbeta'
+  dnf20mhvth2	= '-dnf20mhbeta'
+  dnf20mhbeta1 = dnf20mhbeta
+  dnf20mhbeta2 = dnf20mhbeta
+  dnf20mhrj	= '-dnf20mhbeta'
+  xnf20mhcj	= agauss('-cnr_hv_nfet',1,3)
+  dnf20mhcj	= xnf20mhcj
+  xnf20mhdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnf20mhdlc	= xnf20mhdlc
+  xnf20mhk1	= agauss('-cnr_hv_nfet',1,3)
+  dnf20mhk1	= xnf20mhk1
+  xnf20mhk2	= agauss(cnr_hv_nfet,1,3)
+  dnf20mhk2	= xnf20mhk2
+  xnf20mhvsat	= agauss(cnr_hv_nfet,1,3)
+  dnf20mhvsat	= xnf20mhvsat
+  xnf20mhuo	= agauss(cnr_hv_nfet,1,3)
+  dnf20mhuo	= xnf20mhuo
+  xnf20mhxl	= agauss('-cnr_hv_nfet',1,3)
+  dnf20mhxl	= xnf20mhxl
+  xnf20mhnoi	= agauss('-cnr_hv_noin',1,3)
+  dnf20mhnoi	= xnf20mhnoi
*
+  tox_nfet20mh	  = '1.2600e-08 + deltmoxn + dtox_nfet20mh_fc'
+  vth0_nfet20mh  = '6.4658e-01 + 5.1726e-02*dnf20mhvth0 + 5.834e+7*(tox_nfet20mh-12.6n) + dvth0_nfet20mh_fc'
+  dvt0_nfet20mh  = '1.2560e+01 + 3.768*dnf20mhvt0 + ddvt0_nfet20mh_fc'
+  cgso_nfet20mh  = '8.0940e-11 + 9.7100e-12*dnf20mhcgso + dcgso_nfet20mh_fc'
+  dlc_nfet20mh	  = '-4.000e-07 + 1.1200e-07*dnf20mhdlc + ddlc_nfet20mh_fc'
+  k1_nfet20mh	  = '1.1625 + 7.9500e-02*dnf20mhk1 + dk1_nfet20mh_fc'
+  k2_nfet20mh	  = '-7.651e-02 + 7.3500e-04*dnf20mhk2 + dk2_nfet20mh_fc'
+  vsat_nfet20mh  = '1.7427e+05 + 3.4850e+04*dnf20mhvsat + dvsat_nfet20mh_fc'
+  cj_nfet20mh	  = '7.2560e-04 + 8.7100e-05*dnf20mhcj + dcj_nfet20mh_fc'
+  rj_nfet20mh	  = '2.4706 + 6.7290e-01*dnf20mhrj + drj_nfet20mh_fc'
+  cgdx1_nfet20mh = '2.50e-10 + 3.00e-11*dnf20mhcgdx1 + dcgdx1_nfet20mh_fc'
+  beta1_nfet20mh = '3.2048e+01 + 7.371*dnf20mhbeta1 + dbeta1_nfet20mh_fc'
+  beta2_nfet20mh = '1.3992e+01 + 3.498*dnf20mhbeta2 + dbeta2_nfet20mh_fc'
+  vth1_nfet20mh  = '-4.288 + 0.1286*dnf20mhvth1 + dvth1_nfet20mh_fc'
+  vth2_nfet20mh  = '-4.628 + 0.1388*dnf20mhvth2 + dvth2_nfet20mh_fc'
+  uo_nfet20mh	  = '498.33 + 9.967*dnf20mhuo + duo_nfet20mh_fc'
+  xl_nfet20mh	  = '0 + 0.11e-6*dnf20mhxl + dxl_nfet20mh_fc'
+  xw_nfet20mh	  = '0 + 0*dnf20mhxw + dxw_nfet20mh_fc'
*
*					    NFETI25M
.param
+  xnfi25mxw	= agauss(cnr_hv_nfet,1,3)
+  dnfi25mxw	= xnfi25mxw
+  xnfi25mvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnfi25mvth0	= xnfi25mvth0
+  xnfi25mvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnfi25mvt0 	= xnfi25mvt0
+  xnfi25mcgso	= agauss('-cnr_hv_nfet',1,3)
+  dnfi25mcgso	= xnfi25mcgso
+  xnfi25mcgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnfi25mcgdx1 = xnfi25mcgdx1
+  xnfi25mbeta	= agauss(cnr_hv_nfet,1,3)
+  dnfi25mbeta	= xnfi25mbeta
+  dnfi25mvth1	= '-dnfi25mbeta'
+  dnfi25mvth2	= '-dnfi25mbeta'
+  dnfi25mbeta1 = dnfi25mbeta
+  dnfi25mbeta2 = dnfi25mbeta
+  dnfi25mrj	= '-dnfi25mbeta'
+  xnfi25mcj	= agauss('-cnr_hv_nfet',1,3)
+  dnfi25mcj	= xnfi25mcj
+  xnfi25mdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnfi25mdlc	= xnfi25mdlc
+  xnfi25mk1	= agauss('-cnr_hv_nfet',1,3)
+  dnfi25mk1	= xnfi25mk1
+  xnfi25mk2	= agauss(cnr_hv_nfet,1,3)
+  dnfi25mk2	= xnfi25mk2
+  xnfi25mvsat	= agauss(cnr_hv_nfet,1,3)
+  dnfi25mvsat	= xnfi25mvsat
+  xnfi25muo	= agauss(cnr_hv_nfet,1,3)
+  dnfi25muo	= xnfi25muo
+  xnfi25mxl	= agauss('-cnr_hv_nfet',1,3)
+  dnfi25mxl	= xnfi25mxl
+  xnfi25mnoi	= agauss('-cnr_hv_noin',1,3)
+  dnfi25mnoi	= xnfi25mnoi
*
+  tox_nfeti25m	  = '1.2600e-08 + deltmoxn + dtox_nfeti25m_fc'
+  vth0_nfeti25m  = '6.3866e-01 + 5.4286e-02*dnfi25mvth0 + 5.325e+7*(tox_nfeti25m-12.6n) + dvth0_nfeti25m_fc'
+  dvt0_nfeti25m  = '5.350 + 2.943*dnfi25mvt0 + ddvt0_nfeti25m_fc'
+  cgso_nfeti25m  = '8.0940e-11 + 9.7100e-12*dnfi25mcgso + dcgso_nfeti25m_fc'
+  dlc_nfeti25m	  = '-7.406e-07 + 1.6790e-07*dnfi25mdlc + ddlc_nfeti25m_fc'
+  k1_nfeti25m	  = '0.9894 + 1.1840e-01*dnfi25mk1 + dk1_nfeti25m_fc'
+  k2_nfeti25m	  = '-2.204e-02 + 1.2855e-02*dnfi25mk2 + dk2_nfeti25m_fc'
+  vsat_nfeti25m  = '1.1698e+05 + 0*dnfi25mvsat + dvsat_nfeti25m_fc'
+  cj_nfeti25m	  = '9.0520e-04 + 1.0870e-04*dnfi25mcj + dcj_nfeti25m_fc'
+  rj_nfeti25m	  = '0.35569 + 1.7785e-02*dnfi25mrj + drj_nfeti25m_fc'
+  cgdx1_nfeti25m = '3.50e-10 + 4.20e-11*dnfi25mcgdx1 + dcgdx1_nfeti25m_fc'
+  beta1_nfeti25m = '21.884 + 4.3768*dnfi25mbeta1 + dbeta1_nfeti25m_fc'
+  beta2_nfeti25m = '2.4643 + 1.9714e-01*dnfi25mbeta2 + dbeta2_nfeti25m_fc'
+  vth1_nfeti25m  = '-2.120 + 0.0424*dnfi25mvth1 + dvth1_nfeti25m_fc'
+  vth2_nfeti25m  = '-8.312 + 0.3325*dnfi25mvth2 + dvth2_nfeti25m_fc'
+  uo_nfeti25m	  = '530.29 + 10.606*dnfi25muo + duo_nfeti25m_fc'
+  xl_nfeti25m	  = '0 + 0.11e-6*dnfi25mxl + dxl_nfeti25m_fc'
+  xw_nfeti25m	  = '0 + 0*dnfi25mxw + dxw_nfeti25m_fc'
*
*					    PFET25M
.param
+  xpf25mxw    = agauss(cnr_hv_pfet,1,3)
+  dpf25mxw    = xpf25mxw
+  xpf25mvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf25mvth0  = xpf25mvth0
+  xpf25mvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf25mvt0   = xpf25mvt0
+  xpf25mcgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf25mcgso  = xpf25mcgso
+  xpf25mcgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf25mcgdx1 = xpf25mcgdx1
+  xpf25mbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf25mbeta  = xpf25mbeta
+  dpf25mvth1  = '-dpf25mbeta'
+  dpf25mvth2  = '-dpf25mbeta'
+  dpf25mbeta1 = dpf25mbeta
+  dpf25mbeta2 = dpf25mbeta
+  dpf25mrj    = '-dpf25mbeta'
+  xpf25mcj    = agauss('-cnr_hv_pfet',1,3)
+  dpf25mcj    = xpf25mcj
+  xpf25mdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf25mdlc   = xpf25mdlc
+  xpf25mk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf25mk1    = xpf25mk1
+  xpf25mk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf25mk2    = xpf25mk2
+  xpf25mvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf25mvsat  = xpf25mvsat
+  xpf25muo    = agauss(cnr_hv_pfet,1,3)
+  dpf25muo    = xpf25muo
+  xpf25mxl    = agauss('-cnr_hv_pfet',1,3)
+  dpf25mxl    = xpf25mxl
+  xpf25mnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf25mnoi   = xpf25mnoi
*
+  tox_pfet25m	 = '1.2700e-08 + deltmoxp + dtox_pfet25m_fc'
+  vth0_pfet25m	 = '-5.513e-01 + 5.513e-02*dpf25mvth0 - 4.4e+7*(tox_pfet25m-12.7n) + dvth0_pfet25m_fc'
+  dvt0_pfet25m  = '7.618 + 1.224*dpf25mvt0 + ddvt0_pfet25m_fc'
+  cgso_pfet25m	 = '1.229e-10 + 1.470e-11*dpf25mcgso + dcgso_pfet25m_fc'
+  cgdx1_pfet25m = '1.50e-10 + 1.80e-11*dpf25mcgdx1 + dcgdx1_pfet25m_fc'
+  beta1_pfet25m = '1.425 + 1.71e-01*dpf25mbeta1 + dbeta1_pfet25m_fc'
+  beta2_pfet25m = '0.820 + 8.20e-02*dpf25mbeta2 + dbeta2_pfet25m_fc'
+  vth1_pfet25m	 = '-1.52e+01 + 7.60e-01*dpf25mvth1 + dvth1_pfet25m_fc'
+  vth2_pfet25m	 = '-1.30e+01 + 6.50e-01*dpf25mvth2 + dvth2_pfet25m_fc'
+  rj_pfet25m	 = '0.53632 + 7.9335e-02*dpf25mrj + drj_pfet25m_fc'
+  cj_pfet25m	 = '6.3710e-04 + 7.65e-05*dpf25mcj + dcj_pfet25m_fc'
+  dlc_pfet25m	 = '-2.902e-07 + 1.25e-07*dpf25mdlc + ddlc_pfet25m_fc'
+  k1_pfet25m	 = '9.9073e-01 + 1.1600e-01*dpf25mk1 + dk1_pfet25m_fc'
+  k2_pfet25m	 = '-9.011e-02 + 1.6715e-02*dpf25mk2 + dk2_pfet25m_fc'
+  vsat_pfet25m	 = '5.3920e+4 + 0*dpf25mvsat + dvsat_pfet25m_fc'
+  uo_pfet25m	 = '120.3 + 8.421*dpf25muo + duo_pfet25m_fc'
+  xl_pfet25m	 = '0 + 0*dpf25mxl + dxl_pfet25m_fc'
+  xw_pfet25m	 = '0 + 5.00e-7*dpf25mxw + dxw_pfet25m_fc'
*
*					    NFETI50M
.param
+  xnfi50mxw	= agauss(cnr_hv_nfet,1,3)
+  dnfi50mxw	= xnfi50mxw
+  xnfi50mvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50mvth0	= xnfi50mvth0
+  xnfi50mvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnfi50mvt0 	= xnfi50mvt0
+  xnfi50mcgso	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50mcgso	= xnfi50mcgso
+  xnfi50mcgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnfi50mcgdx1 = xnfi50mcgdx1
+  xnfi50mbeta	= agauss(cnr_hv_nfet,1,3)
+  dnfi50mbeta	= xnfi50mbeta
+  dnfi50mvth1	= '-dnfi50mbeta'
+  dnfi50mvth2	= '-dnfi50mbeta'
+  dnfi50mbeta1 = dnfi50mbeta
+  dnfi50mbeta2 = '1.2*dnfi50mbeta'
+  dnfi50mrj	= '-dnfi50mbeta'
+  xnfi50mcj	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50mcj	= xnfi50mcj
+  xnfi50mdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50mdlc	= xnfi50mdlc
+  xnfi50mk1	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50mk1	= xnfi50mk1
+  xnfi50mk2	= agauss(cnr_hv_nfet,1,3)
+  dnfi50mk2	= xnfi50mk2
+  xnfi50mvsat	= agauss(cnr_hv_nfet,1,3)
+  dnfi50mvsat	= xnfi50mvsat
+  xnfi50muo	= agauss(cnr_hv_nfet,1,3)
+  dnfi50muo	= xnfi50muo
+  xnfi50mxl	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50mxl	= xnfi50mxl
+  xnfi50mnoi	= agauss('-cnr_hv_noin',1,3)
+  dnfi50mnoi	= xnfi50mnoi
*
+  tox_nfeti50m	  = '1.2600e-08 + deltmoxn + dtox_nfeti50m_fc'
+  vth0_nfeti50m  = '6.10e-01 + 7.4747e-02*dnfi50mvth0 + 5.834e+7*(tox_nfeti50m-12.6n) + dvth0_nfeti50m_fc'
+  dvt0_nfeti50m  = '5.370 + 2.685*dnfi50mvt0 + ddvt0_nfeti50m_fc'
+  cgso_nfeti50m  = '7.6090e-11 + 9.1300e-12*dnfi50mcgso + dcgso_nfeti50m_fc'
+  dlc_nfeti50m	  = '-9.370e-07 + 2.1340e-07*dnfi50mdlc + ddlc_nfeti50m_fc'
+  k1_nfeti50m	  = '1.0286 + 7.2360e-02*dnfi50mk1 + dk1_nfeti50m_fc'
+  k2_nfeti50m	  = '-2.113e-02 + 0*dnfi50mk2 + dk2_nfeti50m_fc'
+  vsat_nfeti50m  = '1.0000e+06 + 0*dnfi50mvsat + dvsat_nfeti50m_fc'
+  cj_nfeti50m	  = '9.0520e-04 + 1.0870e-04*dnfi50mcj + dcj_nfeti50m_fc'
+  rj_nfeti50m	  = '3.2013 + 1.6007e-01*dnfi50mrj + drj_nfeti50m_fc'
+  cgdx1_nfeti50m = '7.50e-10 + 9.00e-11*dnfi50mcgdx1 + dcgdx1_nfeti50m_fc'
+  beta1_nfeti50m = '4.2278 + 0.5017*dnfi50mbeta1 + dbeta1_nfeti50m_fc'
+  beta2_nfeti50m = '5.8250e-01 + 7.5730e-02*dnfi50mbeta2 + dbeta2_nfeti50m_fc'
+  vth1_nfeti50m  = '-5.135 + 0.25675*dnfi50mvth1 + dvth1_nfeti50m_fc'
+  vth2_nfeti50m  = '-16.09 + 0.8045*dnfi50mvth2 + dvth2_nfeti50m_fc'
+  uo_nfeti50m	  = '516.28 + 20*dnfi50muo + duo_nfeti50m_fc'
+  xl_nfeti50m	  = '0 + 0.11e-6*dnfi50mxl + dxl_nfeti50m_fc'
+  xw_nfeti50m	  = '0 + 0*dnfi50mxw + dxw_nfeti50m_fc'
*
*					    PFET50M
.param
+  xpf50mxw    = agauss(cnr_hv_pfet,1,3)
+  dpf50mxw    = xpf50mxw
+  xpf50mvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf50mvth0  = xpf50mvth0
+  xpf50mvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf50mvt0   = xpf50mvt0
+  xpf50mcgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf50mcgso  = xpf50mcgso
+  xpf50mcgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf50mcgdx1 = xpf50mcgdx1
+  xpf50mbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf50mbeta  = xpf50mbeta
+  dpf50mvth1  = '-dpf50mbeta'
+  dpf50mvth2  = '-dpf50mbeta'
+  dpf50mbeta1 = dpf50mbeta
+  dpf50mbeta2 = dpf50mbeta
+  dpf50mrj    = '-dpf50mbeta'
+  xpf50mcj    = agauss('-cnr_hv_pfet',1,3)
+  dpf50mcj    = xpf50mcj
+  xpf50mdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf50mdlc   = xpf50mdlc
+  xpf50mk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf50mk1    = xpf50mk1
+  xpf50mk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf50mk2    = xpf50mk2
+  xpf50mvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf50mvsat  = xpf50mvsat
+  xpf50muo    = agauss(cnr_hv_pfet,1,3)
+  dpf50muo    = xpf50muo
+  xpf50mxl    = agauss('-cnr_hv_pfet',1,3)
+  dpf50mxl    = xpf50mxl
+  xpf50mnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf50mnoi   = xpf50mnoi
*
+  tox_pfet50m	 = '1.2700e-08 + deltmoxp + dtox_pfet50m_fc'
+  vth0_pfet50m	 = '-5.780e-01 + 5.0976e-02*dpf50mvth0 - 4.3e+7*(tox_pfet50m-12.7n) + dvth0_pfet50m_fc'
+  dvt0_pfet50m  = '4.935 + 0*dpf50mvt0 + ddvt0_pfet50m_fc'
+  cgso_pfet50m	 = '1.445e-10 + 1.7300e-11*dpf50mcgso + dcgso_pfet50m_fc'
+  cgdx1_pfet50m = '5.25e-10 + 6.30e-11*dpf50mcgdx1 + dcgdx1_pfet50m_fc'
+  vth1_pfet50m	 = '-1.730e+01 + 3.646e-01*dpf50mvth1 + dvth1_pfet50m_fc'
+  vth2_pfet50m	 = '-2.550e+01 + 6.150e-01*dpf50mvth2 + dvth2_pfet50m_fc'
+  beta1_pfet50m = '6.75e-01 + 7.25e-02*dpf50mbeta1 + dbeta1_pfet50m_fc'
+  beta2_pfet50m = '2.37e-01 + 1.4851e-02*dpf50mbeta2 + dbeta2_pfet50m_fc'
+  rj_pfet50m	 = '1.580 + 1.896e-01*dpf50mrj + drj_pfet50m_fc'
+  cj_pfet50m	 = '6.3710e-04 + 7.65e-05*dpf50mcj + dcj_pfet50m_fc'
+  dlc_pfet50m	 = '-3.427e-07 + 1.3e-07*dpf50mdlc + ddlc_pfet50m_fc'
+  k1_pfet50m	 = '9.6305e-01 + 7.915e-02*dpf50mk1 + dk1_pfet50m_fc'
+  k2_pfet50m	 = '-8.251e-02 + 0*dpf50mk2 + dk2_pfet50m_fc'
+  vsat_pfet50m	 = '6.0220e+4 + 0*dpf50mvsat + dvsat_pfet50m_fc'
+  uo_pfet50m	 = '119.8 + 11.58*dpf50muo + duo_pfet50m_fc'
+  xl_pfet50m	 = '0 + 0*dpf50mxl + dxl_pfet50m_fc'
+  xw_pfet50m	 = '0 + 5.00e-7*dpf50mxw + dxw_pfet50m_fc'
*
*					    NFETI20H
.param
+  xnfi20hxw	= agauss(cnr_hv_nfet,1,3)
+  dnfi20hxw	= xnfi20hxw
+  xnfi20hvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20hvth0	= xnfi20hvth0
+  xnfi20hvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnfi20hvt0 	= xnfi20hvt0
+  xnfi20hcgso	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20hcgso	= xnfi20hcgso
+  xnfi20hcgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnfi20hcgdx1 = xnfi20hcgdx1
+  xnfi20hbeta	= agauss(cnr_hv_nfet,1,3)
+  dnfi20hbeta	= xnfi20hbeta
+  dnfi20hvth1	= '-dnfi20hbeta'
+  dnfi20hvth2	= '-dnfi20hbeta'
+  dnfi20hbeta1 = dnfi20hbeta
+  dnfi20hbeta2 = dnfi20hbeta
+  dnfi20hrj	= '-dnfi20hbeta'
+  xnfi20hcj	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20hcj	= xnfi20hcj
+  xnfi20hdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20hdlc	= xnfi20hdlc
+  xnfi20hk1	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20hk1	= xnfi20hk1
+  xnfi20hk2	= agauss(cnr_hv_nfet,1,3)
+  dnfi20hk2	= xnfi20hk2
+  xnfi20hvsat	= agauss(cnr_hv_nfet,1,3)
+  dnfi20hvsat	= xnfi20hvsat
+  xnfi20huo	= agauss(cnr_hv_nfet,1,3)
+  dnfi20huo	= xnfi20huo
+  xnfi20hxl	= agauss('-cnr_hv_nfet',1,3)
+  dnfi20hxl	= xnfi20hxl
+  xnfi20hnoi	= agauss('-cnr_hv_noin',1,3)
+  dnfi20hnoi	= xnfi20hnoi
*
+  tox_nfeti20h	  = '52.000e-09 + delthoxn + dtox_nfeti20h_fc'
+  vth0_nfeti20h  = '1.9171 + 2.684e-01*dnfi20hvth0 + 3.86e+7*(tox_nfeti20h-52.0n) + dvth0_nfeti20h_fc'
+  dvt0_nfeti20h  = '2.1958e+01 + 12.0*dnfi20hvt0 + ddvt0_nfeti20h_fc'
+  cgso_nfeti20h  = '1.4570e-10 + 1.7500e-11*dnfi20hcgso + dcgso_nfeti20h_fc'
+  dlc_nfeti20h	  = '-8.338e-07 + 2.0825e-07*dnfi20hdlc + ddlc_nfeti20h_fc'
+  k1_nfeti20h	  = '2.2137 + 3.4670e-01*dnfi20hk1 + dk1_nfeti20h_fc'
+  k2_nfeti20h	  = '9.6671e-03 + 4.2219e-03*dnfi20hk2 + dk2_nfeti20h_fc'
+  vsat_nfeti20h  = '7.6702e+04 + 7.670e+03*dnfi20hvsat + dvsat_nfeti20h_fc'
+  cj_nfeti20h	  = '9.0520e-04 + 1.0870e-04*dnfi20hcj + dcj_nfeti20h_fc'
+  rj_nfeti20h	  = '1.7653e-01 + 6.1786e-02*dnfi20hrj + drj_nfeti20h_fc'
+  cgdx1_nfeti20h = '2.75e-10 + 3.30e-11*dnfi20hcgdx1 + dcgdx1_nfeti20h_fc'
+  beta1_nfeti20h = '13.916 + 3.8965*dnfi20hbeta1 + dbeta1_nfeti20h_fc'
+  beta2_nfeti20h = '3.2021 + 0.3522*dnfi20hbeta2 + dbeta2_nfeti20h_fc'
+  vth1_nfeti20h  = '-4.593 + 0.2297*dnfi20hvth1 + dvth1_nfeti20h_fc'
+  vth2_nfeti20h  = '-10.13 + 0.3546*dnfi20hvth2 + dvth2_nfeti20h_fc'
+  uo_nfeti20h	  = '536.31 + 26.816*dnfi20huo + duo_nfeti20h_fc'
+  xl_nfeti20h	  = '0 + 0*dnfi20hxl + dxl_nfeti20h_fc'
+  xw_nfeti20h	  = '0 + 5.00e-7*dnfi20hxw + dxw_nfeti20h_fc'
*
*					    PFET20H
.param
+  xpf20hxw    = agauss(cnr_hv_pfet,1,3)
+  dpf20hxw    = xpf20hxw
+  xpf20hvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf20hvth0  = xpf20hvth0
+  xpf20hvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf20hvt0   = xpf20hvt0
+  xpf20hcgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf20hcgso  = xpf20hcgso
+  xpf20hcgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf20hcgdx1 = xpf20hcgdx1
+  xpf20hbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf20hbeta  = xpf20hbeta
+  dpf20hvth1  = '-dpf20hbeta'
+  dpf20hvth2  = '-dpf20hbeta'
+  dpf20hbeta1 = dpf20hbeta
+  dpf20hbeta2 = dpf20hbeta
+  dpf20hrj    = '-dpf20hbeta'
+  xpf20hcj    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hcj    = xpf20hcj
+  xpf20hdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf20hdlc   = xpf20hdlc
+  xpf20hk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hk1    = xpf20hk1
+  xpf20hk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hk2    = xpf20hk2
+  xpf20hvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf20hvsat  = xpf20hvsat
+  xpf20huo    = agauss(cnr_hv_pfet,1,3)
+  dpf20huo    = xpf20huo
+  xpf20hxl    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hxl    = xpf20hxl
+  xpf20hnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf20hnoi   = xpf20hnoi
*
+  tox_pfet20h	 = '52.000e-09 + delthoxp + dtox_pfet20h_fc'
+  vth0_pfet20h	 = '-2.375 + 2.1375e-01*dpf20hvth0 - 4.76e+7*(tox_pfet20h-52.0n) + dvth0_pfet20h_fc'
+  dvt0_pfet20h  = '3.930 + 0.786*dpf20hvt0 + ddvt0_pfet20h_fc'
+  cgso_pfet20h	 = '0.6808e-10 + 2.04e-11*dpf20hcgso + dcgso_pfet20h_fc'
+  cgdx1_pfet20h = '1.30e-10 + 1.56e-11*dpf20hcgdx1 + dcgdx1_pfet20h_fc'
+  vth1_pfet20h	 = '-5.975 + 6.573e-01*dpf20hvth1 + dvth1_pfet20h_fc'
+  vth2_pfet20h	 = '-1.779e+01 + 1.423e-01*dpf20hvth2 + dvth2_pfet20h_fc'
+  beta1_pfet20h = '3.1087 + 3.1087e-01*dpf20hbeta1 + dbeta1_pfet20h_fc'
+  beta2_pfet20h = '1.0734 + 1.0734e-01*dpf20hbeta2 + dbeta2_pfet20h_fc'
+  rj_pfet20h	 = '0.23718 + 1.8974e-02*dpf20hrj + drj_pfet20h_fc'
+  cj_pfet20h	 = '6.3710e-04 + 7.65e-05*dpf20hcj + dcj_pfet20h_fc'
+  dlc_pfet20h	 = '-4.504e-07 + 1.5025e-07*dpf20hdlc + ddlc_pfet20h_fc'
+  k1_pfet20h	 = '2.5347 + 2.422e-01*dpf20hk1 + dk1_pfet20h_fc'
+  k2_pfet20h	 = '1.8074e-01 + 2.304e-02*dpf20hk2 + dk2_pfet20h_fc'
+  vsat_pfet20h	 = '7.3377e+04 + 0*dpf20hvsat + dvsat_pfet20h_fc'
+  uo_pfet20h	 = '150.08 + 15.008*dpf20huo + duo_pfet20h_fc'
+  xl_pfet20h	 = '0 + 0*dpf20hxl + dxl_pfet20h_fc'
+  xw_pfet20h	 = '0 + 5.00e-7*dpf20hxw + dxw_pfet20h_fc'
*
*					    NFET20HS
.param
+  xnf20hsxw	= agauss(cnr_hv_nfet,1,3)
+  dnf20hsxw	= xnf20hsxw
+  xnf20hsvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnf20hsvth0	= xnf20hsvth0
+  xnf20hsvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnf20hsvt0 	= xnf20hsvt0
+  xnf20hscgso	= agauss('-cnr_hv_nfet',1,3)
+  dnf20hscgso	= xnf20hscgso
+  xnf20hscgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnf20hscgdx1 = xnf20hscgdx1
+  xnf20hsbeta	= agauss(cnr_hv_nfet,1,3)
+  dnf20hsbeta	= xnf20hsbeta
+  dnf20hsvth1	= '-dnf20hsbeta'
+  dnf20hsvth2	= '-dnf20hsbeta'
+  dnf20hsbeta1 = dnf20hsbeta
+  dnf20hsbeta2 = dnf20hsbeta
+  dnf20hsrj	= '-dnf20hsbeta'
+  xnf20hscj	= agauss('-cnr_hv_nfet',1,3)
+  dnf20hscj	= xnf20hscj
+  xnf20hscjsw	= agauss('-cnr_hv_nfet',1,3)
+  dnf20hscjsw	= xnf20hscjsw
+  xnf20hsdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnf20hsdlc	= xnf20hsdlc
+  xnf20hsk1	= agauss('-cnr_hv_nfet',1,3)
+  dnf20hsk1	= xnf20hsk1
+  xnf20hsk2	= agauss(cnr_hv_nfet,1,3)
+  dnf20hsk2	= xnf20hsk2
+  xnf20hsvsat	= agauss(cnr_hv_nfet,1,3)
+  dnf20hsvsat	= xnf20hsvsat
+  xnf20hsuo	= agauss(cnr_hv_nfet,1,3)
+  dnf20hsuo	= xnf20hsuo
+  xnf20hsxl	= agauss('-cnr_hv_nfet',1,3)
+  dnf20hsxl	= xnf20hsxl
+  xnf20hsnoi	= agauss('-cnr_hv_noin',1,3)
+  dnf20hsnoi	= xnf20hsnoi
*
+  tox_nfet20hs	  = '52.000e-09 + delthoxn + dtox_nfet20hs_fc'
+  vth0_nfet20hs  = '2.088 + 2.2124e-01*dnf20hsvth0 + 3.7343e+7*(tox_nfet20hs-52.0n) + dvth0_nfet20hs_fc'
+  dvt0_nfet20hs  = '8.637 + 3.322*dnf20hsvt0 + ddvt0_nfet20hs_fc'
+  cgso_nfet20hs  = '1.0000e-12 + 0*dnf20hscgso + dcgso_nfet20hs_fc'
+  dlc_nfet20hs	  = '-1.1424e-06 + 3.2000e-07*dnf20hsdlc + ddlc_nfet20hs_fc'
+  k1_nfet20hs	  = '2.3407 + 3.3230e-01*dnf20hsk1 + dk1_nfet20hs_fc'
+  k2_nfet20hs	  = '5.9529e-02 + 3.4358e-02*dnf20hsk2 + dk2_nfet20hs_fc'
+  vsat_nfet20hs  = '6.3760e+04 + 0*dnf20hsvsat + dvsat_nfet20hs_fc'
+  cj_nfet20hs	  = '1.1250e-04 + 1.3500e-05*dnf20hscj + dcj_nfet20hs_fc'
+  cjsw_nfet20hs  = '4.0250e-10 + 4.8300e-11*dnf20hscjsw'
+  rj_nfet20hs	  = '3.8865e-01 + 4.6795e-02*dnf20hsrj + drj_nfet20hs_fc'
+  cgdx1_nfet20hs = '1.00e-10 + 1.20e-11*dnf20hscgdx1 + dcgdx1_nfet20hs_fc'
+  beta1_nfet20hs = '9.2421 + 8.3180e-01*dnf20hsbeta1 + dbeta1_nfet20hs_fc'
+  beta2_nfet20hs = '9.3770 + 8.4393e-01*dnf20hsbeta2 + dbeta2_nfet20hs_fc'
+  vth1_nfet20hs  = '-5.290 + 3.7030e-01*dnf20hsvth1 + dvth1_nfet20hs_fc'
+  vth2_nfet20hs  = '-8.369 + 2.0923e-01*dnf20hsvth2 + dvth2_nfet20hs_fc'
+  uo_nfet20hs	  = '463.90 + 41.751*dnf20hsuo + duo_nfet20hs_fc'
+  xl_nfet20hs	  = '0 + 0*dnf20hsxl + dxl_nfet20hs_fc'
+  xw_nfet20hs	  = '0 + 5.00e-7*dnf20hsxw + dxw_nfet20hs_fc'
*
*					    PFET20HS
.param
+  xpf20hsxw    = agauss(cnr_hv_pfet,1,3)
+  dpf20hsxw    = xpf20hsxw
+  xpf20hsvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf20hsvth0  = xpf20hsvth0
+  xpf20hsvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf20hsvt0   = xpf20hsvt0
+  xpf20hscgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf20hscgso  = xpf20hscgso
+  xpf20hscgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf20hscgdx1 = xpf20hscgdx1
+  xpf20hsbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf20hsbeta  = xpf20hsbeta
+  dpf20hsvth1  = '-dpf20hsbeta'
+  dpf20hsvth2  = '-dpf20hsbeta'
+  dpf20hsbeta1 = dpf20hsbeta
+  dpf20hsbeta2 = dpf20hsbeta
+  dpf20hsrj    = '-dpf20hsbeta'
+  xpf20hscj    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hscj    = xpf20hscj
+  xpf20hscjsw  = agauss('-cnr_hv_pfet',1,3)
+  dpf20hscjsw  = xpf20hscjsw
+  xpf20hsdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf20hsdlc   = xpf20hsdlc
+  xpf20hsk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hsk1    = xpf20hsk1
+  xpf20hsk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hsk2    = xpf20hsk2
+  xpf20hsvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf20hsvsat  = xpf20hsvsat
+  xpf20hsuo    = agauss(cnr_hv_pfet,1,3)
+  dpf20hsuo    = xpf20hsuo
+  xpf20hsxl    = agauss('-cnr_hv_pfet',1,3)
+  dpf20hsxl    = xpf20hsxl
+  xpf20hsnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf20hsnoi   = xpf20hsnoi
*
+  tox_pfet20hs	  = '52.000e-09 + delthoxp + dtox_pfet20hs_fc'
+  vth0_pfet20hs  = '-1.785 + 1.4104e-01*dpf20hsvth0 - 2.5e+7*(tox_pfet20hs-52.0n) + dvth0_pfet20hs_fc'
+  dvt0_pfet20hs  = '4.6812e-01 + 4.6812e-02*dpf20hsvt0 + ddvt0_pfet20hs_fc'
+  cgso_pfet20hs  = '1.0000e-12 + 0*dpf20hscgso + dcgso_pfet20hs_fc'
+  cgdx1_pfet20hs = '2.40e-10 + 2.88e-11*dpf20hscgdx1 + dcgdx1_pfet20hs_fc'
+  vth1_pfet20hs  = '-1.792e+01 + 2.586e-01*dpf20hsvth1 + dvth1_pfet20hs_fc'
+  vth2_pfet20hs  = '-2.210e+01 + 4.420*dpf20hsvth2 + dvth2_pfet20hs_fc'
+  beta1_pfet20hs = '2.2727 + 4.0890e-01*dpf20hsbeta1 + dbeta1_pfet20hs_fc'
+  beta2_pfet20hs = '1.3353 + 3.4420e-01*dpf20hsbeta2 + dbeta2_pfet20hs_fc'
+  rj_pfet20hs	  = '6.7390e-02 + 2.843e-02*dpf20hsrj + drj_pfet20hs_fc'
+  cj_pfet20hs	  = '1.1670e-03 + 1.40e-04*dpf20hscj + dcj_pfet20hs_fc'
+  cjsw_pfet20hs  = '0.0 + 0*dpf20hscjsw'
+  dlc_pfet20hs	  = '-4.144e-07 + 2.402e-07*dpf20hsdlc + ddlc_pfet20hs_fc'
+  k1_pfet20hs	  = '1.2303 + 2.266e-01*dpf20hsk1 + dk1_pfet20hs_fc'
+  k2_pfet20hs	  = '-1.055e-01 + 3.770e-02*dpf20hsk2 + dk2_pfet20hs_fc'
+  vsat_pfet20hs  = '1.0705e+05 + 2.6761e+04*dpf20hsvsat + dvsat_pfet20hs_fc'
+  uo_pfet20hs	  = '209.34 + 25.829*dpf20hsuo + duo_pfet20hs_fc'
+  xl_pfet20hs	  = '0 + 0*dpf20hsxl + dxl_pfet20hs_fc'
+  xw_pfet20hs	  = '0 + 0*dpf20hsxw + dxw_pfet20hs_fc'
*
*					    NFETI50H
.param
+  xnfi50hxw	= agauss(cnr_hv_nfet,1,3)
+  dnfi50hxw	= xnfi50hxw
+  xnfi50hvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50hvth0	= xnfi50hvth0
+  xnfi50hvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnfi50hvt0 	= xnfi50hvt0
+  xnfi50hcgso	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50hcgso	= xnfi50hcgso
+  xnfi50hcgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnfi50hcgdx1 = xnfi50hcgdx1
+  xnfi50hbeta	= agauss(cnr_hv_nfet,1,3)
+  dnfi50hbeta	= xnfi50hbeta
+  dnfi50hvth1	= dnfi50hbeta
+  dnfi50hvth2	= dnfi50hbeta
+  dnfi50hbeta1 = dnfi50hbeta
+  dnfi50hbeta2 = dnfi50hbeta
+  dnfi50hrj	= '-dnfi50hbeta'
+  xnfi50hcj	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50hcj	= xnfi50hcj
+  xnfi50hdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50hdlc	= xnfi50hdlc
+  xnfi50hk1	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50hk1	= xnfi50hk1
+  xnfi50hk2	= agauss(cnr_hv_nfet,1,3)
+  dnfi50hk2	= xnfi50hk2
+  xnfi50hvsat	= agauss(cnr_hv_nfet,1,3)
+  dnfi50hvsat	= xnfi50hvsat
+  xnfi50huo	= agauss(cnr_hv_nfet,1,3)
+  dnfi50huo	= xnfi50huo
+  xnfi50hxl	= agauss('-cnr_hv_nfet',1,3)
+  dnfi50hxl	= xnfi50hxl
+  xnfi50hnoi	= agauss('-cnr_hv_noin',1,3)
+  dnfi50hnoi	= xnfi50hnoi
*
+  tox_nfeti50h	  = '52.000e-09 + delthoxn + dtox_nfeti50h_fc'
+  vth0_nfeti50h  = '1.900 + 3.5298e-01*dnfi50hvth0 + 3.9e+7*(tox_nfeti50h-52.0n) + dvth0_nfeti50h_fc'
+  dvt0_nfeti50h  = '1.5000e+01 + 4.0*dnfi50hvt0 + ddvt0_nfeti50h_fc'
+  cgso_nfeti50h  = '1.6980e-10 + 2.0400e-11*dnfi50hcgso + dcgso_nfeti50h_fc'
+  dlc_nfeti50h	  = '-1.189e-06 + 2.6250e-07*dnfi50hdlc + ddlc_nfeti50h_fc'
+  k1_nfeti50h	  = '1.7887 + 5.2360e-01*dnfi50hk1 + dk1_nfeti50h_fc'
+  k2_nfeti50h	  = '2.1606e-01 + 7.1545e-02*dnfi50hk2 + dk2_nfeti50h_fc'
+  vsat_nfeti50h  = '7.6260e+04 + 0*dnfi50hvsat + dvsat_nfeti50h_fc'
+  cj_nfeti50h	  = '9.7230e-04 + 1.1670e-04*dnfi50hcj + dcj_nfeti50h_fc'
+  rj_nfeti50h	  = '7.4840e-01 + 1.7240e-01*dnfi50hrj + drj_nfeti50h_fc'
+  cgdx1_nfeti50h = '8.50e-10 + 1.02e-10*dnfi50hcgdx1 + dcgdx1_nfeti50h_fc'
+  beta1_nfeti50h = '2.7168 + 6.4684e-01*dnfi50hbeta1 + dbeta1_nfeti50h_fc'
+  beta2_nfeti50h = '0.5590 + 1.8876e-01*dnfi50hbeta2 + dbeta2_nfeti50h_fc'
+  vth1_nfeti50h  = '-8.730 + 1.9880e-01*dnfi50hvth1 + dvth1_nfeti50h_fc'
+  vth2_nfeti50h  = '-16.14 + 6.4800e-01*dnfi50hvth2 + dvth2_nfeti50h_fc'
+  uo_nfeti50h	  = '578.60 + 46.288*dnfi50huo + duo_nfeti50h_fc'
+  xl_nfeti50h	  = '0 + 0*dnfi50hxl + dxl_nfeti50h_fc'
+  xw_nfeti50h	  = '0 + 5.00e-7*dnfi50hxw + dxw_nfeti50h_fc'
*
*					    PFET50H
.param
+  xpf50hxw    = agauss(cnr_hv_pfet,1,3)
+  dpf50hxw    = xpf50hxw
+  xpf50hvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf50hvth0  = xpf50hvth0
+  xpf50hvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf50hvt0   = xpf50hvt0
+  xpf50hcgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf50hcgso  = xpf50hcgso
+  xpf50hcgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf50hcgdx1 = xpf50hcgdx1
+  xpf50hbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf50hbeta  = xpf50hbeta
+  dpf50hvth1  = '-dpf50hbeta'
+  dpf50hvth2  = '-dpf50hbeta'
+  dpf50hbeta1 = dpf50hbeta
+  dpf50hbeta2 = dpf50hbeta
+  dpf50hrj    = '-dpf50hbeta'
+  xpf50hcj    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hcj    = xpf50hcj
+  xpf50hdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf50hdlc   = xpf50hdlc
+  xpf50hk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hk1    = xpf50hk1
+  xpf50hk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hk2    = xpf50hk2
+  xpf50hvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf50hvsat  = xpf50hvsat
+  xpf50huo    = agauss(cnr_hv_pfet,1,3)
+  dpf50huo    = xpf50huo
+  xpf50hxl    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hxl    = xpf50hxl
+  xpf50hnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf50hnoi   = xpf50hnoi
*
+  tox_pfet50h	 = '52.000e-09 + delthoxp + dtox_pfet50h_fc'
+  vth0_pfet50h	 = '-2.411 + 1.9288e-01*dpf50hvth0 - 4.73e+7*(tox_pfet50h-52.0n) + dvth0_pfet50h_fc'
+  dvt0_pfet50h  = '3.8557 + 1.7351*dpf50hvt0 + ddvt0_pfet50h_fc'
+  cgso_pfet50h	 = '1.0241e-10 + 2.23e-11*dpf50hcgso + dcgso_pfet50h_fc'
+  cgdx1_pfet50h = '4.25e-10 + 5.10e-11*dpf50hcgdx1 + dcgdx1_pfet50h_fc'
+  vth1_pfet50h	 = '-1.240e+01 + 3.720e-01*dpf50hvth1 + dvth1_pfet50h_fc'
+  vth2_pfet50h	 = '-3.138e+01 + 1.4121*dpf50hvth2 + dvth2_pfet50h_fc'
+  beta1_pfet50h = '7.9686e-01 + 7.1717e-02*dpf50hbeta1 + dbeta1_pfet50h_fc'
+  beta2_pfet50h = '3.2648e-01 + 3.4628e-02*dpf50hbeta2 + dbeta2_pfet50h_fc'
+  rj_pfet50h	 = '1.3610 + 3.5675e-01*dpf50hrj + drj_pfet50h_fc'
+  cj_pfet50h	 = '6.3710e-04 + 7.65e-05*dpf50hcj + dcj_pfet50h_fc'
+  dlc_pfet50h	 = '-4.485e-07 + 1.385e-07*dpf50hdlc + ddlc_pfet50h_fc'
+  k1_pfet50h	 = '2.5420 + 0*dpf50hk1 + dk1_pfet50h_fc'
+  k2_pfet50h	 = '1.8225e-01 + 0*dpf50hk2 + dk2_pfet50h_fc'
+  vsat_pfet50h	 = '1.0447e+05 + 0*dpf50hvsat + dvsat_pfet50h_fc'
+  uo_pfet50h	 = '145.21 + 13.069*dpf50huo + duo_pfet50h_fc'
+  xl_pfet50h	 = '0 + 0*dpf50hxl + dxl_pfet50h_fc'
+  xw_pfet50h	 = '0 + 5.00e-7*dpf50hxw + dxw_pfet50h_fc'
*
*					    NFET50HS
.param
+  xnf50hsxw	= agauss(cnr_hv_nfet,1,3)
+  dnf50hsxw	= xnf50hsxw
+  xnf50hsvth0	= agauss('-cnr_hv_nfet',1,3)
+  dnf50hsvth0	= xnf50hsvth0
+  xnf50hsvt0 	= agauss(cnr_hv_nfet,1,3)
+  dnf50hsvt0 	= xnf50hsvt0
+  xnf50hscgso	= agauss('-cnr_hv_nfet',1,3)
+  dnf50hscgso	= xnf50hscgso
+  xnf50hscgdx1 = agauss('-cnr_hv_nfet',1,3)
+  dnf50hscgdx1 = xnf50hscgdx1
+  xnf50hsbeta	= agauss(cnr_hv_nfet,1,3)
+  dnf50hsbeta	= xnf50hsbeta
+  dnf50hsvth1	= '-dnf50hsbeta'
+  dnf50hsvth2	= '-dnf50hsbeta'
+  dnf50hsbeta1 = dnf50hsbeta
+  dnf50hsbeta2 = dnf50hsbeta
+  dnf50hsrj	= '-dnf50hsbeta'
+  xnf50hscj	= agauss('-cnr_hv_nfet',1,3)
+  dnf50hscj	= xnf50hscj
+  xnf50hscjsw	= agauss('-cnr_hv_nfet',1,3)
+  dnf50hscjsw	= xnf50hscjsw
+  xnf50hsdlc	= agauss('-cnr_hv_nfet',1,3)
+  dnf50hsdlc	= xnf50hsdlc
+  xnf50hsk1	= agauss('-cnr_hv_nfet',1,3)
+  dnf50hsk1	= xnf50hsk1
+  xnf50hsk2	= agauss(cnr_hv_nfet,1,3)
+  dnf50hsk2	= xnf50hsk2
+  xnf50hsvsat	= agauss(cnr_hv_nfet,1,3)
+  dnf50hsvsat	= xnf50hsvsat
+  xnf50hsuo	= agauss(cnr_hv_nfet,1,3)
+  dnf50hsuo	= xnf50hsuo
+  xnf50hsxl	= agauss('-cnr_hv_nfet',1,3)
+  dnf50hsxl	= xnf50hsxl
+  xnf50hsnoi	= agauss('-cnr_hv_noin',1,3)
+  dnf50hsnoi	= xnf50hsnoi
*
+  tox_nfet50hs	  = '52.000e-09 + delthoxn + dtox_nfet50hs_fc'
+  vth0_nfet50hs  = '2.090 + 1.913e-01*dnf50hsvth0 + 3.74e+7*(tox_nfet50hs-52.0n) + dvth0_nfet50hs_fc'
+  dvt0_nfet50hs  = '8.81 + 0*dnf50hsvt0 + ddvt0_nfet50hs_fc'
+  cgso_nfet50hs  = '1.00e-12 + 0*dnf50hscgso + dcgso_nfet50hs_fc'
+  dlc_nfet50hs	  = '-1.1770e-06 + 3.9000e-07*dnf50hsdlc + ddlc_nfet50hs_fc'
+  k1_nfet50hs	  = '2.2835 + 4.6170e-01*dnf50hsk1 + dk1_nfet50hs_fc'
+  k2_nfet50hs	  = '8.1421e-02 + 6.0588e-02*dnf50hsk2 + dk2_nfet50hs_fc'
+  vsat_nfet50hs  = '6.2720e+04 + 0*dnf50hsvsat + dvsat_nfet50hs_fc'
+  cj_nfet50hs	  = '1.1250e-04 + 1.3500e-05*dnf50hscj + dcj_nfet50hs_fc'
+  cjsw_nfet50hs  = '4.0250e-10 + 4.8300e-11*dnf50hscjsw'
+  rj_nfet50hs	  = '5.2985e-01 + 5.1835e-02*dnf50hsrj + drj_nfet50hs_fc'
+  cgdx1_nfet50hs = '3.00e-10 + 3.60e-11*dnf50hscgdx1 + dcgdx1_nfet50hs_fc'
+  beta1_nfet50hs = '1.2676 + 1.0141e-01*dnf50hsbeta1 + dbeta1_nfet50hs_fc'
+  beta2_nfet50hs = '1.8820 + 1.5056e-01*dnf50hsbeta2 + dbeta2_nfet50hs_fc'
+  vth1_nfet50hs  = '-14.52 + 4.2000e-01*dnf50hsvth1 + dvth1_nfet50hs_fc'
+  vth2_nfet50hs  = '-14.79 + 7.395e-01*dnf50hsvth2 + dvth2_nfet50hs_fc'
+  uo_nfet50hs	  = '473.20 + 42.59*dnf50hsuo + duo_nfet50hs_fc'
+  xl_nfet50hs	  = '0 + 0*dnf50hsxl + dxl_nfet50hs_fc'
+  xw_nfet50hs	  = '0 + 5.00e-7*dnf50hsxw + dxw_nfet50hs_fc'
*
*					    PFET50HS
.param
+  xpf50hsxw    = agauss(cnr_hv_pfet,1,3)
+  dpf50hsxw    = xpf50hsxw
+  xpf50hsvth0  = agauss(cnr_hv_pfet,1,3)
+  dpf50hsvth0  = xpf50hsvth0
+  xpf50hsvt0   = agauss(cnr_hv_pfet,1,3)
+  dpf50hsvt0   = xpf50hsvt0
+  xpf50hscgso  = agauss('-cnr_hv_pfet',1,3)
+  dpf50hscgso  = xpf50hscgso
+  xpf50hscgdx1 = agauss('-cnr_hv_pfet',1,3)
+  dpf50hscgdx1 = xpf50hscgdx1
+  xpf50hsbeta  = agauss(cnr_hv_pfet,1,3)
+  dpf50hsbeta  = xpf50hsbeta
+  dpf50hsvth1  = '-dpf50hsbeta'
+  dpf50hsvth2  = '-dpf50hsbeta'
+  dpf50hsbeta1 = dpf50hsbeta
+  dpf50hsbeta2 = dpf50hsbeta
+  dpf50hsrj    = '-dpf50hsbeta'
+  xpf50hscj    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hscj    = xpf50hscj
+  xpf50hscjsw  = agauss('-cnr_hv_pfet',1,3)
+  dpf50hscjsw  = xpf50hscjsw
+  xpf50hsdlc   = agauss('-cnr_hv_pfet',1,3)
+  dpf50hsdlc   = xpf50hsdlc
+  xpf50hsk1    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hsk1    = xpf50hsk1
+  xpf50hsk2    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hsk2    = xpf50hsk2
+  xpf50hsvsat  = agauss(cnr_hv_pfet,1,3)
+  dpf50hsvsat  = xpf50hsvsat
+  xpf50hsuo    = agauss(cnr_hv_pfet,1,3)
+  dpf50hsuo    = xpf50hsuo
+  xpf50hsxl    = agauss('-cnr_hv_pfet',1,3)
+  dpf50hsxl    = xpf50hsxl
+  xpf50hsnoi   = agauss('-cnr_hv_noip',1,3)
+  dpf50hsnoi   = xpf50hsnoi
*
+  tox_pfet50hs	  = '52.000e-09 + delthoxp + dtox_pfet50hs_fc'
+  vth0_pfet50hs  = '-1.763 + 1.2341e-01*dpf50hsvth0 - 2.4e+7*(tox_pfet50hs-52.0n) + dvth0_pfet50hs_fc'
+  dvt0_pfet50hs  = '3.7166 + 0*dpf50hsvt0 + ddvt0_pfet50hs_fc'
+  cgso_pfet50hs  = '1.0000e-12 + 0*dpf50hscgso + dcgso_pfet50hs_fc'
+  cgdx1_pfet50hs = '8.50e-10 + 1.02e-10*dpf50hscgdx1 + dcgdx1_pfet50hs_fc'
+  vth1_pfet50hs  = '-9.957 + 0.6970*dpf50hsvth1 + dvth1_pfet50hs_fc'
+  vth2_pfet50hs  = '-1.907e+01 + 0.7628*dpf50hsvth2 + dvth2_pfet50hs_fc'
+  beta1_pfet50hs = '1.7953 + 2.3339e-01*dpf50hsbeta1 + dbeta1_pfet50hs_fc'
+  beta2_pfet50hs = '4.6514e-01 + 2.326e-02*dpf50hsbeta2 + dbeta2_pfet50hs_fc'
+  rj_pfet50hs	  = '3.7203 + 1.1161*dpf50hsrj + drj_pfet50hs_fc'
+  cj_pfet50hs	  = '2.5980e-04 + 3.12e-05*dpf50hscj + dcj_pfet50hs_fc'
+  cjsw_pfet50hs  = '5.5210e-10 + 6.63e-11*dpf50hscjsw'
+  dlc_pfet50hs	  = '-6.139e-07 + 3.905e-07*dpf50hsdlc + ddlc_pfet50hs_fc'
+  k1_pfet50hs	  = '1.0301 + 2.5790e-01*dpf50hsk1 + dk1_pfet50hs_fc'
+  k2_pfet50hs	  = '-3.536e-03 + 4.0533e-02*dpf50hsk2 + dk2_pfet50hs_fc'
+  vsat_pfet50hs  = '9.6981e+04 + 0*dpf50hsvsat + dvsat_pfet50hs_fc'
+  uo_pfet50hs	  = '215.24 + 25.829*dpf50hsuo + duo_pfet50hs_fc'
+  xl_pfet50hs	  = '0 + 0*dpf50hsxl + dxl_pfet50hs_fc'
+  xw_pfet50hs	  = '0 + 0*dpf50hsxw + dxw_pfet50hs_fc'
*
***********************************************************************
*
* HiSIM_HV Device Models
*
***********************************************************************
*
*					    NFET12MH
.param
+  xnf12mhvfbc	  = agauss('-cnr_hv_nfet',1,3)
+  dnf12mhvfbc	  = xnf12mhvfbc
+  xnf12mhcgso	  = agauss('-cnr_hv_nfet',1,3)
+  dnf12mhcgso	  = xnf12mhcgso
+  xnf12mhcgdo    = agauss('-cnr_hv_nfet',1,3)
+  dnf12mhcgdo    = xnf12mhcgdo
+  xnf12mhcj	  = agauss('-cnr_hv_nfet',1,3)
+  dnf12mhcj	  = xnf12mhcj
+  xnf12mhloverld = agauss(cnr_hv_nfet,1,3)
+  dnf12mhloverld = xnf12mhloverld
+  xnf12mhsc1	  = agauss(cnr_hv_nfet,1,3)
+  dnf12mhsc1	  = xnf12mhsc1
+  xnf12mhsc2	  = agauss(cnr_hv_nfet,1,3)
+  dnf12mhsc2	  = xnf12mhsc2
+  xnf12mhsc3	  = agauss(cnr_hv_nfet,1,3)
+  dnf12mhsc3	  = xnf12mhsc3
+  xnf12mhnsubc   = agauss('-cnr_hv_nfet',1,3)
+  dnf12mhnsubc   = xnf12mhnsubc
+  xnf12mhrd	  = agauss('-cnr_hv_nfet',1,3)
+  dnf12mhrd	  = xnf12mhrd
+  xnf12mhvmax	  = agauss(cnr_hv_nfet,1,3)
+  dnf12mhvmax	  = xnf12mhvmax
+  xnf12mhmueph1  = agauss(cnr_hv_nfet,1,3)
+  dnf12mhmueph1  = xnf12mhmueph1
+  xnf12mhxld	  = agauss(cnr_hv_nfet,1,3)
+  dnf12mhxld	  = xnf12mhxld
+  xnf12mhxldld	  = agauss(cnr_hv_nfet,1,3)
+  dnf12mhxldld	  = xnf12mhxldld
+  xnf12mhnoi	  = agauss('-cnr_hv_noin',1,3)
+  dnf12mhnoi	  = xnf12mhnoi
*
+  tox_nfet12mh	    = '1.2275e-08 + deltmoxn + dtox_nfet12mh_fc'
+  vfbc_nfet12mh    = '-1.125 + 0.020*dnf12mhvfbc + 2e+07*(tox_nfet12mh-12.2275n) + dvfbc_nfet12mh_fc'
+  cgso_nfet12mh    = '1.00e-11 + 0.20e-11*dnf12mhcgso + dcgso_nfet12mh_fc'
+  cgdo_nfet12mh    = '6.00e-11 + 1.20e-11*dnf12mhcgdo + dcgdo_nfet12mh_fc'
+  cj_nfet12mh	    = '9.50e-04 + 1.90e-04*dnf12mhcj + dcj_nfet12mh_fc'
+  loverld_nfet12mh = '7.10e-07 + 0.71e-07*dnf12mhloverld + dloverld_nfet12mh_fc'
+  sc1_nfet12mh	    = '97.0 + 18.0*dnf12mhsc1 + dsc1_nfet12mh_fc'
+  sc2_nfet12mh	    = '7.220e-14 + 0.2220e-14*dnf12mhsc2 + dsc2_nfet12mh_fc'
+  sc3_nfet12mh	    = '7.445e-07 + 0.7445e-07*dnf12mhsc3 + dsc3_nfet12mh_fc'
+  nsubc_nfet12mh   = '2.142e+17 + 0.2142e+17*dnf12mhnsubc + dnsubc_nfet12mh_fc'
+  vmax_nfet12mh    = '8.15e+06 + 1.0e+06*dnf12mhvmax + dvmax_nfet12mh_fc'
+  rd_nfet12mh	    = '3.050e-03 + 0.10e-03*dnf12mhrd - 0.755e-09*(vmax_nfet12mh-8.15e+06) + drd_nfet12mh_fc'
+  mueph1_nfet12mh  = '2.202e+04 + 0.12e+04*dnf12mhmueph1 + dmueph1_nfet12mh_fc'
+  xld_nfet12mh	    = '1.15e-07 + 0.25e-07*dnf12mhxld + dxld_nfet12mh_fc'
+  xldld_nfet12mh   = '-1.5e-07 + 0.30e-07*dnf12mhxldld + dxldld_nfet12mh_fc'
*
*					    PFET12MH
.param
+  xpf12mhvfbc    = agauss('-cnr_hv_pfet',1,3)
+  dpf12mhvfbc    = xpf12mhvfbc
+  xpf12mhcgso    = agauss('-cnr_hv_pfet',1,3)
+  dpf12mhcgso    = xpf12mhcgso
+  xpf12mhcgdo    = agauss('-cnr_hv_pfet',1,3)
+  dpf12mhcgdo    = xpf12mhcgdo
+  xpf12mhcj      = agauss('-cnr_hv_pfet',1,3)
+  dpf12mhcj      = xpf12mhcj
+  xpf12mhloverld = agauss(cnr_hv_pfet,1,3)
+  dpf12mhloverld = xpf12mhloverld
+  xpf12mhsc1     = agauss(cnr_hv_pfet,1,3)
+  dpf12mhsc1     = xpf12mhsc1
+  xpf12mhsc2     = agauss(cnr_hv_pfet,1,3)
+  dpf12mhsc2     = xpf12mhsc2
+  xpf12mhsc3     = agauss(cnr_hv_pfet,1,3)
+  dpf12mhsc3     = xpf12mhsc3
+  xpf12mhnsubc   = agauss('-cnr_hv_pfet',1,3)
+  dpf12mhnsubc   = xpf12mhnsubc
+  xpf12mhrd      = agauss('-cnr_hv_pfet',1,3)
+  dpf12mhrd      = xpf12mhrd
+  xpf12mhvmax    = agauss(cnr_hv_pfet,1,3)
+  dpf12mhvmax    = xpf12mhvmax
+  xpf12mhmueph1  = agauss(cnr_hv_pfet,1,3)
+  dpf12mhmueph1  = xpf12mhmueph1
+  xpf12mhxld     = agauss(cnr_hv_pfet,1,3)
+  dpf12mhxld     = xpf12mhxld
+  xpf12mhxldld   = agauss(cnr_hv_pfet,1,3)
+  dpf12mhxldld   = xpf12mhxldld
+  xpf12mhnoi     = agauss('-cnr_hv_noip',1,3)
+  dpf12mhnoi     = xpf12mhnoi
*
+  tox_pfet12mh	    = '1.2383e-08 + deltmoxp + dtox_pfet12mh_fc'
+  vfbc_pfet12mh    = '-0.9945 + 0.0549*dpf12mhvfbc + 3e+07*(tox_pfet12mh-12.383n) + dvfbc_pfet12mh_fc'
+  cgso_pfet12mh    = '5.00e-12 + 1.0e-12*dpf12mhcgso + dcgso_pfet12mh_fc'
+  cgdo_pfet12mh    = '5.00e-11 + 1.0e-11*dpf12mhcgdo + dcgdo_pfet12mh_fc'
+  cj_pfet12mh	    = '7.0667e-04 + 1.413e-04*dpf12mhcj + dcj_pfet12mh_fc'
+  loverld_pfet12mh = '8.20e-07 + 0.82e-07*dpf12mhloverld + dloverld_pfet12mh_fc'
+  sc1_pfet12mh	    = '0.76 + 0.0*dpf12mhsc1 + dsc1_pfet12mh_fc'
+  sc2_pfet12mh	    = '0.10 + 0.02*dpf12mhsc2 + dsc2_pfet12mh_fc'
+  sc3_pfet12mh	    = '3.10e-06 + 0.0*dpf12mhsc3 + dsc3_pfet12mh_fc'
+  nsubc_pfet12mh   = '1.340e+17 + 0.1340e+17*dpf12mhnsubc + dnsubc_pfet12mh_fc'
+  rd_pfet12mh	    = '7.37e-03 + 1.369e-03*dpf12mhrd + drd_pfet12mh_fc'
+  vmax_pfet12mh    = '9.20e+06 + 0.194e+06*dpf12mhvmax - 4.5e+08*(rd_pfet12mh-7.37e-03) + dvmax_pfet12mh_fc'
+  mueph1_pfet12mh  = '7150.0 + 0.0*dpf12mhmueph1 + dmueph1_pfet12mh_fc'
+  xld_pfet12mh	    = '7.75e-08 + 2.5e-08*dpf12mhxld + dxld_pfet12mh_fc'
+  xldld_pfet12mh   = '-3.00e-08 + 0.30e-08*dpf12mhxldld + dxldld_pfet12mh_fc'
*
*					    NFETI120M
.param
+  xnfi120mvfbc	   = agauss('-cnr_hv_nfet',1,3)
+  dnfi120mvfbc	   = xnfi120mvfbc
+  xnfi120mcgso	   = agauss('-cnr_hv_nfet',1,3)
+  dnfi120mcgso	   = xnfi120mcgso
+  xnfi120mcgdo    = agauss('-cnr_hv_nfet',1,3)
+  dnfi120mcgdo    = xnfi120mcgdo
+  xnfi120mcj	   = agauss('-cnr_hv_nfet',1,3)
+  dnfi120mcj	   = xnfi120mcj
+  xnfi120mloverld = agauss(cnr_hv_nfet,1,3)
+  dnfi120mloverld = xnfi120mloverld
+  xnfi120msc1	   = agauss(cnr_hv_nfet,1,3)
+  dnfi120msc1	   = xnfi120msc1
+  xnfi120msc2	   = agauss(cnr_hv_nfet,1,3)
+  dnfi120msc2	   = xnfi120msc2
+  xnfi120msc3	   = agauss(cnr_hv_nfet,1,3)
+  dnfi120msc3	   = xnfi120msc3
+  xnfi120mnsubc   = agauss('-cnr_hv_nfet',1,3)
+  dnfi120mnsubc   = xnfi120mnsubc
+  xnfi120mrd	   = agauss('-cnr_hv_nfet',1,3)
+  dnfi120mrd	   = xnfi120mrd
+  xnfi120mvmax	   = agauss(cnr_hv_nfet,1,3)
+  dnfi120mvmax	   = xnfi120mvmax
+  xnfi120mmueph1  = agauss(cnr_hv_nfet,1,3)
+  dnfi120mmueph1  = xnfi120mmueph1
+  xnfi120mxld	   = agauss(cnr_hv_nfet,1,3)
+  dnfi120mxld	   = xnfi120mxld
+  xnfi120mxldld   = agauss(cnr_hv_nfet,1,3)
+  dnfi120mxldld   = xnfi120mxldld
+  xnfi120mnoi	   = agauss('-cnr_hv_noin',1,3)
+  dnfi120mnoi	   = xnfi120mnoi
*
+  tox_nfeti120m     = '1.232e-08 + deltmoxn + dtox_nfeti120m_fc'
+  vfbc_nfeti120m    = '-1.087 + 0.010*dnfi120mvfbc + 0.0e+07*(tox_nfeti120m-12.32n) + dvfbc_nfeti120m_fc'
+  cgso_nfeti120m    = '1.00e-12 + 0.20e-12*dnfi120mcgso + dcgso_nfeti120m_fc'
+  cgdo_nfeti120m    = '9.00e-10 + 1.80e-10*dnfi120mcgdo + dcgdo_nfeti120m_fc'
+  cj_nfeti120m	     = '9.156e-04 + 1.83e-04*dnfi120mcj + dcj_nfeti120m_fc'
+  loverld_nfeti120m = '7.10e-07 + 2.13e-07*dnfi120mloverld + dloverld_nfeti120m_fc'
+  sc1_nfeti120m     = '1.0 + 0.2*dnfi120msc1 + dsc1_nfeti120m_fc'
+  sc2_nfeti120m     = '0.11 + 2.0e-03*dnfi120msc2 + dsc2_nfeti120m_fc'
+  sc3_nfeti120m     = '1.0e-05 + 0.2e-05*dnfi120msc3 + dsc3_nfeti120m_fc'
+  nsubc_nfeti120m   = '2.708e+17 + 0.279e+17*dnfi120mnsubc + dnsubc_nfeti120m_fc'
+  rd_nfeti120m	     = '0.0 + 2.0e-03*dnfi120mrd + drd_nfeti120m_fc'
+  vmax_nfeti120m    = '4.40e+06 + 0.0e+06*dnfi120mvmax + dvmax_nfeti120m_fc'
+  mueph1_nfeti120m  = '2.189e+04 + 0.12e+04*dnfi120mmueph1 + dmueph1_nfeti120m_fc'
+  xld_nfeti120m     = '1.15e-07 + 0.25e-07*dnfi120mxld + dxld_nfeti120m_fc'
+  xldld_nfeti120m   = '-5.0e-07 + 1.50e-07*dnfi120mxldld + dxldld_nfeti120m_fc'
*
*					    PFET120M
.param
+  xpf120mvfbc    = agauss('-cnr_hv_pfet',1,3)
+  dpf120mvfbc    = xpf120mvfbc
+  xpf120mcgso    = agauss('-cnr_hv_pfet',1,3)
+  dpf120mcgso    = xpf120mcgso
+  xpf120mcgdo    = agauss('-cnr_hv_pfet',1,3)
+  dpf120mcgdo    = xpf120mcgdo
+  xpf120mcj      = agauss('-cnr_hv_pfet',1,3)
+  dpf120mcj      = xpf120mcj
+  xpf120mloverld = agauss(cnr_hv_pfet,1,3)
+  dpf120mloverld = xpf120mloverld
+  xpf120msc1     = agauss(cnr_hv_pfet,1,3)
+  dpf120msc1     = xpf120msc1
+  xpf120msc2     = agauss(cnr_hv_pfet,1,3)
+  dpf120msc2     = xpf120msc2
+  xpf120msc3     = agauss(cnr_hv_pfet,1,3)
+  dpf120msc3     = xpf120msc3
+  xpf120mnsubc   = agauss('-cnr_hv_pfet',1,3)
+  dpf120mnsubc   = xpf120mnsubc
+  xpf120mrd      = agauss('-cnr_hv_pfet',1,3)
+  dpf120mrd      = xpf120mrd
+  xpf120mvmax    = agauss(cnr_hv_pfet,1,3)
+  dpf120mvmax    = xpf120mvmax
+  xpf120mmueph1  = agauss(cnr_hv_pfet,1,3)
+  dpf120mmueph1  = xpf120mmueph1
+  xpf120mxld     = agauss(cnr_hv_pfet,1,3)
+  dpf120mxld     = xpf120mxld
+  xpf120mxldld   = agauss(cnr_hv_pfet,1,3)
+  dpf120mxldld   = xpf120mxldld
+  xpf120mnoi     = agauss('-cnr_hv_noip',1,3)
+  dpf120mnoi     = xpf120mnoi
*
+  tox_pfet120m	    = '1.2416e-08 + deltmoxp + dtox_pfet120m_fc'
+  vfbc_pfet120m    = '-0.985 + 0.01*dpf120mvfbc + 0.0e+07*(tox_pfet120m-12.416n) + dvfbc_pfet120m_fc'
+  cgso_pfet120m    = '1.00e-10 + 0.20e-10*dpf120mcgso + dcgso_pfet120m_fc'
+  cgdo_pfet120m    = '1.50e-09 + 0.30e-09*dpf120mcgdo + dcgdo_pfet120m_fc'
+  cj_pfet120m	    = '6.880e-04 + 1.376e-04*dpf120mcj + dcj_pfet120m_fc'
+  loverld_pfet120m = '6.50e-07 + 0.650e-07*dpf120mloverld + dloverld_pfet120m_fc'
+  sc1_pfet120m	    = '0.0 + 0.0*dpf120msc1 + dsc1_pfet120m_fc'
+  sc2_pfet120m	    = '0.0 + 0.0*dpf120msc2 + dsc2_pfet120m_fc'
+  sc3_pfet120m	    = '1.00e-06 + 0.0*dpf120msc3 + dsc3_pfet120m_fc'
+  nsubc_pfet120m   = '1.390e+17 + 0.0973e+17*dpf120mnsubc + dnsubc_pfet120m_fc'
+  rd_pfet120m	    = '4.95e-02 + 0.61875e-02*dpf120mrd + drd_pfet120m_fc'
+  vmax_pfet120m    = '0.81e+07 + 0.08586e+07*dpf120mvmax - 1.0e+08*(rd_pfet120m-4.95e-02) + dvmax_pfet120m_fc'
+  mueph1_pfet120m  = '7763.0 + 465.78*dpf120mmueph1 + dmueph1_pfet120m_fc'
+  xld_pfet120m	    = '7.75e-08 + 1.55e-08*dpf120mxld + dxld_pfet120m_fc'
+  xldld_pfet120m   = '-3.0e-07 + 0.60e-07*dpf120mxldld + dxldld_pfet120m_fc'
*
*					    HV DN/SX Diode
.param
+  xcj_dnsx   = agauss('-cnr_hv_diode',1,3)
+  dcj_dnsx   = xcj_dnsx
+  xcjsw_dnsx = agauss('-cnr_hv_diode',1,3)
+  dcjsw_dnsx = xcjsw_dnsx
+  xjs_dnsx   = agauss(cnr_hv_diode,1,3)
+  djs_dnsx   = xjs_dnsx
*
+  cj_diodednsx   = '5.300e-05 + 1.300e-05*dcj_dnsx'
+  cjsw_diodednsx = '1.050e-09 + 0.250e-09*dcjsw_dnsx'
+  n_dnsx         = 1.04
+  js_dnsx        = '2.9u*(1+0.5*djs_dnsx)'
+  jsw_dnsx       = '25p*(1+0.5*djs_dnsx)'
+  lka_dnsx       = 0.0u
+  vlka_dnsx      = 1.0
+  lkp_dnsx       = 0.0p
+  vlkp_dnsx      = 1.0
*
*					    HV PW/DN Diode
.param
+  xcj_pwdn   = agauss('-cnr_hv_diode',1,3)
+  dcj_pwdn   = xcj_pwdn
+  xcjsw_pwdn = agauss('-cnr_hv_diode',1,3)
+  dcjsw_pwdn = xcjsw_pwdn
+  xjs_pwdn   = agauss(cnr_hv_diode,1,3)
+  djs_pwdn   = xjs_pwdn
*
+  cj_diodepwdn   = '2.5910e-04 + 3.1100e-05*dcj_pwdn'
+  cjsw_diodepwdn = '5.6720e-10 + 6.8100e-11*dcjsw_pwdn'
+  n_pwdn         = 1.2
+  js_pwdn        = '850n*(1+0.5*djs_pwdn)'
+  jsw_pwdn       = '19p*(1+0.5*djs_pwdn)'
+  lka_pwdn       = 'exp(-13.82+2.3*djs_pwdn)'
+  vlka_pwdn      = 1.3
+  lkp_pwdn       = 'exp(-26.24+2.3*djs_pwdn)'
+  vlkp_pwdn      = 1.3
*
*					    HV ND/PW Diode
.param
+  xcj_ndpw   = agauss('-cnr_hv_diode',1,3)
+  dcj_ndpw   = xcj_ndpw
+  xcjsw_ndpw = agauss('-cnr_hv_diode',1,3)
+  dcjsw_ndpw = xcjsw_ndpw
+  xjs_ndpw   = agauss(cnr_hv_diode,1,3)
+  djs_ndpw   = xjs_ndpw
*
+  cj_diodendpw   = '9.0530e-04 + 1.0870e-04 * dcj_ndpw'
+  cjsw_diodendpw = '0.0 + 0.0*dcjsw_ndpw'
+  n_ndpw         = 1.05
+  js_ndpw        = '140n*(1+0.5*djs_ndpw)'
+  jsw_ndpw       = '150f*(1+0.5*djs_ndpw)'
+  lka_ndpw       = 'exp(-8.42+2.3*djs_ndpw)'
+  vlka_ndpw      = 0.6
+  lkp_ndpw       = 0.0p
+  vlkp_ndpw      = 0.01
*
*					    HV NW Resistor
.param
+  xbeta_hvnwr = agauss('-cnr_hv_res',1,3)
+  dbeta_hvnwr = xbeta_hvnwr
+  xwd_hvnwr   = agauss(cnr_hv_res,1,3)
+  dwd_hvnwr   = xwd_hvnwr
+  xcgsa_hvnwr = agauss(cnr_hv_res,1,3)
+  dcgsa_hvnwr = xcgsa_hvnwr
+  xcgsp_hvnwr = agauss(cnr_hv_res,1,3)
+  dcgsp_hvnwr = xcgsp_hvnwr
+  xcgda_hvnwr = agauss(cnr_hv_res,1,3)
+  dcgda_hvnwr = xcgda_hvnwr
+  xcgdp_hvnwr = agauss(cnr_hv_res,1,3)
+  dcgdp_hvnwr = xcgdp_hvnwr
*
+  beta_hvnwr  = '2.1175e-06 + 4.3185e-07*dbeta_hvnwr + beta_hvnwr_fc'
+  wd_hvnwr    = '-2.136e-06 + 4.9980e-07*dwd_hvnwr + wd_hvnwr_fc'
+  cgsa_hvnwr  = '5.6250e-05 + 8.4400e-06*dcgsa_hvnwr + cgsa_hvnwr_fc'
+  cgsp_hvnwr  = '4.0250e-10 + 6.0400e-11*dcgsp_hvnwr + cgsp_hvnwr_fc'
+  cgda_hvnwr  = '5.6250e-05 + 8.4400e-06*dcgda_hvnwr + cgda_hvnwr_fc'
+  cgdp_hvnwr  = '4.0250e-10 + 6.0400e-11*dcgdp_hvnwr + cgdp_hvnwr_fc'
*
*					    HV PW Resistor
.param
+  xbeta_hvpwr = agauss('-cnr_hv_res',1,3)
+  dbeta_hvpwr = xbeta_hvpwr
+  xwd_hvpwr   = agauss(cnr_hv_res,1,3)
+  dwd_hvpwr   = xwd_hvpwr
+  xcgsa_hvpwr = agauss(cnr_hv_res,1,3)
+  dcgsa_hvpwr = xcgsa_hvpwr
+  xcgsp_hvpwr = agauss(cnr_hv_res,1,3)
+  dcgsp_hvpwr = xcgsp_hvpwr
+  xcgda_hvpwr = agauss(cnr_hv_res,1,3)
+  dcgda_hvpwr = xcgda_hvpwr
+  xcgdp_hvpwr = agauss(cnr_hv_res,1,3)
+  dcgdp_hvpwr = xcgdp_hvpwr
*
+  beta_hvpwr  = '1.7037e-06 + 1.9165e-07*dbeta_hvpwr + beta_hvpwr_fc'
+  wd_hvpwr    = '-2.371e-06 + 2.5000e-07*dwd_hvpwr + wd_hvpwr_fc'
+  cgsa_hvpwr  = '5.6250e-05 + 8.4400e-06*dcgsa_hvpwr + cgsa_hvpwr_fc'
+  cgsp_hvpwr  = '4.0250e-10 + 6.0400e-11*dcgsp_hvpwr + cgsp_hvpwr_fc'
+  cgda_hvpwr  = '5.6250e-05 + 8.4400e-06*dcgda_hvpwr + cgda_hvpwr_fc'
+  cgdp_hvpwr  = '4.0250e-10 + 6.0400e-11*dcgdp_hvpwr + cgdp_hvpwr_fc'
*
*					    HV PJFET
.param
+  xvta_pjfet    = agauss('-cnr_hv_res',1,3)
+  dvta_pjfet    = xvta_pjfet
+  xcgsa_pjfet   = agauss(cnr_hv_res,1,3)
+  dcgsa_pjfet   = xcgsa_pjfet
+  xcgsp_pjfet   = agauss(cnr_hv_res,1,3)
+  dcgsp_pjfet   = xcgsp_pjfet
+  xcgda_pjfet   = agauss(cnr_hv_res,1,3)
+  dcgda_pjfet   = xcgda_pjfet
+  xcgdp_pjfet   = agauss(cnr_hv_res,1,3)
+  dcgdp_pjfet   = xcgdp_pjfet
*
+  vta_pjfet     = '-0.7111 + exp(1.135 + 1.03*(dvta_pjfet + vta_pjfet_fc))'
+  beta_pjfet    = '1.0e-06 / (0.1215 + 0.0168*vta_pjfet)'
+  lambda_pjfet  = '12.96e-07 - 4.36e-07*vta_pjfet + 0.4e-07*vta_pjfet**2'
+  cgsa_pjfet    = '1.2955e-04 + 1.9450e-05*dcgsa_pjfet + cgsa_pjfet_fc'
+  cgsp_pjfet    = '5.6720e-10 + 8.5100e-11*dcgsp_pjfet + cgsp_pjfet_fc'
+  cgda_pjfet    = '1.2955e-04 + 1.9450e-05*dcgda_pjfet + cgda_pjfet_fc'
+  cgdp_pjfet    = '5.6720e-10 + 8.5100e-11*dcgdp_pjfet + cgdp_pjfet_fc'
*
*					    HV VNPN
.param
+  xre_hvnpn     = agauss('-cnr_hv_bip',1,3)
+  dre_hvnpn     = xre_hvnpn
+  xrbi_hvnpn    = agauss('-cnr_hv_bip',1,3)
+  drbi_hvnpn    = xrbi_hvnpn
+  xrbx_hvnpn    = agauss('-cnr_hv_bip',1,3)
+  drbx_hvnpn    = xrbx_hvnpn
+  xrci_hvnpn    = agauss('-cnr_hv_bip',1,3)
+  drci_hvnpn    = xrci_hvnpn
+  xrcx_hvnpn    = agauss('-cnr_hv_bip',1,3)
+  drcx_hvnpn    = xrcx_hvnpn
+  xcje_hvnpn    = agauss('-cnr_hv_bip',1,3)
+  dcje_hvnpn    = xcje_hvnpn
+  xcjep_hvnpn   = agauss('-cnr_hv_bip',1,3)
+  dcjep_hvnpn   = xcjep_hvnpn
+  xcjc_hvnpn    = agauss('-cnr_hv_bip',1,3)
+  dcjc_hvnpn    = xcjc_hvnpn
+  xcjcp_hvnpn   = agauss('-cnr_hv_bip',1,3)
+  dcjcp_hvnpn   = xcjcp_hvnpn
+  xis_hvnpn     = agauss(cnr_hv_bip,1,3)
+  dis_hvnpn     = xis_hvnpn
+  xibei_hvnpn   = agauss('-cnr_hv_bip',1,3)
+  dibei_hvnpn   = xibei_hvnpn
+  xiben_hvnpn   = agauss('-cnr_hv_bip',1,3)
+  diben_hvnpn   = xiben_hvnpn
+  xvef_hvnpn    = agauss('-cnr_hv_bip',1,3)
+  dvef_hvnpn    = xvef_hvnpn
+  xavc2_hvnpn   = agauss('-cnr_hv_bip',1,3)
+  davc2_hvnpn   = xavc2_hvnpn
+  xtf_hvnpn     = agauss('-cnr_hv_bip',1,3)
+  dtf_hvnpn     = xtf_hvnpn
*
+  re_hvnpn      = '60.95 + 6.10*dre_hvnpn + re_hvnpn_fc'
+  rbi_hvnpn     = '5728.0 + 636.0*drbi_hvnpn + rbi_hvnpn_fc'
+  rbx_hvnpn     = '38.9 + 4.32*drbx_hvnpn + rbx_hvnpn_fc'
+  rci_hvnpn     = '565.3 + 110.8*drci_hvnpn + rci_hvnpn_fc'
+  rcx_hvnpn     = '22.87 + 4.48*drcx_hvnpn + rcx_hvnpn_fc'
+  cje_hvnpn     = '1.1028e-15 + 0.1322e-15*dcje_hvnpn + cje_hvnpn_fc'
+  cjep_hvnpn    = '19.850e-15 + 2.3800e-15*dcjep_hvnpn + cjep_hvnpn_fc'
+  cjc_hvnpn     = '2.0510e-15 + 0.2460e-15*dcjc_hvnpn + cjc_hvnpn_fc'
+  cjcp_hvnpn    = '52.850e-15 + 6.3400e-15*dcjcp_hvnpn + cjcp_hvnpn_fc'
*
+  xdicvnpn      = '10**(0.155*dis_hvnpn)'
+  is_hvnpn      = '(6.3250e-18-0.875e-18*p5vonly)*xdicvnpn + is_hvnpn_fc'
+  xdibvnpn      = '10**((0.30+0.30*p5vonly)*dibei_hvnpn)'
+  ibei_hvnpn    = '(0.70e-19+0.125e-19*p5vonly)*xdibvnpn + (0.97e-19+0.30e-19*p5vonly)*xdicvnpn + ibei_hvnpn_fc'
+  iben_hvnpn    = '3.521e-16 + 0.599e-16*diben_hvnpn + iben_hvnpn_fc'
+  vef_hvnpn     = '(16.73+3.0*p5vonly) + (5.08+2.5*p5vonly)*dvef_hvnpn + vef_hvnpn_fc'
+  avc2_hvnpn    = '(30.0-1.045*p5vonly) + (1.35+0.20*p5vonly)*davc2_hvnpn + avc2_hvnpn_fc'
+  tf_hvnpn      = '62.13e-12 + 7.460e-12*dtf_hvnpn + tf_hvnpn_fc'
*
*					    HV VPNP
.param
+  xre_hvpnp     = agauss('-cnr_hv_bip',1,3)
+  dre_hvpnp     = xre_hvpnp
+  xrb_hvpnp     = agauss('-cnr_hv_bip',1,3)
+  drb_hvpnp     = xrb_hvpnp
+  xrbm_hvpnp    = agauss('-cnr_hv_bip',1,3)
+  drbm_hvpnp    = xrbm_hvpnp
+  xrc_hvpnp     = agauss('-cnr_hv_bip',1,3)
+  drc_hvpnp     = xrc_hvpnp
+  xcje_hvpnp    = agauss('-cnr_hv_bip',1,3)
+  dcje_hvpnp    = xcje_hvpnp
+  xcjc_hvpnp    = agauss('-cnr_hv_bip',1,3)
+  dcjc_hvpnp    = xcjc_hvpnp
+  xis_hvpnp     = agauss(cnr_hv_bip,1,3)
+  dis_hvpnp     = xis_hvpnp
+  xikf_hvpnp    = agauss(cnr_hv_bip,1,3)
+  dikf_hvpnp    = xikf_hvpnp
+  xbf_hvpnp     = agauss(cnr_hv_bip,1,3)
+  dbf_hvpnp     = xbf_hvpnp
+  xvaf_hvpnp    = agauss('-cnr_hv_bip',1,3)
+  dvaf_hvpnp    = xvaf_hvpnp
+  xtf_hvpnp     = agauss('-cnr_hv_bip',1,3)
+  dtf_hvpnp     = xtf_hvpnp
*
+  re_hvpnp      = '4.966 + 0.552*dre_hvpnp + re_hvpnp_fc'
+  rb_hvpnp      = '42.90 + 8.410*drb_hvpnp + rb_hvpnp_fc'
+  rbm_hvpnp     = '4.10 + 0.804*drbm_hvpnp + rbm_hvpnp_fc'
+  rc_hvpnp      = '7.10 + 0.852*drc_hvpnp + rc_hvpnp_fc'
+  cje_hvpnp     = '140.0e-15 + 16.80e-15*dcje_hvpnp + cje_hvpnp_fc'
+  cjc_hvpnp     = '155.0e-15 + 18.60e-15*dcjc_hvpnp + cjc_hvpnp_fc'
*
+  is_hvpnp      = '6.145e-16 + 2.250e-16*dis_hvpnp + is_hvpnp_fc'
+  ikf_hvpnp     = '2.30e-04 + 0.70e-04*dikf_hvpnp + ikf_hvpnp_fc'
+  bf_hvpnp      = '98.5 + 43.5*dbf_hvpnp + bf_hvpnp_fc'
+  vaf_hvpnp     = '91.0 + 41.0*dvaf_hvpnp + vaf_hvpnp_fc'
+  tf_hvpnp      = '2.201e-09 + 0.264e-09*dtf_hvpnp + tf_hvpnp_fc'
*
*					    HV ESDTDI20 Diode
.param
+  xrs_esdtdi20  = agauss('-cnr_hv_diode',1,3)
+  drs_esdtdi20  = xrs_esdtdi20
+  xbv_esdtdi20  = agauss('-cnr_hv_diode',1,3)
+  dbv_esdtdi20  = xbv_esdtdi20
+  xcj_esdtdi20  = agauss(cnr_hv_diode,1,3)
+  dcj_esdtdi20  = xcj_esdtdi20
*
+  rs_esdtdi20   = '7.000e-07 + 0.840e-07*drs_esdtdi20'
+  bv_esdtdi20   = '2.430e+01 + 2.600e+00*dbv_esdtdi20'
+  cj_esdtdi20   = '9.821e-04 + 1.179e-04*dcj_esdtdi20'
*
*					    HV ESDTDI25 Diode
.param
+  xrs_esdtdi25  = agauss('-cnr_hv_diode',1,3)
+  drs_esdtdi25  = xrs_esdtdi25
+  xbv_esdtdi25  = agauss('-cnr_hv_diode',1,3)
+  dbv_esdtdi25  = xbv_esdtdi25
+  xcj_esdtdi25  = agauss(cnr_hv_diode,1,3)
+  dcj_esdtdi25  = xcj_esdtdi25
*
+  rs_esdtdi25   = '2.422e-10 + 2.910e-11*drs_esdtdi25'
+  bv_esdtdi25   = '3.130e+01 + 3.100e+00*dbv_esdtdi25'
+  cj_esdtdi25   = '2.930e-04 + 3.520e-05*dcj_esdtdi25'
*
*					    HV ESDFDI25 Diode
.param
+  xrs_esdfdi25  = agauss('-cnr_hv_diode',1,3)
+  drs_esdfdi25  = xrs_esdfdi25
+  xbv_esdfdi25  = agauss('-cnr_hv_diode',1,3)
+  dbv_esdfdi25  = xbv_esdfdi25
+  xcj_esdfdi25  = agauss(cnr_hv_diode,1,3)
+  dcj_esdfdi25  = xcj_esdfdi25
*
+  rs_esdfdi25   = '3.362e-08 + 0.403e-08*drs_esdfdi25'
+  bv_esdfdi25   = '4.560e+01 + 4.950e+00*dbv_esdfdi25'
+  cj_esdfdi25   = '2.350e-04 + 2.820e-05*dcj_esdfdi25'
*
*					    HV ESDTDI50 Diode
.param
+  xrs_esdtdi50  = agauss('-cnr_hv_diode',1,3)
+  drs_esdtdi50  = xrs_esdtdi50
+  xbv_esdtdi50  = agauss('-cnr_hv_diode',1,3)
+  dbv_esdtdi50  = xbv_esdtdi50
+  xcj_esdtdi50  = agauss(cnr_hv_diode,1,3)
+  dcj_esdtdi50  = xcj_esdtdi50
*
+  rs_esdtdi50   = '3.564e-06 + 0.428e-06*drs_esdtdi50'
+  bv_esdtdi50   = '5.400e+01 + 5.800e+00*dbv_esdtdi50'
+  cj_esdtdi50   = '4.650e-04 + 5.580e-05*dcj_esdtdi50'
*
*					    HV ESDFDI50 Diode
.param
+  xrs_esdfdi50  = agauss('-cnr_hv_diode',1,3)
+  drs_esdfdi50  = xrs_esdfdi50
+  xbv_esdfdi50  = agauss('-cnr_hv_diode',1,3)
+  dbv_esdfdi50  = xbv_esdfdi50
+  xcj_esdfdi50  = agauss(cnr_hv_diode,1,3)
+  dcj_esdfdi50  = xcj_esdfdi50
*
+  rs_esdfdi50   = '2.265e-07 + 0.272e-07*drs_esdfdi50'
+  bv_esdfdi50   = '7.800e+01 + 8.100e+00*dbv_esdfdi50'
+  cj_esdfdi50   = '4.650e-04 + 5.580e-05*dcj_esdfdi50'
*
.endl hvstats
