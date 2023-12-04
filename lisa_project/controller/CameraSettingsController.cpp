#include "CameraSettingsController.h"
#include "../EventDispatcher.h"
#include "../view/CameraSettingsDialog.h"
#include "WFS.h"

CameraSettingsController::CameraSettingsController(MyAppInterface* main, bool is_wfs_connected) :  BaseController(main, is_wfs_connected)
{
	this->cameraConfig = new CameraConfig();
	this->cameraConfig->setDefault();
}

//=== Event Handlers ===//

void CameraSettingsController::handleSettingsSelection(const Event& event)
{
	/*
	if(!is_wfs_connected){
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
	*/
	CameraSettingsDialog* cameraSettingsDialog = new CameraSettingsDialog(nullptr, this);
	cameraSettingsDialog->loadCameraSettings(cameraConfig);
	cameraSettingsDialog->ShowModal();

	return;
}

void CameraSettingsController::onSetDefault()
{
	// Set default camera settings
	cameraConfig->setDefault();
	return;
}

void CameraSettingsController::onOK(CameraConfig* newCamConfig)
{
	// Set new camera settings
	delete cameraConfig;
	cameraConfig = newCamConfig;
	return;
}

void CameraSettingsController::onClose()
{
	return;
}
//=== WFS API Functions ===//

//=== Getters ===//

CameraConfig* CameraSettingsController::getCameraConfig()
{
	return cameraConfig;
}

