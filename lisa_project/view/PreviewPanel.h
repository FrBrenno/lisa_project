#pragma once
#include <wx/wx.h>
#include "interface/IPreviewHolder.h"
#include "interface/IPreviewHolderListener.h"

class PreviewPanel : public wxPanel, public IPreviewHolder
{
	wxStaticBitmap* imageControl;
	wxButton* previewButton;
	wxButton* captureButton;

	IPreviewHolderListener* previewListener;
public:
	PreviewPanel(wxWindow* parent);
	~PreviewPanel();

	wxStaticBitmap* getPreviewImageControl() override;
	wxButton* getPreviewButton() override;
	wxButton* getCaptureButton() override;

	void onCapture(wxWindow* parent);
	void loadImage();
	void setImage(wxImage* image);

	void setPreviewListener(IPreviewHolderListener* listener) override;
};
