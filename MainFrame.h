#pragma once
#include <wx/wx.h>;
#include <wx/listctrl.h>;

class MainFrame : public wxFrame 
{
public:
	MainFrame(const wxString& title);

private:
	
	void CreateControls();
	void BindEventHandlers();

	void OnAddMemberClicked(wxCommandEvent& evt);
	void OnDelMemberClicked(wxCommandEvent& evt);

	void OnAddTaskClicked(wxCommandEvent& evt);
	void OnDelTaskClicked(wxCommandEvent& evt);

	void OnInputMemberEnter(wxCommandEvent& evt);
	void OnInputTaskEnter(wxCommandEvent& evt);

	void AddTaskFromInput();
	void DelTaskFromList();

	void AddMemberFromInput();
	void DelMemberFromList();

	void OnListKeyDown(wxKeyEvent& evt);

	wxString textName;

	wxPanel* panel;

	wxPanel* panelLeftSide;
	wxPanel* panelMidSide;
	wxPanel* panelRightSide;

	wxStaticText* textStatic;
	wxStaticText* textStaticMembers;
	wxListBox* listboxMembers;
	wxTextCtrl* textFieldMember;
	wxCheckBox* checkboxMembers;
	wxButton* btn1 ;
	wxButton* btn2 ;

	wxStaticText* textStatic2 ;
	wxStaticText* textStaticTasks ;
	wxListBox* listboxTasks ;
	wxTextCtrl* textFieldTask ;
	wxCheckBox* checkboxTasks ;
	wxButton* btn3;
	wxButton* btn4 ;

	wxStaticText* textStatic3;
	wxListBox* listboxProperties;
	wxButton* btn5;

	void OnButtonClicked(wxCommandEvent& evt);
	void OnKeyEvent(wxKeyEvent& evt);
};

