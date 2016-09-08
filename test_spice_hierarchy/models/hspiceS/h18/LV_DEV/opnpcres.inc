* Path, Component, Release: cmhv7sf/rel/HSPICE/models/opnpcres.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  opnpcres    N+ Poly Resistor
*
***********************************************************************
*
*  Distributed R-C network which accounts for end resistance effects,
*  parasitic capacitance and includes a fixed substrate resistance.
*
*          Rend        Rmid                     Rmid        Rend
*  in  o--/\/\/\--o---/\/\/\---------o---------/\/\/\---o--/\/\/\--o  out
*                 |                  |                  |
*                 |                  |                  |
*               ----               -----              -----
*          Cpcx ----          Cpcx -----         Cpcx -----
*                 |                  |                  |
*                 |                  |                  |
*                 \                  \                  \
*             Rg  /               Rg /               Rg /
*                 \                  \                  \
*                 |                  |                  |
*                 o------------------o------------------o
*                                    |
*   Parasitic capacitance is         \
*   divided among C elements         / Rsub
*   in 1/6 - 2/3 - 1/6 ratios        \
*                                    |
*                                    o substrate (sx)
*
***********************************************************************
*
*  DIMENSIONS: W = Design width  of PC
*              L = Design length of OP
*
*  SYNTAX:     Specify both width and length:
*              xxx  in out sx  opnpcres (w=2u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in out sx  opnpcres (w=2u  r=520)
*
*  SERIES:        s  --> Defined model parameter,  Reff = Rbar * s
*
*  PARALLEL: m (par) --> Multiplicity parameters,  Reff = Rbar / m (par)
*
*              pbar  --> Defined model parameter,  Reff = Rbar
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                 sh --> Self-heating switch, default = 1
*                        No self-heating effects => sh=0
*
*                rsx --> Fixed substrate resistance, default = 50 ohm.
*
*                 bp --> Specify groundplane, default bp=3 (SX)
*                                                     bp=1 (NW)
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
*
.subckt opnpcres  in out sx  w=2u l=-1u r=-1 s=1 par=1 pbar=1 dtemp=0 rsx=50 bp=3 sh=1

.param
* Check for minimum width, calculate effective width
+ opwdth = 'max(w,0.32u) + opnpcdwf'
*
* Calculate op length, assumes w,r and groundrule spacings for contacts
+ rendn = '1u*(exp(opnpcrenn) - 97)'
+ pleqn = '((r*pbar*(w+opnpcdwn) - 2*rendn) / opnpcrsn) - opnpcdln'
*
* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'
*
* Check for minimum length, calculate effective length
+ oplen = 'max(plnom,1.06u) + opnpcdlf'
*
* Resistance calculation
+ rmid = 'opnpcrsf * (oplen / opwdth) / 2'
+ rend = '1u*(exp(opnpcrenf) - 97) / opwdth'
*
* Calculate area, perimeter for capacitance
* Subtract delta w, delta l to obtain drawn dimensions,
* Then include region outside of op mask
+ opcaplen  = '2 * ((oplen-opnpcdln) + 2*oppcendf + (opwdth-opnpcdwn))'
+ opcaparea = '((oplen-opnpcdln) + 2*oppcendf) * (opwdth-opnpcdwn)'
*
* Partition capacitance area, perimeter
+ apcx = 'opcaparea / 3'
+ ppcx = 'opcaplen / 3'
*
* Mis-match Calculation
+ opma   = 'opnpcma * opnpcma / (oplen * opwdth * 1e12)'
+ opml   = 'opnpcml * opnpcml / (opwdth * oplen * oplen * 1e18)'
+ opmw   = 'opnpcmw * opnpcmw / (opwdth * opwdth * 1e12)'
+ op3sig = '0.01 * sqrt(opma + opml + opmw)'
+ opmm   = 'op3sig * 0.7071 / sqrt(s*pbar*par)'
+ mmres  = agauss(0,1,3)
+ mmatr  = '1 + (opmm * mmres)'
*
*  The voltage coefficients take into effect self-heating
+ usesh = '((gsh==1)&&(sh==1))||(gsh==2)'    $ self-heating switch
+ psh = 'usesh*opnpshk * exp(opnpshm*log(opwdth*oplen*1e12)) / (2*rmid*opwdth*oplen*s*s*1e12)'
*
* Effective resistance from conductance
* ptnw and ptsx are also used for the capacitance
+ ptnw = '(bp==1)'
+ ptsx = '(bp==3)'
+ rg = '1/((ptsx*13.4e2+ptnw*12e2)*opwdth + (ptsx*4.9e2+ptnw*4.3e2)*oplen)'
*
+ pdeltat='temper-25+dtemp'
+ rmidt = 'rmid*(1.0+(opnpcrstc*pdeltat))'
*
* Flicker Noise
+ lnoi = 'oplen - opnpcdlf'
+ wnoi = 'opwdth - opnpcdwf'
+ rtot = '2*rmid+2*rend'
+ k1 = 'exp(log(10.34e-22)+dnoinpc*log(2))*exp(log(wnoi/lnoi))*(rtot/rend)*(rtot/rend)/(s*pbar*par)'
*
* Resistor network
rea  in   1  resnoi r='rend*mmatr*s/pbar'  dtemp=dtemp  tc1=opnpcrntc 
reb   5 out  	      'rend*mmatr*s/pbar'  dtemp=dtemp  tc1=opnpcrntc 
rma   1   3           'rmidt*mmatr*s*(1+opnpcvcr*(abs(v(in,sx)+v(out,sx))/2))/pbar/(1 + psh*v(in,out)*v(in,out))'
rmb   3   5           'rmidt*mmatr*s*(1+opnpcvcr*(abs(v(in,sx)+v(out,sx))/2))/pbar/(1 + psh*v(in,out)*v(in,out))'

cpca  1  11  c='((ptnw+ptsx)*(apcx*oppcdown + ppcx*oppcfrng)/2)*s*pbar'
cpcb  3  31  c='((ptnw+ptsx)*2*(apcx*oppcdown + ppcx*oppcfrng))*s*pbar'
cpcc  5  51  c='((ptnw+ptsx)*(apcx*oppcdown + ppcx*oppcfrng)/2)*s*pbar'

rga   11  6  '6*rg/(s*pbar)'
rgb   31  6  '1.5*rg/(s*pbar)'
rgc   51  6  '6*rg/(s*pbar)'

rsb   6  sx  r=rsx

.model resnoi r noise=1 kf=k1 af=2 lf=0 wf=2 ef=1 dw=0u dlr=0u l=lnoi w=wnoi

.ends opnpcres
