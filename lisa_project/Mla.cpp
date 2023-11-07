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

