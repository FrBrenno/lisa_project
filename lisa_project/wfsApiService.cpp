#include "wfsApiService.h"
#include <lib/thorlabs_api/WFS.h>
#include <EventDispatcher.h>

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
    }

    return isConnected;
}

bool WfsApiService::getInstrumentsList(std::vector<InstrumentDto>* instruments)
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
		return false;
	}

	if (instrumentCount == 0)
	{
		// No instrument found, return empty list
		instruments->clear();
		return true;
	}
	else
	{
		for (int i = 0; i < instrumentCount; i++)
		{
			if (err = WFS_GetInstrumentListInfo(VI_NULL, i, &device_id, &in_use, instr_name, serNr, resourceName))
			{
				// Not able to get instrument's information
				return false;
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
		return true; // Success
	}
}
