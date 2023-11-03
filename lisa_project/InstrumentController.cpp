#include "InstrumentController.h"
#include "EventDispatcher.h"
#include "InstrumentSelectionDialog.h"

InstrumentController::InstrumentController()
{
	EventDispatcher::Instance().SubscribeToEvent("InstrumentSelection",
		[this](const Event& event) {
			HandleInstrumentSelection(event);
		});

	this->err = VI_SUCCESS;
	this->instrumentCount = 0;
	this->selectedInstrument = new Instrument();

}

//=== Event Handlers ===//

void InstrumentController::HandleInstrumentSelection(const Event& event)
{
	InstrumentSelectionDialog* instrumentSelectionDialog = new InstrumentSelectionDialog(nullptr, this);
	instrumentSelectionDialog->ShowModal();
}

//=== WFS API Functions ===//

void InstrumentController::populateInstrumentList(wxListBox* list)
{
	// Clear list
	list->Clear();

	// Variable Initialization
	ViInt32 device_id;
	ViInt32 in_use;
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
			list->Append(wxString::Format("%4d %s %s %s\n", device_id, instr_name, serNr, (!in_use) ? "" : "(inUse)"));
		}
	}
}

void InstrumentController::onInstrumentSelected(int selectedIndex)
{
	ViInt32 device_id;
	ViChar resourceName[WFS_BUFFER_SIZE];

	// Get information of selected instrument
	if (err = WFS_GetInstrumentListInfo(VI_NULL, selectedIndex, &device_id, VI_NULL, VI_NULL, VI_NULL, resourceName))
	{
		this->handleError(err, "Not able to get instrument's information");
	}
	else{
		this->selectedInstrument->setDeviceId(device_id);

		// Initialize instrument
		this->initInstrument(resourceName);
		// Driver Revision
		this->reviseDrive(this->selectedInstrument);
	}
}

void InstrumentController::onClose() {
	// If instrument is initialized, just close it
	if (this->selectedInstrument->isInitialized()) 
	{
		return;
	}

	// No instrument is selected
	wxMessageBox("No instrument is selected.\nTo select a instrument, go to FILE -> \"Select Instrument\"", "INFO", wxOK | wxICON_INFORMATION);
}

void InstrumentController::reviseDrive(Instrument* instrument) {
	ViChar version_wfs_driver[256];
	ViChar version_cam_driver[256];

	if (err = WFS_revision_query(NULL, version_wfs_driver, version_cam_driver)) {
		printf("%d\n", err);
		wxMessageBox(wxString::Format("Error %d: %s", err, (err)), "Error", wxOK | wxICON_ERROR);
		return;
	}
	else {
		wxMessageBox(
			wxString::Format("WFS Driver Version: %s\nCam Driver Version: %s", version_wfs_driver, version_cam_driver),
			"Driver Revision", wxOK | wxICON_INFORMATION
		);

		instrument->setWfsDriverVersion(static_cast<std::string> (version_wfs_driver));
		instrument->setCamDriverVersion(static_cast<std::string> (version_cam_driver));
	}
}

void InstrumentController::initInstrument(ViRsrc resourceName) 
{
	ViSession* handle = this->selectedInstrument->getHandle();
	ViChar manufacturer_name[WFS_BUFFER_SIZE], instrument_name[WFS_BUFFER_SIZE],
		serial_number_wfs[WFS_BUFFER_SIZE], serial_number_cam[WFS_BUFFER_SIZE];

	if (err = WFS_init(resourceName, VI_FALSE, VI_FALSE, handle))
	{
		this->handleError(err, "Not able to initialize instrument");
	}
	else{
		if (err = WFS_GetInstrumentInfo(*handle, manufacturer_name, instrument_name, serial_number_wfs, serial_number_cam))
		{
			this->handleError(err, "Not able to get instrument's information");
		}
		else {
			this->selectedInstrument->setInstrumentInfo(static_cast<std::string> (manufacturer_name),
				static_cast<std::string> (instrument_name),
				static_cast<std::string> (serial_number_wfs),
				static_cast<std::string> (serial_number_cam)
			);
		}
	}
	this->selectedInstrument->setInitialized(true);

}

//=== Utility Functions ===//
std::string InstrumentController::getInstrumentName() {
	return this->selectedInstrument->getInstrumentName();
}

void InstrumentController::handleError(int code, std::string message)
{
	char description[WFS_ERR_DESCR_BUFFER_SIZE];

	if (!code) return;

	// Get error string
	WFS_error_message(VI_NULL, code, description);

	wxMessageBox(wxString::Format("%s:\n =>\t %s", message, description), "Error", wxOK | wxICON_ERROR);
}

