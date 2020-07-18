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


ProtoFaustWidget::ProtoFaustWidget( ProtoFaust* currentModule ) :
   _module( currentModule )
{
   _parameterId = -1;
   _inputId = -1;
   _outputId = -1;
   _lightId = -1;

   setModule( _module );
   setPanel( APP->window->loadSvg(
                asset::plugin( pluginInstance, "res/ProtoFaust.svg" ) ) );

   // when the module selection window is openend, this constructor is
   // called with a null pointer -- I mean, honestly!!!
   if ( _module ) {
      currentUI = &_module->FaustUI;
   } else {
      dummyFaustDSP = std::unique_ptr<faust::FaustDSP>(
                         new faust::FaustDSP() );

      dummyFaustUI = std::unique_ptr<faust::VCVRACKUI>(
                        new faust::VCVRACKUI() );

      dummyFaustDSP->buildUserInterface( dummyFaustUI.get() );
      currentUI = dummyFaustUI.get();
   }

   // sorry for the following cruft -- I'd give my right arm for
   // LISP-like macros in C++ ...

   // ------ screws ------

   addScrew( RACK_GRID_WIDTH,
             0 );

   addScrew( box.size.x - 2 * RACK_GRID_WIDTH,
             0 );

   addScrew( RACK_GRID_WIDTH,
             RACK_GRID_HEIGHT - RACK_GRID_WIDTH );

   addScrew( box.size.x - 2 * RACK_GRID_WIDTH,
             RACK_GRID_HEIGHT - RACK_GRID_WIDTH );

   // ------ input ports ------

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            21.82 );

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            34.52 );

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            49.76 );

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            62.46 );

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            77.7 );

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            90.4 );

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            105.64 );

   addPort( faust::VCVRACKUI::PORT_INPUT,
            _inputId,
            17.78,
            118.34 );

   // ------ output ports ------

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            21.82 );

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            34.52 );

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            49.76 );

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            62.46 );

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            77.7 );

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            90.4 );

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            105.64 );

   addPort( faust::VCVRACKUI::PORT_OUTPUT,
            _outputId,
            114.3,
            118.34 );

   // ------ switches ------

   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/1" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/2" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/3" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/4" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/5" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/6" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/7" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Buttons/8" );

   // ------ knobs ------

   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/1" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/2" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/3" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/4" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/5" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/6" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/7" );
   addWidgetAndParameter( _parameterId, "/ProtoFaust/Knobs/8" );

   // ------ RGB LEDs ------

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/1_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/1_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/1_Blue" );

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/2_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/2_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/2_Blue" );

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/3_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/3_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/3_Blue" );

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/4_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/4_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/4_Blue" );

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/5_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/5_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/5_Blue" );

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/6_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/6_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/6_Blue" );

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/7_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/7_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/7_Blue" );

   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/8_Red" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/8_Green" );
   addWidgetAndParameter( _lightId, "/ProtoFaust/Lights/8_Blue" );
}


void ProtoFaustWidget::addWidgetAndParameter( int& parameterId,
                                              const std::string& faustStringId )
{
   auto zone = currentUI->getParamZone( faustStringId );
   auto widgetType = currentUI->getWidgetType( zone );

   // create a new parameter ID
   ++parameterId;

   if ( _module ) {
      _module->addParameter( widgetType, parameterId, zone );
   }

   // add light widget only once
   if ( ( widgetType != faust::VCVRACKUI::LED_RGB ) ||
        ( faustStringId.rfind( "_Red" ) != std::string::npos ) ) {
      auto x = currentUI->getPositionX( zone );
      auto y = currentUI->getPositionY( zone );

      addWidget( widgetType, parameterId, x, y );
   }
}


void ProtoFaustWidget::addPort( int widgetType,
                                int& parameterId,
                                float x,
                                float y )
{
   // create a new parameter ID
   ++parameterId;

   addWidget( widgetType, parameterId, x, y );
}


void ProtoFaustWidget::addScrew( float x,
                                 float y )
{
   addWidget( faust::VCVRACKUI::SCREW,
              -1,
              x,
              y );
}


void ProtoFaustWidget::addWidget( int widgetType,
                                  int parameterId,
                                  float x,
                                  float y )
{
   auto pos = math::Vec( x, y );
   auto pos_converted = mm2px( pos );

   switch ( widgetType ) {
      case faust::VCVRACKUI::SWITCH_TOGGLE:

         addParam( createParamCentered<CKSS>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::SWITCH_THREE_WAY:

         addParam( createParamCentered<CKSSThree>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::SWITCH_MOMENTARY:

         addParam( createParamCentered<BefacoPush>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::KNOB_LARGE_BLACK:

         addParam( createParamCentered<Davies1900hLargeBlackKnob>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::KNOB_LARGE_WHITE:

         addParam( createParamCentered<Davies1900hLargeWhiteKnob>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::KNOB_LARGE_RED:

         addParam( createParamCentered<Davies1900hLargeRedKnob>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::KNOB_SMALL_BLACK:

         addParam( createParamCentered<Davies1900hBlackKnob>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::KNOB_SMALL_WHITE:

         addParam( createParamCentered<Davies1900hWhiteKnob>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::KNOB_SMALL_RED:

         addParam( createParamCentered<Davies1900hRedKnob>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::PORT_INPUT:

         addInput( createInputCentered<CL1362Port>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::PORT_OUTPUT:

         addOutput( createOutputCentered<CL1362Port>(
                       pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::LED_RGB:

         addChild( createLightCentered<MediumLight<RedGreenBlueLight>>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::SCREW:

         addChild( createWidget<ScrewBlack>(
                      pos ) );
         break;
   }
}
