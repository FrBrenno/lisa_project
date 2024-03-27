#include "TestWfsApiService.h"
#include <opencv2/opencv.hpp>

TestWfsApiService::TestWfsApiService()
{
	isConnected = true;
}

TestWfsApiService::~TestWfsApiService()
{}

const bool TestWfsApiService::isApiConnectionActive()
{
	return isConnected;
}

ViStatus TestWfsApiService::getInstrumentsList(std::vector<InstrumentDto>& instruments)
{
	InstrumentDto instr, instr2;
	instr.setDeviceId(1);
	instr.setInUse(0);
	instr.setInstrName((ViChar*) "Test Instrument");
	instr.setResourceName((ViChar*) "Test Resource");
	instr.setSerNr((ViChar*) "Test Serial Number");
	instruments.push_back(instr);

	instr2.setDeviceId(2);
	instr2.setInUse(0);
	instr2.setInstrName((ViChar*) "Test Instrument 2");
	instr2.setResourceName((ViChar*) "Test Resource 2");
	instr2.setSerNr((ViChar*) "Test Serial Number 2");
	instruments.push_back(instr2);
	return VI_SUCCESS;

}

ViStatus TestWfsApiService::getInstrumentInfo(InstrumentDto& instrument, int selectedIndex)
{
	instrument.setDeviceId(1);
	instrument.setInUse(0);
	instrument.setInstrName((ViChar*) "Test Instrument");
	instrument.setResourceName((ViChar*) "Test Resource");
	instrument.setSerNr((ViChar*) "Test Serial Number");
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::initInstrument(InstrumentDto& instrDto, Instrument* instr)
{
	instr->setDeviceId(instrDto.getDeviceId());
	instr->setWfsDriverVersion((ViChar*) "Test Wfs Driver Version");
	instr->setCamDriverVersion((ViChar*) "Test Cam Driver Version");
	instr->setManufacturerName((ViChar*) "Test Manufacturer Name");
	instr->setInstrumentName((ViChar*)"Test Instrument Name");
	instr->setSerialNumberWfs((ViChar*) "Test Serial Number WFS");
	instr->setSerialNumberCam((ViChar*) "Test Serial Number Cam");
	instr->setHandle(1);
	instr->setInitialized(true);
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::closeInstrument(ViSession handle)
{
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::getMlaInfo(ViSession handle, int selectedIndex, MlaDto& mla)
{
	mla.setMlaName((ViChar*) "Test MLA");
	mla.setCamPitchm(0.001);
	mla.setLensletPitchm(0.001);
	mla.setSpotOffsetX(0.001);
	mla.setSpotOffsetY(0.001);
	mla.setLensletFm(0.001);
	mla.setGrdCorr0(0.001);
	mla.setGrdCorr45(0.001);
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::selectMla(ViSession handle, int selectedIndex)
{
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::configureCamera(ViSession handle, int devideId, ViInt32& spotsX, ViInt32& spotsY)
{
	spotsX = 512;
	spotsY = 512;
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::setReferencePlane(ViSession handle)
{
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::setPupil(ViSession handle)
{
	return VI_SUCCESS;
}


ViStatus TestWfsApiService::getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols)
{
	bool calibrationTest = false;
	*rows = 512;
	*cols = 512;
	
	// Clean the image buffer
	if (*imageBuffer != nullptr)
	{
		delete[] *imageBuffer;
		*imageBuffer = nullptr;
	}

	// Allocate memory for the image buffer
	ViUInt8* buffer = new ViUInt8[512 * 512];

	if (calibrationTest){
		// Load an image and store it in imageBuffer
		cv::Mat img = cv::imread("./img/calibration_img/nice_mla_cercles_low.png", cv::IMREAD_GRAYSCALE);
		memcpy(buffer, img.data, 512 * 512);
	}
	else {

		// Load an image and store it in imageBuffer
		for (int i = 0; i < 512; i++)
		{
			for (int j = 0; j < 512; j++)
			{
				// Fill the image with random values
				buffer[i * 512 + j] = rand() % 256;
			}
		}
	}
	*imageBuffer = buffer;
	return VI_SUCCESS;
}
