* Path, Component, Release: cmos7base/rel/HSPICE/models/oprrpres.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  oprrpres   RR Poly Resistor (Over SX, NW, or BB)
*
***********************************************************************
*
*  Distributed R-C network which accounts for end resistance effects,
*  parasitic capacitance and includes a fixed substrate resistance.
*
*           Rend       Rmid                     Rmid       Rend
*   in  o--/\/\/\--o--/\/\/\---------o---------/\/\/\--o--/\/\/\--o  out
*                  |                 |                 |
*                  |                 |                 |
*                ----              -----             -----
*           Cpcx ----         Cpcx -----        Cpcx -----
*                  |                 |                 |
*                  |                 |                 |
*                  \                 \                 \
*              Rg  /              Rg /              Rg /
*                  \                 \                 \
*                  |                 |                 |
*                  o-----------o-----o-----o-----------o
*                              |           |
*   Parasitic capacitance is   \           |
*   divided among C elements   / Rsub    ----- Csub
*   in 1/6 - 2/3 - 1/6 ratios  \         -----
*                              |           |
*                              o-----o-----o
*                                    |
*                                    o  substrate (sx)
*
***********************************************************************
*
*  DIMENSIONS: W = Design width  of PC
*              L = Design length of OP
*
*  SYNTAX:     Specify both width and length:
*              xxx  in out sx  oprrpres (w=2u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in out sx  oprrpres (w=2u  r=9.0k)
*
*  SERIES:        s  --> Defined model parameter,   Reff = Rbar * s
*
*  PARALLEL:      m  --> Implicit model parameter,  Reff = Rbar / m
*
*              pbar  --> Defined model parameter,   Reff = Rbar
*
*               par  --> Explicit device multiplicity (par must equal m in netlist)
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                 sh --> Self-heating switch, default = 1
*                        No self-heating effects => sh=0
*
*                rsx --> Substrate resistance, default = -1
*                        -1 = model estimate based on groundplane, substrate options
*                         0 = substrate model (sxmodel) to be placed by user
*                        >0 = user-defined value
*
*                 bp --> Specify groundplane, bp=3 (SX), default
*                                             bp=2 (BB), bp=1 (NW)
*
*  NOTES:
*
*  1. Model supports only rectangular resistors with contacts at each
*     end of the resistor bar. "Dogbone" or multiple tap layouts are 
*     not supported.
*
*  2. Model assumes minimum groundrule spacings used for placing contacts
*     to calculate the end resistance effects based on OP design length.
*
*                                
***********************************************************************
.subckt oprrpres  in out sx  w=2u l=-1u r=-1 s=1 pbar=1 sh=1 dtemp=0 rsx=-1 bp=3 par=1
*
.param
* Check for minimum width, calculate effective width
+ opwdth = 'max(w,0.32u) + oprrdwf'
*
* Calculate op length, assumes w,r and groundrule spacings for contacts
+ rend2n = '1u*(exp(oppcrenn) - 97)'
+ pleqn  = '((r*pbar*(w+oprrdwn) - 2*rend2n - 2*oppcrsn*opdlbnn) / oprrrsn) - oppcdln + 2*opdlbnn'
*
* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'
*
* Check for minimum length, calculate effective length
+ oplen = 'max(plnom,1.1u) + oppcdlf'
*
* Resistance calculation
+ rmid  = 'oprrrsf * (max((oplen - 2*opdlbnf),1e-9) / opwdth) / 2'
+ rend1 = 'oppcrsf * (min(opdlbnf,oplen/2) / opwdth)'
+ rend2 = '1u*(exp(oppcrenf) - 97) / opwdth'
*
* Substrate resistance and capacitance calculations
+ ptnw = '(bp==1)'
+ ptbb = '(bp==2)'
+ ptsx = '(bp==3)'
+ prsx = '((ptnw+ptsx)*50 + ptbb*500)*(rsx==-1) + 1m*(rsx==0) + rsx*(rsx>0)'
+ prho = '(ptnw+ptsx)*rsub + ptbb*rsubbb'
+ pcsx = '(e0*ersi*prho)/prsx'
*
* Calculate area, perimeter for capacitance
* Subtract delta w, delta l to obtain drawn dimensions,
* Then include region outside of op mask
+ opcaplen  = '2 * ((oplen-oppcdln) + 2*oppcendf + (opwdth-oprrdwn))'
+ opcaparea = '((oplen-oppcdln) + 2*oppcendf) * (opwdth-oprrdwn)'
*
* Partition capacitance area, perimeter
+ apcx = 'opcaparea / 3'
+ ppcx = 'opcaplen / 3'
*
* Mis-match Calculation
+ opma   = 'oprrma * oprrma / (oplen * opwdth * 1e12)'
+ opml   = 'oprrml * oprrml / (opwdth * oplen * oplen * 1e18)'
+ opmw   = 'oprrmw * oprrmw / (opwdth * opwdth * 1e12)'
+ op3sig = '0.01 * sqrt(opma + opml + opmw)'
+ opmm   = 'op3sig * 0.7071 / sqrt(s*pbar*par)'
+ mmres  = agauss(0,1,3)
+ mmatr  = '1 + (opmm * mmres)'
*
*  The voltage coefficients take into effect self-heating
+ usesh = '((gsh==1)&&(sh==1))||(gsh==2)'    $ self-heating switch
+ psh = 'usesh*oprrshk * exp(oprrshm*log(opwdth*oplen*1e12)) / (2*rmid*opwdth*oplen*s*s*1e12)'
*
* Effective resistance from conductance
+ rg = '2.5/((ptsx*3.1e2+ptbb*1.6e2+ptnw*12e2)*opwdth + (ptsx*1.1e2+ptbb*0.55e2+ptnw*4.3e2)*oplen)'
*
+ pdeltat='temper-25+dtemp'
+ rmidt = 'rmid*(1.0+(oprrtc1*pdeltat)+(oprrtc2*pdeltat*pdeltat))'
*
* Flicker Noise
+ lnoi = 'oplen - oppcdlf'
+ wnoi = 'opwdth - oprrdwf'
+ rtot = '2*rmid+2*rend1+2*rend2'
+ k1 = '53e-23*(wnoi/lnoi)*(rtot/rmid)*(rtot/rmid)/(s*pbar*par)'
*
* Resistor network
rea2 in  12  	      'rend2*mmatr*s/pbar'  dtemp=dtemp  tc1=oppcrntc
rea1 12   1  	      'rend1*mmatr*s/pbar'  dtemp=dtemp  tc1=oppcrstc
rma  1    3  resnoi r='rmidt*mmatr*s/pbar/(1 + psh*v(in,out)*v(in,out))'
rmb  3    5  	      'rmidt*mmatr*s/pbar/(1 + psh*v(in,out)*v(in,out))'
reb1 5   52  	      'rend1*mmatr*s/pbar'  dtemp=dtemp  tc1=oppcrstc
reb2 52 out  	      'rend2*mmatr*s/pbar'  dtemp=dtemp  tc1=oppcrntc

cpca  1  11  c='((apcx*oppcdown + ppcx*oppcfrng)/2)*s*pbar'
cpcb  3  31  c='(2*(apcx*oppcdown + ppcx*oppcfrng))*s*pbar'
cpcc  5  51  c='((apcx*oppcdown + ppcx*oppcfrng)/2)*s*pbar'

rga   11  6  '6*rg/(s*pbar)'
rgb   31  6  '1.5*rg/(s*pbar)'
rgc   51  6  '6*rg/(s*pbar)'

rsb   6  sx  r=prsx
csb   6  sx  c=pcsx

.model resnoi r noise=1 kf=k1 af=2 lf=0 wf=2 ef=1 dw=0u dlr=0u l=lnoi w=wnoi

.ends oprrpres
