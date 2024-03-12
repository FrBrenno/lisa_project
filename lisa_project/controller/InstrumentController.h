#pragma once
#include "wx/wx.h"
#include "../model/Instrument.h"
#include "BaseController.h"
#include "../interface/IInstrumentViewListener.h"

/**
 * @class InstrumentController.
 * @brief This controller class is responsible for managing Instruments and their associated views.
 */
class InstrumentController: public BaseController, public IInstrumentViewListener{
	Instrument* instrument;
	ViInt32 err;

public:
	InstrumentController(MyAppInterface* main, IApiService* wfsApiService);
	~InstrumentController();

	std::string getInstrumentName();
	Instrument* getInstrument();

	//=== Interface Implementation ===//
	// View management

	/**
	 * Inserts the list of instruments into the listbox.
	 * 
	 * @param list Listbox to populate
	 */
	void populateInstrumentList(wxListBox* list) override;
	/**
	 * Handles when a instrument is selected. Normally, the view should call this function.
	 * 
	 * @param selectedIndex
	 */
	void onInstrumentSelected(int selectedIndex) override;
	/**
	* Handles when the view is closed.
	** 
	**/
	void onClose() override;

	//=== Instrument API Functions ===//
	// Low-level instrument API functions

	/**
	 * Initialize instrument attributes by extracting information from Thorslab API.
	 * 
	 * @param resourceName Resource name of the instrument.
	 */
	void initInstrument(InstrumentDto& instrumentDto);
	/**
	 * Closes instrument API session.
	 * 
	 */
	void closeInstrument();


	//=== Event Handlers ===//

	/**
	 * Handles when a InstrumentSelectionEvent is published
	 *
	 */
	void HandleInstrumentSelection();
	/**
	* Handles when a ExitEvent is published
	**
	*/
	void onExit();

	//=== Getters ===//
	const ViSession getInstrumentHandle();

};
