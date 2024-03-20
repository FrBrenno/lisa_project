#pragma once
#include <wx/wx.h>
#include "IPreviewHolderListener.h"

class IPreviewHolder
{
public:
	virtual wxStaticBitmap* getPreviewImageControl() = 0;
	virtual wxButton* getPreviewButton() = 0;
	virtual wxButton* getCaptureButton() = 0;

	virtual void setPreviewListener(IPreviewHolderListener* listener) = 0;
};
