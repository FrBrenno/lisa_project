#include "wfsApiService.h"
#include <lib/thorlabs_api/WFS.h>
#include <EventDispatcher.h>
#include <iostream>

WfsApiService::WfsApiService()
{
	this->isConnected = this->isApiConnectionActive();
}

WfsApiService::~WfsApiService(){}

bool WfsApiService::isApiConnectionActive()
{
    ViInt32 instr_count = VI_NULL;
    int err = WFS_GetInstrumentListLen(VI_NULL, &instr_count);

    const bool connected = (err == VI_SUCCESS);
    if (connected != isConnected) {
        isConnected = connected;
		std::cerr << "API connection status changed. New status: " << (connected ? "Connected" : "Disconnected") << std::endl;
    }

    return isConnected;
}

ViStatus WfsApiService::getInstrumentsList(std::vector<InstrumentDto>* instruments)
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
		instruments->clear();
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
			instruments->push_back(instrument);
		}
		return VI_SUCCESS; // Success
	}
}

ViStatus WfsApiService::getInstrumentInfo(InstrumentDto* instrument, int selectedIndex)
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
	instrument->setDeviceId(device_id);
	instrument->setInUse(in_use);
	instrument->setInstrName(instr_name);
	instrument->setSerNr(serNr);
	instrument->setResourceName(resourceName);
	return VI_SUCCESS; // Success
}

ViStatus WfsApiService::initInstrument(InstrumentDto instrDto, Instrument* instr)
{
	ViRsrc resourceName = (ViRsrc) instrDto.getResourceName(); // ATTENTION: Casting from ViChar* to ViRsrc
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
