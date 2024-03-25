#pragma once

class ICalibrationViewListener {
public:
	virtual void OnCalibrate() = 0;
	virtual void OnClose() = 0;
};
