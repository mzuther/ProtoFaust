import("stdfaust.lib");
eurorack = component("eurorack.dsp");


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


vco(i_cv_pitch , btn) = internal_vco
with
{
  freq = i_cv_pitch : eurorack.i_cv_pitch2freq : _;
  internal_vco = ba.if(btn > 0 , (freq : os.oscws) , (freq : os.saw2)) : _;
};


voices(i_cv_pitch_1 , i_cv_pitch_2) = internal_voices
with
{
  i_cv_pitch_added_1 = knob_1 , 0.5 : - : si.smooth(1e-3) : _;
  i_cv_pitch_added_2 = knob_2 , 0.5 : - : si.smooth(1e-3) : _;

  i_cv_pitch_final_1 = i_cv_pitch_1 , i_cv_pitch_added_1 : + : _;
  i_cv_pitch_final_2 = i_cv_pitch_2 , i_cv_pitch_added_2 : + : _;

  voice(i_cv_pitch , btn , pan) = i_cv_pitch , btn : 1 , vco : pan , vca : sp.panner : _ , _;
  mix(a1 , b1 , a2 , b2) = a1 + a2 , b1 + b2 : _ , _;

  internal_voices = i_cv_pitch_final_1 , button_1 , 0 , i_cv_pitch_final_2 , button_2 , 1 : voice , voice : mix : _ , _;
};


process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
with
{
  lfo_1 = 1 , os.osccos(0.5) : + , 2 : / : _;
  lfo_2 = 1 - lfo_1 : _;

  attacher = _ :
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

             attach(_ , lfo_1 : led_1) :
             attach(_ , lfo_2 : led_2) :
             attach(_ , lfo_1 : led_3) :
             attach(_ , lfo_2 : led_4) :
             attach(_ , lfo_1 : led_5) :
             attach(_ , lfo_2 : led_6) :
             attach(_ , lfo_1 : led_7) :
             attach(_ , lfo_2 : led_8) :
             _;

  internal_processor = (in1 : attacher) , in2 : voices : _ , _ , in3 , in4 , in5 , in6 , in7 , in8 : si.bus(8);
};
