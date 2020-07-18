/* ----------------------------------------------------------------------------

   ProtoFaust
   ==========
   DSP prototyping in Faust for VCV Rack

   Copyright (c) 2019-2020 Martin Zuther (http://www.mzuther.de/) and
   contributors

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


main_group(x) = vgroup("ProtoFaust", x);

button_group(x) = main_group(hgroup("[2] Buttons", x));

button_1 = button_group(vslider("1 [style:knob][variant:switch-three-way]" , 0.5 , 0 , 1 , 1e-3));
button_2 = button_group(vslider("2 [style:knob][variant:switch-three-way]" , 0.5 , 0 , 1 , 1e-3));
button_3 = button_group(vslider("3 [style:knob][variant:switch-toggle   ]" , 0.5 , 0 , 1 , 1e-3));
button_4 = button_group(vslider("4 [style:knob][variant:switch-toggle   ]" , 0.5 , 0 , 1 , 1e-3));
button_5 = button_group(vslider("5 [style:knob][variant:switch-momentary]" , 0.5 , 0 , 1 , 1e-3));
button_6 = button_group(vslider("6 [style:knob][variant:switch-momentary]" , 0.5 , 0 , 1 , 1e-3));
button_7 = button_group(vslider("7 [style:knob][variant:switch-momentary]" , 0.5 , 0 , 1 , 1e-3));
button_8 = button_group(vslider("8 [style:knob][variant:switch-momentary]" , 0.5 , 0 , 1 , 1e-3));

knob_group(x) = main_group(hgroup("[1] Knobs", x));

knob_1 = knob_group(vslider("1 [style:knob][variant:knob-large-white]" , 0.5 , 0 , 1 , 1e-3));
knob_2 = knob_group(vslider("2 [style:knob][variant:knob-large-red  ]" , 0.5 , 0 , 1 , 1e-3));
knob_3 = knob_group(vslider("3 [style:knob][variant:knob-large-white]" , 0.5 , 0 , 1 , 1e-3));
knob_4 = knob_group(vslider("4 [style:knob][variant:knob-large-red  ]" , 0.5 , 0 , 1 , 1e-3));
knob_5 = knob_group(vslider("5 [style:knob][variant:knob-large-white]" , 0.5 , 0 , 1 , 1e-3));
knob_6 = knob_group(vslider("6 [style:knob][variant:knob-large-red  ]" , 0.5 , 0 , 1 , 1e-3));
knob_7 = knob_group(vslider("7 [style:knob][variant:knob-large-white]" , 0.5 , 0 , 1 , 1e-3));
knob_8 = knob_group(vslider("8 [style:knob][variant:knob-large-red  ]" , 0.5 , 0 , 1 , 1e-3));

led_group(x) = main_group(hgroup("[3] Lights", x));

led_1_r = led_group(vbargraph("1_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_1_g = led_group(vbargraph("1_Green [style:led][variant:led-rgb]" , 0 , 1));
led_1_b = led_group(vbargraph("1_Blue  [style:led][variant:led-rgb]" , 0 , 1));

led_2_r = led_group(vbargraph("2_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_2_g = led_group(vbargraph("2_Green [style:led][variant:led-rgb]" , 0 , 1));
led_2_b = led_group(vbargraph("2_Blue  [style:led][variant:led-rgb]" , 0 , 1));

led_3_r = led_group(vbargraph("3_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_3_g = led_group(vbargraph("3_Green [style:led][variant:led-rgb]" , 0 , 1));
led_3_b = led_group(vbargraph("3_Blue  [style:led][variant:led-rgb]" , 0 , 1));

led_4_r = led_group(vbargraph("4_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_4_g = led_group(vbargraph("4_Green [style:led][variant:led-rgb]" , 0 , 1));
led_4_b = led_group(vbargraph("4_Blue  [style:led][variant:led-rgb]" , 0 , 1));

led_5_r = led_group(vbargraph("5_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_5_g = led_group(vbargraph("5_Green [style:led][variant:led-rgb]" , 0 , 1));
led_5_b = led_group(vbargraph("5_Blue  [style:led][variant:led-rgb]" , 0 , 1));

led_6_r = led_group(vbargraph("6_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_6_g = led_group(vbargraph("6_Green [style:led][variant:led-rgb]" , 0 , 1));
led_6_b = led_group(vbargraph("6_Blue  [style:led][variant:led-rgb]" , 0 , 1));

led_7_r = led_group(vbargraph("7_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_7_g = led_group(vbargraph("7_Green [style:led][variant:led-rgb]" , 0 , 1));
led_7_b = led_group(vbargraph("7_Blue  [style:led][variant:led-rgb]" , 0 , 1));

led_8_r = led_group(vbargraph("8_Red   [style:led][variant:led-rgb]" , 0 , 1));
led_8_g = led_group(vbargraph("8_Green [style:led][variant:led-rgb]" , 0 , 1));
led_8_b = led_group(vbargraph("8_Blue  [style:led][variant:led-rgb]" , 0 , 1));
