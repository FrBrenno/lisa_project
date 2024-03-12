#pragma once
#include "model/Dto/InstrumentDto.h"
#include "model/Dto/MlaDto.h"
#include "model/Instrument.h"
#include "model/Mla.h"
#include <vector>


class IApiService
{
	bool isConnected;
public:
	//=== API Connection ===//
	virtual const bool isApiConnectionActive() = 0;

	//=== API Usage ===//

	// Instrument
	virtual ViStatus getInstrumentsList(std::vector<InstrumentDto>& instruments) = 0;
	virtual ViStatus getInstrumentInfo(InstrumentDto& instrument, int selectedIndex) = 0;
	virtual ViStatus initInstrument(InstrumentDto& instrDto, Instrument* instr) = 0;
	virtual ViStatus closeInstrument(ViSession handle) = 0;

	// MLA
	virtual ViStatus getMlaInfo(ViSession handle, int selectedIndex, MlaDto& mla) = 0;
	virtual ViStatus selectMla(ViSession handle, int selectedIndex) = 0;

	// Camera
	virtual ViStatus configureCamera(ViSession handle, int devideId, ViInt32& spotsX, ViInt32& spotsY) = 0;
	virtual ViStatus setReferencePlane(ViSession handle) = 0;
	virtual ViStatus setPupil(ViSession handle) = 0;
	
	// Image
	virtual ViStatus getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols) = 0;
};
