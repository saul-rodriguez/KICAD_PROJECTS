* Path, Component, Release: cmhv7sf/relAM/HSPICE/models/singlewire.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  CMHV7SF (AM metal option) "singlewire" transmission line
*
***************************************************************************
*
* The singlewire model contains:
*
*  1. Seven identical blocks connected in series. 
*     Example of one of such a block is shown below.
*     
*  2. Ladder network models frequency dependent skin effect.
*
*                   ________                       
* va      Rtotl/7  |        |       delta_Rl/7      delta_Rl*rt/7  delta_Rl*(rt^2)/7     vb
*  o--+---/\/\/\---|        |---+-----/\/\/\-----+-----/\/\/\-----+----/\/\/\-----+---+---o      
*     |            |________|   |    ________    |    ________    |    _______    |   |
*     |              Ltotl/7    |   |        |   |   |        |   |   |       |   |   |
*     |                         |---|        |---+---|        |---+---|       |---|   |
*     |                             |________|       |________|       |_______|       |
*     |                             delta_Ll/7      delta_Ll/rt/7  delta_Ll/rt^2/7    |
*   -----                                                                           -----
*   -----                                                                           -----
*     |  Ctotl/14                                                           Ctotl/14  |
*     |                                                                               |
*     |                                                                               |
*     |                                                                               |
*     +--------------------------------------+----------------------------------------+
*                                            |
*                                            |
*                                            o
*                                         vshield
*
***************************************************************************
*
* SYNTAX:
*
*  x1 va vb vshield singlewire
*  +  l          = 100.0u   transmission line length       
*  +  w          = 4u       transmission line width	    
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
.subckt  singlewire  ( va  vb  vshield )
*
** singlewire default parameters ******************************************
+  l          = 100.0u
+  w          = 4u
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
+  wglt = '(shieldsads==0)*(w+2.0*(hl+thl))+(shieldsads==1)*(w+2.0*(slt+wslt))'
*
+  dlw = '(layerads==2)*delm2+(layerads==3)*delm3+(layerads==4)*delm4+\\
          (layerads==5)*delm5+(layerads==6)*delmt+(layerads==7)*delam'
