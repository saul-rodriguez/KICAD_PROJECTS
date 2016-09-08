* Path, Component, Release: cmrf7sf/relAM/HSPICE/models/bondpad.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
*
*>  CMRF7SF  bondpad  Analog Metal (AM) Bondpad over BB, PC or HR groundplane
*
***************************************************************************
*
*                                   in
*  Cox represents oxide capacitance  o
*  between the AM bondpad and the    |-----------+
*  groundplane.                      |           |
*                             Cox1 -----  Cox2 -----
*                                  -----       -----
*                                    |           |
*                          Cgp2      |           |
*                     +___||___+     |           |
*                     |   ||   |     |           |
*                     |        |     |           |
*                 +---+-/\/\/\/+---- | ----------+ 2
*                 |     Rgp2         |           |
*                 |                  |           |
*          gp  o--+---+-/\/\/\/+-----+ 1         |
*                     | Rgp1   |     |           |
*                     |        |     |           |
*                     +___||___+     |           |
*                         ||         |           |
*    Rgp and Cgp           Cgp1      |           |
*    represent the                   |           |  Rsb is set to a high
*    BB or PC groundplane            |           |  value (1GOhm) to
*    resistance and capacitance      \           \  effectively remove this
*                                    /           /  node from the circuit.
*                               Rsb1 \      Rsb2 \  This node is provided
*                                    /           /  for compatibility with
*                                    |           |  bondpad model topologies
*                                    +-----------+  from BiCMOS technologies.
*                                          |
*                                          |
*                                          o sx (dummy node for compatibility)
*
*  All elements (Cox, Cgp, Rgp) are distributed in order to account
*  for high frequency effects.
********************************************************************************
*
*  DIMENSIONS: W, L = Design width, length of AM bondpad
*
*  SYNTAX:     Specify both width and length:
*              xxx  in gp sx  bondpad (w=70u  l=100u)
*
*      OR:     Specify length only (width default = -1 for square bondpad)
*              xxx  in gp sx  bondpad (l=100u)
*
*      OR:     Specify both area and perimeter:
*              xxx  in gp sx  bondpad (area=10n  perim=400u)
*
*  OPTIONAL:   nlev  --> Indicates number of metal levels including AM.
*                        Possible values = 3, 4, 5, 6, or 7.  (default, nlev=3)
*
*              rect  --> Flag to select rectangular (default, rect=1) or
*                        octagonal (rect=-1) bondpad shape.
*
*              grnd  --> Indicator for grounding scheme under bondpad,
*                        Default= -1 (BB) or specify -2 (PC) or -5 (HR)
*
*              dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*  EXAMPLES:
*
*
*   For rectangular bondpad with AM = 5th level over BB:
*       x1  in gp sx  bondpad  l=100u  w=70u  nlev=5
*
*
*   For symmetrical octagonal bondpad with AM = 6th level over PC:
*       x1  in gp sx  bondpad  l=100u  grnd=-2 rect=-1  nlev=6
*                               ____________
*                             /              \      /|\
*                            /                \      |
*                           /                  \     |
*                          |                    |
*                          |     AM Bondpad     | W=100um
*                          |                    |
*                           \                  /     |
*                            \                /      |
*                             \______________/      \|/
*                          <----  L=100um  ----->
*
*
*   For asymmetrical octagonal (rectangular with beveled corners)
*       with AM = 4th level over BB:
*       x1  in gp sx  bondpad  l=100u  w=70u  rect=-1
*                              ______________
*                            /                \     /|\
*                           /                  \     |
*                          |                    |
*                          |     AM Bondpad     | W=70um
*                           \                  /     |
*                            \________________/     \|/
*                          <----  L=100um  ----->
*
*******************************************************************************
*
* NOTES:
*
*  1. Either length and width or area and perimeter must be specified in
*     order to get a valid result. Otherwise, the internal oxide capacitance
*     will be set to zero.
*
*     When specifying area and perimeter, the statistical variation and metal
*     bias of the width and length of the bondpad will not be calculated.
*
*  2. This model provides a terminal for the groundplane connection.
*     For BB version (grnd=-1), this connection represents a substrate
*      contact that connects to the substrate underneath the bondpad.  This
*      connection would be connected to the same potential as all other
*      substrate contacts in a design.
*     For HR version (grnd=-5), this connection represents a substrate
*      contact that connects to the High Resistivity substrate underneath the
*      bondpad.  This connection would be connected to the same potential as
*      all other substrate contacts in a design.
*     For PC version (grnd=-2), this connection represents a PC
*      contact that connects to the PC layer underneath the bondpad.
*      This connection should be tied to any "quiet" AC ground.
*
*  3. For a PC bondpad, the groundplane resistance is nominally 8 ohms/sq.
*     Note that the groundplane resistance gets distributed into Rgp1 and Rgp2
*     to improve model accuracy at high frequencies.
*
*  4. For a BB or HR bondpad, the substrate resistance scales with the area of
*     the bondpad and its value is extracted from fitting the model to measured
*     hardware.
*
*  5. The series resistance, Rsb, is set to a very high value in order to
*     remove the "dummy" node from the circuit.  This node is provided for
*     topology compatability between CMOS and BiCMOS technologies.  BiCMOS
*     technologies generally include an NS groundplane option that requires
*     use of this third outside node.
*
*
*******************************************************************************
.subckt bondpad  ( in gp sx )
+ l=-1u w=-1u area=-1p perim=-1p  nlev=4 rect=1 grnd=-1 dtemp=0
*
.param
* Calculate # Sides
+ rbp  = '(rect==1)'                            $ rectangular
+ obp  = '(rect==-1)'                           $ octagonal
+ pn   = '(rbp*4 + obp*8)'                      $ number of sides
*
* Set width for square or rectangular pad
+ pwpp = '((w*1e6>0)*w + (w*1e6<=0)*l)'         $ w=l if w is not given
*
* Check to see if length is less than width
+ pw   = '(min(pwpp,l)+delam)'                  $ net width
+ pl   = '(max(pwpp,l)+delam)'                  $ net length
*
* Calculate appropriate area and perimeter depending on geometry
+ sbp    = '(pw*(rbp + obp*(2**0.5 -1)))'       $ length of one side
+ areap  = '((rbp + obp*4.82843)*sbp**2)'
+ parea  = '((l*1e6>0)*(areap+(pl-pw)*pw) + (l*1e6<=0)*(area>0)*area)'
+ pperim = '((l*1e6>0)*(pn*sbp+2*(pl-pw)) + (l*1e6<=0)*(perim*1e6>0)*perim)'
*
* Calculate the stack height to groundplane from the bondpad
+ h        = '(oppcstif+oppcthk)*(grnd!=-2)+capct+m1t+(nlev>3)*(m1m2t+m2t)+(nlev>4)*(m2m3t+m3t)+(nlev>5)*(m3m4t+m4t)+(nlev>6)*(m4m5t+m5t)+(mxmtt)*(nlev>3)+(m1m2t)*(nlev==3)+mtt+mtamt'
*
* Calculate effective stack height reduction due to M1 fill
+ m1flfrac = 0.089
+ m1dt     = '-2*m1flfrac*m1t'
*
* Calculate effective stack heigh reduction due to RX fill
+ rxflfrac = 0.45
+ rxdt     = '-2*rxflfrac*oppcstif'
*
* Calculate total effective stack height delta
+ totdt    = 'm1dt+rxdt*(grnd==-1)'
*
* Calculate effective stack height
+ heffec   = 'h+totdt'
*
* Calculate area and perimeter capacitance
+ pcams  = 'e0*4.217/heffec'
+ pcamsf = 'e0*4.217*(2*0.697/(pi-2)*log(pi/2)+2*1.271/pi*log(1+amt/heffec))'
*
* Calculate AM to substrate oxide and silicon capacitance
+ pcox = '(pcams*parea + pcamsf*pperim)'
+ csx  = '((grnd>-5)+(grnd==-5)*2)*(2.143e-6*parea)'
*
* Select appropriate resistance parameters for groundplane
+ prho  = '(grnd==-1)*rsub+(grnd==-5)*rsubhr'
+ rsxgp = 'e0*ersi*prho/csx'
+ gpres = '((grnd==-1)*813.9+(grnd==-2)*pcrsi)*(1/3)*pl/pw+(grnd==-5)*rsxgp'
+ tgp   = '((grnd==-1)*trsub+(grnd==-2)*tpcrsi)'
+ rsx   = 1e9
*
* Subcircuit network
cox1  in 1   c='0.5*pcox'                         dtemp=dtemp
cox2  in 2   c='0.5*pcox'                         dtemp=dtemp
cgp1  gp 1   c='0.5*csx'                          dtemp=dtemp
cgp2  gp 2   c='((grnd>-5)*2+(grnd==-5)*0.5)*csx' dtemp=dtemp
rgp1  gp 1   r='(((grnd==-1)+(grnd==-2))*0.5 + (grnd==-5)*2)*gpres'  tc1=tgp  dtemp=dtemp
rgp2  gp 2   r='2*gpres'         tc1=tgp          dtemp=dtemp
rsb1  sx 1   r='rsx*2'
rsb2  sx 2   r='rsx*2'

.ends bondpad
