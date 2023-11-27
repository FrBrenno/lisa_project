#pragma once

#include "BaseController.h"
#include "../Event.h"

class CameraSettingsController : public BaseController
{
	void HandleSettingsSelection(const Event& event);

public:
	CameraSettingsController(MyAppInterface* main, bool is_wfs_connected);

	void onOK() override;
	void onClose() override;
};