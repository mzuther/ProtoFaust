# ProtoFaust

DSP prototyping in Faust for VCV Rack

![Screenshot of ProtoFaust](images/screenshot_1.png?raw=true "Screenshot")


## Installation

These are the instructions for Linux, but it should be relatively
simple to modify them for use on Windows or MacOS:

1. clone this repository: `git clone
   https://github.com/mzuther/ProtoFaust.git`

1. [download and install][SDK Rack] VCV Rack SDK **1.1.6** or a
   compatible version

   - the Makefile defaults to `../Rack-SDK` but respects the
     `RACK_DIR` shell variable

1. install Faust version **2.27.1** or later

   - I recommend using a [recent version][Faust compiler] of Faust

1. `make run` will compile and install your module

   - this will also run Rack if it is found in your path


## Prototype your own DSP

The default Faust process is a simple three-oscillator synth with
resonant filter.  Simply edit `src/faust/main.dsp` to change this.
The main process is

```
process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
with
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

Just make sure that you add `gui_attacher` somewhere – this will
attach the GUI parameters and simply copy any mono input signal to its
output.  If you fail to do so, the ` ProtoFaust` module will not find
any of the knobs, buttons and LEDs (they will be thought as
superfluous and optimized out) and probably crash.

Enjoy!


## Signal ranges

Input signals from VCV Rack are divided by `5.0`.  Conversely, output
signals are multiplied by `5.0` to bring them back in range.  This
keeps values in the usual range of DSP processing (`-1.0 .. +1.0`) and
should help when porting algorithms to VCV Rack.  All signals are
full-range, so you have to apply any input or output saturation
yourself.

Knobs have a range of `0.0 .. 1.0`; the center position is located at
`0.5`.  Toggle switches take on values of `0.0` and `1.0`, whereas
three-way switches add a third state of `0.5`.


## Ideas and bug fixes

This module is very new and experimental.  So please send problems,
bug reports, fixes and any ideas that come to your mind.  Thanks!


## Contributors

- [Martin Zuther][]: maintainer; code and GUI design

- [Stéphane Letz](https://github.com/sletz): optimization, improved
  readability of Faust code (`src/faust/rack.dsp`)


## Code of conduct

Please read the [code of conduct][COC] before asking for help, filing
bug reports or contributing to this project.  Thanks!


## License

Copyright (c) 2019-2020 [Martin Zuther][] and contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Thank you for using free software!


[Martin Zuther]:  http://www.mzuther.de/
[COC]:            https://github.com/mzuther/ProtoFaust/tree/master/CODE_OF_CONDUCT.markdown
[Faust compiler]: http://faust.grame.fr/doc/manual/index.html#compiling-and-installing-the-faust-compiler
[SDK Rack]:       https://vcvrack.com/manual/PluginDevelopmentTutorial.html
