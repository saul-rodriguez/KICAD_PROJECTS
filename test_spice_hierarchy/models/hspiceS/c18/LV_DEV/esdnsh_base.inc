* Path, Component, Release: cmrf7sf/rel/HSPICE/models/esdnsh_base.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
************************************************************************************
*
*   Licensed Materials
*
************************************************************************************
* ESD nMOSFETs model

.subckt esdnsh_base (d g s b)  wtesd=400u wesd=25u lesd=0.18u esdoxide=1 nf=1 ldop=1.0u lsop=0.48u gns=1

  xesdnsh_spe   (d g s b)  esdnsh_spe wtesd=wtesd wesd=wesd lesd=lesd nf=nf ldop=ldop lsop=lsop esdoxide=esdoxide gns=gns esd_event=esd_event esd_exit=esd_exit

.ends esdnsh_base
