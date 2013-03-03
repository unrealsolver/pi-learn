/*
 * hworld.cpp
 */

#include "wx/wx.h" 
#include "wx/textfile.h"
#include <algorithm>

class MyApp: public wxApp
{
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
private:
	wxTextCtrl *piEdit;
	wxString piStr;
public:

    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	void validate(wxString str);
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
    
    wxTextFile* file = new wxTextFile(_("pi.dat"));
    file->Open();
    piStr = file->GetFirstLine();
    
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
	validate(piEdit->GetValue());
}

void
MyFrame::validate(wxString s)
{
	int i;
	wxString* a = new wxString(_("testtesttest"));
	wxString* b = new wxString(a->Mid(1,2));
	wxString* message = new wxString(_("Correct"));
	
	for (i = 0; i < s.Len(); i++)
	{
		if (piStr[i] != s[i])
		{
			message->Printf(_("Error at: %d\nContext: ...%s\nCorrect: ...%s"),
					i, s.Mid(std::max(i-3, 0), 4).wc_str(),
					piStr.Mid(std::max(i-3, 0), 4).wc_str());
			break;
		}
	}
	
	wxMessageBox( *message, _("Validation"),
                  wxOK | wxICON_INFORMATION, this);
}
