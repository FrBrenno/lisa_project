#include "InstrumentController.h"
#include "InstrumentSelectionDialog.h"
#include "InstrumentDto.h"
#include "EventDispatcher.h"
#include "InstrumentSelectedEvent.h"
#include "InstrumentSelectionEvent.h"
#include "ExitEvent.h"

InstrumentController::InstrumentController(MyAppInterface* main, IApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->err = VI_SUCCESS;
	this->instrument = new Instrument();
	this->mla = new Mla();

	EventDispatcher::Instance().SubscribeToEvent<InstrumentSelectionEvent>(
		[this](const InstrumentSelectionEvent& event) {
			HandleInstrumentSelection();
		});
	EventDispatcher::Instance().SubscribeToEvent<ExitEvent>(
		[this](const ExitEvent& event) {
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
	if (!this->wfsApiService->isApiConnectionActive()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
	// Launch InstrumentSelectionDialog view
	InstrumentSelectionDialog instrumentSelectionDialog(this->app->getHomeFrame(), this);
	instrumentSelectionDialog.ShowSelectionDialog();

	EventDispatcher::Instance().PublishEvent(
		InstrumentSelectedEvent(this->instrument)
	);
}

//=== WFS API Functions ===//

void InstrumentController::populateInstrumentList(wxListBox* list)
{
	if (!this->wfsApiService->isApiConnectionActive()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// New instrument list
	std::vector<InstrumentDto> instruments;
	ViStatus status = this->wfsApiService->getInstrumentsList(instruments);
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
		for (InstrumentDto instr : instruments)
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
	if (!this->wfsApiService->isApiConnectionActive()) {
		// API is not connected
		this->handleError(-1, "WFS is not connected");
		return;
	}

	InstrumentDto selectedInstrument;
	ViStatus status = this->wfsApiService->getInstrumentInfo(selectedInstrument, selectedIndex);

	// Get information of selected instrument
	if (status != VI_SUCCESS)
	{
		this->handleError(err, "Not able to get instrument's information");
	}
	else{
		// Initialize instrument
		this->initInstrument(selectedInstrument);
		this->selectMla();
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


void InstrumentController::initInstrument(InstrumentDto& instrumentDto)
{
	if (!this->wfsApiService->isApiConnectionActive()) {
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


void InstrumentController::cameraConfiguration()
{
	if (!this->wfsApiService->isApiConnectionActive()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	ViSession handle = this->instrument->getHandle();
	int deviceId = this->instrument->getDeviceId();
	ViInt32 spotsX, spotsY;

	ViStatus status = 0;
	if (status = this->wfsApiService->configureCamera(handle, deviceId, spotsX, spotsY))
	{
		if (status == -1) {
			// Other devices are not compatible with this software for now
			this->handleError(-1, "The device selected is not a WFS20. Others devices are not compatible.");
			return;
		}
		else
		{
			this->handleError(err, "Not able to configure camera");
			return;
		}
	}
	this->instrument->setSpotsX(spotsX);
	this->instrument->setSpotsY(spotsY);

	// WFS Internal Reference Plane Setup
	if (status = this->wfsApiService->setReferencePlane(handle))
	{
		this->handleError(err, "Not able to set reference plane");
		return;
	}

	// WFS Pupil Setup
	if (status = this->wfsApiService->setPupil(handle))
	{
		this->handleError(err, "Not able to set pupil");
		return;
	}
}


void InstrumentController::closeInstrument()
{
	if (!this->wfsApiService->isApiConnectionActive()) {
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

void InstrumentController::selectMla()
{
	if (!this->wfsApiService->isApiConnectionActive()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Get MLA information
	int defaultMlaIndex = 0;
	MlaDto mlaDto;
	ViStatus status = this->wfsApiService->getMlaInfo(this->getInstrumentHandle(), defaultMlaIndex, mlaDto);
	if (status != VI_SUCCESS)
	{
		this->handleError(err, "Not able to get MLA information");
		return;
	}

	// Set MLA information
	this->mla->setMlaName(mlaDto.getMlaName());
	this->mla->setCamPitchm(mlaDto.getCamPitchm());
	this->mla->setLensletPitchm(mlaDto.getLensletPitchm());
	this->mla->setCenterSpotOffsetX(mlaDto.getSpotOffsetX());
	this->mla->setCenterSpotOffsetY(mlaDto.getSpotOffsetY());
	this->mla->setLensletFm(mlaDto.getLensletFm());
	this->mla->setGrdCorr0(mlaDto.getGrdCorr0());
	this->mla->setGrdCorr45(mlaDto.getGrdCorr45());


	// Select MLA, set calibration files active
	status = this->wfsApiService->selectMla(this->getInstrumentHandle(), defaultMlaIndex);
	if (status != VI_SUCCESS)
	{
		this->handleError(err, "Not able to select MLA");
		return;
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