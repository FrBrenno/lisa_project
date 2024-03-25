#pragma once

class IPreviewListener
{
public:
	virtual void stopPreview() = 0;
	virtual void onPreviewButton() = 0;
};
