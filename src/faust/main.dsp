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
import("prototype_gui.dsp");

rack = component("rack.dsp");


vca(i_cv , in) = internal_vca
with
{
  gain = ba.if(i_cv > 0 , i_cv , 0) : _;

  internal_vca = gain , in : * : _;
};


vco(i_cv_pitch , btn) = internal_vco
with
{
  freq = i_cv_pitch : rack.i_cv_pitch2freq : _;

  internal_vco = (freq : os.saw2) , (freq : os.square) , (freq : os.triangle) : ba.selectn(3 , btn) : _;
};


vcf(i_cv_cutoff , i_cv_resonance , in) = internal_vcf
with
{
  cutoff = i_cv_cutoff , 1.5 : * , 0.5 : - : rack.i_cv_pitch2freq , (ma.SR / 2) : min : _;
  resonance = i_cv_resonance , 10 : * , 0.1 : max : _;
  gain = 1;

  internal_vcf = cutoff , resonance , gain , in : fi.resonlp : _;
};


voices(i_cv_pitch) = internal_voices
with
{
  i_cv_pitch_coarse_1 = knob_1 , 48 : * , 12 : - : int , 60 : / : si.smooth(1e-3) : _;
  i_cv_pitch_fine_1 = knob_2 , 0.5 : - , 30 : / : si.smooth(1e-3) : _;

  i_cv_pitch_coarse_2 = knob_3 , 48 : * , 12 : - : int , 60 : / : si.smooth(1e-3) : _;
  i_cv_pitch_fine_2 = knob_4 , 0.5 : - , 30 : / : si.smooth(1e-3) : _;

  i_cv_pitch_coarse_3 = knob_5 , 48 : * , 12 : - : int , 60 : / : si.smooth(1e-3) : _;
  i_cv_pitch_fine_3 = knob_6 , 0.5 : - , 30 : / : si.smooth(1e-3) : _;

  i_cv_pitch_final_1 = i_cv_pitch , i_cv_pitch_coarse_1 : + , i_cv_pitch_fine_1 : + : _;
  i_cv_pitch_final_2 = i_cv_pitch , i_cv_pitch_coarse_2 : + , i_cv_pitch_fine_2 : + : _;
  i_cv_pitch_final_3 = i_cv_pitch , i_cv_pitch_coarse_3 : + , i_cv_pitch_fine_3 : + : _;

  i_cv_cutoff = knob_7 : si.smooth(1e-3) : _;
  i_cv_resonance = knob_8 : si.smooth(1e-3) : _;

  voice(i_cv_pitch , btn) = i_cv_pitch , btn : 1 , vco : vca : _;
  mix(a1 , a2 , a3) = a1 + a2 + a3 : _;

  internal_voices = (i_cv_pitch_final_1 , (button_1 , 2 : *) : voice),
                    (i_cv_pitch_final_2 , (button_2 , 2 : *) : voice) ,
                    (i_cv_pitch_final_3 , (button_3 , 2 : * , 1 : +) : voice) : mix :
                    i_cv_cutoff , i_cv_resonance , _ : vcf : _;
};


process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
with
{
  lfo_1 = 1 , os.osccos(0.5) : + , 2 : / : _;
  lfo_2 = 1 - lfo_1 : _;

  gui_attacher = _ :
                 attach(_ , button_1) :
                 attach(_ , button_2) :
                 attach(_ , button_3) :
                 attach(_ , button_4) :
                 attach(_ , button_5) :
                 attach(_ , button_6) :
                 attach(_ , button_7) :
                 attach(_ , button_8) :

                 attach(_ , knob_1) :
                 attach(_ , knob_2) :
                 attach(_ , knob_3) :
                 attach(_ , knob_4) :
                 attach(_ , knob_5) :
                 attach(_ , knob_6) :
                 attach(_ , knob_7) :
                 attach(_ , knob_8) :

                 attach(_ , lfo_1 : led_1_r) :
                 attach(_ , lfo_1 : led_1_g) :
                 attach(_ , lfo_1 : led_1_b) :

                 attach(_ , lfo_2 : led_2_r) :
                 attach(_ , 0 : led_2_g) :
                 attach(_ , 0 : led_2_b) :

                 attach(_ , lfo_1 : led_3_r) :
                 attach(_ , lfo_1 : led_3_g) :
                 attach(_ , lfo_1 : led_3_b) :

                 attach(_ , lfo_2 : led_4_r) :
                 attach(_ , 0 : led_4_g) :
                 attach(_ , 0 : led_4_b) :

                 attach(_ , lfo_1 : led_5_r) :
                 attach(_ , lfo_1 : led_5_g) :
                 attach(_ , lfo_1 : led_5_b) :

                 attach(_ , lfo_2 : led_6_r) :
                 attach(_ , 0 : led_6_g) :
                 attach(_ , 0 : led_6_b) :

                 attach(_ , lfo_1 : led_7_r) :
                 attach(_ , lfo_1 : led_7_g) :
                 attach(_ , lfo_1 : led_7_b) :

                 attach(_ , lfo_2 : led_8_r) :
                 attach(_ , 0 : led_8_g) :
                 attach(_ , 0 : led_8_b) :
                 _;

  internal_processor = in1 : gui_attacher : voices : _ , in2 , in3 , in4 , in5 , in6 , in7 , in8 : si.bus(8);
};
