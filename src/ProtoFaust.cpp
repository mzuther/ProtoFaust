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
           NUM_LED_PINS );

   // sorry for the following cruft -- I'd give my right arm for
   // LISP-like macros in C++ ...

   // ------ switches & buttons ------

   addParameter( activeWidgets,
                 ProtoFaustWidget::THREE_WAY_SWITCH,
                 BUTTON_1_PARAM,
                 "/ProtoFaust/Buttons/1" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::THREE_WAY_SWITCH,
                 BUTTON_2_PARAM,
                 "/ProtoFaust/Buttons/2" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::TOGGLE_SWITCH,
                 BUTTON_3_PARAM,
                 "/ProtoFaust/Buttons/3" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::TOGGLE_SWITCH,
                 BUTTON_4_PARAM,
                 "/ProtoFaust/Buttons/4" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_5_PARAM,
                 "/ProtoFaust/Buttons/5" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_6_PARAM,
                 "/ProtoFaust/Buttons/6" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_7_PARAM,
                 "/ProtoFaust/Buttons/7" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_8_PARAM,
                 "/ProtoFaust/Buttons/8" );

   // ------ knobs ------

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_WHITE,
                 KNOB_1_PARAM,
                 "/ProtoFaust/Knobs/1" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_RED,
                 KNOB_2_PARAM,
                 "/ProtoFaust/Knobs/2" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_WHITE,
                 KNOB_3_PARAM,
                 "/ProtoFaust/Knobs/3" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_RED,
                 KNOB_4_PARAM,
                 "/ProtoFaust/Knobs/4" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_WHITE,
                 KNOB_5_PARAM,
                 "/ProtoFaust/Knobs/5" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_RED,
                 KNOB_6_PARAM,
                 "/ProtoFaust/Knobs/6" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_WHITE,
                 KNOB_7_PARAM,
                 "/ProtoFaust/Knobs/7" );

   addParameter( activeWidgets,
                 ProtoFaustWidget::KNOB_RED,
                 KNOB_8_PARAM,
                 "/ProtoFaust/Knobs/8" );

   // ------ RGB LEDs ------

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_1,
                    "/ProtoFaust/Lights/1" );

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_2,
                    "/ProtoFaust/Lights/2" );

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_3,
                    "/ProtoFaust/Lights/3" );

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_4,
                    "/ProtoFaust/Lights/4" );

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_5,
                    "/ProtoFaust/Lights/5" );

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_6,
                    "/ProtoFaust/Lights/6" );

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_7,
                    "/ProtoFaust/Lights/7" );

   addParameterLed( passiveWidgets,
                    ProtoFaustWidget::LED_RGB,
                    LED_8,
                    "/ProtoFaust/Lights/8" );
}


void ProtoFaust::onAdd()
{
   FaustDSP.buildUserInterface( &FaustUI );

   // store GUI IDs to save time during processing
   for ( auto& widget : activeWidgets ) {
      attachFaustParameter( widget );
   }

   for ( auto& widget : passiveWidgets ) {
      attachFaustParameter( widget );
   }

   // initialize Faust using default sample rate
   FaustDSP.init( 44100 );
}


