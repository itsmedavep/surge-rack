#pragma once
#include "Surge.hpp"
#include "SurgeModuleCommon.hpp"
#include "dsp/Oscillator.h"
#include "rack.hpp"
#include <cstring>

struct SurgeVOC : virtual public SurgeModuleCommon {
    enum ParamIds {
        NUM_PARAMS 
    };
    enum InputIds {
        NUM_INPUTS,
    };
    enum OutputIds {
        NUM_OUTPUTS
    };
    enum LightIds { NUM_LIGHTS };

    ParamCache pc;

#if RACK_V1
    SurgeVOC() : SurgeModuleCommon() {
        config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        setupSurge();
    }
#else
    SurgeVOC()
        : SurgeModuleCommon(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
        setupSurge();
    }
#endif

    virtual std::string getName() override { return "VOC"; }

    virtual void setupSurge() {
        setupSurgeCommon();
    }


#if RACK_V1
    void process(const typename rack::Module::ProcessArgs &args) override
#else
    void step() override
#endif
    {
    }
};
