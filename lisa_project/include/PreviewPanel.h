#pragma once
#include <wx/wx.h>
#include "IPreview.h"
#include "IPreviewListener.h"

class PreviewPanel : public wxPanel, public IPreview
{
	wxWindow* parent;

	wxStaticBitmap* imageControl;
	wxButton* previewButton;
	wxButton* captureButton;
	wxButton* loadButton;

	IPreviewListener* previewListener;
public:
	PreviewPanel(wxWindow* parent);
	~PreviewPanel();

	void onCapture(wxWindow* parent);
	void loadImage();

	// Inherited via IPreview
	void startPreview() override;
	void stopPreview() override;
	void updatePreviewButton(bool isPreviewOn) override;
	wxImage getFrame() override;
	void setImage(wxImage* image) override;
	void freezePreview() override;
	void thawPreview() override;
	void setPreviewListener(IPreviewListener* listener) override;
};
