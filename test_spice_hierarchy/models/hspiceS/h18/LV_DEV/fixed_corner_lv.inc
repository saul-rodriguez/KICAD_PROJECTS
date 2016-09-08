* Path, Component, Release: cmhv7sf/rel/HSPICE/models/fixed_corner_lv.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
* *********************************************************************
*
*>  Low Voltage MOSFET Fixed Process Corner Parameter Settings
*
*   Low Voltage MOSFET corner parameter settings only. Does not include or
*   account for flicker (1/f) noise or passive corner parameters.
*
* *********************************************************************

.lib tt_nfet
.param
+ dvfbo_nfet_fc =   0.0000e+00
+ dcjorgat_nfet_fc =   0.0000e+00
+ dcjorsti_nfet_fc =   0.0000e+00
+ dfol2_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =   0.0000e+00
+ dlov_nfet_fc =   0.0000e+00
+ dthesatl_nfet_fc =   0.0000e+00
+ dfol1_nfet_fc =   0.0000e+00
+ dtoxo_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =   0.0000e+00
+ dvfblw_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =   0.0000e+00
+ duo_nfet_fc =	  0.0000e+00
+ dwot_nfet_fc =   0.0000e+00
.endl tt_nfet

.lib ff_nfet
.param
+ dvfbo_nfet_fc =  -1.1241e-02
+ dcjorgat_nfet_fc =  -2.7609e-11
+ dcjorsti_nfet_fc =  -1.3630e-11
+ dfol2_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =   5.1960e-04
+ dcjorbot_nfet_fc =  -6.9895e-05
+ dlov_nfet_fc =   0.0000e+00
+ dthesatl_nfet_fc =  -5.2926e-03
+ dfol1_nfet_fc =   5.2421e-04
+ dtoxo_nfet_fc =  -7.8632e-11
+ dlap_nfet_fc =   2.9706e-09
+ dvfblw_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =  -7.8632e-01
+ duo_nfet_fc =	  1.4661e-03
+ dwot_nfet_fc =  -1.7474e-08
.endl ff_nfet

.lib ss_nfet
.param
+ dvfbo_nfet_fc =   1.6312e-02
+ dcjorgat_nfet_fc =   3.4365e-11
+ dcjorsti_nfet_fc =   1.6965e-11
+ dfol2_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =  -3.2703e-04
+ dcjorbot_nfet_fc =   8.6999e-05
+ dlov_nfet_fc =   0.0000e+00
+ dthesatl_nfet_fc =   8.2214e-04
+ dfol1_nfet_fc =   0.0000e+00
+ dtoxo_nfet_fc =   9.7874e-11
+ dlap_nfet_fc =  -3.6975e-09
+ dvfblw_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =   9.7874e-01
+ duo_nfet_fc =	 -2.2461e-03
+ dwot_nfet_fc =   0.0000e+00
.endl ss_nfet

.lib fs_nfet
.param
+ dvfbo_nfet_fc =  -2.5000e-02
+ dcjorgat_nfet_fc =  -7.0783e-11
+ dcjorsti_nfet_fc =  -3.4943e-11
+ dfol2_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =   7.5372e-04
+ dcjorbot_nfet_fc =  -1.7920e-04
+ dlov_nfet_fc =   0.0000e+00
+ dthesatl_nfet_fc =   0.0000e+00
+ dfol1_nfet_fc =   0.0000e+00
+ dtoxo_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =   0.0000e+00
+ dvfblw_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =  -2.0160e+00
+ duo_nfet_fc =	  2.7111e-03
+ dwot_nfet_fc =   0.0000e+00
.endl fs_nfet

.lib sf_nfet
.param
+ dvfbo_nfet_fc =   2.5000e-02
+ dcjorgat_nfet_fc =   5.6408e-11
+ dcjorsti_nfet_fc =   2.7847e-11
+ dfol2_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =  -5.3680e-04
+ dcjorbot_nfet_fc =   1.4281e-04
+ dlov_nfet_fc =   0.0000e+00
+ dthesatl_nfet_fc =   0.0000e+00
+ dfol1_nfet_fc =   0.0000e+00
+ dtoxo_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =   0.0000e+00
+ dvfblw_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =   1.6066e+00
+ duo_nfet_fc =	 -4.0063e-03
+ dwot_nfet_fc =   0.0000e+00
.endl sf_nfet

.lib fff_nfet
.param
+ dvfbo_nfet_fc =  -2.1443e-02
+ dcjorgat_nfet_fc =  -5.2667e-11
+ dcjorsti_nfet_fc =  -2.6000e-11
+ dfol2_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =   9.9119e-04
+ dcjorbot_nfet_fc =  -1.3333e-04
+ dlov_nfet_fc =   0.0000e+00
+ dthesatl_nfet_fc =  -1.0096e-02
+ dfol1_nfet_fc =   1.0000e-03
+ dtoxo_nfet_fc =  -1.5000e-10
+ dlap_nfet_fc =   5.6667e-09
+ dvfblw_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =  -1.5000e+00
+ duo_nfet_fc =	  2.7968e-03
+ dwot_nfet_fc =  -3.3333e-08
.endl fff_nfet

.lib ssf_nfet
.param
+ dvfbo_nfet_fc =   2.5000e-02
+ dcjorgat_nfet_fc =   5.2667e-11
+ dcjorsti_nfet_fc =   2.6000e-11
+ dfol2_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =  -5.0120e-04
+ dcjorbot_nfet_fc =   1.3333e-04
+ dlov_nfet_fc =   0.0000e+00
+ dthesatl_nfet_fc =   1.2600e-03
+ dfol1_nfet_fc =   0.0000e+00
+ dtoxo_nfet_fc =   1.5000e-10
+ dlap_nfet_fc =  -5.6667e-09
+ dvfblw_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =   1.5000e+00
+ duo_nfet_fc =	 -3.4423e-03
+ dwot_nfet_fc =   0.0000e+00
.endl ssf_nfet

.lib tt_pfet
.param
+ dvfbo_pfet_fc =   0.0000e+00
+ dcjorgat_pfet_fc =   0.0000e+00
+ dcjorsti_pfet_fc =   0.0000e+00
+ dfol2_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =   0.0000e+00
+ dlov_pfet_fc =   0.0000e+00
+ dthesatl_pfet_fc =   0.0000e+00
+ dfol1_pfet_fc =   0.0000e+00
+ dtoxo_pfet_fc =   0.0000e+00
+ dlap_pfet_fc =   0.0000e+00
+ dvfblw_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =   0.0000e+00
+ duo_pfet_fc =	  0.0000e+00
+ dwot_pfet_fc =   0.0000e+00
.endl tt_pfet

.lib ff_pfet
.param
+ dvfbo_pfet_fc =  -9.4358e-03
+ dcjorgat_pfet_fc =  -2.7259e-11
+ dcjorsti_pfet_fc =  -7.8632e-12
+ dfol2_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =  -5.5916e-05
+ dlov_pfet_fc =   0.0000e+00
+ dthesatl_pfet_fc =  -4.7179e-04
+ dfol1_pfet_fc =   3.6064e-03
+ dtoxo_pfet_fc =  -8.3874e-11
+ dlap_pfet_fc =   2.9706e-09
+ dvfblw_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =  -1.5726e+00
+ duo_pfet_fc =	  5.2421e-05
+ dwot_pfet_fc =  -1.7474e-08
.endl ff_pfet

.lib ss_pfet
.param
+ dvfbo_pfet_fc =   1.1745e-02
+ dcjorgat_pfet_fc =   3.3930e-11
+ dcjorsti_pfet_fc =   1.0005e-11
+ dfol2_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =  -5.8724e-04
+ dcjorbot_pfet_fc =   6.9599e-05
+ dlov_pfet_fc =   0.0000e+00
+ dthesatl_pfet_fc =   5.2199e-04
+ dfol1_pfet_fc =  -2.0002e-03
+ dtoxo_pfet_fc =   1.0440e-10
+ dlap_pfet_fc =  -3.6975e-09
+ dvfblw_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =   3.2625e+00
+ duo_pfet_fc =	 -4.5666e-04
+ dwot_pfet_fc =   2.1750e-08
.endl ss_pfet

.lib fs_pfet
.param
+ dvfbo_pfet_fc =   1.8000e-02
+ dcjorgat_pfet_fc =   7.6412e-11
+ dcjorsti_pfet_fc =   2.2532e-11
+ dfol2_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =  -9.0000e-04
+ dcjorbot_pfet_fc =   1.5674e-04
+ dlov_pfet_fc =   0.0000e+00
+ dthesatl_pfet_fc =   0.0000e+00
+ dfol1_pfet_fc =   0.0000e+00
+ dtoxo_pfet_fc =   0.0000e+00
+ dlap_pfet_fc =   0.0000e+00
+ dvfblw_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =   7.3473e+00
+ duo_pfet_fc =	 -1.0000e-03
+ dwot_pfet_fc =   0.0000e+00
.endl fs_pfet

.lib sf_pfet
.param
+ dvfbo_pfet_fc =  -1.0800e-02
+ dcjorgat_pfet_fc =  -3.1200e-11
+ dcjorsti_pfet_fc =  -9.0000e-12
+ dfol2_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =   9.0000e-04
+ dcjorbot_pfet_fc =  -6.4000e-05
+ dlov_pfet_fc =   0.0000e+00
+ dthesatl_pfet_fc =   0.0000e+00
+ dfol1_pfet_fc =   0.0000e+00
+ dtoxo_pfet_fc =   0.0000e+00
+ dlap_pfet_fc =   0.0000e+00
+ dvfblw_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =  -1.8000e+00
+ duo_pfet_fc =	  1.0000e-03
+ dwot_pfet_fc =   0.0000e+00
.endl sf_pfet

.lib fff_pfet
.param
+ dvfbo_pfet_fc =  -1.8000e-02
+ dcjorgat_pfet_fc =  -5.2000e-11
+ dcjorsti_pfet_fc =  -1.5000e-11
+ dfol2_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =  -1.0667e-04
+ dlov_pfet_fc =   0.0000e+00
+ dthesatl_pfet_fc =  -9.0000e-04
+ dfol1_pfet_fc =   6.8796e-03
+ dtoxo_pfet_fc =  -1.6000e-10
+ dlap_pfet_fc =   5.6667e-09
+ dvfblw_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =  -3.0000e+00
+ duo_pfet_fc =	  1.0000e-04
+ dwot_pfet_fc =  -3.3333e-08
.endl fff_pfet

.lib ssf_pfet
.param
+ dvfbo_pfet_fc =   1.8000e-02
+ dcjorgat_pfet_fc =   5.2000e-11
+ dcjorsti_pfet_fc =   1.5333e-11
+ dfol2_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =  -9.0000e-04
+ dcjorbot_pfet_fc =   1.0667e-04
+ dlov_pfet_fc =   0.0000e+00
+ dthesatl_pfet_fc =   8.0000e-04
+ dfol1_pfet_fc =  -3.0655e-03
+ dtoxo_pfet_fc =   1.6000e-10
+ dlap_pfet_fc =  -5.6667e-09
+ dvfblw_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =   5.0000e+00
+ duo_pfet_fc =	 -6.9986e-04
+ dwot_pfet_fc =   3.3333e-08
.endl ssf_pfet

.lib tt_nfeti
.param
+ dvfbo_nfeti_fc =   0.0000e+00
+ dcjorgat_nfeti_fc =	0.0000e+00
+ dcjorsti_nfeti_fc =	0.0000e+00
+ dfol2_nfeti_fc =   0.0000e+00
+ dvfbl_nfeti_fc =   0.0000e+00
+ dcjorbot_nfeti_fc =	0.0000e+00
+ dlov_nfeti_fc =   0.0000e+00
+ dthesatl_nfeti_fc =	0.0000e+00
+ dfol1_nfeti_fc =   0.0000e+00
+ dtoxo_nfeti_fc =   0.0000e+00
+ dlap_nfeti_fc =   0.0000e+00
+ dvfblw_nfeti_fc =   0.0000e+00
+ drsw1_nfeti_fc =   0.0000e+00
+ duo_nfeti_fc =   0.0000e+00
+ dwot_nfeti_fc =   0.0000e+00
.endl tt_nfeti

.lib ff_nfeti
.param
+ dvfbo_nfeti_fc =  -1.0937e-02
+ dcjorgat_nfeti_fc =  -3.4635e-11
+ dcjorsti_nfeti_fc =  -1.4218e-11
+ dfol2_nfeti_fc =   0.0000e+00
+ dvfbl_nfeti_fc =   5.7932e-04
+ dcjorbot_nfeti_fc =  -7.2915e-05
+ dlov_nfeti_fc =   0.0000e+00
+ dthesatl_nfeti_fc =  -7.1092e-04
+ dfol1_nfeti_fc =   0.0000e+00
+ dtoxo_nfeti_fc =  -8.2030e-11
+ dlap_nfeti_fc =   3.0989e-09
+ dvfblw_nfeti_fc =   0.0000e+00
+ drsw1_nfeti_fc =   0.0000e+00
+ duo_nfeti_fc =   1.2840e-03
+ dwot_nfeti_fc =  -1.8229e-08
.endl ff_nfeti

