#pragma once
#include <InstrumentDto.h>
#include <model/Instrument.h>

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
};

