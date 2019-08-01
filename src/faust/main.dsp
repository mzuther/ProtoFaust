import("stdfaust.lib");
eurorack = component("eurorack.dsp");


main_group(x) = vgroup("Prototype", x);

large_knob_group(x) = main_group(hgroup("[1] Knobs", x));

large_knob_1 = large_knob_group(vslider("1 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
large_knob_2 = large_knob_group(vslider("2 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
large_knob_3 = large_knob_group(vslider("3 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
large_knob_4 = large_knob_group(vslider("4 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
large_knob_5 = large_knob_group(vslider("5 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
large_knob_6 = large_knob_group(vslider("6 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
large_knob_7 = large_knob_group(vslider("7 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;
large_knob_8 = large_knob_group(vslider("8 [style:knob]" , 0.5 , 0 , 1 , 1e-3)) : _;

led_group(x) = main_group(hgroup("[2] Lights", x));

led_1 = led_group(vbargraph("1 [style:led]" , 0 , 1)) : _;
led_2 = led_group(vbargraph("2 [style:led]" , 0 , 1)) : _;
led_3 = led_group(vbargraph("3 [style:led]" , 0 , 1)) : _;
led_4 = led_group(vbargraph("4 [style:led]" , 0 , 1)) : _;
led_5 = led_group(vbargraph("5 [style:led]" , 0 , 1)) : _;
led_6 = led_group(vbargraph("6 [style:led]" , 0 , 1)) : _;
led_7 = led_group(vbargraph("7 [style:led]" , 0 , 1)) : _;
led_8 = led_group(vbargraph("8 [style:led]" , 0 , 1)) : _;

vca(i_cv , in) = internal_vca
with
{
  gain = ba.if(i_cv > 0 , i_cv , 0) : _;
  internal_vca = gain , in : * : _;
};


vco(i_cv_pitch) = internal_vco
with
{
  freq = i_cv_pitch : eurorack.i_cv_pitch2freq : _;
  internal_vco = freq : os.oscws : _;
};


voices(i_cv_pitch_1 , i_cv_pitch_2) = internal_voices
with
{
  i_cv_pitch_added_1 = large_knob_1 , 0.5 : - : si.smooth(1e-3) : _;
  i_cv_pitch_added_2 = large_knob_2 , 0.5 : - : si.smooth(1e-3) : _;

  i_cv_pitch_final_1 = i_cv_pitch_1 , i_cv_pitch_added_1 : + : _;
  i_cv_pitch_final_2 = i_cv_pitch_2 , i_cv_pitch_added_2 : + : _;

  voice(i_cv_pitch , pan) = i_cv_pitch : 1 , vco : pan , vca : sp.panner : _ , _;
  mix(a1 , b1 , a2 , b2) = a1 + a2 , b1 + b2 : _ , _;

  internal_voices = i_cv_pitch_final_1 , 0 , i_cv_pitch_final_2 , 1 : voice , voice : mix : _ , _;
};


process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
with
{
  lfo_1 = 1 , os.osccos(0.5) : + , 2 : / : _;
  lfo_2 = 1 - lfo_1 : _;

  attacher = _ : attach(_ , lfo_1 : led_1) :
                 attach(_ , lfo_2 : led_2) :
                 attach(_ , lfo_1 : led_3) :
                 attach(_ , lfo_2 : led_4) :
                 attach(_ , lfo_1 : led_5) :
                 attach(_ , lfo_2 : led_6) :
                 attach(_ , lfo_1 : led_7) :
                 attach(_ , lfo_2 : led_8) :

                 attach(_ , large_knob_1) :
                 attach(_ , large_knob_2) :
                 attach(_ , large_knob_3) :
                 attach(_ , large_knob_4) :
                 attach(_ , large_knob_5) :
                 attach(_ , large_knob_6) :
                 attach(_ , large_knob_7) :
                 attach(_ , large_knob_8) :
                 _;

  internal_processor = (in1 : attacher) , in2 : voices : _ , _ , in3 , in4 , in5 , in6 , in7 , in8 : si.bus(8);
};
