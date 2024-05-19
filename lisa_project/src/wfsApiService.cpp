#include "wfsApiService.h"
#include "thorlabs_api/WFS.h"
#include "WfsParameters.h"
#include <iostream>


WfsApiService::WfsApiService()
{
	this->isConnected = this->isApiConnectionActive();
}

WfsApiService::~WfsApiService(){}

//=== API Connection ===//

const bool WfsApiService::isApiConnectionActive()
{
    ViInt32 instr_count = VI_NULL;

    if (int err = WFS_GetInstrumentListLen(VI_NULL, &instr_count))
	{
		isConnected = false;
		std::cerr << "API connection status changed. New status: Disconnected" << std::endl;
	}	
	else{
        isConnected = true;
		std::cerr << "API connection status changed. New status: Connected" << std::endl;
    }

    return this->isConnected;
}

//=== API Usage ===//
// Instrument

ViStatus WfsApiService::getInstrumentsList(std::vector<InstrumentDto>& instruments)
{
	// Variables
	ViInt32 instrumentCount = 0;
	ViInt32 device_id;
	ViInt32 in_use;
	ViChar instr_name[WFS_BUFFER_SIZE];
	ViChar serNr[WFS_BUFFER_SIZE];
	ViChar resourceName[WFS_BUFFER_SIZE];
	ViStatus err;

	// Get instrument count
	if (err = WFS_GetInstrumentListLen(VI_NULL, &instrumentCount))
	{
		// Not able to get the count of instruments connected
		std::cerr << "Failed to get instrument count. Error code: " << err << std::endl;
		return err;
	}

	if (instrumentCount == 0)
	{
		// No instrument found, return empty list
		instruments.clear();
		return VI_SUCCESS;
	}
	else
	{
		for (int i = 0; i < instrumentCount; i++)
		{
			if (err = WFS_GetInstrumentListInfo(VI_NULL, i, &device_id, &in_use, instr_name, serNr, resourceName))
			{
				// Not able to get instrument's information
				std::cerr << "Failed to get instrument info. Error code: " << err << std::endl;
				return err;
			}
			// Add instrument to list
			InstrumentDto instrument;
			instrument.setDeviceId(device_id);
			instrument.setInUse(in_use);
			instrument.setInstrName(instr_name);
			instrument.setSerNr(serNr);
			instrument.setResourceName(resourceName);
			instruments.push_back(instrument);
		}
		return VI_SUCCESS; // Success
	}
}

ViStatus WfsApiService::getInstrumentInfo(InstrumentDto& instrument, int selectedIndex)
{
	// Variables
	ViInt32 device_id;
	ViInt32 in_use;
	ViChar instr_name[WFS_BUFFER_SIZE];
	ViChar serNr[WFS_BUFFER_SIZE];
	ViChar resourceName[WFS_BUFFER_SIZE];
	ViStatus err;

	// Get instrument information
	if (err = WFS_GetInstrumentListInfo(VI_NULL, selectedIndex, &device_id, &in_use, instr_name, serNr, resourceName))
	{
		// Not able to get instrument's information
		std::cerr << "Failed to get instrument info. Error code: " << err << std::endl;
		return err;
	}
	// Set instrument information
	instrument.setDeviceId(device_id);
	instrument.setInUse(in_use);
	instrument.setInstrName(instr_name);
	instrument.setSerNr(serNr);
	instrument.setResourceName(resourceName);
	return VI_SUCCESS; // Success
}

ViStatus WfsApiService::initInstrument(InstrumentDto& instrDto, Instrument* instr)
{
	ViChar resourceName[WFS_BUFFER_SIZE];
	strcpy_s(resourceName, instrDto.getResourceName());
	ViSession handle;
	ViStatus err;

	// API call to initiate a instrument session (handle)
	if (err = WFS_init(resourceName, VI_FALSE, VI_FALSE, &handle))
	{
		// Not able to initiate instrument
		std::cerr << "Failed to initiate instrument. Error code: " << err << std::endl;
		return err;
	}
	else {
		ViChar manufacturer_name[WFS_BUFFER_SIZE];
		ViChar instrument_name[WFS_BUFFER_SIZE];
		ViChar serial_number_wfs[WFS_BUFFER_SIZE];
		ViChar serial_number_cam[WFS_BUFFER_SIZE];
		// Get instrument information
		if (err = WFS_GetInstrumentInfo(handle, manufacturer_name, instrument_name, serial_number_wfs, serial_number_cam))
		{
			WFS_close(handle);
			std::cerr << "Failed to get instrument info after initiation. Error code: " << err << std::endl;
			return err;
		}
		else {
			instr->setDeviceId(instrDto.getDeviceId());
			instr->setWfsDriverVersion(manufacturer_name);
			instr->setCamDriverVersion(instrument_name);
			instr->setManufacturerName(manufacturer_name);
			instr->setInstrumentName(instrument_name);
			instr->setSerialNumberWfs(serial_number_wfs);
			instr->setSerialNumberCam(serial_number_cam);
			instr->setHandle(handle);
			instr->setInitialized(true);
		}
	}
	return VI_SUCCESS; // Success
}

