* Path, Component, Release: cmrf7sf/rel/HSPICE/models/wafer.inc, rf7sf_models, mod_cmrf7sf
* CMVC Revision: 2.0
*
* *****************************************************************************
*
*>  CMRF7SF    User input file for wafer-specific overrides using
*                  inline kerf (PCM) parametric measurement data
*
*
* *****************************************************************************
*
* Wafer-specific overrides for a subset of model / process parameters are
* available and may be used to aid in the correlation of circuit level
* simulation to hardware measurements on prototype parts. These first-order
* parameters are defined using a minimal number of measurements on the inline
* kerf (PCM) monitors.
*
* Notes and Definitions:
*
*   k_wafer		Switch to enable (1) or disable (0) use of the
*                       wafer-specific override parameters
*
*   Use of this wafer-specific methodology and corner analysis is mutually
*   exclusive. All corner parameter inputs are ignored when the k_wafer switch
*   is enabled (k_wafer=1). Likewise, when the k_wafer switch is turned off
*   (k_wafer=0), the wafer-specific parameter inputs are ignored in favor of
*   any corner parameter values.
*
*   Enter parameter values as shown in the wafer snapshot of interest. The
*   defaults given here correspond to the expected nominal (target) values.
*
* ****************************************************************************
*
.param
+ k_wafer = 0              $ Switch to activate wafer specific parameters
*
+ k_ntoxinv   = 4.45       $ NFET Tox, default = 4.45nm
+ k_nfetidsat = 600        $ NFET Idsat, default = 600 uA/um
+ k_nfetvtlin = 0.355      $ NFET Vtlin, default = 0.355 V
+ k_nfetidlin = 77.5       $ NFET Idlin, default = 77.5 uA/um
+ k_nfetcolap = 0.33       $ NFET Overlap Cap, default = 0.33 fF/um
+ k_narea     = 0.85       $ NFET Junction Area Cap, default = 0.85 fF/um^2
*
+ k_pfetidsat = -260       $ PFET Idsat, default = -260 uA/um
+ k_pfetvtlin = -0.420     $ PFET Vtlin, default = -0.420 V
+ k_pfetidlin = -20.5      $ PFET Idlin, default = -20.5 uA/um
+ k_pfetcolap = 0.35       $ PFET Overlap Cap, default = 0.35 fF/um
+ k_parea     = 1.15       $ PFET Junction Area Cap, default = 1.15 fF/um^2
*
+ k_thickntoxinv   = 7.9       $ 3.3V NFET Tox, default = 7.9nm
+ k_thicknfetidsat = 575       $ 3.3V NFET Idsat, default = 575 uA/um
+ k_thicknfetvtlin = 0.660     $ 3.3V NFET Vtlin, default = 0.660 V
*
+ k_thickpfetidsat = -225      $ 3.3V PFET Idsat, default = -225 uA/um
+ k_thickpfetvtlin = -0.730    $ 3.3V PFET Vtlin, default = -0.730 V
*
+ k_5vnfetidsat = 630          $ 5V NFET Idsat, default = 630 uA/um
+ k_5vnfetvtlin = 0.625        $ 5V NFET Vtlin, default = 0.625 V
*
+ k_5vptoxinv   = 12.7         $ 5V PFET Tox, default = 12.7nm
+ k_5vpfetidsat = -315         $ 5V PFET Idsat, default = -315 uA/um
+ k_5vpfetvtlin = -0.650       $ 5V PFET Vtlin, default = -0.650 V
*
+ k_highvtnfetidsat = 500      $ High-Vt NFET Idsat, default = 500 uA/um
+ k_highvtnfetvtlin = 0.525    $ High-Vt NFET Vtlin, default = 0.525 V
*
+ k_highvtpfetidsat = -210     $ High-Vt PFET Idsat, default = -210 uA/um
+ k_highvtpfetvtlin = -0.520   $ High-Vt PFET Vtlin, default = -0.520 V
*
+ k_zvtthinvtlin = -0.040      $ Thin ZVT NFET Vtlin, default = -0.040 V
+ k_zvtthickvtlin = 0.005      $ Thick ZVT NFET Vtlin, default = 0.005 V
*
+ k_opndifrs = 72          $ N+ S/D Resistor Rs, default = 72 ohm/sq
+ k_oppdifrs = 105         $ P+ S/D Resistor Rs, default = 105 ohm/sq
+ k_ppcrs    = 260         $ P+ Poly Resistor Rs, default = 260 ohm/sq
+ k_rprs     = 165         $ RP Poly Resistor Rs, default = 165 ohm/sq
+ k_rrrs     = 1600        $ RR Poly Resistor Rs, default = 1600 ohm/sq
+ k_k1rs     = 61          $ K1 BEOL Resistor Rs, default = 61 ohm/sq
+ k_nwellrs  = 360         $ NWell Rs, default = 360 ohm/sq
*
+ k_havarcarea = 2.45      $ HA Varactor Capacitance, default = 2.45 fF/um^2
*
+ k_sbdvf = 0.335          $ SBD Forward Voltage, default = 0.335 V
*
+ k_ncmimcarea   = 2.05     $ Single Nitride MIM Cap, default = 2.05 fF/um^2
+ k_dncmimcarea  = 4.1      $ Dual Nitride MIM Cap, default = 4.1 fF/um^2
+ k_hikcmimcarea = 4.1      $ Hi-K MIM Cap, default = 4.1 fF/um^2
*
+ k_mtrs = 0.089           $ MT Rs, default = 0.089 ohm/sq
+ k_mzrs = 0.069           $ MZ Rs, default = 0.069 ohm/sq
+ k_mlrs = 0.014           $ ML Rs, default = 0.014 ohm/sq
+ k_am_mars = 0.007        $ AM (or MA) Rs, default = 0.007 ohm/sq
