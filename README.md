# audiobook_controlbox
 A specific midi controler for simple audiobook controls.

 The main project folder contains everything you need to create a simple DAW controler mainly focused at audiobook recording.

 It gives the person recording simple controls over the transport STOP/PLAY, REC, REV and FWD.
 the marker button sends a blip out to be used with editing.

 the SAVE and QUIT buttons send out a simple keyboard combination (configuerd for mac atm, but that sould be easy enough to change to windows)

 The headphone in/out is a very simple passive implementation of a volume knob, just send in at full volume and ajust accordingly (subject to change)

Right now it is configuerd to work with ProTools over the M-audio midi cc commands, there are other implementations like HUI and MCU these need some work to function fully.

