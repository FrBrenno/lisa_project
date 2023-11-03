#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "HomeFrame.h"
#include "Instrument.h"
#include "HomeFrameController.h"
#include "InstrumentController.h"
#include "InstrumentSelectionDialog.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
    //=== Models ===//
    Instrument* instrument;

    //=== Controllers ===//
    HomeFrameController* homeFrameController;
    InstrumentController* instrumentController;

    //== Views ===//
    HomeFrame* homeFrame;


    //=== Models Methods ===//
    void setInstrument(Instrument* instrument);

public:
    virtual bool OnInit();
};