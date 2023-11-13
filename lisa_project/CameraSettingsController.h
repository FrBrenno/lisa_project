#pragma once

#include "BaseController.h"
#include "Event.h"

class CameraSettingsController : public BaseController
{
	void HandleSettingsSelection(const Event& event);

public:
	CameraSettingsController(bool is_wfs_connected);

	void onOK();
	void onClose() override;
};
