* Path, Component, Release: cmos7base/rel/HSPICE/models/pcapc.inc, tech7_models, mod_cmos7base
* CMVC Revision: 2.0
*
*>  7RF/7WL  pcapc     Extracted parasitic capacitance model
*
***********************************************************************
*
*  Model can be used in conjunction with the design system extraction
*  program which calculates/combines passive wiring parasitic capacitance
*  per node.
*
*                  o  in
*                  |
*                  |
*                ----
*                             Capacitance multiplied by expected
*                ----         statistical process variation.
*                  |
*                  |
*                  o  out
*
***********************************************************************
*
*  SYNTAX:     Specify capacitance:
*              xxx  in out  pcapc  c=10p
*
*  NOTES:
*
*  1. Units for input capacitance parameter are farads.
*
*                                
***********************************************************************
*
.subckt pcapc  in out  c=1f

cpass  in out  'c * tpcap'

.ends pcapc
