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


#include "plugin.hpp"

namespace faust {
#include "faust_generated.cpp"
}


struct ProtoFaust : Module {
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

    enum LightIds {
        LED_1_LIGHT_R,
        LED_1_LIGHT_G,
        LED_1_LIGHT_B,

        LED_2_LIGHT_R,
        LED_2_LIGHT_G,
        LED_2_LIGHT_B,

        LED_3_LIGHT_R,
        LED_3_LIGHT_G,
        LED_3_LIGHT_B,

        LED_4_LIGHT_R,
        LED_4_LIGHT_G,
        LED_4_LIGHT_B,

        LED_5_LIGHT_R,
        LED_5_LIGHT_G,
        LED_5_LIGHT_B,

        LED_6_LIGHT_R,
        LED_6_LIGHT_G,
        LED_6_LIGHT_B,

        LED_7_LIGHT_R,
        LED_7_LIGHT_G,
        LED_7_LIGHT_B,

        LED_8_LIGHT_R,
        LED_8_LIGHT_G,
        LED_8_LIGHT_B,

        NUM_LIGHTS
    };


    faust::FaustDSP FaustDSP;
    faust::APIUI FaustUI;

    // variables for storing GUI IDs
    int paramButton_1 = -1;
    int paramButton_2 = -1;
    int paramButton_3 = -1;
    int paramButton_4 = -1;
    int paramButton_5 = -1;
    int paramButton_6 = -1;
    int paramButton_7 = -1;
    int paramButton_8 = -1;

    int paramKnob_1 = -1;
    int paramKnob_2 = -1;
    int paramKnob_3 = -1;
    int paramKnob_4 = -1;
    int paramKnob_5 = -1;
    int paramKnob_6 = -1;
    int paramKnob_7 = -1;
    int paramKnob_8 = -1;

    int paramLight_1_r = -1;
    int paramLight_1_g = -1;
    int paramLight_1_b = -1;

    int paramLight_2_r = -1;
    int paramLight_2_g = -1;
    int paramLight_2_b = -1;

    int paramLight_3_r = -1;
    int paramLight_3_g = -1;
    int paramLight_3_b = -1;

    int paramLight_4_r = -1;
    int paramLight_4_g = -1;
    int paramLight_4_b = -1;

    int paramLight_5_r = -1;
    int paramLight_5_g = -1;
    int paramLight_5_b = -1;

    int paramLight_6_r = -1;
    int paramLight_6_g = -1;
    int paramLight_6_b = -1;

    int paramLight_7_r = -1;
    int paramLight_7_g = -1;
    int paramLight_7_b = -1;

    int paramLight_8_r = -1;
    int paramLight_8_g = -1;
    int paramLight_8_b = -1;

    const int numberOfChannels = 8;
    const FAUSTFLOAT voltageScaling = 5.0f;

    ProtoFaust() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

        // three-way switches
        // values:  0.0, 0.5, 1.0; see ProtoFaust::process()
        // default: 0.0 (off)
        configParam(BUTTON_1_PARAM, 0.0f, 2.0f, 0.0f, "");
        configParam(BUTTON_2_PARAM, 0.0f, 2.0f, 0.0f, "");

        // two-way switches
        // values:  0.0, 1.0
        // default: 0.0 (off)
        configParam(BUTTON_3_PARAM, 0.0f, 1.0f, 0.0f, "");
        configParam(BUTTON_4_PARAM, 0.0f, 1.0f, 0.0f, "");

        // momentary push buttons
        // values:  0.0, 1.0
        // default: 0.0 (off)
        configParam(BUTTON_5_PARAM, 0.0f, 1.0f, 0.0f, "");
        configParam(BUTTON_6_PARAM, 0.0f, 1.0f, 0.0f, "");
        configParam(BUTTON_7_PARAM, 0.0f, 1.0f, 0.0f, "");
        configParam(BUTTON_8_PARAM, 0.0f, 1.0f, 0.0f, "");

