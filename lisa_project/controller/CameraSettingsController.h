#pragma once

#include "BaseController.h"
#include "../Event.h"
#include "../model/CameraConfig.h"

class CameraSettingsController : public BaseController
{
	CameraConfig* cameraConfig;

public:
	CameraSettingsController(MyAppInterface* main, WfsApiService* wfsApiService);

	void handleSettingsSelection(const Event& event);

	CameraConfig* getCameraConfig();
	void onSetDefault();
	void onOK(CameraConfig* newCamConfig);
	void onClose() override;
};
