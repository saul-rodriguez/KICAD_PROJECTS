* Path, Component, Release: cmhv7sf/rel/HSPICE/models/oppdires.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  oppdires    P+ S/D Resistor over HV well
*
***********************************************************************
*
*                                  Ropp
*
*                        (in)  o--/\/\/\--o  (out)
*                                    |        
*                                    o (dn)              
*                                    |        
*                                    |
*                                  ----
*                                   /\  Ddnx
*                                  /  \ 
*                                  ----
*                                    |
*                                    |
*                                    o (sx) 
*
***********************************************************************
*
*  DIMENSIONS: W = Design width  of RX
*              L = Design length of OP
*
*  SYNTAX:     Specify both width and length:
*              xxx  in out dn sx  oppdires (w=2u  l=5u)
*
*       OR     Specify width and resistance:
*              xxx  in out dn sx  oppdires (w=2u  r=250)
*
*  SERIES:        s  --> Defined model parameter,  Reff = Rbar * s
*
*  PARALLEL: m (par) --> Multiplicity parameters,  Reff = Rbar / m (par)
*
*              pbar  --> Defined model parameter,  Reff = Rbar
*
*              est   --> Include estimated parasitic diode capacitance
*                        (default, est=1). Turn switch off (est=0) for
*                        extracted layout.
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*                rsx --> Fixed nwell resistance, default = 50 ohm.
*
*              vdnsx --> DN/SX max voltage option (50V or 120V)
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
*  3. The well node (dn) should be tied to the most positive power supply
*     in the circuit. The value of the resistor will be modulated by the
*     voltage on the well node according to the voltage coefficient.
*
*                                
***********************************************************************
.subckt oppdires  in out dn sx  w=2u l=-1u r=-1 s=1 par=1 pbar=1 dtemp=0
+                               est=1 rsx=50 vdnsx=50

.param
*
* Calculate op length, assumes w,r and groundrule spacings for contacts
+ rendn = '1u*(exp(oppdrenn) - 10)'
+ pleqn = '((r*pbar*(w+oppddwn) - 2*rendn) / oppdrsn) - oppddln'
*
* Select op length, user input takes precedence over calculated length
+ plnom = 'max(l,0) + ((l-abs(l))/(2*l))*pleqn'
*
* Calculate area, perimeter for capacitance
* Subtract delta w, delta l to obtain drawn dimensions,
* Then include region outside of op mask
+ opcaplen  = '2 * ((plnom-oppddln) + 2*opendf + (w-oppddwn))'
+ opcaparea = '((plnom-oppddln) + 2*opendf) * (w-oppddwn)'
*
* Resistor network
xropp  in out dn  oppdres  w=w l=l r=r s=s par=par pbar=pbar dtemp=dtemp rsx=rsx
xddnx  sx dn  diodednsx  area='max(0.01f,(opcaparea*s*pbar)*est)'  perimeter='max(0.01f,(opcaplen*s*pbar)*est)' vdnsx=vdnsx

.ends oppdires
