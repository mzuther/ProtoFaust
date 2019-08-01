#include "plugin.hpp"

namespace faust {
#include "faust_generated.cpp"
}


struct Prototype : Module {
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
        LED_1_LIGHT,
        LED_2_LIGHT,
        LED_3_LIGHT,
        LED_4_LIGHT,
        LED_5_LIGHT,
        LED_6_LIGHT,
        LED_7_LIGHT,
        LED_8_LIGHT,

        NUM_LIGHTS
    };


    faust::PrototypeDSP DSP;
    faust::APIUI ui;

    int paramLight_1 = -1;
    int paramLight_2 = -1;
    int paramLight_3 = -1;
    int paramLight_4 = -1;
    int paramLight_5 = -1;
    int paramLight_6 = -1;
    int paramLight_7 = -1;
    int paramLight_8 = -1;

    int paramKnob_1 = -1;
    int paramKnob_2 = -1;
    int paramKnob_3 = -1;
    int paramKnob_4 = -1;
    int paramKnob_5 = -1;
    int paramKnob_6 = -1;
    int paramKnob_7 = -1;
    int paramKnob_8 = -1;

    const FAUSTFLOAT pitchScaling = 5.0f;
    const FAUSTFLOAT cvScaling = 10.0f;

    Prototype() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

        configParam(BUTTON_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BUTTON_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BUTTON_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BUTTON_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BUTTON_5_PARAM, 0.f, 2.f, 1.f, "");
        configParam(BUTTON_6_PARAM, 0.f, 2.f, 1.f, "");
        configParam(BUTTON_7_PARAM, 0.f, 2.f, 1.f, "");
        configParam(BUTTON_8_PARAM, 0.f, 2.f, 1.f, "");

        configParam(KNOB_1_PARAM, 0.f, 10.f, 5.f, "");
        configParam(KNOB_2_PARAM, 0.f, 10.f, 5.f, "");
        configParam(KNOB_3_PARAM, 0.f, 10.f, 5.f, "");
        configParam(KNOB_4_PARAM, 0.f, 10.f, 5.f, "");
        configParam(KNOB_5_PARAM, 0.f, 10.f, 5.f, "");
        configParam(KNOB_6_PARAM, 0.f, 10.f, 5.f, "");
        configParam(KNOB_7_PARAM, 0.f, 10.f, 5.f, "");
        configParam(KNOB_8_PARAM, 0.f, 10.f, 5.f, "");
    }


    void onAdd() override {
        // Activate the UI
        DSP.buildUserInterface(&ui);

        // for (int n=0; n < ui.getParamsCount(); n++)
        //     std::cout << ui.getParamAddress(n) << std::endl;

        paramLight_1 = ui.getParamIndex("/Prototype/Lights/1");
        paramLight_2 = ui.getParamIndex("/Prototype/Lights/2");
        paramLight_3 = ui.getParamIndex("/Prototype/Lights/3");
        paramLight_4 = ui.getParamIndex("/Prototype/Lights/4");
        paramLight_5 = ui.getParamIndex("/Prototype/Lights/5");
        paramLight_6 = ui.getParamIndex("/Prototype/Lights/6");
        paramLight_7 = ui.getParamIndex("/Prototype/Lights/7");
        paramLight_8 = ui.getParamIndex("/Prototype/Lights/8");

        paramKnob_1 = ui.getParamIndex("/Prototype/Knobs/1");
        paramKnob_2 = ui.getParamIndex("/Prototype/Knobs/2");
        paramKnob_3 = ui.getParamIndex("/Prototype/Knobs/3");
        paramKnob_4 = ui.getParamIndex("/Prototype/Knobs/4");
        paramKnob_5 = ui.getParamIndex("/Prototype/Knobs/5");
        paramKnob_6 = ui.getParamIndex("/Prototype/Knobs/6");
        paramKnob_7 = ui.getParamIndex("/Prototype/Knobs/7");
        paramKnob_8 = ui.getParamIndex("/Prototype/Knobs/8");

        int sampleRate = APP->engine->getSampleRate();
        DSP.init(sampleRate);
    }


    void onSampleRateChange() override {
        int sampleRate = APP->engine->getSampleRate();
        DSP.instanceConstants(sampleRate);
    }


    void process(const ProcessArgs &args) override {
        std::vector<FAUSTFLOAT> temporaryInputs(8);
        std::vector<FAUSTFLOAT> temporaryOutputs(8);

        for (int channel = 0; channel < 8; channel++) {
            FAUSTFLOAT input = inputs[channel + IN_1_INPUT].getVoltage();
            FAUSTFLOAT output = outputs[channel + OUT_1_OUTPUT].getVoltage();

            // scale levels to value range of Faust (-1.0 to +1.0)
            output /= pitchScaling;
            input /= pitchScaling;

            temporaryInputs[channel] = input;
            temporaryOutputs[channel] = output;
        }

        int int_control[DSP.getNumIntControls()];
        FAUSTFLOAT real_control[DSP.getNumRealControls()];
        FAUSTFLOAT value;

        value = params[KNOB_1_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_1, value);

        value = params[KNOB_2_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_2, value);

        value = params[KNOB_3_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_3, value);

        value = params[KNOB_4_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_4, value);

        value = params[KNOB_5_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_5, value);

        value = params[KNOB_6_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_6, value);

        value = params[KNOB_7_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_7, value);

        value = params[KNOB_8_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramKnob_8, value);

        DSP.control(int_control, real_control);
        DSP.compute(temporaryInputs.data(), temporaryOutputs.data(), int_control, real_control);

        for (int channel = 0; channel < 8; channel++) {
            FAUSTFLOAT input = temporaryInputs[channel];
            FAUSTFLOAT output = temporaryOutputs[channel];

            // scale levels to value range of Rack (-5.0 to +5.0)
            output *= pitchScaling;
            input *= pitchScaling;

            inputs[channel + IN_1_INPUT].setVoltage(input);
            outputs[channel + OUT_1_OUTPUT].setVoltage(output);
        }

        lights[LED_1_LIGHT].setBrightness(ui.getParamValue(paramLight_1));
        lights[LED_2_LIGHT].setBrightness(ui.getParamValue(paramLight_2));
        lights[LED_3_LIGHT].setBrightness(ui.getParamValue(paramLight_3));
        lights[LED_4_LIGHT].setBrightness(ui.getParamValue(paramLight_4));
        lights[LED_5_LIGHT].setBrightness(ui.getParamValue(paramLight_5));
        lights[LED_6_LIGHT].setBrightness(ui.getParamValue(paramLight_6));
        lights[LED_7_LIGHT].setBrightness(ui.getParamValue(paramLight_7));
        lights[LED_8_LIGHT].setBrightness(ui.getParamValue(paramLight_8));
    }
};


