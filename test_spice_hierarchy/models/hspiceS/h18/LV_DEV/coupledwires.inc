* Path, Component, Release: cmhv7sf/relAM/HSPICE/models/coupledwires.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  (AM metal option) "coupledwires" transmission line
*
***************************************************************************
*
* The coupledwires model contains:
*
*  1. Seven identical blocks connected in series. 
*     Example of one of such a block is shown below.
*     
*  2. Ladder network models frequency dependent skin effect.
*
*                                           vshield 
*                                              o
*                                              |
*                                              |
*      +---------------------------------------+---------------------------------------+
*      |                                                                               |
*      |                                                                               |
*      |                                                                               |
*    ----- Ctotl/14                                                         Ctotl/14 -----
*    -----                                                                           -----
*      |                                                                               |
*      |                                                                               |
*      |             ________                                                          |
*  va1 |   Rtotl/7  |        |       delta_Rl/7      delta_Rl*rt/7  delta_Rl*(rt^2)/7  | vb1
*  o---+---/\/\/\---|        |-+-+-----/\/\/\-----+-----/\/\/\-----+----/\/\/\-----+---+---o    
*      |            |________| | |    ________    |    ________    |    _______    |   |
*      |             Ltotl/7   | |   |        |   |   |        |   |   |       |   |   |
*      |                       | |---|        |---+---|        |---+---|       |---|   |
*      |                       |     |________|       |________|       |_______|       |
*      |                      _|_    delta_Ll/7      delta_Ll/rt/7  delta_Ll/rt^2/7    |
*    -----                   |   |                                                   -----
*    -----                   |   |                                                   -----
*      |  Cctotl/14          |   | mutual_inductor (Kl)                     Cctotl/14  |
*      |                     |___|                                                     |
*      |                       |                                                       |
*      |             ________  |                                                       | 
*  va2 |   Rtotl/7  |        | |      delta_Rl/7     delta_Rl*rt/7  delta_Rl*(rt^2)/7  | vb2
*  o---+---/\/\/\---|        |-+-+-----/\/\/\-----+-----/\/\/\-----+----/\/\/\-----+---+---o
*      |            |________|   |    ________    |    ________    |    _______    |   |
*      |             Ltotl/7     |   |        |   |   |        |   |   |       |   |   |
*      |                         |---|        |---+---|        |---+---|       |---|   |
*      |                             |________|       |________|       |_______|       |
*      |                              delta_Ll/7      delta_Ll/rt/7  delta_Ll/rt^2/7   |
*    -----                                                                           -----
*    ----- Ctotl/14                                                         Ctotl/14 -----
*      |                                                                               |
*      |                                                                               |
*      +---------------------------------------+---------------------------------------+
*                                              |
*                                              |
*                                              o      
*                                           vshield 
*
***************************************************************************
*
* SYNTAX:
*
*  x1 va1 va2 vb1 vb2 vshield coupledwires
*  +  l          = 100.0u   transmission line length       
*  +  w          = 4u       transmission line width
*  +  d          = 0.7u     distance between wires 	    
*  +  shieldsads = 0        optional shielding	     
*  +  s          = 6.0u     distance to side shielding     
*  +  nlev       = 4        number of metal wiring levels  
*  +  layerads   = 7        signal layer		     
*  +  overads    = 1        ground layer		     
*  +  dtemp      = 0        difference in temperature between line and circuit (C)
*
***************************************************************************
*
* NOTES:
*
*  1. Length can vary continuously up to 1000um
*
*  2. Width can vary continuously within DRC rules
*
*  3. Number of total metal levels (nlev) always includes M1, MT and AM. 
*     Possible values = 3, 4, 5, 6 or 7.
*
*
***************************************************************************
.subckt coupledwires ( va1 va2 vb1 vb2 vshield )
*
** coupledwires default parameters ****************************************
+  l          = 100.0u
+  w          = 4u
+  d          = 0.7u
+  shieldsads = 0
+  s          = 6.0u
+  nlev       = 4
+  layerads   = 7
+  overads    = 1
+  dtemp      = 0
*
** additional constants and parameters *************************************     
+  rt   = 3.162278
*
+  wsmx = 0.28e-6
+  wsmt = 0.56e-6
+  wsam = 4.00e-6
*
+  slt  = '(shieldsads==0)*6.0u+(shieldsads==1)*s'
*
** metal stack ************************************************************
+  m1top3 = '-m1m2t' 
+  m1bot3 = 'm1top3 - m1t'
*       
+  m2top4 = '-mxmtt' 
+  m2bot4 = 'm2top4 - m2t' 
+  m1top4 = 'm2bot4 - m1m2t'
+  m1bot4 = 'm1top4 - m1t'
*
+  m3top5 = '-mxmtt'  
+  m3bot5 = 'm3top5 - m3t'
+  m2top5 = 'm3bot5 - m2m3t'
+  m2bot5 = 'm2top5 - m2t'
+  m1top5 = 'm2bot5 - m1m2t'
+  m1bot5 = 'm1top5 - m1t'
*
+  m4top6 = '-mxmtt'  
+  m4bot6 = 'm4top6 - m4t'
+  m3top6 = 'm4bot6 - m3m4t'
+  m3bot6 = 'm3top6 - m3t'
+  m2top6 = 'm3bot6 - m2m3t'
+  m2bot6 = 'm2top6 - m2t'
+  m1top6 = 'm2bot6 - m1m2t'
+  m1bot6 = 'm1top6 - m1t'
*
+  m5top7 = '-mxmtt'  
+  m5bot7 = 'm5top7 - m5t'
+  m4top7 = 'm5bot7 - m4m5t'
+  m4bot7 = 'm4top7 - m4t'
+  m3top7 = 'm4bot7 - m3m4t'
+  m3bot7 = 'm3top7 - m3t'
+  m2top7 = 'm3bot7 - m2m3t'
+  m2bot7 = 'm2top7 - m2t'
+  m1top7 = 'm2bot7 - m1m2t'
+  m1bot7 = 'm1top7 - m1t'
*
+  mtbota = '0.0' 
+  mttopa = 'mtt'
+  ambota = 'mttopa + mtamt'
+  amtopa = 'ambota + amt' 
*
** to calculate th, th_g, h ***********************************************
+  ly3 = '(nlev==3)'
+  ly4 = '(nlev==4)'
+  ly5 = '(nlev==5)'
+  ly6 = '(nlev==6)'
+  ly7 = '(nlev==7)'
*
+  layer_bota = '(layerads==6)*mtbota+(layerads==7)*ambota'
+  layer_bot3 = 'ly3*(layer_bota)'
+  layer_bot4 = 'ly4*(layer_bota+(layerads==2)*m2bot4)'
+  layer_bot5 = 'ly5*(layer_bota+(layerads==2)*m2bot5+(layerads==3)*m3bot5)'
+  layer_bot6 = 'ly6*(layer_bota+(layerads==2)*m2bot6+(layerads==3)*m3bot6+(layerads==4)*m4bot6)'
+  layer_bot7 = 'ly7*(layer_bota+(layerads==2)*m2bot7+(layerads==3)*m3bot7+\\
                 (layerads==4)*m4bot7+(layerads==5)*m5bot7)'
