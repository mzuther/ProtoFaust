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

#ifndef PROTO_FAUST_HPP
#define PROTO_FAUST_HPP


struct ProtoFaust : Module {
public:
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

   enum LedIds {
      LED_1,
      LED_1_GREEN_INTERNAL_USE_ONLY,
      LED_1_BLUE_INTERNAL_USE_ONLY,

      LED_2,
      LED_2_GREEN_INTERNAL_USE_ONLY,
      LED_2_BLUE_INTERNAL_USE_ONLY,

      LED_3,
      LED_3_GREEN_INTERNAL_USE_ONLY,
      LED_3_BLUE_INTERNAL_USE_ONLY,

      LED_4,
      LED_4_GREEN_INTERNAL_USE_ONLY,
      LED_4_BLUE_INTERNAL_USE_ONLY,

      LED_5,
      LED_5_GREEN_INTERNAL_USE_ONLY,
      LED_5_BLUE_INTERNAL_USE_ONLY,

      LED_6,
      LED_6_GREEN_INTERNAL_USE_ONLY,
      LED_6_BLUE_INTERNAL_USE_ONLY,

      LED_7,
      LED_7_GREEN_INTERNAL_USE_ONLY,
      LED_7_BLUE_INTERNAL_USE_ONLY,

      LED_8,
      LED_8_GREEN_INTERNAL_USE_ONLY,
      LED_8_BLUE_INTERNAL_USE_ONLY,

      NUM_LED_PINS
   };

   enum GenericIds {
      GENERIC_SCREW,

      NUM_GENERIC_IDS
   };

   const int numberOfChannels = 8;
   const FAUSTFLOAT voltageScaling = 5.0f;

   faust::FaustDSP FaustDSP;
   faust::APIUI FaustUI;

   ProtoFaust();

   void onAdd() override;
   void onSampleRateChange() override;

   void process( const ProcessArgs& args ) override;

private:
   std::vector<WidgetAccess> activeWidgets;
   std::vector<WidgetAccess> passiveWidgets;

   void addParameter( std::vector<WidgetAccess>& widgets,
                      int widgetType,
                      int parameterId,
                      const std::string& faustStringId );

   void addParameterLed( std::vector<WidgetAccess>& widgets,
                         int widgetType,
                         int parameterId,
                         const std::string& faustStringId );

   void attachFaustParameter( WidgetAccess& widget );
   void updateParameter( WidgetAccess& widget );
};

#endif // PROTO_FAUST_HPP
