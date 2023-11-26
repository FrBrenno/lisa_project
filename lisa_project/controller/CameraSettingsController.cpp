#include "CameraSettingsController.h"
#include "../EventDispatcher.h"
#include "../view/CameraSettingsDialog.h"

CameraSettingsController::CameraSettingsController(bool is_wfs_connected) :  BaseController(is_wfs_connected)
{
	EventDispatcher::Instance().SubscribeToEvent("CameraSettingsSelection",
		[this](const Event& event) {
			HandleSettingsSelection(event);
		});
}

//=== Event Handlers ===//

void CameraSettingsController::HandleSettingsSelection(const Event& event)
{
	/*
	if(!is_wfs_connected){
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
	*/
	CameraSettingsDialog* cameraSettingsDialog = new CameraSettingsDialog(nullptr, this);
	cameraSettingsDialog->ShowModal();

	return;
}

void CameraSettingsController::onOK()
{
	return;
}


//=== WFS API Functions ===//


