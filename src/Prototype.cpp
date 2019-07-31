#include "plugin.hpp"

namespace faust {
#include "faust_generated.cpp"
}


struct Prototype : Module {
    enum ParamIds {
        LARGE_KNOB_1_PARAM,
        LARGE_KNOB_2_PARAM,
        LARGE_KNOB_3_PARAM,
        LARGE_KNOB_4_PARAM,
        LARGE_KNOB_5_PARAM,
        LARGE_KNOB_6_PARAM,
        LARGE_KNOB_7_PARAM,
        LARGE_KNOB_8_PARAM,
        SMALL_KNOB_1_PARAM,
        SMALL_KNOB_2_PARAM,
        SMALL_KNOB_3_PARAM,
        SMALL_KNOB_4_PARAM,
        SMALL_KNOB_5_PARAM,
        SMALL_KNOB_6_PARAM,
        SMALL_KNOB_7_PARAM,
        SMALL_KNOB_8_PARAM,
        SWITCH_1_PARAM,
        SWITCH_2_PARAM,
        SWITCH_3_PARAM,
        SWITCH_4_PARAM,
        SWITCH_5_PARAM,
        SWITCH_6_PARAM,
        SWITCH_7_PARAM,
        SWITCH_8_PARAM,
        NUM_PARAMS
    };
    enum InputIds {
        AUDIO_1_INPUT,
        AUDIO_2_INPUT,
        AUDIO_3_INPUT,
        AUDIO_4_INPUT,
        AUDIO_5_INPUT,
        AUDIO_6_INPUT,
        AUDIO_7_INPUT,
        AUDIO_8_INPUT,
        CV_1_INPUT,
        CV_2_INPUT,
        CV_3_INPUT,
        CV_4_INPUT,
        CV_5_INPUT,
        CV_6_INPUT,
        CV_7_INPUT,
        CV_8_INPUT,
        GATE_1_INPUT,
        GATE_2_INPUT,
        GATE_3_INPUT,
        GATE_4_INPUT,
        GATE_5_INPUT,
        GATE_6_INPUT,
        GATE_7_INPUT,
        GATE_8_INPUT,
        NUM_INPUTS
    };
    enum OutputIds {
        AUDIO_1_OUTPUT,
        AUDIO_2_OUTPUT,
        AUDIO_3_OUTPUT,
        AUDIO_4_OUTPUT,
        AUDIO_5_OUTPUT,
        AUDIO_6_OUTPUT,
        AUDIO_7_OUTPUT,
        AUDIO_8_OUTPUT,
        CV_1_OUTPUT,
        CV_2_OUTPUT,
        CV_3_OUTPUT,
        CV_4_OUTPUT,
        CV_5_OUTPUT,
        CV_6_OUTPUT,
        CV_7_OUTPUT,
        CV_8_OUTPUT,
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

    faust::mydsp DSP;
    faust::PrintUI ui;

    float phase = 0.f;
    float blinkPhase = 0.f;

    const FAUSTFLOAT levelScaling = 5.0f;

    Prototype() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(LARGE_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LARGE_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LARGE_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LARGE_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LARGE_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LARGE_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LARGE_KNOB_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(LARGE_KNOB_8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_5_PARAM, -1.f, 1.f, 0.f, "");
        configParam(SWITCH_6_PARAM, -1.f, 1.f, 0.f, "");
        configParam(SWITCH_7_PARAM, -1.f, 1.f, 0.f, "");
        configParam(SWITCH_8_PARAM, -1.f, 1.f, 0.f, "");
    }


    void onAdd() override {
        // Activate the UI
        // (here that only print the control paths)
        DSP.buildUserInterface(&ui);

        int sampleRate = APP->engine->getSampleRate();
        DSP.init(sampleRate);
    }


    void onSampleRateChange() override {
        int sampleRate = APP->engine->getSampleRate();
        DSP.instanceConstants(sampleRate);
    }


