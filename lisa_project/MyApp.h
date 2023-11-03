#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "HomeFrame.h"
#include "HomeFrameController.h"
#include "InstrumentController.h"
#include "InstrumentSelectionDialog.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
    //=== Controllers ===//
    HomeFrameController* homeFrameController;
    InstrumentController* instrumentController;

    //== Views ===//
    HomeFrame* homeFrame;


public:
    virtual bool OnInit();
};