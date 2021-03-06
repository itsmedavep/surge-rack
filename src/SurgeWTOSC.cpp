#include "SurgeWTOSC.hpp"
#include "Surge.hpp"
#include "SurgeRackGUI.hpp"

struct SurgeWTOSCWidget : public virtual SurgeModuleWidgetCommon {
    typedef SurgeWTOSC M;
    SurgeWTOSCWidget(M *module);

    int fontId = -1;
    int ioMargin = 7;
    int ioRegionWidth = 105;
    int padMargin = 3;
    int padFromEdge = 5;

    float pitchY = SCREW_WIDTH + padFromEdge;
    float pitchCtrlX = padFromEdge + 2 * padMargin + 2 * SurgeLayout::portX;
    
    float controlsY = pitchY + 2 * padMargin + SurgeLayout::surgeRoosterY + SurgeLayout::portY;
    float controlsHeight = SurgeLayout::orangeLine - controlsY - padMargin;
    float controlHeightPer = controlsHeight / n_osc_params;

    float colOneEnd = SurgeLayout::surgeRoosterX + SurgeLayout::portX + 2 * padMargin + 14 + pitchCtrlX + padFromEdge;
    
    void moduleBackground(NVGcontext *vg) {
        // The input triggers and output
        nvgBeginPath(vg);

        if (fontId < 0)
            fontId = InternalFontMgr::get(vg, SurgeStyle::fontFace());

        // Draw the output blue box
        float x0 = box.size.x - ioRegionWidth - 2 * ioMargin;
        SurgeStyle::drawBlueIORect(
            vg, x0 + ioMargin, SurgeLayout::orangeLine + ioMargin,
            ioRegionWidth, box.size.y - SurgeLayout::orangeLine - 2 * ioMargin);

        nvgFillColor(vg, SurgeStyle::backgroundGray());
        nvgFontFaceId(vg, fontId);
        nvgFontSize(vg, 12);
        nvgSave(vg);
        nvgTranslate(vg, x0 + ioMargin + ioRegionWidth - 2,
                     SurgeLayout::orangeLine + ioMargin * 1.5);
        nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgRotate(vg, M_PI / 2);
        nvgText(vg, 0, 0, "Output", NULL);
        nvgRestore(vg);

        rack::Vec ll;
        ll = ioPortLocation(0);
        ll.y = box.size.y - ioMargin - 1.5;
        ll.x += 24.6721 / 2;
        nvgFontSize(vg, 11);
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_BOTTOM);
        nvgText(vg, ll.x, ll.y, "L/Mon", NULL);

