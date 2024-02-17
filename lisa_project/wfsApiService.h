#pragma once
#include <InstrumentDto.h>

class WfsApiService
{
	bool isConnected;
	public:
		WfsApiService();
		~WfsApiService();

		//=== API Connection ===//
		bool isApiConnectionActive();

		//=== API Usage ===//
		bool getInstrumentsList(std::vector<InstrumentDto>* instruments);
};

