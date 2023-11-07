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
}

void MlaController::onMlaSelected(int selectedIndex) {

}

void MlaController::OnOK() {

}

void MlaController::OnClose() {

}

//=== Utility Function ===//
void MlaController::handleError(int code, std::string message)
{
	char description[WFS_ERR_DESCR_BUFFER_SIZE];

	if (!code) return;

	// Get error string
	if (err != -1)
	{
		WFS_error_message(VI_NULL, code, description);
	}
	else
	{
		strcpy(description, "");
	}
	wxMessageBox(wxString::Format("%s:\n =>\t %s", message, description), "PCV - Error", wxOK | wxICON_ERROR);

}
