#include "MlaDto.h"
#include <string.h>

MlaDto::MlaDto()
{
}

MlaDto::~MlaDto()
{
}

ViChar* MlaDto::getMlaName() const
{
	return this->mlaName;
}

ViReal64 MlaDto::getCamPitchm() const
{
	return this->CamPitchm;
}

ViReal64 MlaDto::getLensletPitchm() const
{
	return this->lensletPitch;
}

ViReal64 MlaDto::getSpotOffsetX() const
{
	return this->spotOffsetX;
}

ViReal64 MlaDto::getSpotOffsetY() const
{
	return this->spotOffsetY;
}

ViReal64 MlaDto::getLensletFm() const
{
	return this->lensletFm;
}

ViReal64 MlaDto::getGrdCorr0() const
{
	return this->grdCorr0;
}

	
ViReal64 MlaDto::getGrdCorr45() const
{
	return this->grdCorr45;
}

void MlaDto::setMlaName(ViChar* mlaName)
{
	this->mlaName = mlaName;
}

void MlaDto::setCamPitchm(ViReal64 CamPitchm)
{
	this->CamPitchm = CamPitchm;
}

void MlaDto::setLensletPitchm(ViReal64 lensletpitch)
{
	this->lensletPitch = lensletpitch;
}

void MlaDto::setSpotOffsetX(ViReal64 spotOffsetX)
{
	this->spotOffsetX = spotOffsetX;
}

void MlaDto::setSpotOffsetY(ViReal64 spotOffsetY)
{
	this->spotOffsetY = spotOffsetY;
}

void MlaDto::setLensletFm(ViReal64 lensletFm)
{
	this->lensletFm = lensletFm;
}

void MlaDto::setGrdCorr0(ViReal64 grdCorr0)
{
	this->grdCorr0 = grdCorr0;
}

void MlaDto::setGrdCorr45(ViReal64 grdCorr45)
{
	this->grdCorr45 = grdCorr45;
}
