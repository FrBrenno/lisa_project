#pragma once
#include "wx/wx.h"
#include "Instrument.h"
#include "BaseController.h"
#include "IInstrumentViewListener.h"

/**
 * @class InstrumentController.
 * @brief This controller class is responsible for managing Instruments and their associated views.
 */
class InstrumentController: public BaseController, public IInstrumentViewListener{
	/**
	 * @brief Instrument object.
	 * 
	 */
	Instrument* instrument;
	/**
	 * @brief MLA object.
	 * 
	 */
	Mla* mla;
	/**
	 * @brief Flag that indicates if the instrument is connected.
	 * 
	 */
	ViInt32 err;

public:
	InstrumentController(MyAppInterface* main, IApiService* wfsApiService);
	~InstrumentController();

	/**
	 * @brief Returns the name of the instrument.
	 * 
	 * @return std::string name of the instrument
	 */
	std::string getInstrumentName();
	/**
	 * @brief Returns the instrument object.
	 * 
	 * @return Instrument* pointer to the instrument object
	 */
	Instrument* getInstrument();

	//=== Interface Implementation ===//
	// View management

	/**
	 * @brief Populates the instrument list.
	 * 
	 * @param list Listbox to populate
	 */
	void populateInstrumentList(wxListBox* list) override;
	/**
	 * @brief Handles when a instrument is selected. Normally, the view should call this function.
	 * 
	 * @param selectedIndex
	 */
	void onInstrumentSelected(int selectedIndex) override;
	/**
	* @brief Handles when the view is closed.
	* 
	**/
	void onClose() override;

	//=== Instrument API Functions ===//
	// Low-level instrument API functions

	/**
	 * @brief Initialize instrument attributes by extracting information from Thorslab API.
	 * 
	 * @param resourceName Resource name of the instrument.
	 */
	void initInstrument(InstrumentDto& instrumentDto);
	/**
	 * @brief Closes instrument API session.
	 * 
	 */
	void closeInstrument();
	/**
	 * @brief Selects default MLA.
	 * 
	 */
	void selectMla();
	/**
	 * @brief Configures the camera.
	 * 
	 */
	void cameraConfiguration();

	//=== Event Handlers ===//

	/**
	 * @brief Handles when a InstrumentSelectionEvent is published
	 *
	 */
	void HandleInstrumentSelection();
	/**
	* @brief Handles when a ExitEvent is published
	*
	*/
	void onExit();

	//=== Getters ===//
	/**
	 * @brief Get the Instrument Handle object
	 * 
	 * @return ViSession handle to the instrument.
	 */
	const ViSession getInstrumentHandle();
};
