* Path, Component, Release: cmrf7sf/rel/HSPICE/models/esdpsh_base.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
************************************************************************************
*
*   Licensed Materials
************************************************************************************
* ESD pMOSFETs calling model (including all flavors of thin/thick oxide)

.subckt esdpsh_base (d g s b)  wesd=1u lesd=1u esdoxide=1 nf=1 ldop=4.0u lsop=0.48u gns=0 

 xesdnsh_spe   (d g s b)  esdpsh_spe wesd=wesd lesd=lesd nf=nf ldop=ldop lsop=lsop esdoxide=esdoxide gns=gns esd_event=esd_event esd_exit=esd_exit

.ends esdpsh_base
