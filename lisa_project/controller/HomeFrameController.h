#pragma once
#include "wx/wx.h"
#include "../Event.h"
#include "BaseController.h"

/**
 * @class HomeFrameController.
 * @brief This controller manages HomeFrame view responsible for the main window of the software.
 */
class HomeFrameController: public BaseController{
public:
	HomeFrameController(MyAppInterface* main, bool is_wfs_connected);

	/**
	 * Publishes an InstrumentSelectionEvent.
	 * 
	 * @param parent 
	 */
	void onInstrumentSelection(wxWindow* parent);

	wxImage onLoadImage(wxWindow* parent);

	void onConnectAPI(wxWindow* parent);

	void onCameraSettings(wxWindow* parent);

	void onCapture(wxWindow* parent, wxBitmap lastBitmap);
};