.lib ss_nfeti
.param
+ dvfbo_nfeti_fc =   1.2000e-02
+ dcjorgat_nfeti_fc =	3.8000e-11
+ dcjorsti_nfeti_fc =	1.5600e-11
+ dfol2_nfeti_fc =   0.0000e+00
+ dvfbl_nfeti_fc =  -4.8326e-04
+ dcjorbot_nfeti_fc =	8.0000e-05
+ dlov_nfeti_fc =   0.0000e+00
+ dthesatl_nfeti_fc =	2.3972e-03
+ dfol1_nfeti_fc =   0.0000e+00
+ dtoxo_nfeti_fc =   9.0000e-11
+ dlap_nfeti_fc =  -3.4000e-09
+ dvfblw_nfeti_fc =   0.0000e+00
+ drsw1_nfeti_fc =   9.0000e-01
+ duo_nfeti_fc =  -1.9757e-03
+ dwot_nfeti_fc =   2.0000e-08
.endl ss_nfeti

.lib fs_nfeti
.param
+ dvfbo_nfeti_fc =  -2.0000e-02
+ dcjorgat_nfeti_fc =  -6.7731e-11
+ dcjorsti_nfeti_fc =  -2.7805e-11
+ dfol2_nfeti_fc =   0.0000e+00
+ dvfbl_nfeti_fc =   1.1329e-03
+ dcjorbot_nfeti_fc =  -1.4259e-04
+ dlov_nfeti_fc =   0.0000e+00
+ dthesatl_nfeti_fc =	0.0000e+00
+ dfol1_nfeti_fc =   0.0000e+00
+ dtoxo_nfeti_fc =   0.0000e+00
+ dlap_nfeti_fc =   0.0000e+00
+ dvfblw_nfeti_fc =   0.0000e+00
+ drsw1_nfeti_fc =   0.0000e+00
+ duo_nfeti_fc =   4.2233e-03
+ dwot_nfeti_fc =   0.0000e+00
.endl fs_nfeti

.lib sf_nfeti
.param
+ dvfbo_nfeti_fc =   1.8758e-02
+ dcjorgat_nfeti_fc =	6.2037e-11
+ dcjorsti_nfeti_fc =	2.5468e-11
+ dfol2_nfeti_fc =   0.0000e+00
+ dvfbl_nfeti_fc =  -1.1164e-03
+ dcjorbot_nfeti_fc =	1.3060e-04
+ dlov_nfeti_fc =   0.0000e+00
+ dthesatl_nfeti_fc =	0.0000e+00
+ dfol1_nfeti_fc =   0.0000e+00
+ dtoxo_nfeti_fc =   0.0000e+00
+ dlap_nfeti_fc =   0.0000e+00
+ dvfblw_nfeti_fc =   0.0000e+00
+ drsw1_nfeti_fc =   1.4693e+00
+ duo_nfeti_fc =  -3.6393e-03
+ dwot_nfeti_fc =   0.0000e+00
.endl sf_nfeti

.lib fff_nfeti
.param
+ dvfbo_nfeti_fc =  -2.0000e-02
+ dcjorgat_nfeti_fc =  -6.3333e-11
+ dcjorsti_nfeti_fc =  -2.6000e-11
+ dfol2_nfeti_fc =   0.0000e+00
+ dvfbl_nfeti_fc =   1.0593e-03
+ dcjorbot_nfeti_fc =  -1.3333e-04
+ dlov_nfeti_fc =   0.0000e+00
+ dthesatl_nfeti_fc =  -1.3000e-03
+ dfol1_nfeti_fc =   0.0000e+00
+ dtoxo_nfeti_fc =  -1.5000e-10
+ dlap_nfeti_fc =   5.6667e-09
+ dvfblw_nfeti_fc =   0.0000e+00
+ drsw1_nfeti_fc =   0.0000e+00
+ duo_nfeti_fc =   2.3479e-03
+ dwot_nfeti_fc =  -3.3333e-08
.endl fff_nfeti

.lib ssf_nfeti
.param
+ dvfbo_nfeti_fc =   2.0000e-02
+ dcjorgat_nfeti_fc =	6.3333e-11
+ dcjorsti_nfeti_fc =	2.6000e-11
+ dfol2_nfeti_fc =   0.0000e+00
+ dvfbl_nfeti_fc =  -8.0543e-04
+ dcjorbot_nfeti_fc =	1.3333e-04
+ dlov_nfeti_fc =   0.0000e+00
+ dthesatl_nfeti_fc =	3.9953e-03
+ dfol1_nfeti_fc =   0.0000e+00
+ dtoxo_nfeti_fc =   1.5000e-10
+ dlap_nfeti_fc =  -5.6667e-09
+ dvfblw_nfeti_fc =   0.0000e+00
+ drsw1_nfeti_fc =   1.5000e+00
+ duo_nfeti_fc =  -3.2928e-03
+ dwot_nfeti_fc =   3.3333e-08
.endl ssf_nfeti

.lib tt_pfeti
.param
+ dvfbo_pfeti_fc =   0.0000e+00
+ dcjorgat_pfeti_fc =	0.0000e+00
+ dcjorsti_pfeti_fc =	0.0000e+00
+ dfol2_pfeti_fc =   0.0000e+00
+ dvfbl_pfeti_fc =   0.0000e+00
+ dcjorbot_pfeti_fc =	0.0000e+00
+ dlov_pfeti_fc =   0.0000e+00
+ dthesatl_pfeti_fc =	0.0000e+00
+ dfol1_pfeti_fc =   0.0000e+00
+ dtoxo_pfeti_fc =   0.0000e+00
+ dlap_pfeti_fc =   0.0000e+00
+ dvfblw_pfeti_fc =   0.0000e+00
+ drsw1_pfeti_fc =   0.0000e+00
+ duo_pfeti_fc =   0.0000e+00
+ dwot_pfeti_fc =   0.0000e+00
.endl tt_pfeti

.lib ff_pfeti
.param
+ dvfbo_pfeti_fc =  -8.2029e-03
+ dcjorgat_pfeti_fc =  -2.8437e-11
+ dcjorsti_pfeti_fc =  -8.2030e-12
+ dfol2_pfeti_fc =   0.0000e+00
+ dvfbl_pfeti_fc =   0.0000e+00
+ dcjorbot_pfeti_fc =  -5.8332e-05
+ dlov_pfeti_fc =   0.0000e+00
+ dthesatl_pfeti_fc =  -4.9218e-04
+ dfol1_pfeti_fc =   4.4520e-03
+ dtoxo_pfeti_fc =  -8.2030e-11
+ dlap_pfeti_fc =   3.0989e-09
+ dvfblw_pfeti_fc =   0.0000e+00
+ drsw1_pfeti_fc =  -1.6406e+00
+ duo_pfeti_fc =   5.4686e-05
+ dwot_pfeti_fc =  -1.8229e-08
.endl ff_pfeti

.lib ss_pfeti
.param
+ dvfbo_pfeti_fc =   9.0000e-03
+ dcjorgat_pfeti_fc =	3.1200e-11
+ dcjorsti_pfeti_fc =	9.2000e-12
+ dfol2_pfeti_fc =   0.0000e+00
+ dvfbl_pfeti_fc =  -5.4000e-04
+ dcjorbot_pfeti_fc =	6.4000e-05
+ dlov_pfeti_fc =   0.0000e+00
+ dthesatl_pfeti_fc =	4.8000e-04
+ dfol1_pfeti_fc =  -4.3949e-03
+ dtoxo_pfeti_fc =   9.0000e-11
+ dlap_pfeti_fc =  -3.4000e-09
+ dvfblw_pfeti_fc =   0.0000e+00
+ drsw1_pfeti_fc =   3.0000e+00
+ duo_pfeti_fc =  -1.4791e-04
+ dwot_pfeti_fc =   2.0000e-08
.endl ss_pfeti

.lib fs_pfeti
.param
+ dvfbo_pfeti_fc =   1.5000e-02
+ dcjorgat_pfeti_fc =	7.8000e-11
+ dcjorsti_pfeti_fc =	2.3000e-11
+ dfol2_pfeti_fc =   0.0000e+00
+ dvfbl_pfeti_fc =  -9.0000e-04
+ dcjorbot_pfeti_fc =	1.6000e-04
+ dlov_pfeti_fc =   0.0000e+00
+ dthesatl_pfeti_fc =	0.0000e+00
+ dfol1_pfeti_fc =   0.0000e+00
+ dtoxo_pfeti_fc =   0.0000e+00
+ dlap_pfeti_fc =   0.0000e+00
+ dvfblw_pfeti_fc =   0.0000e+00
+ drsw1_pfeti_fc =   8.8817e+00
+ duo_pfeti_fc =  -4.3790e-04
+ dwot_pfeti_fc =   0.0000e+00
.endl fs_pfeti

.lib sf_pfeti
.param
+ dvfbo_pfeti_fc =  -9.0000e-03
+ dcjorgat_pfeti_fc =  -3.1200e-11
+ dcjorsti_pfeti_fc =  -9.0000e-12
+ dfol2_pfeti_fc =   0.0000e+00
+ dvfbl_pfeti_fc =   9.0000e-04
+ dcjorbot_pfeti_fc =  -6.4000e-05
+ dlov_pfeti_fc =   0.0000e+00
+ dthesatl_pfeti_fc =	0.0000e+00
+ dfol1_pfeti_fc =   0.0000e+00
+ dtoxo_pfeti_fc =   0.0000e+00
+ dlap_pfeti_fc =   0.0000e+00
+ dvfblw_pfeti_fc =   0.0000e+00
+ drsw1_pfeti_fc =  -1.8000e+00
+ duo_pfeti_fc =   1.0000e-03
+ dwot_pfeti_fc =   0.0000e+00
.endl sf_pfeti

.lib fff_pfeti
.param
+ dvfbo_pfeti_fc =  -1.5000e-02
+ dcjorgat_pfeti_fc =  -5.2000e-11
+ dcjorsti_pfeti_fc =  -1.5000e-11
+ dfol2_pfeti_fc =   0.0000e+00
+ dvfbl_pfeti_fc =   0.0000e+00
+ dcjorbot_pfeti_fc =  -1.0667e-04
+ dlov_pfeti_fc =   0.0000e+00
+ dthesatl_pfeti_fc =  -9.0000e-04
+ dfol1_pfeti_fc =   8.1409e-03
+ dtoxo_pfeti_fc =  -1.5000e-10
+ dlap_pfeti_fc =   5.6667e-09
+ dvfblw_pfeti_fc =   0.0000e+00
+ drsw1_pfeti_fc =  -3.0000e+00
+ duo_pfeti_fc =   1.0000e-04
+ dwot_pfeti_fc =  -3.3333e-08
.endl fff_pfeti

.lib ssf_pfeti
.param
+ dvfbo_pfeti_fc =   1.5000e-02
+ dcjorgat_pfeti_fc =	5.2000e-11
+ dcjorsti_pfeti_fc =	1.5333e-11
+ dfol2_pfeti_fc =   0.0000e+00
+ dvfbl_pfeti_fc =  -9.0000e-04
+ dcjorbot_pfeti_fc =	1.0667e-04
+ dlov_pfeti_fc =   0.0000e+00
+ dthesatl_pfeti_fc =	8.0000e-04
+ dfol1_pfeti_fc =  -7.3248e-03
+ dtoxo_pfeti_fc =   1.5000e-10
+ dlap_pfeti_fc =  -5.6667e-09
+ dvfblw_pfeti_fc =   0.0000e+00
+ drsw1_pfeti_fc =   5.0000e+00
+ duo_pfeti_fc =  -2.4652e-04
+ dwot_pfeti_fc =   3.3333e-08
.endl ssf_pfeti

.lib tt_nfethvt
.param
+ dvfbo_nfethvt_fc =   0.0000e+00
+ dcjorgat_nfethvt_fc =	  0.0000e+00
+ dcjorsti_nfethvt_fc =	  0.0000e+00
+ dfol2_nfethvt_fc =   0.0000e+00
+ dvfbl_nfethvt_fc =   0.0000e+00
+ dcjorbot_nfethvt_fc =	  0.0000e+00
+ dlov_nfethvt_fc =   0.0000e+00
+ dthesatl_nfethvt_fc =	  0.0000e+00
+ dfol1_nfethvt_fc =   0.0000e+00
+ dtoxo_nfethvt_fc =   0.0000e+00
+ dlap_nfethvt_fc =   0.0000e+00
+ dvfblw_nfethvt_fc =	0.0000e+00
+ drsw1_nfethvt_fc =   0.0000e+00
+ duo_nfethvt_fc =   0.0000e+00
+ dwot_nfethvt_fc =   0.0000e+00
.endl tt_nfethvt

