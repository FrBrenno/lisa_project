#include "HomeFrameController.h"
#include "../view/InstrumentSelectionDialog.h"
#include "../EventDispatcher.h"

HomeFrameController::HomeFrameController(bool is_wfs_connected) : BaseController(is_wfs_connected)
{
	if (!is_wfs_connected) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
}

void HomeFrameController::onInstrumentSelection(wxWindow* parent) 
{
	Event instrumentSelectionEvent("InstrumentSelection");

	EventDispatcher::Instance().PublishEvent(instrumentSelectionEvent);
}

void HomeFrameController::onConnectAPI(wxWindow* parent)
{
	// TODO
}

void HomeFrameController::onCameraSettings(wxWindow* parent)
{
	Event cameraSettingsSelectionEvent("CameraSettingsSelection");

	EventDispatcher::Instance().PublishEvent(cameraSettingsSelectionEvent);
}

void HomeFrameController::onCapture(wxWindow* parent, wxBitmap lastBitmap)
{
	wxFileDialog saveFileDialog(parent, "Save Image", "", "", "PNG files (*.png)|*.png|All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		// User canceled the operation
		return;
	}

	wxString filePath = saveFileDialog.GetPath();

	// Ensure a valid file path
	if (filePath.empty()) {
		wxMessageBox("Invalid file path.", "Error", wxOK | wxICON_ERROR);
		return;
	}

	// Save the image
	lastBitmap.SaveFile(filePath, wxBITMAP_TYPE_PNG);
}
