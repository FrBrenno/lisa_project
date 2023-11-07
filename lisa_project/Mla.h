#include <string>
#include "WFS.h"

class Mla{
	ViSession handle;

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
	ViInt32* getMlaCount();
	ViSession getHandle();

	void setHandle(ViSession handle);
};
