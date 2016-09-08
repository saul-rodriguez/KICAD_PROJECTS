* Path, Component, Release: cmos7base/rel/HSPICE/models/subc.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  subc         Substrate Contact
*
*******************************************************************************
*
*  A single resistor is used to simulate a substrate contact.
*
*                                  Rsubc
*                          in  o--/\/\/\/--o  out
*
*
*  SYNTAX:     Specify both width and length:
*              xxx  in out  subc (w=1u  l=2u)
*
*  OPTIONAL:   dtemp --> Device temperature difference with respect to
*                        the simulated circuit temperature (deg C).
*
*  NOTES:
*
*  1. If the substrate contact length is NOT provided, then the
*     length defaults to 0.8 microns.
*
*  2. If the substrate contact width is NOT provided, then the
*     width defaults to 0.8 microns.
*
*
*
*******************************************************************************
.subckt subc  in out  
+       l = 0.8u
+       w = 0.8u
+   dtemp = 0
*
  r1  in out  r='rsubc/((l+delrx)*(w+delrx))'  tc1=trsubc  dtemp=dtemp
.ends  subc
