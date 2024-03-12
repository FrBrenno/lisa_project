#pragma once
#include "interface/IApiService.h"

class TestWfsApiService: public IApiService
{
	bool isConnected;
public:
	TestWfsApiService();
	~TestWfsApiService();

	//=== API Connection ===//
	const bool isApiConnectionActive() override;

	//=== API Usage ===//

	// Instrument
	ViStatus getInstrumentsList(std::vector<InstrumentDto>& instruments) override;
	ViStatus getInstrumentInfo(InstrumentDto& instrument, int selectedIndex) override;
	ViStatus initInstrument(InstrumentDto& instrDto, Instrument* instr) override;
	ViStatus closeInstrument(ViSession handle) override;

	// MLA
	ViStatus getMlaList(ViSession handle, std::vector<MlaDto>* mlas) override;
	ViStatus getMlaInfo(ViSession handle, int selectedIndex, Mla* mla) override;

	// Image
	ViStatus getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols) override;
};

