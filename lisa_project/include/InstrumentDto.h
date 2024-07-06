#pragma once
#include "thorlabs_api/WFS.h"

/**
 * @class InstrumentDto.
 * @brief This class is a data transfer object for the Instrument class.
 */
class InstrumentDto
{
	/**
	 * @brief Device ID.
	 * 
	 */
	ViInt32 device_id;
	/**
	 * @brief In use flag.
	 * 
	 */
	ViInt32 in_use;
	/**
	 * @brief Instrument name.
	 * 
	 */
	ViChar instr_name[WFS_BUFFER_SIZE];
	/**
	 * @brief Serial number.
	 * 
	 */
	ViChar serNr[WFS_BUFFER_SIZE];
	/**
	 * @brief Resource name.
	 * 
	 */
	ViChar resourceName[WFS_BUFFER_SIZE];

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

