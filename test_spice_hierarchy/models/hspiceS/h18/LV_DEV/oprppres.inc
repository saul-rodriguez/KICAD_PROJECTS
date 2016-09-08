* Path, Component, Release: cmhv7sf/rel/HSPICE/models/oprppres.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  oprppres    RP Poly Resistor (Over SX, NW, or BB)
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
*              xxx  in out sx  oprppres (w=2u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in out sx  oprppres (w=2u  r=520)
*
*  SERIES:        s  --> Defined model parameter,   Reff = Rbar * s
*
*  PARALLEL: m (par) --> Multiplicity parameters,   Reff = Rbar / m (par)
*
*              pbar  --> Defined model parameter,   Reff = Rbar
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                rsx --> Fixed substrate resistance, default = 50 ohm.
*
*                 bp --> Specify groundplane, default bp=3 (SX)
*                                                     bp=2 (BB)
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
*                                
***********************************************************************
*
.subckt oprppres  in out sx  w=2u l=-1u r=-1 s=1 pbar=1 dtemp=0 rsx=50 bp=3 par=1

.param
* Check for minimum width, calculate effective width
+ opwdth = 'max(w,0.32u) + oprpdwf'
*
* Calculate op length, assumes w,r and groundrule spacings for contacts
+ rendn = '1u*(exp(oprprenn) + 1)'
+ pleqn = '((r*pbar*(w+oprpdwn) - 2*rendn) / oprprsn) - oprpdln'
*
* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'
*
* Check for minimum length, calculate effective length
+ oplen = 'max(plnom,1.1u) + oprpdlf'
*
* Resistance calculation
+ rmid = 'oprprsf * (oplen / opwdth) / 2'
+ rend = '1u*(exp(oprprenf) + 1) / opwdth'
*
* Calculate area, perimeter for capacitance
* Subtract delta w, delta l to obtain drawn dimensions,
* Then include region outside of op mask
+ opcaplen  = '2 * ((oplen-oprpdln) + 2*oppcendf + (opwdth-oprpdwn))'
+ opcaparea = '((oplen-oprpdln) + 2*oppcendf) * (opwdth-oprpdwn)'
*
* Partition capacitance area, perimeter
+ apcx = 'opcaparea / 3'
+ ppcx = 'opcaplen / 3'
*
* Mis-match Calculation
+ opma   = 'oprpma * oprpma / (oplen * opwdth * 1e12)'
+ opml   = 'oprpml * oprpml / (opwdth * oplen * oplen * 1e18)'
+ opmw   = 'oprpmw * oprpmw / (opwdth * opwdth * 1e12)'
+ op3sig = '0.01 * sqrt(opma + opml + opmw)'
+ opmm   = 'op3sig * 0.7071 / sqrt(s*pbar*par)'
+ mmres  = agauss(0,1,3)
+ mmatr  = '1 + (opmm * mmres)'
*
* Effective resistance from conductance
* ptnw, ptbb, and ptsx are also used for the capacitance
+ ptnw = '(bp==1)'
+ ptbb = '(bp==2)'
+ ptsx = '(bp==3)'
+ rg = '1/((ptsx*13.4e2+ptbb*1.0e2+ptnw*12e2)*opwdth + (ptsx*4.9e2+ptbb*0.36e2+ptnw*4.3e2)*oplen)'
*
* Flicker Noise
+ lnoi = 'oplen - oprpdlf'
+ wnoi = 'opwdth - oprpdwf'
+ rtot = '2*rmid+2*rend'
+ k1 = 'exp(log(13.44e-23)+dnoirp*log(2))*exp(log(wnoi/lnoi))*(rtot/rend)*(rtot/rend)/(s*pbar*par)'
*
* Resistor network
rea  in   1  resnoi r='rend*mmatr*s/pbar'  dtemp=dtemp  tc1=oprprntc noise=1
reb   5 out  	      'rend*mmatr*s/pbar'  dtemp=dtemp  tc1=oprprntc
rma   1   3           'rmid*mmatr*s/pbar*(1+oprpvcr*(abs(v(in,sx)+v(out,sx))/2))'  dtemp=dtemp  tc1=oprprstc 
rmb   3   5 	      'rmid*mmatr*s/pbar*(1+oprpvcr*(abs(v(in,sx)+v(out,sx))/2))'  dtemp=dtemp  tc1=oprprstc

cpca  1  11  c='((ptnw+ptsx+0.9*ptbb)*(apcx*oppcdown + ppcx*oppcfrng)/2)*s*pbar'
cpcb  3  31  c='((ptnw+ptsx+0.9*ptbb)*2*(apcx*oppcdown + ppcx*oppcfrng))*s*pbar'
cpcc  5  51  c='((ptnw+ptsx+0.9*ptbb)*(apcx*oppcdown + ppcx*oppcfrng)/2)*s*pbar'

rga   11  6  '6*rg/(s*pbar)'
rgb   31  6  '1.5*rg/(s*pbar)'
rgc   51  6  '6*rg/(s*pbar)'

rsb   6  sx  r='rsx'

.model resnoi r noise=1 kf=k1 af=2 lf=0 wf=2 ef=1 dw=0u dlr=0u l=lnoi w=wnoi

.ends oprppres
