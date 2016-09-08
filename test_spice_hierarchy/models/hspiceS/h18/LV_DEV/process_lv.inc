* Path, Component, Release: cmhv7sf/rel/HSPICE/models/process_lv.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
*
***********************************************************************
*
*>  process_lv.inc  Statistical Process / Device Parameters
*
*
***********************************************************************
 
.lib lvstats
***********************************************************************
* Global Functions / User Input Parameters
***********************************************************************
.param
+   mc_d1    = agauss(0,1,3)
+   mc_d2    = agauss(0,1,3)
+   mc_d3    = agauss(0,1,3)
+   mc_sw    = '(mc_d1 != 0) || (mc_d2 != 0) || (mc_d3 != 0)'
*
***********************************************************************
* Statistical and Corner Analysis Selections
*     Note: Corners and Monte Carlo mutually exclusive
* Translate Corner Value to Distribution "Sigma" ( divide by 3 )
***********************************************************************
.param
+   cnr_rx      = '(1-mc_sw) * (cor_rx_fc + cor_rx*(1-fixcnrlv))/3'
+   cnr_pc      = '(1-mc_sw) * (cor_pc_fc + cor_pc*(1-fixcnrlv))/3'
+   cnr_tox     = '(1-mc_sw) * (cor_tox_fc + cor_tox*(1-fixcnrlv))/3'
+   cnr_toxm    = '(1-mc_sw) * (cor_toxm_fc + cor_toxm*(1-fixcnrlv))/3'
+   cnr_toxh    = '(1-mc_sw) * (cor_toxh*(1-fixcnrlv))/3'
+   cnr_cap     = '(1-mc_sw) * (cor_cap_fc + cor_cap*(1-fixcnrc))/3'
+   cnr_dio     = '(1-mc_sw) * (cor_dio_fc + cor_dio*(1-fixcnrd))/3'
+   cnr_ind     = '(1-mc_sw) * (cor_ind_fc + cor_ind*(1-fixcnrc))/3'
+   cnr_lv_noin = '(1-mc_sw) * cor_lv_noin/3'
+   cnr_lv_noip = '(1-mc_sw) * cor_lv_noip/3'
+   cnr_res     = '(1-mc_sw) * (cor_res_fc + cor_res*(1-fixcnrr))/3'
*
+   cnr_lv_nmos = 'cor_lv_nmos * (1-fixcnrlv)'
+   cnr_lv_pmos = 'cor_lv_pmos * (1-fixcnrlv)'
*
+   cnr_nfet  = '(1-mc_sw) * (cnr_lv_nmos)/3'
+   cnr_pfet  = '(1-mc_sw) * (cnr_lv_pmos)/3'
+   cnr_nhvt  = '(1-mc_sw) * (cnr_lv_nmos)/3'
+   cnr_phvt  = '(1-mc_sw) * (cnr_lv_pmos)/3'
+   cnr_nshvt = '(1-mc_sw) * (cnr_lv_nmos)/3'
+   cnr_pshvt = '(1-mc_sw) * (cnr_lv_pmos)/3'
+   cnr_nf5m  = '(1-mc_sw) * (cnr_lv_nmos)/3'
+   cnr_pf5m  = '(1-mc_sw) * (cnr_lv_pmos)/3'
*
+   npmsxt = 'waferthk*1.0e-6'    $ Convert units for nominal value
*
***********************************************************************
* Process Parameters
***********************************************************************
*
.param
+   pi         = 3.14159
+   e0         = 8.8542p
+   ersi       = 11.9
+   mu0        = 1.2566e-6
+   eoxdepo    = 4.1
*
*                                            $ Process Image Distributions
+   xistrx     = agauss(cnr_rx,1,3)          $ RX bias
+   distrx     = xistrx
+   xistpc     = agauss('-cnr_pc',1,3)       $ PC bias
+   distpc     = xistpc
+   xistop     = agauss(0,1,3)               $ OP bias
+   distop     = xistop
+   xistnw     = agauss(0,1,3)               $ NW bias
+   distnw     = xistnw
+   xistk1     = agauss(0,1,3)               $ K1 bias
+   distk1     = xistk1
+   xistv1     = agauss(0,1,3)               $ V1 bias
+   distv1     = xistv1
*
*                                            $ Process Profile Distributions
+   xistoxt    = agauss('-cnr_tox',1,3)      $ 1.8V Gate oxide
+   distoxt    = xistoxt
+   xistoxm    = agauss('-cnr_toxm',1,3)     $ 5V Gate oxide
+   distoxm    = xistoxm
+   xistoxh    = agauss('-cnr_toxh',1,3)     $ HV Gate oxide
+   distoxh    = xistoxh
+   xpcthk     = agauss(cnr_ind,1,3)         $ Poly Line Thickness
+   dpcthk     = xpcthk
+   xpcsti     = agauss(cnr_ind,1,3)         $ STI Thickness
+   dpcsti     = xpcsti
* 
+   tdelrx     = '0.049u * distrx'           $ RX bias tolerance
+   tdelpc     = '0.03u * distpc'            $ PC bias tolerance
+   opdld      = '0.105u * distop'           $ OP bias tolerance
+   delnw      = '0.44u + 0.24u*distnw'      $ NW image bias
*
+   lwbpc      = '-0.03u + tdelpc'           $ Poly Line Width Bias (Thin ox)
+   lwbpc33    = '-0.11u + tdelpc'           $ Poly Line Width Bias (Thick ox)
+   oppcthk    = '0.20u + 0.02u*dpcthk'      $ Poly Line Thickness
+   oppcstin   = 0.33u                       $ Effective STI Thickness
+   oppcstif   = 'oppcstin + 0.04u*dpcsti'
*
+   opendf     = 0.76u                $ RX overlap past CA
+   oppcendf   = 0.72u                $ PC overlap past CA
+   k1endf     = 0.78u                $ K1 overlap past V1
*
*                                       PC area, peri cap (F/meter**2, F/meter)
+   oppcdown   = '3.453E-11 / oppcstif'
+   oppcfrng   = '3.453E-11 * (2.0 + (2/pi)*log(1 + oppcthk/oppcstif))'
*
*                                              N+ S/D Resistor
*
+   xndrs      = agauss(cnr_res,1,3)         $ Distributions
+   dndrs      = xndrs
+   xndren     = agauss(cnr_res,1,3)
+   dndren     = xndren
+   xnoind     = agauss(cnr_res,1,3)
+   dnoind     = xnoind
*
+   opndrsn    = '72 - 3*p5vonly'            $ Rs, ohm/sq
+   opndrsf    = 'opndrsn + 7.2*dndrs'
+   opndrenn   = 2.321                       $ Rend, ohm-meter exponent
+   opndrenf   = 'opndrenn+ 1.531*dndren'
+   opnddln    =  0u                         $ delta lop
+   opnddlf    = 'opnddln + opdld'
+   opnddwn    =  0u                         $ delta w
+   opnddwf    = 'opnddwn + tdelrx'
+   opndrstc   =  1900u                      $ Rs   Tcr = +1900 ppm
+   opndrntc   =   600u                      $ Rend Tcr = + 600 ppm
+   opndvcr    =   650u                      $ Vcr =  650 ppm/V
+   opndma     =  4.0                        $ Mis-match coefficients
+   opndml     =  7.0
+   opndmw     =  0.5
*
*                                              P+ S/D Resistor
*
+   xpdrs      = agauss(cnr_res,1,3)         $ Distributions
+   dpdrs      = xpdrs
+   xpdren     = agauss(cnr_res,1,3)
+   dpdren     = xpdren
+   xnoipd     = agauss(cnr_res,1,3)
+   dnoipd     = xnoipd
*
+   oppdrsn    = 105                         $ Rs, ohm/sq
+   oppdrsf    = 'oppdrsn + 15*dpdrs'
+   oppdrenn   = 3.4012                      $ Rend, ohm-meter exponent
+   oppdrenf   = 'oppdrenn + 0.693*dpdren'
+   oppddln    =  0u                         $ delta lop
+   oppddlf    = 'oppddln + opdld'
+   oppddwn    = -0.07u                      $ delta w
+   oppddwf    = 'oppddwn + tdelrx'
+   oppdrstc   =  1340u                      $ Rs   Tcr = +1340 ppm
+   oppdrntc   = -160u                       $ Rend Tcr =  -160 ppm
+   oppdvcr    =  540u                       $ Vcr = 540 ppm/V
+   oppdma     =  8.0                        $ Mis-match coefficients
+   oppdml     =  9.0
+   oppdmw     =  1.0
*
*                                              N+ Poly Resistor
*
+   xnpcrs     = agauss(cnr_res,1,3)         $ Distributions
+   dnpcrs     = xnpcrs
+   xnpcren    = agauss(cnr_res,1,3)
+   dnpcren    = xnpcren
+   xnoinpc    = agauss(cnr_res,1,3)
+   dnoinpc    = xnoinpc
*
+   opnpcrsn   =  370                        $ Rs, ohm/sq
+   opnpcrsf   = 'opnpcrsn + 55.5*dnpcrs'
+   opnpcrenn  = 5.031                       $ Rend, ohm-meter exponent
+   opnpcrenf  = 'opnpcrenn + 0.3118*dnpcren'
+   opnpcdln   =  0u                         $ delta lop
+   opnpcdlf   = 'opnpcdln + opdld'
+   opnpcdwn   = -0.05u                      $ delta w
+   opnpcdwf   = 'opnpcdwn + 0.1u*distpc'
+   opnpcrstc  = -812u                       $ Rs   Tcr = - 812 ppm
+   opnpcrntc  =  0                          $ Rend Tcr = 0 ppm
+   opnpcvcr   = -70u                        $ Vcr = -70 ppm/V
+   opnpshk    =  74                         $ Self-heating parameters
+   opnpshm    =  0.78
+   opnpcma    =  0                          $ Mis-match coefficients
+   opnpcml    =  2.45
+   opnpcmw    =  6
*
*                                              P+ Poly Resistor
*
+   xpcrs      = agauss(cnr_res,1,3)         $ Distributions
+   dpcrs      = xpcrs
+   xpcren     = agauss(cnr_res,1,3)
+   dpcren     = xpcren
+   xnoippc    = agauss(cnr_res,1,3)
+   dnoippc    = xnoippc
*
+   oppcrsn    =  260                        $ Rs, ohm/sq
+   oppcrsf    = 'oppcrsn + 39*dpcrs'
+   oppcrenn   = 5.031                       $ Rend, ohm-meter exponent
+   oppcrenf   = 'oppcrenn + 0.3118*dpcren'
+   oppcdln    =  0u                         $ delta lop
+   oppcdlf    = 'oppcdln + opdld'
+   oppcdwn    = -0.04u                      $ delta w
+   oppcdwf    = 'oppcdwn + tdelpc'
+   oppcrstc   =  160u                       $ Rs   Tcr = + 160 ppm
+   oppcrntc   = -790u                       $ Rend Tcr = - 790 ppm
+   oppcvcr    =  55u                        $ Vcr = 55 ppm/V
+   oppcma     =  5.0                        $ Mis-match coefficients
+   oppcml     =  2.0
+   oppcmw     =  0
*
*                                              RP Poly Resistor
*
+   xrprs      = agauss(cnr_res,1,3)         $ Distributions
+   drprs      = xrprs
+   xrpren     = agauss(cnr_res,1,3)
+   drpren     = xrpren
+   xnoirp     = agauss(cnr_res,1,3)
+   dnoirp     = xnoirp
*
+   oprprsn    =  165                        $ Rs, ohm/sq
+   oprprsf    = 'oprprsn + 13.2*drprs'
+   oprprenn   =  2.6391                     $ Rend, ohm-meter exponent
+   oprprenf   = 'oprprenn + 1.253*drpren'
+   oprpdln    =  0u                         $ delta lop
+   oprpdlf    = 'oprpdln + opdld'
+   oprpdwn    = -0.03u                      $ delta w
+   oprpdwf    = 'oprpdwn + tdelpc'
+   oprprstc   =  210u                       $ Rs   Tcr = + 210 ppm
+   oprprntc   = -1960u                      $ Rend Tcr = -1960 ppm
+   oprpvcr    =  35u                        $ Vcr = 35 ppm/V
+   oprpma     =  6.5                        $ Mis-match coefficients
+   oprpml     =  0
+   oprpmw     =  0.9
*
*                                              RR Poly Resistor
*
+   xrrrs      = agauss(cnr_res,1,3)         $ Distributions
+   drrrs      = xrrrs
+   xdlbn      = agauss('-cnr_res',1,3)
+   ddlbn      = xdlbn
+   xnoirr     = agauss(cnr_res,1,3)
+   dnoirr     = xnoirr
*
+   oprrrsn    = 1600                        $ Rs, ohm/sq
+   oprrrsf    = 'oprrrsn + 320*drrrs'
+   opdlbnn    =  0.490u                     $ BN overlap OP + outdiffusion
+   opdlbnf    = 'opdlbnn + 0.11u*ddlbn'
+   oprrdwn    = -0.04u                      $ delta w
+   oprrdwf    = 'oprrdwn + tdelpc'
+   oprrtc1    = -1360u                      $ Rs Tcr1 = -1360 ppm
+   oprrtc2    =  3.33u                      $ Rs Tcr2 = +3.33 ppm
+   oprrshk    =  131                        $ Self-heating parameters
+   oprrshm    =  0.2
+   oprrvcr    =  215u                       $ Vcr = 215 ppm/V
+   oprrma     =  8.5                        $ Mis-match coefficients
+   oprrml     =  7.0
+   oprrmw     =  0
*
*                                              K1 BEOL Resistor
*
+   xk1rs      = agauss(cnr_res,1,3)         $ Distributions
+   dk1rs      = xk1rs
+   xk1ren     = agauss(cnr_res,1,3)
+   dk1ren     = xk1ren
+   xnoik1     = agauss(cnr_res,1,3)
+   dnoik1     = xnoik1
*
+   k1rsn      =  61                         $ Rs, ohm/sq
+   k1rsf      = 'k1rsn + 4.88*dk1rs'
+   k1renn     =  3.4012                     $ Rend exponent, ohm-meter
+   k1renf     = 'k1renn + 0.69*dk1ren'
+   k1dln      =  0u                         $ delta l
+   k1dlf      = 'k1dln - 0.07u*distv1'  
+   k1dwn      =  0.32u                      $ delta w
+   k1dwf      = 'k1dwn + 0.14u*distk1'
+   k1rstc     = -420u                       $ Rs Tc1 = - 420 ppm
+   k1rntc     =  600u                       $ Ren Tc = + 600 ppm
+   k1ma       =  0                          $ Mis-match coefficients
+   k1ml       =  0.60
+   k1mw       =  0.45
+   k1ms       =  0.09
*
+   ndelrx     = -0.06u                      $ Shallow Trench Image
+   delrx      = 'ndelrx  + tdelrx'
+   xpcrsi     = agauss(0,1,3)               $ Silicided Poly Sheet Rho dist
+   dpcrsi     = xpcrsi
+   pcrsi      = '8.0 + 3.0*dpcrsi'          $ Silicided Poly Rs (ohm/sq)
*
*                                              DI Diode / VPNP
*
+   xistdi     = agauss(cnr_dio,1,3)         $ Distributions
+   distdi     = xistdi
+   xpwrs      = agauss(cnr_dio,1,3)
+   dpwrs      = xpwrs
*
+   tdeldi     = '0.5*distdi'                $ Sat Current Tolerance
*
+   js_di      = '3.8u + 1.9u*dnwjs'         $ DI Nwell/SX Sat Current (A/meter**2)
+   jsw_di     = '5.2p + 2.6p*dnwjs'         $ Sidewall Sat Current (A/meter)
+   cj_di      = '0.20m + 0.05m*dnwcj'       $ Capacitance (F/meter**2)
+   cjsw_di    = '1.65n + 0.41n*dnwcjsw'     $ Sidewall Cap (F/meter)
*
+   pwrs       = '(430+30*p5vonly)*(1+0.35*dpwrs)'     $ PWell Sheet Rho (ohm/sq)
+   pwrv       = '(540p+310p*p5vonly)*(1+0.25*dpwrs)'  $ Vertical PWell (ohm-meter**2)
*
*                                            NFET
*
+   xnvth0  = agauss('-cnr_nfet',1,3)    $ Distributions
+   dnvth0  = xnvth0
+   xnvfbl  = agauss('-cnr_nfet',1,3)
+   dnvfbl  = xnvfbl
+   xnu0    = agauss(cnr_nfet,1,3)
+   dnu0    = xnu0
+   xnrdsw  = agauss('-cnr_nfet',1,3)
+   dnrdsw  = xnrdsw
+   xnfol   = agauss('cnr_nfet',1,3)
+   dnfol   = xnfol
+   xnjs    = agauss('cnr_dio',1,3)
+   dnjs    = xnjs
+   xncj    = agauss('-cnr_nfet',1,3)
+   dncj    = xncj
+   xncjsw  = agauss('-cnr_nfet',1,3)
+   dncjsw  = xncjsw
+   xncjsg  = agauss('-cnr_nfet',1,3)
+   dncjsg  = xncjsg
+   xnoin   = agauss('-cnr_lv_noin',1,3)
+   dnoin   = xnoin
+   xistncov = agauss('-cnr_nfet',1,3)
+   distncov = xistncov
*
+   tox_n   = '3.74n + 0.3n*distoxt*(1-fixcnrlv) + dtoxo_nfet_fc' $ Gate oxide thickness (meter)
+   vtol_n  = '0.025*dnvth0'
+   vfb_n   = '-1.463 + vtol_n + dvfbo_nfet_fc'             $ Base Threshold voltage (V)
+   vfbl_n  = '-8.5m + 3m*dnvfbl + dvfbl_nfet_fc'
+   vfblw_n = '-3.559m + dvfblw_nfet_fc'
+   ltol_n  = '-8.5n*distpc*(1-fixcnrlv)'
+   lint_n  = '0.0175u + ltol_n + dlap_nfet_fc'             $ Delta L (one side)
+   lov_n   = '40n + 3.5n*distncov - 1.5n*distpc + dlov_nfet_fc'
+   wtol_n  = '-0.05u*distrx*(1-fixcnrlv)'
+   wint_n  = '0.01u + wtol_n + dwot_nfet_fc'               $ Delta W (one side)
+   uo_n    = 'exp(-3.0262 + 0.14*dnu0) + duo_nfet_fc'      $ Base mobility (m**2/Vsec)
+   rsw_n   = '62.5 + 9*dnrdsw + drsw1_nfet_fc'             $ Base series resistance (ohm-um)
+   fol1_n  = '20m + 10m*dnfol + dfol1_nfet_fc'             $ First order short channel roll-off and body effect
+   fol2_n  = '10u + 2.5u*dnfol + dfol2_nfet_fc'            $ Second order short channel roll-off and body effect
+   thesatl_n = '0.6514 + dthesatl_nfet_fc'                 $ Saturation velocity
*
+   rsh_n  = 8                         $ S/D sheet resistance (ohms/sq)
+   tdeljs = '0.5*dnjs'                $ Sat Current Tolerance
+   js_n   = '90n*(1+tdeljs)'          $ N+ Area Sat Cur (A/meter**2)
+   jsw_n  = '120f*(1+tdeljs)'         $ N+ Sidewall Sat Cur (A/meter)
+   n_n    = 1.02                      $ Ideality
+   cj_n   = '(1.12m+0.20m*dncj+dcjorbot_nfet_fc)*(1-p5vonly) + cj_n5m*p5vonly'   $ N+ Diode Cap (F/meter**2)
+   pb_n   = '0.61*(1-p5vonly) + pb_n5m*p5vonly'       $ Voltage dependence
+   mj_n   = '0.46*(1-p5vonly) + mj_n5m*p5vonly'
+   cjsw_n = '(155p+39p*dncjsw+dcjorsti_nfet_fc)*(1-p5vonly) + cjsw_n5m*p5vonly'  $ N+ STI Sidewall Cap (F/meter)
+   pbsw_n = '0.42*(1-p5vonly) + pbsw_n5m*p5vonly'     $ Voltage dependence
+   mjsw_n = '0.40*(1-p5vonly) + mjsw_n5m*p5vonly'
+   cjsg_n = '315p + 78.8p*dncjsg + dcjorgat_nfet_fc'  $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_n = 1.0                       $ Voltage dependence
+   mjsg_n = 0.45
+   cta_n  = '1.1m*(1-p5vonly) + cta_n5m*p5vonly'      $ Cap temperature dependence
+   pta_n  = '1.2m*(1-p5vonly) + pta_n5m*p5vonly'
+   ctp_n  = '1.2m*(1-p5vonly) + ctp_n5m*p5vonly'
+   ptp_n  = '0.98m*(1-p5vonly) + ptp_n5m*p5vonly'
+   noideva_n = 1.8e-11                $ Area, 1/f statistics (meter*2)
+   noistd_n  = 2.0                    $ 3-sigma log noise distribution
*
*                                            NFETI
*
+   tox_ni   = '3.59n + 0.3n*distoxt*(1-fixcnrlv) + dtoxo_nfeti_fc' $ Gate oxide thickness (meter)
+   vtol_ni  = '0.020*dnvth0'
+   vfb_ni   = '-1.491 + vtol_ni + dvfbo_nfeti_fc'            $ Base Threshold voltage (V)
+   vfbl_ni  = '-7.25m + 2.5m*dnvfbl + dvfbl_nfeti_fc'
+   vfblw_ni = '-4m + dvfblw_nfeti_fc'
+   lint_ni  = '0.0175u + ltol_n + dlap_nfeti_fc'             $ Delta L (one side)
+   lov_ni   = '38.5n + 3.3n*distncov - 1.5n*distpc + dlov_nfeti_fc'
+   wint_ni  = '0.01u + wtol_n + dwot_nfeti_fc'               $ Delta W (one side)
+   uo_ni    = 'exp(-3.02 + 0.135*dnu0) + duo_nfeti_fc'       $ Base mobility (m**2/Vsec)
+   rsw_ni   = '52.09 + 9*dnrdsw + drsw1_nfeti_fc'            $ Base series resistance (ohm-um)
+   fol1_ni  = '13.54m + 9m*dnfol + dfol1_nfeti_fc'           $ First order short channel roll-off and body effect
+   fol2_ni  = '969.2u + 200u*dnfol + dfol2_nfeti_fc'         $ Second order short channel roll-off and body effect
+   thesatl_ni = '0.6504 + dthesatl_nfeti_fc'                 $ Saturation velocity
*
+   rsh_ni  = 8                         $ S/D sheet resistance (ohms/sq)
+   js_ni  = '90n*(1+tdeljs)'           $ N+ Area Sat Cur (A/meter**2)
+   jsw_ni = '120f*(1+tdeljs)'          $ N+ Sidewall Sat Cur (A/meter)
+   n_ni    = 1.02                      $ Ideality
+   cj_ni   = '(1.05m+0.20m*dncj+dcjorbot_nfeti_fc)*(1-p5vonly) + cj_n5im*p5vonly'   $ N+ Diode Cap (F/meter**2)
+   pb_ni   = '0.535*(1-p5vonly) + pb_n5im*p5vonly'      $ Voltage dependence
+   mj_ni   = '0.368*(1-p5vonly) + mj_n5im*p5vonly'
+   cjsw_ni = '(155p+39p*dncjsw+dcjorsti_nfeti_fc)*(1-p5vonly) + cjsw_n5im*p5vonly'  $ N+ STI Sidewall Cap (F/meter)
+   pbsw_ni = '0.42*(1-p5vonly) + pbsw_n5im*p5vonly'     $ Voltage dependence
+   mjsw_ni = '0.40*(1-p5vonly) + mjsw_n5im*p5vonly'
+   cjsg_ni = '380p + 95p*dncjsg + dcjorgat_nfeti_fc'    $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_ni = 1.0                       $ Voltage dependence
+   mjsg_ni = 0.45
+   cta_ni  = '1.1m*(1-p5vonly) + cta_n5im*p5vonly'      $ Cap temperature dependence
+   pta_ni  = '1.2m*(1-p5vonly) + pta_n5im*p5vonly'
+   ctp_ni  = '1.2m*(1-p5vonly) + ctp_n5im*p5vonly'
+   ptp_ni  = '0.98m*(1-p5vonly) + ptp_n5im*p5vonly'
*
*                                            PFET
*
+   xpvth0 = agauss(cnr_pfet,1,3)      $ Distributions
+   dpvth0 = xpvth0
+   xpu0   = agauss(cnr_pfet,1,3)
+   dpu0   = xpu0
+   xprdsw = agauss('-cnr_pfet',1,3)
+   dprdsw = xprdsw
+   xpfol  = agauss('cnr_pfet',1,3)
+   dpfol  = xpfol
+   xpcj   = agauss('-cnr_pfet',1,3)
+   dpcj   = xpcj
+   xpcjsw = agauss('-cnr_pfet',1,3)
+   dpcjsw = xpcjsw
+   xpcjsg = agauss('-cnr_pfet',1,3)
+   dpcjsg = xpcjsg
+   xnoip  = agauss('-cnr_lv_noip',1,3)
+   dnoip  = xnoip
+   xistpcov = agauss('-cnr_pfet',1,3)
+   distpcov = xistpcov
*
+   tox_p   = '3.84n + 0.3n*distoxt*(1-fixcnrlv) + dtoxo_pfet_fc' $ Gate oxide thickness (meter)
+   vtol_p  = '-0.018*dpvth0'
+   vfb_p   = '-1.292 + vtol_p + dvfbo_pfet_fc'                $ Base Threshold voltage (V)
+   vfbl_p  = '-9m + dvfbl_pfet_fc'
+   vfblw_p = '1.663m + dvfblw_pfet_fc'
+   ltol_p  = '-8.5n*distpc*(1-fixcnrlv)'
+   lint_p  = '0.0175u + ltol_p + dlap_pfet_fc'                $ Delta L (one side)
+   lov_p   = '44.6n + 3.68n*distpcov - 0.8n*distpc + dlov_pfet_fc'
+   wtol_p  = '-0.05u*distrx*(1-fixcnrlv)'
+   wint_p  = '0.01u + wtol_p + dwot_pfet_fc'                  $ Delta W (one side)
+   uo_p    = '0.02685 + 0.001*dpu0 + duo_pfet_fc'             $ Base mobility (m**2/Vsec)
+   rsw_p   = '120 + 30*dprdsw + drsw1_pfet_fc'                $ Base series resistance (ohm-um)
+   fol1_p  = '47.83m + 12m*dpfol + dfol1_pfet_fc'             $ First order short channel roll-off and body effect
+   fol2_p  = '1.296m + 0.5m*dpfol + dfol2_pfet_fc'            $ Second order short channel roll-off and body effect
+   thesatl_p = '0.4151 + dthesatl_pfet_fc'                    $ Saturation velocity
*
+   rsh_p  = 8                           $ S/D sheet resistance (ohms/sq)
+   js_p   = '100n*(1+tdeldi)'           $ P+ Area Sat Cur (A/meter**2)
+   jsw_p  = '45f*(1+tdeldi)'            $ P+ Sidewall Sat Cur (A/meter)
+   n_p    = 1.007                       $ Ideality
+   cj_p   = '(1.15m+0.16m*dpcj+dcjorbot_pfet_fc)*(1-p5vonly) + cj_p5m*p5vonly'    $ P+ Diode Cap (F/meter**2)
+   pb_p   = '0.73*(1-p5vonly) + pb_p5m*p5vonly'        $ Voltage dependence
+   mj_p   = '0.42*(1-p5vonly) + mj_p5m*p5vonly'
+   cjsw_p = '(90p+22.5p*dpcjsw+dcjorsti_pfet_fc)*(1-p5vonly) + cjsw_p5m*p5vonly'  $ P+ STI Sidewall Cap (F/meter)
+   pbsw_p = '0.99*(1-p5vonly) + pbsw_p5m*p5vonly'      $ Voltage dependence
+   mjsw_p = '0.01*(1-p5vonly) + mjsw_p5m*p5vonly'
+   cjsg_p = '312p + 78p*dpcjsg + dcjorgat_pfet_fc'     $ P+ Gate Sidewall Cap (F/meter)
+   pbsg_p = 1.0                         $ Voltage dependence
+   mjsg_p = 0.5
+   cta_p  = '0.9m*(1-p5vonly) + cta_p5m*p5vonly'       $ Cap temperature dependence
+   pta_p  = '1.3m*(1-p5vonly) + pta_p5m*p5vonly'
+   ctp_p  = '0*(1-p5vonly) + ctp_p5m*p5vonly'
+   ptp_p  = '0*(1-p5vonly) + ptp_p5m*p5vonly'
+   noideva_p = 1.8e-11                  $ Area, 1/f statistics (meter*2)
+   noistd_p  = 2.2                      $ 3-sigma log noise distribution
*
*                                            PFETI
*
+   tox_pi   = '3.84n + 0.3n*distoxt*(1-fixcnrlv) + dtoxo_pfeti_fc' $ Gate oxide thickness (meter)
+   vtol_pi  = '-0.015*dpvth0'
+   vfb_pi   = '-1.304 + vtol_pi + dvfbo_pfeti_fc'               $ Base Threshold voltage (V)
+   vfbl_pi  = '-9.75m + dvfbl_pfeti_fc'
+   vfblw_pi = '1.10m + dvfblw_pfeti_fc'
+   lint_pi  = '0.0175u + ltol_p + dlap_pfeti_fc'                $ Delta L (one side)
+   lov_pi   = '44.6n + 3.68n*distpcov - 0.8n*distpc + dlov_pfeti_fc'
+   wint_pi  = '0.01u + wtol_p + dwot_pfeti_fc'                  $ Delta W (one side)
+   uo_pi    = '0.02456 + 0.001*dpu0 + duo_pfeti_fc'             $ Base mobility (m**2/Vsec)
+   rsw_pi   = '120 + 30*dprdsw + drsw1_pfeti_fc'                $ Base series resistance (ohm-um)
+   fol1_pi  = '62m + 15m*dpfol + dfol1_pfeti_fc'                $ First order short channel roll-off and body effect
+   fol2_pi  = '0 + 0.0*dpfol + dfol2_pfeti_fc'                  $ Second order short channel roll-off and body effect
+   thesatl_pi = '0.4261 + dthesatl_pfeti_fc'                    $ Saturation velocity
*
+   rsh_pi  = 8                           $ S/D sheet resistance (ohms/sq)
+   js_pi  = '100n*(1+tdeldi)'            $ P+ Area Sat Cur (A/meter**2)
+   jsw_pi = '45f*(1+tdeldi)'             $ P+ Sidewall Sat Cur (A/meter)
+   n_pi    = 1.007                       $ Ideality
+   cj_pi   = '(1.22m+0.16m*dpcj+dcjorbot_pfeti_fc)*(1-p5vonly) + cj_p5im*p5vonly'    $ P+ Diode Cap (F/meter**2)
+   pb_pi   = '0.787*(1-p5vonly) + pb_p5im*p5vonly'       $ Voltage dependence
+   mj_pi   = '0.405*(1-p5vonly) + mj_p5im*p5vonly'
+   cjsw_pi = '(90p+22.5p*dpcjsw+dcjorsti_pfeti_fc)*(1-p5vonly) + cjsw_p5im*p5vonly'  $ P+ STI Sidewall Cap (F/meter)
+   pbsw_pi = '0.99*(1-p5vonly) + pbsw_p5im*p5vonly'      $ Voltage dependence
+   mjsw_pi = '0.01*(1-p5vonly) + mjsw_p5im*p5vonly'
+   cjsg_pi = '312p + 78p*dpcjsg + dcjorgat_pfeti_fc'     $ P+ Gate Sidewall Cap (F/meter)
+   pbsg_pi = 1.0                         $ Voltage dependence
+   mjsg_pi = 0.573
+   cta_pi  = '0.9m*(1-p5vonly) + cta_p5im*p5vonly'       $ Cap temperature dependence
+   pta_pi  = '1.3m*(1-p5vonly) + pta_p5im*p5vonly'
+   ctp_pi  = '0*(1-p5vonly) + ctp_p5im*p5vonly'
+   ptp_pi  = '0*(1-p5vonly) + ptp_p5im*p5vonly'
*
*                                            NFETHVT
*
+   xnhvvth0  = agauss('-cnr_nhvt',1,3)    $ Distributions
+   dnhvvth0  = xnhvvth0
+   xnhvu0    = agauss(cnr_nhvt,1,3)
+   dnhvu0    = xnhvu0
+   xnhvfol   = agauss('cnr_nhvt',1,3)
+   dnhvfol   = xnhvfol
+   xnhvcj    = agauss('-cnr_nhvt',1,3)
+   dnhvcj    = xnhvcj
+   xnhvcjsw  = agauss('-cnr_nhvt',1,3)
+   dnhvcjsw  = xnhvcjsw
+   xnhvcjsg  = agauss('-cnr_nhvt',1,3)
+   dnhvcjsg  = xnhvcjsg
+   xnoinhv   = agauss('-cnr_lv_noin',1,3)
+   dnoinhv   = xnoinhv
*
+   tox_nhv   = '3.635n + 0.32n*distoxt*(1-fixcnrlv) + dtoxo_nfethvt_fc' $ Gate oxide thickness (meter)
+   vtol_nhv  = '0.015*dnhvvth0'
+   vfb_nhv   = '-1.043 + vtol_nhv + dvfbo_nfethvt_fc'           $ Base Threshold voltage (V)
+   vfbl_nhv  = '-9.3m + dvfbl_nfethvt_fc'
+   vfblw_nhv = '1.3m + dvfblw_nfethvt_fc'
+   ltol_nhv  = '-8.5n*distpc*(1-fixcnrlv)'
+   lint_nhv  = '0.0185u + ltol_nhv + dlap_nfethvt_fc'           $ Delta L (one side)
+   lov_nhv   = '36.6n + 3.3n*distncov - 1.5n*distpc + dlov_nfethvt_fc'
+   wtol_nhv  = '-0.05u*distrx*(1-fixcnrlv)'
+   wint_nhv  = '0.01u + wtol_nhv + dwot_nfethvt_fc'             $ Delta W (one side)
+   uo_nhv    = 'exp(-2.9565 + 0.12*dnhvu0) + duo_nfethvt_fc'    $ Base mobility (m**2/Vsec)
+   rsw_nhv   = '58.0 + 6.6*dnrdsw + drsw1_nfethvt_fc'           $ Base series resistance (ohm-um)
+   fol1_nhv  = '21.6m + 12m*dnhvfol + dfol1_nfethvt_fc'         $ First order short channel roll-off and body effect
+   fol2_nhv  = '20u + 5u*dnhvfol + dfol2_nfethvt_fc'            $ Second order short channel roll-off and body effect
+   thesatl_nhv = '0.7225 + dthesatl_nfethvt_fc'                 $ Saturation velocity
*
+   rsh_nhv  = 8                         $ S/D sheet resistance (ohms/sq)
+   js_nhv   = 100n                      $ N+ Area Sat Cur (A/meter**2)
+   jsw_nhv  = 50f                       $ N+ Sidewall Sat Cur (A/meter)
+   n_nhv    = 1.0                       $ Ideality
+   cj_nhv   = '1.35m + 0.20m*dnhvcj + dcjorbot_nfethvt_fc'  $ N+ Diode Cap (F/meter**2)
+   pb_nhv   = 0.711                     $ Voltage dependence
+   mj_nhv   = 0.46
+   cjsw_nhv = '180p + 45p*dnhvcjsw + dcjorsti_nfethvt_fc'   $ N+ STI Sidewall Cap (F/meter)
+   pbsw_nhv = 0.787                     $ Voltage dependence
+   mjsw_nhv = 0.430
+   cjsg_nhv = '420p + 105p*dnhvcjsg + dcjorgat_nfethvt_fc'  $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_nhv = 1.0                       $ Voltage dependence
+   mjsg_nhv = 0.4
+   cta_nhv  = 1.0m                      $ Cap temperature dependence
+   pta_nhv  = 0.7m
+   ctp_nhv  = 1.6m
+   ptp_nhv  = 0.3m
+   noideva_nhv = 1.8e-11                $ Area, 1/f statistics (meter*2)
+   noistd_nhv  = 2.0                    $ 3-sigma log noise distribution
*
*                                            NFETIHVT
*
+   tox_nhvi   = '3.635n + 0.34n*distoxt*(1-fixcnrlv) + dtoxo_nfetihvt_fc' $ Gate oxide thickness (meter)
+   vtol_nhvi  = '0.01*dnhvvth0'
+   vfb_nhvi   = '-1.025 + vtol_nhvi + dvfbo_nfetihvt_fc'          $ Base Threshold voltage (V)
+   vfbl_nhvi  = '-5.7m + dvfbl_nfetihvt_fc'
+   vfblw_nhvi = '1.995m + dvfblw_nfetihvt_fc'
+   lint_nhvi  = '0.0185u + ltol_nhv + dlap_nfetihvt_fc'           $ Delta L (one side)
+   lov_nhvi   = '36.6n + 3.3n*distncov - 1.0n*distpc + dlov_nfetihvt_fc'
+   wint_nhvi  = '0.01u + wtol_nhv + dwot_nfetihvt_fc'             $ Delta W (one side)
+   uo_nhvi    = 'exp(-2.9515 + 0.12*dnhvu0) + duo_nfetihvt_fc'    $ Base mobility (m**2/Vsec)
+   rsw_nhvi   = '60.75 + 6.6*dnrdsw + drsw1_nfetihvt_fc'          $ Base series resistance (ohm-um)
+   fol1_nhvi  = '21.6m + 12m*dnhvfol + dfol1_nfetihvt_fc'         $ First order short channel roll-off and body effect
+   fol2_nhvi  = '20u + 5u*dnhvfol + dfol2_nfetihvt_fc'            $ Second order short channel roll-off and body effect
+   thesatl_nhvi = '0.7565 + dthesatl_nfetihvt_fc'                 $ Saturation velocity
*
+   rsh_nhvi  = 8                         $ S/D sheet resistance (ohms/sq)
+   js_nhvi   = 100n                      $ N+ Area Sat Cur (A/meter**2)
+   jsw_nhvi  = 50f                       $ N+ Sidewall Sat Cur (A/meter)
+   n_nhvi    = 1.0                       $ Ideality
+   cj_nhvi   = '1.30m + 0.20m*dnhvcj + dcjorbot_nfetihvt_fc'    $ N+ Diode Cap (F/meter**2)
+   pb_nhvi   = 0.711                     $ Voltage dependence
+   mj_nhvi   = 0.46
+   cjsw_nhvi = '185p + 46.2p*dnhvcjsw + dcjorsti_nfetihvt_fc'   $ N+ STI Sidewall Cap (F/meter)
+   pbsw_nhvi = 0.787                     $ Voltage dependence
+   mjsw_nhvi = 0.43
+   cjsg_nhvi = '420p + 105p*dnhvcjsg + dcjorgat_nfetihvt_fc'    $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_nhvi = 1.0                       $ Voltage dependence
+   mjsg_nhvi = 0.4
+   cta_nhvi  = 1.0m                      $ Cap temperature dependence
+   pta_nhvi  = 0.7m
+   ctp_nhvi  = 1.6m
+   ptp_nhvi  = 0.3m
*
*                                            PFETHVT
*
+   xphvvth0 = agauss(cnr_phvt,1,3)      $ Distributions
+   dphvvth0 = xphvvth0
+   xphvu0   = agauss(cnr_phvt,1,3)
+   dphvu0   = xphvu0
+   xphvfol  = agauss('cnr_phvt',1,3)
+   dphvfol  = xphvfol
+   xphvvsat = agauss(cnr_phvt,1,3)
+   dphvvsat = xphvvsat
+   xphvcj   = agauss('-cnr_phvt',1,3)
+   dphvcj   = xphvcj
+   xphvcjsw = agauss('-cnr_phvt',1,3)
+   dphvcjsw = xphvcjsw
+   xphvcjsg = agauss('-cnr_phvt',1,3)
+   dphvcjsg = xphvcjsg
+   xnoiphv  = agauss('-cnr_lv_noip',1,3)
+   dnoiphv  = xnoiphv
*
+   tox_phv   = '3.95n + 0.32n*distoxt*(1-fixcnrlv) + dtoxo_pfethvt_fc' $ Gate oxide thickness (meter)
+   vtol_phv  = '0.0*dphvvth0'
+   vfb_phv   = '-1.412 + vtol_phv + dvfbo_pfethvt_fc'              $ Base Threshold voltage (V)
+   vfbl_phv  = '-11m + dvfbl_pfethvt_fc'
+   vfblw_phv = '10u + dvfblw_pfethvt_fc'
+   ltol_phv  = '-8.5n*distpc*(1-fixcnrlv)'
+   lint_phv  = '0.020u + ltol_phv + dlap_pfethvt_fc'               $ Delta L (one side)
+   lov_phv   = '41.9n + 3.98n*distpcov - 1.0n*distpc + dlov_pfethvt_fc'
+   wtol_phv  = '-0.051u*distrx*(1-fixcnrlv)'
+   wint_phv  = '0.010u + wtol_phv + dwot_pfethvt_fc'               $ Delta W (one side)
+   uo_phv    = '0.0248 + 0.002*dphvu0 + duo_pfethvt_fc'            $ Base mobility (m**2/Vsec)
+   rsw_phv   = '190 + 30*dprdsw + drsw1_pfethvt_fc'                $ Base series resistance (ohm-um)
+   fol1_phv  = '44.98m + 7m*dphvfol + dfol1_pfethvt_fc'            $ First order short channel roll-off and body effect
+   fol2_phv  = '1.186m + 0.3m*dphvfol + dfol2_pfethvt_fc'          $ Second order short channel roll-off and body effect
+   thesatl_phv = '0.150 + 0.0*dphvvsat + dthesatl_pfethvt_fc'      $ Saturation velocity
*
+   rsh_phv  = 8                           $ S/D sheet resistance (ohms/sq)
+   js_phv   = 85n                         $ P+ Area Sat Cur (A/meter**2)
+   jsw_phv  = 30f                         $ P+ Sidewall Sat Cur (A/meter)
+   n_phv    = 1.01                        $ Ideality
+   cj_phv   = '1.22m + 0.16m*dphvcj + dcjorbot_pfethvt_fc'    $ P+ Diode Cap (F/meter**2)
+   pb_phv   = 0.804                       $ Voltage dependence
+   mj_phv   = 0.419
+   cjsw_phv = '101.3p + 25.3p*dphvcjsw + dcjorsti_pfethvt_fc' $ P+ STI Sidewall Cap (F/meter)
+   pbsw_phv = 0.40                        $ Voltage dependence
+   mjsw_phv = 0.0263
+   cjsg_phv = '370p + 92.5p*dphvcjsg + dcjorgat_pfethvt_fc'   $ P+ Gate Sidewall Cap (F/meter)
+   pbsg_phv = 0.7992                      $ Voltage dependence
+   mjsg_phv = 0.3754
+   cta_phv  = 0.967m                      $ Cap temperature dependence
+   pta_phv  = 1.6m
+   ctp_phv  = 0.5m
+   ptp_phv  = 2m
+   noideva_phv = 1.8e-11                  $ Area, 1/f statistics (meter*2)
+   noistd_phv  = 2.2                      $ 3-sigma log noise distribution
*
*                                            PFETIHVT
*
+   tox_phvi   = '3.95n + 0.32n*distoxt*(1-fixcnrlv) + dtoxo_pfetihvt_fc' $ Gate oxide thickness (meter)
+   vtol_phvi  = '0.0*dphvvth0'
+   vfb_phvi   = '-1.421 + vtol_phvi + dvfbo_pfetihvt_fc'             $ Base Threshold voltage (V)
+   vfbl_phvi  = '-11.6m + dvfbl_pfetihvt_fc'
+   vfblw_phvi = '-66.0u + dvfblw_pfetihvt_fc'
+   lint_phvi  = '0.020u + ltol_phv + dlap_pfetihvt_fc'               $ Delta L (one side)
+   lov_phvi   = '41.9n + 3.88n*distpcov - 1.0n*distpc + dlov_pfetihvt_fc'
+   wint_phvi  = '0.010u + wtol_phv + dwot_pfetihvt_fc'               $ Delta W (one side)
+   uo_phvi    = '0.0255 + 0.002*dphvu0 + duo_pfetihvt_fc'            $ Base mobility (m**2/Vsec)
+   rsw_phvi   = '158.5 + 30*dprdsw + drsw1_pfetihvt_fc'              $ Base series resistance (ohm-um)
+   fol1_phvi  = '45.5m + 7m*dphvfol + dfol1_pfetihvt_fc'             $ First order short channel roll-off and body effect
+   fol2_phvi  = '1.25m + 0.3m*dphvfol + dfol2_pfetihvt_fc'           $ Second order short channel roll-off and body effect
+   thesatl_phvi = '0.119 + 0.0*dphvvsat + dthesatl_pfetihvt_fc'      $ Saturation velocity
*
+   rsh_phvi  = 8                           $ S/D sheet resistance (ohms/sq)
+   js_phvi   = 85n                         $ P+ Area Sat Cur (A/meter**2)
+   jsw_phvi  = 30f                         $ P+ Sidewall Sat Cur (A/meter)
+   n_phvi    = 1.01                        $ Ideality
+   cj_phvi   = '1.32m + 0.16m*dphvcj + dcjorbot_pfetihvt_fc'     $ P+ Diode Cap (F/meter**2)
+   pb_phvi   = 0.804                       $ Voltage dependence
+   mj_phvi   = 0.419
+   cjsw_phvi = '94.15p + 23.5p*dphvcjsw + dcjorsti_pfetihvt_fc'  $ P+ STI Sidewall Cap (F/meter)
+   pbsw_phvi = 0.30                        $ Voltage dependence
+   mjsw_phvi = 0.02
+   cjsg_phvi = '430.0p + 107.5p*dphvcjsg + dcjorgat_pfetihvt_fc' $ P+ Gate Sidewall Cap (F/meter)
+   pbsg_phvi = 0.90                        $ Voltage dependence
+   mjsg_phvi = 0.375
+   cta_phvi  = 0.967m                      $ Cap temperature dependence
+   pta_phvi  = 1.456m
+   ctp_phvi  = 1.0m
+   ptp_phvi  = 0
*
*                                            NFETSHVT
*
+   xnshvvth0  = agauss('-cnr_nshvt',1,3)  $ Distributions
+   dnshvvth0  = xnshvvth0
+   xnshvu0    = agauss(cnr_nshvt,1,3)
+   dnshvu0    = xnshvu0
+   xnshvfol   = agauss('cnr_nshvt',1,3)
+   dnshvfol   = xnshvfol
+   xnshvcj    = agauss('-cnr_nshvt',1,3)
+   dnshvcj    = xnshvcj
+   xnshvcjsw  = agauss('-cnr_nshvt',1,3)
+   dnshvcjsw  = xnshvcjsw
+   xnshvcjsg  = agauss('-cnr_nshvt',1,3)
+   dnshvcjsg  = xnshvcjsg
+   xnoinshv   = agauss('-cnr_lv_noin',1,3)
+   dnoinshv   = xnoinshv
*
+   tox_nshv   = '3.61n + 0.32n*distoxt*(1-fixcnrlv) + dtoxo_nfetshvt_fc' $ Gate oxide thickness (meter)
+   vtol_nshv  = '0.033*dnshvvth0'
+   vfb_nshv   = '-1.009 + vtol_nshv + dvfbo_nfetshvt_fc'         $ Base Threshold voltage (V)
+   vfbl_nshv  = '19.62m + dvfbl_nfetshvt_fc'
+   vfblw_nshv = '5.5m + dvfblw_nfetshvt_fc'
+   ltol_nshv  = '-8.5n*distpc*(1-fixcnrlv)'
+   lint_nshv  = '0.015u + ltol_nshv + dlap_nfetshvt_fc'          $ Delta L (one side)
+   lov_nshv   = '31.7n + 3.3n*distncov - 1.5n*distpc + dlov_nfetshvt_fc'
+   wtol_nshv  = '-0.05u*distrx*(1-fixcnrlv)'
+   wint_nshv  = '0.01u + wtol_nshv + dwot_nfetshvt_fc'           $ Delta W (one side)
+   uo_nshv    = '0.078 + 0.010*dnshvu0 + duo_nfetshvt_fc'        $ Base mobility (m**2/Vsec)
+   rsw_nshv   = '95.0 + 6.5*dnrdsw + drsw1_nfetshvt_fc'          $ Base series resistance (ohm-um)
+   fol1_nshv  = '73.9m + 5.3m*dnshvfol + dfol1_nfetshvt_fc'      $ First order short channel roll-off and body effect
+   fol2_nshv  = '5.28m + 5u*dnshvfol + dfol2_nfetshvt_fc'        $ Second order short channel roll-off and body effect
+   thesatl_nshv = '0.438 + dthesatl_nfetshvt_fc'                 $ Saturation velocity
*
+   rsh_nshv  = 8                         $ S/D sheet resistance (ohms/sq)
+   js_nshv   = 100n                      $ N+ Area Sat Cur (A/meter**2)
+   jsw_nshv  = 50f                       $ N+ Sidewall Sat Cur (A/meter)
+   n_nshv    = 1.0                       $ Ideality
+   cj_nshv   = '1.24m + 0.20m*dnshvcj + dcjorbot_nfetshvt_fc'    $ N+ Diode Cap (F/meter**2)
+   pb_nshv   = 0.700                     $ Voltage dependence
+   mj_nshv   = 0.450
+   cjsw_nshv = '190.4p + 47.5p*dnshvcjsw + dcjorsti_nfetshvt_fc' $ N+ STI Sidewall Cap (F/meter)
+   pbsw_nshv = 0.700                     $ Voltage dependence
+   mjsw_nshv = 0.436
+   cjsg_nshv = '208.1p + 52p*dnshvcjsg + dcjorgat_nfetshvt_fc'   $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_nshv = 0.628                     $ Voltage dependence
+   mjsg_nshv = 0.224
+   cta_nshv  = 1.0m                      $ Cap temperature dependence
+   pta_nshv  = 0.7m
+   ctp_nshv  = 0.5m
+   ptp_nshv  = 0.3m
+   noideva_nshv = 1.8e-11                $ Area, 1/f statistics (meter*2)
+   noistd_nshv  = 2.5                    $ 3-sigma log noise distribution
*
*                                            PFETSHVT
*
+   xpshvvth0 = agauss(cnr_pshvt,1,3)      $ Distributions
+   dpshvvth0 = xpshvvth0
+   xpshvu0   = agauss(cnr_pshvt,1,3)
+   dpshvu0   = xpshvu0
+   xpshvfol  = agauss('cnr_pshvt',1,3)
+   dpshvfol  = xpshvfol
+   xpshvvsat = agauss(cnr_pshvt,1,3)
+   dpshvvsat = xpshvvsat
+   xpshvcj   = agauss('-cnr_pshvt',1,3)
+   dpshvcj   = xpshvcj
+   xpshvcjsw = agauss('-cnr_pshvt',1,3)
+   dpshvcjsw = xpshvcjsw
+   xpshvcjsg = agauss('-cnr_pshvt',1,3)
+   dpshvcjsg = xpshvcjsg
+   xnoipshv  = agauss('-cnr_lv_noip',1,3)
+   dnoipshv  = xnoipshv
*
+   tox_pshv   = '3.668n + 0.32n*distoxt*(1-fixcnrlv) + dtoxo_pfetshvt_fc' $ Gate oxide thickness (meter)
+   vtol_pshv  = '0.0409*dpshvvth0'
+   vfb_pshv   = '-0.9553 + vtol_pshv + dvfbo_pfetshvt_fc'       $ Base Threshold voltage (V)
+   vfbl_pshv  = '-13.3m + dvfbl_pfetshvt_fc'
+   vfblw_pshv = '69.18u + dvfblw_pfetshvt_fc'
+   ltol_pshv  = '-8.5n*distpc*(1-fixcnrlv)'
+   lint_pshv  = '0.020u + ltol_pshv + dlap_pfetshvt_fc'         $ Delta L (one side)
+   lov_pshv   = '36.68n + 3.45n*distpcov - 0.8n*distpc + dlov_pfetshvt_fc'
+   wtol_pshv  = '-0.050u*distrx*(1-fixcnrlv)'
+   wint_pshv  = '0.010u + wtol_pshv + dwot_pfetshvt_fc'         $ Delta W (one side)
+   uo_pshv    = '0.02739 + 0.00535*dpshvu0 + duo_pfetshvt_fc'   $ Base mobility (m**2/Vsec)
+   rsw_pshv   = '401.3 + 16.5*dprdsw + drsw1_pfetshvt_fc'       $ Base series resistance (ohm-um)
+   fol1_pshv  = '5.012m + 3.0m*dpshvfol + dfol1_pfetshvt_fc'    $ First order short channel roll-off and body effect
+   fol2_pshv  = '-3.094m + 3.42m*dpshvfol + dfol2_pfetshvt_fc'  $ Second order short channel roll-off and body effect
+   thesatl_pshv = '2.0 + 0.0*dpshvvsat + dthesatl_pfetshvt_fc'  $ Saturation velocity
*
+   rsh_pshv  = 8                         $ S/D sheet resistance (ohms/sq)
+   js_pshv   = 105n                      $ P+ Area Sat Cur (A/meter**2)
+   jsw_pshv  = 95f                       $ P+ Sidewall Sat Cur (A/meter)
+   n_pshv    = 0.99                      $ Ideality
+   cj_pshv   = '1.37m + 0.16m*dpshvcj + dcjorbot_pfetshvt_fc'  $ P+ Diode Cap (F/meter**2)
+   pb_pshv   = 0.830                     $ Voltage dependence
+   mj_pshv   = 0.458
+   cjsw_pshv = '70p + 17.5p*dpshvcjsw + dcjorsti_pfetshvt_fc'  $ P+ STI Sidewall Cap (F/meter)
+   pbsw_pshv = 1.00                      $ Voltage dependence
+   mjsw_pshv = 0.01
+   cjsg_pshv = '315p + 78.8p*dpshvcjsg + dcjorgat_pfetshvt_fc' $ P+ Gate Sidewall Cap (F/meter)
+   pbsg_pshv = 0.792                     $ Voltage dependence
+   mjsg_pshv = 0.330
+   cta_pshv  = 0.777m                    $ Cap temperature dependence
+   pta_pshv  = 1.6m
+   ctp_pshv  = 0.005m
+   ptp_pshv  = 2m
+   noideva_pshv = 1.8e-11                 $ Area, 1/f statistics (meter*2)
+   noistd_pshv  = 4.2                     $ 3-sigma log noise distribution
*
*                                            NFETM
*
+   xn5mvth0  = agauss('-cnr_nf5m',1,3)    $ Distributions
+   dn5mvth0  = xn5mvth0
+   xn5mu0    = agauss(cnr_nf5m,1,3)
+   dn5mu0    = xn5mu0
+   xn5mfol   = agauss('cnr_nf5m',1,3)
+   dn5mfol   = xn5mfol
+   xn5mcj    = agauss('-cnr_nf5m',1,3)
+   dn5mcj    = xn5mcj
+   xn5mcjsw  = agauss('-cnr_nf5m',1,3)
+   dn5mcjsw  = xn5mcjsw
+   xn5mcjsg  = agauss('-cnr_nf5m',1,3)
+   dn5mcjsg  = xn5mcjsg
+   xnoin5m   = agauss('-cnr_lv_noin',1,3)
+   dnoin5m   = xnoin5m
*
+   tox_n5m   = '11.2n + 0.83n*distoxm*(1-fixcnrlv) + dtoxo_nfetm_fc' $ Gate oxide thickness (meter)
+   vtol_n5m  = '0.022*dn5mvth0'
+   vfb_n5m   = '-0.960 + vtol_n5m + dvfbo_nfetm_fc'             $ Base Threshold voltage (V)
+   vfbl_n5m  = '-3m + dvfbl_nfetm_fc'
+   vfblw_n5m = '-16.98m + dvfblw_nfetm_fc'
+   ltol_n5m  = '-0.025u*distpc*(1-fixcnrlv)'
+   lint_n5m  = '0.115u + ltol_n5m + dlap_nfetm_fc'              $ Delta L (one side)
+   lov_n5m   = '211n + 13.2n*distncov - 1.5n*distpc + dlov_nfetm_fc'
+   wtol_n5m  = '-0.05u*distrx*(1-fixcnrlv)'
+   wint_n5m  = '0.025u + wtol_n5m + dwot_nfetm_fc'              $ Delta W (one side)
+   uo_n5m    = '49.7m + 2.1m*dn5mu0 + duo_nfetm_fc'             $ Base mobility (m**2/Vsec)
+   rsw_n5m   = '328 + 32*dnrdsw + drsw1_nfetm_fc'               $ Base series resistance (ohm-um)
+   fol1_n5m  = '121m + 26m*dn5mfol + dfol1_nfetm_fc'            $ First order short channel roll-off and body effect
+   fol2_n5m  = '60m + 0.5m*dn5mfol + dfol2_nfetm_fc'            $ Second order short channel roll-off and body effect
+   thesatl_n5m = '553.2m + dthesatl_nfetm_fc'                   $ Saturation velocity
*
+   rsh_n5m  = 8                         $ S/D sheet resistance (ohms/sq)
+   js_n5m   = 161.1n                    $ N+ Area Sat Cur (A/meter**2)
+   jsw_n5m  = 59f                       $ N+ Sidewall Sat Cur (A/meter)
+   n_n5m    = 1.048                     $ Ideality
+   cj_n5m   = '0.670m + 0.13m*dn5mcj + dcjorbot_nfetm_fc'   $ N+ Diode Cap (F/meter**2)
+   pb_n5m   = 0.440                     $ Voltage dependence
+   mj_n5m   = 0.232
+   cjsw_n5m = '80.68p + 20.2p*dn5mcjsw + dcjorsti_nfetm_fc' $ N+ STI Sidewall Cap (F/meter)
+   pbsw_n5m = 1.0                       $ Voltage dependence
+   mjsw_n5m = 0.05
+   cjsg_n5m = '215.6p + 53.9p*dn5mcjsg + dcjorgat_nfetm_fc' $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_n5m = 0.720                     $ Voltage dependence
+   mjsg_n5m = 0.480
+   cta_n5m  = 829.1u                    $ Cap temperature dependence
+   pta_n5m  = 1.266m
+   ctp_n5m  = 613.8u
+   ptp_n5m  = 2m
+   noideva_n5m = 1.8e-11                $ Area, 1/f statistics (meter*2)
+   noistd_n5m  = 1.8                    $ 3-sigma log noise distribution
*
*                                            NFETIM
*
+   tox_n5im   = '11.2n + 0.83n*distoxm*(1-fixcnrlv) + dtoxo_nfetim_fc' $ Gate oxide thickness (meter)
+   vtol_n5im  = '0.022*dn5mvth0'
+   vfb_n5im   = '-0.950 + vtol_n5im + dvfbo_nfetim_fc'            $ Base Threshold voltage (V)
+   vfbl_n5im  = '6m + dvfbl_nfetim_fc'
+   vfblw_n5im = '-16.98m + dvfblw_nfetim_fc'
+   lint_n5im  = '0.115u + ltol_n5m + dlap_nfetim_fc'              $ Delta L (one side)
+   lov_n5im   = '211n + 13.2n*distncov - 1.5n*distpc + dlov_nfetim_fc'
+   wint_n5im  = '0.025u + wtol_n5m + dwot_nfetim_fc'              $ Delta W (one side)
+   uo_n5im    = '49.7m + 2.1m*dn5mu0 + duo_nfetim_fc'             $ Base mobility (m**2/Vsec)
+   rsw_n5im   = '305 + 32*dnrdsw + drsw1_nfetim_fc'               $ Base series resistance (ohm-um)
+   fol1_n5im  = '120m + 26m*dn5mfol + dfol1_nfetim_fc'            $ First order short channel roll-off and body effect
+   fol2_n5im  = '52m + 0.5m*dn5mfol + dfol2_nfetim_fc'            $ Second order short channel roll-off and body effect
+   thesatl_n5im = '560m + dthesatl_nfetim_fc'                     $ Saturation velocity
*
+   rsh_n5im  = 8                         $ S/D sheet resistance (ohms/sq)
+   js_n5im   = 161.1n                    $ N+ Area Sat Cur (A/meter**2)
+   jsw_n5im  = 59f                       $ N+ Sidewall Sat Cur (A/meter)
+   n_n5im    = 1.048                     $ Ideality
+   cj_n5im   = '0.770m + 0.15m*dn5mcj + dcjorbot_nfetim_fc'   $ N+ Diode Cap (F/meter**2)
+   pb_n5im   = 0.483                     $ Voltage dependence
+   mj_n5im   = 0.217
+   cjsw_n5im = '60p + 15p*dn5mcjsw + dcjorsti_nfetim_fc'   $ N+ STI Sidewall Cap (F/meter)
+   pbsw_n5im = 1.0                       $ Voltage dependence
+   mjsw_n5im = 0.05
+   cjsg_n5im = '190.6p + 47.6p*dn5mcjsg + dcjorgat_nfetim_fc' $ N+ Gate Sidewall Cap (F/meter)
+   pbsg_n5im = 0.5092                    $ Voltage dependence
+   mjsg_n5im = 0.3816
+   cta_n5im  = 600u                      $ Cap temperature dependence
+   pta_n5im  = 1m
+   ctp_n5im  = 900u
+   ptp_n5im  = 2.2m
*
*                                            PFETM
*
+   xp5mvth0 = agauss(cnr_pf5m,1,3)      $ Distributions
+   dp5mvth0 = xp5mvth0
+   xp5mu0   = agauss(cnr_pf5m,1,3)
+   dp5mu0   = xp5mu0
+   xp5mfol  = agauss('cnr_pf5m',1,3)
+   dp5mfol  = xp5mfol
+   xp5mvsat = agauss(cnr_pf5m,1,3)
+   dp5mvsat = xp5mvsat
+   xp5mcj   = agauss('-cnr_pf5m',1,3)
+   dp5mcj   = xp5mcj
+   xp5mcjsw = agauss('-cnr_pf5m',1,3)
+   dp5mcjsw = xp5mcjsw
+   xp5mcjsg = agauss('-cnr_pf5m',1,3)
+   dp5mcjsg = xp5mcjsg
+   xnoip5m  = agauss('-cnr_lv_noip',1,3)
+   dnoip5m  = xnoip5m
*
+   tox_p5m   = '11.15n + 0.8n*distoxm*(1-fixcnrlv) + dtoxo_pfetm_fc' $ Gate oxide thickness (meter)
+   vtol_p5m  = '-0.03908*dp5mvth0'
+   vfb_p5m   = '-1.0275 + vtol_p5m + dvfbo_pfetm_fc'               $ Base Threshold voltage (V)
+   vfbl_p5m  = '-49.65m + dvfbl_pfetm_fc'
+   vfblw_p5m = '19.19m + dvfblw_pfetm_fc'
+   ltol_p5m  = '-0.025u*distpc*(1-fixcnrlv)'
+   lint_p5m  = '0.0775u + ltol_p5m + dlap_pfetm_fc'                $ Delta L (one side)
+   lov_p5m   = '149.5n + 16.5n*distpcov - 4.0n*distpc + dlov_pfetm_fc'
+   wtol_p5m  = '-0.05u*distrx*(1-fixcnrlv)'
+   wint_p5m  = '0.045u + wtol_p5m + dwot_pfetm_fc'                 $ Delta W (one side)
+   uo_p5m    = '18.0m + 0.9561m*dp5mu0 + duo_pfetm_fc'             $ Base mobility (m**2/Vsec)
+   rsw_p5m   = '878.5 + 225*dprdsw + drsw1_pfetm_fc'               $ Base series resistance (ohm-um)
+   fol1_p5m  = '105.1m + 15.5m*dp5mfol + dfol1_pfetm_fc'           $ First order short channel roll-off and body effect
+   fol2_p5m  = '21.72m + 1.1m*dp5mfol + dfol2_pfetm_fc'            $ Second order short channel roll-off and body effect
+   thesatl_p5m = '545.7m + 0.96m*dp5mvsat + dthesatl_pfetm_fc'     $ Saturation velocity
*
+   rsh_p5m  = 8                           $ S/D sheet resistance (ohms/sq)
+   js_p5m   = 892.4p                      $ P+ Area Sat Cur (A/meter**2)
+   jsw_p5m  = 14f                         $ P+ Sidewall Sat Cur (A/meter)
+   n_p5m    = 1.02                        $ Ideality
+   cj_p5m   = '0.90m + 0.14m*dp5mcj + dcjorbot_pfetm_fc'    $ P+ Diode Cap (F/meter**2)
+   pb_p5m   = 0.7471                      $ Voltage dependence
+   mj_p5m   = 0.3496
+   cjsw_p5m = '80.46p + 20.1p*dp5mcjsw + dcjorsti_pfetm_fc' $ P+ STI Sidewall Cap (F/meter)
+   pbsw_p5m = 0.3345                      $ Voltage dependence
+   mjsw_p5m = 0.05513
+   cjsg_p5m = '167.1p + 41.8p*dp5mcjsg + dcjorgat_pfetm_fc' $ P+ Gate Sidewall Cap (F/meter)
+   pbsg_p5m = 0.5833                      $ Voltage dependence
+   mjsg_p5m = 0.3533
+   cta_p5m  = 710.9u                      $ Cap temperature dependence
+   pta_p5m  = 0.5m
+   ctp_p5m  = 793u
+   ptp_p5m  = 1m
+   noideva_p5m = 1.8e-11                  $ Area, 1/f statistics (meter*2)
+   noistd_p5m  = 2.5                      $ 3-sigma log noise distribution
*
*                                            PFETIM
*
+   tox_p5im   = '11.45n + 0.8n*distoxm*(1-fixcnrlv) + dtoxo_pfetim_fc' $ Gate oxide thickness (meter)
+   vtol_p5im  = '-0.03908*dp5mvth0'
+   vfb_p5im   = '-1.011 + vtol_p5im + dvfbo_pfetim_fc'               $ Base Threshold voltage (V)
+   vfbl_p5im  = '0.19m + dvfbl_pfetim_fc'
+   vfblw_p5im = '1.802m + dvfblw_pfetim_fc'
+   lint_p5im  = '0.0775u + ltol_p5m + dlap_pfetim_fc'                $ Delta L (one side)
+   lov_p5im   = '157.8n + 17.3n*distpcov - 4.0n*distpc + dlov_pfetim_fc'
+   wint_p5im  = '0.045u + wtol_p5m + dwot_pfetim_fc'                 $ Delta W (one side)
+   uo_p5im    = '19.0m + 1.5561m*dp5mu0 + duo_pfetim_fc'             $ Base mobility (m**2/Vsec)
+   rsw_p5im   = '840.7 + 160*dprdsw + drsw1_pfetim_fc'               $ Base series resistance (ohm-um)
+   fol1_p5im  = '111.1m + 25.5m*dp5mfol + dfol1_pfetim_fc'           $ First order short channel roll-off and body effect
+   fol2_p5im  = '24.19m + 1.5m*dp5mfol + dfol2_pfetim_fc'            $ Second order short channel roll-off and body effect
+   thesatl_p5im = '437.05m + 5.96m*dp5mvsat + dthesatl_pfetim_fc'    $ Saturation velocity
*
+   rsh_p5im  = 8                           $ S/D sheet resistance (ohms/sq)
+   js_p5im   = 892.4p                      $ P+ Area Sat Cur (A/meter**2)
+   jsw_p5im  = 18f                         $ P+ Sidewall Sat Cur (A/meter)
+   n_p5im    = 1.018                       $ Ideality
+   cj_p5im   = '0.70m + 0.11m*dp5mcj + dcjorbot_pfetim_fc'    $ P+ Diode Cap (F/meter**2)
+   pb_p5im   = 0.7808                      $ Voltage dependence
+   mj_p5im   = 0.3755
+   cjsw_p5im = '117.2p + 29.3p*dp5mcjsw + dcjorsti_pfetim_fc' $ P+ STI Sidewall Cap (F/meter)
+   pbsw_p5im = 0.2951                      $ Voltage dependence
+   mjsw_p5im = 0.03844
+   cjsg_p5im = '187.4p + 46.9p*dp5mcjsg + dcjorgat_pfetim_fc' $ P+ Gate Sidewall Cap (F/meter)
+   pbsg_p5im = 0.6079                      $ Voltage dependence
+   mjsg_p5im = 0.3618
+   cta_p5im  = 999u                        $ Cap temperature dependence
+   pta_p5im  = 2m
+   ctp_p5im  = 184.7u
+   ptp_p5im  = 0.1m
*
*                                              Nwell to Substrate Diode
*
+   xnwcj      = agauss(0,1,3)               $ Distributions
+   dnwcj      = xnwcj
+   xnwcjsw    = agauss(0,1,3)
+   dnwcjsw    = xnwcjsw
+   xnwjs      = agauss(0,1,3)
+   dnwjs      = xnwjs
+   xnwrs      = agauss(cnr_res,1,3)
+   dnwrs      = xnwrs
*
+   js_nw      = 1.8u                        $ Sat Current (A/meter**2)
+   jsw_nw     = 1.8p                        $ Sidewall Sat Current (A/meter)
+   n_nw       = 1.04                        $ Ideality
+   cj_nw      = '0.135m + 0.034m*dnwcj'     $ Capacitance (F/meter**2)
+   pb_nw      = 0.69                        $ Voltage dependence
+   mj_nw      = 0.52
+   cjsw_nw    = '0.930n + 0.233n*dnwcjsw'   $ Sidewall Cap (F/meter)
+   pbsw_nw    = 0.54                        $ Voltage dependence
+   mjsw_nw    = 0.30
+   cta_nw     = 3.8m                        $ Cap temperature dependence
+   pta_nw     = 3.3m
+   ctp_nw     = 1.7m
+   ptp_nw     = 2.1m
*
+   nwrs       = '(420-60*p5vonly)*(1+0.30*dnwrs)'  $ NW Sheet Rho (ohm/sq)
*
*                                              1.8V PCDCAP / MOSVAR
*
+   xnrnw      = agauss('-cnr_cap',1,3)      $ Distributions
+   dnrnw      = xnrnw
+   nrnw       = '(310p-10p*p5vonly)*(1+0.25*dnrnw)'  $ Vertical NWell (ohm-meter**2)
*
+   nco_mv     = 8.81m
+   co_mv      = 'nco_mv - 0.97m*distoxt'    $ Unit capacitance (F/meter**2)
+   nqs_mv     = 579u
+   qs_mv      = 'nqs_mv - 65u*dnwrs'        $ NWell depletion region charge
+   qp_mv      = '7.7m - 1.8m*dnpcrs'        $ Gate depletion charge
+   pon_mv     = 1m                          $ Hole-to-Electron density ratio
*
*                                              5V MOSVAR
*
+   nco_tmv    = 2.91m
+   co_tmv     = 'nco_tmv - 0.31m*distoxm'   $ Unit capacitance (F/meter**2)
+   nqs_tmv    = 349u
+   qs_tmv     = 'nqs_tmv - 46u*dnwrs'       $ NWell depletion region charge
+   qp_tmv     = '7.4m - 2.0m*dnpcrs'        $ Gate depletion charge
*
*                                              1.8V PFET in PWell Capacitor
*
+   xpwirs     = agauss(cnr_res,1,3)         $ Distributions
+   dpwirs     = xpwirs
+   pwirs      = '(385-10*p5vonly)*(1+0.35*dpwirs)'     $ IsoPWell Sheet Rho (ohm/sq)
*
+   prvpw      = '(1.0n+0.8n*p5vonly)*(1+0.25*dpwirs)'  $ Vertical IsoPWell (ohm-meter**2)
*
+   nco_pmv    = 8.56m
+   co_pmv     = 'nco_pmv - 0.95m*distoxt'   $ Unit capacitance (F/meter**2)
+   nqs_pmv    = 485u
+   qs_pmv     = 'nqs_pmv - 65u*dpwirs'      $ PWell depletion region charge
+   qp_pmv     = '8m - 1.25m*dpcrs'          $ Gate depletion charge
*
*                                              5V PFET in PWell Capacitor
*
+   nco_tpmv   = 2.89m
+   co_tpmv    = 'nco_tpmv - 0.32m*distoxm'  $ Unit capacitance (F/meter**2)
+   nqs_tpmv   = 345u
+   qs_tpmv    = 'nqs_tpmv - 46u*dpwirs'     $ PWell depletion region charge
+   qp_tpmv    = '8m - 1.25m*dpcrs'          $ Gate depletion charge
*
*                                              BEOL Area Cap (F/meter**2)
*
+   xpcap      = agauss(0,1,3)               $ Distribution
+   dpcap      = xpcap
+   tpcap      = '1.0 + 0.20*dpcap'          $ Extracted wiring cap tolerance
*
*                                              N-Type Schottky Barrier Diode
*
+   xsbdphib   = agauss('-cnr_dio',1,3)      $ Distributions
+   dsbdphib   = xsbdphib
+   xsbdcj     = agauss('-cnr_dio',1,3)
+   dsbdcj     = xsbdcj
*
+   ndelbn     = -0.52u                      $ photo + outdiffusion
+   delbn      = 'ndelbn - 0.10u*ddlbn'
*
+   sbdphib    = '0.646 + 0.065*dsbdphib'    $ Barrier height
*
+   nvepi      = '4.60n + 2.30n*dsbdphib'    $ Ver EPI res (ohms-meter**2)
+   nvepigr    = 46.0p                       $ Ver res under gr (ohms-meter**2)
*
+   nnsbdcj    = 0.613m                      $ SBD Cj area (F/meter**2)
+   nsbdcj     = 'nnsbdcj + 0.125m*dsbdcj'
*
+   nnsbdcjp   = 0.398n                      $ SBD Cj peri (F/meter)
+   nsbdcjp    = 'nnsbdcjp + 0.08n*dsbdcj'
*
+   sbdlk      = 'exp(25.389-3.75*dsbdphib)' $ Reverse Leakage Current
*
*                                              P-Type Schottky Barrier Diode
*
+   xpsbdphib  = agauss('-cnr_dio',1,3)      $ Distributions
+   dpsbdphib  = xpsbdphib
+   xpsbdcj    = agauss('-cnr_dio',1,3)
+   dpsbdcj    = xpsbdcj
*
+   ndelbnp    = -0.20u                      $ photo + outdiffusion
+   delbnp     = 'ndelbnp - 0.04u*ddlbn'
*
+   psbdphib   = '0.408 + 0.022*dpsbdphib'   $ Barrier height
*
+   pvepi      = '1.0n + 0.6n*dpsbdphib'     $ Ver EPI res (ohms-meter**2)
*
+   npsbdcj    = 2.5m                        $ SBD Cj area (F/meter**2)
+   psbdcj     = 'npsbdcj + 0.75m*dpsbdcj'
*
+   npsbdcjp   = 0.31n                       $ SBD Cj peri (F/meter)
+   psbdcjp    = 'npsbdcjp + 0.125n*dpsbdcj'
*
+   psbdlka    = '4.33e11*exp(0.875*(-dpsbdphib))' $ Reverse Leakage Current
+   psbdlkp    = '3.0e5*exp(0.875*(-dpsbdphib))'
*
+   psbdvb     = 4.0                         $ Breakdown Voltage
*
*                                              Single / Dual MIM Capacitors
*
+   xcmimqa    = agauss(cnr_cap,1,3)         $ Capacitance distributions
+   dcmimqa    = xcmimqa
+   xcmimha    = agauss(cnr_cap,1,3)
+   dcmimha    = xcmimha
+   xcmimp     = agauss(cnr_cap,1,3)
+   dcmimp     = xcmimp
+   xcdlmimp   = agauss(cnr_cap,1,3)
+   dcdlmimp   = xcdlmimp
+   xistmq     = agauss(cnr_cap,1,3)         $ Image distributions
+   distmq     = xistmq
+   xistmh     = agauss(cnr_cap,1,3)
+   distmh     = xistmh
+   xftrs      = agauss('-cnr_cap',1,3)
+   dftrs      = xftrs
+   xqtt       = agauss(cnr_cap,1,3)
+   dqtt       = xqtt
+   xhtt       = agauss(cnr_cap,1,3)
+   dhtt       = xhtt
*
+   ncmimqa    =  2.05m                      $ MIM Qx Cap area (F/meter**2)
+   cmimqa     = 'ncmimqa + 0.205m*dcmimqa'
+   ncmimha    =  2.05m                      $ MIM Hx Cap area (F/meter**2)
+   cmimha     = 'ncmimha + 0.205m*dcmimha'
+   ncmimp     =  0.12n                      $ Single MIM Cap peri (F/meter)
+   cmimp      = 'ncmimp + 0.06n*dcmimp'
+   ncdlmimp   =  0.44n                      $ Dual MIM Cap peri (F/meter)
+   cdlmimp    = 'ncdlmimp + 0.22n*dcdlmimp'
*
+   ndelmq     = -0.23u                      $ Q level Image
+   delmq      = 'ndelmq + 0.40u*distmq'
+   ndelmh     = -0.23u                      $ H level Image
+   delmh      = 'ndelmh + 0.30u*distmh'
*
+   prvft      = '-0.60 + exp(0.223*dftrs)'  $ FT Via Resistance (ohm/via)
*
+   qtt        = '0.242u + 0.0202u*dqtt'     $ QT Thickness
+   htt        = '0.242u + 0.0202u*dhtt'     $ HT Thickness
*
+   qtrs       = '0.17 - 0.034*dqtt'         $ QT Plate Res (ohm/sq)
*
*                                              Thinner Nitride (HD) MIM Caps
*
+   nhdmimqa   =  2.70m                      $ MIM Qx Cap area (F/meter**2)
+   hdmimqa    = 'nhdmimqa + 0.405m*dcmimqa'
+   nhdmimha   =  2.70m                      $ MIM Hx Cap area (F/meter**2)
+   hdmimha    = 'nhdmimha + 0.405m*dcmimha'
+   nhdmimp    =  0.2975n                    $ Single MIM Cap peri (F/meter)
+   hdmimp     = 'nhdmimp + 0.14875n*dcmimp'
+   nhddmimp   =  0.425n                     $ Dual MIM Cap peri (F/meter)
+   hddmimp    = 'nhddmimp + 0.2125n*dcdlmimp'
*
*                                              BEOL Devices
*
+   xistm1  = agauss(cnr_ind,1,3)            $ Image distributions
+   distm1  = xistm1
+   xistm2  = agauss(cnr_ind,1,3)
+   distm2  = xistm2
+   xistm3  = agauss(cnr_ind,1,3)
+   distm3  = xistm3
+   xistm4  = agauss(cnr_ind,1,3)
+   distm4  = xistm4
+   xistm5  = agauss(cnr_ind,1,3)
+   distm5  = xistm5
+   xistmt  = agauss(cnr_ind,1,3)
+   distmt  = xistmt
+   xistam  = agauss(cnr_ind,1,3)
+   distam  = xistam
*
+   delm1   = '0.006u + 0.045u*distm1'       $ M1 mask bias, M1<0.5um
+   delm1i  = '0.01u + 0.07u*distm1'         $ M1 mask bias, M1>=0.5um
+   delm2   = '-0.0316u + 0.07u*distm2'      $ M2 mask bias
+   delm3   = '-0.0316u + 0.07u*distm3'      $ M3 mask bias
+   delm4   = '-0.0316u + 0.07u*distm4'      $ M4 mask bias
+   delm5   = '-0.0316u + 0.07u*distm5'      $ M5 mask bias
+   delmt   = '-0.0316u + 0.07u*distmt'      $ MT mask bias
+   delam   = '-0.1116u + 0.60u*distam'      $ AM mask bias
*
+   xpmsxt  = agauss(0,1,3)                  $ Profile distributions
+   dpmsxt  = xpmsxt
+   xcapct  = agauss(cnr_ind,1,3)
+   dcapct  = xcapct
+   xm1t    = agauss(cnr_ind,1,3)
+   dm1t    = xm1t
+   xm2t    = agauss(cnr_ind,1,3)
+   dm2t    = xm2t
+   xm3t    = agauss(cnr_ind,1,3)
+   dm3t    = xm3t
+   xm4t    = agauss(cnr_ind,1,3)
+   dm4t    = xm4t
+   xm5t    = agauss(cnr_ind,1,3)
+   dm5t    = xm5t
+   xmtt    = agauss(cnr_ind,1,3)
+   dmtt    = xmtt
+   xamt    = agauss(cnr_ind,1,3)
+   damt    = xamt
+   xm1m2t  = agauss(cnr_ind,1,3)
+   dm1m2t  = xm1m2t
+   xm2m3t  = agauss(cnr_ind,1,3)
+   dm2m3t  = xm2m3t
+   xm3m4t  = agauss(cnr_ind,1,3)
+   dm3m4t  = xm3m4t
+   xm4m5t  = agauss(cnr_ind,1,3)
+   dm4m5t  = xm4m5t
+   xm1mtt  = agauss(cnr_ind,1,3)
+   dm1mtt  = xm1mtt
+   xmxmtt  = agauss(cnr_ind,1,3)
+   dmxmtt  = xmxmtt
+   xmtmlt  = agauss(cnr_ind,1,3)
+   dmtmlt  = xmtmlt
+   xmtamt  = agauss(cnr_ind,1,3)
+   dmtamt  = xmtamt
+   dck1s   = 'sqrt(dcapct*dcapct + dm1t*dm1t)'
*
+   pmsxt   = 'npmsxt + 12.5u*dpmsxt'        $ P- substrate Thickness
+   capct   = '0.21u + 0.13u*dcapct'         $ CA between PC and M1 1.0 <= M1 <= Wmax
+   capcti  = '0.26u + 0.13u*dcapct'         $ CA between PC and M1 0.5 <= M1 <= 1.0
+   ck1s    = '0.031m + 0.003m*dck1s'        $ K1 Res Area Cap (F/meter**2)
+   ck1sf   = '0.020n + 0.012n*dck1s'        $ K1 Res Fringe Cap (F/meter)
+   m1tn    =  0.425u
+   m1t     = 'm1tn + 0.14u*dm1t'            $ M1 Thickness 1.0 <= M1 <= Wmax
+   m1tin   =  0.375u
+   m1ti    = 'm1tin + 0.14u*dm1t'           $ M1 Thickness 0.5 <= M1 <= 1.0
+   m1tvn   =  0.325u
+   m1tv    = 'm1tvn + 0.14u*dm1t'           $ M1 Thickness M1 < 0.5um
+   m2tn    =  0.48u
+   m2t     = 'm2tn + 0.057u*dm2t'           $ M2 Thickness
+   m3tn    =  0.48u
+   m3t     = 'm3tn + 0.057u*dm3t'           $ M3 Thickness
+   m4tn    =  0.48u
+   m4t     = 'm4tn + 0.057u*dm4t'           $ M4 Thickness
+   m5tn    =  0.48u
+   m5t     = 'm5tn + 0.057u*dm5t'           $ M5 Thickness
+   mttn    =  0.48u
+   mtt     = 'mttn + 0.057u*dmtt'           $ MT Thickness
+   amt     = '4.0u + 0.4u*damt'             $ AM Thickness
+   m1m2tn  =  0.40u
+   m1m2t   = 'm1m2tn + 0.08u*dm1m2t'        $ M1-M2 Thickness 1.0 <= M1 <= Wmax
+   m2m3tn  =  0.55u
+   m2m3t   = 'm2m3tn + 0.183u*dm2m3t'       $ M2-M3 Thickness
+   m3m4tn  =  0.55u
+   m3m4t   = 'm3m4tn + 0.183u*dm3m4t'       $ M3-M4 Thickness
+   m4m5tn  =  0.55u
+   m4m5t   = 'm4m5tn + 0.183u*dm4m5t'       $ M4-M5 Thickness
+   m1mttn  =  0.40u
+   m1mtt   = 'm1mttn + 0.08u*dm1mtt'        $ M1-MT Thickness
+   mxmttn  =  0.55u
+   mxmtt   = 'mxmttn + 0.183u*dmxmtt'       $ Mx-MT Thickness (Mx=M2,M3 or M4)
+   mtamt   = '4.00u + 0.50u*dmtamt'         $ MT-AM Thickness
*
+   xrsub   = agauss(cnr_ind,1,3)            $ Sheet resistivity distributions
+   drsub   = xrsub
+   xrsubc  = agauss(0,1,3)
+   drsubc  = xrsubc
*
+   m1rs    = '0.062 - 0.023*dm1t'           $ M1 Rs (ohm/sq) 1.0 <= M1 <= Wmax
+   m1rsi   = '0.071 - 0.031*dm1t'           $ M1 Rs (ohm/sq) 0.5 <= M1 <= 1.0
+   m1rsv   = '0.084 - 0.042*dm1t'           $ M1 Rs (ohm/sq) M1 < 0.5um
+   m2rs    = '0.089 - 0.014*dm2t'           $ M2 Rs (ohm/sq)
+   m3rs    = '0.089 - 0.014*dm3t'           $ M3 Rs (ohm/sq)
+   m4rs    = '0.089 - 0.014*dm4t'           $ M4 Rs (ohm/sq)
+   m5rs    = '0.089 - 0.014*dm5t'           $ M5 Rs (ohm/sq)
+   mtrs    = '0.089 - 0.014*dmtt'           $ MT Rs (ohm/sq)
+   amrs    = '0.007 - 0.0015*damt'          $ AM Rs (ohm/sq)
+   rsub    = '0.158 + 0.022*drsub'          $ Sub Res (ohm-meter)
+   rsubc   = '6.0n + 0.23n*drsubc'          $ Sub Contact Res (ohm-meter**2)
*
*                                              Temp Coefficients (per degC)
*
+   tnwrs   = 0.0020                         $ NW Rs
+   tm1rs   = 0.0033                         $ M1 Rs
+   tm2rs   = 0.0033                         $ M2 Rs
+   tm3rs   = 0.0033                         $ M3 Rs
+   tm4rs   = 0.0033                         $ M4 Rs
+   tm5rs   = 0.0033                         $ M5 Rs
+   tmxrs   = 0.0033                         $ MX Rs
+   tmtrs   = 0.0033                         $ MT Rs
+   tamrs   = 0.0033                         $ AM Rs
+   trsub   = 0.0040                         $ Substrate Resistivity DC
+   tacrsub = 0.0020                         $ Substrate Resistivity AC
+   trsubc  = 0.0036                         $ Substrate Contact Resistance
+   tpcrsi  = 0.0032                         $ Silicided Poly Rs
*
.endl lvstats
