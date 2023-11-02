#include "BaseController.h"

BaseController::BaseController(wxApp* main)
{
	this->main = main;
}

wxApp* BaseController::getMain()
{
	return main;
}
