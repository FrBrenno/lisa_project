#pragma once
#include "thorlabs_api/visatype.h"
#include "HomeFrame.h"

/**
 * @class MyAppInterface
 * @brief Interface class to be implemented by the main class of the application.
 * 
 */
class MyAppInterface
{
public:
	virtual ~MyAppInterface() {};
	/**
	 * @brief Checks the connection with the API.
	 * 
	 */
	virtual void check_api_connection() = 0;
	/**
	 * @brief Gets the instrument handle.
	 * 
	 * @return ViSession the instrument handle.
	 */
	virtual ViSession getInstrumentHandle() = 0;
	/**
	 * @brief Gets the HomeFrame object.
	 * 
	 * @return HomeFrame* the HomeFrame object.
	 */
	virtual HomeFrame* getHomeFrame() = 0;
};
