/* ------------------------------------------------------------
name: "main"
Code generated with Faust 2.27.1 (https://faust.grame.fr)
Compilation options: -lang cpp -os -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __FaustDSP_H__
#define  __FaustDSP_H__

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


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

class FaustDSPSIG0 {
	
  private:
	
	int iRec4[2];
	
  public:
	
	int getNumInputsFaustDSPSIG0() {
		return 0;
	}
	int getNumOutputsFaustDSPSIG0() {
		return 1;
	}
	int getInputRateFaustDSPSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRateFaustDSPSIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitFaustDSPSIG0(int sample_rate) {
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec4[l2] = 0;
		}
	}
	
	void fillFaustDSPSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec4[0] = (iRec4[1] + 1);
			table[i] = std::cos((9.58738019e-05f * float((iRec4[0] + -1))));
			iRec4[1] = iRec4[0];
		}
	}

};

static FaustDSPSIG0* newFaustDSPSIG0() { return (FaustDSPSIG0*)new FaustDSPSIG0(); }
static void deleteFaustDSPSIG0(FaustDSPSIG0* dsp) { delete dsp; }

static float ftbl0FaustDSPSIG0[65536];
static float FaustDSP_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS FaustDSP
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#define FAUST_INPUTS 8
#define FAUST_OUTPUTS  8
#define FAUST_INT_CONTROLS 16
#define FAUST_REAL_CONTROLS 24

class FaustControls {
	
 public:
	
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT fVbargraph0;
	FAUSTFLOAT fVbargraph1;
	FAUSTFLOAT fVbargraph2;
	FAUSTFLOAT fVbargraph3;
	FAUSTFLOAT fVbargraph4;
	FAUSTFLOAT fVbargraph5;
	FAUSTFLOAT fVbargraph6;
	FAUSTFLOAT fVbargraph7;
	FAUSTFLOAT fVbargraph8;
	FAUSTFLOAT fVbargraph9;
	FAUSTFLOAT fVbargraph10;
	FAUSTFLOAT fVbargraph11;
	FAUSTFLOAT fVbargraph12;
	FAUSTFLOAT fVbargraph13;
	FAUSTFLOAT fVbargraph14;
	FAUSTFLOAT fVbargraph15;
	FAUSTFLOAT fVbargraph16;
	FAUSTFLOAT fVbargraph17;
	FAUSTFLOAT fVbargraph18;
	FAUSTFLOAT fVbargraph19;
	FAUSTFLOAT fVbargraph20;
	FAUSTFLOAT fVbargraph21;
	FAUSTFLOAT fVbargraph22;
	FAUSTFLOAT fVbargraph23;
	FAUSTFLOAT fVslider4;
	FAUSTFLOAT fVslider5;
	FAUSTFLOAT fVslider6;
	FAUSTFLOAT fVslider7;
	FAUSTFLOAT fVslider8;
	FAUSTFLOAT fVslider9;
	FAUSTFLOAT fVslider10;
	FAUSTFLOAT fVslider11;
	FAUSTFLOAT fVslider12;
	FAUSTFLOAT fVslider13;
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "main.dsp");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonhp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonhp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonhp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/resonlp:author", "Julius O. Smith III");
		m->declare("filters.lib/resonlp:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/resonlp:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.0");
		m->declare("name", "main");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 8;
	}

   virtual int getNumOutputs() {
		return 8;
	}

   virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(0.5f);
		fVslider1 = FAUSTFLOAT(0.5f);
		fVslider2 = FAUSTFLOAT(0.5f);
		fVslider3 = FAUSTFLOAT(0.5f);
		fVslider4 = FAUSTFLOAT(0.5f);
		fVslider5 = FAUSTFLOAT(0.5f);
		fVslider6 = FAUSTFLOAT(0.5f);
		fVslider7 = FAUSTFLOAT(0.5f);
		fVslider8 = FAUSTFLOAT(0.5f);
		fVslider9 = FAUSTFLOAT(0.5f);
		fVslider10 = FAUSTFLOAT(0.5f);
		fVslider11 = FAUSTFLOAT(0.5f);
		fVslider12 = FAUSTFLOAT(0.5f);
		fVslider13 = FAUSTFLOAT(0.5f);
		fVslider14 = FAUSTFLOAT(0.5f);
		fVslider15 = FAUSTFLOAT(0.5f);
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("ProtoFaust");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Knobs");
		ui_interface->declare(&fVslider2, "style", "knob");
		ui_interface->declare(&fVslider2, "variant", "knob-large-white");
		ui_interface->declare(&fVslider2, "x", "53.34");
		ui_interface->declare(&fVslider2, "y", "28.17");
		ui_interface->addVerticalSlider("1", &fVslider2, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider3, "style", "knob");
		ui_interface->declare(&fVslider3, "variant", "knob-large-red");
		ui_interface->declare(&fVslider3, "x", "78.74");
		ui_interface->declare(&fVslider3, "y", "28.17");
		ui_interface->addVerticalSlider("2", &fVslider3, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider9, "style", "knob");
		ui_interface->declare(&fVslider9, "variant", "knob-large-white");
		ui_interface->declare(&fVslider9, "x", "53.34");
		ui_interface->declare(&fVslider9, "y", "56.11");
		ui_interface->addVerticalSlider("3", &fVslider9, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider8, "style", "knob");
		ui_interface->declare(&fVslider8, "variant", "knob-large-red");
		ui_interface->declare(&fVslider8, "x", "78.74");
		ui_interface->declare(&fVslider8, "y", "56.11");
		ui_interface->addVerticalSlider("4", &fVslider8, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider7, "style", "knob");
		ui_interface->declare(&fVslider7, "variant", "knob-large-white");
		ui_interface->declare(&fVslider7, "x", "53.34");
		ui_interface->declare(&fVslider7, "y", "84.05");
		ui_interface->addVerticalSlider("5", &fVslider7, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider6, "style", "knob");
		ui_interface->declare(&fVslider6, "variant", "knob-large-red");
		ui_interface->declare(&fVslider6, "x", "78.74");
		ui_interface->declare(&fVslider6, "y", "84.05");
		ui_interface->addVerticalSlider("6", &fVslider6, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider5, "style", "knob");
		ui_interface->declare(&fVslider5, "variant", "knob-large-white");
		ui_interface->declare(&fVslider5, "x", "53.34");
		ui_interface->declare(&fVslider5, "y", "111.99");
		ui_interface->addVerticalSlider("7", &fVslider5, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider4, "style", "knob");
		ui_interface->declare(&fVslider4, "variant", "knob-large-red");
		ui_interface->declare(&fVslider4, "x", "78.74");
		ui_interface->declare(&fVslider4, "y", "111.99");
		ui_interface->addVerticalSlider("8", &fVslider4, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Buttons");
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->declare(&fVslider1, "variant", "switch-three-way");
		ui_interface->declare(&fVslider1, "x", "31.75");
		ui_interface->declare(&fVslider1, "y", "21.82");
		ui_interface->addVerticalSlider("1", &fVslider1, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider15, "style", "knob");
		ui_interface->declare(&fVslider15, "variant", "switch-three-way");
		ui_interface->declare(&fVslider15, "x", "31.75");
		ui_interface->declare(&fVslider15, "y", "34.52");
		ui_interface->addVerticalSlider("2", &fVslider15, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider14, "style", "knob");
		ui_interface->declare(&fVslider14, "variant", "switch-toggle");
		ui_interface->declare(&fVslider14, "x", "31.75");
		ui_interface->declare(&fVslider14, "y", "49.76");
		ui_interface->addVerticalSlider("3", &fVslider14, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->declare(&fVslider0, "variant", "switch-toggle");
		ui_interface->declare(&fVslider0, "x", "31.75");
		ui_interface->declare(&fVslider0, "y", "62.46");
		ui_interface->addVerticalSlider("4", &fVslider0, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider13, "style", "knob");
		ui_interface->declare(&fVslider13, "variant", "switch-momentary");
		ui_interface->declare(&fVslider13, "x", "31.75");
		ui_interface->declare(&fVslider13, "y", "77.70");
		ui_interface->addVerticalSlider("5", &fVslider13, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider12, "style", "knob");
		ui_interface->declare(&fVslider12, "variant", "switch-momentary");
		ui_interface->declare(&fVslider12, "x", "31.75");
		ui_interface->declare(&fVslider12, "y", "90.40");
		ui_interface->addVerticalSlider("6", &fVslider12, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider11, "style", "knob");
		ui_interface->declare(&fVslider11, "variant", "switch-momentary");
		ui_interface->declare(&fVslider11, "x", "31.75");
		ui_interface->declare(&fVslider11, "y", "105.64");
		ui_interface->addVerticalSlider("7", &fVslider11, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fVslider10, "style", "knob");
		ui_interface->declare(&fVslider10, "variant", "switch-momentary");
		ui_interface->declare(&fVslider10, "x", "31.75");
		ui_interface->declare(&fVslider10, "y", "118.34");
		ui_interface->addVerticalSlider("8", &fVslider10, 0.5f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("Lights");
		ui_interface->declare(&fVbargraph21, "style", "led");
		ui_interface->declare(&fVbargraph21, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("1_Blue", &fVbargraph21, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph22, "style", "led");
		ui_interface->declare(&fVbargraph22, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("1_Green", &fVbargraph22, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph23, "style", "led");
		ui_interface->declare(&fVbargraph23, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph23, "x", "99.06");
		ui_interface->declare(&fVbargraph23, "y", "21.82");
		ui_interface->addVerticalBargraph("1_Red", &fVbargraph23, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph18, "style", "led");
		ui_interface->declare(&fVbargraph18, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("2_Blue", &fVbargraph18, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph19, "style", "led");
		ui_interface->declare(&fVbargraph19, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("2_Green", &fVbargraph19, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph20, "style", "led");
		ui_interface->declare(&fVbargraph20, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph20, "x", "99.06");
		ui_interface->declare(&fVbargraph20, "y", "34.52");
		ui_interface->addVerticalBargraph("2_Red", &fVbargraph20, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph15, "style", "led");
		ui_interface->declare(&fVbargraph15, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("3_Blue", &fVbargraph15, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph16, "style", "led");
		ui_interface->declare(&fVbargraph16, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("3_Green", &fVbargraph16, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph17, "style", "led");
		ui_interface->declare(&fVbargraph17, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph17, "x", "99.06");
		ui_interface->declare(&fVbargraph17, "y", "49.76");
		ui_interface->addVerticalBargraph("3_Red", &fVbargraph17, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph12, "style", "led");
		ui_interface->declare(&fVbargraph12, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("4_Blue", &fVbargraph12, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph13, "style", "led");
		ui_interface->declare(&fVbargraph13, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("4_Green", &fVbargraph13, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph14, "style", "led");
		ui_interface->declare(&fVbargraph14, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph14, "x", "99.06");
		ui_interface->declare(&fVbargraph14, "y", "62.46");
		ui_interface->addVerticalBargraph("4_Red", &fVbargraph14, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph9, "style", "led");
		ui_interface->declare(&fVbargraph9, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("5_Blue", &fVbargraph9, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph10, "style", "led");
		ui_interface->declare(&fVbargraph10, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("5_Green", &fVbargraph10, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph11, "style", "led");
		ui_interface->declare(&fVbargraph11, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph11, "x", "99.06");
		ui_interface->declare(&fVbargraph11, "y", "77.70");
		ui_interface->addVerticalBargraph("5_Red", &fVbargraph11, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph6, "style", "led");
		ui_interface->declare(&fVbargraph6, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("6_Blue", &fVbargraph6, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph7, "style", "led");
		ui_interface->declare(&fVbargraph7, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("6_Green", &fVbargraph7, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph8, "style", "led");
		ui_interface->declare(&fVbargraph8, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph8, "x", "99.06");
		ui_interface->declare(&fVbargraph8, "y", "90.40");
		ui_interface->addVerticalBargraph("6_Red", &fVbargraph8, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph3, "style", "led");
		ui_interface->declare(&fVbargraph3, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("7_Blue", &fVbargraph3, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph4, "style", "led");
		ui_interface->declare(&fVbargraph4, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("7_Green", &fVbargraph4, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph5, "style", "led");
		ui_interface->declare(&fVbargraph5, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph5, "x", "99.06");
		ui_interface->declare(&fVbargraph5, "y", "105.64");
		ui_interface->addVerticalBargraph("7_Red", &fVbargraph5, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph0, "style", "led");
		ui_interface->declare(&fVbargraph0, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("8_Blue", &fVbargraph0, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph1, "style", "led");
		ui_interface->declare(&fVbargraph1, "variant", "led-rgb");
		ui_interface->addVerticalBargraph("8_Green", &fVbargraph1, 0.0f, 1.0f);
		ui_interface->declare(&fVbargraph2, "style", "led");
		ui_interface->declare(&fVbargraph2, "variant", "led-rgb");
		ui_interface->declare(&fVbargraph2, "x", "99.06");
		ui_interface->declare(&fVbargraph2, "y", "118.34");
		ui_interface->addVerticalBargraph("8_Red", &fVbargraph2, 0.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}

	virtual int getNumIntControls() { return 16; }

   virtual int getNumRealControls() { return 24; }
};

class FaustDSP : public one_sample_dsp {
	
 private:
   FaustControls controls;
	
	int iVec0[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fRec3[2];
	float fConst2;
	float fRec5[2];
	float fRec1[2];
	float fConst3;
	float fRec6[2];
	float fVec1[2];
	int IOTA;
	float fVec2[4096];
	float fConst4;
	float fConst5;
	float fRec7[2];
	float fRec10[2];
	float fRec8[2];
	float fRec11[2];
	float fVec3[2];
	float fVec4[4096];
	float fRec12[2];
	float fRec15[2];
	float fRec13[2];
	float fRec16[2];
	float fVec5[2];
	float fVec6[4096];
	float fRec17[2];
	float fConst6;
	float fRec19[2];
	float fRec20[2];
	float fRec18[3];
	float fVec7[2];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) {
       controls.metadata(m);
	}

	virtual int getNumInputs() {
		return controls.getNumInputs();
	}

   virtual int getNumOutputs() {
		return controls.getNumOutputs();
	}

   virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			case 2: {
				rate = 1;
				break;
			}
			case 3: {
				rate = 1;
				break;
			}
			case 4: {
				rate = 1;
				break;
			}
			case 5: {
				rate = 1;
				break;
			}
			case 6: {
				rate = 1;
				break;
			}
			case 7: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
		FaustDSPSIG0* sig0 = newFaustDSPSIG0();
		sig0->instanceInitFaustDSPSIG0(sample_rate);
		sig0->fillFaustDSPSIG0(65536, ftbl0FaustDSPSIG0);
		deleteFaustDSPSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.5f / fConst0);
		fConst3 = (0.25f * fConst0);
		fConst4 = (0.5f * fConst0);
		fConst5 = (1760.0f / fConst0);
		fConst6 = (3.14159274f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
       controls.instanceResetUserInterface();
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec3[l1] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec5[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;
		}
		IOTA = 0;
		for (int l7 = 0; (l7 < 4096); l7 = (l7 + 1)) {
			fVec2[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec10[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec3[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 4096); l13 = (l13 + 1)) {
			fVec4[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec12[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec15[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec13[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec5[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 4096); l19 = (l19 + 1)) {
			fVec6[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec17[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec19[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec20[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec18[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec7[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec0[l25] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}

   virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual FaustDSP* clone() {
		return new FaustDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
       controls.buildUserInterface(ui_interface);
	}

   virtual void control(int* iControl, FAUSTFLOAT* fControl) {
		fControl[0] = float(controls.fVslider0);
		iControl[0] = ((2.0f * fControl[0]) >= 1.0f);
		fControl[1] = float(controls.fVslider1);
		fControl[2] = (2.0f * fControl[1]);
		iControl[1] = (fControl[2] >= 2.0f);
		iControl[2] = (fControl[2] >= 1.0f);
		fControl[3] = float(controls.fVslider2);
		fControl[4] = float(controls.fVslider3);
		fControl[5] = (0.999000013f * ((0.0166666675f * float(int(((48.0f * fControl[3]) + -12.0f)))) + (0.0333333351f * (fControl[4] + -0.5f))));
		controls.fVbargraph1 = FAUSTFLOAT(0);
		iControl[3] = int(controls.fVbargraph1);
		controls.fVbargraph5 = FAUSTFLOAT(0);
		iControl[4] = int(controls.fVbargraph5);
		controls.fVbargraph6 = FAUSTFLOAT(0);
		iControl[5] = int(controls.fVbargraph6);
		controls.fVbargraph16 = FAUSTFLOAT(0);
		iControl[6] = int(controls.fVbargraph16);
		controls.fVbargraph17 = FAUSTFLOAT(0);
		iControl[7] = int(controls.fVbargraph17);
		controls.fVbargraph18 = FAUSTFLOAT(0);
		iControl[8] = int(controls.fVbargraph18);
		controls.fVbargraph20 = FAUSTFLOAT(0);
		iControl[9] = int(controls.fVbargraph20);
		controls.fVbargraph21 = FAUSTFLOAT(0);
		iControl[10] = int(controls.fVbargraph21);
		controls.fVbargraph22 = FAUSTFLOAT(0);
		iControl[11] = int(controls.fVbargraph22);
		fControl[6] = float(controls.fVslider4);
		fControl[7] = float(controls.fVslider5);
		fControl[8] = float(controls.fVslider6);
		fControl[9] = float(controls.fVslider7);
		fControl[10] = float(controls.fVslider8);
		fControl[11] = float(controls.fVslider9);
		fControl[12] = float(controls.fVslider10);
		fControl[13] = float(controls.fVslider11);
		fControl[14] = float(controls.fVslider12);
		fControl[15] = float(controls.fVslider13);
		fControl[16] = float(controls.fVslider14);
		fControl[17] = float(controls.fVslider15);
		fControl[18] = (2.0f * fControl[17]);
		iControl[12] = (fControl[18] >= 2.0f);
		iControl[13] = (fControl[18] >= 1.0f);
		fControl[19] = (0.999000013f * ((0.0166666675f * float(int(((48.0f * fControl[11]) + -12.0f)))) + (0.0333333351f * (fControl[10] + -0.5f))));
		fControl[20] = ((2.0f * fControl[16]) + 1.0f);
		iControl[14] = (fControl[20] >= 2.0f);
		iControl[15] = (fControl[20] >= 1.0f);
		fControl[21] = (0.999000013f * ((0.0166666675f * float(int(((48.0f * fControl[9]) + -12.0f)))) + (0.0333333351f * (fControl[8] + -0.5f))));
		fControl[22] = (0.999000013f * fControl[7]);
		fControl[23] = (0.999000013f * fControl[6]);
	}

   virtual int getNumIntControls() {
      return controls.getNumIntControls();
   }

   virtual int getNumRealControls() {
      return controls.getNumRealControls();
    }
	
	virtual void compute(FAUSTFLOAT* inputs, FAUSTFLOAT* outputs, int* iControl, FAUSTFLOAT* fControl) {
		iVec0[0] = 1;
		fRec3[0] = (fControl[5] + (0.00100000005f * fRec3[1]));
		fRec5[0] = (fConst2 + (fRec5[1] - std::floor((fConst2 + fRec5[1]))));
		float fTemp0 = (0.5f * (ftbl0FaustDSPSIG0[int((65536.0f * fRec5[0]))] + 1.0f));
		float fTemp1 = (1.0f - fTemp0);
		controls.fVbargraph0 = FAUSTFLOAT(fTemp1);
		controls.fVbargraph2 = FAUSTFLOAT(fTemp0);
		controls.fVbargraph3 = FAUSTFLOAT(fTemp1);
		controls.fVbargraph4 = FAUSTFLOAT(fTemp0);
		controls.fVbargraph7 = FAUSTFLOAT(fTemp1);
		controls.fVbargraph8 = FAUSTFLOAT(fTemp0);
		controls.fVbargraph9 = FAUSTFLOAT(fTemp0);
		controls.fVbargraph10 = FAUSTFLOAT(fTemp0);
		controls.fVbargraph11 = FAUSTFLOAT(fTemp0);
		controls.fVbargraph12 = FAUSTFLOAT(fTemp1);
		controls.fVbargraph13 = FAUSTFLOAT(fTemp1);
		controls.fVbargraph14 = FAUSTFLOAT(fTemp1);
		controls.fVbargraph15 = FAUSTFLOAT(fTemp0);
		controls.fVbargraph19 = FAUSTFLOAT(fTemp1);
		controls.fVbargraph23 = FAUSTFLOAT(fTemp0);
		float fTemp2 = float(inputs[0]);
		float fTemp3 = std::pow(2.0f, ((5.0f * (fRec3[0] + fTemp2)) + -0.75f));
		float fTemp4 = (440.0f * fTemp3);
		float fTemp5 = std::max<float>(1.00000001e-07f, std::fabs(fTemp4));
		float fTemp6 = (fRec1[1] + (fConst1 * fTemp5));
		float fTemp7 = (fTemp6 + -1.0f);
		int iTemp8 = (fTemp7 < 0.0f);
		fRec1[0] = (iTemp8 ? fTemp6 : fTemp7);
		float fRec2 = (iTemp8 ? fTemp6 : (fTemp6 + (fTemp7 * (1.0f - (fConst0 / fTemp5)))));
		float fTemp9 = float(iVec0[1]);
		float fTemp10 = std::max<float>(fTemp4, 23.4489498f);
		float fTemp11 = std::max<float>(20.0f, std::fabs(fTemp10));
		float fTemp12 = (fRec6[1] + (fConst1 * fTemp11));
		fRec6[0] = (fTemp12 - std::floor(fTemp12));
		float fTemp13 = FaustDSP_faustpower2_f(((2.0f * fRec6[0]) + -1.0f));
		fVec1[0] = fTemp13;
		float fTemp14 = ((fTemp9 * (fTemp13 - fVec1[1])) / fTemp11);
		fVec2[(IOTA & 4095)] = fTemp14;
		float fTemp15 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst4 / fTemp10)));
		int iTemp16 = int(fTemp15);
		float fTemp17 = std::floor(fTemp15);
		float fTemp18 = (fConst3 * ((fTemp14 - (fVec2[((IOTA - iTemp16) & 4095)] * (fTemp17 + (1.0f - fTemp15)))) - ((fTemp15 - fTemp17) * fVec2[((IOTA - (iTemp16 + 1)) & 4095)])));
		fRec7[0] = (fTemp18 + (0.999000013f * fRec7[1]));
		fRec10[0] = (fControl[19] + (0.00100000005f * fRec10[1]));
		float fTemp19 = std::pow(2.0f, ((5.0f * (fRec10[0] + fTemp2)) + -0.75f));
		float fTemp20 = (440.0f * fTemp19);
		float fTemp21 = std::max<float>(1.00000001e-07f, std::fabs(fTemp20));
		float fTemp22 = (fRec8[1] + (fConst1 * fTemp21));
		float fTemp23 = (fTemp22 + -1.0f);
		int iTemp24 = (fTemp23 < 0.0f);
		fRec8[0] = (iTemp24 ? fTemp22 : fTemp23);
		float fRec9 = (iTemp24 ? fTemp22 : (fTemp22 + (fTemp23 * (1.0f - (fConst0 / fTemp21)))));
		float fTemp25 = std::max<float>(fTemp20, 23.4489498f);
		float fTemp26 = std::max<float>(20.0f, std::fabs(fTemp25));
		float fTemp27 = (fRec11[1] + (fConst1 * fTemp26));
		fRec11[0] = (fTemp27 - std::floor(fTemp27));
		float fTemp28 = FaustDSP_faustpower2_f(((2.0f * fRec11[0]) + -1.0f));
		fVec3[0] = fTemp28;
		float fTemp29 = ((fTemp9 * (fTemp28 - fVec3[1])) / fTemp26);
		fVec4[(IOTA & 4095)] = fTemp29;
		float fTemp30 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst4 / fTemp25)));
		int iTemp31 = int(fTemp30);
		float fTemp32 = std::floor(fTemp30);
		float fTemp33 = (fConst3 * ((fTemp29 - (fVec4[((IOTA - iTemp31) & 4095)] * (fTemp32 + (1.0f - fTemp30)))) - ((fTemp30 - fTemp32) * fVec4[((IOTA - (iTemp31 + 1)) & 4095)])));
		fRec12[0] = (fTemp33 + (0.999000013f * fRec12[1]));
		fRec15[0] = (fControl[21] + (0.00100000005f * fRec15[1]));
		float fTemp34 = std::pow(2.0f, ((5.0f * (fRec15[0] + fTemp2)) + -0.75f));
		float fTemp35 = (440.0f * fTemp34);
		float fTemp36 = std::max<float>(1.00000001e-07f, std::fabs(fTemp35));
		float fTemp37 = (fRec13[1] + (fConst1 * fTemp36));
		float fTemp38 = (fTemp37 + -1.0f);
		int iTemp39 = (fTemp38 < 0.0f);
		fRec13[0] = (iTemp39 ? fTemp37 : fTemp38);
		float fRec14 = (iTemp39 ? fTemp37 : (fTemp37 + (fTemp38 * (1.0f - (fConst0 / fTemp36)))));
		float fTemp40 = std::max<float>(fTemp35, 23.4489498f);
		float fTemp41 = std::max<float>(20.0f, std::fabs(fTemp40));
		float fTemp42 = (fRec16[1] + (fConst1 * fTemp41));
		fRec16[0] = (fTemp42 - std::floor(fTemp42));
		float fTemp43 = FaustDSP_faustpower2_f(((2.0f * fRec16[0]) + -1.0f));
		fVec5[0] = fTemp43;
		float fTemp44 = ((fTemp9 * (fTemp43 - fVec5[1])) / fTemp41);
		fVec6[(IOTA & 4095)] = fTemp44;
		float fTemp45 = std::max<float>(0.0f, std::min<float>(2047.0f, (fConst4 / fTemp40)));
		int iTemp46 = int(fTemp45);
		float fTemp47 = std::floor(fTemp45);
		float fTemp48 = (fConst3 * ((fTemp44 - (fVec6[((IOTA - iTemp46) & 4095)] * (fTemp47 + (1.0f - fTemp45)))) - ((fTemp45 - fTemp47) * fVec6[((IOTA - (iTemp46 + 1)) & 4095)])));
		fRec17[0] = (fTemp48 + (0.999000013f * fRec17[1]));
		float fTemp49 = (0.125892535f * (((iControl[1] ? (fConst5 * (fRec7[0] * fTemp3)) : (iControl[2] ? fTemp18 : ((2.0f * fRec2) + -1.0f))) + (iControl[12] ? (fConst5 * (fRec12[0] * fTemp19)) : (iControl[13] ? fTemp33 : ((2.0f * fRec9) + -1.0f)))) + (iControl[14] ? (fConst5 * (fRec17[0] * fTemp34)) : (iControl[15] ? fTemp48 : ((2.0f * fRec14) + -1.0f)))));
		float fTemp50 = float(inputs[1]);
		fRec19[0] = (fControl[22] + (0.00100000005f * fRec19[1]));
		float fTemp51 = std::tan((fConst6 * std::max<float>(10.0f, std::min<float>((440.0f * std::pow(2.0f, ((5.0f * ((1.5f * (fTemp50 + fRec19[0])) + -0.5f)) + -0.75f))), 20000.0f))));
		float fTemp52 = (1.0f / fTemp51);
		float fTemp53 = float(inputs[2]);
		fRec20[0] = (fControl[23] + (0.00100000005f * fRec20[1]));
		float fTemp54 = (1.0f / std::max<float>((5.0f * (fTemp53 + fRec20[0])), 0.100000001f));
		float fTemp55 = (((fTemp52 + fTemp54) / fTemp51) + 1.0f);
		fRec18[0] = (fTemp49 - (((fRec18[2] * (((fTemp52 - fTemp54) / fTemp51) + 1.0f)) + (2.0f * (fRec18[1] * (1.0f - (1.0f / FaustDSP_faustpower2_f(fTemp51)))))) / fTemp55));
		float fTemp56 = ((fRec18[2] + (fRec18[0] + (2.0f * fRec18[1]))) / fTemp55);
		float fTemp57 = std::max<float>(-1.0f, std::min<float>(1.0f, ((3.98107171f * (iControl[0] ? fTemp56 : (fTemp49 - fTemp56))) + 0.100000001f)));
		float fTemp58 = (fTemp57 * (1.0f - (0.333333343f * FaustDSP_faustpower2_f(fTemp57))));
		fVec7[0] = fTemp58;
		fRec0[0] = (((0.995000005f * fRec0[1]) + fTemp58) - fVec7[1]);
		outputs[0] = FAUSTFLOAT(fRec0[0]);
		outputs[1] = FAUSTFLOAT(fTemp50);
		outputs[2] = FAUSTFLOAT(fTemp53);
		outputs[3] = FAUSTFLOAT(float(inputs[3]));
		outputs[4] = FAUSTFLOAT(float(inputs[4]));
		outputs[5] = FAUSTFLOAT(float(inputs[5]));
		outputs[6] = FAUSTFLOAT(float(inputs[6]));
		outputs[7] = FAUSTFLOAT(float(inputs[7]));
		iVec0[1] = iVec0[0];
		fRec3[1] = fRec3[0];
		fRec5[1] = fRec5[0];
		fRec1[1] = fRec1[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		IOTA = (IOTA + 1);
		fRec7[1] = fRec7[0];
		fRec10[1] = fRec10[0];
		fRec8[1] = fRec8[0];
		fRec11[1] = fRec11[0];
		fVec3[1] = fVec3[0];
		fRec12[1] = fRec12[0];
		fRec15[1] = fRec15[0];
		fRec13[1] = fRec13[0];
		fRec16[1] = fRec16[0];
		fVec5[1] = fVec5[0];
		fRec17[1] = fRec17[0];
		fRec19[1] = fRec19[0];
		fRec20[1] = fRec20[0];
		fRec18[2] = fRec18[1];
		fRec18[1] = fRec18[0];
		fVec7[1] = fVec7[0];
		fRec0[1] = fRec0[0];
	}

};

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

      KNOB_LARGE_BLACK,
      KNOB_LARGE_WHITE,
      KNOB_LARGE_RED,
      KNOB_SMALL_BLACK,
      KNOB_SMALL_WHITE,
      KNOB_SMALL_RED,

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

      if ( strcmp( key, "x" ) == 0 ) {
         fPositionX[zone] = std::atof( val );

      } else if ( strcmp( key, "y" ) == 0 ) {
         fPositionY[zone] = std::atof( val );

      } else if ( strcmp( key, "variant" ) == 0 ) {
         if ( strcmp( val, "knob-large-black" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::KNOB_LARGE_BLACK;

         } else if ( strcmp( val, "knob-large-white" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::KNOB_LARGE_WHITE;

         } else if ( strcmp( val, "knob-large-red" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::KNOB_LARGE_RED;


         } else if ( strcmp( val, "knob-small-black" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::KNOB_SMALL_BLACK;

         } else if ( strcmp( val, "knob-small-white" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::KNOB_SMALL_WHITE;

         } else if ( strcmp( val, "knob-small-red" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::KNOB_SMALL_RED;


         } else if ( strcmp( val, "switch-toggle" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::SWITCH_TOGGLE;

         } else if ( strcmp( val, "switch-three-way" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::SWITCH_THREE_WAY;

         } else if ( strcmp( val, "switch-momentary" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::SWITCH_MOMENTARY;


         } else if ( strcmp( val, "led-rgb" ) == 0 ) {
            fWidgetTypeMap[zone] = WidgetTypes::LED_RGB;


         } else {
            fWidgetTypeMap[zone] = -1;
         }
      }
   }


   double getPositionX( FAUSTFLOAT* zone )
   {
      if ( fPositionX.find( zone ) != fPositionX.end() ) {
         return fPositionX[zone];
      } else {
         return -1.0;
      }
   }


   double getPositionY( FAUSTFLOAT* zone )
   {
      if ( fPositionY.find( zone ) != fPositionY.end() ) {
         return fPositionY[zone];
      } else {
         return -1.0;
      }
   }


   int getWidgetType( FAUSTFLOAT* zone )
   {
      if ( fWidgetTypeMap.find( zone ) != fWidgetTypeMap.end() ) {
         return fWidgetTypeMap[zone];
      } else {
         return -1;
      }
   }


protected:
   std::map<FAUSTFLOAT*, double> fPositionX;
   std::map<FAUSTFLOAT*, double> fPositionY;

   std::map<FAUSTFLOAT*, int> fWidgetTypeMap;
};

/********************END ARCHITECTURE SECTION (part 2/2)****************/

#endif
