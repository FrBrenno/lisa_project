#pragma once
#include <wx/wx.h>
#include "IPreviewListener.h"

class IPreview
{
public:
	virtual void updatePreviewButton(bool isPreviewOn) = 0;
	virtual void setImage(wxImage* image) = 0;
	virtual void freezePreview() = 0;
	virtual void thawPreview() = 0;

	virtual void setPreviewListener(IPreviewListener* listener) = 0;
};
