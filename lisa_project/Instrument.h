#pragma once

#include <string>
#include "WFS.h"
#include "Mla.h"

/**
 * @class Instrument.
 * @brief This model class contains all the information about the instrument.
 */
class Instrument{
	// Instrument Parameters
	int device_id;
	ViSession handle;
	int status;
	bool is_initialized;

	// WFS Parameters
	std::string version_wfs_driver;
	std::string version_cam_driver;
	std::string manufacturer_name;
	std::string instrument_name;
	std::string serial_number_wfs;
	std::string serial_number_cam;	

	// MLA Parameters
	Mla* mla;

	// Camera Parameters
	ViInt32 spots_x;
	ViInt32 spots_y;

public:
	void setDeviceId(int device_id);
	void setWfsDriverVersion(std::string version_wfs_driver);
	void setCamDriverVersion(std::string version_cam_driver);
	void setInstrumentInfo(std::string manufacturer_name, std::string instrument_name, std::string serial_number_wfs, std::string serial_number_cam);
	void setInitialized(bool is_initialized);
	void setMla(Mla* mla);

	bool isInitialized();
	std::string getInstrumentName();
	ViSession* getHandle();
	int getDeviceId();
	ViInt32* getSpotsX();
	ViInt32* getSpotsY();

};
