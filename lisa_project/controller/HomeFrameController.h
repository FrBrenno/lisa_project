#pragma once
#include "wx/wx.h"
#include "../Event.h"
#include "BaseController.h"
#include "../interface/IHomeFrameListener.h"

/**
 * @class HomeFrameController.
 * @brief This controller manages HomeFrame view responsible for the main window of the software.
 */
class HomeFrameController : public BaseController, public IHomeFrameListener{
public:
	HomeFrameController(MyAppInterface* main, IApiService* wfsApiService);

	wxImage onLoadImage(wxWindow* parent) override;

	void onConnectAPI() override;

	void onCapture(wxWindow* parent, wxBitmap lastBitmap) override;

	bool isWfsConnected() override;
};
