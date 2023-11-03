#pragma once
#include "wx/wx.h"
#include "Event.h"

class HomeFrameController{

	void handleInstrumentSelected(const Event& event);

public:
	HomeFrameController();

	void onInstrumentSelection(wxWindow* parent);

};