.lib ff_nfethvt
.param
+ dvfbo_nfethvt_fc =  -1.2181e-02
+ dcjorgat_nfethvt_fc =	 -5.6843e-11
+ dcjorsti_nfethvt_fc =	 -2.4361e-11
+ dfol2_nfethvt_fc =   0.0000e+00
+ dvfbl_nfethvt_fc =   0.0000e+00
+ dcjorbot_nfethvt_fc =	 -1.0827e-04
+ dlov_nfethvt_fc =   0.0000e+00
+ dthesatl_nfethvt_fc =	 -7.5790e-03
+ dfol1_nfethvt_fc =   3.7893e-03
+ dtoxo_nfethvt_fc =  -1.2790e-10
+ dlap_nfethvt_fc =   5.1429e-09
+ dvfblw_nfethvt_fc =	0.0000e+00
+ drsw1_nfethvt_fc =  -3.4329e+00
+ duo_nfethvt_fc =   1.7514e-03
+ dwot_nfethvt_fc =  -2.7068e-08
.endl ff_nfethvt

.lib ss_nfethvt
.param
+ dvfbo_nfethvt_fc =   9.3140e-03
+ dcjorgat_nfethvt_fc =	  4.3465e-11
+ dcjorsti_nfethvt_fc =	  1.8628e-11
+ dfol2_nfethvt_fc =   0.0000e+00
+ dvfbl_nfethvt_fc =  -5.5884e-04
+ dcjorbot_nfethvt_fc =	  8.2791e-05
+ dlov_nfethvt_fc =   0.0000e+00
+ dthesatl_nfethvt_fc =	  8.6931e-04
+ dfol1_nfethvt_fc =  -1.0144e-03
+ dtoxo_nfethvt_fc =   1.0090e-10
+ dlap_nfethvt_fc =  -3.1047e-09
+ dvfblw_nfethvt_fc =	0.0000e+00
+ drsw1_nfethvt_fc =   4.0982e-01
+ duo_nfethvt_fc =  -1.7937e-03
+ dwot_nfethvt_fc =   2.0698e-08
.endl ss_nfethvt

.lib fs_nfethvt
.param
+ dvfbo_nfethvt_fc =  -1.5000e-02
+ dcjorgat_nfethvt_fc =	 -1.0500e-10
+ dcjorsti_nfethvt_fc =	 -4.5000e-11
+ dfol2_nfethvt_fc =   0.0000e+00
+ dvfbl_nfethvt_fc =   0.0000e+00
+ dcjorbot_nfethvt_fc =	 -2.0000e-04
+ dlov_nfethvt_fc =   0.0000e+00
+ dthesatl_nfethvt_fc =	  0.0000e+00
+ dfol1_nfethvt_fc =   0.0000e+00
+ dtoxo_nfethvt_fc =   0.0000e+00
+ dlap_nfethvt_fc =   0.0000e+00
+ dvfblw_nfethvt_fc =	0.0000e+00
+ drsw1_nfethvt_fc =  -6.6000e+00
+ duo_nfethvt_fc =   3.9799e-03
+ dwot_nfethvt_fc =   0.0000e+00
.endl fs_nfethvt

.lib sf_nfethvt
.param
+ dvfbo_nfethvt_fc =   1.5000e-02
+ dcjorgat_nfethvt_fc =	  7.7971e-11
+ dcjorsti_nfethvt_fc =	  3.3416e-11
+ dfol2_nfethvt_fc =   0.0000e+00
+ dvfbl_nfethvt_fc =  -9.0000e-04
+ dcjorbot_nfethvt_fc =	  1.4852e-04
+ dlov_nfethvt_fc =   0.0000e+00
+ dthesatl_nfethvt_fc =	  0.0000e+00
+ dfol1_nfethvt_fc =   0.0000e+00
+ dtoxo_nfethvt_fc =   0.0000e+00
+ dlap_nfethvt_fc =   0.0000e+00
+ dvfblw_nfethvt_fc =	0.0000e+00
+ drsw1_nfethvt_fc =   7.3516e-01
+ duo_nfethvt_fc =  -3.2177e-03
+ dwot_nfethvt_fc =   0.0000e+00
.endl sf_nfethvt

.lib fff_nfethvt
.param
+ dvfbo_nfethvt_fc =  -1.5000e-02
+ dcjorgat_nfethvt_fc =	 -7.0000e-11
+ dcjorsti_nfethvt_fc =	 -3.0000e-11
+ dfol2_nfethvt_fc =   0.0000e+00
+ dvfbl_nfethvt_fc =   0.0000e+00
+ dcjorbot_nfethvt_fc =	 -1.3333e-04
+ dlov_nfethvt_fc =   0.0000e+00
+ dthesatl_nfethvt_fc =	 -9.3333e-03
+ dfol1_nfethvt_fc =   4.6664e-03
+ dtoxo_nfethvt_fc =  -1.5750e-10
+ dlap_nfethvt_fc =   6.3333e-09
+ dvfblw_nfethvt_fc =	0.0000e+00
+ drsw1_nfethvt_fc =  -4.2275e+00
+ duo_nfethvt_fc =   2.1568e-03
+ dwot_nfethvt_fc =  -3.3333e-08
.endl fff_nfethvt

.lib ssf_nfethvt
.param
+ dvfbo_nfethvt_fc =   1.5000e-02
+ dcjorgat_nfethvt_fc =	  7.0000e-11
+ dcjorsti_nfethvt_fc =	  3.0000e-11
+ dfol2_nfethvt_fc =   0.0000e+00
+ dvfbl_nfethvt_fc =  -9.0000e-04
+ dcjorbot_nfethvt_fc =	  1.3333e-04
+ dlov_nfethvt_fc =   0.0000e+00
+ dthesatl_nfethvt_fc =	  1.4000e-03
+ dfol1_nfethvt_fc =  -1.6337e-03
+ dtoxo_nfethvt_fc =   1.6250e-10
+ dlap_nfethvt_fc =  -5.0000e-09
+ dvfblw_nfethvt_fc =	0.0000e+00
+ drsw1_nfethvt_fc =   6.6000e-01
+ duo_nfethvt_fc =  -2.8887e-03
+ dwot_nfethvt_fc =   3.3333e-08
.endl ssf_nfethvt

.lib tt_pfethvt
.param
+ dvfbo_pfethvt_fc =   0.0000e+00
+ dcjorgat_pfethvt_fc =	  0.0000e+00
+ dcjorsti_pfethvt_fc =	  0.0000e+00
+ dfol2_pfethvt_fc =   0.0000e+00
+ dvfbl_pfethvt_fc =   0.0000e+00
+ dcjorbot_pfethvt_fc =	  0.0000e+00
+ dlov_pfethvt_fc =   0.0000e+00
+ dthesatl_pfethvt_fc =	  0.0000e+00
+ dfol1_pfethvt_fc =   0.0000e+00
+ dtoxo_pfethvt_fc =   0.0000e+00
+ dlap_pfethvt_fc =   0.0000e+00
+ dvfblw_pfethvt_fc =	0.0000e+00
+ drsw1_pfethvt_fc =   0.0000e+00
+ duo_pfethvt_fc =   0.0000e+00
+ dwot_pfethvt_fc =   0.0000e+00
.endl tt_pfethvt

.lib ff_pfethvt
.param
+ dvfbo_pfethvt_fc =  -8.1204e-03
+ dcjorgat_pfethvt_fc =	 -4.9805e-11
+ dcjorsti_pfethvt_fc =	 -1.2993e-11
+ dfol2_pfethvt_fc =   0.0000e+00
+ dvfbl_pfethvt_fc =   0.0000e+00
+ dcjorbot_pfethvt_fc =	 -4.8722e-05
+ dlov_pfethvt_fc =   0.0000e+00
+ dthesatl_pfethvt_fc =	 -2.4361e-04
+ dfol1_pfethvt_fc =   3.3962e-03
+ dtoxo_pfethvt_fc =  -1.2993e-10
+ dlap_pfethvt_fc =   4.6016e-09
+ dvfblw_pfethvt_fc =	0.0000e+00
+ drsw1_pfethvt_fc =  -2.4361e+00
+ duo_pfethvt_fc =   1.6241e-04
+ dwot_pfethvt_fc =  -2.7068e-08
.endl ff_pfethvt

.lib ss_pfethvt
.param
+ dvfbo_pfethvt_fc =   6.2093e-03
+ dcjorgat_pfethvt_fc =	  3.8498e-11
+ dcjorsti_pfethvt_fc =	  1.1177e-11
+ dfol2_pfethvt_fc =   0.0000e+00
+ dvfbl_pfethvt_fc =  -6.2093e-04
+ dcjorbot_pfethvt_fc =	  9.5210e-05
+ dlov_pfethvt_fc =   0.0000e+00
+ dthesatl_pfethvt_fc =	  1.8628e-04
+ dfol1_pfethvt_fc =  -1.4609e-03
+ dtoxo_pfethvt_fc =   9.9350e-11
+ dlap_pfethvt_fc =  -3.5186e-09
+ dvfblw_pfethvt_fc =	0.0000e+00
+ drsw1_pfethvt_fc =   3.1047e+00
+ duo_pfethvt_fc =  -9.2947e-04
+ dwot_pfethvt_fc =   2.0698e-08
.endl ss_pfethvt

.lib fs_pfethvt
.param
+ dvfbo_pfethvt_fc =   1.0000e-02
+ dcjorgat_pfethvt_fc =	  8.3594e-11
+ dcjorsti_pfethvt_fc =	  2.4269e-11
+ dfol2_pfethvt_fc =   0.0000e+00
+ dvfbl_pfethvt_fc =  -1.0000e-03
+ dcjorbot_pfethvt_fc =	  2.0674e-04
+ dlov_pfethvt_fc =   0.0000e+00
+ dthesatl_pfethvt_fc =	  0.0000e+00
+ dfol1_pfethvt_fc =   0.0000e+00
+ dtoxo_pfethvt_fc =   0.0000e+00
+ dlap_pfethvt_fc =   0.0000e+00
+ dvfblw_pfethvt_fc =	0.0000e+00
+ drsw1_pfethvt_fc =   6.7415e+00
+ duo_pfethvt_fc =  -2.0000e-03
+ dwot_pfethvt_fc =   0.0000e+00
.endl fs_pfethvt

.lib sf_pfethvt
.param
+ dvfbo_pfethvt_fc =  -6.0000e-03
+ dcjorgat_pfethvt_fc =	 -3.6800e-11
+ dcjorsti_pfethvt_fc =	 -9.6000e-12
+ dfol2_pfethvt_fc =   0.0000e+00
+ dvfbl_pfethvt_fc =   1.0000e-03
+ dcjorbot_pfethvt_fc =	 -3.6000e-05
+ dlov_pfethvt_fc =   0.0000e+00
+ dthesatl_pfethvt_fc =	  0.0000e+00
+ dfol1_pfethvt_fc =   0.0000e+00
+ dtoxo_pfethvt_fc =   0.0000e+00
+ dlap_pfethvt_fc =   0.0000e+00
+ dvfblw_pfethvt_fc =	0.0000e+00
+ drsw1_pfethvt_fc =  -1.8000e+00
+ duo_pfethvt_fc =   2.0000e-03
+ dwot_pfethvt_fc =   0.0000e+00
.endl sf_pfethvt

.lib fff_pfethvt
.param
+ dvfbo_pfethvt_fc =  -1.0000e-02
+ dcjorgat_pfethvt_fc =	 -6.1333e-11
+ dcjorsti_pfethvt_fc =	 -1.6000e-11
+ dfol2_pfethvt_fc =   0.0000e+00
+ dvfbl_pfethvt_fc =   0.0000e+00
+ dcjorbot_pfethvt_fc =	 -6.0000e-05
+ dlov_pfethvt_fc =   0.0000e+00
+ dthesatl_pfethvt_fc =	 -3.0000e-04
+ dfol1_pfethvt_fc =   4.1824e-03
+ dtoxo_pfethvt_fc =  -1.6000e-10
+ dlap_pfethvt_fc =   5.6667e-09
+ dvfblw_pfethvt_fc =	0.0000e+00
+ drsw1_pfethvt_fc =  -3.0000e+00
+ duo_pfethvt_fc =   2.0000e-04
+ dwot_pfethvt_fc =  -3.3333e-08
.endl fff_pfethvt

.lib ssf_pfethvt
.param
+ dvfbo_pfethvt_fc =   1.0000e-02
+ dcjorgat_pfethvt_fc =	  6.2000e-11
+ dcjorsti_pfethvt_fc =	  1.8000e-11
+ dfol2_pfethvt_fc =   0.0000e+00
+ dvfbl_pfethvt_fc =  -1.0000e-03
+ dcjorbot_pfethvt_fc =	  1.5333e-04
+ dlov_pfethvt_fc =   0.0000e+00
+ dthesatl_pfethvt_fc =	  3.0000e-04
+ dfol1_pfethvt_fc =  -2.3527e-03
+ dtoxo_pfethvt_fc =   1.6000e-10
+ dlap_pfethvt_fc =  -5.6667e-09
+ dvfblw_pfethvt_fc =	0.0000e+00
+ drsw1_pfethvt_fc =   5.0000e+00
+ duo_pfethvt_fc =  -1.4969e-03
+ dwot_pfethvt_fc =   3.3333e-08
.endl ssf_pfethvt

