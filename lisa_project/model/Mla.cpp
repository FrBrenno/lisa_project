#include "Mla.h"

Mla::Mla()
{
	this->mla_name = nullptr;
	this->is_initialized = false;
	this->cam_pitch_m = 0;
	this->lenslet_pitch_m = 0;
	this->center_spot_offset_x = 0;
	this->center_spot_offset_y = 0;
	this->lenslet_f_m = 0;
	this->grd_corr_0 = 0;
	this->grd_corr_45 = 0;
	this->handle = 0;
}

Mla::~Mla()
{
	delete[] this->mla_name;
}

void Mla::setHandle(ViSession handle)
{
	this->handle = handle;
}

void Mla::setMlaName(ViChar* mla_name)
{
	this->mla_name = mla_name;
}

void Mla::setCamPitchm(ViReal64 cam_pitch_um)
{
	this->cam_pitch_m = cam_pitch_um;
}

void Mla::setLensletPitchm(ViReal64 lenslet_pitch_um)
{
	this->lenslet_pitch_m = lenslet_pitch_um;
}

void Mla::setCenterSpotOffsetX(ViReal64 center_spot_offset_x)
{
	this->center_spot_offset_x = center_spot_offset_x;
}

void Mla::setCenterSpotOffsetY(ViReal64 center_spot_offset_y)
{
	this->center_spot_offset_y = center_spot_offset_y;
}

void Mla::setLensletFm(ViReal64 lenslet_f_um)
{
	this->lenslet_f_m = lenslet_f_um;
}

void Mla::setGrdCorr0(ViReal64 grd_corr_0)
{
	this->grd_corr_0 = grd_corr_0;
}

void Mla::setGrdCorr45(ViReal64 grd_corr_45)
{
	this->grd_corr_45 = grd_corr_45;
}

ViSession Mla::getHandle() const
{
	return this->handle;
}

ViChar* Mla::getMlaName() const
{
	return this->mla_name;
}

ViReal64 Mla::getCamPitchm() const
{
	return this->cam_pitch_m;
}

ViReal64 Mla::getLensletPitchm() const
{
	return this->lenslet_pitch_m;
}

ViReal64 Mla::getCenterSpotOffsetX() const
{
	return this->center_spot_offset_x;
}

ViReal64 Mla::getCenterSpotOffsetY() const
{
	return this->center_spot_offset_y;
}

ViReal64 Mla::getLensletFm() const
{
	return this->lenslet_f_m;
}

ViReal64 Mla::getGrdCorr0() const
{
	return this->grd_corr_0;
}

ViReal64 Mla::getGrdCorr45() const
{
	return this->grd_corr_45;
}


void Mla::setInitialized(bool is_initialized)
{
	this->is_initialized = is_initialized;
}

bool Mla::isInitialized() const
{
	return this->is_initialized;
}
