#include "MlaController.h"
#include "../view/MlaSelectionDialog.h"
#include "../EventDispatcher.h"
#include "wx/wx.h"

MlaController::MlaController(MyApp* app, bool is_wfs_connected) : BaseController(app, is_wfs_connected) {
	this->selectMla = new Mla();
	this->err = 0;
	
	// This class should be aware whenever the user wants to select an MLA.
	EventDispatcher::Instance().SubscribeToEvent("MlaSelection",
		[this](const Event& event) {
			HandleMlaSelection(event);
		});
}

//=== Event Handler ===//

void MlaController::HandleMlaSelection(const Event& event) 
{
	isApiConnected();

	// Generate the view and handle Mla Selection
	this->selectMla->setHandle(*(ViSession*)event.data);
	MlaSelectionDialog* mlaSelectionDialog = new MlaSelectionDialog(nullptr, this);
	mlaSelectionDialog->ShowModal();
}

void MlaController::HandleMlaSelected() {
	// Publish the selected MLA to whatever controller that needs it.
	Event mlaSelectedEvent;
	mlaSelectedEvent.name = "MlaSelected";
	mlaSelectedEvent.data = (void*)this->selectMla;

	EventDispatcher::Instance().PublishEvent(mlaSelectedEvent);
}

//=== WFS API Functions ===//

void MlaController::populateMlaList(wxListBox* list) 
{
	isApiConnected();

	ViSession handle = this->selectMla->getHandle();
	ViInt32* mla_count = this->selectMla->getMlaCount();

	// Get the number of MLAs
	if (err = WFS_GetMlaCount(handle, mla_count)) {
		this->handleError(err, "Not able to get the count of MLAs");
	}

	// If there is no MLA, then show error message
	if (*mla_count == 0) {
		wxMessageBox("No MLA found", "PCV - Error", wxOK | wxICON_ERROR);
		return;
	}
	else {
		ViChar mla_name[WFS_BUFFER_SIZE];
		ViReal64 cam_pitchm, lenslet_pitchm;

		for (int i = 0; i < *mla_count; i++) {
			if (err = WFS_GetMlaData(handle,
				i,
				mla_name,
				&cam_pitchm,
				&lenslet_pitchm,
				VI_NULL,
				VI_NULL,
				VI_NULL,
				VI_NULL,
				VI_NULL))
			{
				this->handleError(err, "Not able to get MLA data");
				return;
			}
			list->Append(wxString::Format("%2d %s CamPitch=%6.3f LensletPitch=%8.3f", i, mla_name, cam_pitchm, lenslet_pitchm));
		}
	}
}

void MlaController::onMlaSelected(int selectedIndex) 
{
	isApiConnected();

	// Setup the selected MLA
	ViStatus handle = this->selectMla->getHandle();
	if (err = WFS_SelectMla(handle, selectedIndex))
	{
		this->handleError(err, "Not able to select MLA");
	}
	
	// Get MLA data
	ViChar mla_name[WFS_BUFFER_SIZE];
	ViReal64 cam_pitchm, lenslet_pitchm, spot_offset_x,
		spot_offset_y, lenslet_fm, grd_corr_0, grd_corr_45;
	if (err = WFS_GetMlaData(handle,
		selectedIndex,
		mla_name,
		&cam_pitchm,
		&lenslet_pitchm,
		&spot_offset_x,
		&spot_offset_y,
		&lenslet_fm,
		&grd_corr_0,
		&grd_corr_45))
	{
		this->handleError(err, "Not able to get MLA data");
	}

	this->selectMla->setMlaInfo(
		mla_name,
		cam_pitchm,
		lenslet_pitchm,
		spot_offset_x,
		spot_offset_y,
		lenslet_fm,
		grd_corr_0,
		grd_corr_45
	);

	HandleMlaSelected();
}


void MlaController::onClose() {
	// When the user closes the view, check if the MLA is selected.
	// Users should be able to close the view without selecting an MLA.
	if (this->selectMla->isInitialized()) {
		return;
	}
	wxMessageBox("No MLA selected", "PCV - Error", wxOK | wxICON_ERROR);

}

//=== Utility Function ===//


