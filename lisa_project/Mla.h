#ifndef MLA_H
#define MLA_H

#include <string>
#include "WFS.h"

/**
 * @class Mla.
 * @brief This model class is used to store the information of the MLA.
 */
class Mla{
	ViSession handle;
	bool is_initialized;

	ViInt32 mla_count;
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
public:
	Mla();

	ViInt32* getMlaCount();
	ViSession getHandle();
	bool isInitialized();

	void setInitialized(bool is_initialized);
	void setHandle(ViSession handle);
	void setMlaInfo(ViChar* mla_name, ViReal64 cam_pitchm, ViReal64 lenslet_pitchm, ViReal64 spot_offset_x, ViReal64 spot_offset_y, ViReal64 lenslet_fm, ViReal64 grd_corr_0, ViReal64 grd_corr_45);
};

#endif