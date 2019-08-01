import("stdfaust.lib");
eurorack = component("eurorack.dsp");


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
  i_cv_pitch_added_1 = hslider(
                         "[1] V/oct 1 [style:knob]" ,
                         0 ,
                         -5 , 5 , 1 / 12) : eurorack.cv_pitch2internal : si.smooth(1e-3) : _;

  i_cv_pitch_added_2 = hslider(
                         "[2] V/oct 2 [style:knob]" ,
                         7 / 12 ,
                         -5 , 5 , 1 / 12) : eurorack.cv_pitch2internal : si.smooth(1e-3) : _;

  i_cv_pitch_final_1 = i_cv_pitch_1 , i_cv_pitch_added_1 : + : _;
  i_cv_pitch_final_2 = i_cv_pitch_2 , i_cv_pitch_added_2 : + : _;

  voice(i_cv_pitch , pan) = i_cv_pitch : 1 , vco : pan , vca : sp.panner : _ , _;
  mix(a1 , b1 , a2 , b2) = a1 + a2 , b1 + b2 : _ , _;

  internal_voices = i_cv_pitch_final_1 , 0 , i_cv_pitch_final_2 , 1 : voice , voice : mix : _ , _;
  //internal_voices = i_cv_pitch_final_1 , 0.5 : voice : _ , _;
};


process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
with
{
  lfo_1 = os.lf_squarewavepos(1) : _;
  led_1 = lfo_1 : vbargraph("[3] LED 1 [style:led]" , -1 , 1) : _;
  led_2 = 1 - lfo_1 : vbargraph("[4] LED 2 [style:led]" , -1 , 1) : _;

  attacher = _ : attach(_ , led_1) : attach(_ , led_2) : _;
  internal_processor = (in1 : attacher) , in2 : voices : _ , _ , in3 , in4 , in5 , in6 , in7 , in8 : si.bus(8);
};
