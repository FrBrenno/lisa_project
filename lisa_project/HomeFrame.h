#pragma once
#include <wx/wx.h>

class HomeFrame : public wxFrame
{
public:
    HomeFrame();

private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    //TODO: Add methods to all available menu items
};