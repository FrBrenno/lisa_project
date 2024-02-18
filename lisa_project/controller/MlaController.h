#pragma once
#include "wx/wx.h"
#include "../model/Mla.h"
#include "lib/thorlabs_api/WFS.h"
#include "../Event.h"
#include "BaseController.h"

/**
 * @class MlaController.
 * @brief This controller manages the MlaSelectionDialog view and generate Mla objects.
 */
class MlaController: public BaseController {
	Mla* mla;
	ViInt32 err;

	
public:
	MlaController(MyAppInterface* main, WfsApiService* wfsApiService);
	~MlaController();

	/**
	 * Inserts all the MLAs given by Thorlabs API in the list.
	 * 
	 * @param list
	 */
	void populateMlaList(wxListBox* list);
	/**
	 * Handles when the user seleced an MLA.
	 * 
	 * @param selectedIndex Index of the selected MLA.
	 */
	void onMlaSelected(int selectedIndex);
	/**
	 * Handles when a MlaSelectionEvent is published.
	 *
	 * @param event MlaSelectionEvent.
	 */
	void HandleMlaSelection();
	/**
	 * Handles when this class finishes handling MlaSelectionEvent.
	 *
	 * @param event MlaSelectedEvent
	 */
	void HandleMlaSelected();
	void onClose() override;
};
