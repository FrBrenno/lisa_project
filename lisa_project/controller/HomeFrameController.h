#pragma once
#include "wx/wx.h"
#include "../Event.h"
#include "BaseController.h"

/**
 * @class HomeFrameController.
 * @brief This controller manages HomeFrame view responsible for the main window of the software.
 */
class HomeFrameController : public BaseController{
public:
	HomeFrameController(MyAppInterface* main, WfsApiService* wfsApiService);

	/**
	 * Publishes an InstrumentSelectionEvent.
	 * 
	 * @param parent 
	 */
	void onInstrumentSelection(wxWindow* parent);

	wxImage onLoadImage(wxWindow* parent);

	void onConnectAPI(wxWindow* parent);

	void onCapture(wxWindow* parent, wxBitmap lastBitmap);

	void onExit();
};
