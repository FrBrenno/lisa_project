#include "InstrumentController.h"
#include "../EventDispatcher.h"
#include "../view/InstrumentSelectionDialog.h"
#include "../model/Settings.h"

InstrumentController::InstrumentController(MyApp* app, bool is_wfs_connected) : BaseController(app, is_wfs_connected)
{
	this->err = VI_SUCCESS;
	this->instrumentCount = 0;
	this->selectedInstrument = new Instrument();

	EventDispatcher::Instance().SubscribeToEvent("InstrumentSelection",
		[this](const Event& event) {
			HandleInstrumentSelection(event);
		});
}

//=== Event Handlers ===//

void InstrumentController::HandleInstrumentSelection(const Event& event)
{
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}
	// Launch InstrumentSelectionDialog view
	InstrumentSelectionDialog* instrumentSelectionDialog = new InstrumentSelectionDialog(nullptr, this);
	instrumentSelectionDialog->ShowModal();
}

void InstrumentController::HandleMlaSelected(const Event& event)
{
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}
	// Get the reference to the selected MLA and set it into instrument attributes
	Mla* selectedMla = (Mla*)event.data;
	this->selectedInstrument->setMla(selectedMla);
}

void InstrumentController::mlaConfiguration() {
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}
	// Publish MlaSelectionEvent in order to allow the user to select an MLA
	// Normally, MlaController should handle this event.
	Event mlaSelectionEvent;
	mlaSelectionEvent.name = "MlaSelection";
	mlaSelectionEvent.data = (void*)this->selectedInstrument->getHandle();

	EventDispatcher::Instance().PublishEvent(mlaSelectionEvent);
	return;
}

//=== WFS API Functions ===//

void InstrumentController::populateInstrumentList(wxListBox* list)
{
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}

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
		wxMessageBox("No instrument found.", "PCV - INFO", wxOK | wxICON_INFORMATION);
		return;
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
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}

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
		// this->reviseDrive();
		// MLA Selection
		this->mlaConfiguration();
		// Camera Configuration
		this->cameraConfiguration();
	}

	// Publish InstrumentSelectedEvent

}

void InstrumentController::onClose(){
	// If instrument is initialized, just close it
	if (this->selectedInstrument->isInitialized()) 
	{
		return;
	}

	// No instrument is selected
	wxMessageBox("No instrument is selected.\nTo select a instrument, go to FILE -> \"Select Instrument\"", "INFO", wxOK | wxICON_INFORMATION);
}

void InstrumentController::reviseDrive() 
{
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}

	ViChar version_wfs_driver[256];
	ViChar version_cam_driver[256];

	if (err = WFS_revision_query(NULL, version_wfs_driver, version_cam_driver)) {
		this->handleError(err, "Not able to get driver revision");
		return;
	}
	else {
		wxMessageBox(
			wxString::Format("WFS Driver Version: %s\nCam Driver Version: %s", version_wfs_driver, version_cam_driver),
			"Driver Revision", wxOK | wxICON_INFORMATION
		);

		this->selectedInstrument->setWfsDriverVersion(static_cast<std::string> (version_wfs_driver));
		this->selectedInstrument->setCamDriverVersion(static_cast<std::string> (version_cam_driver));
	}
}

void InstrumentController::initInstrument(ViRsrc resourceName) 
{
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Variable initialization
	ViSession* handle = this->selectedInstrument->getHandle();
	ViChar manufacturer_name[WFS_BUFFER_SIZE], instrument_name[WFS_BUFFER_SIZE],
		serial_number_wfs[WFS_BUFFER_SIZE], serial_number_cam[WFS_BUFFER_SIZE];

	// API call to initiate a instrument session (handle)
	if (err = WFS_init(resourceName, VI_FALSE, VI_FALSE, handle))
	{
		this->handleError(err, "Not able to initialize instrument");
		return;
	}
	else{
		// Get instrument information
		if (err = WFS_GetInstrumentInfo(*handle, manufacturer_name, instrument_name, serial_number_wfs, serial_number_cam))
		{
			this->handleError(err, "Not able to get instrument's information");
			return;
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


void InstrumentController::cameraConfiguration()
{
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}

	ViSession handle = *this->selectedInstrument->getHandle();
	int device_id = this->selectedInstrument->getDeviceId();

	// If device is a WFS20
	if (device_id & DEVICE_OFFSET_WFS20) {
		ViInt32* spotsX = this->selectedInstrument->getSpotsX();
		ViInt32* spotsY = this->selectedInstrument->getSpotsY();
		if (err = WFS_ConfigureCam(handle,
			SAMPLE_PIXEL_FORMAT,
			SAMPLE_CAMERA_RESOL_WFS20,
			spotsX,
			spotsY))
		{
			this->handleError(err, "Not able to configure camera");
			return;
		}
	}
	else {
		// Other devices are not compatible with this software for now
		this->handleError(-1, "The device selected is not a WFS20. Others devices are not compatible.");
	}

	// WFS Internal Reference Plane Setup
	if (err = WFS_SetReferencePlane(handle, SAMPLE_REF_PLANE)) {
		this->handleError(err, "Not able to set reference plane");
		return;
	}
	// WFS Pupil Setup
	if (err = WFS_SetPupil(handle, SAMPLE_PUPIL_CENTROID_X, SAMPLE_PUPIL_CENTROID_Y, SAMPLE_PUPIL_DIAMETER_X, SAMPLE_PUPIL_DIAMETER_Y)) {
		this->handleError(err, "Not able to set pupil");
		return;
	}
}

void InstrumentController::closeInstrument()
{
	if (!this->is_wfs_connected) {
		// this->handleError(-1, "WFS is not connected");
		return;
	}

	if (err = WFS_close(*this->selectedInstrument->getHandle())) {
		this->handleError(err, "Not able to close instrument");
		return;
	}
	else {
		this->selectedInstrument->setInitialized(false);
	}
}


//=== Utility Functions ===//

std::string InstrumentController::getInstrumentName() {
	return this->selectedInstrument->getInstrumentName();
}

Instrument* InstrumentController::getInstrument() {
	return this->selectedInstrument;
}


