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
    /**
     * @brief API Service object.
     * 
     */
    IApiService* wfsApiService;

    //=== Controllers ===//

    /**
     * @brief HomeFrameController object.
     * 
     */
    HomeFrameController * homeFrameController;
    /**
     * @brief InstrumentController object.
     * 
     */
    InstrumentController* instrumentController;
    /**
     * @brief ImageController object.
     * 
     */
    ImageController* imageController;
    /**
     * @brief PreviewController object.
     * 
     */
    PreviewController* previewController;
    /**
     * @brief CalibrationController object.
     * 
     */
    CalibrationController* calibrationController;

    //== Views ===//

    /**
     * @brief HomeFrame object.
     * 
     */
    HomeFrame* homeFrame;

public:
    ~MyApp();

    /**
     * @brief Initializes the application.
     * 
     * @return true if the application was initialized successfully
     */
    virtual bool OnInit();   
    /**
     * @brief Checks the connection to the API.
     * 
     */ 
    void check_api_connection() override;
    
    /**
     * @brief Get the Instrument Handle object
     * 
     * @return ViSession handle to the instrument
     */
    ViSession getInstrumentHandle() override;
    /**
     * @brief Get the HomeFrame object
     * 
     * @return HomeFrame* pointer to the HomeFrame object
     */
    HomeFrame* getHomeFrame() override;
};