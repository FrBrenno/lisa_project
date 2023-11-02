#include <wx/wx.h>
#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

class BaseController{
	wxApp* main;

public:
	BaseController(wxApp* main);
	wxApp* getMain();
};

#endif // BASECONTROLLER_H