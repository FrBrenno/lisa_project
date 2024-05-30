#pragma once
#include "IApiService.h"

class WfsApiService: public IApiService
{
	bool isConnected;
public:
	WfsApiService();
	~WfsApiService();

	//=== API Connection ===//
	const bool isApiConnectionActive() override;

	//=== API Usage ===//

	// Instrument
	ViStatus getInstrumentsList(std::vector<InstrumentDto>& instruments) override;
	ViStatus getInstrumentInfo(InstrumentDto& instrument, int selectedIndex) override;
	ViStatus initInstrument(InstrumentDto& instrDto, Instrument* instr) override;
	ViStatus closeInstrument(ViSession handle) override;

	// MLA
	ViStatus getMlaInfo(ViSession handle, int selectedIndex, MlaDto& mla) override;
	ViStatus selectMla(ViSession handle, int selectedIndex) override;

	// Camera
	ViStatus configureCamera(ViSession handle, int devideId, ViInt32& spotsX, ViInt32& spotsY) override;
	ViStatus setReferencePlane(ViSession handle) override;
	ViStatus setPupil(ViSession handle) override;

	// Image
	ViStatus getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols) override;
};

