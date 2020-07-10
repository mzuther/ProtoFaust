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
      LED_1_R,
      LED_1_G,
      LED_1_B,

      LED_2_R,
      LED_2_G,
      LED_2_B,

      LED_3_R,
      LED_3_G,
      LED_3_B,

      LED_4_R,
      LED_4_G,
      LED_4_B,

      LED_5_R,
      LED_5_G,
      LED_5_B,

      LED_6_R,
      LED_6_G,
      LED_6_B,

      LED_7_R,
      LED_7_G,
      LED_7_B,

      LED_8_R,
      LED_8_G,
      LED_8_B,

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

   void attachFaustParameter( WidgetAccess& widget );
   void updateParameter( WidgetAccess& widget );
};

#endif // PROTO_FAUST_HPP
