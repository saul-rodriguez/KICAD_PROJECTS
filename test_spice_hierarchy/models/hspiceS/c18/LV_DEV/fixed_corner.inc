* Path, Component, Release: cmrf7sf/rel/HSPICE/models/fixed_corner, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
*
* *********************************************************************
*
*>  CMRF7SF  MOSFET Fixed Process Corner Parameter Settings
*
*   MOSFET device corner parameter settings only. Does not include or
*   account for flicker (1/f) noise, bjt or passive corner parameters.
*
*
* *********************************************************************
*
.lib tt_pfet
.param
+ dvfbo_pfet_fc =   0.0000e+00
+ dcjorsti_pfet_fc =   0.0000e+00
+ dcjorgat_pfet_fc =   0.0000e+00
+ dvfbl_pfet_fc =   0.0000e+00
+ dlov_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =   0.0000e+00
+ dtoxo_pfet_fc =   0.0000e+00
+ dfol1_pfet_fc =   0.0000e+00
+ dlap_pfet_fc =   0.0000e+00
+ dvfblw_pfet_fc =   0.0000e+00
+ duo_pfet_fc =   0.0000e+00
+ drsw1_pfet_fc =   0.0000e+00
+ dwot_pfet_fc =   0.0000e+00
.endl tt_pfet

.lib ff_pfet
.param
+ dvfbo_pfet_fc =  -1.8042e-02
+ dcjorsti_pfet_fc =  -4.6253e-11
+ dcjorgat_pfet_fc =  -4.6253e-11
+ dvfbl_pfet_fc =   0.3511e-03
+ dlov_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =  -8.3245e-05
+ dtoxo_pfet_fc =  -1.1706e-10
+ dfol1_pfet_fc =   2.5494e-03
+ dlap_pfet_fc =   3.3168e-09
+ dvfblw_pfet_fc =   0.0000e+00
+ duo_pfet_fc =   7.8042e-05
+ drsw1_pfet_fc =  -5.7794e+00
+ dwot_pfet_fc =  -1.8860e-08
.endl ff_pfet

.lib ss_pfet
.param
+ dvfbo_pfet_fc =   1.9316e-02
+ dcjorsti_pfet_fc =   4.7008e-11
+ dcjorgat_pfet_fc =   4.7008e-11
+ dvfbl_pfet_fc =  -1.0210e-03
+ dlov_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =   8.4604e-05
+ dtoxo_pfet_fc =   1.1897e-10
+ dfol1_pfet_fc =   0.0000e+00
+ dlap_pfet_fc =  -3.3709e-09
+ dvfblw_pfet_fc =   0.0000e+00
+ duo_pfet_fc =  -7.9316e-05
+ drsw1_pfet_fc =   2.3795e+00
+ dwot_pfet_fc =   3.9658e-08
.endl ss_pfet

.lib fs_pfet
.param
+ dvfbo_pfet_fc =   2.9333e-02
+ dcjorsti_pfet_fc =   5.9267e-11
+ dcjorgat_pfet_fc =   5.9267e-11
+ dvfbl_pfet_fc =  -0.9353e-03
+ dlov_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =   1.0667e-04
+ dtoxo_pfet_fc =   0.0000e+00
+ dfol1_pfet_fc =   0.0000e+00
+ dlap_pfet_fc =  -4.2500e-09
+ dvfblw_pfet_fc =  -7.9191e-04
+ duo_pfet_fc =  -1.3333e-04
+ drsw1_pfet_fc =   1.8000e+01
+ dwot_pfet_fc =   0.0000e+00
.endl fs_pfet

.lib sf_pfet
.param
+ dvfbo_pfet_fc =  -3.0000e-02
+ dcjorsti_pfet_fc =  -5.9267e-11
+ dcjorgat_pfet_fc =  -5.9267e-11
+ dvfbl_pfet_fc =   0.2254e-03
+ dlov_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =  -1.0667e-04
+ dtoxo_pfet_fc =   0.0000e+00
+ dfol1_pfet_fc =   0.8693e-03
+ dlap_pfet_fc =   4.2500e-09
+ dvfblw_pfet_fc =   6.6094e-04
+ duo_pfet_fc =   0.6667e-04
+ drsw1_pfet_fc =  -1.0000e+01
+ dwot_pfet_fc =   0.0000e+00
.endl sf_pfet

.lib fff_pfet
.param
+ dvfbo_pfet_fc =  -3.5000e-02
+ dcjorsti_pfet_fc =  -5.9267e-11
+ dcjorgat_pfet_fc =  -5.9267e-11
+ dvfbl_pfet_fc =   0.2313e-03
+ dlov_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =  -1.0667e-04
+ dtoxo_pfet_fc =  -1.5000e-10
+ dfol1_pfet_fc =   3.2667e-03
+ dlap_pfet_fc =   4.2500e-09
+ dvfblw_pfet_fc =   9.5321e-04
+ duo_pfet_fc =   1.0000e-04
+ drsw1_pfet_fc =  -7.4054e+00
+ dwot_pfet_fc =  -2.4167e-08
.endl fff_pfet

.lib ssf_pfet
.param
+ dvfbo_pfet_fc =   3.5000e-02
+ dcjorsti_pfet_fc =   5.9267e-11
+ dcjorgat_pfet_fc =   5.9267e-11
+ dvfbl_pfet_fc =  -1.8088e-03
+ dlov_pfet_fc =   0.0000e+00
+ dcjorbot_pfet_fc =   1.0667e-04
+ dtoxo_pfet_fc =   1.5000e-10
+ dfol1_pfet_fc =   0.0000e+00
+ dlap_pfet_fc =  -4.2500e-09
+ dvfblw_pfet_fc =  -9.7262e-04
+ duo_pfet_fc =  -2.0000e-04
+ drsw1_pfet_fc =   3.0000e+00
+ dwot_pfet_fc =   5.0000e-08
.endl ssf_pfet