.lib tt_nfetihvt
.param
+ dvfbo_nfetihvt_fc =	0.0000e+00
+ dcjorgat_nfetihvt_fc =   0.0000e+00
+ dcjorsti_nfetihvt_fc =   0.0000e+00
+ dfol2_nfetihvt_fc =	0.0000e+00
+ dvfbl_nfetihvt_fc =	0.0000e+00
+ dcjorbot_nfetihvt_fc =   0.0000e+00
+ dlov_nfetihvt_fc =   0.0000e+00
+ dthesatl_nfetihvt_fc =   0.0000e+00
+ dfol1_nfetihvt_fc =	0.0000e+00
+ dtoxo_nfetihvt_fc =	0.0000e+00
+ dlap_nfetihvt_fc =   0.0000e+00
+ dvfblw_nfetihvt_fc =	 0.0000e+00
+ drsw1_nfetihvt_fc =	0.0000e+00
+ duo_nfetihvt_fc =   0.0000e+00
+ dwot_nfetihvt_fc =   0.0000e+00
.endl tt_nfetihvt

.lib ff_nfetihvt
.param
+ dvfbo_nfetihvt_fc =  -8.1485e-03
+ dcjorgat_nfetihvt_fc =  -5.7040e-11
+ dcjorsti_nfetihvt_fc =  -2.4989e-11
+ dfol2_nfetihvt_fc =	0.0000e+00
+ dvfbl_nfetihvt_fc =	0.0000e+00
+ dcjorbot_nfetihvt_fc =  -1.0865e-04
+ dlov_nfetihvt_fc =   0.0000e+00
+ dthesatl_nfetihvt_fc =  -1.0186e-02
+ dfol1_nfetihvt_fc =	3.3161e-03
+ dtoxo_nfetihvt_fc =  -1.3649e-10
+ dlap_nfetihvt_fc =   5.1607e-09
+ dvfblw_nfetihvt_fc =	 0.0000e+00
+ drsw1_nfetihvt_fc =  -5.3780e-01
+ duo_nfetihvt_fc =   1.6281e-03
+ dwot_nfetihvt_fc =  -2.7162e-08
.endl ff_nfetihvt

.lib ss_nfetihvt
.param
+ dvfbo_nfetihvt_fc =	5.8672e-03
+ dcjorgat_nfetihvt_fc =   4.1071e-11
+ dcjorsti_nfetihvt_fc =   1.7993e-11
+ dfol2_nfetihvt_fc =	0.0000e+00
+ dvfbl_nfetihvt_fc =  -2.9336e-04
+ dcjorbot_nfetihvt_fc =   7.8230e-05
+ dlov_nfetihvt_fc =   0.0000e+00
+ dthesatl_nfetihvt_fc =   8.8009e-04
+ dfol1_nfetihvt_fc =  -2.1938e-03
+ dtoxo_nfetihvt_fc =	1.0121e-10
+ dlap_nfetihvt_fc =  -2.9336e-09
+ dvfblw_nfetihvt_fc =	 0.0000e+00
+ drsw1_nfetihvt_fc =	3.8724e-01
+ duo_nfetihvt_fc =  -1.8991e-03
+ dwot_nfetihvt_fc =   1.9557e-08
.endl ss_nfetihvt

.lib fs_nfetihvt
.param
+ dvfbo_nfetihvt_fc =  -8.3333e-03
+ dcjorgat_nfetihvt_fc =  -4.2000e-11
+ dcjorsti_nfetihvt_fc =  -1.8400e-11
+ dfol2_nfetihvt_fc =	0.0000e+00
+ dvfbl_nfetihvt_fc =	3.3333e-04
+ dcjorbot_nfetihvt_fc =  -8.0000e-05
+ dlov_nfetihvt_fc =   0.0000e+00
+ dthesatl_nfetihvt_fc =   0.0000e+00
+ dfol1_nfetihvt_fc =	0.0000e+00
+ dtoxo_nfetihvt_fc =	0.0000e+00
+ dlap_nfetihvt_fc =   0.0000e+00
+ dvfblw_nfetihvt_fc =	 0.0000e+00
+ drsw1_nfetihvt_fc =  -3.9600e-01
+ duo_nfetihvt_fc =   4.4400e-03
+ dwot_nfetihvt_fc =   0.0000e+00
.endl fs_nfetihvt

.lib sf_nfetihvt
.param
+ dvfbo_nfetihvt_fc =	1.0000e-02
+ dcjorgat_nfetihvt_fc =   1.0500e-10
+ dcjorsti_nfetihvt_fc =   4.6000e-11
+ dfol2_nfetihvt_fc =	0.0000e+00
+ dvfbl_nfetihvt_fc =  -5.0000e-04
+ dcjorbot_nfetihvt_fc =   2.0000e-04
+ dlov_nfetihvt_fc =   0.0000e+00
+ dthesatl_nfetihvt_fc =   0.0000e+00
+ dfol1_nfetihvt_fc =	0.0000e+00
+ dtoxo_nfetihvt_fc =	0.0000e+00
+ dlap_nfetihvt_fc =   0.0000e+00
+ dvfblw_nfetihvt_fc =	 0.0000e+00
+ drsw1_nfetihvt_fc =	1.0120e+00
+ duo_nfetihvt_fc =  -4.9633e-03
+ dwot_nfetihvt_fc =   0.0000e+00
.endl sf_nfetihvt

.lib fff_nfetihvt
.param
+ dvfbo_nfetihvt_fc =  -1.0000e-02
+ dcjorgat_nfetihvt_fc =  -7.0000e-11
+ dcjorsti_nfetihvt_fc =  -3.0667e-11
+ dfol2_nfetihvt_fc =	0.0000e+00
+ dvfbl_nfetihvt_fc =	0.0000e+00
+ dcjorbot_nfetihvt_fc =  -1.3333e-04
+ dlov_nfetihvt_fc =   0.0000e+00
+ dthesatl_nfetihvt_fc =  -1.2500e-02
+ dfol1_nfetihvt_fc =	4.0696e-03
+ dtoxo_nfetihvt_fc =  -1.6750e-10
+ dlap_nfetihvt_fc =   6.3333e-09
+ dvfblw_nfetihvt_fc =	 0.0000e+00
+ drsw1_nfetihvt_fc =  -6.6000e-01
+ duo_nfetihvt_fc =   1.9980e-03
+ dwot_nfetihvt_fc =  -3.3333e-08
.endl fff_nfetihvt

.lib ssf_nfetihvt
.param
+ dvfbo_nfetihvt_fc =	1.0000e-02
+ dcjorgat_nfetihvt_fc =   7.0000e-11
+ dcjorsti_nfetihvt_fc =   3.0667e-11
+ dfol2_nfetihvt_fc =	0.0000e+00
+ dvfbl_nfetihvt_fc =  -5.0000e-04
+ dcjorbot_nfetihvt_fc =   1.3333e-04
+ dlov_nfetihvt_fc =   0.0000e+00
+ dthesatl_nfetihvt_fc =   1.5000e-03
+ dfol1_nfetihvt_fc =  -3.7391e-03
+ dtoxo_nfetihvt_fc =	1.7250e-10
+ dlap_nfetihvt_fc =  -5.0000e-09
+ dvfblw_nfetihvt_fc =	 0.0000e+00
+ drsw1_nfetihvt_fc =	6.6000e-01
+ duo_nfetihvt_fc =  -3.2369e-03
+ dwot_nfetihvt_fc =   3.3333e-08
.endl ssf_nfetihvt

.lib tt_pfetihvt
.param
+ dvfbo_pfetihvt_fc =	0.0000e+00
+ dcjorgat_pfetihvt_fc =   0.0000e+00
+ dcjorsti_pfetihvt_fc =   0.0000e+00
+ dfol2_pfetihvt_fc =	0.0000e+00
+ dvfbl_pfetihvt_fc =	0.0000e+00
+ dcjorbot_pfetihvt_fc =   0.0000e+00
+ dlov_pfetihvt_fc =   0.0000e+00
+ dthesatl_pfetihvt_fc =   0.0000e+00
+ dfol1_pfetihvt_fc =	0.0000e+00
+ dtoxo_pfetihvt_fc =	0.0000e+00
+ dlap_pfetihvt_fc =   0.0000e+00
+ dvfblw_pfetihvt_fc =	 0.0000e+00
+ drsw1_pfetihvt_fc =	0.0000e+00
+ duo_pfetihvt_fc =   0.0000e+00
+ dwot_pfetihvt_fc =   0.0000e+00
.endl tt_pfetihvt

.lib ff_pfetihvt
.param
+ dvfbo_pfetihvt_fc =  -8.1485e-03
+ dcjorgat_pfetihvt_fc =  -5.8126e-11
+ dcjorsti_pfetihvt_fc =  -1.3146e-11
+ dfol2_pfetihvt_fc =	0.0000e+00
+ dvfbl_pfetihvt_fc =	0.0000e+00
+ dcjorbot_pfetihvt_fc =  -8.6917e-05
+ dlov_pfetihvt_fc =   0.0000e+00
+ dthesatl_pfetihvt_fc =  -2.4445e-04
+ dfol1_pfetihvt_fc =	3.8428e-03
+ dtoxo_pfetihvt_fc =  -1.3038e-10
+ dlap_pfetihvt_fc =   4.6175e-09
+ dvfblw_pfetihvt_fc =	 0.0000e+00
+ drsw1_pfetihvt_fc =  -2.4446e+00
+ duo_pfetihvt_fc =   8.1485e-05
+ dwot_pfetihvt_fc =  -2.7162e-08
.endl ff_pfetihvt

.lib ss_pfetihvt
.param
+ dvfbo_pfetihvt_fc =	5.8672e-03
+ dcjorgat_pfetihvt_fc =   4.2244e-11
+ dcjorsti_pfetihvt_fc =   9.3094e-12
+ dfol2_pfetihvt_fc =  -1.7602e-04
+ dvfbl_pfetihvt_fc =  -5.8672e-04
+ dcjorbot_pfetihvt_fc =   6.2584e-05
+ dlov_pfetihvt_fc =   0.0000e+00
+ dthesatl_pfetihvt_fc =   1.1734e-03
+ dfol1_pfetihvt_fc =  -4.1071e-03
+ dtoxo_pfetihvt_fc =	0.0000e+00
+ dlap_pfetihvt_fc =  -3.3248e-09
+ dvfblw_pfetihvt_fc =	 0.0000e+00
+ drsw1_pfetihvt_fc =	1.7602e+01
+ duo_pfetihvt_fc =  -5.8672e-04
+ dwot_pfetihvt_fc =   1.9557e-08
.endl ss_pfetihvt

.lib fs_pfetihvt
.param
+ dvfbo_pfetihvt_fc =	1.0000e-02
+ dcjorgat_pfetihvt_fc =   1.0800e-10
+ dcjorsti_pfetihvt_fc =   2.3800e-11
+ dfol2_pfetihvt_fc =	0.0000e+00
+ dvfbl_pfetihvt_fc =  -1.0000e-03
+ dcjorbot_pfetihvt_fc =   1.6000e-04
+ dlov_pfetihvt_fc =   0.0000e+00
+ dthesatl_pfetihvt_fc =   0.0000e+00
+ dfol1_pfetihvt_fc =	0.0000e+00
+ dtoxo_pfetihvt_fc =	0.0000e+00
+ dlap_pfetihvt_fc =   0.0000e+00
+ dvfblw_pfetihvt_fc =	 0.0000e+00
+ drsw1_pfetihvt_fc =	3.0000e+01
+ duo_pfetihvt_fc =  -1.0000e-03
+ dwot_pfetihvt_fc =   0.0000e+00
.endl fs_pfetihvt

.lib sf_pfetihvt
.param
+ dvfbo_pfetihvt_fc =  -8.3333e-03
+ dcjorgat_pfetihvt_fc =  -4.2800e-11
+ dcjorsti_pfetihvt_fc =  -9.6800e-12
+ dfol2_pfetihvt_fc =	0.0000e+00
+ dvfbl_pfetihvt_fc =	1.0000e-03
+ dcjorbot_pfetihvt_fc =  -6.4000e-05
+ dlov_pfetihvt_fc =   0.0000e+00
+ dthesatl_pfetihvt_fc =   0.0000e+00
+ dfol1_pfetihvt_fc =	0.0000e+00
+ dtoxo_pfetihvt_fc =	0.0000e+00
+ dlap_pfetihvt_fc =   0.0000e+00
+ dvfblw_pfetihvt_fc =	 0.0000e+00
+ drsw1_pfetihvt_fc =  -1.8000e+00
+ duo_pfetihvt_fc =   1.0000e-03
+ dwot_pfetihvt_fc =   0.0000e+00
.endl sf_pfetihvt

.lib fff_pfetihvt
.param
+ dvfbo_pfetihvt_fc =  -1.0000e-02
+ dcjorgat_pfetihvt_fc =  -7.1333e-11
+ dcjorsti_pfetihvt_fc =  -1.6133e-11
+ dfol2_pfetihvt_fc =	0.0000e+00
+ dvfbl_pfetihvt_fc =	0.0000e+00
+ dcjorbot_pfetihvt_fc =  -1.0667e-04
+ dlov_pfetihvt_fc =   0.0000e+00
+ dthesatl_pfetihvt_fc =  -3.0000e-04
+ dfol1_pfetihvt_fc =	4.7160e-03
+ dtoxo_pfetihvt_fc =  -1.6000e-10
+ dlap_pfetihvt_fc =   5.6667e-09
+ dvfblw_pfetihvt_fc =	 0.0000e+00
+ drsw1_pfetihvt_fc =  -3.0000e+00
+ duo_pfetihvt_fc =   1.0000e-04
+ dwot_pfetihvt_fc =  -3.3333e-08
.endl fff_pfetihvt

