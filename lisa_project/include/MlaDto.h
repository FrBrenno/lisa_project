#pragma once
#include "thorlabs_api/visatype.h"

class MlaDto
{
	ViChar* mlaName;
	ViReal64 CamPitchm;
	ViReal64 lensletPitch;
	ViReal64 spotOffsetX;
	ViReal64 spotOffsetY;
	ViReal64 lensletFm;
	ViReal64 grdCorr0;
	ViReal64 grdCorr45;
public:
	MlaDto();
	~MlaDto();

	ViChar* getMlaName() const;
	ViReal64 getCamPitchm() const;
	ViReal64 getLensletPitchm() const;
	ViReal64 getSpotOffsetX() const;
	ViReal64 getSpotOffsetY() const;
	ViReal64 getLensletFm() const;
	ViReal64 getGrdCorr0() const;
	ViReal64 getGrdCorr45() const;

	void setMlaName(ViChar* mlaName);
	void setCamPitchm(ViReal64 CamPitchm);
	void setLensletPitchm(ViReal64 lensletpitch);
	void setSpotOffsetX(ViReal64 spotOffsetX);
	void setSpotOffsetY(ViReal64 spotOffsetY);
	void setLensletFm(ViReal64 lensletFm);
	void setGrdCorr0(ViReal64 grdCorr0);
	void setGrdCorr45(ViReal64 grdCorr45);
};

