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
    InstrumentController* instrumentSelectionController;

    //== Views ===//
    HomeFrame* homeFrame;


    //=== Models Methods ===//
    void setInstrument(Instrument *instrument);

public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    //=== Controller initialization ===//
    this->homeFrameController = new HomeFrameController(this);
    this->instrumentSelectionController = new InstrumentController(this);

    //=== View initialization ===//
    homeFrame = new HomeFrame();
    homeFrame->setListener(this->homeFrameController);
    // Before Showing the software, do instrument selection
    InstrumentSelectionDialog* instrumentSelectionDialog = new InstrumentSelectionDialog(homeFrame);
    instrumentSelectionDialog->setListener(this->instrumentSelectionController);
    instrumentSelectionDialog->ShowModal();

    homeFrame->Show(true);

     return true;
}

void MyApp::setInstrument(Instrument *instrument){
    this->instrument = instrument;  
    return;
}