        ll = ioPortLocation(1);
        ll.y = box.size.y - ioMargin - 1.5;
        ll.x += 24.6721 / 2;
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_BOTTOM);
        nvgText(vg, ll.x, ll.y, "R", NULL);

        ll = ioPortLocation(2);
        ll.y = box.size.y - ioMargin - 1.5;
        ll.x += 24.6721 / 2;
        nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_BOTTOM);
        nvgText(vg, ll.x, ll.y, "Gain", NULL);

        float pitchLY = pitchY + SurgeLayout::surgeRoosterY / 2.0 + SurgeLayout::portY/2 + padMargin/2;
        nvgBeginPath(vg);
        nvgFontFaceId(vg, fontId);
        nvgFontSize(vg, 15);
        nvgTextAlign(vg, NVG_ALIGN_MIDDLE | NVG_ALIGN_LEFT );
        nvgFillColor(vg, SurgeStyle::surgeBlue() );
        nvgText(vg, padFromEdge, pitchLY, "Pitch", NULL );

        float xt = pitchCtrlX + SurgeLayout::surgeRoosterX + SurgeLayout::portX + 2 * padMargin + 12;

        nvgBeginPath(vg);
        nvgFontFaceId(vg, fontId);
        nvgFontSize(vg, 10);
        nvgTextAlign(vg, NVG_ALIGN_TOP | NVG_ALIGN_LEFT );
        nvgFillColor(vg, SurgeStyle::surgeBlue() );
        nvgText(vg, xt, pitchY + 2, "f", NULL );

        nvgBeginPath(vg);
        nvgFontFaceId(vg, fontId);
        nvgFontSize(vg, 10);
        nvgTextAlign(vg, NVG_ALIGN_BOTTOM | NVG_ALIGN_LEFT );
        nvgFillColor(vg, SurgeStyle::surgeBlue() );
        nvgText(vg, xt, pitchY + SurgeLayout::surgeRoosterY - 4, "n", NULL );

        
        xt += 7 + padMargin;
        SurgeStyle::drawTextBGRect(vg, pitchCtrlX, pitchY+SurgeLayout::surgeRoosterY + padMargin,
                                   SurgeLayout::surgeRoosterX + SurgeLayout::portX + 2 * padMargin + 14, SurgeLayout::portY );
            
        for (int i = 0; i < n_osc_params; ++i) {
            float yp = i * controlHeightPer + controlsY;
            float xp = padFromEdge + 2 * padMargin + 2 * SurgeLayout::portX;
            SurgeStyle::drawTextBGRect(vg, xp, yp, colOneEnd - padFromEdge - xp, controlHeightPer - padMargin);
        }

        // OSC picker side
        nvgBeginPath(vg);
        nvgFontFaceId(vg,fontId);
        nvgFontSize(vg,12);
        nvgFillColor(vg, nvgRGB(255,0,0));
        nvgTextAlign(vg, NVG_ALIGN_TOP | NVG_ALIGN_LEFT );
        nvgText(vg, colOneEnd + padFromEdge, SCREW_WIDTH + padFromEdge, "WT PICKER UI ALPHA", NULL );


        nvgBeginPath(vg);
        nvgFontFaceId(vg,fontId);
        nvgFontSize(vg,12);
        nvgFillColor(vg, SurgeStyle::surgeBlue());
        nvgTextAlign(vg, NVG_ALIGN_TOP | NVG_ALIGN_LEFT );
        nvgText(vg, colOneEnd + padFromEdge, SCREW_WIDTH + padFromEdge + 20 + 50, "cat", NULL );
        nvgText(vg, colOneEnd + padFromEdge + SurgeLayout::surgeRoosterX + padMargin, SCREW_WIDTH + padFromEdge + 20 + 50, "wt", NULL );
        nvgText(vg, colOneEnd + padFromEdge + 2*SurgeLayout::surgeRoosterX + 2*padMargin, SCREW_WIDTH + padFromEdge + 20 + 50, "load", NULL );


        auto yTPos = SCREW_WIDTH + padFromEdge + 40 + SurgeLayout::surgeRoosterY + padMargin + 50;
        SurgeStyle::drawTextBGRect(vg, colOneEnd + padFromEdge, yTPos,
                                   box.size.x - colOneEnd - 2 * padFromEdge, 20 );
        yTPos += 20 + padMargin;
        SurgeStyle::drawTextBGRect(vg, colOneEnd + padFromEdge, yTPos,
                                   box.size.x - colOneEnd - 2 * padFromEdge, 20 );
        
    }

    rack::Vec ioPortLocation(int ctrl) { // 0 is L; 1 is R; 2 is gain
        float x0 = box.size.x - ioRegionWidth - 2 * ioMargin;

        int xRes =
            x0 + ioMargin + padFromEdge + (ctrl * (SurgeLayout::portX + 4));
        int yRes = SurgeLayout::orangeLine + 1.5 * ioMargin;

        return rack::Vec(xRes, yRes);
    }
};

SurgeWTOSCWidget::SurgeWTOSCWidget(SurgeWTOSCWidget::M *module)
    : SurgeModuleWidgetCommon(
#if !RACK_V1
          module
#endif
      )
#if !RACK_V1
    , rack::ModuleWidget(module) // why do I need this gcc? SMWC calls it.
