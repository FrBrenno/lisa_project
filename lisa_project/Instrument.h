#pragma once

#include <string>
#include "Message.h"
#include "WFS.h"

class Instrument{
	// Instrument Parameters
	int selected_id;
	int handle;
	int status;

	// WFS Parameters
	std::string version_wfs_driver;
	std::string version_cam_driver;
	std::string manufacturer_name;
	std::string instrument_name;
	std::string serial_number_wfs;
	std::string serial_number_cam;	

	// MLA Parameters
	int mla_count;
	int mla_selected;
	int selected_mla_idx;
	std::string mla_name;
	double cam_pitch_um;
	double lenslet_pitch_um;
	double center_spot_offset_x;
	double center_spot_offset_y;
	double lenslet_f_um;
	double grd_corr_0;
	double grd_corr_45;

	// Camera Parameters
	int spots_x;
	int spots_y;

public:
	Instrument();
	~Instrument();

};
