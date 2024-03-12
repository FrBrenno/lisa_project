#include "MlaController.h"
#include "../EventDispatcher.h"
#include "../view/MlaSelectionDialog.h"
#include "wx/wx.h"
#include "../model/Dto/MlaDto.h"
#include "MlaSelectionEvent.h"

MlaController::MlaController(MyAppInterface* main, IApiService* wfsApiService) : BaseController(main, wfsApiService) {
	this->mla = new Mla();
	this->err = 0;
	
	// This class should be aware whenever the user wants to select an MLA.
	EventDispatcher::Instance().SubscribeToEvent<MlaSelectionEvent>(
		[this](const MlaSelectionEvent& event) {
			HandleMlaSelection();
		});
}

MlaController::~MlaController() {
	delete this->mla;
}

//=== Event Handler ===//

void MlaController::HandleMlaSelection() 
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	MlaSelectionDialog dialog(nullptr, this);
	dialog.ShowModal();
}

//=== WFS API Functions ===//

void MlaController::populateMlaList(wxListBox* list) 
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	ViSession handle = this->app->getInstrumentHandle();
	std::vector<MlaDto> mlas;
	ViStatus status = this->wfsApiService->getMlaList(handle, &mlas);

	if (status != VI_SUCCESS) {
		this->handleError(status, "Not able to get MLA list");
		return;
	}

	int mlaCount = mlas.size();
	if (mlaCount == 0) {
		// If there is no MLA, then show error message
		wxMessageBox("No MLA found", "PCV - Error", wxOK | wxICON_ERROR);
		return;
	}
	else {
		int i = 0;
		for (const auto& mla : mlas) {
			list->Append(wxString::Format("%2d %s CamPitchm=%6.3f LensletPitch=%8.3f", 
				i, 
				mla.getMlaName(),
				mla.getCamPitchm(),
				mla.getLensletPitchm()));
			++i;
		}
	}
	
}

void MlaController::onMlaSelected(int selectedIndex) 
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	} 

	ViSession handle = this->app->getInstrumentHandle();
	ViStatus status = this->wfsApiService->getMlaInfo(handle, selectedIndex, this->mla);
	if (status != VI_SUCCESS) {
		this->handleError(status, "Not able to get MLA info");
		return;
	}
	this->mla->setInitialized(true);
}


void MlaController::onClose() {
	// When the user closes the view, check if the MLA is selected.
	// Users should be able to close the view without selecting an MLA.
	if (this->mla->isInitialized()) {
		return;
	}
	wxMessageBox("No MLA selected", "PCV - Error", wxOK | wxICON_ERROR);

}

//=== Utility Function ===//