void ProtoFaust::process( const ProcessArgs& args )
{
   // update Faust DSP on sample rate changes
   if ( args.sampleRate != FaustDSP.getSampleRate() ) {
      FaustDSP.init( args.sampleRate );
   }

   std::vector<FAUSTFLOAT> temporaryInputs( numberOfChannels );
   std::vector<FAUSTFLOAT> temporaryOutputs( numberOfChannels );

   // read from module's inputs; scale voltages from Rack to usual
   // range in DSP processing (-1.0 to +1.0) so you don't have to
   // adjust algorithms when porting them to VCV Rack
   for ( auto channel = 0; channel < numberOfChannels; channel++ ) {
      FAUSTFLOAT input = inputs[IN_1_INPUT + channel].getVoltage();
      temporaryInputs[channel] = input / voltageScaling;

      // protect your ears in case of misbehaviour
      temporaryOutputs[channel] = 0.0;
   }

   // get widget values and update Faust parameters
   for ( auto& widget : activeWidgets ) {
      updateParameter( widget );
   }

   // update Faust controls
   int int_control[FaustDSP.getNumIntControls()];
   FAUSTFLOAT real_control[FaustDSP.getNumRealControls()];
   FaustDSP.control( int_control, real_control );

   // process one sample in Faust
   FaustDSP.compute( temporaryInputs.data(),
                     temporaryOutputs.data(),
                     int_control,
                     real_control );

   // write to module's outputs; scale voltages from DSP processing
   // back to Rack voltages (-5.0 to +5.0)
   for ( auto channel = 0; channel < numberOfChannels; channel++ ) {
      FAUSTFLOAT output = temporaryOutputs[channel];
      outputs[OUT_1_OUTPUT + channel].setVoltage( output * voltageScaling );
   }

   // get widget values and update Faust parameters
   for ( auto& widget : passiveWidgets ) {
      updateParameter( widget );
   }
}


void ProtoFaust::addParameter( std::vector<WidgetAccess>& widgets,
                               int widgetType,
                               int parameterId,
                               const std::string& faustStringId )
{
   widgets.push_back( WidgetAccess ( widgetType,
                                     parameterId,
                                     faustStringId ) );

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

         // values:  0.0, 1.0, 2.0; scaled in ProtoFaust::updateParameter()
         // default: 0.0 (bottom)
         configParam( parameterId,
                      0.0f,
                      2.0f,
                      0.0f,
                      "" );
         break;

      case ProtoFaustWidget::KNOB_WHITE:
      case ProtoFaustWidget::KNOB_RED:

         // range:   0.0 to 1.0
         // default: 0.5 (centered)
         configParam( parameterId,
                      0.0f,
                      1.0f,
                      0.5f,
                      "" );
         break;
   }
}


void ProtoFaust::addParameterLed( std::vector<WidgetAccess>& widgets,
                                  int widgetType,
                                  int parameterId,
                                  const std::string& faustStringId )
{
   // add a parameter for each virtual LED pin
   // (red, green and blue)

   addParameter( widgets,
                 widgetType,
                 parameterId,
                 faustStringId + "_Red" );

   addParameter( widgets,
                 widgetType,
                 parameterId + 1,
                 faustStringId + "_Green" );

   addParameter( widgets,
                 widgetType,
                 parameterId + 2,
                 faustStringId + "_Blue" );

}


void ProtoFaust::updateParameter( WidgetAccess& widget )
{
   switch ( widget.widgetType ) {
      case ProtoFaustWidget::TOGGLE_SWITCH:
      case ProtoFaustWidget::PUSH_BUTTON:
      case ProtoFaustWidget::KNOB_WHITE:
      case ProtoFaustWidget::KNOB_RED:

      {
         FAUSTFLOAT value = params[widget.parameterId].getValue();
         FaustUI.setParamValue( widget.faustId, value );

         break;
      }

      case ProtoFaustWidget::THREE_WAY_SWITCH: {
         FAUSTFLOAT value = params[widget.parameterId].getValue();

         // three-way switches only work with integer-like values,
         // so scale range from (0 .. 2) to (0 .. 1)
         value /= 2.0f;
         FaustUI.setParamValue( widget.faustId, value );

         break;
      }

      case ProtoFaustWidget::LED_RGB:

         lights[widget.parameterId].setBrightness(
            FaustUI.getParamValue( widget.faustId ) );

         break;
   }
}


void ProtoFaust::attachFaustParameter( WidgetAccess& widget )
{
   widget.faustId = FaustUI.getParamIndex(
                       widget.faustStringId.c_str() );
}


Model* modelProtoFaust = createModel<ProtoFaust, ProtoFaustWidget>(
                            "ProtoFaust" );