.lib ssf_pfetihvt
.param
+ dvfbo_pfetihvt_fc =	1.0000e-02
+ dcjorgat_pfetihvt_fc =   7.2000e-11
+ dcjorsti_pfetihvt_fc =   1.5867e-11
+ dfol2_pfetihvt_fc =  -3.0000e-04
+ dvfbl_pfetihvt_fc =  -1.0000e-03
+ dcjorbot_pfetihvt_fc =   1.0667e-04
+ dlov_pfetihvt_fc =   0.0000e+00
+ dthesatl_pfetihvt_fc =   2.0000e-03
+ dfol1_pfetihvt_fc =  -7.0000e-03
+ dtoxo_pfetihvt_fc =	0.0000e+00
+ dlap_pfetihvt_fc =  -5.6667e-09
+ dvfblw_pfetihvt_fc =	 0.0000e+00
+ drsw1_pfetihvt_fc =	3.0000e+01
+ duo_pfetihvt_fc =  -1.0000e-03
+ dwot_pfetihvt_fc =   3.3333e-08
.endl ssf_pfetihvt


.lib tt_nfetshvt
.param
+ dvfbo_nfetshvt_fc =   0.0000e+00
+ dcjorsti_nfetshvt_fc =   0.0000e+00
+ dcjorgat_nfetshvt_fc =   0.0000e+00
+ dfol2_nfetshvt_fc =   0.0000e+00
+ dvfbl_nfetshvt_fc =   0.0000e+00
+ dlov_nfetshvt_fc =   0.0000e+00
+ dcjorbot_nfetshvt_fc =   0.0000e+00
+ dthesatl_nfetshvt_fc =   0.0000e+00
+ dfol1_nfetshvt_fc =   0.0000e+00
+ dtoxo_nfetshvt_fc =   0.0000e+00
+ dlap_nfetshvt_fc =   0.0000e+00
+ dvfblw_nfetshvt_fc =   0.0000e+00
+ drsw1_nfetshvt_fc =   0.0000e+00
+ duo_nfetshvt_fc =   0.0000e+00
+ dwot_nfetshvt_fc =   0.0000e+00
.endl tt_nfetshvt

.lib ff_nfetshvt
.param
+ dvfbo_nfetshvt_fc =   0.0000e+00
+ dcjorsti_nfetshvt_fc =  -2.9963e-11
+ dcjorgat_nfetshvt_fc =  -3.2801e-11
+ dfol2_nfetshvt_fc =   4.7309e-07
+ dvfbl_nfetshvt_fc =   0.0000e+00
+ dlov_nfetshvt_fc =  -2.2860e-09
+ dcjorbot_nfetshvt_fc =  -1.2616e-04
+ dthesatl_nfetshvt_fc =   0.0000e+00
+ dfol1_nfetshvt_fc =   5.5263e-04
+ dtoxo_nfetshvt_fc =  -1.5139e-10
+ dlap_nfetshvt_fc =   5.3617e-09
+ dvfblw_nfetshvt_fc =   0.0000e+00
+ drsw1_nfetshvt_fc =  -4.7172e+00
+ duo_nfetshvt_fc =   1.4647e-03
+ dwot_nfetshvt_fc =  -3.1540e-08
.endl ff_nfetshvt

.lib ss_nfetshvt
.param
+ dvfbo_nfetshvt_fc =   0.0000e+00
+ dcjorsti_nfetshvt_fc =   2.2440e-11
+ dcjorgat_nfetshvt_fc =   2.4566e-11
+ dfol2_nfetshvt_fc =  -3.5432e-07
+ dvfbl_nfetshvt_fc =   0.0000e+00
+ dlov_nfetshvt_fc =   1.7121e-09
+ dcjorbot_nfetshvt_fc =   9.4485e-05
+ dthesatl_nfetshvt_fc =   0.0000e+00
+ dfol1_nfetshvt_fc =  -1.8604e-03
+ dtoxo_nfetshvt_fc =   1.1338e-10
+ dlap_nfetshvt_fc =  -4.0156e-09
+ dvfblw_nfetshvt_fc =   0.0000e+00
+ drsw1_nfetshvt_fc =   1.6367e+00
+ duo_nfetshvt_fc =  -1.8432e-03
+ dwot_nfetshvt_fc =   2.3621e-08
.endl ss_nfetshvt

.lib fs_nfetshvt
.param
+ dvfbo_nfetshvt_fc =  -2.8501e-02
+ dcjorsti_nfetshvt_fc =  -3.1667e-11
+ dcjorgat_nfetshvt_fc =  -3.4667e-11
+ dfol2_nfetshvt_fc =   5.0000e-07
+ dvfbl_nfetshvt_fc =   0.0000e+00
+ dlov_nfetshvt_fc =  -2.4160e-09
+ dcjorbot_nfetshvt_fc =  -1.3333e-04
+ dthesatl_nfetshvt_fc =   0.0000e+00
+ dfol1_nfetshvt_fc =   5.8406e-04
+ dtoxo_nfetshvt_fc =   0.0000e+00
+ dlap_nfetshvt_fc =   0.0000e+00
+ dvfblw_nfetshvt_fc =   0.0000e+00
+ drsw1_nfetshvt_fc =  -4.9855e+00
+ duo_nfetshvt_fc =   4.3333e-03
+ dwot_nfetshvt_fc =   0.0000e+00
.endl fs_nfetshvt

.lib sf_nfetshvt
.param
+ dvfbo_nfetshvt_fc =   3.0855e-02
+ dcjorsti_nfetshvt_fc =   3.1667e-11
+ dcjorgat_nfetshvt_fc =   3.4667e-11
+ dfol2_nfetshvt_fc =  -5.0000e-07
+ dvfbl_nfetshvt_fc =   0.0000e+00
+ dlov_nfetshvt_fc =   2.4160e-09
+ dcjorbot_nfetshvt_fc =   1.3333e-04
+ dthesatl_nfetshvt_fc =   0.0000e+00
+ dfol1_nfetshvt_fc =  -1.4133e-03
+ dtoxo_nfetshvt_fc =   0.0000e+00
+ dlap_nfetshvt_fc =   0.0000e+00
+ dvfblw_nfetshvt_fc =   0.0000e+00
+ drsw1_nfetshvt_fc =   2.3097e+00
+ duo_nfetshvt_fc =  -2.6010e-03
+ dwot_nfetshvt_fc =   0.0000e+00
.endl sf_nfetshvt

.lib fff_nfetshvt
.param
+ dvfbo_nfetshvt_fc =  -2.8501e-02
+ dcjorsti_nfetshvt_fc =  -3.1667e-11
+ dcjorgat_nfetshvt_fc =  -3.4667e-11
+ dfol2_nfetshvt_fc =   5.0000e-07
+ dvfbl_nfetshvt_fc =   0.0000e+00
+ dlov_nfetshvt_fc =  -2.4160e-09
+ dcjorbot_nfetshvt_fc =  -1.3333e-04
+ dthesatl_nfetshvt_fc =   0.0000e+00
+ dfol1_nfetshvt_fc =   5.8406e-04
+ dtoxo_nfetshvt_fc =  -1.6000e-10
+ dlap_nfetshvt_fc =   5.6667e-09
+ dvfblw_nfetshvt_fc =   0.0000e+00
+ drsw1_nfetshvt_fc =  -4.9855e+00
+ duo_nfetshvt_fc =   1.5480e-03
+ dwot_nfetshvt_fc =  -3.3333e-08
.endl fff_nfetshvt

.lib ssf_nfetshvt
.param
+ dvfbo_nfetshvt_fc =   3.0855e-02
+ dcjorsti_nfetshvt_fc =   3.1667e-11
+ dcjorgat_nfetshvt_fc =   3.4667e-11
+ dfol2_nfetshvt_fc =  -5.0000e-07
+ dvfbl_nfetshvt_fc =   0.0000e+00
+ dlov_nfetshvt_fc =   2.4160e-09
+ dcjorbot_nfetshvt_fc =   1.3333e-04
+ dthesatl_nfetshvt_fc =   0.0000e+00
+ dfol1_nfetshvt_fc =  -2.6253e-03
+ dtoxo_nfetshvt_fc =   1.6000e-10
+ dlap_nfetshvt_fc =  -5.6667e-09
+ dvfblw_nfetshvt_fc =   0.0000e+00
+ drsw1_nfetshvt_fc =   2.3097e+00
+ duo_nfetshvt_fc =  -2.6010e-03
+ dwot_nfetshvt_fc =   3.3333e-08
.endl ssf_nfetshvt

.lib tt_pfetshvt
.param
+ dvfbo_pfetshvt_fc =   0.0000e+00
+ dcjorsti_pfetshvt_fc =   0.0000e+00
+ dcjorgat_pfetshvt_fc =   0.0000e+00
+ dfol2_pfetshvt_fc =   0.0000e+00
+ dvfbl_pfetshvt_fc =   0.0000e+00
+ dlov_pfetshvt_fc =   0.0000e+00
+ dcjorbot_pfetshvt_fc =   0.0000e+00
+ dthesatl_pfetshvt_fc =   0.0000e+00
+ dfol1_pfetshvt_fc =   0.0000e+00
+ dtoxo_pfetshvt_fc =   0.0000e+00
+ dlap_pfetshvt_fc =   0.0000e+00
+ dvfblw_pfetshvt_fc =   0.0000e+00
+ drsw1_pfetshvt_fc =   0.0000e+00
+ duo_pfetshvt_fc =   0.0000e+00
+ dwot_pfetshvt_fc =   0.0000e+00
.endl tt_pfetshvt

.lib ff_pfetshvt
.param
+ dvfbo_pfetshvt_fc =   0.0000e+00
+ dcjorsti_pfetshvt_fc =  -1.1039e-11
+ dcjorgat_pfetshvt_fc =   0.0000e+00
+ dfol2_pfetshvt_fc =   1.5101e-03
+ dvfbl_pfetshvt_fc =   0.0000e+00
+ dlov_pfetshvt_fc =  -2.2336e-09
+ dcjorbot_pfetshvt_fc =  -1.0093e-04
+ dthesatl_pfetshvt_fc =   0.0000e+00
+ dfol1_pfetshvt_fc =   2.0816e-03
+ dtoxo_pfetshvt_fc =  -1.5139e-10
+ dlap_pfetshvt_fc =   5.3617e-09
+ dvfblw_pfetshvt_fc =   0.0000e+00
+ drsw1_pfetshvt_fc =  -1.5612e+01
+ duo_pfetshvt_fc =   8.4369e-04
+ dwot_pfetshvt_fc =  -3.1540e-08
.endl ff_pfetshvt

.lib ss_pfetshvt
.param
+ dvfbo_pfetshvt_fc =   0.0000e+00
+ dcjorsti_pfetshvt_fc =   8.2675e-12
+ dcjorgat_pfetshvt_fc =   0.0000e+00
+ dfol2_pfetshvt_fc =  -2.3387e-03
+ dvfbl_pfetshvt_fc =   0.0000e+00
+ dlov_pfetshvt_fc =   1.6729e-09
+ dcjorbot_pfetshvt_fc =   7.5588e-05
+ dthesatl_pfetshvt_fc =   0.0000e+00
+ dfol1_pfetshvt_fc =  -1.7773e-03
+ dtoxo_pfetshvt_fc =   1.1338e-10
+ dlap_pfetshvt_fc =  -4.0156e-09
+ dvfblw_pfetshvt_fc =   0.0000e+00
+ drsw1_pfetshvt_fc =   1.1693e+01
+ duo_pfetshvt_fc =  -1.2701e-03
+ dwot_pfetshvt_fc =   2.3621e-08
.endl ss_pfetshvt

.lib fs_pfetshvt
.param
+ dvfbo_pfetshvt_fc =   2.3583e-02
+ dcjorsti_pfetshvt_fc =   7.7679e-12
+ dcjorgat_pfetshvt_fc =   0.0000e+00
+ dfol2_pfetshvt_fc =  -2.1974e-03
+ dvfbl_pfetshvt_fc =   0.0000e+00
+ dlov_pfetshvt_fc =   1.5718e-09
+ dcjorbot_pfetshvt_fc =   7.1021e-05
+ dthesatl_pfetshvt_fc =   0.0000e+00
+ dfol1_pfetshvt_fc =  -1.6699e-03
+ dtoxo_pfetshvt_fc =   0.0000e+00
+ dlap_pfetshvt_fc =   0.0000e+00
+ dvfblw_pfetshvt_fc =   0.0000e+00
+ drsw1_pfetshvt_fc =   1.0986e+01
+ duo_pfetshvt_fc =  -1.1933e-03
+ dwot_pfetshvt_fc =   0.0000e+00
.endl fs_pfetshvt

