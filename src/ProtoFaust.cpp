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

   FaustDSP.buildUserInterface( &FaustUI );

   // sorry for the following cruft -- I'd give my right arm for
   // LISP-like macros in C++ ...

   // ------ switches & buttons ------

   addParameter( ProtoFaustWidget::THREE_WAY_SWITCH,
                 BUTTON_1_PARAM,
                 "/ProtoFaust/Buttons/1" );

   addParameter( ProtoFaustWidget::THREE_WAY_SWITCH,
                 BUTTON_2_PARAM,
                 "/ProtoFaust/Buttons/2" );

   addParameter( ProtoFaustWidget::TOGGLE_SWITCH,
                 BUTTON_3_PARAM,
                 "/ProtoFaust/Buttons/3" );

   addParameter( ProtoFaustWidget::TOGGLE_SWITCH,
                 BUTTON_4_PARAM,
                 "/ProtoFaust/Buttons/4" );

   addParameter( ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_5_PARAM,
                 "/ProtoFaust/Buttons/5" );

   addParameter( ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_6_PARAM,
                 "/ProtoFaust/Buttons/6" );

   addParameter( ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_7_PARAM,
                 "/ProtoFaust/Buttons/7" );

   addParameter( ProtoFaustWidget::PUSH_BUTTON,
                 BUTTON_8_PARAM,
                 "/ProtoFaust/Buttons/8" );

   // ------ knobs ------

   addParameter( ProtoFaustWidget::KNOB_WHITE,
                 KNOB_1_PARAM,
                 "/ProtoFaust/Knobs/1" );

   addParameter( ProtoFaustWidget::KNOB_RED,
                 KNOB_2_PARAM,
                 "/ProtoFaust/Knobs/2" );

   addParameter( ProtoFaustWidget::KNOB_WHITE,
                 KNOB_3_PARAM,
                 "/ProtoFaust/Knobs/3" );

   addParameter( ProtoFaustWidget::KNOB_RED,
                 KNOB_4_PARAM,
                 "/ProtoFaust/Knobs/4" );

   addParameter( ProtoFaustWidget::KNOB_WHITE,
                 KNOB_5_PARAM,
                 "/ProtoFaust/Knobs/5" );

   addParameter( ProtoFaustWidget::KNOB_RED,
                 KNOB_6_PARAM,
                 "/ProtoFaust/Knobs/6" );

   addParameter( ProtoFaustWidget::KNOB_WHITE,
                 KNOB_7_PARAM,
                 "/ProtoFaust/Knobs/7" );

   addParameter( ProtoFaustWidget::KNOB_RED,
                 KNOB_8_PARAM,
                 "/ProtoFaust/Knobs/8" );

   // ------ RGB LEDs ------

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_1,
                    "/ProtoFaust/Lights/1" );

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_2,
                    "/ProtoFaust/Lights/2" );

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_3,
                    "/ProtoFaust/Lights/3" );

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_4,
                    "/ProtoFaust/Lights/4" );

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_5,
                    "/ProtoFaust/Lights/5" );

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_6,
                    "/ProtoFaust/Lights/6" );

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_7,
                    "/ProtoFaust/Lights/7" );

   addParameterLed( ProtoFaustWidget::LED_RGB,
                    LED_8,
                    "/ProtoFaust/Lights/8" );
}


void ProtoFaust::onAdd()
{
   // initialize Faust using default sample rate; see
   // ProtoFaust::process()
   FaustDSP.init( 44100 );
}


void ProtoFaust::process( const ProcessArgs& args )
{
   // update Faust DSP on sample rate changes
   //
   // running this check in *every* module and for *every* single
   // sample seems like a *huge* amount of overhead; however, this is
   // the current expected behaviour of VCV Rack modules; see
   // https://github.com/mzuther/ProtoFaust/pull/2
   if ( args.sampleRate != FaustDSP.getSampleRate() ) {
      FaustDSP.init( args.sampleRate );
   }

   FAUSTFLOAT* temporaryInputs = ( FAUSTFLOAT* ) alloca( numberOfChannels *
                                                         sizeof( FAUSTFLOAT ) );
   FAUSTFLOAT* temporaryOutputs = ( FAUSTFLOAT* ) alloca( numberOfChannels *
                                                          sizeof( FAUSTFLOAT ) );

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
      updateParameterIn( widget );
   }

   // update Faust controls
   int int_control[FaustDSP.getNumIntControls()];
   FAUSTFLOAT real_control[FaustDSP.getNumRealControls()];
   FaustDSP.control( int_control, real_control );

   // process one sample in Faust
   FaustDSP.compute( temporaryInputs,
                     temporaryOutputs,
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
      updateParameterOut( widget );
   }
}


void ProtoFaust::addParameter( int widgetType,
                               int parameterId,
                               const std::string& faustStringId )
{
   std::vector<WidgetAccess>* widgets;

   if ( widgetType == ProtoFaustWidget::LED_RGB ) {
      widgets = &passiveWidgets;
   } else {
      widgets = &activeWidgets;
   }

   // prepare controller zone 'set' and 'get' functions
   FAUSTFLOAT* zone = FaustUI.getParamZone( faustStringId );

   WidgetAccess::setFunction setFun = [ = ]( FAUSTFLOAT value ) {
      *zone = value;
   };

   WidgetAccess::getFunction getFun = [ = ]() {
      return *zone;
   };

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

         // special 'set' version
         setFun = [ = ]( FAUSTFLOAT value ) {
            *zone = value / FAUSTFLOAT( 2.0 );
         };
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

   widgets->push_back( WidgetAccess ( widgetType,
                                      parameterId,
                                      setFun,
                                      getFun ) );
}


void ProtoFaust::addParameterLed( int widgetType,
                                  int parameterId,
                                  const std::string& faustStringId )
{
   // add a parameter for each virtual LED pin
   // (red, green and blue)

   addParameter( widgetType,
                 parameterId,
                 faustStringId + "_Red" );

   addParameter( widgetType,
                 parameterId + 1,
                 faustStringId + "_Green" );

   addParameter( widgetType,
                 parameterId + 2,
                 faustStringId + "_Blue" );

}


void ProtoFaust::updateParameterIn( WidgetAccess& widget )
{
   widget.faustSet( params[widget.parameterId].getValue() );
}


void ProtoFaust::updateParameterOut( WidgetAccess& widget )
{
   lights[widget.parameterId].setBrightness( widget.faustGet() );
}


Model* modelProtoFaust = createModel<ProtoFaust, ProtoFaustWidget>(
                            "ProtoFaust" );
