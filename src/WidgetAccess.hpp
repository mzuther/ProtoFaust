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

#ifndef WIDGET_ACCESS_HPP
#define WIDGET_ACCESS_HPP

#include <algorithm>
#include <functional>


struct WidgetAccess {
   typedef std::function<void( FAUSTFLOAT )> setFunction;
   typedef std::function<FAUSTFLOAT()> getFunction;

   int widgetType;
   int parameterId;

   setFunction faustSet;
   getFunction faustGet;

   WidgetAccess( int widget_type,
                 int parameter_id,
                 setFunction& set,
                 getFunction& get ) :
      widgetType( widget_type ),
      parameterId( parameter_id ),
      faustSet( set ),
      faustGet( get )
   {};
};

#endif // WIDGET_ACCESS_HPP
