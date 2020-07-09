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

#include "Amalgamated.hpp"


ProtoFaust::ProtoFaust()
{
   config( NUM_PARAMS,
           NUM_INPUTS,
           NUM_OUTPUTS,
           NUM_LIGHT_PINS );

   // ------ switches ------

   configParameter( ProtoFaustWidget::THREE_WAY_SWITCH,
                    BUTTON_1_PARAM );

   configParameter( ProtoFaustWidget::THREE_WAY_SWITCH,
                    BUTTON_2_PARAM );

   configParameter( ProtoFaustWidget::TOGGLE_SWITCH,
                    BUTTON_3_PARAM );

   configParameter( ProtoFaustWidget::TOGGLE_SWITCH,
                    BUTTON_4_PARAM );

   // ------ buttons ------

   configParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_5_PARAM );

   configParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_6_PARAM );

   configParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_7_PARAM );

   configParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_8_PARAM );

   // ------ knobs ------

   configParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_1_PARAM );

   configParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_2_PARAM );

   configParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_3_PARAM );

   configParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_4_PARAM );

   configParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_5_PARAM );

   configParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_6_PARAM );

   configParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_7_PARAM );

   configParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_8_PARAM );
}


void ProtoFaust::configParameter( int widgetType,
                                  int parameterId )
{
   switch ( widgetType ) {
      case ProtoFaustWidget::TOGGLE_SWITCH:
      case ProtoFaustWidget::PUSH_BUTTON:

         // values:  0.0, 1.0
         // default: 0.0 (off)
         configParam( parameterId,
                      0.0f,
                      1.0f,
                      0.0f,
                      "" );

         break;

      case ProtoFaustWidget::THREE_WAY_SWITCH:
      case ProtoFaustWidget::KNOB_WHITE:
      case ProtoFaustWidget::KNOB_RED:

         // three-way-switch:
         //   values:  0.0, 0.5, 1.0; see ProtoFaust::updateParameter()
         //   default: 0.5 (center)
         //
         // knob:
         //   range:   0.0 to 1.0
         //   default: 0.5 (centered)
         configParam( parameterId,
                      0.0f,
                      1.0f,
                      0.5f,
                      "" );

         break;
   }
}


void ProtoFaust::onAdd()
{
   FaustDSP.buildUserInterface( &FaustUI );

   // store GUI IDs to save time during processing
   paramButton_1 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/1" );
   paramButton_2 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/2" );
   paramButton_3 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/3" );
   paramButton_4 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/4" );
   paramButton_5 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/5" );
   paramButton_6 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/6" );
   paramButton_7 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/7" );
   paramButton_8 = FaustUI.getParamIndex( "/ProtoFaust/Buttons/8" );

   paramKnob_1 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/1" );
   paramKnob_2 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/2" );
   paramKnob_3 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/3" );
   paramKnob_4 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/4" );
   paramKnob_5 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/5" );
   paramKnob_6 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/6" );
   paramKnob_7 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/7" );
   paramKnob_8 = FaustUI.getParamIndex( "/ProtoFaust/Knobs/8" );

   paramLight_1_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/1_R" );
   paramLight_1_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/1_G" );
   paramLight_1_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/1_B" );

   paramLight_2_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/2_R" );
   paramLight_2_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/2_G" );
   paramLight_2_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/2_B" );

   paramLight_3_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/3_R" );
   paramLight_3_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/3_G" );
   paramLight_3_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/3_B" );

   paramLight_4_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/4_R" );
   paramLight_4_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/4_G" );
   paramLight_4_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/4_B" );

   paramLight_5_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/5_R" );
   paramLight_5_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/5_G" );
   paramLight_5_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/5_B" );

   paramLight_6_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/6_R" );
   paramLight_6_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/6_G" );
   paramLight_6_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/6_B" );

   paramLight_7_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/7_R" );
   paramLight_7_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/7_G" );
   paramLight_7_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/7_B" );

   paramLight_8_R = FaustUI.getParamIndex( "/ProtoFaust/Lights/8_R" );
   paramLight_8_G = FaustUI.getParamIndex( "/ProtoFaust/Lights/8_G" );
   paramLight_8_B = FaustUI.getParamIndex( "/ProtoFaust/Lights/8_B" );

   FaustDSP.init(
      APP->engine->getSampleRate() );
}


void ProtoFaust::onSampleRateChange()
{
   FaustDSP.instanceConstants(
      APP->engine->getSampleRate() );
}