+  layer_botf = 'layer_bot3+layer_bot4+layer_bot5+layer_bot6+layer_bot7'
*
+  over_topa  = '(overads==6)*mttopa'
+  over_top3  = 'ly3*(over_topa+(overads==1)*m1top3)'
+  over_top4  = 'ly4*(over_topa+(overads==1)*m1top4+(overads==2)*m2top4)'
+  over_top5  = 'ly5*(over_topa+(overads==1)*m1top5+(overads==2)*m2top5+(overads==3)*m3top5)'
+  over_top6  = 'ly6*(over_topa+(overads==1)*m1top6+(overads==2)*m2top6+(overads==3)*m3top6+(overads==4)*m4top6)'
+  over_top7  = 'ly7*(over_topa+(overads==1)*m1top7+(overads==2)*m2top7+(overads==3)*m3top7+\\
                 (overads==4)*m4top7+(overads==5)*m5top7)'
+  over_topf  = 'over_top3+over_top4+over_top5+over_top6+over_top7'
*
** distance between signal line and ground ********************************
+  hl = 'abs(layer_botf-over_topf)'
*
** signal line thickness  - th ********************************************
+  thl = '(layerads==2)*m2t+(layerads==3)*m3t+(layerads==4)*m4t+\\
          (layerads==5)*m5t+(layerads==6)*mtt+(layerads==7)*amt'
