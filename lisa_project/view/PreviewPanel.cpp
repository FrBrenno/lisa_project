#include "PreviewPanel.h"
#include "id/ButtonID.h"

PreviewPanel::PreviewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(512, 512))
{
	this->parent = parent;

	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap placeholder("./img/lisa_logo.png", wxBITMAP_TYPE_PNG);
	this->imageControl = new wxStaticBitmap(this, wxID_ANY, placeholder, wxDefaultPosition, wxSize(512, 512));
	this->imageControl->SetDoubleBuffered(true);

	this->previewButton = new wxButton(this, ID_PREVIEW, "Start Preview");
	this->captureButton = new wxButton(this, ID_CAPTURE, "Capture");
	this->captureButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		this->onCapture(this->parent);
		});	

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(this->captureButton, 0, wxALIGN_CENTER | wxALL, 5);
	buttonSizer->Add(this->previewButton, 0, wxALIGN_CENTER | wxALL, 5);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(this->imageControl, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);
	SetSizerAndFit(mainSizer);
}

PreviewPanel::~PreviewPanel()
{
	delete this->imageControl;
	delete this->previewButton;
	delete this->captureButton;
}

void PreviewPanel::stopPreview()
{
	this->previewListener->stopPreview();
}

void PreviewPanel::onCapture(wxWindow* parent)
{
	wxFileDialog saveFileDialog(parent, "Save Image", "", "", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	wxString filename = saveFileDialog.GetPath();
	wxImage image = this->imageControl->GetBitmap().ConvertToImage();
	image.SaveFile(filename, wxBITMAP_TYPE_PNG);
}

void PreviewPanel::loadImage()
{
	wxFileDialog openFileDialog(this, "Open Image", "", "", "PNG files (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	wxString filename = openFileDialog.GetPath();
	wxImage image(filename, wxBITMAP_TYPE_PNG);

	this->setImage(&image);
}

void PreviewPanel::setImage(wxImage* image)
{
	// Clear the existing bitmap displayed in the imageControl
	this->imageControl->SetBitmap(wxNullBitmap);

	// Create a new bitmap from the provided image and display it in the imageControl
	wxBitmap bitmap(*image);
	this->imageControl->SetBitmap(bitmap);
	this->imageControl->Refresh();
}

void PreviewPanel::updatePreviewButton(bool isPreviewOn)
{
	if (isPreviewOn)
		this->previewButton->SetLabel("Stop Preview");
	else
		this->previewButton->SetLabel("Start Preview");
}

void PreviewPanel::freezePreview()
{
	this->imageControl->Freeze();
}

void PreviewPanel::thawPreview()
{
	this->imageControl->Thaw();
}

void PreviewPanel::setPreviewListener(IPreviewListener* listener)
{
	this->previewListener = listener;
	this->previewButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		this->previewListener->onPreviewButton();
		});
}
