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

#ifndef PROTO_FAUST_WIDGET_HPP
#define PROTO_FAUST_WIDGET_HPP

#include <string>


struct ProtoFaustWidget : ModuleWidget {
public:
   explicit ProtoFaustWidget( ProtoFaust* currentModule );

protected:
   void addWidgetAndParameter( int& parameterId,
                               const std::string& faustStringId );

   void addPort( int widgetType,
                 int& parameterId,
                 float x,
                 float y );

   void addScrew( float x,
                  float y );

   void addWidget( int widgetType,
                   int parameterId,
                   float x,
                   float y );

   ProtoFaust* _module = nullptr;

   std::unique_ptr<faust::FaustDSP> dummyFaustDSP;
   std::unique_ptr<faust::VCVRACKUI> dummyFaustUI;
   faust::VCVRACKUI* currentUI;

   int _parameterId;
   int _inputId;
   int _outputId;
   int _lightId;
};

#endif // PROTO_FAUST_WIDGET_HPP
