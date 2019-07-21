#include "plugin.hpp"


struct Prototype : Module {
    enum ParamIds {
        SMALL_KNOB_1_PARAM,
        SWITCH_1_PARAM,
        BIG_KNOB_1_PARAM,
        BIG_KNOB_2_PARAM,
        SMALL_KNOB_2_PARAM,
        SWITCH_2_PARAM,
        SMALL_KNOB_3_PARAM,
        SWITCH_3_PARAM,
        BIG_KNOB_3_PARAM,
        BIG_KNOB_4_PARAM,
        SMALL_KNOB_4_PARAM,
        SWITCH_4_PARAM,
        SMALL_KNOB_5_PARAM,
        SWITCH_5_PARAM,
        BIG_KNOB_5_PARAM,
        BIG_KNOB_6_PARAM,
        SMALL_KNOB_6_PARAM,
        SWITCH_6_PARAM,
        SMALL_KNOB_7_PARAM,
        SWITCH_7_PARAM,
        BIG_KNOB_7_PARAM,
        BIG_KNOB_8_PARAM,
        SMALL_KNOB_8_PARAM,
        SWITCH_8_PARAM,
        NUM_PARAMS
    };
    enum InputIds {
        CV_1_INPUT,
        GATE_1_INPUT,
        CV_2_INPUT,
        GATE_2_INPUT,
        CV_3_INPUT,
        GATE_3_INPUT,
        CV_4_INPUT,
        GATE_4_INPUT,
        CV_5_INPUT,
        GATE_5_INPUT,
        CV_6_INPUT,
        GATE_6_INPUT,
        CV_7_INPUT,
        GATE_7_INPUT,
        CV_8_INPUT,
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
        NUM_OUTPUTS
    };
    enum LightIds {
        LEFT_1_LIGHT,
        RIGHT_1_LIGHT,
        LEFT_2_LIGHT,
        RIGHT_2_LIGHT,
        LEFT_3_LIGHT,
        RIGHT_3_LIGHT,
        LEFT_4_LIGHT,
        RIGHT_4_LIGHT,
        LEFT_5_LIGHT,
        RIGHT_5_LIGHT,
        LEFT_6_LIGHT,
        RIGHT_6_LIGHT,
        LEFT_7_LIGHT,
        RIGHT_7_LIGHT,
        LEFT_8_LIGHT,
        RIGHT_8_LIGHT,
        NUM_LIGHTS
    };

    float phase = 0.f;
    float blinkPhase = 0.f;

