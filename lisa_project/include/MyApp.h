#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "HomeFrame.h"
#include "HomeFrameController.h"
#include "InstrumentController.h"
#include "ImageController.h"
#include "PreviewController.h"
#include "CalibrationController.h"
#include "IApiService.h"
#include "MyAppInterface.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/** 
    @class MyApp
    @brief This class is the main class of the application responsible to manage all the application controllers and views.
 */
class MyApp : public wxApp, MyAppInterface
{
    
    IApiService* wfsApiService;

    //=== Controllers ===//

    HomeFrameController * homeFrameController;
    InstrumentController* instrumentController;
    ImageController* imageController;
    PreviewController* previewController;
    CalibrationController* calibrationController;

    //== Views ===//

    HomeFrame* homeFrame;

public:
    ~MyApp();

    virtual bool OnInit();    
    void check_api_connection() override;
    
    ViSession getInstrumentHandle() override;
    HomeFrame* getHomeFrame() override;
};