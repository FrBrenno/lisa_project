#pragma once
#include <wx/wx.h>
#include "HomeFrameController.h"

class HomeFrame : public wxFrame
{
    HomeFrameController* listener;

    void OnInstrumentSelection(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    //TODO: Add methods to all available menu items
public:
    HomeFrame();
    void setListener(HomeFrameController* controller);

    
};