*
** ground plane thickness - th_g ******************************************
+  th_gl = '(overads==1)*m1t+(overads==2)*m2t+(overads==3)*m3t+\\
            (overads==4)*m4t+(overads==5)*m5t+(overads==6)*mtt'
*
** effective dimensions ***************************************************
+  wslt = '((layerads==2)+(layerads==3)+(layerads==4)+(layerads==5))*wsmx+\\
           (layerads==6)*wsmt+(layerads==7)*wsam'
+  wglt = '(shieldsads==0)*(d+2.0*(w+hl+thl))+(shieldsads==1)*(d+2.0*(w+slt+wslt))'
*
+  dlw = '(layerads==2)*delm2+(layerads==3)*delm3+(layerads==4)*delm4+\\
          (layerads==5)*delm5+(layerads==6)*delmt+(layerads==7)*delam'
*
+  wl  = 'w+dlw'
+  wsl = 'wslt+dlw'
+  sl  = 'abs(slt-dlw)'
+  dl  = 'abs(d-dlw)'
*
+  wgl = 'wglt+(overads==1)*delm1+(overads==2)*delm2+(overads==3)*delm3+\\
          (overads==4)*delm4+(overads==5)*delm5+(overads==6)*delmt'
*
** total resistance - R_tot calculation ***********************************
+  tsigrs = '1.0+(temper+dtemp-25.0)*((layerads==2)*tm2rs+(layerads==3)*tm3rs+\\
            (layerads==4)*tm4rs+(layerads==5)*tm5rs+(layerads==6)*tmtrs+(layerads==7)*tamrs)'
*
+  tgndrs = '1.0+(temper+dtemp-25.0)*((overads==1)*tm1rs+(overads==2)*tm2rs+\\
            (overads==3)*tm3rs+(overads==4)*tm4rs+(overads==5)*tm5rs+(overads==6)*tmtrs)'
*
+  Rsig  = '(layerads==2)*m2rs+(layerads==3)*m3rs+(layerads==4)*m4rs+\\
            (layerads==5)*m5rs+(layerads==6)*mtrs+(layerads==7)*amrs'
+  m1rst = 'm1rs/(0.80+0.20*(1.68e-6/wgl))'
+  Rgnd  = '(overads==1)*m1rst+(overads==2)*m2rs+(overads==3)*m3rs+\\
            (overads==4)*m4rs+(overads==5)*m5rs+(overads==6)*mtrs'
*
+  Rtotl = 'Rsig * l / wl * tsigrs'
*
*** total capacitance - C_tot calculation *********************************
+  al  = '2.0 * atan( 0.5 * dl / hl )'
+  bt  = 'pi / 2.0 - al'
*
+  ld0 = '(dl>=2.0*(hl+thl))'
+  ld1 = '(dl<2.0*(hl+thl))'
+  ld2 = '(dl>=2.0*hl)'
+  ld3 = '(dl<2.0*hl)'
*
+  ls0 = '(sl>=2.0*(hl+thl))'
+  ls1 = '(sl<2.0*(hl+thl))'
+  ls2 = '(sl>=2.0*hl)'
+  ls3 = '(sl<2.0*hl)'
*
+  Cpl0_right_no = 'e0*(0.5217*wl/hl+0.9258+0.4779*log(1+thl/hl))'
+  Cpl1_right_no = 'e0*(0.5217*wl/hl+0.9258+0.4779*log(0.5*dl/hl))'
+  Cpl2_right_no = 'e0*(0.5217*wl/hl+1.1702*(1-cos(al))/(al-sin(al))*log(al/sin(al)))'
*
+  Cpl_right_no  = 'ld0 * Cpl0_right_no + ld1 * ( ld2 * Cpl1_right_no + ld3 * Cpl2_right_no )'
*
+  Cpl_left_no   = 'e0*(0.5217*wl/hl+0.9258+0.4779*log(1+thl/hl))'
*
+  Cself_no      = 'Cpl_right_no + Cpl_left_no'
*
+  Cmutual0_no = 'e0*(0.2967*log(1+wl/dl)+0.1537)'
+  Cmutual1_no = 'e0*(0.2967*log(1+wl/dl)+0.1537+1.7460*(thl+hl-0.5*dl)/dl)'
+  Cmutual2_no = 'e0*(0.2967*log(1+wl/dl)+0.1537+1.7460*thl/dl+\\
                  0.7058*(1-cos(bt))/(bt-sin(bt))*log(bt/sin(bt)))'
