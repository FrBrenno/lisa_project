#pragma once
#include <wx/wx.h>
#include "HomeFrameController.h"

class HomeFrame : public wxFrame
{
public:
    HomeFrame();
    void setListener(HomeFrameController* controller);

private:
    HomeFrameController *listener;

    void OnInstrumentSelection(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    //TODO: Add methods to all available menu items
};