    void process(const ProcessArgs &args) override {
        int int_control[DSP.getNumIntControls()];
        FAUSTFLOAT real_control[DSP.getNumRealControls()];

        std::vector<FAUSTFLOAT> temporaryInputs(8);
        std::vector<FAUSTFLOAT> temporaryOutputs(8);

        for (int channel = 0; channel < 8; channel++) {
            FAUSTFLOAT input = inputs[channel + AUDIO_1_INPUT].getVoltage();
            FAUSTFLOAT output = outputs[channel + AUDIO_1_OUTPUT].getVoltage();

            // scale levels to value range of Faust (-1.0 to +1.0)
            output /= levelScaling;
            input /= levelScaling;

            temporaryInputs[channel] = input;
            temporaryOutputs[channel] = output;
        }

        DSP.compute(temporaryInputs.data(), temporaryOutputs.data(), int_control, real_control);

        for (int channel = 0; channel < 8; channel++) {
            FAUSTFLOAT input = temporaryInputs[channel];
            FAUSTFLOAT output = temporaryOutputs[channel];

            // scale levels to value range of Rack (-5.0 to +5.0)
            output *= levelScaling;
            input *= levelScaling;

            inputs[channel + AUDIO_1_INPUT].setVoltage(input);
            outputs[channel + AUDIO_1_OUTPUT].setVoltage(output);
        }

        // Blink light at 1Hz
        blinkPhase += args.sampleTime;

        if (blinkPhase >= 1.f) {
            blinkPhase -= 1.f;
        }

        lights[LED_1_LIGHT].setBrightness(blinkPhase < 0.5f ? 1.f : 0.f);
        lights[LED_2_LIGHT].setBrightness(blinkPhase < 0.5f ? 0.f : 1.f);
    }
};


struct PrototypeWidget : ModuleWidget {
    PrototypeWidget(Prototype *module) {
        setModule(module);
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Prototype.svg")));

        addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec(100.33, 28.17)), module, Prototype::LARGE_KNOB_1_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec(100.33, 56.11)), module, Prototype::LARGE_KNOB_2_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec(100.33, 84.05)), module, Prototype::LARGE_KNOB_3_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec(100.33, 111.99)), module, Prototype::LARGE_KNOB_4_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec(123.19, 28.17)), module, Prototype::LARGE_KNOB_5_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec(123.19, 56.11)), module, Prototype::LARGE_KNOB_6_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec(123.19, 84.05)), module, Prototype::LARGE_KNOB_7_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec(123.19, 111.99)), module, Prototype::LARGE_KNOB_8_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 21.82)), module, Prototype::SMALL_KNOB_1_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 34.52)), module, Prototype::SMALL_KNOB_2_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 49.76)), module, Prototype::SMALL_KNOB_3_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 62.46)), module, Prototype::SMALL_KNOB_4_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 77.7)), module, Prototype::SMALL_KNOB_5_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 90.4)), module, Prototype::SMALL_KNOB_6_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 105.64)), module, Prototype::SMALL_KNOB_7_PARAM));
        addParam(createParamCentered<BefacoTinyKnob>(mm2px(Vec(49.53, 118.34)), module, Prototype::SMALL_KNOB_8_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(80.01, 21.82)), module, Prototype::SWITCH_1_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(80.01, 34.52)), module, Prototype::SWITCH_2_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(80.01, 49.76)), module, Prototype::SWITCH_3_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(80.01, 62.46)), module, Prototype::SWITCH_4_PARAM));
        addParam(createParamCentered<CKSSThree>(mm2px(Vec(80.01, 77.7)), module, Prototype::SWITCH_5_PARAM));
        addParam(createParamCentered<CKSSThree>(mm2px(Vec(80.01, 90.4)), module, Prototype::SWITCH_6_PARAM));
        addParam(createParamCentered<CKSSThree>(mm2px(Vec(80.01, 105.64)), module, Prototype::SWITCH_7_PARAM));
        addParam(createParamCentered<CKSSThree>(mm2px(Vec(80.01, 118.34)), module, Prototype::SWITCH_8_PARAM));

        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 21.82)), module, Prototype::AUDIO_1_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 34.52)), module, Prototype::AUDIO_2_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 49.76)), module, Prototype::AUDIO_3_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 62.46)), module, Prototype::AUDIO_4_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 77.7)), module, Prototype::AUDIO_5_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 90.4)), module, Prototype::AUDIO_6_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 105.64)), module, Prototype::AUDIO_7_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(17.78, 118.34)), module, Prototype::AUDIO_8_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 21.82)), module, Prototype::CV_1_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 34.52)), module, Prototype::CV_2_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 49.76)), module, Prototype::CV_3_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 62.46)), module, Prototype::CV_4_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 77.7)), module, Prototype::CV_5_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 90.4)), module, Prototype::CV_6_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 105.64)), module, Prototype::CV_7_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(35.56, 118.34)), module, Prototype::CV_8_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 21.82)), module, Prototype::GATE_1_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 34.52)), module, Prototype::GATE_2_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 49.76)), module, Prototype::GATE_3_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 62.46)), module, Prototype::GATE_4_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 77.7)), module, Prototype::GATE_5_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 90.4)), module, Prototype::GATE_6_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 105.64)), module, Prototype::GATE_7_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(67.31, 118.34)), module, Prototype::GATE_8_INPUT));

        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 21.82)), module, Prototype::AUDIO_1_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 34.52)), module, Prototype::AUDIO_2_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 49.76)), module, Prototype::AUDIO_3_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 62.46)), module, Prototype::AUDIO_4_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 77.7)), module, Prototype::AUDIO_5_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 90.4)), module, Prototype::AUDIO_6_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 105.64)), module, Prototype::AUDIO_7_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(175.26, 118.34)), module, Prototype::AUDIO_8_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 21.82)), module, Prototype::CV_1_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 34.52)), module, Prototype::CV_2_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 49.76)), module, Prototype::CV_3_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 62.46)), module, Prototype::CV_4_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 77.7)), module, Prototype::CV_5_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 90.4)), module, Prototype::CV_6_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 105.64)), module, Prototype::CV_7_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(157.48, 118.34)), module, Prototype::CV_8_OUTPUT));

        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 21.82)), module, Prototype::LED_1_LIGHT));
        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 34.52)), module, Prototype::LED_2_LIGHT));
        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 49.76)), module, Prototype::LED_3_LIGHT));
        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 62.46)), module, Prototype::LED_4_LIGHT));
        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 77.7)), module, Prototype::LED_5_LIGHT));
        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 90.4)), module, Prototype::LED_6_LIGHT));
        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 105.64)), module, Prototype::LED_7_LIGHT));
        addChild(createLightCentered<MediumLight<BlueLight>>(mm2px(Vec(143.51, 118.34)), module, Prototype::LED_8_LIGHT));
    }
};


Model *modelPrototype = createModel<Prototype, PrototypeWidget>("Prototype");
