#pragma once
#include <wx/wx.h>
#include "interface/IPreview.h"
#include "interface/IPreviewListener.h"

class PreviewPanel : public wxPanel, public IPreview
{
	wxWindow* parent;

	wxStaticBitmap* imageControl;
	wxButton* previewButton;
	wxButton* captureButton;

	IPreviewListener* previewListener;
public:
	PreviewPanel(wxWindow* parent);
	~PreviewPanel();

	void onCapture(wxWindow* parent);
	void loadImage();

	// Inherited via IPreview
	void stopPreview() override;
	void updatePreviewButton(bool isPreviewOn) override;
	void setImage(wxImage* image) override;
	void freezePreview() override;
	void thawPreview() override;
	void setPreviewListener(IPreviewListener* listener) override;
};