.lib tt_nfet
.param
+ dvfbo_nfet_fc =   0.0000e+00
+ dcjorsti_nfet_fc =   0.0000e+00
+ dcjorgat_nfet_fc =   0.0000e+00
+ dvfbl_nfet_fc =   0.0000e+00
+ dlov_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =   0.0000e+00
+ dtoxo_nfet_fc =   0.0000e+00
+ dfol1_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =   0.0000e+00
+ dvfblw_nfet_fc =   0.0000e+00
+ duo_nfet_fc =   0.0000e+00
+ drsw1_nfet_fc =   0.0000e+00
+ dwot_nfet_fc =   0.0000e+00
.endl tt_nfet

.lib ff_nfet
.param
+ dvfbo_nfet_fc =  -2.1603e-02
+ dcjorsti_nfet_fc =  -5.6711e-11
+ dcjorgat_nfet_fc =  -5.6711e-11
+ dvfbl_nfet_fc =   0.6593e-03
+ dlov_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =  -1.0406e-04
+ dtoxo_nfet_fc =  -1.1706e-10
+ dfol1_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =   3.3168e-09
+ dvfblw_nfet_fc =   1.0000e-03
+ duo_nfet_fc =   1.6538e-03
+ drsw1_nfet_fc =  -8.5846e-01
+ dwot_nfet_fc =  -1.0144e-08
.endl ff_nfet

.lib ss_nfet
.param
+ dvfbo_nfet_fc =   2.3375e-02
+ dcjorsti_nfet_fc =   5.7636e-11
+ dcjorgat_nfet_fc =   5.7636e-11
+ dvfbl_nfet_fc =  -0.9179e-03
+ dlov_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =   1.0575e-04
+ dtoxo_nfet_fc =   1.1897e-10
+ dfol1_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =  -3.3709e-09
+ dvfblw_nfet_fc =   -1.0000e-3
+ duo_nfet_fc =  -2.4346e-04
+ drsw1_nfet_fc =   5.2349e-01
+ dwot_nfet_fc =   1.6770e-08
.endl ss_nfet

.lib fs_nfet
.param
+ dvfbo_nfet_fc =  -2.5000e-02
+ dcjorsti_nfet_fc =  -7.2667e-11
+ dcjorgat_nfet_fc =  -7.2667e-11
+ dvfbl_nfet_fc =   0.4129e-03
+ dlov_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =  -1.3333e-04
+ dtoxo_nfet_fc =   0.0000e+00
+ dfol1_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =   4.2500e-09
+ dvfblw_nfet_fc =   6.7320e-04
+ duo_nfet_fc =   1.0267e-03
+ drsw1_nfet_fc =  -6.6000e-01
+ dwot_nfet_fc =   0.0000e+00
.endl fs_nfet

.lib sf_nfet
.param
+ dvfbo_nfet_fc =   3.0705e-02
+ dcjorsti_nfet_fc =   7.2667e-11
+ dcjorgat_nfet_fc =   7.2667e-11
+ dvfbl_nfet_fc =  -0.8126e-03
+ dlov_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =   1.3333e-04
+ dtoxo_nfet_fc =   0.0000e+00
+ dfol1_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =  -4.2500e-09
+ dvfblw_nfet_fc =  -1.1200e-04
+ duo_nfet_fc =  -0.2333e-03
+ drsw1_nfet_fc =   8.6744e-01
+ dwot_nfet_fc =   0.0000e+00
.endl sf_nfet

.lib fff_nfet
.param
+ dvfbo_nfet_fc =  -3.5837e-02
+ dcjorsti_nfet_fc =  -7.2667e-11
+ dcjorgat_nfet_fc =  -7.2667e-11
+ dvfbl_nfet_fc =   1.1262e-03
+ dlov_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =  -1.3333e-04
+ dtoxo_nfet_fc =  -1.5000e-10
+ dfol1_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =   4.2500e-09
+ dvfblw_nfet_fc =   1.6938e-03
+ duo_nfet_fc =   2.3754e-03
+ drsw1_nfet_fc =  -1.1000e+00
+ dwot_nfet_fc =  -1.4531e-08
.endl fff_nfet

.lib ssf_nfet
.param
+ dvfbo_nfet_fc =   4.0166e-02
+ dcjorsti_nfet_fc =   7.2667e-11
+ dcjorgat_nfet_fc =   7.2667e-11
+ dvfbl_nfet_fc =  -1.0181e-03
+ dlov_nfet_fc =   0.0000e+00
+ dcjorbot_nfet_fc =   1.3333e-04
+ dtoxo_nfet_fc =   1.5000e-10
+ dfol1_nfet_fc =   0.0000e+00
+ dlap_nfet_fc =  -4.2500e-09
+ dvfblw_nfet_fc =  -2.0360e-03
+ duo_nfet_fc =  -5.5910e-04
+ drsw1_nfet_fc =   6.6000e-01
+ dwot_nfet_fc =   2.6359e-08
.endl ssf_nfet

.lib tt_pf33
.param
+ dvfbo_pf33_fc =   0.0000e+00
+ dcjorgat_pf33_fc =   0.0000e+00
+ dcjorsti_pf33_fc =   0.0000e+00
+ dvfbl_pf33_fc =   0.0000e+00
+ dcjorbot_pf33_fc =   0.0000e+00
+ dlap_pf33_fc =   0.0000e+00
+ drsw1_pf33_fc =   0.0000e+00
+ dlov_pf33_fc =   0.0000e+00
+ dtoxo_pf33_fc =   0.0000e+00
+ dvfblw_pf33_fc =   0.0000e+00
+ duo_pf33_fc =   0.0000e+00
+ dwot_pf33_fc =   0.0000e+00
.endl tt_pf33

.lib ff_pf33
.param
+ dvfbo_pf33_fc =  -3.1369e-02
+ dcjorgat_pf33_fc =  -1.1820e-11
+ dcjorsti_pf33_fc =  -1.1820e-11
+ dvfbl_pf33_fc =   3.3652e-03
+ dcjorbot_pf33_fc =  -6.4000e-05
+ dlap_pf33_fc =   3.3000e-09
+ drsw1_pf33_fc =  -1.0000e+01
+ dlov_pf33_fc =   0.0000e+00
+ dtoxo_pf33_fc =  -1.5000e-10
+ dvfblw_pf33_fc =   0.0000e+00
+ duo_pf33_fc =   1.0e-03
+ dwot_pf33_fc =  -1.0931e-08
.endl ff_pf33

