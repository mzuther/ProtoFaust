/* ----------------------------------------------------------------------------

   Prototype
   =========
   Faust prototyping for VCV Rack

   Copyright (c) 2019 Martin Zuther (http://www.mzuther.de/)

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

---------------------------------------------------------------------------- */

import("stdfaust.lib");


main_group(x) = vgroup("Prototype", x);

button_group(x) = main_group(hgroup("[2] Buttons", x));

button_1 = button_group(vslider("1 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
button_2 = button_group(vslider("2 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
button_3 = button_group(vslider("3 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
button_4 = button_group(vslider("4 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
button_5 = button_group(vslider("5 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
button_6 = button_group(vslider("6 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
button_7 = button_group(vslider("7 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
button_8 = button_group(vslider("8 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;

knob_group(x) = main_group(hgroup("[1] Knobs", x));

knob_1 = knob_group(vslider("1 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
knob_2 = knob_group(vslider("2 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
knob_3 = knob_group(vslider("3 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
knob_4 = knob_group(vslider("4 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
knob_5 = knob_group(vslider("5 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
knob_6 = knob_group(vslider("6 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
knob_7 = knob_group(vslider("7 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
knob_8 = knob_group(vslider("8 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;

led_group(x) = main_group(hgroup("[3] Lights", x));

led_1_r = led_group(vbargraph("1 Red [style:led]" , 0 , 1)) : _;
led_1_g = led_group(vbargraph("1 Green [style:led]" , 0 , 1)) : _;
led_1_b = led_group(vbargraph("1 Blue [style:led]" , 0 , 1)) : _;

led_2_r = led_group(vbargraph("2 Red [style:led]" , 0 , 1)) : _;
led_2_g = led_group(vbargraph("2 Green [style:led]" , 0 , 1)) : _;
led_2_b = led_group(vbargraph("2 Blue [style:led]" , 0 , 1)) : _;

led_3_r = led_group(vbargraph("3 Red [style:led]" , 0 , 1)) : _;
led_3_g = led_group(vbargraph("3 Green [style:led]" , 0 , 1)) : _;
led_3_b = led_group(vbargraph("3 Blue [style:led]" , 0 , 1)) : _;

led_4_r = led_group(vbargraph("4 Red [style:led]" , 0 , 1)) : _;
led_4_g = led_group(vbargraph("4 Green [style:led]" , 0 , 1)) : _;
led_4_b = led_group(vbargraph("4 Blue [style:led]" , 0 , 1)) : _;

led_5_r = led_group(vbargraph("5 Red [style:led]" , 0 , 1)) : _;
led_5_g = led_group(vbargraph("5 Green [style:led]" , 0 , 1)) : _;
led_5_b = led_group(vbargraph("5 Blue [style:led]" , 0 , 1)) : _;

led_6_r = led_group(vbargraph("6 Red [style:led]" , 0 , 1)) : _;
led_6_g = led_group(vbargraph("6 Green [style:led]" , 0 , 1)) : _;
led_6_b = led_group(vbargraph("6 Blue [style:led]" , 0 , 1)) : _;

led_7_r = led_group(vbargraph("7 Red [style:led]" , 0 , 1)) : _;
led_7_g = led_group(vbargraph("7 Green [style:led]" , 0 , 1)) : _;
led_7_b = led_group(vbargraph("7 Blue [style:led]" , 0 , 1)) : _;

led_8_r = led_group(vbargraph("8 Red [style:led]" , 0 , 1)) : _;
led_8_g = led_group(vbargraph("8 Green [style:led]" , 0 , 1)) : _;
led_8_b = led_group(vbargraph("8 Blue [style:led]" , 0 , 1)) : _;