*
+  Cmutual_no  = 'ld0 * Cmutual0_no + ld1 * ( ld2 * Cmutual1_no + ld3 * Cmutual2_no )'
*
+  al_s = '2.0 * atan( 0.5 * sl / hl )'
+  bt_s = 'pi / 2.0 - al_s'
*
+  al_d = '2.0 * atan( 0.5 * dl / hl )'
+  bt_d = 'pi / 2.0 - al_d'
*
+  Cpl0_right_yes = 'e0*(0.5076*wl/hl+0.4560+0.9108*log(1+thl/hl))'
+  Cpl1_right_yes = 'e0*(0.5076*wl/hl+0.4560+0.9108*log(0.5*dl/hl))'
+  Cpl2_right_yes = 'e0*(0.5076*wl/hl+0.5764*(1-cos(al_d))/(al_d-sin(al_d))*log(al_d/sin(al_d)))'
*
+  Cpl_right_yes  = 'ld0 * Cpl0_right_yes + ld1 * ( ld2 * Cpl1_right_yes + ld3 * Cpl2_right_yes )'
*
+  Cpl0_left_yes  = 'e0*(0.5076*wl/hl+0.4560+0.9108*log(1+thl/hl))'
+  Cpl1_left_yes  = 'e0*(0.5076*wl/hl+0.4560+0.9108*log(0.5*sl/hl))'
+  Cpl2_left_yes  = 'e0*(0.5076*wl/hl+0.5764*(1-cos(al_s))/(al_s-sin(al_s))*log(al_s/sin(al_s)))'
*
+  Cpl_left_yes   = 'ls0 * Cpl0_left_yes + ls1 * ( ls2 * Cpl1_left_yes + ls3 * Cpl2_left_yes )'
*
+  Cmutual0_yes = 'e0*(0.2897*log(1+wl/dl)+0.1215)'
+  Cmutual1_yes = 'e0*(0.2897*log(1+wl/dl)+0.1215+1.4529*(thl+hl-0.5*dl)/dl)'
+  Cmutual2_yes = 'e0*(0.2897*log(1+wl/dl)+0.1215+1.4529*thl/dl+\\
                   0.4049*(1-cos(bt_d))/(bt_d-sin(bt_d))*log(bt_d/sin(bt_d)))'
*
+  Cmutual_yes = 'ld0 * Cmutual0_yes + ld1 * ( ld2 * Cmutual1_yes + ld3 * Cmutual2_yes )'
*
+  Cs0 = 'e0*(0.2651*log(1+wl/sl)+0.7453)'
+  Cs1 = 'e0*(0.2651*log(1+wl/sl)+0.7453+0.9045*(thl+hl-0.5*sl)/sl)'
+  Cs2 = 'e0*(0.2651*log(1+wl/sl)+0.7453+0.9045*thl/sl+\\
          0.3616*(1-cos(bt_s))/(bt_s-sin(bt_s))*log(bt_s/sin(bt_s)))'
