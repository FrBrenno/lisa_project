#ifndef MLA_H
#define MLA_H

#include "thorlabs_api/visatype.h"

/**
 * @class Mla.
 * @brief This model class is used to store the information of the MLA.
 */
class Mla{
	ViSession handle;
	bool is_initialized;

	ViChar* mla_name;
	ViReal64 cam_pitch_m;
	ViReal64 lenslet_pitch_m;
	ViReal64 center_spot_offset_x;
	ViReal64 center_spot_offset_y;
	ViReal64 lenslet_f_m;
	ViReal64 grd_corr_0;
	ViReal64 grd_corr_45;

public:
	Mla();
	~Mla();
	

	void setHandle(ViSession handle);
	void setMlaName(ViChar* mla_name);
	void setCamPitchm(ViReal64 cam_pitch_m);
	void setLensletPitchm(ViReal64 lenslet_pitch_m);
	void setCenterSpotOffsetX(ViReal64 center_spot_offset_x);
	void setCenterSpotOffsetY(ViReal64 center_spot_offset_y);
	void setLensletFm(ViReal64 lenslet_f_m);
	void setGrdCorr0(ViReal64 grd_corr_0);
	void setGrdCorr45(ViReal64 grd_corr_45);
	void setInitialized(bool is_initialized);

	ViSession getHandle() const;
	ViChar* getMlaName() const;
	ViReal64 getCamPitchm() const;
	ViReal64 getLensletPitchm() const;
	ViReal64 getCenterSpotOffsetX() const;
	ViReal64 getCenterSpotOffsetY() const;
	ViReal64 getLensletFm() const;
	ViReal64 getGrdCorr0() const;
	ViReal64 getGrdCorr45() const;
	bool isInitialized() const;
};

#endif