#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "../view/HomeFrame.h"
#include "../controller/HomeFrameController.h"
#include "../controller/InstrumentController.h"
#include "../controller/MlaController.h"
#include "../controller/ImageController.h"
#include "../controller/CameraSettingsController.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/** 
    @class MyApp
    @brief This class is the main class of the application responsible to manage all the application controllers and views.
 */
class MyApp : public wxApp, MyAppInterface
{
    bool is_wfs_connected = false; // Test API connectivity

    //=== Controllers ===//

    HomeFrameController* homeFrameController;
    InstrumentController* instrumentController;
    MlaController* mlaController;
    ImageController* imageController;

    //== Views ===//

    HomeFrame* homeFrame;

public:
    ~MyApp();

    virtual bool OnInit();    
    void check_api_connection() override;
    void change_api_status();
};