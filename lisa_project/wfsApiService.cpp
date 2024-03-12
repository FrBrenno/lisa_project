#include "wfsApiService.h"
#include <lib/thorlabs_api/WFS.h>
#include <EventDispatcher.h>
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

ViStatus WfsApiService::getMlaList(ViSession handle, std::vector<MlaDto>* mlas)
{
	// Variables
	ViInt32 mlaCount = 0;
	ViChar mla_name[WFS_BUFFER_SIZE];
	ViReal64 cam_pitch, lenslet_pitch, spot_offset_x, spot_offset_y, lenslet_fm, grd_corr_0, grd_corr_45;
	ViStatus err;

	// Get MLA count
	if (err = WFS_GetMlaCount(handle, &mlaCount))
	{
		// Not able to get the count of MLA
		std::cerr << "Failed to get MLA count. Error code: " << err << std::endl;
		return err;
	}

	if (mlaCount == 0)
	{
		// No MLA found, return empty list
		mlas->clear();
		return VI_SUCCESS;
	}
	else
	{
		for (int i = 0; i < mlaCount; i++)
		{
			if (err = WFS_GetMlaData(handle, i, mla_name, &cam_pitch, &lenslet_pitch, &spot_offset_x, &spot_offset_y, &lenslet_fm, &grd_corr_0, &grd_corr_45))
			{
				// Not able to get MLA's information
				std::cerr << "Failed to get MLA info. Error code: " << err << std::endl;
				return err;
			}
			// Add MLA to list
			MlaDto mla;
			mla.setMlaName(mla_name);
			mla.setCamPitchm(cam_pitch);
			mla.setLensletPitchm(lenslet_pitch);
			mla.setSpotOffsetX(spot_offset_x);
			mla.setSpotOffsetY(spot_offset_y);
			mla.setLensletFm(lenslet_fm);
			mla.setGrdCorr0(grd_corr_0);
			mla.setGrdCorr45(grd_corr_45);
			mlas->push_back(mla);
		}
		return VI_SUCCESS; // Success
	}
}

ViStatus WfsApiService::getMlaInfo(ViSession handle, int selectedIndex, Mla* mla)
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
	mla->setMlaName(mla_name);
	mla->setCamPitchm(cam_pitch);
	mla->setLensletPitchm(lenslet_pitch);
	mla->setCenterSpotOffsetX(spot_offset_x);
	mla->setCenterSpotOffsetY(spot_offset_y);
	mla->setLensletFm(lenslet_fm);
	mla->setGrdCorr0(grd_corr_0);	
	mla->setGrdCorr45(grd_corr_45);
	return VI_SUCCESS; // Success
}

// Image

ViStatus WfsApiService::getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols)
{
	ViStatus err;
	for (int i = 0; i < NUMBER_READING_IMAGES; i++) // TODO: Find somewhere to put the NbOfReadings
	{
		if (err = WFS_TakeSpotfieldImageAutoExpos(handle, VI_NULL, VI_NULL)) {
			std::cerr << "Error while taking spotfield image" << err << std::endl;
			return err;
		}
		ViInt32 status = VI_NULL;
		// TODO: this may be the indicative of how to set the camera in order to take a good picture. think about it later
		if (err = WFS_GetStatus(handle, &status))
			std::cerr << "Error while getting instrument status" << err << std::endl;
		if (status & WFS_STATBIT_PTH)
			std::cerr << "Image exposure is too high" << status << std::endl;
		else if (status & WFS_STATBIT_PTL)
			std::cerr << "Image exposure is too low" << status << std::endl;
		else if (status & WFS_STATBIT_HAL)
			std::cerr << "Image gain is too high" << status << std::endl;
		else{}
	}
	// Get last image
	if (err = WFS_GetSpotfieldImage(handle, imageBuffer, rows, cols)) {
		std::cerr << "Error while getting spotfield image" << err << std::endl;
		return err;
	}
	return VI_SUCCESS; // Success
}