.lib sf_pfetshvt
.param
+ dvfbo_pfetshvt_fc =  -3.3954e-02
+ dcjorsti_pfetshvt_fc =  -1.0456e-11
+ dcjorgat_pfetshvt_fc =   0.0000e+00
+ dfol2_pfetshvt_fc =   1.4303e-03
+ dvfbl_pfetshvt_fc =   0.0000e+00
+ dlov_pfetshvt_fc =  -2.1156e-09
+ dcjorbot_pfetshvt_fc =  -9.5594e-05
+ dthesatl_pfetshvt_fc =   0.0000e+00
+ dfol1_pfetshvt_fc =   1.9716e-03
+ dtoxo_pfetshvt_fc =   0.0000e+00
+ dlap_pfetshvt_fc =   0.0000e+00
+ dvfblw_pfetshvt_fc =   0.0000e+00
+ drsw1_pfetshvt_fc =  -1.4787e+01
+ duo_pfetshvt_fc =   7.9910e-04
+ dwot_pfetshvt_fc =   0.0000e+00
.endl sf_pfetshvt

.lib fff_pfetshvt
.param
+ dvfbo_pfetshvt_fc =  -3.7887e-02
+ dcjorsti_pfetshvt_fc =  -1.1667e-11
+ dcjorgat_pfetshvt_fc =   0.0000e+00
+ dfol2_pfetshvt_fc =   1.5960e-03
+ dvfbl_pfetshvt_fc =   0.0000e+00
+ dlov_pfetshvt_fc =  -2.3607e-09
+ dcjorbot_pfetshvt_fc =  -1.0667e-04
+ dthesatl_pfetshvt_fc =   0.0000e+00
+ dfol1_pfetshvt_fc =   2.2000e-03
+ dtoxo_pfetshvt_fc =  -1.6000e-10
+ dlap_pfetshvt_fc =   5.6667e-09
+ dvfblw_pfetshvt_fc =   0.0000e+00
+ drsw1_pfetshvt_fc =  -1.6500e+01
+ duo_pfetshvt_fc =   8.9167e-04
+ dwot_pfetshvt_fc =  -3.3333e-08
.endl fff_pfetshvt

.lib ssf_pfetshvt
.param
+ dvfbo_pfetshvt_fc =   3.5419e-02
+ dcjorsti_pfetshvt_fc =   1.1667e-11
+ dcjorgat_pfetshvt_fc =   0.0000e+00
+ dfol2_pfetshvt_fc =  -3.3003e-03
+ dvfbl_pfetshvt_fc =   0.0000e+00
+ dlov_pfetshvt_fc =   2.3607e-09
+ dcjorbot_pfetshvt_fc =   1.0667e-04
+ dthesatl_pfetshvt_fc =   0.0000e+00
+ dfol1_pfetshvt_fc =  -2.5080e-03
+ dtoxo_pfetshvt_fc =   1.6000e-10
+ dlap_pfetshvt_fc =  -5.6667e-09
+ dvfblw_pfetshvt_fc =   0.0000e+00
+ drsw1_pfetshvt_fc =   1.6500e+01
+ duo_pfetshvt_fc =  -1.7923e-03
+ dwot_pfetshvt_fc =   3.3333e-08
.endl ssf_pfetshvt


.lib tt_nfetm
.param
+ dvfbo_nfetm_fc =   0.0000e+00
+ dcjorsti_nfetm_fc =	0.0000e+00
+ dcjorgat_nfetm_fc =	0.0000e+00
+ dfol2_nfetm_fc =   0.0000e+00
+ dvfbl_nfetm_fc =   0.0000e+00
+ dcjorbot_nfetm_fc =	0.0000e+00
+ dlov_nfetm_fc =   0.0000e+00
+ dfol1_nfetm_fc =   0.0000e+00
+ dtoxo_nfetm_fc =   0.0000e+00
+ dthesatl_nfetm_fc =	0.0000e+00
+ dlap_nfetm_fc =   0.0000e+00
+ dvfblw_nfetm_fc =   0.0000e+00
+ drsw1_nfetm_fc =   0.0000e+00
+ duo_nfetm_fc =   0.0000e+00
+ dwot_nfetm_fc =   0.0000e+00
.endl tt_nfetm

.lib ff_nfetm
.param
+ dvfbo_nfetm_fc =  -1.9631e-02
+ dcjorsti_nfetm_fc =  -1.4872e-11
+ dcjorgat_nfetm_fc =  -3.0934e-11
+ dfol2_nfetm_fc =   0.0000e+00
+ dvfbl_nfetm_fc =   0.0000e+00
+ dcjorbot_nfetm_fc =  -7.7336e-05
+ dlov_nfetm_fc =   0.0000e+00
+ dfol1_nfetm_fc =   2.3201e-03
+ dtoxo_nfetm_fc =  -3.7032e-10
+ dthesatl_nfetm_fc =	0.0000e+00
+ dlap_nfetm_fc =   1.4872e-08
+ dvfblw_nfetm_fc =   0.0000e+00
+ drsw1_nfetm_fc =  -4.7591e+00
+ duo_nfetm_fc =   6.7476e-04
+ dwot_nfetm_fc =  -2.9744e-08
.endl ff_nfetm

.lib ss_nfetm
.param
+ dvfbo_nfetm_fc =   1.6067e-02
+ dcjorsti_nfetm_fc =	1.2172e-11
+ dcjorgat_nfetm_fc =	2.5317e-11
+ dfol2_nfetm_fc =   0.0000e+00
+ dvfbl_nfetm_fc =   0.0000e+00
+ dcjorbot_nfetm_fc =	6.3292e-05
+ dlov_nfetm_fc =   0.0000e+00
+ dfol1_nfetm_fc =  -1.8988e-03
+ dtoxo_nfetm_fc =   3.0307e-10
+ dthesatl_nfetm_fc =	0.0000e+00
+ dlap_nfetm_fc =  -1.2172e-08
+ dvfblw_nfetm_fc =   0.0000e+00
+ drsw1_nfetm_fc =   3.8949e+00
+ duo_nfetm_fc =  -6.2912e-04
+ dwot_nfetm_fc =   2.4343e-08
.endl ss_nfetm

.lib fs_nfetm
.param
+ dvfbo_nfetm_fc =  -2.2000e-02
+ dcjorsti_nfetm_fc =  -2.3963e-11
+ dcjorgat_nfetm_fc =  -4.9843e-11
+ dfol2_nfetm_fc =   0.0000e+00
+ dvfbl_nfetm_fc =   0.0000e+00
+ dcjorbot_nfetm_fc =  -1.2461e-04
+ dlov_nfetm_fc =   0.0000e+00
+ dfol1_nfetm_fc =   0.0000e+00
+ dtoxo_nfetm_fc =   0.0000e+00
+ dthesatl_nfetm_fc =	0.0000e+00
+ dlap_nfetm_fc =   0.0000e+00
+ dvfblw_nfetm_fc =   0.0000e+00
+ drsw1_nfetm_fc =  -7.6681e+00
+ duo_nfetm_fc =   1.0872e-03
+ dwot_nfetm_fc =   0.0000e+00
.endl fs_nfetm

.lib sf_nfetm
.param
+ dvfbo_nfetm_fc =   2.2000e-02
+ dcjorsti_nfetm_fc =	2.3071e-11
+ dcjorgat_nfetm_fc =	4.7988e-11
+ dfol2_nfetm_fc =   0.0000e+00
+ dvfbl_nfetm_fc =   0.0000e+00
+ dcjorbot_nfetm_fc =	1.1997e-04
+ dlov_nfetm_fc =   0.0000e+00
+ dfol1_nfetm_fc =   0.0000e+00
+ dtoxo_nfetm_fc =   0.0000e+00
+ dthesatl_nfetm_fc =	0.0000e+00
+ dlap_nfetm_fc =   0.0000e+00
+ dvfblw_nfetm_fc =   0.0000e+00
+ drsw1_nfetm_fc =   7.3828e+00
+ duo_nfetm_fc =  -1.1925e-03
+ dwot_nfetm_fc =   0.0000e+00
.endl sf_nfetm

.lib fff_nfetm
.param
+ dvfbo_nfetm_fc =  -2.2000e-02
+ dcjorsti_nfetm_fc =  -1.6667e-11
+ dcjorgat_nfetm_fc =  -3.4667e-11
+ dfol2_nfetm_fc =   0.0000e+00
+ dvfbl_nfetm_fc =   0.0000e+00
+ dcjorbot_nfetm_fc =  -8.6667e-05
+ dlov_nfetm_fc =   0.0000e+00
+ dfol1_nfetm_fc =   2.6000e-03
+ dtoxo_nfetm_fc =  -4.1500e-10
+ dthesatl_nfetm_fc =	0.0000e+00
+ dlap_nfetm_fc =   1.6667e-08
+ dvfblw_nfetm_fc =   0.0000e+00
+ drsw1_nfetm_fc =  -5.3333e+00
+ duo_nfetm_fc =   7.5617e-04
+ dwot_nfetm_fc =  -3.3333e-08
.endl fff_nfetm

.lib ssf_nfetm
.param
+ dvfbo_nfetm_fc =   2.2000e-02
+ dcjorsti_nfetm_fc =	1.6667e-11
+ dcjorgat_nfetm_fc =	3.4667e-11
+ dfol2_nfetm_fc =   0.0000e+00
+ dvfbl_nfetm_fc =   0.0000e+00
+ dcjorbot_nfetm_fc =	8.6667e-05
+ dlov_nfetm_fc =   0.0000e+00
+ dfol1_nfetm_fc =  -2.6000e-03
+ dtoxo_nfetm_fc =   4.1500e-10
+ dthesatl_nfetm_fc =	0.0000e+00
+ dlap_nfetm_fc =  -1.6667e-08
+ dvfblw_nfetm_fc =   0.0000e+00
+ drsw1_nfetm_fc =   5.3333e+00
+ duo_nfetm_fc =  -8.6145e-04
+ dwot_nfetm_fc =   3.3333e-08
.endl ssf_nfetm

.lib tt_pfetm
.param
+ dvfbo_pfetm_fc =   0.0000e+00
+ dcjorsti_pfetm_fc =	0.0000e+00
+ dcjorgat_pfetm_fc =	0.0000e+00
+ dfol2_pfetm_fc =   0.0000e+00
+ dvfbl_pfetm_fc =   0.0000e+00
+ dcjorbot_pfetm_fc =	0.0000e+00
+ dlov_pfetm_fc =   0.0000e+00
+ dfol1_pfetm_fc =   0.0000e+00
+ dtoxo_pfetm_fc =   0.0000e+00
+ dthesatl_pfetm_fc =	0.0000e+00
+ dlap_pfetm_fc =   0.0000e+00
+ dvfblw_pfetm_fc =   0.0000e+00
+ drsw1_pfetm_fc =   0.0000e+00
+ duo_pfetm_fc =   0.0000e+00
+ dwot_pfetm_fc =   0.0000e+00
.endl tt_pfetm

.lib ff_pfetm
.param
+ dvfbo_pfetm_fc =  -3.4355e-02
+ dcjorsti_pfetm_fc =  -1.1957e-11
+ dcjorgat_pfetm_fc =  -2.4866e-11
+ dfol2_pfetm_fc =   9.8157e-05
+ dvfbl_pfetm_fc =   0.0000e+00
+ dcjorbot_pfetm_fc =  -8.3285e-05
+ dlov_pfetm_fc =   0.0000e+00
+ dfol1_pfetm_fc =   1.3831e-03
+ dtoxo_pfetm_fc =  -3.5693e-10
+ dthesatl_pfetm_fc =  -8.5664e-05
+ dlap_pfetm_fc =   1.4872e-08
+ dvfblw_pfetm_fc =   0.0000e+00
+ drsw1_pfetm_fc =  -2.0078e+01
+ duo_pfetm_fc =   8.5307e-05
+ dwot_pfetm_fc =  -2.9744e-08
.endl ff_pfetm

.lib ss_pfetm
.param
+ dvfbo_pfetm_fc =   5.7109e-03
+ dcjorsti_pfetm_fc =	9.7860e-12
+ dcjorgat_pfetm_fc =	2.0351e-11
+ dfol2_pfetm_fc =  -8.0333e-04
+ dvfbl_pfetm_fc =   0.0000e+00
+ dcjorbot_pfetm_fc =	6.8161e-05
+ dlov_pfetm_fc =   0.0000e+00
+ dfol1_pfetm_fc =  -1.1320e-02
+ dtoxo_pfetm_fc =   2.9212e-10
+ dthesatl_pfetm_fc =	7.0108e-05
+ dlap_pfetm_fc =  -1.2172e-08
+ dvfblw_pfetm_fc =   0.0000e+00
+ drsw1_pfetm_fc =   1.6432e+02
+ duo_pfetm_fc =  -1.1636e-04
+ dwot_pfetm_fc =   2.4343e-08
.endl ss_pfetm