.lib ss_pf33
.param
+ dvfbo_pf33_fc =   3.1369e-02
+ dcjorgat_pf33_fc =  -2.8880e-11
+ dcjorsti_pf33_fc =  -2.8880e-11
+ dvfbl_pf33_fc =  -3.3652e-03
+ dcjorbot_pf33_fc =   6.4000e-05
+ dlap_pf33_fc =  -3.3000e-09
+ drsw1_pf33_fc =   1.0000e+01
+ dlov_pf33_fc =   0.0000e+00
+ dtoxo_pf33_fc =   1.6500e-10
+ dvfblw_pf33_fc =   0.0000e+00
+ duo_pf33_fc =  -8.2702e-04
+ dwot_pf33_fc =   1.0931e-08
.endl ss_pf33

.lib fs_pf33
.param
+ dvfbo_pf33_fc =   3.0839e-03
+ dcjorgat_pf33_fc =  -4.8133e-11
+ dcjorsti_pf33_fc =  -4.8133e-11
+ dvfbl_pf33_fc =  -4.2533e-04
+ dcjorbot_pf33_fc =   1.0667e-04
+ dlap_pf33_fc =  -5.5000e-09
+ drsw1_pf33_fc =   1.6667e+01
+ dlov_pf33_fc =   0.0000e+00
+ dtoxo_pf33_fc =   2.7500e-10
+ dvfblw_pf33_fc =   0.0000e+00
+ duo_pf33_fc =  -0.2615e-04
+ dwot_pf33_fc =   5.8890e-09
.endl fs_pf33

.lib sf_pf33
.param
+ dvfbo_pf33_fc =  -3.8820e-03
+ dcjorgat_pf33_fc =  -1.9700e-11
+ dcjorsti_pf33_fc =  -1.9700e-11
+ dvfbl_pf33_fc =   2.0863e-03
+ dcjorbot_pf33_fc =  -1.0667e-04
+ dlap_pf33_fc =   5.5000e-09
+ drsw1_pf33_fc =  -1.6667e+01
+ dlov_pf33_fc =   0.0000e+00
+ dtoxo_pf33_fc =  -2.5000e-10
+ dvfblw_pf33_fc =   0.0000e+00
+ duo_pf33_fc =   1.2837e-04
+ dwot_pf33_fc =  -3.2183e-09
.endl sf_pf33

.lib fff_pf33
.param
+ dvfbo_pf33_fc =  -3.8948e-02
+ dcjorgat_pf33_fc =  -1.9700e-11
+ dcjorsti_pf33_fc =  -1.9700e-11
+ dvfbl_pf33_fc =   2.6086e-03
+ dcjorbot_pf33_fc =  -1.0667e-04
+ dlap_pf33_fc =   5.5000e-09
+ drsw1_pf33_fc =  -1.6667e+01
+ dlov_pf33_fc =   0.0000e+00
+ dtoxo_pf33_fc =  -2.5000e-10
+ dvfblw_pf33_fc =   0.0000e+00
+ duo_pf33_fc =   1.2950e-03
+ dwot_pf33_fc =  -1.8218e-08
.endl fff_pf33

.lib ssf_pf33
.param
+ dvfbo_pf33_fc =   3.1084e-02
+ dcjorgat_pf33_fc =  -4.8133e-11
+ dcjorsti_pf33_fc =  -4.8133e-11
+ dvfbl_pf33_fc =  -2.0920e-03
+ dcjorbot_pf33_fc =   1.0667e-04
+ dlap_pf33_fc =  -5.5000e-09
+ drsw1_pf33_fc =   1.6667e+01
+ dlov_pf33_fc =   0.0000e+00
+ dtoxo_pf33_fc =   2.7500e-10
+ dvfblw_pf33_fc =   0.0000e+00
+ duo_pf33_fc =  -4.5282e-04
+ dwot_pf33_fc =   4.4222e-08
.endl ssf_pf33

.lib tt_nf33
.param
+ dvfbo_nf33_fc =   0.0000e+00
+ dcjorgat_nf33_fc =   0.0000e+00
+ dcjorsti_nf33_fc =   0.0000e+00
+ dvfbl_nf33_fc =   0.0000e+00
+ dcjorbot_nf33_fc =   0.0000e+00
+ dlap_nf33_fc =   0.0000e+00
+ drsw1_nf33_fc =   0.0000e+00
+ dlov_nf33_fc =   0.0000e+00
+ dtoxo_nf33_fc =   0.0000e+00
+ dvfblw_nf33_fc =   0.0000e+00
+ duo_nf33_fc =   0.0000e+00
+ dwot_nf33_fc =   0.0000e+00
.endl tt_nf33

.lib ff_nf33
.param
+ dvfbo_nf33_fc =  -3.9472e-02
+ dcjorgat_nf33_fc =  -3.4040e-11
+ dcjorsti_nf33_fc =  -3.4040e-11
+ dvfbl_nf33_fc =   5.7536e-03
+ dcjorbot_nf33_fc =  -6.4000e-05
+ dlap_nf33_fc =   3.3000e-09
+ drsw1_nf33_fc =  -2.7000e+00
+ dlov_nf33_fc =   0.0000e+00
+ dtoxo_nf33_fc =  -1.5000e-10
+ dvfblw_nf33_fc =   0.0000e+00
+ duo_nf33_fc =   2.0641e-03
+ dwot_nf33_fc =  -1.4558e-08
.endl ff_nf33

.lib ss_nf33
.param
+ dvfbo_nf33_fc =   4.9472e-02
+ dcjorgat_nf33_fc =   3.4440e-11
+ dcjorsti_nf33_fc =   3.4440e-11
+ dvfbl_nf33_fc =  -7.1536e-03
+ dcjorbot_nf33_fc =   6.4000e-05
+ dlap_nf33_fc =  -3.3000e-09
+ drsw1_nf33_fc =   2.7000e+00
+ dlov_nf33_fc =   0.0000e+00
+ dtoxo_nf33_fc =   1.5000e-10
+ dvfblw_nf33_fc =   0.0000e+00
+ duo_nf33_fc =  -2.2641e-03
+ dwot_nf33_fc =   1.4558e-08
.endl ss_nf33

