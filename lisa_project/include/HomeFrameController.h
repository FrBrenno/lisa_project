#pragma once
#include "wx/wx.h"
#include "BaseController.h"
#include "IHomeFrameListener.h"

/**
 * @class HomeFrameController.
 * @brief This controller manages HomeFrame view responsible for the main window of the software.
 */
class HomeFrameController : public BaseController, public IHomeFrameListener{
public:
	HomeFrameController(MyAppInterface* main, IApiService* wfsApiService);


	void onConnectAPI() override;

};
