/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.

 ************************************************************************
 ************************************************************************/

#include <cstring>

#include "faust/gui/MapUI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/one-sample-dsp.h"

// *INDENT-OFF* --> make astyle behave ...

/******************************************************************************
 *******************************************************************************

 VECTOR INTRINSICS

 *******************************************************************************
 *******************************************************************************/

<<includeIntrinsic>>

/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

// *INDENT-ON* --> give astyle free reign ...

      class VCVRACKUI : public MapUI
{
public:
   enum WidgetTypes {
      SWITCH_TOGGLE,
      SWITCH_THREE_WAY,
      SWITCH_MOMENTARY,

      KNOB_LARGE_WHITE,
      KNOB_LARGE_RED,

      PORT_INPUT,
      PORT_OUTPUT,
      LED_RGB,
      SCREW,

      NUM_WIDGET_TYPES
   };


   VCVRACKUI() : MapUI()
   {
   }


   virtual ~VCVRACKUI()
   {
   }


   virtual void declare( FAUSTFLOAT* zone,
                         const char* key,
                         const char* val ) override
   {
      MapUI::declare( zone, key, val );
   }
};

/********************END ARCHITECTURE SECTION (part 2/2)****************/