ViStatus WfsApiService::closeInstrument(ViSession handle)
{
	// API call to close a instrument session (handle)
	if (ViStatus err = WFS_close(handle))
	{
		// Not able to close instrument
		std::cerr << "Failed to close instrument. Error code: " << err << std::endl;
		return err;
	}
	return VI_SUCCESS; // Success
}

// MLA

ViStatus WfsApiService::getMlaInfo(ViSession handle, int selectedIndex, MlaDto& mla)
{
	// Variables
	ViChar mla_name[WFS_BUFFER_SIZE];
	ViReal64 cam_pitch, lenslet_pitch, spot_offset_x, spot_offset_y, lenslet_fm, grd_corr_0, grd_corr_45;
	ViStatus err;

	// Get MLA information
	if (err = WFS_GetMlaData(handle, selectedIndex, mla_name, &cam_pitch, &lenslet_pitch, &spot_offset_x, &spot_offset_y, &lenslet_fm, &grd_corr_0, &grd_corr_45))
	{
		// Not able to get MLA's information
		std::cerr << "Failed to get MLA info. Error code: " << err << std::endl;
		return err;
	}
	// Set MLA information
	mla.setMlaName(mla_name);
	mla.setCamPitchm(cam_pitch);
	mla.setLensletPitchm(lenslet_pitch);
	mla.setSpotOffsetX(spot_offset_x);
	mla.setSpotOffsetY(spot_offset_y);
	mla.setLensletFm(lenslet_fm);
	mla.setGrdCorr0(grd_corr_0);	
	mla.setGrdCorr45(grd_corr_45);
	return VI_SUCCESS; // Success
}

ViStatus WfsApiService::selectMla(ViSession handle, int selectedIndex)
{
	// API call to select MLA
	if (ViStatus err = WFS_SelectMla(handle, selectedIndex))
	{
		// Not able to select MLA
		std::cerr << "Failed to select MLA. Error code: " << err << std::endl;
		return err;
	}
	return VI_SUCCESS; // Success
}

// Camera

ViStatus WfsApiService::configureCamera(ViSession handel, int deviceId, ViInt32& spotsX, ViInt32& spotsY)
{
	if (deviceId & DEVICE_OFFSET_WFS20)
	{
		// API call to configure camera
		if (ViStatus err = WFS_ConfigureCam(handel, SAMPLE_PIXEL_FORMAT, SAMPLE_CAMERA_RESOL_WFS20, &spotsX, &spotsY))
		{
			// Not able to configure camera
			std::cerr << "Failed to configure camera. Error code: " << err << std::endl;
			return err;
		}
		return VI_SUCCESS; // Success
	}
	else
	{
		// Other devices are not compatible with this software for now
		std::cerr << "Device is not compatible with this software for now" << std::endl;
		return -1;
	}
	
}

ViStatus WfsApiService::setReferencePlane(ViSession handle)
{
	// API call to set reference plane
	if (ViStatus err = WFS_SetReferencePlane(handle, SAMPLE_REF_PLANE))
	{
		// Not able to set reference plane
		std::cerr << "Failed to set reference plane. Error code: " << err << std::endl;
		return err;
	}
	return VI_SUCCESS; // Success
}

ViStatus WfsApiService::setPupil(ViSession handle)
{
	// API call to set pupil
	if (ViStatus err = WFS_SetPupil(handle, SAMPLE_PUPIL_CENTROID_X, SAMPLE_PUPIL_CENTROID_Y, SAMPLE_PUPIL_DIAMETER_X, SAMPLE_PUPIL_DIAMETER_Y))
	{
		// Not able to set pupil
		std::cerr << "Failed to set pupil. Error code: " << err << std::endl;
		return err;
	}
	return VI_SUCCESS; // Success
}

// Image

ViStatus WfsApiService::getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols)
{
	ViStatus err;
	ViStatus status = VI_NULL;
	ViReal64 exposure = 0.0;
	ViReal64 gain = 0.0;
	for (int i = 0; i < NUMBER_READING_IMAGES; i++) // TODO: Find somewhere to put the NbOfReadings
	{
		if (err = WFS_TakeSpotfieldImageAutoExpos(handle, &exposure, &gain)){
			std::cerr << "Error while taking spotfield image" << err << std::endl;
			return err;
		}
		// TODO: this may be the indicative of how to set the camera in order to take a good picture. think about it later
		if (err = WFS_GetStatus(handle, &status))
			std::cerr << "Error while getting instrument status" << err << std::endl;

		if (status & WFS_STATBIT_PTH)
			std::cerr << "Image exposure is too high" << status << std::endl;
		if (status & WFS_STATBIT_PTL)
			std::cerr << "Image exposure is too low" << status << std::endl;
		if (status & WFS_STATBIT_HAL)
			std::cerr << "Image gain is too high" << status << std::endl;
		else
		{}
	}

	// Get last image
	if (err = WFS_GetSpotfieldImage(handle, imageBuffer, rows, cols)) {
		std::cerr << "Error while getting spotfield image" << err << std::endl;
		return err;
	}
	return VI_SUCCESS; // Success
}
