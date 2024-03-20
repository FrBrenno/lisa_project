#pragma once

class IPreviewHolderListener
{
public:
	virtual void startPreview() = 0;
	virtual void stopPreview() = 0;
	virtual void onCapture(wxWindow* window, wxBitmap bitmap) = 0;
};
