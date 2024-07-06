#pragma once
#include <wx/wx.h>

/**
 * @class IInstrumentViewListener.
 * @brief Interface for the instrument view listener.
 * 
 * This interface defines the methods that must be implemented by the instrument view listener.
 */
class IInstrumentViewListener 
{
public:
	/**
	 * @brief Populates the instrument list.
	 * 
	 * @param instrumentList List of instruments.
	 */
	virtual void populateInstrumentList(wxListBox* instrumentList) = 0;
	/**
	 * @brief Handles the selection of an instrument, its initialization and configuration.
	 * 
	 * @param selectedIndex Index of the selected instrument.
	 */
	virtual void onInstrumentSelected(int selectedIndex) = 0;
	/**
	 * @brief Handles the closing of the instrument view.
	 * 
	 */
	virtual void onClose() = 0;
};