.lib fs_nf33
.param
+ dvfbo_nf33_fc =  -25.2500e-03
+ dcjorgat_nf33_fc =  -5.6733e-11
+ dcjorsti_nf33_fc =  -5.6733e-11
+ dvfbl_nf33_fc =   2.5894e-03
+ dcjorbot_nf33_fc =  -1.0667e-04
+ dlap_nf33_fc =   5.5000e-09
+ drsw1_nf33_fc =  -4.5000e+00
+ dlov_nf33_fc =   0.0000e+00
+ dtoxo_nf33_fc =  -2.5000e-10
+ dvfblw_nf33_fc =   1.0000e-03
+ duo_nf33_fc =   1.4000e-04
+ dwot_nf33_fc =  -2.5967e-09
.endl fs_nf33

.lib sf_nf33
.param
+ dvfbo_nf33_fc =   25.2500e-03
+ dcjorgat_nf33_fc =   5.7400e-11
+ dcjorsti_nf33_fc =   5.7400e-11
+ dvfbl_nf33_fc =  -3.1667e-03
+ dcjorbot_nf33_fc =   1.0667e-04
+ dlap_nf33_fc =  -5.5000e-09
+ drsw1_nf33_fc =   4.5000e+00
+ dlov_nf33_fc =   0.0000e+00
+ dtoxo_nf33_fc =   2.5000e-10
+ dvfblw_nf33_fc =   0.0000e+00
+ duo_nf33_fc =  -2.4000e-04
+ dwot_nf33_fc =   2.0042e-09
.endl sf_nf33

.lib fff_nf33
.param
+ dvfbo_nf33_fc =  -5.2454e-02
+ dcjorgat_nf33_fc =  -5.6733e-11
+ dcjorsti_nf33_fc =  -5.6733e-11
+ dvfbl_nf33_fc =   6.0194e-03
+ dcjorbot_nf33_fc =  -1.0667e-04
+ dlap_nf33_fc =   5.5000e-09
+ drsw1_nf33_fc =  -4.5000e+00
+ dlov_nf33_fc =   0.0000e+00
+ dtoxo_nf33_fc =  -2.5000e-10
+ dvfblw_nf33_fc =   1.0000e-03
+ duo_nf33_fc =   2.1068e-03
+ dwot_nf33_fc =  -2.4263e-08
.endl fff_nf33

.lib ssf_nf33
.param
+ dvfbo_nf33_fc =   5.3390e-02
+ dcjorgat_nf33_fc =   5.7400e-11
+ dcjorsti_nf33_fc =   5.7400e-11
+ dvfbl_nf33_fc =  -8.0000e-03
+ dcjorbot_nf33_fc =   1.0667e-04
+ dlap_nf33_fc =  -5.5000e-09
+ drsw1_nf33_fc =   4.5000e+00
+ dlov_nf33_fc =   0.0000e+00
+ dtoxo_nf33_fc =   2.5000e-10
+ dvfblw_nf33_fc =   0.0000e+00
+ duo_nf33_fc =  -2.4701e-03
+ dwot_nf33_fc =   3.8671e-08
.endl ssf_nf33

.lib tt_pf50
.param
+ dvfbo_pfet50_fc =   0.0000e+00
+ dfol2_pfet50_fc =   0.0000e+00
+ dcjorsti_pfet50_fc =   0.0000e+00
+ dcjorgat_pfet50_fc =   0.0000e+00
+ dvfbl_pfet50_fc =   0.0000e+00
+ dlov_pfet50_fc =   0.0000e+00
+ dcjorbot_pfet50_fc =   0.0000e+00
+ dtoxo_pfet50_fc =   0.0000e+00
+ dthesatl_pfet50_fc =   0.0000e+00
+ dfol1_pfet50_fc =   0.0000e+00
+ dlap_pfet50_fc =   0.0000e+00
+ dvfblw_pfet50_fc =   0.0000e+00
+ duo_pfet50_fc =   0.0000e+00
+ drsw1_pfet50_fc =   0.0000e+00
+ dwot_pfet50_fc =   0.0000e+00
.endl tt_pf50

.lib ff_pf50
.param
+ dvfbo_pfet50_fc =  -2.7760e-02
+ dfol2_pfet50_fc =   0.0000e+00
+ dcjorsti_pfet50_fc =  -1.2054e-11
+ dcjorgat_pfet50_fc =  -2.3003e-11
+ dvfbl_pfet50_fc =   0.0000e+00
+ dlov_pfet50_fc =   0.0000e+00
+ dcjorbot_pfet50_fc =  -8.8473e-05
+ dtoxo_pfet50_fc =  -3.3177e-10
+ dthesatl_pfet50_fc =   0.0000e+00
+ dfol1_pfet50_fc =   0.0000e+00
+ dlap_pfet50_fc =   1.0368e-08
+ dvfblw_pfet50_fc =   0.0000e+00
+ duo_pfet50_fc =   1.4830e-03
+ drsw1_pfet50_fc =   0.0000e+00
+ dwot_pfet50_fc =  -2.7648e-08
.endl ff_pf50

.lib ss_pf50
.param
+ dvfbo_pfet50_fc =   2.8328e-02
+ dfol2_pfet50_fc =   0.0000e+00
+ dcjorsti_pfet50_fc =   1.2753e-11
+ dcjorgat_pfet50_fc =   2.4331e-11
+ dvfbl_pfet50_fc =   0.0000e+00
+ dlov_pfet50_fc =   0.0000e+00
+ dcjorbot_pfet50_fc =   9.4031e-05
+ dtoxo_pfet50_fc =   3.5262e-10
+ dthesatl_pfet50_fc =   0.0000e+00
+ dfol1_pfet50_fc =   0.0000e+00
+ dlap_pfet50_fc =  -1.1019e-08
+ dvfblw_pfet50_fc =   0.0000e+00
+ duo_pfet50_fc =  -1.5816e-03
+ drsw1_pfet50_fc =   0.0000e+00
+ dwot_pfet50_fc =   2.9385e-08
.endl ss_pf50

