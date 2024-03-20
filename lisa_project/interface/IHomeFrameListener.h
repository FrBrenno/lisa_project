#pragma once
#include <wx/wx.h>

class IHomeFrameListener
{
public:
	virtual wxImage onLoadImage(wxWindow* parent) = 0;
	virtual void onConnectAPI() = 0;
};
