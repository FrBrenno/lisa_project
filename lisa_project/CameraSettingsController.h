#pragma once
#include "BaseController.h"
#include "CameraConfig.h"

class CameraSettingsController : public BaseController 
{
	CameraConfig* camSettings;
	int err;
public:
	CameraSettingsController(bool is_wfs_connected);
};
