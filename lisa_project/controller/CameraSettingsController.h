#pragma once

#include "BaseController.h"
#include "../Event.h"
#include "../model/CameraConfig.h"

class CameraSettingsController : public BaseController
{
	CameraConfig* cameraConfig;
	void HandleSettingsSelection(const Event& event);

public:
	CameraSettingsController(MyAppInterface* main, bool is_wfs_connected, CameraConfig* cameraConfig);

	void onSetDefault();
	void onOK(CameraConfig* newCamConfig);
	void onClose() override;
};
