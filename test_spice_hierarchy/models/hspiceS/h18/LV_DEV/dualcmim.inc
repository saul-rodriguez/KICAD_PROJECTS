* Path, Component, Release: cmhv7sf/relAM/HSPICE/models/dualcmim.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  dualcmim      Dual MIM Capacitor
*
***********************************************************************
*
* The model is comprised of capacitors with series resistance and inductance.
* The input (lower plate) has losses to substrate characterized by a capacitor
* and series resistor.
*              
*                 
*       R1                       C1       R2     
*              |----|           | |            
*  o--/\  /\---| L1 |-----|-----| |-----/\  /\---o out
*  in   \/     |----|     |     | |       \/     
*                         |                             
*                       -----                           
*                       -----  C3                       
*                         |                             
*                         |                             
*                         \                             
*                         /  R3                         
*                         \  
*                         |
*                         |  reference plane
*  o----------------------|----------------------o
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
*              nlev  --> Indicates total # of metal levels (default, nlev=4)
*                        Possible values = 3, 4, 5, 6, or 7.
*
*              setind --> User determined value for the parasitic inductance.
*                        The default value of -2, which is used as a switch,
*                        forces the calculated inductance to be used.
*
*	 	par  --> Explicit device multiplicity.
*
*              dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                 bp --> Ground plane indicator 
*                        bp=3 (default) is usual substrate
*
*
*  NOTES:
*
*  1. Node assignment  - Node "in"  = HT and MT plates
*                      - Node "out" = QT plate
*
*  2. Model assumes the following design/process targets:
*
*     - MIM area capacitance = 4.10 mF/meter**2
*     - MIM dielectric thickness between QT, HT and MT = 330  Angstroms
*     - Qx thickness = 2000 Angstroms
*
*  3. Estimated bottom plate parasitic capacitance calculation assumes
*     no devices placed under the MIM. Accurate parasitic capacitance
*     value for cases with devices under MIM can only be obtained from
*     extracted layout.
*
*  4. The parasitic inductance included in this model is for the Dualmim only,
*     It does not include any user designed wiring connections which are
*     external to the Dualmim pcell.
*
*                                
***********************************************************************
.subckt dualcmim in out ref l=100u w=-0.5 c=-0.5 rsx=50 est=1 setind=-2 nlev=4 dtemp=0 par=1 bp=3
.param
*
+  qlev = 'nlev-1'
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
+  pql  = 'npql + delmq'                          $ Length of Q level	
+  qlnb = 'npql + ndelmq'
*
* Set the nominal and skewed Ca and Cp
+  nmimqa = ncmimqa
+  nmimha = ncmimha
+  mimqa  = cmimqa
+  mimha  = cmimha
+  mimp   = cdlmimp
*
* Calculate W
+  whx  = '((c-nmimqa*qlnb*(-ndelmh+ndelmq+4.0u)-2*mimp*(-ndelmh+ndelmq+4.0u+qlnb))/(nmimqa*qlnb + nmimha*hlnb + 2*mimp)) - ndelmh'
*
+  nphw = 'max(w,0) + abs(w-abs(w))*whx'
+  npqw = 'nphw + 4u'
+  phw  = 'nphw + delmh'                          $ Width of H level
+  pqw  = 'npqw + delmq'                          $ Width of Q level
*
* Calculate bottom plate dimensions
+  plmbot = 'phl - delmq + 14.48u + delmt'
+  pwmbot = 'phw - delmq + 14.48u + delmt'
*
* Mis-match Calculation
+  mma   = '1.1 / (nphw*l * 1e12)'
+  mmw   = '1.2 / (nphw*nphw * 1e12)'
+  mml   = '1.0 / (l*l * 1e12)'
+  m3sig = '0.01 * sqrt(mma+mmw+mml) * 0.7071 / sqrt(par)'
+  mmcap = agauss(0,1,3)
+  mmatc = '1 + (m3sig * mmcap)'
*
* Calculate total capacitance
+  pctot = '(mimha*phw*phl+mimqa*pqw*pql+2*mimp*(phl+phw+14.48u)) * mmatc * (1-q_error)'
+  pdeltat = 'temper - 25 + dtemp'
+  tcc1  = 18e-6
+  tcc2  = '-4.56e-7*(pdeltat<0)'
+  ptcc  = '1 + tcc1 * pdeltat + tcc2 * pdeltat**2'
*
* Calculate number of FT vias present
+  nftlh  = '2*int((l-7.995u)/3.24u)'      $ Last Metal to H level
+  nftlmt = '2*int((l+12.485u)/3.24u)'     $ Last Metal to MT level
+  nftwq  = '(1+(nphw>22.47u)) * int((nphw-3.995u)/3.24u)'  $ Last Metal to Q level
*
* Via and wiring resistance calculations
+  prviahmt = '2.5 * prvft / (nftlh + nftlmt)'
+  prviaqn  = '2.5 * prvft / nftwq'              $ Resistance to Q plate
+  prviaq   = 'prviaqn+qtrs*npql/(12*npqw)'      $ Include Q plate resistance
*
* Calculate # squares of top metal wiring per side of dev
+  wirsqrsh = '(4u/(nphw+14u) + 0.5*((l+16.24u)/(4u*3) + (0.5*(l+6u)/(nphw-8.48u))*(1-(nphw>22.47u)) + (7.24u/(nphw-8.48u)*(nphw>22.47u))))'
+  wirsqrsq = '(8u/(nphw-4u)*(1-(nphw>22.47u)) + (8u/(l-4u) + 4u/(l-4u) + (l+2u)/(nphw-18.48u)*(nphw>22.47u)))'
*
* Calculate total resistance due to top level metal wiring
+  prwir = 'amrs * (wirsqrsh+wirsqrsq)'
*
* Calculate H and MT plates total resistance 
+  botplt = '(mtrs*phw/phl) / 12'
+  prhmt  = 'prviahmt + prwir + botplt'
*
* Calculate the dualmim inductance
+  ltopwire = '2*(l + 16.25u + 7u + nphw/2)'
+  indtop   = '(1/2)*0.2u*(ltopwire+delam)*(log(2*(ltopwire+delam)/(4u+delam+amt))+0.5+(4u+delam+amt)/(3*(ltopwire+delam)))'
+  indh     = '0.2u*((2/3)*phw)*(log(2*(phw)/(phl+htt))+0.5+(phl+htt)/(3*(phw)))'
+  indq     = '0.2u*((2/3)*pql)*(log(2*(pql)/(pqw+qtt))+0.5+(pqw+qtt)/(3*(pql)))'
+  indmt    = '0.2u*((2/3)*pwmbot)*(log(2*(pwmbot)/(plmbot+mtt))+0.5+(plmbot+mtt)/(3*(pwmbot)))'
+  indval   = '(((indtop+indh)*indmt)/((indtop+indh)+indmt))+indq'
*
* Total inductance calculated
+  plind    = '(setind>=0)*setind + (setind<0)*(indval)'
*
* Calculate the stack height to groundplane from MIM bottom plate
+  h      = 'oppcstif+oppcthk+capct+m1t+(qlev>2)*(m1m2t+m2t)+(qlev>3)*(m2m3t+m3t)+(qlev>4)*(m3m4t+m4t)+(qlev>5)*(m4m5t+m5t)+(mxmtt)*(qlev>2)+(m1m2t)*(qlev==2)'
*
* Calculate effective stack height reduction due to M1,M2,M3 and M4 fill
+  mflfrac = 0.45
+  mtldt   = '-2*mflfrac*((m1t*(qlev>1))+(m2t*(qlev>2))+(m3t*(qlev>3))+(m4t*(qlev>4))+(m5t*(qlev>5)))'
*
* Calculate effective stack height reduction due to RX fill 
+  rxflfrac = 0.45
+  rxdt     = '-2*rxflfrac*oppcstif'
*
* Calculate total effective stack height delta
+  totdt    = 'mtldt+rxdt'
*
* Calculate effective stack height
+  heffec   = 'h+totdt'
*
* Calculate area and perimeter capacitance
+  cmbot  = 'e0*4.438/heffec'
+  cmfbot = 'e0*4.438*(2*0.525/(pi-2)*log(pi/2)+2*3.150/pi*log(1+mtt/heffec))'
+  pcref  = 'plmbot*pwmbot*cmbot + 2*(plmbot+pwmbot)*cmfbot'
*
* Set Vcc coefficients to be used 
+  vcc1 = -5.15e-7
+  vcc2 = 1.8e-5

r1   in   1  r='max(0.001,prhmt)'   tc1=0.0033  dtemp=dtemp
c1   1    2  c='pctot*ptcc*(1+(vcc1*(v(1,2)))+(vcc2*(abs((v(1,2)))**2)))'
l1   2    3  l=plind                            dtemp=dtemp
r2   3  out  r='max(0.001,prviaq)'  tc1=0.0033  dtemp=dtemp
c3   1    4  c='max(0.01f,(pcref*est))'         dtemp=dtemp
r3   4  ref  r=rsx                              dtemp=dtemp

.ends dualcmim
