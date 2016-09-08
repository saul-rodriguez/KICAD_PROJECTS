* Path, Component, Release: cmhv7sf/rel/HSPICE/models/esdpsh_base.inc, 7hv_models, mod_cmhv7sf
* CMVC Revision: 3.0
************************************************************************************
*
************************************************************************************
* 
* ESD pMOSFETs model 
* Please note this release enables only esdpfet (1.8V gate silicided) and esdpfetm (5.0V gate-silicided) models.
*  esdpfet  (esdoxide=1, gns=0)
*  esdpfetm (esdoxide=4, gns=0)

.subckt esdpsh_base (d g s b)  wesd=1u lesd=1u esdoxide=1 nf=1 ldop=2.0u lsop=0.48u gns=0 

 xesdpsh_base_va   (d g s b)  esdpsh_base_va wesd=wesd lesd=lesd nf=nf ldop=ldop lsop=lsop esdoxide=esdoxide gns=gns esd_event=esd_event esd_exit=esd_exit

.ends esdpsh_base
