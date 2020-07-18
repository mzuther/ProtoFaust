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


// "repetitive" takes on a whole new meaning in this file ...

ProtoFaustWidget::ProtoFaustWidget( ProtoFaust* currentModule ) :
   _module( currentModule )
{
   setModule( _module );
   setPanel( APP->window->loadSvg(
                asset::plugin( pluginInstance, "res/ProtoFaust.svg" ) ) );

   // sorry for the following cruft -- I'd give my right arm for
   // LISP-like macros in C++ ...

   // ------ screws ------

   addWidget( faust::VCVRACKUI::SCREW,
              ProtoFaustWidget::GENERIC_SCREW,
              RACK_GRID_WIDTH,
              0 );

   addWidget( faust::VCVRACKUI::SCREW,
              ProtoFaustWidget::GENERIC_SCREW,
              box.size.x - 2 * RACK_GRID_WIDTH,
              0 );

   addWidget( faust::VCVRACKUI::SCREW,
              ProtoFaustWidget::GENERIC_SCREW,
              RACK_GRID_WIDTH,
              RACK_GRID_HEIGHT - RACK_GRID_WIDTH );

   addWidget( faust::VCVRACKUI::SCREW,
              ProtoFaustWidget::GENERIC_SCREW,
              box.size.x - 2 * RACK_GRID_WIDTH,
              RACK_GRID_HEIGHT - RACK_GRID_WIDTH );

   // ------ switches ------

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_1_PARAM,
                          "/ProtoFaust/Buttons/1",
                          31.75,
                          21.82 );

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_2_PARAM,
                          "/ProtoFaust/Buttons/2",
                          31.75,
                          34.52 );

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_3_PARAM,
                          "/ProtoFaust/Buttons/3",
                          31.75,
                          49.76 );

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_4_PARAM,
                          "/ProtoFaust/Buttons/4",
                          31.75,
                          62.46 );

   // ------ buttons ------

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_5_PARAM,
                          "/ProtoFaust/Buttons/5",
                          31.75,
                          77.7 );

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_6_PARAM,
                          "/ProtoFaust/Buttons/6",
                          31.75,
                          90.4 );

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_7_PARAM,
                          "/ProtoFaust/Buttons/7",
                          31.75,
                          105.64 );

   addWidgetAndParameter( ProtoFaustWidget::BUTTON_8_PARAM,
                          "/ProtoFaust/Buttons/8",
                          31.75,
                          118.34 );

   // ------ knobs ------

   addWidgetAndParameter( ProtoFaustWidget::KNOB_1_PARAM,
                          "/ProtoFaust/Knobs/1",
                          53.34,
                          28.17 );

   addWidgetAndParameter( ProtoFaustWidget::KNOB_2_PARAM,
                          "/ProtoFaust/Knobs/2",
                          78.74,
                          28.17 );

   addWidgetAndParameter( ProtoFaustWidget::KNOB_3_PARAM,
                          "/ProtoFaust/Knobs/3",
                          53.34,
                          56.11 );

   addWidgetAndParameter( ProtoFaustWidget::KNOB_4_PARAM,
                          "/ProtoFaust/Knobs/4",
                          78.74,
                          56.11 );

   addWidgetAndParameter( ProtoFaustWidget::KNOB_5_PARAM,
                          "/ProtoFaust/Knobs/5",
                          53.34,
                          84.05 );

   addWidgetAndParameter( ProtoFaustWidget::KNOB_6_PARAM,
                          "/ProtoFaust/Knobs/6",
                          78.74,
                          84.05 );

   addWidgetAndParameter( ProtoFaustWidget::KNOB_7_PARAM,
                          "/ProtoFaust/Knobs/7",
                          53.34,
                          111.99 );

   addWidgetAndParameter( ProtoFaustWidget::KNOB_8_PARAM,
                          "/ProtoFaust/Knobs/8",
                          78.74,
                          111.99 );

   // ------ input ports ------

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_1_INPUT,
              17.78,
              21.82 );

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_2_INPUT,
              17.78,
              34.52 );

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_3_INPUT,
              17.78,
              49.76 );

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_4_INPUT,
              17.78,
              62.46 );

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_5_INPUT,
              17.78,
              77.7 );

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_6_INPUT,
              17.78,
              90.4 );

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_7_INPUT,
              17.78,
              105.64 );

   addWidget( faust::VCVRACKUI::PORT_INPUT,
              ProtoFaustWidget::IN_8_INPUT,
              17.78,
              118.34 );

   // ------ output ports ------

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_1_OUTPUT,
              114.3,
              21.82 );

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_2_OUTPUT,
              114.3,
              34.52 );

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_3_OUTPUT,
              114.3,
              49.76 );

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_4_OUTPUT,
              114.3,
              62.46 );

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_5_OUTPUT,
              114.3,
              77.7 );

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_6_OUTPUT,
              114.3,
              90.4 );

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_7_OUTPUT,
              114.3,
              105.64 );

   addWidget( faust::VCVRACKUI::PORT_OUTPUT,
              ProtoFaustWidget::OUT_8_OUTPUT,
              114.3,
              118.34 );

   // ------ RGB LEDs ------

   addWidgetAndParameter( ProtoFaustWidget::LED_1,
                          "/ProtoFaust/Lights/1_Red",
                          99.06,
                          21.82 );

   addWidgetAndParameter( ProtoFaustWidget::LED_2,
                          "/ProtoFaust/Lights/2_Red",
                          99.06,
                          34.52 );

   addWidgetAndParameter( ProtoFaustWidget::LED_3,
                          "/ProtoFaust/Lights/3_Red",
                          99.06,
                          49.76 );

   addWidgetAndParameter( ProtoFaustWidget::LED_4,
                          "/ProtoFaust/Lights/4_Red",
                          99.06,
                          62.46 );

   addWidgetAndParameter( ProtoFaustWidget::LED_5,
                          "/ProtoFaust/Lights/5_Red",
                          99.06,
                          77.7 );

   addWidgetAndParameter( ProtoFaustWidget::LED_6,
                          "/ProtoFaust/Lights/6_Red",
                          99.06,
                          90.4 );

   addWidgetAndParameter( ProtoFaustWidget::LED_7,
                          "/ProtoFaust/Lights/7_Red",
                          99.06,
                          105.64 );

   addWidgetAndParameter( ProtoFaustWidget::LED_8,
                          "/ProtoFaust/Lights/8_Red",
                          99.06,
                          118.34 );
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

      case faust::VCVRACKUI::KNOB_LARGE_WHITE:

         addParam( createParamCentered<Davies1900hLargeWhiteKnob>(
                      pos_converted, _module, parameterId ) );
         break;

      case faust::VCVRACKUI::KNOB_LARGE_RED:

         addParam( createParamCentered<Davies1900hLargeRedKnob>(
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


void ProtoFaustWidget::addWidgetAndParameter( int parameterId,
                                              const std::string& faustStringId,
                                              float x,
                                              float y )
{
   auto zone = _module->FaustUI.getParamZone( faustStringId );
   auto widgetType = _module->FaustUI.getWidgetType( zone );
   _module->addParameter( widgetType, parameterId, zone );

   if ( widgetType == faust::VCVRACKUI::LED_RGB ) {
      auto index = faustStringId.rfind( "_Red" );
      auto faustStringIdBase = faustStringId.substr( 0, index );

      zone = _module->FaustUI.getParamZone( faustStringIdBase + "_Green" );
      widgetType = _module->FaustUI.getWidgetType( zone );
      _module->addParameter( widgetType, parameterId + 1, zone );

      zone = _module->FaustUI.getParamZone( faustStringIdBase + "_Blue" );
      widgetType = _module->FaustUI.getWidgetType( zone );
      _module->addParameter( widgetType, parameterId + 2, zone );
   }

   addWidget( widgetType, parameterId, x, y );
}
