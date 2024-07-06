#pragma once

#include <string>
#include "thorlabs_api/WFS.h"

/**
 * @class Instrument.
 * @brief This model class contains all the information about the instrument.
 */
class Instrument{
	// Instrument Parameters
	/**
	 * @brief Flag that indicates if the instrument is initialized.
	 * 
	 */
	bool is_initialized;
	/**
	 * @brief Handle to the instrument.
	 * 
	 */
	ViSession handle;
	/**
	 * @brief Status of the instrument.
	 * 
	 */
	ViInt32 status;
	/**
	 * @brief Device ID of the instrument.
	 * 
	 */
	ViInt32 device_id;
	/**
	 * @brief Resource name of the instrument.
	 * 
	 */
	ViChar resourceName[WFS_BUFFER_SIZE];

	// WFS Parameters
	/**
	 * @brief Version of the WFS driver.
	 * 
	 */
	ViChar version_wfs_driver[WFS_BUFFER_SIZE];
	/**
	 * @brief Version of the camera driver.
	 * 
	 */
	ViChar version_cam_driver[WFS_BUFFER_SIZE];
	/**
	 * @brief Manufacturer name.
	 * 
	 */
	ViChar manufacturer_name[WFS_BUFFER_SIZE];
	/**
	 * @brief Instrument name.
	 * 
	 */
	ViChar instrument_name[WFS_BUFFER_SIZE];
	/**
	 * @brief Serial number of the WFS.
	 * 
	 */
	ViChar serial_number_wfs[WFS_BUFFER_SIZE];
	/**
	 * @brief Serial number of the camera.
	 * 
	 */
	ViChar serial_number_cam[WFS_BUFFER_SIZE];

	// Camera Parameters
	/**
	 * @brief Number of spots in the X axis.
	 * 
	 */
	ViInt32 spots_x;
	/**
	 * @brief Number of spots in the Y axis.
	 * 
	 */
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
	void setSpotsX(ViInt32 spots_x);
	void setSpotsY(ViInt32 spots_y);

	void setInitialized(bool is_initialized);
	void setStatus(ViInt32 status);

	// Getters
	bool isInitialized() const;
	int getDeviceId();
	ViSession getHandle() const;
	const ViChar* getInstrumentName() const;
	const ViInt32* getSpotsX() const;
	const ViInt32* getSpotsY() const;
	const ViChar* getWfsDriverVersion() const;
	const ViChar* getCamDriverVersion() const;
	const ViChar* getManufacturerName() const;
	const ViChar* getSerialNumberWfs() const;
	const ViChar* getSerialNumberCam() const;
	ViInt32 getStatus() const;
};
