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

#include <vector>
#include <string>


struct ProtoFaust : Module {
public:
   const int numberOfChannels = 8;
   const FAUSTFLOAT voltageScaling = 5.0f;

   faust::FaustDSP FaustDSP;
   faust::VCVRACKUI FaustUI;

   ProtoFaust();

   void onAdd() override;
   void process( const ProcessArgs& args ) override;

   void addParameter( int widgetType,
                      int parameterId,
                      const std::string& faustStringId );

   void addParameterLed( int widgetType,
                         int parameterId,
                         const std::string& faustStringId );

private:
   std::vector<WidgetAccess> activeWidgets;
   std::vector<WidgetAccess> passiveWidgets;

   void updateParameterIn( WidgetAccess& widget );
   void updateParameterOut( WidgetAccess& widget );
};

#endif // PROTO_FAUST_HPP
