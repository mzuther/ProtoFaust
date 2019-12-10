ProtoFaust
==========

DSP prototyping in Faust for VCV Rack  
Copyright (c) 2019 [Martin Zuther][1]

![Screenshot of ProtoFaust](images/screenshot_1.png?raw=true "Screenshot")

Installation
------------

These are the instructions for Linux, but it should be relatively
simple to modify them for use on Windows or MacOS:

1. clone this repository: `git clone https://github.com/mzuther/ProtoFaust.git`
1. [download and install][2] the latest VCV Rack SDK
1. install Faust (I recommend using a [recent version][3])
1. `make run` will compile and install your module; Rack is run if it is found in your path


Prototype your own DSP
----------------------

The default Faust process is a simple three-oscillator synth with
resonant filter.  Simply edit `src/faust/main.dsp` to change this.
The main process is

```
process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
{
     internal_processor = ... ;
};
```

You can simply put your mono DSP process in there:

```
    internal_processor = (in1 : gui_attacher) :
                         your_mono_process :
                         _ , in2 , in3 , in4 , in5 , in6 , in7 , in8 :
                         si.bus(8);
```

Or in stereo:

```
    internal_processor = (in1 : gui_attacher) , in2 :
                         your_stereo_process :
                         _ , _ , in3 , in4 , in5 , in6 , in7 , in8 :
                         si.bus(8);
```

Just make sure that you add `gui_attacher` somewhere -- this will
attach the GUI parameters and simply copy any mono input signal to its
output.  If you fail to do so, the ` ProtoFaust` module will not find
any of the knobs, buttons and LEDs (they will be thought as
superfluous and optimized out) and probably crash.

Enjoy!


Ideas and bug fixes
-------------------

This module is very new and experimental.  So please send problems,
bug reports, fixes and any ideas that come to your mind.  Thanks!


[1]: http://www.mzuther.de/
[2]: https://vcvrack.com/manual/PluginDevelopmentTutorial.html
[3]: http://faust.grame.fr/doc/manual/index.html#compiling-and-installing-the-faust-compiler
