import("stdfaust.lib");
eurorack = component("eurorack.dsp");


vca(cv , in) = internal_vca
with
{
  cv_limited = ba.if(cv > 0 , cv , 0) : _;
  gain = cv_limited , 10 : / : _;
  internal_vca = gain , in : * : _;
};


vco(v_oct) = internal_vco
with
{
  freq = v_oct : eurorack.volts2frequency : _;
  internal_vco = freq : os.oscws : _;
};


voices(v_oct1 , v_oct2) = internal_voices
with
{
  v_oct_added_1 = hslider(
                    "[1] V/oct 1 [style:knob]" ,
                    0 ,
                    -5 , 5 , 1 / 12) : si.smooth(1e-3) : _;

  v_oct_added_2 = hslider(
                    "[2] V/oct 2 [style:knob]" ,
                    7 / 12 ,
                    -5 , 5 , 1 / 12) : si.smooth(1e-3) : _;

  v_oct_final_1 = v_oct1 , v_oct_added_1 : + : _;
  v_oct_final_2 = v_oct2 , v_oct_added_2 : + : _;

  voice(v_oct , pan) = v_oct : 0.1 , vco : pan , vca : sp.panner : _ , _;
  mix(a1 , b1 , a2 , b2) = a1 + a2 , b1 + b2 : _ , _;

  internal_voices = v_oct_final_1 , 0 , v_oct_final_2 , 1 : voice , voice : mix : _ , _;
  //internal_voices = v_oct_final_1 , 0.5 : voice : _ , _;
};


process(in1 , in2 , in3 , in4 , in5 , in6 , in7 , in8) = internal_processor
with
{
  internal_processor = in1 , in2 : voices : _ , _ , in3 , in4 , in5 , in6 , in7 , in8 : si.bus(8);
};
