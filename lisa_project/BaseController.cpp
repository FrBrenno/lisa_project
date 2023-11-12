#include "BaseController.h"
#include "WFS.h"

BaseController::BaseController(bool is_wfs_connected) {
	this->is_wfs_connected = is_wfs_connected;
}

void BaseController::handleError(int code, std::string message){
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
	wxMessageBox(wxString::Format("%s\n\t%s", message, description), "PCV - Error", wxOK | wxICON_ERROR);
}
