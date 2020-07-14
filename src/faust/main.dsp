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
import("gui.dsp");

rack = component("rack.dsp");


vca(i_cv , in) = internal_vca
with
{
  gain = max(0 , i_cv);

  internal_vca = gain * in;
};


vco(i_cv_pitch , btn) = internal_vco
with
{
  freq = i_cv_pitch :
         rack.i_cv_pitch2freq;

  internal_vco = freq <:
                 os.saw2 , os.square , os.triangle :
                 ba.selectn(3 , btn);
};


vcf(i_cv_cutoff , i_cv_resonance , btn , in) = internal_vcf
with
{
  cutoff = i_cv_cutoff * 1.5 - 0.5 :
           rack.i_cv_pitch2freq;
  cutoff_limited = min(cutoff , ma.SR / 2);
  resonance = max(i_cv_resonance * 5 , 0.1);
  gain = 1;

  internal_vcf = cutoff_limited , resonance , gain , in <:
                 fi.resonhp , fi.resonlp :
                 ba.selectn(2 , btn);
};


voice(i_cv_pitch , volume, knob_coarse , knob_fine, btn_waveform) = internal_voice
with
{
  i_cv_pitch_coarse = int(knob_coarse * 48 - 12) / 60;
  i_cv_pitch_fine = (knob_fine - 0.5) / 30;
  i_cv_pitch_final = i_cv_pitch + (i_cv_pitch_coarse + i_cv_pitch_fine : si.smooth(1e-3));

  internal_voice = i_cv_pitch_final , btn_waveform :
                   volume , vco :
                   vca;
};


voices(i_cv_pitch , i_cv_cutoff , i_cv_resonance) = internal_voices
with
{
  volume = -18 : ba.db2linear;

  voice_1 = voice(i_cv_pitch , volume , knob_1 , knob_2 , button_1 * 2);
  voice_2 = voice(i_cv_pitch , volume , knob_3 , knob_4 , button_2 * 2);
  voice_3 = voice(i_cv_pitch , volume , knob_5 , knob_6 , button_3 * 2 + 1);

  i_cv_cutoff_final = i_cv_cutoff + (knob_7 : si.smooth(1e-3));
  i_cv_resonance_final = i_cv_resonance + (knob_8 : si.smooth(1e-3));

  internal_voices = voice_1 + voice_2 + voice_3 :
                    i_cv_cutoff_final , i_cv_resonance_final , button_4 * 2 , _ : vcf :
                    0.3 , 0.1 , _ : ef.cubicnl :
                    fi.dcblocker;
};


process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
with
{
  lfo_1 = (os.osccos(0.5) + 1) / 2;
  lfo_2 = 1 - lfo_1;

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

  internal_processor = (in1 : gui_attacher) , in2 , in3 :
                       voices :
                       _ , in2 , in3 , in4 , in5 , in6 , in7 , in8 :
                       si.bus(8);
};