*
+  wl  = 'w+dlw'
+  wsl = 'wslt+dlw'
+  sl  = 'abs(slt-dlw)'
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
+  Rsg1  = 'Rgnd'
+  Rsg2  = '(shieldsads==0)*1.0e15+(shieldsads==1)*Rsig'
*
+  Rg1   = 'Rsg1 * l / wgl * tgndrs'
+  Rg2   = 'Rsg2 * l / wsl * tsigrs'
*
+  Rpath = 'Rsig * l / wl * tsigrs'
+  Rret  = 'Rg1 * Rg2 / ( 2.0 * Rg1 + Rg2 )'
*
+  Rtotl = 'Rpath + Rret'
*
** total capacitance - C_tot calculation **********************************
+  al  = '2.0 * atan( 0.5 * sl / hl )'
+  bt  = 'pi / 2.0 - al'
*
+  Ctot_no = '2.0*e0*(0.5174*wl/hl+0.9902+0.5581*log(1.0+thl/hl))'
*
+  Cpl0 = 'e0*(0.5073*wl/hl+0.6683+0.6869*log(1.0+thl/hl))'
+  Cpl1 = 'e0*(0.5073*wl/hl+0.6683+0.6869*log(0.5*sl/hl))'
+  Cpl2 = 'e0*(0.5073*wl/hl+0.8447*(1.0-cos(al))/(al-sin(al))*log(al/sin(al)))'
+  Cpl  = '(sl>=2.0*(hl+thl))*Cpl0 + (sl<2.0*(hl+thl))*((sl>=2.0*hl)*Cpl1 + (sl<2.0*hl)*Cpl2)' 
*
+  Cc0  = 'e0*(0.3180*log(1.0+wl/sl)+0.2953)'
+  Cc1  = 'e0*(0.3180*log(1.0+wl/sl)+0.2953+1.2061*(thl+hl-0.5*sl)/sl)'
+  Cc2  = 'e0*(0.3180*log(1.0+wl/sl)+0.2953+1.2061*thl/sl+0.5193*(1.0-cos(bt))/(bt-sin(bt))*log(bt/sin(bt)))'
+  Cc   = '(sl>=2.0*(hl+thl))*Cc0 + (sl<2.0*(hl+thl))*((sl>=2.0*hl)*Cc1 + (sl<2.0*hl)*Cc2)' 
*
+  Ctot_yes = '2.0 * ( Cpl + Cc )'
*
+  Ctotl = '((shieldsads==0)*Ctot_no+(shieldsads==1)*Ctot_yes)*eoxdepo*l'
*
** high - frequency inductance - L_tot calc. ******************************
+  tofl  = 'l * sqrt( eoxdepo ) / 3.0e8'
+  Ltotl = 'tofl * tofl / Ctotl'
*
*** delta_R, delta_L calculation ******************************************
+  t1  = 'thl'
+  t2  = 'th_gl'
+  w1  = 'wl'
+  Rs1 = 'Rsig * tsigrs'
+  w3  = 'wsl'
+  w2  = 'wgl'
+  Rs2 = 'Rgnd * tgndrs'
+  row = 'Rsig * t1 * tsigrs'
+  fil = 'row / ( pi * mu0 * t1 * t1 )'
*
+  delta_L1  = '(8*w1 - (8-pi)*t1)*t1/(64*w1*(4*w1 - (4-pi)*t1))'
+  delta_L2  = '((2*w1 - (pi-2)*t1) - pi*(2*w1-(6-pi)*t1)/(16-2*pi))/(64*w1-8*pi*w1)'
+  delta_L3  = '(3*pi*t1/32)/(16*w1-2*pi*w1)'
+  delta_L4  = '(pi*pow((2*w1-(6-pi)*t1),2))/(w1*t1*pow((16-2*pi),3))'
+  delta_L5  = '(2*w1 - (pi-2)*t1)*(2*w1-(6-pi)*t1)/(w1*t1*pow((16-2*pi),2))'
+  delta_L6  = '(1-pi/4)*t1/(w1*(16-2*pi))'
+  delta_L7  = '(t1/2 + (2*w1-(6-pi)*t1)/(16-2*pi))/(t1/4 + (2*w1-(6-pi)*t1)/(16-2*pi))'
+  delta_L8  = '(8*w2 - (8-pi)*t2)*t2/(64*w2*(4*w2-(4-pi)*t2))'
+  delta_L9  = '((2*w2 - (pi-2)*t2) - pi*(2*w2-(6-pi)*t2)/(16-2*pi))/(64*w2-8*pi*w2)'
+  delta_L10 = '(3*pi*t2/32)/(16*w2-2*pi*w2)'
+  delta_L11 = '(pi*pow((2*w2-(6-pi)*t2),2))/(w2*t2*pow((16-2*pi),3))'
+  delta_L12 = '(2*w2 - (pi-2)*t2)*(2*w2-(6-pi)*t2)/(w2*t2*pow((16-2*pi),2))'
+  delta_L13 = '(1-pi/4)*t2/(w2*(16-2*pi))'
+  delta_L14 = '(t2/2 + (2*w2-(6-pi)*t2)/(16-2*pi))/(t2/4 + (2*w2-(6-pi)*t2)/(16-2*pi))'
+  delta_L15 = '1 + (t2/2 + hl)/(w1/pi + t1/pi)'
+  delta_L16 = '1 + (t1/2 + hl)/(w2/pi + t2/pi)'
+  delta_L17 = '(2*w3+2*t1+2*pi*sqrt(pow((sl+w1/2),2)+pow((t2/2+hl),2)))/(2*w3+2*t1+2*pi*(sl+w1/2))'
+  delta_L18 = '0.5*(1+tanh((0.5-w1/w2)/0.16))*(2.07*(0.721*w2+5*w2*log(w2)+9.9*hl+4.9*t1+4.99*t2)/\\
                (100*w2)-0.1035*log(2*hl+t1+t2)-0.1184)'
*
+  delta_Ll_no = 'mu0*l*(delta_L1+delta_L2+delta_L3+\\ 
                 (delta_L4-delta_L5-delta_L6)*log(delta_L7)+\\
                 delta_L8+delta_L9+delta_L10+(delta_L11-delta_L12-\\ 
                 delta_L13)*log(delta_L14)+(1/(2*pi))*(log(delta_L15)+\\
                 log(delta_L16)))'
*
+  delta_Ll_yes = 'mu0*l*(delta_L1+delta_L2+delta_L3+\\ 
                  (delta_L4-delta_L5-delta_L6)*log(delta_L7)+\\ 
                  ((Rs1/w3)/(Rs1/w3+2*Rs2/w2))*(delta_L8+delta_L9+\\ 
                  delta_L10+(delta_L11-delta_L12-delta_L13)*log(delta_L14))+\\ 
                  (1/(2*pi))*(log(delta_L15)+((Rs1/w3)/(Rs1/w3+2*Rs2/w2))*\\
                  log(delta_L16))-((0.5*Rs2/w2)/(Rs2/w2+0.5*Rs1/w3))*(1/pi)*\\
                  log(delta_L17)+delta_L18)'  