.lib fs_pf50
.param
+ dvfbo_pfet50_fc =   5.1356e-02
+ dfol2_pfet50_fc =   0.0000e+00
+ dcjorsti_pfet50_fc =   1.4467e-11
+ dcjorgat_pfet50_fc =   2.7600e-11
+ dvfbl_pfet50_fc =   0.0000e+00
+ dlov_pfet50_fc =   0.0000e+00
+ dcjorbot_pfet50_fc =   1.0667e-04
+ dtoxo_pfet50_fc =   0.0000e+00
+ dthesatl_pfet50_fc =   0.0000e+00
+ dfol1_pfet50_fc =   0.0000e+00
+ dlap_pfet50_fc =   0.0000e+00
+ dvfblw_pfet50_fc =   0.0000e+00
+ duo_pfet50_fc =  -2.5000e-03
+ drsw1_pfet50_fc =   2.3633e+01
+ dwot_pfet50_fc =   0.0000e+00
.endl fs_pf50

.lib sf_pf50
.param
+ dvfbo_pfet50_fc =  -6.0000e-02
+ dfol2_pfet50_fc =   0.0000e+00
+ dcjorsti_pfet50_fc =  -1.4533e-11
+ dcjorgat_pfet50_fc =  -2.7733e-11
+ dvfbl_pfet50_fc =   0.0000e+00
+ dlov_pfet50_fc =   0.0000e+00
+ dcjorbot_pfet50_fc =  -1.0667e-04
+ dtoxo_pfet50_fc =   0.0000e+00
+ dthesatl_pfet50_fc =   0.0000e+00
+ dfol1_pfet50_fc =   0.0000e+00
+ dlap_pfet50_fc =   0.0000e+00
+ dvfblw_pfet50_fc =   0.0000e+00
+ duo_pfet50_fc =   2.5000e-03
+ drsw1_pfet50_fc =  -2.7285e+01
+ dwot_pfet50_fc =   0.0000e+00
.endl sf_pf50

.lib fff_pf50
.param
+ dvfbo_pfet50_fc =  -3.3469e-02
+ dfol2_pfet50_fc =   0.0000e+00
+ dcjorsti_pfet50_fc =  -1.4533e-11
+ dcjorgat_pfet50_fc =  -2.7733e-11
+ dvfbl_pfet50_fc =   0.0000e+00
+ dlov_pfet50_fc =   0.0000e+00
+ dcjorbot_pfet50_fc =  -1.0667e-04
+ dtoxo_pfet50_fc =  -4.0000e-10
+ dthesatl_pfet50_fc =   0.0000e+00
+ dfol1_pfet50_fc =   0.0000e+00
+ dlap_pfet50_fc =   1.2500e-08
+ dvfblw_pfet50_fc =   0.0000e+00
+ duo_pfet50_fc =   1.7880e-03
+ drsw1_pfet50_fc =   0.0000e+00
+ dwot_pfet50_fc =  -3.3333e-08
.endl fff_pf50

.lib ssf_pf50
.param
+ dvfbo_pfet50_fc =   3.2134e-02
+ dfol2_pfet50_fc =   0.0000e+00
+ dcjorsti_pfet50_fc =   1.4467e-11
+ dcjorgat_pfet50_fc =   2.7600e-11
+ dvfbl_pfet50_fc =   0.0000e+00
+ dlov_pfet50_fc =   0.0000e+00
+ dcjorbot_pfet50_fc =   1.0667e-04
+ dtoxo_pfet50_fc =   4.0000e-10
+ dthesatl_pfet50_fc =   0.0000e+00
+ dfol1_pfet50_fc =   0.0000e+00
+ dlap_pfet50_fc =  -1.2500e-08
+ dvfblw_pfet50_fc =   0.0000e+00
+ duo_pfet50_fc =  -1.7941e-03
+ drsw1_pfet50_fc =   0.0000e+00
+ dwot_pfet50_fc =   3.3333e-08
.endl ssf_pf50

.lib tt_nf50
.param
+ dvfbo_nfet50_fc =   0.0000e+00
+ dfol2_nfet50_fc =   0.0000e+00
+ dcjorsti_nfet50_fc =   0.0000e+00
+ dcjorgat_nfet50_fc =   0.0000e+00
+ dvfbl_nfet50_fc =   0.0000e+00
+ dcjorbot_nfet50_fc =   0.0000e+00
+ dtoxo_nfet50_fc =   0.0000e+00
+ dthesatl_nfet50_fc =   0.0000e+00
+ dfol1_nfet50_fc =   0.0000e+00
+ dlap_nfet50_fc =   0.0000e+00
+ dvfblw_nfet50_fc =   0.0000e+00
+ duo_nfet50_fc =   0.0000e+00
+ drsw1_nfet50_fc =   0.0000e+00
+ dwot_nfet50_fc =   0.0000e+00
.endl tt_nf50

.lib ff_nf50
.param
+ dvfbo_nfet50_fc =  -2.0386e-02
+ dfol2_nfet50_fc =   0.0000e+00
+ dcjorsti_nfet50_fc =  -1.1989e-11
+ dcjorgat_nfet50_fc =  -1.7696e-11
+ dvfbl_nfet50_fc =   0.0000e+00
+ dcjorbot_nfet50_fc =  -9.5913e-05
+ dtoxo_nfet50_fc =  -3.8365e-10
+ dthesatl_nfet50_fc =   0.0000e+00
+ dfol1_nfet50_fc =   0.0000e+00
+ dlap_nfet50_fc =   1.1989e-08
+ dvfblw_nfet50_fc =   0.0000e+00
+ duo_nfet50_fc =   9.4330e-04
+ drsw1_nfet50_fc =  -2.3019e+00
+ dwot_nfet50_fc =  -2.5177e-08
.endl ff_nf50

.lib ss_nf50
.param
+ dvfbo_nfet50_fc =   2.2802e-02
+ dfol2_nfet50_fc =   0.0000e+00
+ dcjorsti_nfet50_fc =   1.2742e-11
+ dcjorgat_nfet50_fc =   1.8909e-11
+ dvfbl_nfet50_fc =   0.0000e+00
+ dcjorbot_nfet50_fc =   1.0194e-04
+ dtoxo_nfet50_fc =   4.0775e-10
+ dthesatl_nfet50_fc =   0.0000e+00
+ dfol1_nfet50_fc =   0.0000e+00
+ dlap_nfet50_fc =  -1.2742e-08
+ dvfblw_nfet50_fc =   0.0000e+00
+ duo_nfet50_fc =  -1.3498e-03
+ drsw1_nfet50_fc =   4.0775e+00
+ dwot_nfet50_fc =   2.6758e-08
.endl ss_nf50