.lib fs_pfetm
.param
+ dvfbo_pfetm_fc =   2.6067e-02
+ dcjorsti_pfetm_fc =	8.0400e-12
+ dcjorgat_pfetm_fc =	1.6720e-11
+ dfol2_pfetm_fc =   0.0000e+00
+ dvfbl_pfetm_fc =   0.0000e+00
+ dcjorbot_pfetm_fc =	5.6000e-05
+ dlov_pfetm_fc =   0.0000e+00
+ dfol1_pfetm_fc =   0.0000e+00
+ dtoxo_pfetm_fc =   0.0000e+00
+ dthesatl_pfetm_fc =	0.0000e+00
+ dlap_pfetm_fc =   0.0000e+00
+ dvfblw_pfetm_fc =   0.0000e+00
+ drsw1_pfetm_fc =   1.3500e+02
+ duo_pfetm_fc =  -9.5600e-05
+ dwot_pfetm_fc =   0.0000e+00
.endl fs_pfetm

.lib sf_pfetm
.param
+ dvfbo_pfetm_fc =  -3.8500e-02
+ dcjorsti_pfetm_fc =  -1.5313e-11
+ dcjorgat_pfetm_fc =  -3.1845e-11
+ dfol2_pfetm_fc =   0.0000e+00
+ dvfbl_pfetm_fc =   0.0000e+00
+ dcjorbot_pfetm_fc =  -1.0666e-04
+ dlov_pfetm_fc =   0.0000e+00
+ dfol1_pfetm_fc =   0.0000e+00
+ dtoxo_pfetm_fc =   0.0000e+00
+ dthesatl_pfetm_fc =	0.0000e+00
+ dlap_pfetm_fc =   0.0000e+00
+ dvfblw_pfetm_fc =   0.0000e+00
+ drsw1_pfetm_fc =  -2.5712e+01
+ duo_pfetm_fc =   1.0925e-04
+ dwot_pfetm_fc =   0.0000e+00
.endl sf_pfetm

.lib fff_pfetm
.param
+ dvfbo_pfetm_fc =  -3.8500e-02
+ dcjorsti_pfetm_fc =  -1.3400e-11
+ dcjorgat_pfetm_fc =  -2.7867e-11
+ dfol2_pfetm_fc =   1.1000e-04
+ dvfbl_pfetm_fc =   0.0000e+00
+ dcjorbot_pfetm_fc =  -9.3333e-05
+ dlov_pfetm_fc =   0.0000e+00
+ dfol1_pfetm_fc =   1.5500e-03
+ dtoxo_pfetm_fc =  -4.0000e-10
+ dthesatl_pfetm_fc =  -9.6000e-05
+ dlap_pfetm_fc =   1.6667e-08
+ dvfblw_pfetm_fc =   0.0000e+00
+ drsw1_pfetm_fc =  -2.2500e+01
+ duo_pfetm_fc =   9.5600e-05
+ dwot_pfetm_fc =  -3.3333e-08
.endl fff_pfetm

.lib ssf_pfetm
.param
+ dvfbo_pfetm_fc =   7.8200e-03
+ dcjorsti_pfetm_fc =	1.3400e-11
+ dcjorgat_pfetm_fc =	2.7867e-11
+ dfol2_pfetm_fc =  -1.1000e-03
+ dvfbl_pfetm_fc =   0.0000e+00
+ dcjorbot_pfetm_fc =	9.3333e-05
+ dlov_pfetm_fc =   0.0000e+00
+ dfol1_pfetm_fc =  -1.5500e-02
+ dtoxo_pfetm_fc =   4.0000e-10
+ dthesatl_pfetm_fc =	9.6000e-05
+ dlap_pfetm_fc =  -1.6667e-08
+ dvfblw_pfetm_fc =   0.0000e+00
+ drsw1_pfetm_fc =   2.2500e+02
+ duo_pfetm_fc =  -1.5933e-04
+ dwot_pfetm_fc =   3.3333e-08
.endl ssf_pfetm

.lib tt_nfetim
.param
+ dvfbo_nfetim_fc =   0.0000e+00
+ dcjorsti_nfetim_fc =	 0.0000e+00
+ dcjorgat_nfetim_fc =	 0.0000e+00
+ dfol2_nfetim_fc =   0.0000e+00
+ dvfbl_nfetim_fc =   0.0000e+00
+ dcjorbot_nfetim_fc =	 0.0000e+00
+ dlov_nfetim_fc =   0.0000e+00
+ dfol1_nfetim_fc =   0.0000e+00
+ dtoxo_nfetim_fc =   0.0000e+00
+ dthesatl_nfetim_fc =	 0.0000e+00
+ dlap_nfetim_fc =   0.0000e+00
+ dvfblw_nfetim_fc =   0.0000e+00
+ drsw1_nfetim_fc =   0.0000e+00
+ duo_nfetim_fc =   0.0000e+00
+ dwot_nfetim_fc =   0.0000e+00
.endl tt_nfetim

.lib ff_nfetim
.param
+ dvfbo_nfetim_fc =  -1.8254e-02
+ dcjorsti_nfetim_fc =	-1.1727e-11
+ dcjorgat_nfetim_fc =	-3.1530e-11
+ dfol2_nfetim_fc =   0.0000e+00
+ dvfbl_nfetim_fc =   0.0000e+00
+ dcjorbot_nfetim_fc =	-8.2974e-05
+ dlov_nfetim_fc =   0.0000e+00
+ dfol1_nfetim_fc =   0.0000e+00
+ dtoxo_nfetim_fc =  -3.4434e-10
+ dthesatl_nfetim_fc =	 0.0000e+00
+ dlap_nfetim_fc =   1.3829e-08
+ dvfblw_nfetim_fc =   0.0000e+00
+ drsw1_nfetim_fc =  -4.4253e+00
+ duo_nfetim_fc =   5.3533e-04
+ dwot_nfetim_fc =  -2.7658e-08
.endl ff_nfetim

.lib ss_nfetim
.param
+ dvfbo_nfetim_fc =   1.6308e-02
+ dcjorsti_nfetim_fc =	 1.0378e-11
+ dcjorgat_nfetim_fc =	 2.8168e-11
+ dfol2_nfetim_fc =  -3.7064e-05
+ dvfbl_nfetim_fc =   0.0000e+00
+ dcjorbot_nfetim_fc =	 7.4128e-05
+ dlov_nfetim_fc =   0.0000e+00
+ dfol1_nfetim_fc =  -1.9273e-03
+ dtoxo_nfetim_fc =   3.0763e-10
+ dthesatl_nfetim_fc =	 0.0000e+00
+ dlap_nfetim_fc =  -1.2355e-08
+ dvfblw_nfetim_fc =   0.0000e+00
+ drsw1_nfetim_fc =   3.9535e+00
+ duo_nfetim_fc =  -6.6718e-04
+ dwot_nfetim_fc =   2.4709e-08
.endl ss_nfetim

.lib fs_nfetim
.param
+ dvfbo_nfetim_fc =  -2.2000e-02
+ dcjorsti_nfetim_fc =	-2.1200e-11
+ dcjorgat_nfetim_fc =	-5.7000e-11
+ dfol2_nfetim_fc =   0.0000e+00
+ dvfbl_nfetim_fc =   0.0000e+00
+ dcjorbot_nfetim_fc =	-1.5000e-04
+ dlov_nfetim_fc =   0.0000e+00
+ dfol1_nfetim_fc =   0.0000e+00
+ dtoxo_nfetim_fc =   0.0000e+00
+ dthesatl_nfetim_fc =	 0.0000e+00
+ dlap_nfetim_fc =   0.0000e+00
+ dvfblw_nfetim_fc =   0.0000e+00
+ drsw1_nfetim_fc =  -8.2807e+00
+ duo_nfetim_fc =   1.0017e-03
+ dwot_nfetim_fc =   0.0000e+00
.endl fs_nfetim

.lib sf_nfetim
.param
+ dvfbo_nfetim_fc =   2.2000e-02
+ dcjorsti_nfetim_fc =	 2.1000e-11
+ dcjorgat_nfetim_fc =	 5.7000e-11
+ dfol2_nfetim_fc =   0.0000e+00
+ dvfbl_nfetim_fc =   0.0000e+00
+ dcjorbot_nfetim_fc =	 1.5000e-04
+ dlov_nfetim_fc =   0.0000e+00
+ dfol1_nfetim_fc =   0.0000e+00
+ dtoxo_nfetim_fc =   0.0000e+00
+ dthesatl_nfetim_fc =	 0.0000e+00
+ dlap_nfetim_fc =   0.0000e+00
+ dvfblw_nfetim_fc =   0.0000e+00
+ drsw1_nfetim_fc =   8.0505e+00
+ duo_nfetim_fc =  -1.3586e-03
+ dwot_nfetim_fc =   0.0000e+00
.endl sf_nfetim

.lib fff_nfetim
.param
+ dvfbo_nfetim_fc =  -2.2000e-02
+ dcjorsti_nfetim_fc =	-1.4133e-11
+ dcjorgat_nfetim_fc =	-3.8000e-11
+ dfol2_nfetim_fc =   0.0000e+00
+ dvfbl_nfetim_fc =   0.0000e+00
+ dcjorbot_nfetim_fc =	-1.0000e-04
+ dlov_nfetim_fc =   0.0000e+00
+ dfol1_nfetim_fc =   0.0000e+00
+ dtoxo_nfetim_fc =  -4.1500e-10
+ dthesatl_nfetim_fc =	 0.0000e+00
+ dlap_nfetim_fc =   1.6667e-08
+ dvfblw_nfetim_fc =   0.0000e+00
+ drsw1_nfetim_fc =  -5.3333e+00
+ duo_nfetim_fc =   6.4518e-04
+ dwot_nfetim_fc =  -3.3333e-08
.endl fff_nfetim

.lib ssf_nfetim
.param
+ dvfbo_nfetim_fc =   2.2000e-02
+ dcjorsti_nfetim_fc =	 1.4000e-11
+ dcjorgat_nfetim_fc =	 3.8000e-11
+ dfol2_nfetim_fc =  -5.0000e-05
+ dvfbl_nfetim_fc =   0.0000e+00
+ dcjorbot_nfetim_fc =	 1.0000e-04
+ dlov_nfetim_fc =   0.0000e+00
+ dfol1_nfetim_fc =  -2.6000e-03
+ dtoxo_nfetim_fc =   4.1500e-10
+ dthesatl_nfetim_fc =	 0.0000e+00
+ dlap_nfetim_fc =  -1.6667e-08
+ dvfblw_nfetim_fc =   0.0000e+00
+ drsw1_nfetim_fc =   5.3333e+00
+ duo_nfetim_fc =  -9.0005e-04
+ dwot_nfetim_fc =   3.3333e-08
.endl ssf_nfetim

.lib tt_pfetim
.param
+ dvfbo_pfetim_fc =   0.0000e+00
+ dcjorsti_pfetim_fc =	 0.0000e+00
+ dcjorgat_pfetim_fc =	 0.0000e+00
+ dfol2_pfetim_fc =   0.0000e+00
+ dvfbl_pfetim_fc =   0.0000e+00
+ dcjorbot_pfetim_fc =	 0.0000e+00
+ dlov_pfetim_fc =   0.0000e+00
+ dfol1_pfetim_fc =   0.0000e+00
+ dtoxo_pfetim_fc =   0.0000e+00
+ dthesatl_pfetim_fc =	 0.0000e+00
+ dlap_pfetim_fc =   0.0000e+00
+ dvfblw_pfetim_fc =   0.0000e+00
+ drsw1_pfetim_fc =   0.0000e+00
+ duo_pfetim_fc =   0.0000e+00
+ dwot_pfetim_fc =   0.0000e+00
.endl tt_pfetim

.lib ff_pfetim
.param
+ dvfbo_pfetim_fc =  -2.8977e-02
+ dcjorsti_pfetim_fc =	-1.6208e-11
+ dcjorgat_pfetim_fc =	-7.9655e-12
+ dfol2_pfetim_fc =   1.2446e-04
+ dvfbl_pfetim_fc =   0.0000e+00
+ dcjorbot_pfetim_fc =	-6.0848e-05
+ dlov_pfetim_fc =   0.0000e+00
+ dfol1_pfetim_fc =   2.1158e-03
+ dtoxo_pfetim_fc =  -3.3190e-10
+ dthesatl_pfetim_fc =	-4.9452e-04
+ dlap_pfetim_fc =   1.3829e-08
+ dvfblw_pfetim_fc =   0.0000e+00
+ drsw1_pfetim_fc =  -1.3276e+01
+ duo_pfetim_fc =   1.2911e-04
+ dwot_pfetim_fc =  -2.7658e-08
.endl ff_pfetim

.lib ss_pfetim
.param
+ dvfbo_pfetim_fc =   2.9651e-03
+ dcjorsti_pfetim_fc =	 1.4480e-11
+ dcjorgat_pfetim_fc =	 7.1162e-12
+ dfol2_pfetim_fc =  -6.8927e-04
+ dvfbl_pfetim_fc =   0.0000e+00
+ dcjorbot_pfetim_fc =	 5.4360e-05
+ dlov_pfetim_fc =   0.0000e+00
+ dfol1_pfetim_fc =  -1.7493e-02
+ dtoxo_pfetim_fc =   2.9651e-10
+ dthesatl_pfetim_fc =	 3.1104e-03
+ dlap_pfetim_fc =  -1.2355e-08
+ dvfblw_pfetim_fc =   0.0000e+00
+ drsw1_pfetim_fc =   1.1860e+02
+ duo_pfetim_fc =  -1.9224e-04
+ dwot_pfetim_fc =   2.4709e-08
.endl ss_pfetim

