#pragma once
#include "wx/wx.h"
#include "../model/Instrument.h"
#include "../Event.h"
#include "BaseController.h"

/**
 * @class InstrumentController.
 * @brief This controller class is responsible for managing Instruments and their associated views.
 */
class InstrumentController: public BaseController{
	Instrument* instrument;
	ViInt32 err;

	

public:
	InstrumentController(MyAppInterface* main, WfsApiService* wfsApiService);
	~InstrumentController();

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
	void initInstrument(InstrumentDto instrumentDto);	
	/**
	 * Closes instrument API session.
	 * 
	 */
	void closeInstrument();

	void onClose() override;

	void onExit();

	/**
	 * Handles when a InstrumentSelectionEvent is published
	 *
	 */
	void HandleInstrumentSelection();

	const ViSession getInstrumentHandle();
};