.lib fs_nf50
.param
+ dvfbo_nfet50_fc =  -3.5510e-02
+ dfol2_nfet50_fc =   0.0000e+00
+ dcjorsti_nfet50_fc =  -2.0884e-11
+ dcjorgat_nfet50_fc =  -3.0824e-11
+ dvfbl_nfet50_fc =   0.0000e+00
+ dcjorbot_nfet50_fc =  -1.6707e-04
+ dtoxo_nfet50_fc =   0.0000e+00
+ dthesatl_nfet50_fc =   0.0000e+00
+ dfol1_nfet50_fc =   0.0000e+00
+ dlap_nfet50_fc =   0.0000e+00
+ dvfblw_nfet50_fc =   0.0000e+00
+ duo_nfet50_fc =   1.6431e-03
+ drsw1_nfet50_fc =  -4.0096e+00
+ dwot_nfet50_fc =   0.0000e+00
.endl fs_nf50

.lib sf_nf50
.param
+ dvfbo_nfet50_fc =   3.6481e-02
+ dfol2_nfet50_fc =   0.0000e+00
+ dcjorsti_nfet50_fc =   2.0386e-11
+ dcjorgat_nfet50_fc =   3.0253e-11
+ dvfbl_nfet50_fc =   0.0000e+00
+ dcjorbot_nfet50_fc =   1.6309e-04
+ dtoxo_nfet50_fc =   0.0000e+00
+ dthesatl_nfet50_fc =   0.0000e+00
+ dfol1_nfet50_fc =   0.0000e+00
+ dlap_nfet50_fc =   0.0000e+00
+ dvfblw_nfet50_fc =   0.0000e+00
+ duo_nfet50_fc =  -2.1596e-03
+ drsw1_nfet50_fc =   6.5236e+00
+ dwot_nfet50_fc =   0.0000e+00
.endl sf_nf50

.lib fff_nf50
.param
+ dvfbo_nfet50_fc =  -2.8339e-02
+ dfol2_nfet50_fc =   0.0000e+00
+ dcjorsti_nfet50_fc =  -1.6667e-11
+ dcjorgat_nfet50_fc =  -2.4600e-11
+ dvfbl_nfet50_fc =   0.0000e+00
+ dcjorbot_nfet50_fc =  -1.3333e-04
+ dtoxo_nfet50_fc =  -5.3333e-10
+ dthesatl_nfet50_fc =   0.0000e+00
+ dfol1_nfet50_fc =   0.0000e+00
+ dlap_nfet50_fc =   1.6667e-08
+ dvfblw_nfet50_fc =   0.0000e+00
+ duo_nfet50_fc =   1.3113e-03
+ drsw1_nfet50_fc =  -3.2000e+00
+ dwot_nfet50_fc =  -3.5000e-08
.endl fff_nf50

.lib ssf_nf50
.param
+ dvfbo_nfet50_fc =   2.9825e-02
+ dfol2_nfet50_fc =   0.0000e+00
+ dcjorsti_nfet50_fc =   1.6667e-11
+ dcjorgat_nfet50_fc =   2.4733e-11
+ dvfbl_nfet50_fc =   0.0000e+00
+ dcjorbot_nfet50_fc =   1.3333e-04
+ dtoxo_nfet50_fc =   5.3333e-10
+ dthesatl_nfet50_fc =   0.0000e+00
+ dfol1_nfet50_fc =   0.0000e+00
+ dlap_nfet50_fc =  -1.6667e-08
+ dvfblw_nfet50_fc =   0.0000e+00
+ duo_nfet50_fc =  -1.7656e-03
+ drsw1_nfet50_fc =   5.3333e+00
+ dwot_nfet50_fc =   3.5000e-08
.endl ssf_nf50

.lib tt_p5pf50
.param
+ dvfbo_p5pfet50_fc =   0.0000e+00
+ dfol2_p5pfet50_fc =   0.0000e+00
+ dcjorsti_p5pfet50_fc =   0.0000e+00
+ dcjorgat_p5pfet50_fc =   0.0000e+00
+ dvfbl_p5pfet50_fc =   0.0000e+00
+ dcjorbot_p5pfet50_fc =   0.0000e+00
+ dtoxo_p5pfet50_fc =   0.0000e+00
+ dthesatl_p5pfet50_fc =   0.0000e+00
+ dfol1_p5pfet50_fc =   0.0000e+00
+ dlap_p5pfet50_fc =   0.0000e+00
+ dvfblw_p5pfet50_fc =   0.0000e+00
+ duo_p5pfet50_fc =   0.0000e+00
+ drsw1_p5pfet50_fc =   0.0000e+00
+ dwot_p5pfet50_fc =   0.0000e+00
.endl tt_p5pf50

.lib ff_p5pf50
.param
+ dvfbo_p5pfet50_fc =  -2.0462e-02
+ dfol2_p5pfet50_fc =   0.0000e+00
+ dcjorsti_p5pfet50_fc =  -1.0455e-11
+ dcjorgat_p5pfet50_fc =  -2.0142e-11
+ dvfbl_p5pfet50_fc =   0.0000e+00
+ dcjorbot_p5pfet50_fc =  -7.6731e-05
+ dtoxo_p5pfet50_fc =  -3.8365e-10
+ dthesatl_p5pfet50_fc =  -1.4387e-03
+ dfol1_p5pfet50_fc =   1.4387e-04
+ dlap_p5pfet50_fc =   1.1989e-08
+ dvfblw_p5pfet50_fc =   0.0000e+00
+ duo_p5pfet50_fc =   8.7208e-04
+ drsw1_p5pfet50_fc =  -1.7984e+01
+ dwot_p5pfet50_fc =  -2.3978e-08
.endl ff_p5pf50

