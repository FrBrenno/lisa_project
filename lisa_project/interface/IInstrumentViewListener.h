#pragma once
#include <wx/wx.h>

class IInstrumentViewListener 
{
public:
	virtual void populateInstrumentList(wxListBox* instrumentList) = 0;
	virtual void onInstrumentSelected(int selectedIndex) = 0;
	virtual void onClose() = 0;
};
