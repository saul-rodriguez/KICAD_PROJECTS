* Path, Component, Release: cmos7base/rel/HSPICE/models/dualcmim.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  dualcmim      Dual MIM Capacitor
*
***********************************************************************
*
* The model is comprised of capacitors with series resistance and inductance.
* The input (lower plate) has losses to substrate characterized by a capacitor
* and series resistor.
*              
*       R1                           |------|      R2
*                             | |    |  L1  |     
*  o--/\  /\---------o--------| |----|      |----/\  /\--o
*  in   \/           |        | |    |------|      \/   out
*                    |
*                  -----
*                  -----  C3
*                    |
*                    |
*              o-----o-----o
*              |           |
*              \           |
*              / Rsub    ----- Csub
*              \         ----- 
*              |           |
*     o--------o-----------o--------o
*                  reference
*                    plane
*
***********************************************************************
*
*  DIMENSIONS: W, L = Design length of Hx
*
*  SYNTAX:     Specify both length and width:
*              xxx  in out ref  dualcmim (l=100u w=100u)
*
*       OR     Specify length and capacitance (of lower Qx):
*              xxx  in out ref  dualcmim (l=100u c=5p)
*
*  OPTIONAL:   rsx   --> Specifies the substrate resistance
*
*              est   --> Include estimated bottom plate to substrate (or BB
*                        or N-well) capacitance (default, est=1). Turn
*                        switch off (est=0) for extracted layout.
*
*	       lm    --> Specifies last metal back end of the line option.
*                        Dual metal (lm=0), AM (default, lm=1) or ML (lm=2)
*
*              nlev  --> Indicates total # of metal levels (default, nlev=4)
*                        Possible values = 3 (AM,ML), 4, 5, 6, 7 or 8 (DM).
*
*             setind --> User determined value for the parasitic inductance.
*                        The default value of -2, which is used as a switch,
*                        forces the calculated inductance to be used.
*
*	     par (m) --> Device multiplicity (par must equal m in netlist).
*
*              dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*		  hd --> High Density or regular MIM.  The nitride MIM can be 
*			 produced in two thicknesses allowing for a higher or 
*			 lower area capacitance.  hd = 0 (default) indicates 
*			 the thicker, lower capacitance MIM while hd = 1 
*			 indicates the thinner higher capacitance MIM.
*
*                rsx --> Substrate resistance, default = -1
*                        -1 = model estimate based on groundplane, substrate options
*                         0 = substrate model (sxmodel) to be placed by user
*                        >0 = user-defined value
*
*                 bp --> Specify groundplane, bp=3 (SX), default
*                                             bp=2 (BB), bp=1 (NW)
*                                             bp=-5 (High Res, 7RF only)
*
*    (7WL only)   ti --> Specifies "ref" node as TI groundplane (ti=1)
*                        or substrate groundplane (default, ti=0).
*
*  NOTES:
*
*  1. Node assignment  - Node "in"  = HT and MT plates
*                      - Node "out" = QT plate
*
*  2. Model assumes the following design/process targets:
*
*     - MIM area capacitance = 4.10 (5.40 HD) mF/meter**2
*     - MIM dielectric thickness between QT, HT and MT = 330 (250 HD) Angstroms
*     - Qx thickness = 2000 Angstroms
*
*  3. Estimated bottom plate parasitic capacitance calculation assumes
*     no devices placed under the MIM. Accurate parasitic capacitance
*     value for cases with devices under MIM can only be obtained from
*     extracted layout.
*
*  4. The parasitic inductance included in this model is for the Dualcmim only,
*     It does not include any user designed wiring connections which are
*     external to the Dualcmim pcell.
*
*                                
***********************************************************************
.subckt dualcmim in out ref l=100u w=-0.5 c=-0.5 rsx=-1 bp=3 est=1 setind=-2 nlev=4 lm=1 dtemp=0 hd=0 par=1 ti=0
.param
*
* Last metal and Q level switch settings
+  dm   = '(lm==0)'
+  am   = '(lm==1)'
+  ml   = '(lm==2)'
*
+  qlev = 'nlev-1-dm'
+  q2   = '(qlev==2)'
+  q3   = '(qlev==3)'
+  q4   = '(qlev==4)'
+  q5   = '(qlev==5)'
+  q6   = '(qlev==6)'
*
* Flag set to 1 if an invalid q level was selected by user
+  q_error = '1 - (q2 + q3 + q4 + q5 + q6)'
*
* Calculate width of device
+  phl  = 'l + delmh'                             $ Length of H level
+  hlnb = 'l + ndelmh'
+  npql = 'l + 10.48u'
+  npqlhd = 'l + 1.4u'
+  pql  = '(hd==0)*(npql + delmq)+(hd==1)*(npqlhd + delmq)'   $ Length of Q level	
+  qlnb = '(hd==0)*(npql + ndelmq)+(hd==1)*(npqlhd + ndelmq)'
*
* Calculate nominal and skewed Ca and Cp based on hd switch
+  ncmimqa = '(hd==1)*nhdcmimqa + (hd==0)*nccmimqa'
+  ncmimha = '(hd==1)*nhdcmimha + (hd==0)*nccmimha'
+  cmimqa = '(hd==1)*hdcmimqa + (hd==0)*ccmimqa'
+  cmimha = '(hd==1)*hdcmimha + (hd==0)*ccmimha'
+  cmimp = '(hd==1)*hddcmimp + (hd==0)*cdlcmimp'
*
* Calculate W
+  whx  = '((c-ncmimqa*qlnb*(-ndelmh+ndelmq+4.0u*(hd==0)+4.14u*(hd==1))-2*cmimp*(-ndelmh+ndelmq+4.0u*(hd==0)+4.14u*(hd==1)+qlnb))/(ncmimqa*qlnb + ncmimha*hlnb + 2*cmimp)) - ndelmh'
*
+  nphw = 'max(w,0) + abs(w-abs(w))*whx'
+  npqw = 'nphw + 4u'
+  npqwhd = 'nphw + 4.14u'
+  phw  = 'nphw + delmh'                          $ Width of H level
+  pqw  = '(hd==0)*(npqw + delmq)+(hd==1)*(npqwhd + delmq)'   $ Width of Q level
*
* Calculate bottom plate dimensions
+  plmbotn = 'phl - delmh + 14.48u + delmt'
+  pwmbotn = 'phw - delmh + 14.48u + delmt'
+  plmbothd = 'phl - delmh + 2.8u + delmt'
+  pwmbothd = 'phw - delmh + 8.08u + delmt'
+  plmbot = '(hd==0)*plmbotn + (hd==1)*plmbothd'
+  pwmbot = '(hd==0)*pwmbotn + (hd==1)*pwmbothd'
*
* Mis-match Calculation
+  mma   = '((hd==0)*2 + (hd==1)*6.25) / (nphw*l * 1e12)'
+  mmw   = '((hd==0)*2 + (hd==1)*0.0) / (nphw*nphw * 1e12)'
+  mml   = '((hd==0)*2 + (hd==1)*3.0625) / (l*l * 1e12)'
+  m3sig = '0.01 * sqrt(mma+mmw+mml) * 0.7071 / sqrt(par)'
+  mmcap = agauss(0,1,3)
+  mmatc = '1 + (m3sig * mmcap)'
*
* Calculate total capacitance
+  pctot = '(cmimha*phw*phl+cmimqa*pqw*pql+2*cmimp*(phl+phw+14.48u*(hd==0)+5.54u*(hd==1))) * mmatc * (1-q_error)'
+  ptcc  = '1 + 18e-6 * (temper + dtemp - 25)'
*
* Calculate number of FT vias present
+  nftlh  = '2 * int((l+(-7.995u*am-2.795u*ml+12.485u*dm))/3.24u)'       $ Last Metal to HT level
+  nftlmt = '2 * int((l+(12.485u*(1-dm)-1.995u*dm))/3.24u)'       $ Last Metal to MT level
+  nftwq  = '(1+(dm+(nphw>22.47u)*am+(nphw>15.68u)*ml)) * int((nphw+(-3.995u*am+1.205u*ml+2.005u*dm))/3.24u)'    $ Last Metal to Q level
* Calculate number of FT vias for HT top plate of the HD MIMs 
+  nftlhhdam = 'int((l+0.27u)/3.91u)'
+  nftwhhdam = 'int((nphw-4.529u)/3.91u)'
+  nftlhhdml = 'int((l+0.29u)/3.93u)'
+  nftwhhdml = 'int((nphw-1.109u)/3.93u)'
+  nftlhhddm = 'int((l+1.6u)/5.24u)'
+  nftwhhddm = 'int((nphw-2.199u)/3.24u)'
+  nftlhhd = 'am*nftlhhdam+ml*nftlhhdml+dm*nftlhhddm'
+  nftwhhd = 'am*nftwhhdam+ml*nftwhhdml+dm*nftwhhddm'
+  nfthhd = 'nftlhhd*nftwhhd'
* Calculate number of FT vias for QT middle plate of the HD MIMs 
+  nftqhd = 'dm*(int((l+1.0u)/3.24u))+am*(int((l+1.67u)/3.91u))+ml*(int((l+1.69u)/3.93u))'
* Calculate number of FT vias for MT bottom plate of the HD MIMs 
+  nftmhd = 'dm*(int((l+2.8u)/3.24u))+am*(int((l+3.47u)/3.91u))+ml*(int((l+3.49u)/3.93u))'
*
* Via and wiring resistance calculations
+  prviahmtn = '2.5 * prvft / (nftlh + nftlmt + 1e-24)'
+  prviaqn   = '2.5 * prvft / (nftwq+1e-24)'              $ Resistance to Q plate
+  prviahmt  = '(hd==0)*prviahmtn+(hd==1)*(prvft/(nfthhd+nftmhd+1e-24))'
+  prviaq    = '(hd==0)*(prviaqn+qtrs*npql/(12*npqw))+(hd==1)*((prvft/(nftqhd+1e-24))+qtrs*npqwhd/(3*npqlhd))'
*
*  Calculate # squares of top metal wiring per side of dev
+  wirsqrshn = 'dm*((2u/(nphw-4u+1e-24)) + 0.5*((l+12.48u)/(3*3.24u) + 3.24u/(l-2u) + 4u/(l-3u))) + am*(4u/(nphw+14u) + 0.5*((l+16.24u)/(4u*3) + (0.5*(l+6u)/(nphw-8.48u+1e-24))*(1-(nphw>22.47u)) + (7.24u/(nphw-8.48u+1e-24)*(nphw>22.47u)))) + ml*(2.4u/(nphw+12.48u) + 0.5*((l+12.88u)/(3.24u*3) + 0.5*(nphw+6u)/(l-2.8u)*(1-(nphw>15.68u)) + (l-2.8u)/7.24u)*(nphw>15.68u))'
+  wirsqrsqn = 'dm*(8u/(nphw+2u) + 3.24u/(nphw+2u) + ((l+2u)/2u)*(4u/(nphw-11.48u+1e-24))) + am*(8u/(nphw-4u+1e-24)*(1-(nphw>22.47u)) + (8u/(l-4u+1e-24) + 4u/(l-4u+1e-24) + (l+2u)/(nphw-18.48u+1e-24)*(nphw>22.47u))) + ml*(8u/(nphw+1.2u)*(1-(nphw>15.68u)) + (8u/(nphw+1.2u) + 3.24u/(nphw+1.2u) + (l+2u)/(nphw-13.28u+1e-24))*(nphw>15.68u))'
+  wirsqrshhd = '(((nphw-1.3u)/3.24u)/nftlhhddm)*dm+((nphw-4.3u)/(l-0.4u))*am+((nphw-1.3u)/(l-1.2u))*ml'
+  wirsqrsqhd = '(3.24u/(l+2.8u))*(1-ml)+ml*(2.44u/plmbot)'
+  wirsqrsh = '(hd==0)*wirsqrshn+(hd==1)*wirsqrshhd'
+  wirsqrsq = '(hd==0)*wirsqrsqn+(hd==1)*wirsqrsqhd'
*
* Calculate total resistance due to top level metal wiring
+  prwir = '(dm*e1rs + am*amrs + ml*mlrs) * (wirsqrsh+wirsqrsq)'
*
* Calculate H and MT plates total resistance 
+  botpltn  = '(mtrs*phw/phl) / 12'
+  botplthd = '(mtrs*pwmbot/plmbot)/3'
+  botplt   = '(hd==0)*botpltn + (hd==1)*botplthd'
+  prhmt    = 'prviahmt + prwir + botplt' 
*
* Calculate the dualcmim inductance
+  ltopwire = '2*(l + 16.25u + 7u + nphw/2)'
+  indtopamhd = '0.2u*((2/3)*phl)*(log(2*(phl)/(phw+amt))+0.5+(phw+amt)/(3*(phl)))'
+  indtopmlhd = '0.2u*((2/3)*phl)*(log(2*(phl)/(phw+mlt))+0.5+(phw+mlt)/(3*(phl)))'
+  indtope1hd = '0.2u*((2/3)*phl)*(log(2*(phl)/(phw+e1t))+0.5+(phw+e1t)/(3*(phl)))'
+  indtopam = '(1/2)*0.2u*(ltopwire+delam)*(log(2*(ltopwire+delam)/(4u+delam+amt))+0.5+(4u+delam+amt)/(3*(ltopwire+delam)))'
+  indtopml = '(1/2)*0.2u*(ltopwire+delml)*(log(2*(ltopwire+delml)/(4u+delml+mlt))+0.5+(4u+delml+mlt)/(3*(ltopwire+delml)))'
+  indtope1 = '(1/2)*0.2u*(ltopwire+dele1)*(log(2*(ltopwire+dele1)/(3.24u+dele1+e1t))+0.5+(3.24u+dele1+e1t)/(3*(ltopwire+dele1)))'
+  indtophd = 'am*indtopamhd + ml*indtopmlhd + dm*indtope1hd'
+  indtopn  = 'am*indtopam + ml*indtopml + dm*indtope1'
+  indtop   = '(hd==0)*indtopn + (hd==1)*indtophd'
+  indh     = '0.2u*((2/3)*phw)*(log(2*(phw)/(phl+htt))+0.5+(phl+htt)/(3*(phw)))'
+  indq     = '0.2u*((2/3)*pql)*(log(2*(pql)/(pqw+qtt))+0.5+(pqw+qtt)/(3*(pql)))'
+  indmt    = '0.2u*((2/3)*pwmbot)*(log(2*(pwmbot)/(plmbot+mtt))+0.5+(plmbot+mtt)/(3*(pwmbot)))'
+  indval   = '(((indtop+indh)*indmt)/((indtop+indh)+indmt))+indq'
+  plind    = '(setind!=-2)*setind + (setind==-2)*(indval)'
*
* Calculate the stack height to groundplane from MIM bottom plate
+  h = 'oppcstif+oppcthk+capct+m1t+(qlev>2)*(m1m2t+m2t)+(qlev>3)*(m2m3t+m3t)+(qlev>4)*(m3m4t+m4t)+(qlev>5)*(m4m5t+m5t)+(mxmtt)*(qlev>2)+(m1m2t)*(qlev==2)'
*
* Calculate effective stack height reduction due to M1,M2,M3 and M4 fill
+  mflfrac = 0.45
+  mtldt   = '-2*mflfrac*((m1t*(qlev>1))+(m2t*(qlev>2))+(m3t*(qlev>3))+(m4t*(qlev>4))+(m5t*(qlev>5)))'     
*
* Calculate effective stack heigh reduction due to RX fill 
+  rxflfrac = 0.45
+  rxdt     = '-2*rxflfrac*oppcstif'
*
* Calculate total effective stack height delta
+  totdt  = 'mtldt+tih*(ti==1)+rxdt*(ti==0)'
*
* Calculate effective stack height
+  heffec = 'h+totdt'
*
* Calculate area and perimeter capacitance
+  cmbot  = 'e0*4.438/heffec'
+  cmfbot = 'e0*4.438*(2*0.525/(pi-2)*log(pi/2)+2*3.150/pi*log(1+mtt/heffec))'
+  pcref  = 'plmbot*pwmbot*cmbot + 2*(plmbot+pwmbot)*cmfbot'
*
* Determine Vcc coefficients to be used based on hd switch
+  vcc1 = '(hd==0)*-5.15e-7+(hd==1)*-8e-6'
+  vcc2 = '(hd==0)*1.8e-5+(hd==1)*28e-6'
*
* Substrate resistance and capacitance calculations
+  ptnw = '(bp==1)'
+  ptbb = '(bp==2)'
+  ptsx = '(bp==3)'
+  pthr = '(bp==-5)'
+  prsx = '((ptnw+ptsx)*50 + ptbb*500 + pthr*5000)*(rsx==-1) + 1m*(rsx==0) + rsx*(rsx>0)'
+  prho = '(ptnw+ptsx)*rsub + ptbb*rsubbb + pthr*rsubhr'
+  pcsx = '(e0*ersi*prho)/prsx'

r1  in   1  r='max(0.001,prhmt)'   tc1=0.0033  dtemp=dtemp
c1  1    2  c='pctot*ptcc*(1+(vcc1*(v(1,2)))+(vcc2*(abs((v(1,2)))**2)))'
l1  2    3  l=plind                            dtemp=dtemp
r2  3  out  r='max(0.001,prviaq)'  tc1=0.0033  dtemp=dtemp
c3  1    4  c='max(0.01f,(pcref*est))'         dtemp=dtemp
rsb 4  ref  r=prsx                             dtemp=dtemp
csb 4  ref  c=pcsx                             dtemp=dtemp

.ends dualcmim
