
# Homebrew 5.7GHz XVTR with relatively cheap WiFi components

Original intention was to make a 6cm XVTR for roving application driving from an IC705, however this one is now in use for EME, with an additional 50W SSPA and a DU3T CLNA.
The first design was on a 2 layer JLCPCB teflon substrate, the latest version was done together with Rens PA3AXA, on double sided FR4.
Although the XVTR itself is ready, the roving station is not yet build.


# Quick indicative reference data

 - IF: 432MHz 27dBm
 - RX: Nf 1.5dB, G 36dB
 - TX: 27dBm
 - DC: 8V RX 500mA, TX no drive 600mA, TX full drive 1000mA
 - REF: Internal 40MHz TCXO: stable enough for EME, but optional external Ref e.g. 10MHz
  

# Basic circuit description

RX: LNA QPL9504 followed by gain stage TQP369184. In the first design a SKY65404 was used as LNA but never the published figures were met.
TX: TQP369184, dielectric BPF and SSPA SE5004L
MIXER: one combined pad for both TX and RX: switch RF SKY13446, dielectric BPF, mixer HCM218B, switch IF AS179
LO: 40MHz TCXO, STuW81300 synthesizer (this is e.o.l. but still available at most suppliers), TQP369184
DC: Some stabilisers and PMOS switches, switching logic and ATtiny412 as controller for the synthesizer
Some options: RF vox, Bias-T power input and 12V/24V RX/TX det


# BOM

Component BOM ~90Euro incl. VAT. Excluding PCB, housing and SMA's
PCB: 5 pieces for 5.95USD at JLCPCB 


# Building

Most components are reflow technology with QFN packages and 0603 SMD's. So unless there is some experience with soldering these type of components it is not for the average amateur.
Having a heatplate eases the soldering much, however we experienced the 4 layer FR4 more difficult to solder as the heat transfer is much higher.
As still some "exotic" keycomponents are used, is the design not really optimised for JLCPCB assembly, unless you are happy with only SMD R and C.



73's Maarten PA0MHE