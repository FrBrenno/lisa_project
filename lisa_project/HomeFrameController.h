#pragma once
#include <wx/wx.h>

class HomeFrameController{
private:
	wxApp* main;
public:
	HomeFrameController(wxApp *main);
	void selectInstrument();
	void reviseDrive();
};
