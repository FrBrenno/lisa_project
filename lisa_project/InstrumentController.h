#pragma once
#include "wx/wx.h"
#include "Instrument.h"
#include "Event.h"

/**
 * @class InstrumentController.
 * @brief This controller class is responsible for managing Instruments and their associated views.
 */
class InstrumentController{
	Instrument* selectedInstrument;
	ViInt32 instrumentCount;
	ViInt32 err;

	/**
	 * Handles when a InstrumentSelectionEvent is published
	 * 
	 * @param event InstrumentSelectionEvent
	 */
	void HandleInstrumentSelection(const Event& event);
	/**
	 * Handles when a MlaSelectedEvent is published.
	 * 
	 * @param event MlaSelectedEvent
	 */
	void HandleMlaSelected(const Event& event);

public:
	InstrumentController();

	std::string getInstrumentName();
	Instrument* getInstrument();

	/**
	 * Inserts the list of instruments into the listbox.
	 * 
	 * @param list Listbox to populate
	 */
	void populateInstrumentList(wxListBox* list);
	/**
	 * Handles when a instrument is selected. Normally, the view should call this function.
	 * 
	 * @param selectedIndex
	 */
	void onInstrumentSelected(int selectedIndex);
	/**
	 * Initialize instrument attributes by extracting information from Thorslab API.
	 * 
	 * @param resourceName Resource name of the instrument.
	 */
	void initInstrument(ViRsrc resourceName);
	/**
	 * Make a driver revision in order to verify driver version. Used to check API connexion.
	 * 
	 */
	void reviseDrive();
	/**
	 * Uses Thorslab API to configure the camera.
	 * 
	 */
	void cameraConfiguration();
	/**
	 * Publishes an MlaSelectionEvent.
	 * 
	 */
	void mlaConfiguration();
	/**
	 * Handles when the user closes the InstrumentSelectionDialog.
	 */
	void onClose();	
	/**
	 * Closes instrument API session.
	 * 
	 */
	void closeInstrument();

	/**
	 * Handles error messages.
	 * 
	 * @param code Error code
	 * @param message Developer error message
	 */
	void handleError(int code, std::string message);
};
