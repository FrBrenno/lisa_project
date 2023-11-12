#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "HomeFrame.h"
#include "HomeFrameController.h"
#include "InstrumentController.h"
#include "MlaController.h"
#include "ImageController.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/** 
    @class MyApp
    @brief This class is the main class of the application responsible to manage all the application controllers and views.
 */
class MyApp : public wxApp
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
    virtual bool OnInit();
    void check_api_connection();
    virtual int OnExit();
};