.lib ss_p5pf50
.param
+ dvfbo_p5pfet50_fc =   2.0767e-02
+ dfol2_p5pfet50_fc =   0.0000e+00
+ dcjorsti_p5pfet50_fc =  -3.5270e-11
+ dcjorgat_p5pfet50_fc =   2.1407e-11
+ dvfbl_p5pfet50_fc =   0.0000e+00
+ dcjorbot_p5pfet50_fc =   8.1549e-05
+ dtoxo_p5pfet50_fc =   4.0775e-10
+ dthesatl_p5pfet50_fc =   1.5291e-03
+ dfol1_p5pfet50_fc =  -1.5291e-04
+ dlap_p5pfet50_fc =  -1.2742e-08
+ dvfblw_p5pfet50_fc =   0.0000e+00
+ duo_p5pfet50_fc =  -1.0712e-03
+ drsw1_p5pfet50_fc =   1.9113e+01
+ dwot_p5pfet50_fc =   2.5484e-08
.endl ss_p5pf50

.lib fs_p5pf50
.param
+ dvfbo_p5pfet50_fc =   4.2796e-02
+ dfol2_p5pfet50_fc =   0.0000e+00
+ dcjorsti_p5pfet50_fc =  -4.6133e-11
+ dcjorgat_p5pfet50_fc =   2.8000e-11
+ dvfbl_p5pfet50_fc =   0.0000e+00
+ dcjorbot_p5pfet50_fc =   1.0667e-04
+ dtoxo_p5pfet50_fc =   0.0000e+00
+ dthesatl_p5pfet50_fc =   0.0000e+00
+ dfol1_p5pfet50_fc =   0.0000e+00
+ dlap_p5pfet50_fc =   0.0000e+00
+ dvfblw_p5pfet50_fc =   0.0000e+00
+ duo_p5pfet50_fc =  -1.9561e-03
+ drsw1_p5pfet50_fc =   3.9389e+01
+ dwot_p5pfet50_fc =   0.0000e+00
.endl fs_p5pf50

.lib sf_p5pf50
.param
+ dvfbo_p5pfet50_fc =  -5.0000e-02
+ dfol2_p5pfet50_fc =   0.0000e+00
+ dcjorsti_p5pfet50_fc =  -1.4533e-11
+ dcjorgat_p5pfet50_fc =  -2.8000e-11
+ dvfbl_p5pfet50_fc =   0.0000e+00
+ dcjorbot_p5pfet50_fc =  -1.0667e-04
+ dtoxo_p5pfet50_fc =   0.0000e+00
+ dthesatl_p5pfet50_fc =   0.0000e+00
+ dfol1_p5pfet50_fc =   0.0000e+00
+ dlap_p5pfet50_fc =   0.0000e+00
+ dvfblw_p5pfet50_fc =   0.0000e+00
+ duo_p5pfet50_fc =   1.9511e-03
+ drsw1_p5pfet50_fc =  -4.5474e+01
+ dwot_p5pfet50_fc =   0.0000e+00
.endl sf_p5pf50

.lib fff_p5pf50
.param
+ dvfbo_p5pfet50_fc =  -2.8445e-02
+ dfol2_p5pfet50_fc =   0.0000e+00
+ dcjorsti_p5pfet50_fc =  -1.4533e-11
+ dcjorgat_p5pfet50_fc =  -2.8000e-11
+ dvfbl_p5pfet50_fc =   0.0000e+00
+ dcjorbot_p5pfet50_fc =  -1.0667e-04
+ dtoxo_p5pfet50_fc =  -5.3333e-10
+ dthesatl_p5pfet50_fc =  -2.0000e-03
+ dfol1_p5pfet50_fc =   2.0000e-04
+ dlap_p5pfet50_fc =   1.6667e-08
+ dvfblw_p5pfet50_fc =   0.0000e+00
+ duo_p5pfet50_fc =   1.2123e-03
+ drsw1_p5pfet50_fc =  -2.5000e+01
+ dwot_p5pfet50_fc =  -3.3333e-08
.endl fff_p5pf50

.lib ssf_p5pf50
.param
+ dvfbo_p5pfet50_fc =   2.7163e-02
+ dfol2_p5pfet50_fc =   0.0000e+00
+ dcjorsti_p5pfet50_fc =  -4.6133e-11
+ dcjorgat_p5pfet50_fc =   2.8000e-11
+ dvfbl_p5pfet50_fc =   0.0000e+00
+ dcjorbot_p5pfet50_fc =   1.0667e-04
+ dtoxo_p5pfet50_fc =   5.3333e-10
+ dthesatl_p5pfet50_fc =   2.0000e-03
+ dfol1_p5pfet50_fc =  -2.0000e-04
+ dlap_p5pfet50_fc =  -1.6667e-08
+ dvfblw_p5pfet50_fc =   0.0000e+00
+ duo_p5pfet50_fc =  -1.4011e-03
+ drsw1_p5pfet50_fc =   2.5000e+01
+ dwot_p5pfet50_fc =   3.3333e-08
.endl ssf_p5pf50

.lib  tt_bsim
.param 
+ cor_rx_fc    = 0
+ cor_pc_fc    = 0
+ cor_tox_fc   = 0
+ cor_toxdg_fc = 0
+ cor_toxtg_fc = 0
+ cor_nf18_fc  = 0
+ cor_pf18_fc  = 0
+ cor_nfhv_fc  = 0
+ cor_pfhv_fc  = 0
+ cor_nf33_fc  = 0
+ cor_pf33_fc  = 0
+ cor_zn_fc    = 0
+ cor_zn33_fc  = 0
.endl  tt_bsim

.lib  ff_bsim
.param 
+ cor_rx_fc    = 0.25
+ cor_pc_fc    = 0.25
+ cor_tox_fc   = 0.75
+ cor_toxdg_fc = 0.75
+ cor_toxtg_fc = 0.75
+ cor_nf18_fc  = 1.3461
+ cor_pf18_fc  = 1.3461
+ cor_nfhv_fc  = 1.5121
+ cor_pfhv_fc  = 1.5121
+ cor_nf33_fc  = 1.5297
+ cor_pf33_fc  = 1.5297
+ cor_zn_fc    = 1.3461
+ cor_zn33_fc  = 1.5297
.endl  ff_bsim

