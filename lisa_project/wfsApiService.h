#pragma once
#include "model/Dto/InstrumentDto.h"
#include "model/Dto/MlaDto.h"
#include "model/Instrument.h"
#include "model/Mla.h"
#include <vector>

class WfsApiService
{
	bool isConnected;
public:
	WfsApiService();
	~WfsApiService();

	//=== API Connection ===//
	bool isApiConnectionActive();

	//=== API Usage ===//

	// Instrument
	ViStatus getInstrumentsList(std::vector<InstrumentDto>* instruments);
	ViStatus getInstrumentInfo(InstrumentDto* instrument, int selectedIndex);
	ViStatus initInstrument(InstrumentDto instrDto, Instrument* instr);
	ViStatus closeInstrument(ViSession handle);

	// MLA
	ViStatus getMlaList(ViSession handle, std::vector<MlaDto>* mlas);
	ViStatus getMlaInfo(ViSession handle, int selectedIndex, Mla* mla);

	// Image
	ViStatus getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols);
};