*
+  Cs = 'ls0 * Cs0 + ls1 * ( ls2 * Cs1 + ls3 * Cs2 )'
*
+  Cself_yes = 'Cpl_right_yes + Cpl_left_yes + Cs'
*
+  Ctotl  = '( (shieldsads==0) * Cself_no + (shieldsads==1) * Cself_yes ) * eoxdepo * l'
+  Cctotl = '( (shieldsads==0) * Cmutual_no + (shieldsads==1) * Cmutual_yes ) * eoxdepo * l'
*
** coupling factor - K ****************************************************
+  Kl =  'Cctotl / ( Ctotl + Cctotl )' 
*
** high - frequency inductance - L_tot calc. ******************************
+  tofl  = 'l * sqrt( eoxdepo ) / 3.0e8'
+  Ltotl = 'tofl * tofl / Ctotl * ( Ctotl + Cctotl ) / ( Ctotl + 2.0 * Cctotl )'
*
*** delta_R, delta_L calculation ******************************************
+  t1   = 'thl'
+  t2   = 'th_gl'
+  w1   = 'wl'
+  Rs1  = 'Rsig * tsigrs'
+  Rs2  = 'Rgnd * tgndrs'
+  w3   = 'wsl'
+  w2   = 'wgl'
+  w21  = 'w1 + 2.0 * ( t1 + hl )'
+  w211 = 'w2 - dl - w1'
+  row  = 'Rsig * t1 * tsigrs'
+  fil  = 'row / ( pi * mu0 * t1 * t1 )'
*
+  delta_L1  = '(8*w1 - (8-pi)*t1)*t1/(64*w1*(4*w1 - (4-pi)*t1))'
+  delta_L2  = '((2*w1 - (pi-2)*t1) - pi*(2*w1-(6-pi)*t1)/(16-2*pi))/(64*w1-8*pi*w1)'
+  delta_L3  = '(3*pi*t1/32)/(16*w1-2*pi*w1)'
+  delta_L4  = '(pi*pow((2*w1-(6-pi)*t1),2))/(w1*t1*pow((16-2*pi),3))'
+  delta_L5  = '(2*w1 - (pi-2)*t1)*(2*w1-(6-pi)*t1)/(w1*t1*pow((16-2*pi),2))' 
+  delta_L6  = '(1-pi/4)*t1/(w1*(16-2*pi))'
+  delta_L7  = '(t1/2 + (2*w1-(6-pi)*t1)/(16-2*pi))/(t1/4 + (2*w1-(6-pi)*t1)/(16-2*pi))'
+  delta_L8  = '(8*w21 - (8-pi)*t2)*t2/(64*w21*(4*w21 - (4-pi)*t2))'
+  delta_L9  = '((2*w21 - (pi-2)*t2) - pi*(2*w21-(6-pi)*t2)/(16-2*pi))/(64*w21-8*pi*w21)'
+  delta_L10 = '(3*pi*t2/32)/(16*w21-2*pi*w21)'
+  delta_L11 = '(pi*pow((2*w21-(6-pi)*t2),2))/(w21*t2*pow((16-2*pi),3))'
+  delta_L12 = '(2*w21 - (pi-2)*t2)*(2*w21-(6-pi)*t2)/(w21*t2*pow((16-2*pi),2))'
+  delta_L13 = '(1-pi/4)*t2/(w21*(16-2*pi))'
+  delta_L14 = '(t2/2 + (2*w21-(6-pi)*t2)/(16-2*pi))/(t2/4 + (2*w21-(6-pi)*t2)/(16-2*pi))'          
+  delta_L15 = '1 + (t2/2 + hl)/(w1/pi + t1/pi)'
+  delta_L16 = '1 + (t1/2 + hl)/(w2/pi + t2/pi)'           
+  delta_L17off = '0.5*(1+tanh((0.35-w1/w2)/0.16))*(3.105*(0.721*w2+5*\\
                   w2*log(w2)+9.9*hl+4.9*t1+4.99*t2)/(100*w2)-0.15525*\\
                   log(2*hl+t1+t2)-0.1776)'
+  delta_L17on = '0.5*(1+tanh((0.35-w1/w2)/0.16))*(3.105*(0.721*w2+5*w2*\\
                  log(w2)+9.9*hl+4.9*t1+4.99*t2)/(100*w2)-0.15525*\\
                  log(2*hl+t1+t2)-0.1776)'   
+  delta_L18 = '(8*w211 - (8-pi)*t2)*t2/(64*w211*(4*w211 - (4-pi)*t2))'
+  delta_L19 = '((2*w211 - (pi-2)*t2) - pi*(2*w211-(6-pi)*t2)/(16-2*pi))/(64*w211-8*pi*w211)'
+  delta_L20 = '(3*pi*t2/32)/(16*w211-2*pi*w211)'
+  delta_L21 = '(pi*pow((2*w211-(6-pi)*t2),2))/(w211*t2*pow((16-2*pi),3))'
+  delta_L22 = '(2*w211 - (pi-2)*t2)*(2*w211-(6-pi)*t2)/(w211*t2*pow((16-2*pi),2))'
+  delta_L23 = '(1-pi/4)*t2/(w211*(16-2*pi))'
+  delta_L24 = '(t2/2 + (2*w211-(6-pi)*t2)/(16-2*pi))/(t2/4 + (2*w211-(6-pi)*t2)/(16-2*pi))'           
+  delta_L25 = '(2*w3+2*t1+2*pi*sqrt(pow((sl+w1/2),2)+pow((t2/2 + hl),2)))/(2*w3+2*t1+2*pi*(sl+w1/2))'
+  delta_L26 = '(2*w3+2*t1+2*pi*sqrt(pow((sl+3*w1/2+dl),2)+pow((t2/2 + hl),2)))/\\
                (2*w3+2*t1+2*pi*(sl+3*w1/2+dl))'
