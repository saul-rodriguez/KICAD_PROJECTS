* Path, Component, Release: cmhv7sf/rel/HSPICE/models/k1res.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  k1res    K1 BEOL Resistor
*
***********************************************************************
*
*  Distributed R-C network that accounts for end resistance effects,
*  parasitic capacitance and includes a fixed substrate resistance.
*
*           Rend       Rmid                     Rmid       Rend
*   in  o--/\/\/\--+--/\/\/\---------+---------/\/\/\--+--/\/\/\--o  out
*                  |                 |                 |
*                  |                 |                 |
*                ----              -----             -----
*           Capa ----         Capb -----        Capc -----
*                  |                 |                 |
*                  |                 |                 |
*                  +-----------------+-----------------+
*                                    |
*   Parasitic capacitance is         \
*   divided among C elements         / Rsub
*   in 1/6 - 2/3 - 1/6 ratios        \
*                                    |
*                                    o substrate (sx)
*
***********************************************************************
*
*  DIMENSIONS: W = Design width  of K1
*              L = Design space between Vias
*
*  SYNTAX:     Specify both width and length:
*              xxx  in out sx  k1res (w=5u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in out sx  k1res (w=5u  r=150)
*
*  SERIES:        s  --> Defined model parameter,  Reff = Rbar * s
*
*  PARALLEL: m (par) --> Multiplicity parameters,  Reff = Rbar / m (par)
*
*              pbar  --> Defined model parameter,  Reff = Rbar
*
*  OPTIONAL:  dtemp  --> Device temperature difference with respect to
*                         the simulated circuit temperature (deg C).
*
*                 sh --> Self-heating switch, default = 1
*                        No self-heating effects => sh=0
*
*                rsx --> Fixed substrate resistance, default = 50 ohm.
*
*  NOTES:
*
*  1. Model supports only rectangular resistors with vias at each
*     end of the resistor bar. "Dogbone" or multiple tap layouts are
*     not supported.
*
*
***********************************************************************
*
.subckt k1res  ( in out sx )  w=5u l=-5u r=-1 s=1 par=1 pbar=1 dtemp=0 sh=1 rsx=50 
*
* Check for minimum width, calculate effective width
+ k1wdth = 'max(w,5.0u) + k1dwf'
*
* Calculate  length when r > 0, l < 0
+ rendn = '2u*(exp(k1renn)-10)/k1wdth'
+ pleqn =  '((r - rendn)*(w+k1dwn) - k1rsn*k1dln ) / k1rsn'
*
* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'
*
* Check for minimum length, calculate effective length
+ k1len = 'max(plnom,3.44u)'
*
* Resistance calculation including temperature effects
+ pdeltat= 'temper-25+dtemp'
+ rmidt  = 'k1rsf * (k1len+k1dlf) / k1wdth / 2'
+ rmid   = 'rmidt * (1 + k1rstc*pdeltat)'
+ rend   = '1u*(exp(k1renf)-10) / k1wdth'
+ prtot  = '2 * (rmid + rend)'
*
* Calculate area, perimeter for capacitance
* Subtract delta w, delta l to obtain drawn dimensions,
* Then include region outside of contacts
+ k1capperi  = '2*((k1len + 2*k1endf) + (k1wdth-k1dwn))'
+ k1caparea = '(k1len + 2*k1endf) * (k1wdth-k1dwn)'
*
* Partition capacitance area, perimeter
+ ak1xc = 'k1caparea / 3'
+ pk1xc = 'k1capperi / 3'
*
* Mis-match Calculation
+ pk1ms   = 'k1ms * k1ms / (k1len / k1wdth)'
+ pk1ml   = 'k1ml * k1ml / (k1len * k1len * 1e12)'
+ pk1mw   = 'k1mw * k1mw / (k1wdth * k1wdth * 1e12)'
+ k13sig = '0.01 * sqrt(pk1ms + pk1ml + pk1mw)'
+ k1mm   = 'k13sig * 0.7071 / sqrt(s * pbar * par)'
+ mmres  = agauss(0,1,3)
+ mmatr  = '1 + (k1mm * mmres)'
*
*  The voltage coefficients take into effect self-heating
+ usesh = '((gsh==1)&&(sh==1))||(gsh==2)'    $ self-heating switch
+ k1psh = 'usesh*74.0 / (prtot*s*s) / exp(.78*log(w*plnom*1e12))'
*
* Flicker Noise
+ lnoi = 'k1len - k1dlf'
+ wnoi = 'k1wdth - k1dwf'
+ k1 = 'exp(log(6e-25)+dnoik1*log(2))*(exp(1.3*log(wnoi/lnoi)))*(prtot/rmid)*(prtot/rmid)/(s*pbar*par)'
*
* Resistor network
rea  in 1          r='rend*mmatr*s/pbar' tc1=k1rntc  dtemp=dtemp
rma  1  2   resnoi r='rmid*mmatr*s/pbar/(1 + k1psh*v(in,out)*v(in,out))' 
rmb  2  3          r='rmid*mmatr*s/pbar/(1 + k1psh*v(in,out)*v(in,out))'  
reb  3  out        r='rend*mmatr*s/pbar' tc1=k1rntc  dtemp=dtemp
*
capa  6   1   c='(  (ak1xc*ck1s + pk1xc*ck1sf)/2)*s*pbar'
capb  6   2   c='(2*(ak1xc*ck1s + pk1xc*ck1sf)  )*s*pbar'
capc  6   3   c='(  (ak1xc*ck1s + pk1xc*ck1sf)/2)*s*pbar'
*
rsb   6  sx   r=rsx
*
.model resnoi r noise=1 kf=k1 af=2 lf=0 wf=2 ef=1 dw=0u dlr=0u l=lnoi w=wnoi
*
.ends k1res