#endif    
{
#if RACK_V1
    setModule(module);
#endif

    box.size = rack::Vec(SCREW_WIDTH * 20, RACK_HEIGHT);
    SurgeRackBG *bg = new SurgeRackBG(rack::Vec(0, 0), box.size, "WTOSC");
    bg->moduleSpecificDraw = [this](NVGcontext *vg) {
        this->moduleBackground(vg);
    };
    addChild(bg);

    addOutput(rack::createOutput<rack::PJ301MPort>(ioPortLocation(0), module,
                                                   M::OUTPUT_L));
    addOutput(rack::createOutput<rack::PJ301MPort>(ioPortLocation(1), module,
                                                   M::OUTPUT_R));
    addParam(rack::createParam<SurgeSmallKnob>(ioPortLocation(2), module,
                                               M::OUTPUT_GAIN
#if !RACK_V1
                                               ,
                                               0, 1, 1
#endif
                                               ));


    int xp = pitchCtrlX;
    addParam(rack::createParam<SurgeKnobRooster>(
                 rack::Vec(xp, pitchY), module, M::PITCH_0
#if !RACK_V1
        ,
        1, 127, 72
#endif
        ));
    addInput(rack::createInput<rack::PJ301MPort>(
                 rack::Vec( xp + SurgeLayout::surgeRoosterX + padMargin,
                            pitchY + ( SurgeLayout::surgeRoosterY - SurgeLayout::portY ) / 2),
                 module, M::PITCH_CV));
    addParam(rack::createParam<SurgeSwitch>(rack::Vec(xp + SurgeLayout::surgeRoosterX + SurgeLayout::portX + 2 * padMargin,
                                                      pitchY + ( SurgeLayout::surgeRoosterY - 21 ) / 2),
                                            module, M::PITCH_0_IN_FREQ
#if !RACK_V1
                                            ,0,1,0
#endif
                 ));

    addChild(TextDisplayLight::create(
                 rack::Vec(pitchCtrlX + 2, pitchY+SurgeLayout::surgeRoosterY + padMargin),
                 rack::Vec(SurgeLayout::surgeRoosterX + SurgeLayout::portX + 2 * padMargin + 14, SurgeLayout::portY ),
                 module ? &(module->pitch0DisplayCache) : nullptr,
                 14,
                 NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE,
                 SurgeStyle::surgeWhite()
                 ));

    for (int i = 0; i < n_osc_params; ++i) {
        float yp = i * controlHeightPer + controlsY;
        float yctrl = yp + controlHeightPer / 2 - SurgeLayout::portY / 2 - padMargin/2;
        addParam(rack::createParam<SurgeSmallKnob>(rack::Vec(padFromEdge, yctrl), module,
                                                   M::OSC_CTRL_PARAM_0 + i
#if !RACK_V1
                                                   ,
                                                   0, 1, 0.5
#endif
                                                   ));
        addInput(rack::createInput<rack::PJ301MPort>(rack::Vec(padFromEdge + padMargin + SurgeLayout::portX, yctrl), module,
                                                     M::OSC_CTRL_CV_0 + i));

        float xt = padFromEdge + 2 * padMargin + 2 * SurgeLayout::portX;

        addChild(TextDisplayLight::create(
                     rack::Vec(xt+2, yp + 0.5), rack::Vec(colOneEnd - xt - padMargin, controlHeightPer - padMargin - 2),
                     module ? &(module->paramNameCache[i]) : nullptr,
                     12));
        addChild(TextDisplayLight::create(
                     rack::Vec(xt+2, yp+1 ), rack::Vec(colOneEnd - xt - padMargin, controlHeightPer - padMargin - 2),
                     module ? (&module->paramValueCache[i]) : nullptr,
                     15, NVG_ALIGN_LEFT | NVG_ALIGN_BOTTOM, SurgeStyle::surgeWhite()));
    }

    SurgeButtonBank *bank = SurgeButtonBank::create( rack::Vec(colOneEnd+padFromEdge, pitchY + 20),
                                                     rack::Vec(box.size.x - colOneEnd - 2 * padFromEdge, 40),
                                                     module, M::WT_OR_WINDOW,
                                                     2, 1, 13 );

    bank->addLabel("Wavetable");
    bank->addLabel("Window");
    
    addParam(bank);

    float wtSelY = pitchY + 50;

    addParam(rack::createParam<SurgeKnobRooster>(
                 rack::Vec(colOneEnd + padFromEdge, wtSelY + 40), module, M::CATEGORY_IDX
#if !RACK_V1
        ,
                 0,1,0
#endif
        ));


    addParam(rack::createParam<SurgeKnobRooster>(
                 rack::Vec(colOneEnd + padFromEdge + padMargin + SurgeLayout::surgeRoosterX, wtSelY + 40),
                 module, M::WT_IN_CATEGORY_IDX
#if !RACK_V1
                 ,
                 0,1,0
#endif
                 ));

    addParam(rack::createParam<rack::CKD6>(
                 rack::Vec(colOneEnd + padFromEdge + 2*padMargin + 2*SurgeLayout::surgeRoosterX, wtSelY + 40),
                 module, M::LOAD_WT
#if !RACK_V1
                 ,
                 0,1,0
#endif
                 ));

    addChild(rack::createLight<rack::SmallLight<rack::GreenLight>>(
                 rack::Vec(colOneEnd + padFromEdge + 3*padMargin + 3*SurgeLayout::surgeRoosterX, wtSelY + 37),
                 module, M::NEEDS_LOAD
                 ));


    auto xTPos = colOneEnd + padMargin;
    auto yTPos = SCREW_WIDTH + padFromEdge + 40 + SurgeLayout::surgeRoosterY + padMargin + 50;
    addChild(TextDisplayLight::create(
                 rack::Vec(xTPos + 4, yTPos),
                 rack::Vec(box.size.x - xTPos - 2 * padMargin, 19 ),
                 module ? &(module->wtCategoryName) : nullptr,
                 15, NVG_ALIGN_MIDDLE | NVG_ALIGN_LEFT, SurgeStyle::surgeWhite()));

    yTPos += 20 + padMargin;
    addChild(TextDisplayLight::create(
                 rack::Vec(xTPos + 4, yTPos),
                 rack::Vec(box.size.x - xTPos - 2 * padMargin, 19 ),
                 module ? &(module->wtItemName) : nullptr,
                 15, NVG_ALIGN_MIDDLE | NVG_ALIGN_LEFT, SurgeStyle::surgeWhite()));

 
}

#if RACK_V1
rack::Model *modelSurgeWTOSC =
    rack::createModel<SurgeWTOSCWidget::M, SurgeWTOSCWidget>("SurgeWTOSC");
#else
rack::Model *modelSurgeWTOSC =
    rack::createModel<SurgeWTOSCWidget::M, SurgeWTOSCWidget>(
        "Surge Team", "SurgeWTOSC", "SurgeWTOSC", rack::ENVELOPE_GENERATOR_TAG);
#endif
