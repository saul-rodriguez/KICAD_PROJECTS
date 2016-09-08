* Path, Component, Release: cmhv7sf/rel/HSPICE/models/subc.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 2.0
*
*>  IBM CMHV7SF  subc         Substrate Contact
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
*     length defaults to 0.6 microns.
*
*  2. If the substrate contact width is NOT provided, then the
*     width defaults to 1.4 microns.
*
*
*
*******************************************************************************
.subckt subc  in out  
+       l = 0.6u
+       w = 1.4u
+   dtemp = 0
*
  r1  in out  r='rsubc/((l+delrx)*(w+delrx))'  tc1=trsubc  dtemp=dtemp
*
.ends subc
