* Path, Component, Release: cmhv7sf/relAM/HSPICE/models/cmimhd.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  cmimhd          Single HD MIM Capacitor
*
***********************************************************************
*
* The model is comprised of a capacitor and series resistance and inductance.
* The input (lower plate) has losses to substrate characterized by a capacitor
* and series resistor.
*
*
*       R1           C1    |------|      R2
*                   | |    |  L1  |     
*  o--/\  /\---|----| |----|      |----/\  /\--o
*  in   \/     |    | |    |------|      \/   out
*              |
*            -----
*            -----  C3
*              |
*              |
*              \
*              /  R3
*              \
*              |
*              |  reference plane
*   o----------|-------------------------------o
*                                
***********************************************************************
*
*  DIMENSIONS: W, L = Design length of Qx
*
*  SYNTAX:     Specify both length and width:
*              xxx  in out ref  cmimhd (l=100u w=100u)
*
*       OR     Specify length and capacitance:
*              xxx  in out ref  cmimhd (l=100u c=5p)
*
*  OPTIONAL:   est   --> Include estimated bottom plate to substrate (or BB
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
*  NOTES:
*
*  1. Node assignment  - Node "in"  = lower metal plate
*                      - Node "out" = upper metal plate
*
*  2. Model assumes the following design/process targets:
*     - MIM area capacitance = 2.70mF/meter**2 
*     - MIM dielectric thickness between Qx and bottom plate = 350 Angstroms
*
*  3. Estimated bottom plate parasitic capacitance calculation assumes
*     no devices placed under the MIM. Accurate parasitic capacitance
*     value for cases with devices under MIM can only be obtained from
*     extracted layout.
*
*  4. The parasitic inductance included in this model is for the MIM only,
*     It does not include any connections to the MIM.
*     The inducance assumes the wiring is into the MIM on one side
*     and out of the MIM on the opposite side. These two sides are assumed
*     to be sides defined by the parameter w. For any other connection
*     the inductance would be different than the model indicates.
*
*                                
***********************************************************************
.subckt cmimhd in out ref l=100u w=-0.5 c=-0.5 est=1 nlev=4 setind=-2 rsx=50 dtemp=0 par=1 bp=3
*
+  qlev   = 'nlev-1'
+  q2     = '(qlev==2)'
+  q3     = '(qlev==3)'
+  q4     = '(qlev==4)'
+  q5     = '(qlev==5)'
+  q6     = '(qlev==6)'
*
* Flag set to 1 if an invalid q level was selected by user
+  q_error = '1 - (q2 + q3 + q4 + q5 + q6)'
*
* Set nominal and skewed Ca and Cp 
+  nmimqa = nhdmimqa
+  mimqa  = hdmimqa
+  mimp   = hdmimp
+  nmimp   = nhdmimp
*
* Calculate width of device
+  pl = 'l + delmq'
+  lnb = 'l + ndelmq'
+  wx = '(c-(2*lnb*nmimp))/(nmimqa*lnb+2*nmimp)-ndelmq'
+  npw= 'max(w,0) + abs(w-abs(w))*wx'
+  pw = 'npw + delmq'
*
* Calculate bottom plate dimensions
+  plmbot = 'pl - delmq + 1.4u + delmt'
+  pwmbot = 'pw - delmq + 1.4u + delmt'
*
* Mis-match Calculation
+  mma   = '1.0 / (npw*l * 1e12)'
+  mmw   = '2.2 / (npw*npw * 1e12)'
+  mml   = '2.1 / (l*l * 1e12)'
+  m3sig = '0.01 * sqrt(mma+mmw+mml) * 0.7071 / sqrt(par)'
+  mmcap = agauss(0,1,3)
+  mmatc = '1 + (m3sig * mmcap)'
*
* Calculate total capacitance
+  pctot = '(mimqa*pl*pw + mimp*2*(pl+pw)) * mmatc * (1-q_error)'
+  pdeltat = 'temper - 25 + dtemp'
+  tcc1  = '30.26e-6*(pdeltat>0) + 18.74e-6*(pdeltat<0)'
+  tcc2  = '-3.68e-8*(pdeltat>0) + -7.37e-7*(pdeltat<0)'
+  ptcc  = '1 + tcc1 * pdeltat + tcc2 * pdeltat**2'
*
* Calculate number of FT vias present
+  nfthdaml = 'max(1,int((l+0.57u)/4.21u))'
+  nfthdamw = 'max(1,int((npw+0.57u)/4.21u))'
+  nfttot = 'nfthdaml*nfthdamw'
*
* Via and wiring resistance calculations
+  prvia = '11*prvft/nfttot'
*
+  prwir = 'amrs*pl/pw'                         $ Top Plate resistance
+  prtop = 'prvia + (prwir/3)'
+  prbot = '(mtrs*pl/pw) / 3'                   $ Bottom Plate resistance
*
* Calculate the inductance of the MIM
+  indtop   = '0.2u*((2/3)*pl)*(log(2*(pl)/(pw+amt))+0.5+(pw+amt)/(3*(pl)))'
+  indbot   = '0.2u*((2/3)*plmbot)*(log(2*(plmbot)/(pwmbot+mtt))+0.5+(pwmbot+mtt)/(3*(plmbot)))'
*
* Total inductance calculated
+  plind    = '(setind>=0)*setind + (setind<0)*(indtop+indbot)'
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
* Determine Vcc coefficients to be used based
+  vcc1 = -459.4e-6
+  vcc2 = 27e-6

r1   in   1  r='max(0.001,prbot)'    tc1=0.0033  dtemp=dtemp
c1   1    2  c='pctot*ptcc*(1+(vcc1*(v(1,2)))+(vcc2*(abs((v(1,2)))**2)))'
l1   2    3  l=plind                             dtemp=dtemp
r2   3  out  r='max(0.001,prtop)'    tc1=0.0033  dtemp=dtemp
c3   1    4  c='max(0.01f,pcref*est)'            dtemp=dtemp
r3   4  ref  r=rsx                               dtemp=dtemp

.ends cmimhd
