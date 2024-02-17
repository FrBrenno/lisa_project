#include "InstrumentController.h"
#include "../EventDispatcher.h"
#include "../view/InstrumentSelectionDialog.h"
#include "../model/Settings.h"
#include <InstrumentDto.h>

InstrumentController::InstrumentController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->err = VI_SUCCESS;
	this->instrumentSelectionDialog = new InstrumentSelectionDialog(nullptr, this);
	this->instrument = new Instrument();

	EventDispatcher::Instance().SubscribeToEvent("InstrumentSelection",
		[this](const Event& event) {
			HandleInstrumentSelection(event);
		});
	EventDispatcher::Instance().SubscribeToEvent("Exit",
		[this](const Event& event) {
			onExit();
		});
}

InstrumentController::~InstrumentController()
{
	delete instrument;
}

//=== Event Handlers ===//

void InstrumentController::HandleInstrumentSelection(const Event& event)
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Launch InstrumentSelectionDialog view
	if (instrumentSelectionDialog != nullptr) {
		instrumentSelectionDialog->ShowModal();
		return;
	}

}

void InstrumentController::HandleMlaSelected(const Event& event)
{
	// REFACTOR IT
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Get the reference to the selected MLA and set it into instrument attributes
	Mla* selectedMla = (Mla*)event.getData();
	this->instrument->setMla(selectedMla);
}

void InstrumentController::mlaConfiguration() {
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Publish MlaSelectionEvent in order to allow the user to select an MLA
	// Normally, MlaController should handle this event.
	Event mlaSelectionEvent("MlaSelection", (void*) this->instrument->getHandle());

	EventDispatcher::Instance().PublishEvent(mlaSelectionEvent);
	return;
}

//=== WFS API Functions ===//

void InstrumentController::populateInstrumentList(wxListBox* list)
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Clear list
	list->Clear();

	// New instrument list
	std::vector<InstrumentDto> instruments;
	this->wfsApiService->getInstrumentsList(&instruments);
	int instrumentCount = instruments.size();

	if (instrumentCount == 0)
	{
		// No instrument found
		wxMessageBox("No instrument found.", "PCV - INFO", wxOK | wxICON_INFORMATION);
		return;
	}
	else
	{
		for (const auto& instr: instruments)
		{
			list->Append(wxString::Format("%4d %s %s %s\n", 
				instr.getDeviceId(),
				instr.getInstrName(),
				instr.getSerNr(),
				(!instr.getInUse()) ? "" : "(in use)"));
		}
	}
}

void InstrumentController::onInstrumentSelected(int selectedIndex)
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
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
		this->instrument->setDeviceId(device_id);

		// Initialize instrument
		this->initInstrument(resourceName);
		// MLA Selection
		//this->mlaConfiguration();
		// Camera Configuration
		this->cameraConfiguration();
	}

}

void InstrumentController::onClose(){
	// If instrument is initialized, just close it
	if (this->instrument->isInitialized()) 
	{
		return;
	}

	// No instrument is selected
	wxMessageBox("No instrument is selected.\nTo select a instrument, go to FILE -> \"Select Instrument\"", "INFO", wxOK | wxICON_INFORMATION);
}


void InstrumentController::initInstrument(ViRsrc resourceName) 
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Variable initialization
	ViSession* handle = this->instrument->getHandle();
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
			this->instrument->setInstrumentInfo(static_cast<std::string> (manufacturer_name),
				static_cast<std::string> (instrument_name),
				static_cast<std::string> (serial_number_wfs),
				static_cast<std::string> (serial_number_cam)
			);
		}
	}
	this->instrument->setInitialized(true);
}


void InstrumentController::cameraConfiguration()
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	ViSession handle = *this->instrument->getHandle();
	int device_id = this->instrument->getDeviceId();

	// If device is a WFS20
	if (device_id & DEVICE_OFFSET_WFS20) {
		ViInt32* spotsX = this->instrument->getSpotsX();
		ViInt32* spotsY = this->instrument->getSpotsY();
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
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	if (err = WFS_close(*this->instrument->getHandle())) {
		delete this->instrument;
		this->handleError(err, "Not able to close instrument");
		return;
	}
	else {
		this->instrument->setInitialized(false);
	}
}

void InstrumentController::onExit()
{
		// If instrument is initialized, just close it
	if (this->instrument->isInitialized())
	{
		this->closeInstrument();
		return;
	}
	return;
}

//=== Utility Functions ===//

std::string InstrumentController::getInstrumentName() {
	return this->instrument->getInstrumentName();
}

Instrument* InstrumentController::getInstrument() {
	return this->instrument;
}