*
+  delta_Ll_no = 'mu0*l*(delta_L1+delta_L2+delta_L3+(delta_L4-\\
                  delta_L5-delta_L6)*log(delta_L7)+\\ 
                  (w21/w2)*delta_L8+delta_L9+delta_L10+\\ 
                  (delta_L11-delta_L12-delta_L13)*\\
                  log(delta_L14)+(1/(2*pi))*(log(delta_L15)+\\ 
                  log(delta_L16))+delta_L17off)'
*
+  delta_Ll_yes = 'mu0*l*(delta_L1+delta_L2+delta_L3+(delta_L4-\\
                  delta_L5-delta_L6)*log(delta_L7)+(w211*Rs1/(w2*Rs1+\\
                  2*w3*Rs2))*delta_L18+delta_L19+delta_L20+(delta_L21-\\
                  delta_L22-delta_L23)*log(delta_L24)+(1/(2*pi))*\\
                  (log(delta_L15)+(Rs1/(Rs1+2*w3*Rs2/w2))*\\
                  log(delta_L16))-(Rs2/(2*Rs2+\\
                  Rs1*w2/w3))*(1/pi)*(log(delta_L25)+\\
                  log(delta_L26))+delta_L17on)'
*
+  L0l = '(shieldsads==0)*delta_Ll_no+(shieldsads==1)*delta_Ll_yes'
*
+  delta_Ll = '( pow(rt,2) / ( pow(rt,2) + rt + 1.0 ) ) * abs( L0l - Ltotl )'
+  delta_Rl = '2.0 * pi * rt * ( delta_Ll * fil )'
*
** lumped element network *************************************************
*
  C90   vshield net0539  C = 'Ctotl/7.0'
  C94   vshield net0517  C = 'Ctotl/7.0'
  C85   net0513 net0539  C = 'Cctotl/7.0'
  C79   net0503 net0521  C = 'Cctotl/7.0'
  C77   net0491 net0517  C = 'Cctotl/7.0'
  C81   net0473 net0569  C = 'Cctotl/7.0'
  C84   vshield net0487  C = 'Ctotl/7.0'
  C87   vshield vb1      C = 'Ctotl/14.0'
  C59       va1 va2      C = 'Cctotl/14.0'
  C60   net0495 net0547  C = 'Cctotl/7.0'
  C95   vshield net0547  C = 'Ctotl/7.0'
  C96   vshield va2      C = 'Ctotl/14.0'
  C91   vshield net0555  C = 'Ctotl/7.0'
  C89   vshield vb2      C = 'Ctotl/14.0'
  C92   vshield net0569  C = 'Ctotl/7.0'
  C78   vshield net0491  C = 'Ctotl/7.0'
  C80   vshield net0503  C = 'Ctotl/7.0'
  C82   vshield net0473  C = 'Ctotl/7.0'
  C83   net0487 net0555  C = 'Cctotl/7.0'
  C86   vshield net0513  C = 'Ctotl/7.0'
  C88       vb1 vb2      C = 'Cctotl/14.0'
  C76   vshield net0495  C = 'Ctotl/7.0'
  C61   vshield va1      C = 'Ctotl/14.0'
  C93   vshield net0521  C = 'Ctotl/7.0'
  L94   net0565 net0545  L = 'delta_Ll/7.0'
  L2        va2 net0361  L = 'Ltotl/7.0'
  L8    net0521 net0349  L = 'Ltotl/7.0'
  L3    net0495 net0515  L = 'Ltotl/7.0'
  L135  net0501 net0513  L = 'delta_Ll/rt/rt/7.0'
  L117  net0703 net0511  L = 'delta_Ll/7.0'
  L121  net0715 net0509  L = 'delta_Ll/7.0'
  L118  net0511 net0507  L = 'delta_Ll/rt/7.0'
  L5    net0491 net0505  L = 'Ltotl/7.0'
  L123  net0499 net0503  L = 'delta_Ll/rt/rt/7.0'
  L134  net0479 net0501  L = 'delta_Ll/rt/7.0'
  L122  net0509 net0499  L = 'delta_Ll/rt/7.0'
  L139  net0493 vb1      L = 'delta_Ll/rt/rt/7.0'
  L91   net0469 net0495  L = 'delta_Ll/rt/rt/7.0'
  L138  net0461 net0493  L = 'delta_Ll/rt/7.0'
  L119  net0507 net0491  L = 'delta_Ll/rt/rt/7.0'
  L9    net0473 net0489  L = 'Ltotl/7.0'
  L131  net0483 net0487  L = 'delta_Ll/rt/rt/7.0'
  L129  net0691 net0485  L = 'delta_Ll/7.0'
  L130  net0485 net0483  L = 'delta_Ll/rt/7.0'
  L11   net0487 net0481  L = 'Ltotl/7.0'
  L133  net0707 net0479  L = 'delta_Ll/7.0'
  L13   net0513 net0477  L = 'Ltotl/7.0'
  L7    net0503 net0475  L = 'Ltotl/7.0'
  L127  net0465 net0473  L = 'delta_Ll/rt/rt/7.0'
  L90   net0669 net0471  L = 'delta_Ll/7.0'
  L92   net0471 net0469  L = 'delta_Ll/rt/7.0'
  L125  net0679 net0467  L = 'delta_Ll/7.0'
  L126  net0467 net0465  L = 'delta_Ll/rt/7.0'
  L1        va1 net0463  L = 'Ltotl/7.0'
  L137  net0675 net0461  L = 'delta_Ll/7.0'
  L105  net0551 net0553  L = 'delta_Ll/rt/7.0'
  L106  net0549 net0551  L = 'delta_Ll/7.0'
  L107  net0553 net0555  L = 'delta_Ll/rt/rt/7.0'
  L14   net0539 net0347  L = 'Ltotl/7.0'
  L99   net0571 net0559  L = 'delta_Ll/7.0'
  L103  net0533 net0529  L = 'delta_Ll/7.0'
  L97   net0561 net0563  L = 'delta_Ll/7.0'
  L100  net0567 net0569  L = 'delta_Ll/rt/rt/7.0'
  L4    net0547 net0309  L = 'Ltotl/7.0'
  L144  net0535 net0539  L = 'delta_Ll/rt/rt/7.0'
  L143  net0537 net0543  L = 'delta_Ll/7.0'
  L142  net0525 net0527  L = 'delta_Ll/7.0'
  L141  net0543 net0523  L = 'delta_Ll/rt/7.0'
  L6    net0517 net0319  L = 'Ltotl/7.0'
  L115  net0519 net0521  L = 'delta_Ll/rt/rt/7.0'
  L114  net0529 net0535  L = 'delta_Ll/rt/7.0'
  L113  net0527 net0519  L = 'delta_Ll/rt/7.0'
  L112  net0541 vb2      L = 'delta_Ll/rt/rt/7.0'
  L111  net0557 net0547  L = 'delta_Ll/rt/rt/7.0'
  L110  net0545 net0541  L = 'delta_Ll/rt/7.0'
  L109  net0523 net0517  L = 'delta_Ll/rt/rt/7.0'
  L10   net0569 net0335  L = 'Ltotl/7.0'
  L98   net0559 net0557  L = 'delta_Ll/rt/7.0'
  L96   net0563 net0567  L = 'delta_Ll/rt/7.0'
  L12   net0555 net0343  L = 'Ltotl/7.0'
  k48        L1 L2       k = 'Kl'
  k49        L3 L4       k = 'Kl'
  k50        L5 L6       k = 'Kl'
  k51        L7 L8       k = 'Kl'
  k52        L9 L10      k = 'Kl'
  k53       L11 L12      k = 'Kl'
  k54       L13 L14      k = 'Kl'
  R119  net0507 net0491  R = 'delta_Rl*rt*rt/7.0'
  R122  net0509 net0499  R = 'delta_Rl*rt/7.0'
  R123  net0499 net0503  R = 'delta_Rl*rt*rt/7.0'
  R118  net0511 net0507  R = 'delta_Rl*rt/7.0'
  R120  net0505 net0715  R = 'Rtotl/7.0'
  R121  net0715 net0509  R = 'delta_Rl/7.0'
  R133  net0707 net0479  R = 'delta_Rl/7.0'
  R139  net0493 vb1      R = 'delta_Rl*rt*rt/7.0'
  R132  net0481 net0707  R = 'Rtotl/7.0'
  R134  net0479 net0501  R = 'delta_Rl*rt/7.0'
  R116  net0515 net0703  R = 'Rtotl/7.0'
  R135  net0501 net0513  R = 'delta_Rl*rt*rt/7.0'
  R138  net0461 net0493  R = 'delta_Rl*rt/7.0'
  R117  net0703 net0511  R = 'delta_Rl/7.0'
  R137  net0675 net0461  R = 'delta_Rl/7.0'
  R91   net0469 net0495  R = 'delta_Rl*rt*rt/7.0'
  R128  net0489 net0691  R = 'Rtotl/7.0'
  R129  net0691 net0485  R = 'delta_Rl/7.0'
  R130  net0485 net0483  R = 'delta_Rl*rt/7.0'
  R131  net0483 net0487  R = 'delta_Rl*rt*rt/7.0'
  R90   net0471 net0469  R = 'delta_Rl*rt/7.0'
  R92   net0669 net0471  R = 'delta_Rl/7.0'
  R124  net0475 net0679  R = 'Rtotl/7.0'
  R125  net0679 net0467  R = 'delta_Rl/7.0'
  R136  net0477 net0675  R = 'Rtotl/7.0'
  R126  net0467 net0465  R = 'delta_Rl*rt/7.0'
  R127  net0465 net0473  R = 'delta_Rl*rt*rt/7.0'
  R93   net0463 net0669  R = 'Rtotl/7.0'
  R145  net0523 net0517  R = 'delta_Rl*rt*rt/7.0'
  R144  net0527 net0519  R = 'delta_Rl*rt/7.0'
  R143  net0519 net0521  R = 'delta_Rl*rt*rt/7.0'
  R142  net0543 net0523  R = 'delta_Rl*rt/7.0'
  R141  net0319 net0525  R = 'Rtotl/7.0'
  R140  net0525 net0527  R = 'delta_Rl/7.0'
  R115  net0533 net0529  R = 'delta_Rl/7.0'
  R114  net0541 vb2      R = 'delta_Rl*rt*rt/7.0'
  R113  net0343 net0533  R = 'Rtotl/7.0'
  R112  net0529 net0535  R = 'delta_Rl*rt/7.0'
  R111  net0309 net0537  R = 'Rtotl/7.0'
  R110  net0535 net0539  R = 'delta_Rl*rt*rt/7.0'
  R109  net0545 net0541  R = 'delta_Rl*rt/7.0'
  R108  net0537 net0543  R = 'delta_Rl/7.0'
  R107  net0565 net0545  R = 'delta_Rl/7.0'
  R106  net0557 net0547  R = 'delta_Rl*rt*rt/7.0'
  R105  net0335 net0549  R = 'Rtotl/7.0'
  R104  net0549 net0551  R = 'delta_Rl/7.0'
  R103  net0551 net0553  R = 'delta_Rl*rt/7.0'
  R102  net0553 net0555  R = 'delta_Rl*rt*rt/7.0'
  R101  net0559 net0557  R = 'delta_Rl*rt/7.0'
  R100  net0571 net0559  R = 'delta_Rl/7.0'
  R99   net0349 net0561  R = 'Rtotl/7.0'
  R98   net0561 net0563  R = 'delta_Rl/7.0'
  R97   net0347 net0565  R = 'Rtotl/7.0'
  R96   net0563 net0567  R = 'delta_Rl*rt/7.0'
  R95   net0567 net0569  R = 'delta_Rl*rt*rt/7.0'
  R94   net0361 net0571  R = 'Rtotl/7.0'
*
.ends coupledwires
