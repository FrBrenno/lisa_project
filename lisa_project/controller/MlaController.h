#pragma once
#include "wx/wx.h"
#include "../model/Mla.h"
#include "WFS.h"
#include "../Event.h"
#include "BaseController.h"

/**
 * @class MlaController.
 * @brief This controller manages the MlaSelectionDialog view and generate Mla objects.
 */
class MlaController: public BaseController {
	Mla* selectMla;
	ViInt32 err;

	/**
	 * Handles when a MlaSelectionEvent is published.
	 * 
	 * @param event MlaSelectionEvent.
	 */
	void HandleMlaSelection(const Event& event);
	/**
	 * Handles when this class finishes handling MlaSelectionEvent.
	 * 
	 * @param event MlaSelectedEvent
	 */
	void HandleMlaSelected();
public:
	MlaController(MyAppInterface* main, bool is_wfs_connected);

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

	void onClose() override;
};
