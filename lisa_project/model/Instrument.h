#pragma once

#include <string>
#include "lib/thorlabs_api/WFS.h"
#include "Mla.h"

/**
 * @class Instrument.
 * @brief This model class contains all the information about the instrument.
 */
class Instrument{
	// Instrument Parameters
	bool is_initialized;
	ViSession handle;
	ViInt32 status;
	ViInt32 device_id;
	ViRsrc resourceName[WFS_BUFFER_SIZE];

	// WFS Parameters
	ViChar version_wfs_driver[WFS_BUFFER_SIZE];
	ViChar version_cam_driver[WFS_BUFFER_SIZE];
	ViChar manufacturer_name[WFS_BUFFER_SIZE];
	ViChar instrument_name[WFS_BUFFER_SIZE];
	ViChar serial_number_wfs[WFS_BUFFER_SIZE];
	ViChar serial_number_cam[WFS_BUFFER_SIZE];

	// MLA Parameters
	Mla* mla;

	// Camera Parameters
	ViInt32 spots_x;
	ViInt32 spots_y;

public:
	Instrument();
	~Instrument();

	// Setters
	void setDeviceId(int device_id);
	void setHandle(ViSession handle);
	void setWfsDriverVersion(ViChar* wfs_driver_version);
	void setCamDriverVersion(ViChar* cam_driver_version);
	void setManufacturerName(ViChar* manufacturer_name);
	void setInstrumentName(ViChar* instrument_name);
	void setSerialNumberWfs(ViChar* serial_number_wfs);
	void setSerialNumberCam(ViChar* serial_number_cam);

	void setInitialized(bool is_initialized);
	void setMla(Mla* mla);
	void setStatus(ViInt32 status);

	// Getters
	bool isInitialized();
	int getDeviceId();
	const ViSession getHandle();
	const ViChar* getInstrumentName();
	const ViInt32* getSpotsX();
	const ViInt32* getSpotsY();
};
