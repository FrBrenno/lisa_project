#include "InstrumentDto.h"
#include <string.h>

InstrumentDto::InstrumentDto()
{}

InstrumentDto::~InstrumentDto()
{}

ViInt32 InstrumentDto::getDeviceId() const 
{
	return this->device_id;
}

ViInt32 InstrumentDto::getInUse() const
{
	return this->in_use;
}

const ViChar* InstrumentDto::getInstrName() const
{
	return this->instr_name;
}

const ViChar* InstrumentDto::getSerNr() const
{
	return this->serNr;
}

const ViRsrc* InstrumentDto::getResourceName() const
{
	return this->resourceName;
}

void InstrumentDto::setDeviceId(ViInt32 device_id)
{
	this->device_id = device_id;
}

void InstrumentDto::setInUse(ViInt32 in_use)
{
	this->in_use = in_use;
}

void InstrumentDto::setInstrName(ViChar* instr_name)
{
	strcpy_s(this->instr_name, instr_name);
}

void InstrumentDto::setSerNr(ViChar* serNr)
{
	strcpy_s(this->serNr, serNr);
}

void InstrumentDto::setResourceName(ViRsrc* resourceName)
{
	this->resourceName = resourceName;
}