struct PrototypeWidget : ModuleWidget {
    PrototypeWidget(Prototype *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(
                     asset::plugin(pluginInstance, "res/Prototype.svg")));

        addChild(createWidget<ScrewBlack>(
                     Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewBlack>(
                     Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewBlack>(
                     Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewBlack>(
                     Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 21.82)), module, Prototype::BUTTON_1_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 34.52)), module, Prototype::BUTTON_2_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 49.76)), module, Prototype::BUTTON_3_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 62.46)), module, Prototype::BUTTON_4_PARAM));
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 77.7)), module, Prototype::BUTTON_5_PARAM));
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 90.4)), module, Prototype::BUTTON_6_PARAM));
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 105.64)), module, Prototype::BUTTON_7_PARAM));
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 118.34)), module, Prototype::BUTTON_8_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(52.07, 28.17)), module, Prototype::KNOB_1_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(74.93, 28.17)), module, Prototype::KNOB_2_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(52.07, 56.11)), module, Prototype::KNOB_3_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(74.93, 56.11)), module, Prototype::KNOB_4_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(52.07, 84.05)), module, Prototype::KNOB_5_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(74.93, 84.05)), module, Prototype::KNOB_6_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(52.07, 111.99)), module, Prototype::KNOB_7_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(74.93, 111.99)), module, Prototype::KNOB_8_PARAM));

        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 21.82)), module, Prototype::IN_1_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 34.52)), module, Prototype::IN_2_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 49.76)), module, Prototype::IN_3_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 62.46)), module, Prototype::IN_4_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 77.7)), module, Prototype::IN_5_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 90.4)), module, Prototype::IN_6_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 105.64)), module, Prototype::IN_7_INPUT));
        addInput(createInputCentered<CL1362Port>(
                     mm2px(Vec(17.78, 118.34)), module, Prototype::IN_8_INPUT));

        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 21.82)), module, Prototype::OUT_1_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 34.52)), module, Prototype::OUT_2_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 49.76)), module, Prototype::OUT_3_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 62.46)), module, Prototype::OUT_4_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 77.7)), module, Prototype::OUT_5_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 90.4)), module, Prototype::OUT_6_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 105.64)), module, Prototype::OUT_7_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(109.22, 118.34)), module, Prototype::OUT_8_OUTPUT));

        addChild(createLightCentered<MediumLight<WhiteLight>>(
                     mm2px(Vec(95.25, 21.82)), module, Prototype::LED_1_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(
                     mm2px(Vec(95.25, 34.52)), module, Prototype::LED_2_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(
                     mm2px(Vec(95.25, 49.76)), module, Prototype::LED_3_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(
                     mm2px(Vec(95.25, 62.46)), module, Prototype::LED_4_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(
                     mm2px(Vec(95.25, 77.7)), module, Prototype::LED_5_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(
                     mm2px(Vec(95.25, 90.4)), module, Prototype::LED_6_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(
                     mm2px(Vec(95.25, 105.64)), module, Prototype::LED_7_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(
                     mm2px(Vec(95.25, 118.34)), module, Prototype::LED_8_LIGHT));
    }
};


Model *modelPrototype = createModel<Prototype, PrototypeWidget>("Prototype");
