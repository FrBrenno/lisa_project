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

