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
        LED_1_LIGHT_RED,
        LED_1_LIGHT_GREEN,
        LED_1_LIGHT_BLUE,

        LED_2_LIGHT_RED,
        LED_2_LIGHT_GREEN,
        LED_2_LIGHT_BLUE,

        LED_3_LIGHT_RED,
        LED_3_LIGHT_GREEN,
        LED_3_LIGHT_BLUE,

        LED_4_LIGHT_RED,
        LED_4_LIGHT_GREEN,
        LED_4_LIGHT_BLUE,

        LED_5_LIGHT_RED,
        LED_5_LIGHT_GREEN,
        LED_5_LIGHT_BLUE,

        LED_6_LIGHT_RED,
        LED_6_LIGHT_GREEN,
        LED_6_LIGHT_BLUE,

        LED_7_LIGHT_RED,
        LED_7_LIGHT_GREEN,
        LED_7_LIGHT_BLUE,

        LED_8_LIGHT_RED,
        LED_8_LIGHT_GREEN,
        LED_8_LIGHT_BLUE,

        NUM_LIGHTS
    };


    faust::PrototypeDSP DSP;
    faust::APIUI ui;

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

    int paramLight_1_red = -1;
    int paramLight_1_green = -1;
    int paramLight_1_blue = -1;

    int paramLight_2_red = -1;
    int paramLight_2_green = -1;
    int paramLight_2_blue = -1;

    int paramLight_3_red = -1;
    int paramLight_3_green = -1;
    int paramLight_3_blue = -1;

    int paramLight_4_red = -1;
    int paramLight_4_green = -1;
    int paramLight_4_blue = -1;

    int paramLight_5_red = -1;
    int paramLight_5_green = -1;
    int paramLight_5_blue = -1;

    int paramLight_6_red = -1;
    int paramLight_6_green = -1;
    int paramLight_6_blue = -1;

    int paramLight_7_red = -1;
    int paramLight_7_green = -1;
    int paramLight_7_blue = -1;

    int paramLight_8_red = -1;
    int paramLight_8_green = -1;
    int paramLight_8_blue = -1;

    const FAUSTFLOAT pitchScaling = 5.0f;
    const FAUSTFLOAT cvScaling = 10.0f;

    Prototype() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

        configParam(BUTTON_1_PARAM, 0.f, 1.f, 1.f, "");
        configParam(BUTTON_2_PARAM, 0.f, 1.f, 1.f, "");
        configParam(BUTTON_3_PARAM, 0.f, 2.f, 1.f, "");
        configParam(BUTTON_4_PARAM, 0.f, 2.f, 1.f, "");
        configParam(BUTTON_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BUTTON_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BUTTON_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BUTTON_8_PARAM, 0.f, 1.f, 0.f, "");

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

        paramButton_1 = ui.getParamIndex("/Prototype/Buttons/1");
        paramButton_2 = ui.getParamIndex("/Prototype/Buttons/2");
        paramButton_3 = ui.getParamIndex("/Prototype/Buttons/3");
        paramButton_4 = ui.getParamIndex("/Prototype/Buttons/4");
        paramButton_5 = ui.getParamIndex("/Prototype/Buttons/5");
        paramButton_6 = ui.getParamIndex("/Prototype/Buttons/6");
        paramButton_7 = ui.getParamIndex("/Prototype/Buttons/7");
        paramButton_8 = ui.getParamIndex("/Prototype/Buttons/8");

        paramKnob_1 = ui.getParamIndex("/Prototype/Knobs/1");
        paramKnob_2 = ui.getParamIndex("/Prototype/Knobs/2");
        paramKnob_3 = ui.getParamIndex("/Prototype/Knobs/3");
        paramKnob_4 = ui.getParamIndex("/Prototype/Knobs/4");
        paramKnob_5 = ui.getParamIndex("/Prototype/Knobs/5");
        paramKnob_6 = ui.getParamIndex("/Prototype/Knobs/6");
        paramKnob_7 = ui.getParamIndex("/Prototype/Knobs/7");
        paramKnob_8 = ui.getParamIndex("/Prototype/Knobs/8");

        paramLight_1_red = ui.getParamIndex("/Prototype/Lights/1_Red");
        paramLight_1_green = ui.getParamIndex("/Prototype/Lights/1_Green");
        paramLight_1_blue = ui.getParamIndex("/Prototype/Lights/1_Blue");

        paramLight_2_red = ui.getParamIndex("/Prototype/Lights/2_Red");
        paramLight_2_green = ui.getParamIndex("/Prototype/Lights/2_Green");
        paramLight_2_blue = ui.getParamIndex("/Prototype/Lights/2_Blue");

        paramLight_3_red = ui.getParamIndex("/Prototype/Lights/3_Red");
        paramLight_3_green = ui.getParamIndex("/Prototype/Lights/3_Green");
        paramLight_3_blue = ui.getParamIndex("/Prototype/Lights/3_Blue");

        paramLight_4_red = ui.getParamIndex("/Prototype/Lights/4_Red");
        paramLight_4_green = ui.getParamIndex("/Prototype/Lights/4_Green");
        paramLight_4_blue = ui.getParamIndex("/Prototype/Lights/4_Blue");

        paramLight_5_red = ui.getParamIndex("/Prototype/Lights/5_Red");
        paramLight_5_green = ui.getParamIndex("/Prototype/Lights/5_Green");
        paramLight_5_blue = ui.getParamIndex("/Prototype/Lights/5_Blue");

        paramLight_6_red = ui.getParamIndex("/Prototype/Lights/6_Red");
        paramLight_6_green = ui.getParamIndex("/Prototype/Lights/6_Green");
        paramLight_6_blue = ui.getParamIndex("/Prototype/Lights/6_Blue");

        paramLight_7_red = ui.getParamIndex("/Prototype/Lights/7_Red");
        paramLight_7_green = ui.getParamIndex("/Prototype/Lights/7_Green");
        paramLight_7_blue = ui.getParamIndex("/Prototype/Lights/7_Blue");

        paramLight_8_red = ui.getParamIndex("/Prototype/Lights/8_Red");
        paramLight_8_green = ui.getParamIndex("/Prototype/Lights/8_Green");
        paramLight_8_blue = ui.getParamIndex("/Prototype/Lights/8_Blue");

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

        value = params[BUTTON_1_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramButton_1, value);

        value = params[BUTTON_2_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramButton_2, value);

        value = params[BUTTON_3_PARAM].getValue();
        value /= (2.0f * cvScaling);
        ui.setParamValue(paramButton_3, value);

        value = params[BUTTON_4_PARAM].getValue();
        value /= (2.0f * cvScaling);
        ui.setParamValue(paramButton_4, value);

        value = params[BUTTON_5_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramButton_5, value);

        value = params[BUTTON_6_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramButton_6, value);

        value = params[BUTTON_7_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramButton_7, value);

        value = params[BUTTON_8_PARAM].getValue();
        value /= cvScaling;
        ui.setParamValue(paramButton_8, value);

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

        lights[LED_1_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_1_red));
        lights[LED_1_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_1_green));
        lights[LED_1_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_1_blue));

        lights[LED_2_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_2_red));
        lights[LED_2_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_2_green));
        lights[LED_2_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_2_blue));

        lights[LED_3_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_3_red));
        lights[LED_3_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_3_green));
        lights[LED_3_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_3_blue));

        lights[LED_4_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_4_red));
        lights[LED_4_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_4_green));
        lights[LED_4_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_4_blue));

        lights[LED_5_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_5_red));
        lights[LED_5_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_5_green));
        lights[LED_5_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_5_blue));

        lights[LED_6_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_6_red));
        lights[LED_6_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_6_green));
        lights[LED_6_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_6_blue));

        lights[LED_7_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_7_red));
        lights[LED_7_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_7_green));
        lights[LED_7_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_7_blue));

        lights[LED_8_LIGHT_RED].setBrightness(ui.getParamValue(paramLight_8_red));
        lights[LED_8_LIGHT_GREEN].setBrightness(ui.getParamValue(paramLight_8_green));
        lights[LED_8_LIGHT_BLUE].setBrightness(ui.getParamValue(paramLight_8_blue));
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

        addParam(createParamCentered<CKSS>(
                     mm2px(Vec(31.75, 21.82)), module, Prototype::BUTTON_1_PARAM));
        addParam(createParamCentered<CKSS>(
                     mm2px(Vec(31.75, 34.52)), module, Prototype::BUTTON_2_PARAM));
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 49.76)), module, Prototype::BUTTON_3_PARAM));
        addParam(createParamCentered<CKSSThree>(
                     mm2px(Vec(31.75, 62.46)), module, Prototype::BUTTON_4_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 77.7)), module, Prototype::BUTTON_5_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 90.4)), module, Prototype::BUTTON_6_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 105.64)), module, Prototype::BUTTON_7_PARAM));
        addParam(createParamCentered<BefacoPush>(
                     mm2px(Vec(31.75, 118.34)), module, Prototype::BUTTON_8_PARAM));

        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 28.17)), module, Prototype::KNOB_1_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 28.17)), module, Prototype::KNOB_2_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 56.11)), module, Prototype::KNOB_3_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 56.11)), module, Prototype::KNOB_4_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 84.05)), module, Prototype::KNOB_5_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 84.05)), module, Prototype::KNOB_6_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(
                     mm2px(Vec(53.34, 111.99)), module, Prototype::KNOB_7_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(
                     mm2px(Vec(78.74, 111.99)), module, Prototype::KNOB_8_PARAM));

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
                      mm2px(Vec(114.3, 21.82)), module, Prototype::OUT_1_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 34.52)), module, Prototype::OUT_2_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 49.76)), module, Prototype::OUT_3_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 62.46)), module, Prototype::OUT_4_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 77.7)), module, Prototype::OUT_5_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 90.4)), module, Prototype::OUT_6_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 105.64)), module, Prototype::OUT_7_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(
                      mm2px(Vec(114.3, 118.34)), module, Prototype::OUT_8_OUTPUT));

        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 21.82)), module, Prototype::LED_1_LIGHT_RED));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 34.52)), module, Prototype::LED_2_LIGHT_RED));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 49.76)), module, Prototype::LED_3_LIGHT_RED));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 62.46)), module, Prototype::LED_4_LIGHT_RED));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 77.7)), module, Prototype::LED_5_LIGHT_RED));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 90.4)), module, Prototype::LED_6_LIGHT_RED));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 105.64)), module, Prototype::LED_7_LIGHT_RED));
        addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(
                     mm2px(Vec(99.06, 118.34)), module, Prototype::LED_8_LIGHT_RED));
    }
};


Model *modelPrototype = createModel<Prototype, PrototypeWidget>("Prototype");
