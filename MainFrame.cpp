#include "MainFrame.h"
#include "Task.h"
#include "Member.h"
#include <wx/wx.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)	{
	
	CreateControls();
	CreateStatusBar();

	BindEventHandlers();
}

void delay(int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
	wxLogStatus("Created by: Martin Švanda						P.S.: Im looking for job so please write me to martin.k.svanda@gmail.com"); // Log the status
}

void MainFrame::OnKeyEvent(wxKeyEvent& evt) {
	if (evt.GetKeyCode() == WXK_TAB) {
		wxWindow* myWin = (wxWindow*)evt.GetEventObject(); // Get the window that triggered the even
		myWin->Navigate(); // Navigate to the next window)
	}
}

void MainFrame::OnButtonClicked(wxCommandEvent& evt) {
	wxString nameTextMember = wxString::Format("%s", textFieldMember->GetValue()); // Get the text from the text box and store it in a string;
	wxString nameTextTask = wxString::Format("%s", textFieldTask->GetValue()); // Get the text from the text box and store it in a string
	wxLogStatus("Family Member with name : " + nameTextMember + " has been added"); // Log the status
	wxLogStatus("Family Member with name : " + nameTextTask + " has been added"); // Log the status
	std::thread delayThread(delay, 3); // 3 seconds
	delayThread.detach(); // Detach the thread
}

