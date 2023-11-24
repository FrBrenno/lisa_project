#include "CameraSettingsController.h"
#include "../EventDispatcher.h"
#include "../view/CameraSettingsDialog.h"

CameraSettingsController::CameraSettingsController(MyApp* app, bool is_wfs_connected) :  BaseController(app, is_wfs_connected)
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


