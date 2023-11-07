#include "MlaController.h"
#include "MlaSelectionDialog.h"
#include "EventDispatcher.h"
#include "wx/wx.h"

MlaController::MlaController() {
	this->selectMla = new Mla();
	this->err = 0;
	
	EventDispatcher::Instance().SubscribeToEvent("MlaSelection",
		[this](const Event& event) {
			HandleMlaSelection(event);
		});
}

//=== Event Handler ===//
void MlaController::HandleMlaSelection(const Event& event) {
	this->selectMla->setHandle(*(ViSession*)event.data);
	MlaSelectionDialog* mlaSelectionDialog = new MlaSelectionDialog(nullptr, this);
	mlaSelectionDialog->ShowModal();
}

void MlaController::HandleMlaSelected(const Event& event) {
	Event mlaSelectedEvent;
	mlaSelectedEvent.name = "MlaSelected";
	mlaSelectedEvent.data = (void*)this->selectMla;

}

//=== WFS API Functions ===//
void MlaController::populateMlaList(wxListBox* list) {
	ViSession handle = this->selectMla->getHandle();
	ViInt32* mla_count = this->selectMla->getMlaCount();

	if (err = WFS_GetMlaCount(handle, mla_count)) {
		this->handleError(err, "Not able to get the count of MLAs");
	}

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

void MlaController::onMlaSelected(int selectedIndex) {
	ViStatus handle = this->selectMla->getHandle();
	if (err = WFS_SelectMla(handle, selectedIndex))
	{
		this->handleError(err, "Not able to select MLA");
	}

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
}


void MlaController::onClose() {
	if (this->selectMla->isInitialized()) {
		return;
	}
	wxMessageBox("No MLA selected", "PCV - Error", wxOK | wxICON_ERROR);

}

//=== Utility Function ===//
void MlaController::handleError(int code, std::string message)
{
	char description[WFS_ERR_DESCR_BUFFER_SIZE];

	if (!code) return;

	// Get error string
	if (code != -1)
	{
		WFS_error_message(VI_NULL, code, description);
	}
	else
	{
		strcpy(description, "");
	}
	wxMessageBox(wxString::Format("%s:\n =>\t %s", message, description), "PCV - Error", wxOK | wxICON_ERROR);

}
