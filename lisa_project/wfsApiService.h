#pragma once
class WfsApiService
{
	bool isConnected;
	public:
		WfsApiService();
		~WfsApiService();


		bool isApiConnectionActive();
};

