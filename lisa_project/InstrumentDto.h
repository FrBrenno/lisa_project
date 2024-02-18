#pragma once
#include <lib/thorlabs_api/WFS.h>

class InstrumentDto
{
	ViInt32 device_id;
	ViInt32 in_use;
	ViChar instr_name[WFS_BUFFER_SIZE];
	ViChar serNr[WFS_BUFFER_SIZE];
	ViRsrc resourceName[WFS_BUFFER_SIZE];

	public:
		InstrumentDto();
		~InstrumentDto();

		ViInt32 getDeviceId() const;
		ViInt32 getInUse() const;
		const ViChar* getInstrName() const;
		const ViChar* getSerNr() const;
		const ViChar* getResourceName() const;
		void setDeviceId(ViInt32 device_id);
		void setInUse(ViInt32 in_use);
		void setInstrName(ViChar* instr_name);
		void setSerNr(ViChar* serNr);
		void setResourceName(ViChar* resourceName);
};

