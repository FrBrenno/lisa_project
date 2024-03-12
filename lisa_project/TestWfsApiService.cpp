#include "TestWfsApiService.h"

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
	instr->setDeviceId(1);
	instr->setWfsDriverVersion((ViChar*) "Test Wfs Driver Version");
	instr->setCamDriverVersion((ViChar*) "Test Cam Driver Version");
	instr->setManufacturerName((ViChar*) "Test Manufacturer Name");
	instr->setInstrumentName((ViChar*) "Test Instrument Name");
	instr->setSerialNumberWfs((ViChar*) "Test Serial Number Wfs");
	instr->setSerialNumberCam((ViChar*) "Test Serial Number Cam");
	instr->setHandle(1);
	instr->setInitialized(true);
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::closeInstrument(ViSession handle)
{
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::getMlaList(ViSession handle, std::vector<MlaDto>* mlas)
{
	MlaDto mla_1, mla_2;
	mla_1.setMlaName((ViChar*) "Test MLA 1");
	mla_1.setCamPitchm(0.001);
	mla_1.setLensletPitchm(0.001);
	mla_1.setSpotOffsetX(0.001);
	mla_1.setSpotOffsetY(0.001);
	mla_1.setLensletFm(0.001);
	mla_1.setGrdCorr0(0.001);
	mla_1.setGrdCorr45(0.001);

	mla_2.setMlaName((ViChar*) "Test MLA 2");
	mla_2.setCamPitchm(0.002);
	mla_2.setLensletPitchm(0.002);
	mla_2.setSpotOffsetX(0.002);
	mla_2.setSpotOffsetY(0.002);
	mla_2.setLensletFm(0.002);
	mla_2.setGrdCorr0(0.002);
	mla_2.setGrdCorr45(0.002);

	mlas->push_back(mla_1);
	mlas->push_back(mla_2);
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::getMlaInfo(ViSession handle, int selectedIndex, Mla* mla)
{
	mla->setMlaName((ViChar*) "Test MLA");
	mla->setCamPitchm(0.001);
	mla->setLensletPitchm(0.001);
	mla->setCenterSpotOffsetX(0.001);
	mla->setCenterSpotOffsetY(0.001);
	mla->setLensletFm(0.001);
	mla->setGrdCorr0(0.001);
	mla->setGrdCorr45(0.001);
	return VI_SUCCESS;
}

ViStatus TestWfsApiService::getImage(ViSession handle, int NUMBER_READING_IMAGES, ViAUInt8* imageBuffer, ViInt32* rows, ViInt32* cols)
{
	*rows = 512;
	*cols = 512;
	
	ViAUInt8 buffer = new ViUInt8[512 * 512];
	
	// Load an image and store it in imageBuffer
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			// Fill the image with random values
			buffer[i * 512 + j] = rand() % 256;
		}
	}
	ViAUInt8* save = imageBuffer;
	imageBuffer = &buffer;
	delete save;
	return VI_SUCCESS;
}
