#include "Instrument.h"

Instrument::Instrument()
{}

Instrument::~Instrument()
{}

void Instrument::setMla(Mla* mla)
{
	this->mla = mla;
}

void Instrument::setDeviceId(int device_id)
{
	this->device_id = device_id;
}

void Instrument::setHandle(ViSession handle)
{
	this->handle = handle;
}

void Instrument::setWfsDriverVersion(ViChar* wfs_driver_version)
{
	strcpy(this->version_wfs_driver, wfs_driver_version);
}

void Instrument::setCamDriverVersion(ViChar* cam_driver_version)
{
	strcpy(this->version_cam_driver, cam_driver_version);
}

void Instrument::setManufacturerName(ViChar* manufacturer_name)
{
	strcpy(this->manufacturer_name, manufacturer_name);
}

void Instrument::setInstrumentName(ViChar* instrument_name)
{
	strcpy(this->instrument_name, instrument_name);
}

void Instrument::setSerialNumberWfs(ViChar* serial_number_wfs)
{
	strcpy(this->serial_number_wfs, serial_number_wfs);
}

void Instrument::setSerialNumberCam(ViChar* serial_number_cam)
{
	strcpy(this->serial_number_cam, serial_number_cam);
}

void Instrument::setInitialized(bool is_initialized)
{
	this->is_initialized = is_initialized;
}

void Instrument::setStatus(ViInt32 status)
{
	this->status = status;
}

ViSession* Instrument::getHandle()
{
	return &this->handle;
}

bool Instrument::isInitialized()
{
	return this->is_initialized;
}

std::string Instrument::getInstrumentName()
{
	return this->instrument_name;
}

int Instrument::getDeviceId()
{
	return this->device_id;
}

ViInt32* Instrument::getSpotsX()
{
	return &this->spots_x;
}

ViInt32* Instrument::getSpotsY()
{
	return &this->spots_y;
}