.lib fs_pfetim
.param
+ dvfbo_pfetim_fc =   2.6667e-02
+ dcjorsti_pfetim_fc =	 1.1720e-11
+ dcjorgat_pfetim_fc =	 5.7600e-12
+ dfol2_pfetim_fc =   0.0000e+00
+ dvfbl_pfetim_fc =   0.0000e+00
+ dcjorbot_pfetim_fc =	 4.4000e-05
+ dlov_pfetim_fc =   0.0000e+00
+ dfol1_pfetim_fc =   0.0000e+00
+ dtoxo_pfetim_fc =   0.0000e+00
+ dthesatl_pfetim_fc =	 0.0000e+00
+ dlap_pfetim_fc =   0.0000e+00
+ dvfblw_pfetim_fc =   0.0000e+00
+ drsw1_pfetim_fc =   9.6000e+01
+ duo_pfetim_fc =  -1.5560e-04
+ dwot_pfetim_fc =   0.0000e+00
.endl fs_pfetim

.lib sf_pfetim
.param
+ dvfbo_pfetim_fc =  -4.0000e-02
+ dcjorsti_pfetim_fc =	-2.7405e-11
+ dcjorgat_pfetim_fc =	-1.3469e-11
+ dfol2_pfetim_fc =   0.0000e+00
+ dvfbl_pfetim_fc =   0.0000e+00
+ dcjorbot_pfetim_fc =	-1.0288e-04
+ dlov_pfetim_fc =   0.0000e+00
+ dfol1_pfetim_fc =   0.0000e+00
+ dtoxo_pfetim_fc =   0.0000e+00
+ dthesatl_pfetim_fc =	 0.0000e+00
+ dlap_pfetim_fc =   0.0000e+00
+ dvfblw_pfetim_fc =   0.0000e+00
+ drsw1_pfetim_fc =  -2.2448e+01
+ duo_pfetim_fc =   2.1830e-04
+ dwot_pfetim_fc =   0.0000e+00
.endl sf_pfetim

.lib fff_pfetim
.param
+ dvfbo_pfetim_fc =  -3.4923e-02
+ dcjorsti_pfetim_fc =	-1.9533e-11
+ dcjorgat_pfetim_fc =	-9.6000e-12
+ dfol2_pfetim_fc =   1.5000e-04
+ dvfbl_pfetim_fc =   0.0000e+00
+ dcjorbot_pfetim_fc =	-7.3333e-05
+ dlov_pfetim_fc =   0.0000e+00
+ dfol1_pfetim_fc =   2.5500e-03
+ dtoxo_pfetim_fc =  -4.0000e-10
+ dthesatl_pfetim_fc =	-5.9600e-04
+ dlap_pfetim_fc =   1.6667e-08
+ dvfblw_pfetim_fc =   0.0000e+00
+ drsw1_pfetim_fc =  -1.6000e+01
+ duo_pfetim_fc =   1.5560e-04
+ dwot_pfetim_fc =  -3.3333e-08
.endl fff_pfetim

.lib ssf_pfetim
.param
+ dvfbo_pfetim_fc =   4.0000e-03
+ dcjorsti_pfetim_fc =	 1.9533e-11
+ dcjorgat_pfetim_fc =	 9.6000e-12
+ dfol2_pfetim_fc =  -9.2984e-04
+ dvfbl_pfetim_fc =   0.0000e+00
+ dcjorbot_pfetim_fc =	 7.3333e-05
+ dlov_pfetim_fc =   0.0000e+00
+ dfol1_pfetim_fc =  -2.3599e-02
+ dtoxo_pfetim_fc =   4.0000e-10
+ dthesatl_pfetim_fc =	 4.1960e-03
+ dlap_pfetim_fc =  -1.6667e-08
+ dvfblw_pfetim_fc =   0.0000e+00
+ drsw1_pfetim_fc =   1.6000e+02
+ duo_pfetim_fc =  -2.5933e-04
+ dwot_pfetim_fc =   3.3333e-08
.endl ssf_pfetim

.lib lvtt
.param
***********************************************************************
* "TT" corner : Nominal (default) process
***********************************************************************
+  fixcnrlv = 0
+  cor_rx_fc   = 0
+  cor_pc_fc   = 0
+  cor_tox_fc  = 0
+  cor_toxm_fc = 0
.lib 'fixed_corner_lv.inc' tt_nfet
.lib 'fixed_corner_lv.inc' tt_pfet
.lib 'fixed_corner_lv.inc' tt_nfeti
.lib 'fixed_corner_lv.inc' tt_pfeti
.lib 'fixed_corner_lv.inc' tt_nfethvt
.lib 'fixed_corner_lv.inc' tt_pfethvt
.lib 'fixed_corner_lv.inc' tt_nfetihvt
.lib 'fixed_corner_lv.inc' tt_pfetihvt
.lib 'fixed_corner_lv.inc' tt_nfetshvt
.lib 'fixed_corner_lv.inc' tt_pfetshvt
.lib 'fixed_corner_lv.inc' tt_nfetm
.lib 'fixed_corner_lv.inc' tt_pfetm
.lib 'fixed_corner_lv.inc' tt_nfetim
.lib 'fixed_corner_lv.inc' tt_pfetim
.endl lvtt

.lib lvff
.param
***********************************************************************
* "FF" corner : "Fast" NMOS, "Fast" PMOS
***********************************************************************
+  fixcnrlv = 1
+  cor_rx_fc   = 0.25
+  cor_pc_fc   = 0.25
+  cor_tox_fc  = 2.5
+  cor_toxm_fc = 2.5
.lib 'fixed_corner_lv.inc' ff_nfet
.lib 'fixed_corner_lv.inc' ff_pfet
.lib 'fixed_corner_lv.inc' ff_nfeti
.lib 'fixed_corner_lv.inc' ff_pfeti
.lib 'fixed_corner_lv.inc' ff_nfethvt
.lib 'fixed_corner_lv.inc' ff_pfethvt
.lib 'fixed_corner_lv.inc' ff_nfetihvt
.lib 'fixed_corner_lv.inc' ff_pfetihvt
.lib 'fixed_corner_lv.inc' ff_nfetshvt
.lib 'fixed_corner_lv.inc' ff_pfetshvt
.lib 'fixed_corner_lv.inc' ff_nfetm
.lib 'fixed_corner_lv.inc' ff_pfetm
.lib 'fixed_corner_lv.inc' ff_nfetim
.lib 'fixed_corner_lv.inc' ff_pfetim
.endl lvff

.lib lvss
.param
***********************************************************************
* "SS" corner : "Slow" NMOS, "Slow" PMOS
***********************************************************************
+  fixcnrlv = 1
+  cor_rx_fc   = -0.25
+  cor_pc_fc   = -0.25
+  cor_tox_fc  = -2.5
+  cor_toxm_fc = -2.5
.lib 'fixed_corner_lv.inc' ss_nfet
.lib 'fixed_corner_lv.inc' ss_pfet
.lib 'fixed_corner_lv.inc' ss_nfeti
.lib 'fixed_corner_lv.inc' ss_pfeti
.lib 'fixed_corner_lv.inc' ss_nfethvt
.lib 'fixed_corner_lv.inc' ss_pfethvt
.lib 'fixed_corner_lv.inc' ss_nfetihvt
.lib 'fixed_corner_lv.inc' ss_pfetihvt
.lib 'fixed_corner_lv.inc' ss_nfetshvt
.lib 'fixed_corner_lv.inc' ss_pfetshvt
.lib 'fixed_corner_lv.inc' ss_nfetm
.lib 'fixed_corner_lv.inc' ss_pfetm
.lib 'fixed_corner_lv.inc' ss_nfetim
.lib 'fixed_corner_lv.inc' ss_pfetim
.endl lvss

.lib lvfs
.param
***********************************************************************
* "FS" corner : "Fast" NMOS, "Slow" PMOS
***********************************************************************
+  fixcnrlv = 1
+  cor_rx_fc   = 0
+  cor_pc_fc   = 0
+  cor_tox_fc  = 0
+  cor_toxm_fc = 0
.lib 'fixed_corner_lv.inc' fs_nfet
.lib 'fixed_corner_lv.inc' fs_pfet
.lib 'fixed_corner_lv.inc' fs_nfeti
.lib 'fixed_corner_lv.inc' fs_pfeti
.lib 'fixed_corner_lv.inc' fs_nfethvt
.lib 'fixed_corner_lv.inc' fs_pfethvt
.lib 'fixed_corner_lv.inc' fs_nfetihvt
.lib 'fixed_corner_lv.inc' fs_pfetihvt
.lib 'fixed_corner_lv.inc' fs_nfetshvt
.lib 'fixed_corner_lv.inc' fs_pfetshvt
.lib 'fixed_corner_lv.inc' fs_nfetm
.lib 'fixed_corner_lv.inc' fs_pfetm
.lib 'fixed_corner_lv.inc' fs_nfetim
.lib 'fixed_corner_lv.inc' fs_pfetim
.endl lvfs

.lib lvsf
.param
***********************************************************************
* "SF" corner : "Slow" NMOS, "Fast" PMOS
***********************************************************************
+  fixcnrlv = 1
+  cor_rx_fc   = 0
+  cor_pc_fc   = 0
+  cor_tox_fc  = 0
+  cor_toxm_fc = 0
.lib 'fixed_corner_lv.inc' sf_nfet
.lib 'fixed_corner_lv.inc' sf_pfet
.lib 'fixed_corner_lv.inc' sf_nfeti
.lib 'fixed_corner_lv.inc' sf_pfeti
.lib 'fixed_corner_lv.inc' sf_nfethvt
.lib 'fixed_corner_lv.inc' sf_pfethvt
.lib 'fixed_corner_lv.inc' sf_nfetihvt
.lib 'fixed_corner_lv.inc' sf_pfetihvt
.lib 'fixed_corner_lv.inc' sf_nfetshvt
.lib 'fixed_corner_lv.inc' sf_pfetshvt
.lib 'fixed_corner_lv.inc' sf_nfetm
.lib 'fixed_corner_lv.inc' sf_pfetm
.lib 'fixed_corner_lv.inc' sf_nfetim
.lib 'fixed_corner_lv.inc' sf_pfetim
.endl lvsf

.lib lvfff
.param
***********************************************************************
* "FFF" functional corner : "Fast" NMOS, "Fast" PMOS
***********************************************************************
+  fixcnrlv = 1
+  cor_rx_fc   = 0.5
+  cor_pc_fc   = 0.5
+  cor_tox_fc  = 2.5
+  cor_toxm_fc = 2.5
.lib 'fixed_corner_lv.inc' fff_nfet
.lib 'fixed_corner_lv.inc' fff_pfet
.lib 'fixed_corner_lv.inc' fff_nfeti
.lib 'fixed_corner_lv.inc' fff_pfeti
.lib 'fixed_corner_lv.inc' fff_nfethvt
.lib 'fixed_corner_lv.inc' fff_pfethvt
.lib 'fixed_corner_lv.inc' fff_nfetihvt
.lib 'fixed_corner_lv.inc' fff_pfetihvt
.lib 'fixed_corner_lv.inc' fff_nfetshvt
.lib 'fixed_corner_lv.inc' fff_pfetshvt
.lib 'fixed_corner_lv.inc' fff_nfetm
.lib 'fixed_corner_lv.inc' fff_pfetm
.lib 'fixed_corner_lv.inc' fff_nfetim
.lib 'fixed_corner_lv.inc' fff_pfetim
.endl lvfff

.lib lvssf
.param
***********************************************************************
* "SSF" functional corner : "Slow" NMOS, "Slow" PMOS
***********************************************************************
+  fixcnrlv = 1
+  cor_rx_fc   = -0.5
+  cor_pc_fc   = -0.5
+  cor_tox_fc  = -2.5
+  cor_toxm_fc = -2.5
.lib 'fixed_corner_lv.inc' ssf_nfet
.lib 'fixed_corner_lv.inc' ssf_pfet
.lib 'fixed_corner_lv.inc' ssf_nfeti
.lib 'fixed_corner_lv.inc' ssf_pfeti
.lib 'fixed_corner_lv.inc' ssf_nfethvt
.lib 'fixed_corner_lv.inc' ssf_pfethvt
.lib 'fixed_corner_lv.inc' ssf_nfetihvt
.lib 'fixed_corner_lv.inc' ssf_pfetihvt
.lib 'fixed_corner_lv.inc' ssf_nfetshvt
.lib 'fixed_corner_lv.inc' ssf_pfetshvt
.lib 'fixed_corner_lv.inc' ssf_nfetm
.lib 'fixed_corner_lv.inc' ssf_pfetm
.lib 'fixed_corner_lv.inc' ssf_nfetim
.lib 'fixed_corner_lv.inc' ssf_pfetim
.endl lvssf
