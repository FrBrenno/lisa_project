#pragma once
#include <wx/wx.h>
#include "IPreviewListener.h"

class IPreview
{
public:
	/**
	 * @brief Start preview.
	 * 
	 */
	virtual void startPreview() = 0;
	/**
	 * @brief Stop preview.
	 * 
	 */
	virtual void stopPreview() = 0;
	/**
	 * @brief Update the preview button.
	 * 
	 * If preview is on, the button should be set to "Stop preview".
	 * If preview is off, the button should be set to "Start preview".
	 * 
	 * @param isPreviewOn indicates if the preview is on.
	 
	 */
	virtual void updatePreviewButton(bool isPreviewOn) = 0;
	/**
	 * @brief Get the frame on the preview.
	 * 
	 * @return wxImage the preview frame.
	 */
	virtual wxImage getFrame() = 0;
	/**
	 * @brief Set the frame on the preview.
	 * 
	 * @param image the preview frame.
	 */
	virtual void setImage(wxImage* image) = 0;
	/**
	 * @brief Freeze the preview.
	 * 
	 */
	virtual void freezePreview() = 0;
	/**
	 * @brief Thaw the preview.
	 * 
	 */
	virtual void thawPreview() = 0;

	/**
	 * @brief Set the preview listener.
	 * 
	 * @param listener the preview listener.
	 */
	virtual void setPreviewListener(IPreviewListener* listener) = 0;
};
