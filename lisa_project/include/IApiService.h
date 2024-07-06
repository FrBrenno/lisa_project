#pragma once
#include "InstrumentDto.h"
#include "MlaDto.h"
#include "Instrument.h"
#include "Mla.h"
#include <vector>

/**
 * @class IApiService.
 * @brief Interface for the API service.
 * 
 * This interface defines the methods that must be implemented by the API service.
 */
class IApiService
{
	/**
	 * @brief Flag that indicates if the API connection is active.
	 * 
	 */
	bool isConnected;
public:
	//=== API Connection ===//
	/**
	 * @brief Method that checks if the API connection is active.
	 * 
	 * It checks the connectivity by effectuating a simple API call. If it succeeds,
	 * the connection is considered active.	
	 * 
	 * @return  
	 */
	virtual const bool isApiConnectionActive() = 0;

	//=== API Usage ===//

	// Instrument
	/**
	 * @brief Get the list of connected instruments detected by the API.
	 * 
	 * @param instruments List of instruments detected by the API.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus getInstrumentsList(std::vector<InstrumentDto>& instruments) = 0;
	/**
	 * @brief Get the information of a selected instrument.
	 * 
	 * @param instrument Information of the selected instrument.
	 * @param selectedIndex Index of the selected instrument.
	 * @return ViStatus status code of the operation.
	 
	 */
	virtual ViStatus getInstrumentInfo(InstrumentDto& instrument, int selectedIndex) = 0;
	/**
	 * @brief Initialize the selected instrument.
	 * 
	 * It collects all data about the instrument and opens a session to communicate with the instrument
	 * This call returns the handle to the instrument which is necessary to use it.
	 * 
	 * @param instrDto Information of the selected instrument.
	 * @param instr Pointer to the instrument object.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus initInstrument(InstrumentDto& instrDto, Instrument* instr) = 0;
	/**
	 * @brief Close the session with the selected instrument.
	 * 
	 * @param handle Handle to the instrument.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus closeInstrument(ViSession handle) = 0;

	// MLA
	/**
	 * @brief Get the list of connected MLAs detected by the API.
	 * 
	 * @param mlas List of MLAs detected by the API.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus getMlaInfo(ViSession handle, int selectedIndex, MlaDto& mla) = 0;
	/**
	 * @brief Select the MLA to be used.
	 * 
	 * @param handle Handle to the instrument.
	 * @param selectedIndex Index of the selected MLA.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus selectMla(ViSession handle, int selectedIndex) = 0;

	// Camera
	/**
	 * @brief Configure the camera.
	 * 
	 * The camera configuration is done using default values used in the WFS API demo.
	 * 
	 * @param handle Handle to the instrument.
	 * @param devideId ID of the camera device.
	 * @param spotsX Number of spots in the X axis.
	 * @param spotsY Number of spots in the Y axis.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus configureCamera(ViSession handle, int devideId, ViInt32& spotsX, ViInt32& spotsY) = 0;
	/**
	 * @brief Set the Reference Plane of the instrument.
	 * 
	 * @param handle Handle to the instrument.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus setReferencePlane(ViSession handle) = 0;
	/**
	 * @brief Set the Pupil Plane of the instrument.
	 * 
	 * @param handle Handle to the instrument.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus setPupil(ViSession handle) = 0;
	
	// Image
	/**
	 * @brief Get the image from the instrument.
	 * 
	 * @param handle Handle to the instrument.
	 * @param NUMBER_READING_IMAGES Number of images to be read.
	 * @param imageBuffer Buffer to store the image.
	 * @param rows Number of rows of the image.
	 * @param cols Number of columns of the image.
	 * @return ViStatus status code of the operation.
	 */
	virtual ViStatus getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols) = 0;
};
