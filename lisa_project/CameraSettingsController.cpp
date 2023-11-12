#include "CameraSettingsController.h"

CameraSettingsController::CameraSettingsController(bool is_wfs_connected): BaseController(is_wfs_connected)
{
	camSettings = new CameraConfig();
	err = 0;
}