    Prototype() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        configParam(SMALL_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_1_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_2_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_3_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_4_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_5_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_6_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_7_PARAM, 0.f, 1.f, 0.f, "");
        configParam(BIG_KNOB_8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SMALL_KNOB_8_PARAM, 0.f, 1.f, 0.f, "");
        configParam(SWITCH_8_PARAM, 0.f, 1.f, 0.f, "");
    }

    void process(const ProcessArgs &args) override {
        // Compute the frequency from the pitch parameter and input
        float pitch = params[BIG_KNOB_1_PARAM].getValue();
        pitch += inputs[CV_1_INPUT].getVoltage();
        pitch = clamp(pitch, -4.f, 4.f);
        // The default pitch is C4 = 261.6256f
        float freq = dsp::FREQ_C4 * std::pow(2.f, pitch);

        // Accumulate the phase
        phase += freq * args.sampleTime;

        if (phase >= 0.5f) {
            phase -= 1.f;
        }

        // Compute the sine output
        float sine = std::sin(2.f * M_PI * phase);
        // Audio signals are typically +/-5V
        // https://vcvrack.com/manual/VoltageStandards.html
        outputs[AUDIO_1_OUTPUT].setVoltage(5.f * sine);

        // Blink light at 1Hz
        blinkPhase += args.sampleTime;

        if (blinkPhase >= 1.f) {
            blinkPhase -= 1.f;
        }

        lights[LEFT_1_LIGHT].setBrightness(blinkPhase < 0.5f ? 1.f : 0.f);
        lights[RIGHT_1_LIGHT].setBrightness(blinkPhase < 0.5f ? 0.f : 1.f);
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

        addParam(createParamCentered<Davies1900hWhiteKnob>(mm2px(Vec(30.48,  21.82)), module, Prototype::SMALL_KNOB_1_PARAM));
        addParam(createParamCentered<Davies1900hWhiteKnob>(mm2px(Vec(30.48,  34.52)), module, Prototype::SMALL_KNOB_2_PARAM));
        addParam(createParamCentered<Davies1900hRedKnob>(mm2px(Vec(30.48,  49.76)), module, Prototype::SMALL_KNOB_3_PARAM));
        addParam(createParamCentered<Davies1900hRedKnob>(mm2px(Vec(30.48,  62.46)), module, Prototype::SMALL_KNOB_4_PARAM));
        addParam(createParamCentered<Davies1900hWhiteKnob>(mm2px(Vec(30.48,  77.7 )), module, Prototype::SMALL_KNOB_5_PARAM));
        addParam(createParamCentered<Davies1900hWhiteKnob>(mm2px(Vec(30.48,  90.4 )), module, Prototype::SMALL_KNOB_6_PARAM));
        addParam(createParamCentered<Davies1900hRedKnob>(mm2px(Vec(30.48, 105.64)), module, Prototype::SMALL_KNOB_7_PARAM));
        addParam(createParamCentered<Davies1900hRedKnob>(mm2px(Vec(30.48, 118.34)), module, Prototype::SMALL_KNOB_8_PARAM));

        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5,  21.82)), module, Prototype::SWITCH_1_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5,  34.52)), module, Prototype::SWITCH_2_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5,  49.76)), module, Prototype::SWITCH_3_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5,  62.46)), module, Prototype::SWITCH_4_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5,  77.7 )), module, Prototype::SWITCH_5_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5,  90.4 )), module, Prototype::SWITCH_6_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5, 105.64)), module, Prototype::SWITCH_7_PARAM));
        addParam(createParamCentered<BefacoPush>(mm2px(Vec(63.5, 118.34)), module, Prototype::SWITCH_8_PARAM));

        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec( 82.55,  28.17)), module, Prototype::BIG_KNOB_1_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec(105.41,  28.17)), module, Prototype::BIG_KNOB_2_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec( 82.55,  56.11)), module, Prototype::BIG_KNOB_3_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec(105.41,  56.11)), module, Prototype::BIG_KNOB_4_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec( 82.55,  84.05)), module, Prototype::BIG_KNOB_5_PARAM));
        addParam(createParamCentered<Davies1900hLargeWhiteKnob>(mm2px(Vec(105.41,  84.05)), module, Prototype::BIG_KNOB_6_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec( 82.55, 111.99)), module, Prototype::BIG_KNOB_7_PARAM));
        addParam(createParamCentered<Davies1900hLargeRedKnob>(mm2px(Vec(105.41, 111.99)), module, Prototype::BIG_KNOB_8_PARAM));

        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24,  21.82)), module, Prototype::CV_1_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24,  34.52)), module, Prototype::CV_2_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24,  49.76)), module, Prototype::CV_3_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24,  62.46)), module, Prototype::CV_4_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24,  77.7 )), module, Prototype::CV_5_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24,  90.4 )), module, Prototype::CV_6_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24, 105.64)), module, Prototype::CV_7_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(15.24, 118.34)), module, Prototype::CV_8_INPUT));

        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8,  21.82)), module, Prototype::GATE_1_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8,  34.52)), module, Prototype::GATE_2_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8,  49.76)), module, Prototype::GATE_3_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8,  62.46)), module, Prototype::GATE_4_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8,  77.7 )), module, Prototype::GATE_5_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8,  90.4 )), module, Prototype::GATE_6_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8, 105.64)), module, Prototype::GATE_7_INPUT));
        addInput(createInputCentered<CL1362Port>(mm2px(Vec(50.8, 118.34)), module, Prototype::GATE_8_INPUT));

        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32,  21.82)), module, Prototype::AUDIO_1_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32,  34.52)), module, Prototype::AUDIO_2_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32,  49.76)), module, Prototype::AUDIO_3_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32,  62.46)), module, Prototype::AUDIO_4_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32,  77.7 )), module, Prototype::AUDIO_5_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32,  90.4 )), module, Prototype::AUDIO_6_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32, 105.64)), module, Prototype::AUDIO_7_OUTPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(147.32, 118.34)), module, Prototype::AUDIO_8_OUTPUT));

        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19,  21.82)), module, Prototype::LEFT_1_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19,  34.52)), module, Prototype::LEFT_2_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19,  49.76)), module, Prototype::LEFT_3_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19,  62.46)), module, Prototype::LEFT_4_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19,  77.7 )), module, Prototype::LEFT_5_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19,  90.4 )), module, Prototype::LEFT_6_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19, 105.64)), module, Prototype::LEFT_7_LIGHT));
        addChild(createLightCentered<MediumLight<WhiteLight>>(mm2px(Vec(123.19, 118.34)), module, Prototype::LEFT_8_LIGHT));

        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62,  21.82)), module, Prototype::RIGHT_1_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62,  34.52)), module, Prototype::RIGHT_2_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62,  49.76)), module, Prototype::RIGHT_3_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62,  62.46)), module, Prototype::RIGHT_4_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62,  77.7 )), module, Prototype::RIGHT_5_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62,  90.4 )), module, Prototype::RIGHT_6_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62, 105.64)), module, Prototype::RIGHT_7_LIGHT));
        addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(134.62, 118.34)), module, Prototype::RIGHT_8_LIGHT));
    }
};


Model *modelPrototype = createModel<Prototype, PrototypeWidget>("Prototype");