void ProtoFaust::process( const ProcessArgs& /* args (unused) */ )
{
   std::vector<FAUSTFLOAT> temporaryInputs( numberOfChannels );
   std::vector<FAUSTFLOAT> temporaryOutputs( numberOfChannels );

   // ------ inputs ------

   for ( auto channel = 0; channel < numberOfChannels; channel++ ) {
      FAUSTFLOAT input = inputs[IN_1_INPUT + channel].getVoltage();

      // scale voltages from Rack to usual range in DSP processing
      // (-1.0 to +1.0)
      temporaryInputs[channel] = input / voltageScaling;

      // protect your ears in case of misbehaviour
      temporaryOutputs[channel] = 0.0;
   }

   // ------ switches ------

   updateParameter( ProtoFaustWidget::THREE_WAY_SWITCH,
                    BUTTON_1_PARAM,
                    paramButton_1 );

   updateParameter( ProtoFaustWidget::THREE_WAY_SWITCH,
                    BUTTON_2_PARAM,
                    paramButton_2 );

   updateParameter( ProtoFaustWidget::TOGGLE_SWITCH,
                    BUTTON_3_PARAM,
                    paramButton_3 );

   updateParameter( ProtoFaustWidget::TOGGLE_SWITCH,
                    BUTTON_4_PARAM,
                    paramButton_4 );

   // ------ buttons ------

   updateParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_5_PARAM,
                    paramButton_5 );

   updateParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_6_PARAM,
                    paramButton_6 );

   updateParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_7_PARAM,
                    paramButton_7 );

   updateParameter( ProtoFaustWidget::PUSH_BUTTON,
                    BUTTON_8_PARAM,
                    paramButton_8 );

   // ------ knobs ------

   updateParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_1_PARAM,
                    paramKnob_1 );

   updateParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_2_PARAM,
                    paramKnob_2 );

   updateParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_3_PARAM,
                    paramKnob_3 );

   updateParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_4_PARAM,
                    paramKnob_4 );

   updateParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_5_PARAM,
                    paramKnob_5 );

   updateParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_6_PARAM,
                    paramKnob_6 );

   updateParameter( ProtoFaustWidget::KNOB_WHITE,
                    KNOB_7_PARAM,
                    paramKnob_7 );

   updateParameter( ProtoFaustWidget::KNOB_RED,
                    KNOB_8_PARAM,
                    paramKnob_8 );

   // update Faust controls
   int int_control[FaustDSP.getNumIntControls()];
   FAUSTFLOAT real_control[FaustDSP.getNumRealControls()];

   FaustDSP.control( int_control, real_control );

   // process one sample in Faust
   FaustDSP.compute( temporaryInputs.data(),
                     temporaryOutputs.data(),
                     int_control,
                     real_control );

   // ------ outputs ------

   for ( auto channel = 0; channel < numberOfChannels; channel++ ) {
      FAUSTFLOAT output = temporaryOutputs[channel];

      // scale voltages from DSP processing back to Rack voltages
      // (-5.0 to +5.0)
      outputs[OUT_1_OUTPUT + channel].setVoltage( output * voltageScaling );
   }

   // ------ RGB LEDs ------

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_1_LIGHT_R,
                    paramLight_1_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_1_LIGHT_G,
                    paramLight_1_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_1_LIGHT_B,
                    paramLight_1_B );

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_2_LIGHT_R,
                    paramLight_2_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_2_LIGHT_G,
                    paramLight_2_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_2_LIGHT_B,
                    paramLight_2_B );

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_3_LIGHT_R,
                    paramLight_3_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_3_LIGHT_G,
                    paramLight_3_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_3_LIGHT_B,
                    paramLight_3_B );

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_4_LIGHT_R,
                    paramLight_4_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_4_LIGHT_G,
                    paramLight_4_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_4_LIGHT_B,
                    paramLight_4_B );

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_5_LIGHT_R,
                    paramLight_5_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_5_LIGHT_G,
                    paramLight_5_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_5_LIGHT_B,
                    paramLight_5_B );

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_6_LIGHT_R,
                    paramLight_6_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_6_LIGHT_G,
                    paramLight_6_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_6_LIGHT_B,
                    paramLight_6_B );

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_7_LIGHT_R,
                    paramLight_7_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_7_LIGHT_G,
                    paramLight_7_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_7_LIGHT_B,
                    paramLight_7_B );

   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_8_LIGHT_R,
                    paramLight_8_R );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_8_LIGHT_G,
                    paramLight_8_G );
   updateParameter( ProtoFaustWidget::LED_RGB,
                    LED_8_LIGHT_B,
                    paramLight_8_B );
}


void ProtoFaust::updateParameter( int widgetType,
                                  int parameterId,
                                  int guiId )
{
   switch ( widgetType ) {
      case ProtoFaustWidget::TOGGLE_SWITCH:
      case ProtoFaustWidget::PUSH_BUTTON:
      case ProtoFaustWidget::KNOB_WHITE:
      case ProtoFaustWidget::KNOB_RED:

      {
         FAUSTFLOAT value = params[parameterId].getValue();
         FaustUI.setParamValue( guiId, value );

         break;
      }

      case ProtoFaustWidget::THREE_WAY_SWITCH: {
         FAUSTFLOAT value = params[parameterId].getValue();

         // scale range from (0 .. 2) to (0 .. 1)
         value /= 2.0f;

         FaustUI.setParamValue( guiId, value );

         break;
      }

      case ProtoFaustWidget::LED_RGB:

         lights[parameterId].setBrightness( FaustUI.getParamValue( guiId ) );

         break;
   }
}


Model* modelProtoFaust = createModel<ProtoFaust, ProtoFaustWidget>(
                            "ProtoFaust" );
