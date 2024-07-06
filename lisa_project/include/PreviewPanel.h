#pragma once
#include <wx/wx.h>
#include "IPreview.h"
#include "IPreviewListener.h"

/**
 * @class PreviewPanel
 * @brief Panel responsible to show the preview of the image.
 * 
 */
class PreviewPanel : public wxPanel, public IPreview
{
	wxWindow* parent;

	/**
	 * @brief Image container.
	 * 
	 */
	wxStaticBitmap* imageControl;
	/**
	 * @brief Preview button responsible to start/stop the preview.
	 * 
	 */
	wxButton* previewButton;
	/**
	 * @brief Capture button responsible to capture the image.
	 * 
	 */
	wxButton* captureButton;
	/**
	 * @brief Load button responsible to load an image.
	 * 
	 */
	wxButton* loadButton;

	/**
	 * @brief Listener that manage this panel.
	 * 
	 */
	IPreviewListener* previewListener;
public:
	PreviewPanel(wxWindow* parent);
	~PreviewPanel();

	/**
	 * @brief Handles capture button.
	 * 
	 * Opens a dialog to save the image and saves it.
	 * 
	 * @param parent
	 */
	void onCapture(wxWindow* parent);
	/**
	 * @brief Loads an image.
	 * 
	 */
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
