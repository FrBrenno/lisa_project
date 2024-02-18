#include "Instrument.h"

Instrument::Instrument()
{}

Instrument::~Instrument()
{}

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
	strcpy_s(this->version_wfs_driver, wfs_driver_version);
}

void Instrument::setCamDriverVersion(ViChar* cam_driver_version)
{
	strcpy_s(this->version_cam_driver, cam_driver_version);
}

void Instrument::setManufacturerName(ViChar* manufacturer_name)
{
	strcpy_s(this->manufacturer_name, manufacturer_name);
}

void Instrument::setInstrumentName(ViChar* instrument_name)
{
	strcpy_s(this->instrument_name, instrument_name);
}

void Instrument::setSerialNumberWfs(ViChar* serial_number_wfs)
{
	strcpy_s(this->serial_number_wfs, serial_number_wfs);
}

void Instrument::setSerialNumberCam(ViChar* serial_number_cam)
{
	strcpy_s(this->serial_number_cam, serial_number_cam);
}

void Instrument::setInitialized(bool is_initialized)
{
	this->is_initialized = is_initialized;
}

void Instrument::setStatus(ViInt32 status)
{
	this->status = status;
}

bool Instrument::isInitialized() const
{
	return this->is_initialized;
}

int Instrument::getDeviceId()
{
	return this->device_id;
}

ViSession Instrument::getHandle() const
{
	return this->handle;
}

const ViChar* Instrument::getInstrumentName() const
{
	return this->instrument_name;
}

const ViInt32* Instrument::getSpotsX() const
{
	return &this->spots_x;
}

const ViInt32* Instrument::getSpotsY() const
{
	return &this->spots_y;
}

const ViChar* Instrument::getWfsDriverVersion() const
{
	return this->version_wfs_driver;
}

const ViChar* Instrument::getCamDriverVersion() const
{
	return this->version_cam_driver;
}

const ViChar* Instrument::getManufacturerName() const
{
	return this->manufacturer_name;
}

const ViChar* Instrument::getSerialNumberWfs() const
{
	return this->serial_number_wfs;
}

const ViChar* Instrument::getSerialNumberCam() const
{
	return this->serial_number_cam;
}

ViInt32 Instrument::getStatus() const
{
	return this->status;
}


