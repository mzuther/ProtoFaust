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


ProtoFaustWidget::ProtoFaustWidget( ProtoFaust* module ) :
   _module( module )
{
   setModule( module );
   setPanel( APP->window->loadSvg(
                asset::plugin( pluginInstance, "res/ProtoFaust.svg" ) ) );

   // ------ screws ------

   placeWidget( ProtoFaustWidget::SCREW,
                ProtoFaust::GENERIC_SCREW,
                RACK_GRID_WIDTH,
                0 );

   placeWidget( ProtoFaustWidget::SCREW,
                ProtoFaust::GENERIC_SCREW,
                box.size.x - 2 * RACK_GRID_WIDTH,
                0 );

   placeWidget( ProtoFaustWidget::SCREW,
                ProtoFaust::GENERIC_SCREW,
                RACK_GRID_WIDTH,
                RACK_GRID_HEIGHT - RACK_GRID_WIDTH );

   placeWidget( ProtoFaustWidget::SCREW,
                ProtoFaust::GENERIC_SCREW,
                box.size.x - 2 * RACK_GRID_WIDTH,
                RACK_GRID_HEIGHT - RACK_GRID_WIDTH );

   // ------ switches ------

   placeWidget( ProtoFaustWidget::THREE_WAY_SWITCH,
                ProtoFaust::BUTTON_1_PARAM,
                31.75,
                21.82 );

   placeWidget( ProtoFaustWidget::THREE_WAY_SWITCH,
                ProtoFaust::BUTTON_2_PARAM,
                31.75,
                34.52 );

   placeWidget( ProtoFaustWidget::TOGGLE_SWITCH,
                ProtoFaust::BUTTON_3_PARAM,
                31.75,
                49.76 );

   placeWidget( ProtoFaustWidget::TOGGLE_SWITCH,
                ProtoFaust::BUTTON_4_PARAM,
                31.75,
                62.46 );

   // ------ buttons ------

   placeWidget( ProtoFaustWidget::PUSH_BUTTON,
                ProtoFaust::BUTTON_5_PARAM,
                31.75,
                77.7 );

   placeWidget( ProtoFaustWidget::PUSH_BUTTON,
                ProtoFaust::BUTTON_6_PARAM,
                31.75,
                90.4 );

   placeWidget( ProtoFaustWidget::PUSH_BUTTON,
                ProtoFaust::BUTTON_7_PARAM,
                31.75,
                105.64 );

   placeWidget( ProtoFaustWidget::PUSH_BUTTON,
                ProtoFaust::BUTTON_8_PARAM,
                31.75,
                118.34 );

   // ------ knobs ------

   placeWidget( ProtoFaustWidget::KNOB_WHITE,
                ProtoFaust::KNOB_1_PARAM,
                53.34,
                28.17 );

   placeWidget( ProtoFaustWidget::KNOB_RED,
                ProtoFaust::KNOB_2_PARAM,
                78.74,
                28.17 );

   placeWidget( ProtoFaustWidget::KNOB_WHITE,
                ProtoFaust::KNOB_3_PARAM,
                53.34,
                56.11 );

   placeWidget( ProtoFaustWidget::KNOB_RED,
                ProtoFaust::KNOB_4_PARAM,
                78.74,
                56.11 );

   placeWidget( ProtoFaustWidget::KNOB_WHITE,
                ProtoFaust::KNOB_5_PARAM,
                53.34,
                84.05 );

   placeWidget( ProtoFaustWidget::KNOB_RED,
                ProtoFaust::KNOB_6_PARAM,
                78.74,
                84.05 );

   placeWidget( ProtoFaustWidget::KNOB_WHITE,
                ProtoFaust::KNOB_7_PARAM,
                53.34,
                111.99 );

   placeWidget( ProtoFaustWidget::KNOB_RED,
                ProtoFaust::KNOB_8_PARAM,
                78.74,
                111.99 );

   // ------ input ports ------

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_1_INPUT,
                17.78,
                21.82 );

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_2_INPUT,
                17.78,
                34.52 );

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_3_INPUT,
                17.78,
                49.76 );

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_4_INPUT,
                17.78,
                62.46 );

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_5_INPUT,
                17.78,
                77.7 );

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_6_INPUT,
                17.78,
                90.4 );

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_7_INPUT,
                17.78,
                105.64 );

   placeWidget( ProtoFaustWidget::PORT_INPUT,
                ProtoFaust::IN_8_INPUT,
                17.78,
                118.34 );

   // ------ output ports ------

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_1_OUTPUT,
                114.3,
                21.82 );

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_2_OUTPUT,
                114.3,
                34.52 );

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_3_OUTPUT,
                114.3,
                49.76 );

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_4_OUTPUT,
                114.3,
                62.46 );

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_5_OUTPUT,
                114.3,
                77.7 );

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_6_OUTPUT,
                114.3,
                90.4 );

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_7_OUTPUT,
                114.3,
                105.64 );

   placeWidget( ProtoFaustWidget::PORT_OUTPUT,
                ProtoFaust::OUT_8_OUTPUT,
                114.3,
                118.34 );

   // ------ RGB LEDs ------

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_1_LIGHT_R,
                99.06,
                21.82 );

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_2_LIGHT_R,
                99.06,
                34.52 );

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_3_LIGHT_R,
                99.06,
                49.76 );

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_4_LIGHT_R,
                99.06,
                62.46 );

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_5_LIGHT_R,
                99.06,
                77.7 );

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_6_LIGHT_R,
                99.06,
                90.4 );

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_7_LIGHT_R,
                99.06,
                105.64 );

   placeWidget( ProtoFaustWidget::LED_RGB,
                ProtoFaust::LED_8_LIGHT_R,
                99.06,
                118.34 );
}


void ProtoFaustWidget::placeWidget( int widgetType,
                                    int parameterId,
                                    float x,
                                    float y )
{
   math::Vec pos = math::Vec( x, y );
   math::Vec pos_converted = mm2px( pos );

   switch ( widgetType ) {
      case TOGGLE_SWITCH:

         addParam( createParamCentered<CKSS>(
                      pos_converted, module, parameterId ) );
         break;

      case THREE_WAY_SWITCH:

         addParam( createParamCentered<CKSSThree>(
                      pos_converted, module, parameterId ) );
         break;

      case PUSH_BUTTON:

         addParam( createParamCentered<BefacoPush>(
                      pos_converted, module, parameterId ) );
         break;

      case KNOB_WHITE:

         addParam( createParamCentered<Davies1900hLargeWhiteKnob>(
                      pos_converted, module, parameterId ) );
         break;

      case KNOB_RED:

         addParam( createParamCentered<Davies1900hLargeRedKnob>(
                      pos_converted, module, parameterId ) );
         break;

      case PORT_INPUT:

         addInput( createInputCentered<CL1362Port>(
                      pos_converted, module, parameterId ) );
         break;

      case PORT_OUTPUT:

         addOutput( createOutputCentered<CL1362Port>(
                       pos_converted, module, parameterId ) );
         break;

      case LED_RGB:

         addChild( createLightCentered<MediumLight<RedGreenBlueLight>>(
                      pos_converted, module, parameterId ) );
         break;

      case SCREW:

         addChild( createWidget<ScrewBlack>(
                      pos ) );
         break;
   }
}
