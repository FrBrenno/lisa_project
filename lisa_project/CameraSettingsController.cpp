#include "CameraSettingsController.h"
#include "EventDispatcher.h"
#include "CameraSettingsDialog.h"

CameraSettingsController::CameraSettingsController(bool is_wfs_connected):  BaseController(is_wfs_connected)
{
	EventDispatcher::Instance().SubscribeToEvent("SettingsSelection",
		[this](const Event& event) {
			HandleSettingsSelection(event);
		});
}

//=== Event Handlers ===//

void CameraSettingsController::HandleSettingsSelection(const Event& event)
{
	/*
	if (!this->is_wfs_connected) {
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

void CameraSettingsController::onClose()
{
	return;
}

//=== WFS API Functions ===//


