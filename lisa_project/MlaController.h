#pragma once
#include "wx/wx.h"
#include "Mla.h"
#include "WFS.h"
#include "Event.h"

/**
 * @class MlaController.
 * @brief This controller manages the MlaSelectionDialog view and generate Mla objects.
 */
class MlaController {
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
	void HandleMlaSelected(const Event& event);
public:
	MlaController();

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
	 * Handles when the user closes the view.
	 * 
	 */
	void onClose();

	/**
	 * Handles error messages.
	 * 
	 * @param code Error code.
	 * @param message Developer error message.
	 */
	void handleError(int code, std::string message);
};
