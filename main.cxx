/*
 * hworld.cpp
 */

#include "wx/wx.h" 

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
private:
	wxTextCtrl *piEdit;
public:

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
	void onSubmit(wxCommandEvent& event);
	
    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Quit = 1,
    ID_About,
    ID_SUBMIT,
    ID_BUTTON
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Quit, MyFrame::OnQuit)
    EVT_MENU(ID_About, MyFrame::OnAbout)
    EVT_TEXT_ENTER(ID_SUBMIT, MyFrame::onSubmit)
    EVT_BUTTON(ID_BUTTON,  MyFrame::onSubmit)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( _("Hello World"), wxPoint(50, 50),
                                  wxSize(450,340) );
    frame->Show(true);
    SetTopWindow(frame);
    return true;
} 

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
		: wxFrame( NULL, -1, title, pos, size )
{
	wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_About, _("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, _("E&xit") );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _("&File") );
	
	piEdit = new wxTextCtrl(panel, ID_SUBMIT, wxT(""), 
			wxPoint(40, 40), wxSize(120,30), wxTE_PROCESS_ENTER);
	piEdit->SetValue(_("3"));
	
    new wxButton(panel, ID_BUTTON, wxT("Ok"), wxPoint(40, 80));
    
    
    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( _("Welcome to wxWidgets!") );
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _("This is a wxWidgets Hello world sample"),
                  _("About Hello World"),
                  wxOK | wxICON_INFORMATION, this);
}

void
MyFrame::onSubmit(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox( piEdit->GetValue(), _("Validation"),
                  wxOK | wxICON_INFORMATION, this);
}
