#pragma once
#include "Mla.h"
#include "WFS.h"
#include "Event.h"

class MlaController {
	Mla* selectMla;
	ViInt32 err;

	void HandleMlaSelection(const Event& event);
	void HandleMlaSelected(const Event& event);
public:
	MlaController();

	void populateMlaList(wxListBox* list);
	void onMlaSelected(int selectedIndex);
	void OnOK();
	void OnClose();

	void handleError(int code, std::string message);
};
