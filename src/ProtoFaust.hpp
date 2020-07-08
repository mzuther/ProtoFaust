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


#include "plugin.hpp"

namespace faust
{
#include "faust_generated.cpp"
}


struct ProtoFaust : Module {
   enum ParamIds {
      BUTTON_1_PARAM,
      BUTTON_2_PARAM,
      BUTTON_3_PARAM,
      BUTTON_4_PARAM,
      BUTTON_5_PARAM,
      BUTTON_6_PARAM,
      BUTTON_7_PARAM,
      BUTTON_8_PARAM,

      KNOB_1_PARAM,
      KNOB_2_PARAM,
      KNOB_3_PARAM,
      KNOB_4_PARAM,
      KNOB_5_PARAM,
      KNOB_6_PARAM,
      KNOB_7_PARAM,
      KNOB_8_PARAM,

      NUM_PARAMS
   };

   enum InputIds {
      IN_1_INPUT,
      IN_2_INPUT,
      IN_3_INPUT,
      IN_4_INPUT,
      IN_5_INPUT,
      IN_6_INPUT,
      IN_7_INPUT,
      IN_8_INPUT,

      NUM_INPUTS
   };

   enum OutputIds {
      OUT_1_OUTPUT,
      OUT_2_OUTPUT,
      OUT_3_OUTPUT,
      OUT_4_OUTPUT,
      OUT_5_OUTPUT,
      OUT_6_OUTPUT,
      OUT_7_OUTPUT,
      OUT_8_OUTPUT,

      NUM_OUTPUTS
   };

   enum LightIds {
      LED_1_LIGHT_R,
      LED_1_LIGHT_G,
      LED_1_LIGHT_B,

      LED_2_LIGHT_R,
      LED_2_LIGHT_G,
      LED_2_LIGHT_B,

      LED_3_LIGHT_R,
      LED_3_LIGHT_G,
      LED_3_LIGHT_B,

      LED_4_LIGHT_R,
      LED_4_LIGHT_G,
      LED_4_LIGHT_B,

      LED_5_LIGHT_R,
      LED_5_LIGHT_G,
      LED_5_LIGHT_B,

      LED_6_LIGHT_R,
      LED_6_LIGHT_G,
      LED_6_LIGHT_B,

      LED_7_LIGHT_R,
      LED_7_LIGHT_G,
      LED_7_LIGHT_B,

      LED_8_LIGHT_R,
      LED_8_LIGHT_G,
      LED_8_LIGHT_B,

      NUM_LIGHT_PINS
   };


   faust::FaustDSP FaustDSP;
   faust::APIUI FaustUI;

   // variables for storing GUI IDs
   int paramButton_1 = -1;
   int paramButton_2 = -1;
   int paramButton_3 = -1;
   int paramButton_4 = -1;
   int paramButton_5 = -1;
   int paramButton_6 = -1;
   int paramButton_7 = -1;
   int paramButton_8 = -1;

   int paramKnob_1 = -1;
   int paramKnob_2 = -1;
   int paramKnob_3 = -1;
   int paramKnob_4 = -1;
   int paramKnob_5 = -1;
   int paramKnob_6 = -1;
   int paramKnob_7 = -1;
   int paramKnob_8 = -1;

   int paramLight_1_r = -1;
   int paramLight_1_g = -1;
   int paramLight_1_b = -1;

   int paramLight_2_r = -1;
   int paramLight_2_g = -1;
   int paramLight_2_b = -1;

   int paramLight_3_r = -1;
   int paramLight_3_g = -1;
   int paramLight_3_b = -1;

   int paramLight_4_r = -1;
   int paramLight_4_g = -1;
   int paramLight_4_b = -1;

   int paramLight_5_r = -1;
   int paramLight_5_g = -1;
   int paramLight_5_b = -1;

   int paramLight_6_r = -1;
   int paramLight_6_g = -1;
   int paramLight_6_b = -1;

   int paramLight_7_r = -1;
   int paramLight_7_g = -1;
   int paramLight_7_b = -1;

   int paramLight_8_r = -1;
   int paramLight_8_g = -1;
   int paramLight_8_b = -1;

   const int numberOfChannels = 8;
   const FAUSTFLOAT voltageScaling = 5.0f;

   ProtoFaust();

   void onAdd() override;
   void onSampleRateChange() override;

   void process( const ProcessArgs& args ) override;
};


struct ProtoFaustWidget : ModuleWidget {
   explicit ProtoFaustWidget( ProtoFaust* module );
};


Model* modelProtoFaust = createModel<ProtoFaust, ProtoFaustWidget>( "ProtoFaust" );
