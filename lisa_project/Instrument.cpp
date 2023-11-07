#include "Instrument.h"

void Instrument::setDeviceId(int device_id) {
	this->device_id = device_id;
}



void Instrument::setWfsDriverVersion(std::string wfs_driver_version) {
	this->version_wfs_driver = wfs_driver_version;
}

void Instrument::setCamDriverVersion(std::string cam_driver_version) {
	this->version_cam_driver = cam_driver_version;
}


ViSession* Instrument::getHandle(){
	return &this->handle;
}

void Instrument::setInstrumentInfo(std::string manufacturer_name, std::string instrument_name, std::string serial_number_wfs, std::string serial_number_cam) {
	this->manufacturer_name = manufacturer_name;
	this->instrument_name = instrument_name;
	this->serial_number_wfs = serial_number_wfs;
	this->serial_number_cam = serial_number_cam;
}

void Instrument::setInitialized(bool is_initialized) {
	this->is_initialized = is_initialized;
}

void Instrument::setMla(Mla* mla) {
	this->mla = mla;
}

bool Instrument::isInitialized() {
	return this->is_initialized;
}

std::string Instrument::getInstrumentName(){
	return this->instrument_name;
}

int Instrument::getDeviceId(){
	return this->device_id;
}

ViInt32* Instrument::getSpotsX() {
	return &this->spots_x;
}

ViInt32* Instrument::getSpotsY() {
	return &this->spots_y;
}