.lib  ss_bsim
.param 
+ cor_rx_fc    = -0.25
+ cor_pc_fc    = -0.25
+ cor_tox_fc   = -0.75
+ cor_toxdg_fc = -0.75
+ cor_toxtg_fc = -0.75
+ cor_nf18_fc  = -1.2777
+ cor_pf18_fc  = -1.2777
+ cor_nfhv_fc  = -1.0893
+ cor_pfhv_fc  = -1.0893
+ cor_nf33_fc  = -1.6858
+ cor_pf33_fc  = -1.6858
+ cor_zn_fc    = -1.2770
+ cor_zn33_fc  = -1.6858
.endl  ss_bsim

.lib  fs_bsim
.param 
+ cor_rx_fc    = 0
+ cor_pc_fc    = 0
+ cor_tox_fc   = 0
+ cor_toxdg_fc = 0
+ cor_toxtg_fc = 0
+ cor_nf18_fc  = 1.05
+ cor_pf18_fc  = -1.10
+ cor_nfhv_fc  = 1.05
+ cor_pfhv_fc  = -1.15
+ cor_nf33_fc  = 1.25
+ cor_pf33_fc  = -1.20
+ cor_zn_fc    = 1.05
+ cor_zn33_fc  = 1.25
.endl  fs_bsim

.lib  sf_bsim
.param 
+ cor_rx_fc    = 0
+ cor_pc_fc    = 0
+ cor_tox_fc   = 0
+ cor_toxdg_fc = 0
+ cor_toxtg_fc = 0
+ cor_nf18_fc  = -1.10
+ cor_pf18_fc  = 1.05
+ cor_nfhv_fc  = -1.15
+ cor_pfhv_fc  = 1.05
+ cor_nf33_fc  = -1.20
+ cor_pf33_fc  = 1.25
+ cor_zn_fc    = -1.10
+ cor_zn33_fc  = -1.20
.endl  sf_bsim

.lib  fff_bsim
.param 
+ cor_rx_fc    = 0.5
+ cor_pc_fc    = 0.5
+ cor_tox_fc   = 1.5
+ cor_toxdg_fc = 1.5
+ cor_toxtg_fc = 1.5
+ cor_nf18_fc  = 2.0
+ cor_pf18_fc  = 2.0
+ cor_nfhv_fc  = 2.0
+ cor_pfhv_fc  = 2.0
+ cor_nf33_fc  = 2.0
+ cor_pf33_fc  = 2.0
+ cor_zn_fc    = 2.0
+ cor_zn33_fc  = 2.0
.endl  fff_bsim

.lib  ssf_bsim
.param 
+ cor_rx_fc    = -0.5
+ cor_pc_fc    = -0.5
+ cor_tox_fc   = -1.5
+ cor_toxdg_fc = -1.5
+ cor_toxtg_fc = -1.5
+ cor_nf18_fc  = -2.0
+ cor_pf18_fc  = -2.0
+ cor_nfhv_fc  = -2.0
+ cor_pfhv_fc  = -2.0
+ cor_nf33_fc  = -2.0
+ cor_pf33_fc  = -2.0
+ cor_zn_fc    = -2.0
+ cor_zn33_fc  = -2.0
.endl  ssf_bsim

.lib  tt
.param  fixcnr = 0
.inc 'fixed_corner'   tt_nfet
.inc 'fixed_corner'   tt_pfet
.inc 'fixed_corner'   tt_nf33
.inc 'fixed_corner'   tt_pf33
.inc 'fixed_corner'   tt_nf50
.inc 'fixed_corner'   tt_pf50
.inc 'fixed_corner'   tt_p5pf50
.inc 'fixed_corner'   tt_bsim
.endl  tt

.lib  ff
.param  fixcnr = 1
.lib 'fixed_corner'   ff_nfet
.lib 'fixed_corner'   ff_pfet
.lib 'fixed_corner'   ff_nf33
.lib 'fixed_corner'   ff_pf33
.lib 'fixed_corner'   ff_nf50
.lib 'fixed_corner'   ff_pf50
.lib 'fixed_corner'   ff_p5pf50
.lib 'fixed_corner'   ff_bsim
.endl  ff 

.lib  ss
.param  fixcnr = 1
.lib 'fixed_corner'   ss_nfet
.lib 'fixed_corner'   ss_pfet
.lib 'fixed_corner'   ss_nf33
.lib 'fixed_corner'   ss_pf33
.lib 'fixed_corner'   ss_nf50
.lib 'fixed_corner'   ss_pf50
.lib 'fixed_corner'   ss_p5pf50
.lib 'fixed_corner'   ss_bsim
.endl  ss      

.lib  fs
.param  fixcnr = 1
.lib 'fixed_corner'   fs_nfet
.lib 'fixed_corner'   fs_pfet
.lib 'fixed_corner'   fs_nf33
.lib 'fixed_corner'   fs_pf33
.lib 'fixed_corner'   fs_nf50
.lib 'fixed_corner'   fs_pf50
.lib 'fixed_corner'   fs_p5pf50
.lib 'fixed_corner'   fs_bsim
.endl  fs 

.lib  sf
.param  fixcnr = 1
.lib 'fixed_corner'   sf_nfet
.lib 'fixed_corner'   sf_pfet
.lib 'fixed_corner'   sf_nf33
.lib 'fixed_corner'   sf_pf33
.lib 'fixed_corner'   sf_nf50
.lib 'fixed_corner'   sf_pf50
.lib 'fixed_corner'   sf_p5pf50
.lib 'fixed_corner'   sf_bsim
.endl  sf      

.lib  fff
.param  fixcnr = 1
.lib 'fixed_corner'   fff_nfet
.lib 'fixed_corner'   fff_pfet
.lib 'fixed_corner'   fff_nf33
.lib 'fixed_corner'   fff_pf33
.lib 'fixed_corner'   fff_nf50
.lib 'fixed_corner'   fff_pf50
.lib 'fixed_corner'   fff_p5pf50
.lib 'fixed_corner'   fff_bsim
.endl  fff 

.lib  ssf
.param  fixcnr = 1
.lib 'fixed_corner'   ssf_nfet
.lib 'fixed_corner'   ssf_pfet
.lib 'fixed_corner'   ssf_nf33
.lib 'fixed_corner'   ssf_pf33
.lib 'fixed_corner'   ssf_nf50
.lib 'fixed_corner'   ssf_pf50
.lib 'fixed_corner'   ssf_p5pf50
.lib 'fixed_corner'   ssf_bsim
.endl  ssf