        // big knobs
        // range:   0.0 to 1.0
        // default: 0.5 (centered)
        configParam(KNOB_1_PARAM, 0.0f, 1.0f, 0.5f, "");
        configParam(KNOB_2_PARAM, 0.0f, 1.0f, 0.5f, "");
        configParam(KNOB_3_PARAM, 0.0f, 1.0f, 0.5f, "");
        configParam(KNOB_4_PARAM, 0.0f, 1.0f, 0.5f, "");
        configParam(KNOB_5_PARAM, 0.0f, 1.0f, 0.5f, "");
        configParam(KNOB_6_PARAM, 0.0f, 1.0f, 0.5f, "");
        configParam(KNOB_7_PARAM, 0.0f, 1.0f, 0.5f, "");
        configParam(KNOB_8_PARAM, 0.0f, 1.0f, 0.5f, "");
    }


    void onAdd() override {
        // Activate the UI
        FaustDSP.buildUserInterface(&FaustUI);

        // store GUI IDs to save time during processing
        paramButton_1 = FaustUI.getParamIndex("/ProtoFaust/Buttons/1");
        paramButton_2 = FaustUI.getParamIndex("/ProtoFaust/Buttons/2");
        paramButton_3 = FaustUI.getParamIndex("/ProtoFaust/Buttons/3");
        paramButton_4 = FaustUI.getParamIndex("/ProtoFaust/Buttons/4");
        paramButton_5 = FaustUI.getParamIndex("/ProtoFaust/Buttons/5");
        paramButton_6 = FaustUI.getParamIndex("/ProtoFaust/Buttons/6");
        paramButton_7 = FaustUI.getParamIndex("/ProtoFaust/Buttons/7");
        paramButton_8 = FaustUI.getParamIndex("/ProtoFaust/Buttons/8");

        paramKnob_1 = FaustUI.getParamIndex("/ProtoFaust/Knobs/1");
        paramKnob_2 = FaustUI.getParamIndex("/ProtoFaust/Knobs/2");
        paramKnob_3 = FaustUI.getParamIndex("/ProtoFaust/Knobs/3");
        paramKnob_4 = FaustUI.getParamIndex("/ProtoFaust/Knobs/4");
        paramKnob_5 = FaustUI.getParamIndex("/ProtoFaust/Knobs/5");
        paramKnob_6 = FaustUI.getParamIndex("/ProtoFaust/Knobs/6");
        paramKnob_7 = FaustUI.getParamIndex("/ProtoFaust/Knobs/7");
        paramKnob_8 = FaustUI.getParamIndex("/ProtoFaust/Knobs/8");

        paramLight_1_r = FaustUI.getParamIndex("/ProtoFaust/Lights/1_R");
        paramLight_1_g = FaustUI.getParamIndex("/ProtoFaust/Lights/1_G");
        paramLight_1_b = FaustUI.getParamIndex("/ProtoFaust/Lights/1_B");

        paramLight_2_r = FaustUI.getParamIndex("/ProtoFaust/Lights/2_R");
        paramLight_2_g = FaustUI.getParamIndex("/ProtoFaust/Lights/2_G");
        paramLight_2_b = FaustUI.getParamIndex("/ProtoFaust/Lights/2_B");

        paramLight_3_r = FaustUI.getParamIndex("/ProtoFaust/Lights/3_R");
        paramLight_3_g = FaustUI.getParamIndex("/ProtoFaust/Lights/3_G");
        paramLight_3_b = FaustUI.getParamIndex("/ProtoFaust/Lights/3_B");

        paramLight_4_r = FaustUI.getParamIndex("/ProtoFaust/Lights/4_R");
        paramLight_4_g = FaustUI.getParamIndex("/ProtoFaust/Lights/4_G");
        paramLight_4_b = FaustUI.getParamIndex("/ProtoFaust/Lights/4_B");

        paramLight_5_r = FaustUI.getParamIndex("/ProtoFaust/Lights/5_R");
        paramLight_5_g = FaustUI.getParamIndex("/ProtoFaust/Lights/5_G");
        paramLight_5_b = FaustUI.getParamIndex("/ProtoFaust/Lights/5_B");

        paramLight_6_r = FaustUI.getParamIndex("/ProtoFaust/Lights/6_R");
        paramLight_6_g = FaustUI.getParamIndex("/ProtoFaust/Lights/6_G");
        paramLight_6_b = FaustUI.getParamIndex("/ProtoFaust/Lights/6_B");

        paramLight_7_r = FaustUI.getParamIndex("/ProtoFaust/Lights/7_R");
        paramLight_7_g = FaustUI.getParamIndex("/ProtoFaust/Lights/7_G");
        paramLight_7_b = FaustUI.getParamIndex("/ProtoFaust/Lights/7_B");

        paramLight_8_r = FaustUI.getParamIndex("/ProtoFaust/Lights/8_R");
        paramLight_8_g = FaustUI.getParamIndex("/ProtoFaust/Lights/8_G");
        paramLight_8_b = FaustUI.getParamIndex("/ProtoFaust/Lights/8_B");

        // initialize sample rate in Faust
        int sampleRate = APP->engine->getSampleRate();
        FaustDSP.init(sampleRate);
    }


    void onSampleRateChange() override {
        int sampleRate = APP->engine->getSampleRate();
        // update sample rate in Faust
        FaustDSP.instanceConstants(sampleRate);
    }


    void process(const ProcessArgs &args) override {
        std::vector<FAUSTFLOAT> temporaryInputs(numberOfChannels);
        std::vector<FAUSTFLOAT> temporaryOutputs(numberOfChannels);

        // initialize inputs and outputs
        for (int channel = 0; channel < numberOfChannels; channel++) {
            // get input voltages from Rack
            FAUSTFLOAT input = inputs[IN_1_INPUT + channel].getVoltage();

            // scale voltages from Rack to value range of Faust (-1.0 to +1.0)
            temporaryInputs[channel] = input / voltageScaling;

            // silence temporary outputs (might protect your ears in case of misbehaviour)
            temporaryOutputs[channel] = 0.0;
        }

        FAUSTFLOAT value;

        // copy parameter values from Rack to Faust
        value = params[BUTTON_1_PARAM].getValue();
        // scale range to (0 .. 1)
        value /= 2.0f;
        FaustUI.setParamValue(paramButton_1, value);

        value = params[BUTTON_2_PARAM].getValue();
        // scale range to (0 .. 1)
        value /= 2.0f;
        FaustUI.setParamValue(paramButton_2, value);

        value = params[BUTTON_3_PARAM].getValue();
        FaustUI.setParamValue(paramButton_3, value);

        value = params[BUTTON_4_PARAM].getValue();
        FaustUI.setParamValue(paramButton_4, value);

        value = params[BUTTON_5_PARAM].getValue();
        FaustUI.setParamValue(paramButton_5, value);

        value = params[BUTTON_6_PARAM].getValue();
        FaustUI.setParamValue(paramButton_6, value);

        value = params[BUTTON_7_PARAM].getValue();
        FaustUI.setParamValue(paramButton_7, value);

        value = params[BUTTON_8_PARAM].getValue();
        FaustUI.setParamValue(paramButton_8, value);

        value = params[KNOB_1_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_1, value);

        value = params[KNOB_2_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_2, value);

        value = params[KNOB_3_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_3, value);

        value = params[KNOB_4_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_4, value);

        value = params[KNOB_5_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_5, value);

        value = params[KNOB_6_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_6, value);

        value = params[KNOB_7_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_7, value);

        value = params[KNOB_8_PARAM].getValue();
        FaustUI.setParamValue(paramKnob_8, value);

        int int_control[FaustDSP.getNumIntControls()];
        FAUSTFLOAT real_control[FaustDSP.getNumRealControls()];

        // update Faust controls
        FaustDSP.control(int_control, real_control);

        // compute one sample in Faust
        FaustDSP.compute(temporaryInputs.data(), temporaryOutputs.data(), int_control, real_control);

        // update inputs and outputs
        for (int channel = 0; channel < numberOfChannels; channel++) {
            // update output voltages
            FAUSTFLOAT output = temporaryOutputs[channel];

            // scale voltages from Faust back to value range of Rack (-5.0 to +5.0)
            outputs[OUT_1_OUTPUT + channel].setVoltage(output * voltageScaling);
        }

        // update RGB LEDs
        lights[LED_1_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_1_r));
        lights[LED_1_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_1_g));
        lights[LED_1_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_1_b));

        lights[LED_2_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_2_r));
        lights[LED_2_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_2_g));
        lights[LED_2_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_2_b));

        lights[LED_3_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_3_r));
        lights[LED_3_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_3_g));
        lights[LED_3_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_3_b));

        lights[LED_4_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_4_r));
        lights[LED_4_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_4_g));
        lights[LED_4_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_4_b));

        lights[LED_5_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_5_r));
        lights[LED_5_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_5_g));
        lights[LED_5_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_5_b));

        lights[LED_6_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_6_r));
        lights[LED_6_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_6_g));
        lights[LED_6_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_6_b));

        lights[LED_7_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_7_r));
        lights[LED_7_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_7_g));
        lights[LED_7_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_7_b));

        lights[LED_8_LIGHT_R].setBrightness(FaustUI.getParamValue(paramLight_8_r));
        lights[LED_8_LIGHT_G].setBrightness(FaustUI.getParamValue(paramLight_8_g));
        lights[LED_8_LIGHT_B].setBrightness(FaustUI.getParamValue(paramLight_8_b));
    }
};