void MainFrame::CreateControls()
{
	const int windowHeight = 800;
	const int windowWidth = 1500;

	const int buttonHeight = 30;
	const int buttonWidth = 130;

	wxString nameTextMember;
	wxString nameTextTask;

	panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(windowWidth, windowHeight));

	panelLeftSide = new wxPanel(panel, wxID_ANY, wxPoint(0, 0), wxSize(windowWidth / 5, windowHeight - 40));
	panelMidSide = new wxPanel(panel, wxID_ANY, wxPoint(windowWidth / 5, 0), wxSize((windowWidth / 5), windowHeight - 40));
	panelRightSide = new wxPanel(panel, wxID_ANY, wxPoint((windowWidth / 5) * 2, 0), wxSize((windowWidth / 5) * 3, windowHeight - 40));

	//PANEL 1	*panelLeftSide*
	textStatic = new wxStaticText(panelLeftSide, wxID_ANY, "Members", 
		wxPoint(30, 30), wxSize(windowWidth - 300, 30));
	listboxMembers = new wxListBox(panelLeftSide, wxID_ANY, wxPoint(30, 70), 
		wxSize((windowWidth / 5) - 40, windowHeight - 260));
	textStaticMembers = new wxStaticText(panelLeftSide, wxID_ANY, "Name", 
		wxPoint(30, windowHeight - 190), wxSize(100, 30));
	textFieldMember = new wxTextCtrl(panelLeftSide, wxID_ANY, nameTextMember, 
		wxPoint(30, windowHeight - 160), wxSize(100, 30), wxTE_PROCESS_ENTER);
	checkboxMembers = new wxCheckBox(panelLeftSide, wxID_ANY, "Is that Member Adult", 
		wxPoint(windowWidth / 5 - 130, windowHeight - 160), wxSize(130, 30));
	btn1 = new wxButton(panelLeftSide, wxID_ANY, "Add Family Member", 
		wxPoint(30, windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	btn2 = new wxButton(panelLeftSide, wxID_ANY, "Delete Family Member", 
		wxPoint((windowWidth / 5) - (buttonWidth + 10), windowHeight - 100), wxSize(buttonWidth, buttonHeight));

	//PANEL 2	*panelMidSide*
	btn3 = new wxButton(panelMidSide, wxID_ANY, "Add House Work", 
		wxPoint(30, windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	textStatic2 = new wxStaticText(panelMidSide, wxID_ANY, "Tasks", 
		wxPoint(30, 30), wxSize(windowWidth - 300, 30));
	textStaticTasks = new wxStaticText(panelMidSide, wxID_ANY, "Work what you want include tu Planer", 
		wxPoint(30, windowHeight - 190), wxSize(windowWidth / 5, 30)); 
	listboxTasks = new wxListBox(panelMidSide, wxID_ANY, 
		wxPoint(30, 70), wxSize((windowWidth / 5) - 40, windowHeight - 260));
	textFieldTask = new wxTextCtrl(panelMidSide, wxID_ANY, nameTextTask,
		wxPoint(30, windowHeight - 160), wxSize(100, 30), wxTE_PROCESS_ENTER);
	checkboxTasks = new wxCheckBox(panelMidSide, wxID_ANY, "Is this work for Adult", 
		wxPoint(windowWidth / 5 - 130, windowHeight - 160), wxSize(130, 30));
	btn4 = new wxButton(panelMidSide, wxID_ANY, "Delete House Work", 
		wxPoint((windowWidth / 5) - (buttonWidth + 10), windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	
	//PANEL 3	*panelRightSide*
	btn5 = new wxButton(panelRightSide, wxID_ANY, "Edit", 
		wxPoint(30, windowHeight - 100), wxSize(buttonWidth, buttonHeight));
	textStatic3 = new wxStaticText(panelRightSide, wxID_ANY, "Properties of Tasks", 
		wxPoint(30, 30), wxSize(windowWidth - 300, 30));
	listboxProperties = new wxListBox(panelRightSide, wxID_ANY, 
		wxPoint(30, 70), wxSize(((windowWidth / 5) * 3) - 60 , windowHeight - 260));	
}

void MainFrame::BindEventHandlers()
{	
	btn1->Bind(wxEVT_BUTTON, &MainFrame::OnAddMemberClicked, this);
	textFieldMember->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputMemberEnter, this);
	listboxMembers->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this); // For checkbox
	btn2->Bind(wxEVT_BUTTON, &MainFrame::OnDelMemberClicked, this);

	btn3->Bind(wxEVT_BUTTON, &MainFrame::OnAddTaskClicked, this);
	textFieldTask->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputTaskEnter, this);
	listboxTasks->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this); // For checkbox
	btn4->Bind(wxEVT_BUTTON, &MainFrame::OnDelTaskClicked, this);

}

void MainFrame::OnAddMemberClicked(wxCommandEvent& evt) {	
	AddMemberFromInput();
}
void MainFrame::OnDelMemberClicked(wxCommandEvent& evt) {
	DelMemberFromList();
}
void MainFrame::OnAddTaskClicked(wxCommandEvent& evt) {
	AddTaskFromInput();
}
void MainFrame::OnDelTaskClicked(wxCommandEvent& evt) {
	DelTaskFromList();
}

void MainFrame::OnInputMemberEnter(wxCommandEvent& evt) {
	AddMemberFromInput();
}
void MainFrame::OnInputTaskEnter(wxCommandEvent& evt) {
	AddTaskFromInput();
}

void MainFrame::OnListKeyDown(wxKeyEvent& evt) {
	switch (evt.GetKeyCode()) {
	case WXK_SPACE:
		DelMemberFromList();
			break;
	}
}

void MainFrame::AddMemberFromInput() {
	wxString name = textFieldMember->GetValue();

	if (!name.IsEmpty()) {
	listboxMembers->Insert( name, listboxMembers->GetCount());
	textFieldMember->Clear();// Insert the escription
	}
}
void MainFrame::DelMemberFromList() 
{
	int selectedIndex = listboxMembers->GetSelection(); // Getselected

	if (selectedIndex == wxNOT_FOUND) {
		return; // Do no
	}

	listboxMembers->Delete(selectedIndex); // Delete the selected item
}

void MainFrame::AddTaskFromInput() {	
	wxString name = textFieldTask->GetValue();
	
	if (!name.IsEmpty()) {
		listboxTasks->Insert(name, listboxTasks->GetCount());
		textFieldTask->Clear();
	}
}
void MainFrame::DelTaskFromList() 
{

}