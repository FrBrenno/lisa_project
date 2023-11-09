#pragma once
#include <wx/wx.h>
#include "MlaController.h"

/**
 * @class MlaSelectionDialog.
 * @brief This view is a dialog box that allows the user to select a MLA.
 * @details This view is managed by its respective controller, MlaController.
 */
class MlaSelectionDialog : public wxDialog {
	wxWindow* parent;
	MlaController* listener;
public:
	/**
	 * Constructor of MlaSelectionDialog.
	 * 
	 * @param parent The view that generates the dialog box. It could be nullptr.
	 * @param listener The controller that manages the view.
	 */
	MlaSelectionDialog(wxWindow* parent, MlaController* listener);

	/**
	 * Handles when the user clicks in the button OK.
	 * 
	 * @param event OnOK default wxWidgets event.
	 */
	void OnOK(wxCommandEvent& event);
	/**
	 * Handles when the user closes the dialog box.
	 * 
	 * @param event OnClose default wxWidgets event.
	 */
	void OnClose(wxCloseEvent& event);
};
