#pragma once
#include "IApiService.h"

/**
 * @class TestWfsApiService.
 * @brief This class is used to test the WFS API Service. It provides necessary but mock data in 
 * order to test the application without the need of the WFS API.
 */
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
	ViStatus getMlaInfo(ViSession handle, int selectedIndex, MlaDto& mla) override;
	ViStatus selectMla(ViSession handle, int selectedIndex) override;

	// Camera
	virtual ViStatus configureCamera(ViSession handle, int devideId, ViInt32& spotsX, ViInt32& spotsY) override;
	virtual ViStatus setReferencePlane(ViSession handle) override;
	virtual ViStatus setPupil(ViSession handle) override;

	// Image
	ViStatus getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols) override;
};

