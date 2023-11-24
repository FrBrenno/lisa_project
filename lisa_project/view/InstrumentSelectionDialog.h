#pragma once
#include <wx/wx.h>
#include "../controller/InstrumentController.h"

/**
 * @class InstrumentSelectionDialog.
 * @brief This view is used to select an instrument from a list of available instruments.
 * @details This view is managed by its respective controller, InstrumentController.
 */
class InstrumentSelectionDialog: public wxDialog{
	wxWindow* parent;
	InstrumentController* listener;

public:	
	/**
	 * InstrumentSelectionDialog Constructor.
	 * 
	 * @param parent The window that generated this dialog. This could be a nullptr.
	 * @param listener The controller that manages this view.
	 */
	InstrumentSelectionDialog(wxWindow* parent, InstrumentController* listener);

	/**
	 * Handles when the user clicks the OK button.
	 * 
	 * @param event OnOk default wxWidgets Event.
	 */
	void OnOK(wxCommandEvent& event);
	/**
	 * Handles when the user closes the dialog.
	 * 
	 * @param event OnClose default wxWidgets Event.
	 */
	void OnClose(wxCloseEvent& event);
};
