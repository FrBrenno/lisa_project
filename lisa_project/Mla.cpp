#include "Mla.h"

Mla::Mla() {
	mla_count = 0;
	mla_selected = 0;
	selected_mla_idx = 0;
	mla_name = "";
	cam_pitch_um = 0;
	lenslet_pitch_um = 0;
	center_spot_offset_x = 0;
	center_spot_offset_y = 0;
	lenslet_f_um = 0;
	grd_corr_0 = 0;
	grd_corr_45 = 0;
}

ViInt32* Mla::getMlaCount() {
	return &this->mla_count;
}

void Mla::setHandle(ViSession handle) {
	this->handle = handle;
}

ViSession Mla::getHandle() {
	return this->handle;
}

void Mla::setMlaInfo(ViChar* mla_name, ViReal64 cam_pitchm, ViReal64 lenslet_pitchm, ViReal64 spot_offset_x, ViReal64 spot_offset_y, ViReal64 lenslet_fm, ViReal64 grd_corr_0, ViReal64 grd_corr_45) {
	this->mla_name = mla_name;
	this->cam_pitch_um = cam_pitchm;
	this->lenslet_pitch_um = lenslet_pitchm;
	this->center_spot_offset_x = spot_offset_x;
	this->center_spot_offset_y = spot_offset_y;
	this->lenslet_f_um = lenslet_fm;
	this->grd_corr_0 = grd_corr_0;
	this->grd_corr_45 = grd_corr_45;
}

bool Mla::isInitialized() {
	return this->is_initialized;
}

void Mla::setInitialized(bool is_initialized) {
	this->is_initialized = is_initialized;
}
