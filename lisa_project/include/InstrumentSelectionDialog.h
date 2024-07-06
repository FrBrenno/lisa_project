#pragma once
#include <wx/wx.h>
#include "IInstrumentViewListener.h"

/**
 * @class InstrumentSelectionDialog.
 * @brief This view is used to select an instrument from a list of available instruments.
 * @details This view is managed by its respective controller, InstrumentController.
 */
class InstrumentSelectionDialog: public wxDialog{
	wxWindow* parent;
	IInstrumentViewListener* listener;

	wxPanel* panel;
	wxBoxSizer* panelSizer;
	wxListBox* instrumentList;
	wxButton* okButton;
	wxBoxSizer* mainSizer;

public:	
	/**
	 * InstrumentSelectionDialog Constructor.
	 * 
	 * @param parent The window that generated this dialog. This could be a nullptr.
	 * @param controller The controller that manages this view.
	 */
	InstrumentSelectionDialog(wxWindow* parent, IInstrumentViewListener* controller);

	/**
	 * @brief Display the selection instrument dialog.
	 * 
	 * It clears the instrument list and populates it with the available instruments before showing the dialog.
	 * 
	 */
	void ShowSelectionDialog();

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
