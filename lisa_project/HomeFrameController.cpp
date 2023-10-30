#include "HomeFrameController.h"
#include "WFS.h"

HomeFrameController::HomeFrameController(wxApp* main) {
	this->main = main;
}

Instrument* HomeFrameController::selectInstrument() {
	Instrument* instrument = new Instrument();
	//this->reviseDrive(instrument);
	
	return instrument;
}

void HomeFrameController::reviseDrive(Instrument* instrument) {
	ViChar version_wfs_driver[256];
	ViChar version_cam_driver[256];
	int err;

	if (err = WFS_revision_query(NULL, version_wfs_driver, version_cam_driver)) {
		wxMessageBox(wxString::Format("Error %d: %s", err, (err)), "Error", wxOK | wxICON_ERROR);
		return;
	}

	wxMessageBox(
		wxString::Format("WFS Driver Version: %s\nCam Driver Version: %s", version_wfs_driver, version_cam_driver),
		"Revision", wxOK | wxICON_INFORMATION
	);
	
	instrument->setWfsDriverVersion(static_cast<std::string> (version_wfs_driver));
	instrument->setCamDriverVersion(static_cast<std::string> (version_cam_driver));
}