struct ProtoFaustWidget : ModuleWidget {
    ProtoFaustWidget(ProtoFaust *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(
                     asset::plugin(pluginInstance, "res/ProtoFaust.svg")));

        // screws
        addChild(createWidget<ScrewBlack>(
                     Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewBlack>(
                     Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewBlack>(
                     Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewBlack>(
                     Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        // buttons & switches
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 21.82)), module, ProtoFaust::BUTTON_1_PARAM));
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 34.52)), module, ProtoFaust::BUTTON_2_PARAM));
        addParam(createParamCentered<CKSS>(
                     mm2px(Vec(31.75, 49.76)), module, ProtoFaust::BUTTON_3_PARAM));
        addParam(createParamCentered<CKSS>(
                     mm2px(Vec(31.75, 62.46)), module, ProtoFaust::BUTTON_4_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 77.7)), module, ProtoFaust::BUTTON_5_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 90.4)), module, ProtoFaust::BUTTON_6_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 105.64)), module, ProtoFaust::BUTTON_7_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 118.34)), module, ProtoFaust::BUTTON_8_PARAM));

        // big knobs
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 28.17)), module, ProtoFaust::KNOB_1_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 28.17)), module, ProtoFaust::KNOB_2_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 56.11)), module, ProtoFaust::KNOB_3_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 56.11)), module, ProtoFaust::KNOB_4_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 84.05)), module, ProtoFaust::KNOB_5_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 84.05)), module, ProtoFaust::KNOB_6_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 111.99)), module, ProtoFaust::KNOB_7_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 111.99)), module, ProtoFaust::KNOB_8_PARAM));

        // input ports
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 21.82)), module, ProtoFaust::IN_1_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 34.52)), module, ProtoFaust::IN_2_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 49.76)), module, ProtoFaust::IN_3_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 62.46)), module, ProtoFaust::IN_4_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 77.7)), module, ProtoFaust::IN_5_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 90.4)), module, ProtoFaust::IN_6_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 105.64)), module, ProtoFaust::IN_7_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 118.34)), module, ProtoFaust::IN_8_INPUT));

        // output ports
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 21.82)), module, ProtoFaust::OUT_1_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 34.52)), module, ProtoFaust::OUT_2_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 49.76)), module, ProtoFaust::OUT_3_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 62.46)), module, ProtoFaust::OUT_4_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 77.7)), module, ProtoFaust::OUT_5_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 90.4)), module, ProtoFaust::OUT_6_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 105.64)), module, ProtoFaust::OUT_7_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 118.34)), module, ProtoFaust::OUT_8_OUTPUT));

        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 21.82)), module, ProtoFaust::LED_1_LIGHT_R));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 34.52)), module, ProtoFaust::LED_2_LIGHT_R));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 49.76)), module, ProtoFaust::LED_3_LIGHT_R));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 62.46)), module, ProtoFaust::LED_4_LIGHT_R));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 77.7)), module, ProtoFaust::LED_5_LIGHT_R));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 90.4)), module, ProtoFaust::LED_6_LIGHT_R));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 105.64)), module, ProtoFaust::LED_7_LIGHT_R));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 118.34)), module, ProtoFaust::LED_8_LIGHT_R));
    }
};


Model *modelProtoFaust = createModel<ProtoFaust, ProtoFaustWidget>("ProtoFaust");
