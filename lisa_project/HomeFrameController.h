#pragma once
#include "wx/wx.h"
#include "Event.h"

/**
 * @class HomeFrameController.
 * @brief This controller manages HomeFrame view responsible for the main window of the software.
 */
class HomeFrameController{

public:
	HomeFrameController();

	/**
	 * Publishes an InstrumentSelectionEvent.
	 * 
	 * @param parent 
	 */
	void onInstrumentSelection(wxWindow* parent);
	/**
	 * Handles when the user closes the window.
	 * 
	 */
	void onClose();

};
