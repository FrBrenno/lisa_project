#pragma once

class MyAppInterface
{
public:
	virtual ~MyAppInterface() {};
	virtual void check_api_connection() = 0;
};
