#include "Instrument.h"

void Instrument::setWfsDriverVersion(std::string wfs_driver_version) {
	this->version_wfs_driver = wfs_driver_version;
}

void Instrument::setCamDriverVersion(std::string cam_driver_version) {
	this->version_cam_driver = cam_driver_version;
}
