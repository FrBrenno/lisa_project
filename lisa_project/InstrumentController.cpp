#include "InstrumentController.h"


InstrumentController::InstrumentController(wxApp* main): BaseController(main)
{
	this->selectedInstrument = new Instrument();
	this->reviseDrive(this->selectedInstrument);
	return;
}

void InstrumentController::PopulateInstrumentList(wxListBox* list)
{
	// Clear list
	list->Clear();

	// Variable Initialization
	ViInt32 instrumentCount, device_id;
	ViInt32 err, in_use;
	ViChar instr_name[WFS_BUFFER_SIZE];
	ViChar serNr[WFS_BUFFER_SIZE];
	ViChar resourceName[WFS_BUFFER_SIZE];

	// Get instrument count
	if (err = WFS_GetInstrumentListLen(VI_NULL, &instrumentCount))
	{
		this->handleError(err, "Not able to get the count of instruments connected");
	}

	if (instrumentCount == 0) 
	{
		// No instrument found
		wxMessageBox("No instrument found.", "INFO", wxOK | wxICON_INFORMATION);
	}
	else
	{
		for (int i = 0; i < instrumentCount; i++)
		{
			if (err = WFS_GetInstrumentListInfo(VI_NULL, i, &device_id, &in_use, instr_name, serNr, resourceName))
			{
				this->handleError(err, "Not able to get instrument's information");
			 }
			list->Append(wxString::Format("%4d %s %s %s\n", device_id, instr_name, serNr, (!in_use)? "" : "(inUse)"));
		}
	}
}

void InstrumentController::OnInstrumentSelected(int selectedIndex)
{
	// Confirm selection
	wxMessageBox("OnInstrumentSelected");

}

void InstrumentController::OnClose() {
	// Close dialog
	wxMessageBox("OnClose");

}

void InstrumentController::reviseDrive(Instrument* instrument) {
	ViChar version_wfs_driver[256];
	ViChar version_cam_driver[256];
	int err;

	if (err = WFS_revision_query(NULL, version_wfs_driver, version_cam_driver)) {
		printf("%d\n", err);
		wxMessageBox(wxString::Format("Error %d: %s", err, (err)), "Error", wxOK | wxICON_ERROR);
		return;
	}

	wxMessageBox(
		wxString::Format("WFS Driver Version: %s\nCam Driver Version: %s", version_wfs_driver, version_cam_driver),
		"Driver Revision", wxOK | wxICON_INFORMATION
	);

	instrument->setWfsDriverVersion(static_cast<std::string> (version_wfs_driver));
	instrument->setCamDriverVersion(static_cast<std::string> (version_cam_driver));
}


void InstrumentController::handleError(int code, std::string message)
{
	char description[WFS_ERR_DESCR_BUFFER_SIZE];

	if (!code) return;

	// Get error string
	WFS_error_message(VI_NULL, code, description);

	wxMessageBox(wxString::Format("%s:\n =>\t %s", message, description), "Error", wxOK | wxICON_ERROR);
}
