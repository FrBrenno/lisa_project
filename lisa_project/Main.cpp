// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "HomeFrame.h"
#include "Instrument.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
    Instrument* instrument;
    HomeFrameController* homeFrameController;

    void setInstrument(Instrument instrument);

public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    //=== Controller initialization ===//
    this->homeFrameController = new HomeFrameController(this);

    //=== View initialization ===//
    HomeFrame* home = new HomeFrame();
    home->setListener(this->homeFrameController);

    home->Show(true);

     return true;
}

void MyApp::setInstrument(Instrument instrument){
    return;
}
