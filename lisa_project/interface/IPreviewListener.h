#pragma once

class IPreviewListener
{
public:
	virtual void startPreview() = 0;
	virtual void stopPreview() = 0;
	virtual void onPreviewButton() = 0;
	virtual void onLoadImage(wxImage& image) = 0;
};
