#include "InstrumentController.h"
#include "../EventDispatcher.h"
#include "../view/InstrumentSelectionDialog.h"
#include "../model/Dto/InstrumentDto.h"

InstrumentController::InstrumentController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->err = VI_SUCCESS;
	this->instrument = new Instrument();

	EventDispatcher::Instance().SubscribeToEvent("InstrumentSelection",
		[this](const Event& event) {
			HandleInstrumentSelection();
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

void InstrumentController::HandleInstrumentSelection()
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
	// Launch InstrumentSelectionDialog view
	InstrumentSelectionDialog dialog(nullptr, this);
	dialog.ShowModal();
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
	ViStatus status = this->wfsApiService->getInstrumentsList(&instruments);
	if (status != VI_SUCCESS)
	{
		this->handleError(err, "Not able to get instruments list");
		return;
	}

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
		// API is not connected
		this->handleError(-1, "WFS is not connected");
		return;
	}

	InstrumentDto selectedInstrument;
	ViStatus status = this->wfsApiService->getInstrumentInfo(&selectedInstrument, selectedIndex);

	// Get information of selected instrument
	if (status != VI_SUCCESS)
	{
		this->handleError(err, "Not able to get instrument's information");
	}
	else{
		// Initialize instrument
		this->initInstrument(selectedInstrument);
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


void InstrumentController::initInstrument(InstrumentDto instrumentDto)
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Variable initialization
	Instrument* newInstrument = new Instrument();
	ViStatus status = this->wfsApiService->initInstrument(instrumentDto, newInstrument);

	if (status != VI_SUCCESS)
	{
		this->handleError(status, "Not able to initialize instrument");
		delete newInstrument;  // Delete the instrument in case of failure
		return;
	}
	else {
		// If instrument is already initialized, just update it
		delete this->instrument;
		this->instrument = newInstrument;
	}
}

/**  
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
*/

void InstrumentController::closeInstrument()
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	if (!this->instrument->isInitialized()) {
		// Instrument is not initialized
		wxMessageBox("No instrument is initialized.", "INFO", wxOK | wxICON_INFORMATION);
		return;
	}

	ViStatus status = this->wfsApiService->closeInstrument(this->instrument->getHandle());

	if (status != VI_SUCCESS) {
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

const ViSession InstrumentController::getInstrumentHandle() {
	if (this->instrument != nullptr && this->instrument->isInitialized()) {
		return this->instrument->getHandle();
	}
	// Return a default value or handle not available indicator (e.g., VI_NULL)
	return VI_NULL;
}
