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
   config( ProtoFaustWidget::NUM_PARAMS,
           ProtoFaustWidget::NUM_INPUTS,
           ProtoFaustWidget::NUM_OUTPUTS,
           ProtoFaustWidget::NUM_LED_PINS );

   FaustDSP.buildUserInterface( &FaustUI );
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

   // cppcheck-suppress allocaCalled ; Stéphane knows what he is doing ...
   FAUSTFLOAT* temporaryInputs = ( FAUSTFLOAT* ) alloca( numberOfChannels *
                                                         sizeof( FAUSTFLOAT ) );

   // cppcheck-suppress allocaCalled
   FAUSTFLOAT* temporaryOutputs = ( FAUSTFLOAT* ) alloca( numberOfChannels *
                                                          sizeof( FAUSTFLOAT ) );

   // read from module's inputs; scale voltages from Rack to usual
   // range in DSP processing (-1.0 to +1.0) so you don't have to
   // adjust algorithms when porting them to VCV Rack
   for ( auto channel = 0; channel < numberOfChannels; channel++ ) {
      FAUSTFLOAT input = inputs[ProtoFaustWidget::IN_1_INPUT + channel].getVoltage();
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
      outputs[ProtoFaustWidget::OUT_1_OUTPUT + channel].setVoltage( output * voltageScaling );
   }

   // get widget values and update Faust parameters
   for ( auto& widget : passiveWidgets ) {
      updateParameterOut( widget );
   }
}


void ProtoFaust::addParameter( int widgetType,
                               int parameterId,
                               FAUSTFLOAT* zone )
{
   std::vector<WidgetAccess>* widgets;

   if ( widgetType == faust::VCVRACKUI::LED_RGB ) {
      widgets = &passiveWidgets;
   } else {
      widgets = &activeWidgets;
   }

   // prepare controller zone 'set' and 'get' functions
   WidgetAccess::setFunction setFun = [ = ]( FAUSTFLOAT value ) {
      *zone = value;
   };

   WidgetAccess::getFunction getFun = [ = ]() {
      return *zone;
   };

   switch ( widgetType ) {
      case faust::VCVRACKUI::SWITCH_TOGGLE:
      case faust::VCVRACKUI::SWITCH_MOMENTARY:

         // values:  0.0, 1.0
         // default: 0.0 (off)
         configParam( parameterId,
                      0.0f,
                      1.0f,
                      0.0f,
                      "" );
         break;

      case faust::VCVRACKUI::SWITCH_THREE_WAY:

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

      case faust::VCVRACKUI::KNOB_LARGE_WHITE:
      case faust::VCVRACKUI::KNOB_LARGE_RED:

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
