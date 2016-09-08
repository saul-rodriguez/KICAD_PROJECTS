* Path, Component, Release: cmos7base/rel/HSPICE/models/cmim.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  cmim          Single MIM Capacitor
*
***********************************************************************
*
* The model is comprised of a capacitor and series resistance and inductance.
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
*  DIMENSIONS: W, L = Design length of Qx
*
*  SYNTAX:     Specify both length and width:
*              xxx  in out ref  cmim (l=100u w=100u)
*
*       OR     Specify length and capacitance:
*              xxx  in out ref  cmim (l=100u c=5p)
*
*  OPTIONAL:   est   --> Include estimated bottom plate to substrate (or BB
*                        or N-well) capacitance (default, est=1). Turn
*                        switch off (est=0) for extracted layout.
*
*              lm    --> Specifies last metal back end of the line option.
*                        Dual metal (lm=0), AM (default, lm=1), or ML (lm=2)
*
*              nlev  --> Indicates total # of metal levels (default, nlev=4)
*                        Possible values = 3 (AM,ML), 4, 5, 6, 7, or 8 (DM).
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
*  1. Node assignment  - Node "in"  = lower metal plate
*                      - Node "out" = upper metal plate
*
*  2. Model assumes the following design/process targets:
*     - MIM area capacitance = 2.05 (2.70 HD) mF/meter**2
*
*  3. Estimated bottom plate parasitic capacitance calculation assumes
*     no devices placed under the MIM. Accurate parasitic capacitance
*     value for cases with devices under MIM can only be obtained from
*     extracted layout.
*
*  4. The parasitic inductance included in this model is for the MIM only,
*     It does not include any connections to the MIM.
*     The inductance assumes the wiring is into the MIM on one side
*     and out of the MIM on the opposite side. These two sides are assumed
*     to be sides defined by the parameter w. For any other connection
*     the inductance would be different than the model indicates.
*
*                                
***********************************************************************
.subckt cmim in out ref l=100u w=-0.5 c=-0.5 lm=1 est=1 nlev=4 setind=-2 rsx=-1 bp=3 dtemp=0 hd=0 par=1 ti=0
*
* Last metal, Q level switch settings
+  dm     = '(lm==0)'
+  am     = '(lm==1)'
+  ml     = '(lm==2)'
*
+  qlev   = 'nlev-1-dm'
+  q2     = '(qlev==2)'
+  q3     = '(qlev==3)'
+  q4     = '(qlev==4)'
+  q5     = '(qlev==5)'
+  q6     = '(qlev==6)'
*
* Flag set to 1 if an invalid q level was selected by user
+  q_error = '1 - (q2 + q3 + q4 + q5 + q6)'
*
* Calculate nominal and skewed Ca and Cp based on hd switch
+  ncmimqa = '(hd==1)*nhdcmimqa + (hd==0)*nccmimqa'
+  cmimqa = '(hd==1)*hdcmimqa + (hd==0)*ccmimqa'
+  cmimp = '(hd==1)*hdcmimp + (hd==0)*ccmimp'
+  ncmimp = '(hd==1)*nhdcmimp + (hd==0)*nccmimp'
*
* Calculate width of device
+  pl  = 'l + delmq'
+  lnb = 'l + ndelmq'
+  wx1 = '(c-(2*lnb*ncmimp))/(ncmimqa*lnb+2*ncmimp)-ndelmq'
+  wx2 = '(c-(2*lnb*ncmimp*0.85))/(ncmimqa*lnb+2*ncmimp*0.85)-ndelmq'
+  geosw1 = '(wx1>=8u)*(wx2>=8u)*(l>=8u)'
+  wx  = 'geosw1*(hd==0)*wx1 + (1-geosw1)*(hd==0)*wx2 + (hd==1)*wx1'
+  npw = 'max(w,0) + abs(w-abs(w))*wx'
+  pw  = 'npw + delmq'
+  geosw = '(npw>=8u)&&(l>=8u)'
*
* Calculate bottom plate dimensions
+  plmbotn1 = 'pl - delmq + 4.0u + delmt'
+  pwmbotn1 = 'pw - delmq + 4.0u + delmt'
+  plmbotn2 = 'pl - delmq + 2.0u + delmt'
+  pwmbotn2 = 'pw - delmq + 2.0u + delmt'
+  plmbothd = 'pl - delmq + 1.4u + delmt'
+  pwmbothd = 'pw - delmq + 1.4u + delmt'
+  plmbot = '(hd==0)*(geosw==1)*plmbotn1+(hd==0)*(geosw==0)*plmbotn2+(hd==1)*plmbothd'
+  pwmbot = '(hd==0)*(geosw==1)*pwmbotn1+(hd==0)*(geosw==0)*pwmbotn2+(hd==1)*pwmbothd'
*
* Mis-match Calculation
+  mma   = '((hd==0)*1.63 + (hd==1)*6.25) / (npw*l * 1e12)'
+  mmw   = '((hd==0)*0.00 + (hd==1)*0.00) / (npw*npw * 1e12)'
+  mml   = '((hd==0)*0.146 + (hd==1)*12.25) / (l*l * 1e12)'
+  m3sig = '0.01 * sqrt(mma+mmw+mml) * 0.7071 / sqrt(par)'
+  mmcap = agauss(0,1,3)
+  mmatc = '1 + (m3sig * mmcap)'
*
* Calculate total capacitance
+  cmimcp = '(hd==0)*geosw*cmimp+(hd==0)*(1-geosw)*cmimp*0.85+(hd==1)*cmimp'
+  pctot = '(cmimqa*pl*pw + cmimcp*2*(pl+pw)) * mmatc * (1-q_error)'
+  ptcc  = '1 + 18e-6 * (temper + dtemp - 25)'
*
* Calculate number of FT vias present
+  nftw   = 'geosw*int((npw-2.0u*(1-dm))/((3.24u+2.0u*dm)*0.9999))+(1-geosw)*max(1,int((npw-0.4u*(1-dm))/((3.24u+2.0u*dm)*0.9999)))'
+  nftl   = 'geosw*int((l-2.0u)/(3.24u*0.9999))+(1-geosw)*int((l-0.4u)/(3.24u*0.9999))'
+  nfthdaml = 'int((l+0.57u)/4.21u)'
+  nfthdamw = 'int((npw+0.57u)/4.21u)'
+  nfthdmll = 'int((l+0.57u)/4.21u)'
+  nfthdmlw = 'int((npw+0.57u)/4.21u)'
+  nfthddml = 'int((l+0.42u)/4.06u)'
+  nfthddmw = 'int((npw+1.60u)/5.24u)'
+  nfthd = 'am*nfthdaml*nfthdamw + ml*nfthdmll*nfthdmlw + dm*nfthddml*nfthddmw'
+  nfttot = '(hd==0)*nftw * nftl + (hd==1)*nfthd' 
*
* Via and wiring resistance calculations
+  prvia = '11*prvft/nfttot'
*
+  prwir = '(2*dm*e1rs + am*amrs + ml*mlrs)*pl/pw'  $ Top Plate resistance
+  prtop = 'prvia + (prwir/3)'
+  prbot = '(mtrs*pl/pw) / 3'                       $ Bottom Plate resistance
*
* Calculate the inductance of the MIM
+  indtopam = '0.2u*((2/3)*pl)*(log(2*(pl)/(pw+amt))+0.5+(pw+amt)/(3*(pl)))'
+  indtopml = '0.2u*((2/3)*pl)*(log(2*(pl)/(pw+mlt))+0.5+(pw+mlt)/(3*(pl)))'
+  indtope1 = '0.2u*((2/3)*pl)*(log(2*(pl)/(pw+e1t))+0.5+(pw+e1t)/(3*(pl)))'
+  indtop   = 'am*indtopam + ml*indtopml + dm*indtope1'
+  indbot   = '0.2u*((2/3)*plmbot)*(log(2*(plmbot)/(pwmbot+mtt))+0.5+(pwmbot+mtt)/(3*(plmbot)))'
+  plind    = '(setind>=0)*setind + (setind<0)*(indtop+indbot)'
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
+  totdt   = 'mtldt+tih*(ti==1)+rxdt*(ti==0)'
*
* Calculate effective stack height
+  heffec  = 'h+totdt'
*
* Calculate area and perimeter capacitance
+  cmbot  = 'e0*4.438/heffec'
+  cmfbot = 'e0*4.438*(2*0.525/(pi-2)*log(pi/2)+2*3.150/pi*log(1+mtt/heffec))'
+  pcref  = 'plmbot*pwmbot*cmbot + 2*(plmbot+pwmbot)*cmfbot'
*
* Determine Vcc coefficients to be used based on hd switch
+  vcc1 = '(hd==0)*-7.63e-5+(hd==1)*-125e-6'
+  vcc2 = '(hd==0)*1.62e-5+(hd==1)*27e-6'
*
* Substrate resistance and capacitance calculations
+  ptnw = '(bp==1)'
+  ptbb = '(bp==2)'
+  ptsx = '(bp==3)'
+  pthr = '(bp==-5)'
+  prsx = '((ptnw+ptsx)*50 + ptbb*500 + pthr*5000)*(rsx==-1) + 1m*(rsx==0) + rsx*(rsx>0)'
+  prho = '(ptnw+ptsx)*rsub + ptbb*rsubbb + pthr*rsubhr'
+  pcsx = '(e0*ersi*prho)/prsx'

r1  in   1  r='max(0.001,prbot)'    tc1=0.0033   dtemp=dtemp
c1  1    2  c='pctot*ptcc*(1+(vcc1*(v(1,2)))+(vcc2*(abs((v(1,2)))**2)))'
l1  2    3  l=plind                              dtemp=dtemp
r2  3  out  r='max(0.001,prtop)'    tc1=0.0033   dtemp=dtemp
c3  1    4  c='max(0.01f,pcref*est)'             dtemp=dtemp
rsb 4  ref  r=prsx                               dtemp=dtemp
csb 4  ref  c=pcsx                               dtemp=dtemp

.ends cmim
