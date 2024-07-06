#pragma once

class IPreviewListener
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
	 * @brief Handles preview button.
	 * 
	 *  Launch or stop the preview.
	 * 
	 * @param parent the parent window.
	 */
	virtual void onPreviewButton() = 0;
	/**
	 * @brief Handles load button
	 * 
	 * Load an image from a file to the preview
	 * 
	 * @param image the image to load
	 */
	virtual void onLoadImage(wxImage& image) = 0;
};