*
+  L0l = '(shieldsads==0)*delta_Ll_no+(shieldsads==1)*delta_Ll_yes'
*
+  delta_Ll = '(pow(rt,2)/(pow(rt,2)+rt+1))*abs(L0l-Ltotl)' 
+  delta_Rl = '2.0*pi*rt*(delta_Ll*fil)'
*
** lumped element network *************************************************
  C66    net084 vshield   C = 'Ctotl/7.0'
  C69    net074 vshield   C = 'Ctotl/7.0'
  C70        vb vshield   C = 'Ctotl/14.0'
  C68    net064 vshield   C = 'Ctotl/7.0'
  C67   net0209 vshield   C = 'Ctotl/7.0'
  C65    net054 vshield   C = 'Ctotl/7.0'
  C4         va vshield   C = 'Ctotl/14.0' 
  C15   net0184 vshield   C = 'Ctotl/7.0'
  L116  net0184 net088    L = 'Ltotl/7.0'
  L135   net080 net074    L = 'delta_Ll/rt/rt/7.0'
  L117  net0120 net038    L = 'delta_Ll/7.0'
  L121  net0102 net056    L = 'delta_Ll/7.0'
  L118   net038 net044    L = 'delta_Ll/rt/7.0'
  L120   net054 net060    L = 'Ltotl/7.0'
  L123   net062 net084    L = 'delta_Ll/rt/rt/7.0'
  L134   net076 net080    L = 'delta_Ll/rt/7.0'
  L122   net056 net062    L = 'delta_Ll/rt/7.0'
  L139   net048 vb        L = 'delta_Ll/rt/rt/7.0'
  L91    net072 net0184   L = 'delta_Ll/rt/rt/7.0'
  L138   net046 net048    L = 'delta_Ll/rt/7.0'
  L119   net044 net054    L = 'delta_Ll/rt/rt/7.0'
  L128  net0209 net070    L = 'Ltotl/7.0'
  L131   net068 net064    L = 'delta_Ll/rt/rt/7.0'
  L129  net0130 net066    L = 'delta_Ll/7.0'
  L130   net066 net068    L = 'delta_Ll/rt/7.0'
  L132   net064 net086    L = 'Ltotl/7.0'
  L133  net0142 net076    L = 'delta_Ll/7.0'
  L136   net074 net042    L = 'Ltotl/7.0'
  L124   net084 net052    L = 'Ltotl/7.0'
  L127   net050 net0209   L = 'delta_Ll/rt/rt/7.0'
  L2      net44 net0190   L = 'delta_Ll/7.0'
  L5    net0190 net072    L = 'delta_Ll/rt/7.0'
  L125  net0112 net036    L = 'delta_Ll/7.0'
  L126   net036 net050    L = 'delta_Ll/rt/7.0'
  L0         va net32     L = 'Ltotl/7.0'
  L137   net096 net046    L = 'delta_Ll/7.0'
  R119   net044 net054    R = 'delta_Rl*rt*rt/7.0'
  R122   net056 net062    R = 'delta_Rl*rt/7.0'
  R123   net062 net084    R = 'delta_Rl*rt*rt/7.0'
  R118   net038 net044    R = 'delta_Rl*rt/7.0'
  R120   net060 net0102   R = 'Rtotl/7.0'
  R121  net0102 net056    R = 'delta_Rl/7.0'
  R133  net0142 net076    R = 'delta_Rl/7.0'
  R139   net048 vb        R = 'delta_Rl*rt*rt/7.0'
  R132   net086 net0142   R = 'Rtotl/7.0'
  R134   net076 net080    R = 'delta_Rl*rt/7.0'
  R116   net088 net0120   R = 'Rtotl/7.0'
  R135   net080 net074    R = 'delta_Rl*rt*rt/7.0'
  R138   net046 net048    R = 'delta_Rl*rt/7.0'
  R117  net0120 net038    R = 'delta_Rl/7.0'
  R137   net096 net046    R = 'delta_Rl/7.0'
  R91    net072 net0184   R = 'delta_Rl*rt*rt/7.0'
  R128   net070 net0130   R = 'Rtotl/7.0'
  R129  net0130 net066    R = 'delta_Rl/7.0'
  R130   net066 net068    R = 'delta_Rl*rt/7.0'
  R131   net068 net064    R = 'delta_Rl*rt*rt/7.0'
  R5    net0190 net072    R = 'delta_Rl*rt/7.0'
  R2      net44 net0190   R = 'delta_Rl/7.0'
  R124   net052 net0112   R = 'Rtotl/7.0'
  R125  net0112 net036    R = 'delta_Rl/7.0'
  R136   net042 net096    R = 'Rtotl/7.0'
  R126   net036 net050    R = 'delta_Rl*rt/7.0'
  R127   net050 net0209   R = 'delta_Rl*rt*rt/7.0'
  R0      net32 net44     R = 'Rtotl/7.0'
*
.ends singlewire
