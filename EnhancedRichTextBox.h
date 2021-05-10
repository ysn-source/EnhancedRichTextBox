#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Drawing;

/*
*  Utility Class : Last Word written
*/
public ref class LastWord {
public:
	String ^word;
	Point ^position;
	LastWord() {}
	LastWord(String^w, Point pos) {
		this->word = w;
		this->position = pos;
	}
	LastWord(String^w, int start, int end) {
		this->word = w;
		this->position = gcnew Point(start, end);
	}
	~LastWord() {}

};
/*
*  Utility Class : Keyword List
*/
public ref class KeywordList : List<String^> {
public:
	KeywordList(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
		__super::List();
	}
	KeywordList(int r, int g, int b, cli::array<String^>^ arrKeyword) {
		this->r = r;
		this->g = g;
		this->b = b;
		__super::List();
		this->AddRange(arrKeyword);
	}
	KeywordList(int r, int g, int b, List<String^>^ arrKeyword) {
		this->r = r;
		this->g = g;
		this->b = b;
		__super::List();
		this->AddRange(arrKeyword);
	}
	~KeywordList() {}
	int r, g, b;
	String ^GetColor() { return " \\red" + r + "\\green" + g + "\\blue" + b + ";"; }
};

/* 
*  Components
*/
public ref class EnhancedRichTextBox : public RichTextBox
{
public:
	EnhancedRichTextBox();
	~EnhancedRichTextBox() {}
	
	List<KeywordList^>^ Keywords;
	cli::array<wchar_t>^ Delims;
		
private:
	ListBox ^_internalListBox;
	LastWord ^_lWord;
	int _lastKeyPressed;
	cli::array<String^, 1>^ _latestRTF = gcnew cli::array<String^, 1>(4);

	/*
	*  Events : ListBox
	*/
	System::Void __Click(Object^s, EventArgs^e);
	System::Void __KeyPress(Object^s, KeyEventArgs^e);
	Void updateListBox();
	Void resetListBox();

	/* 
	*  Events : RichTextBox
	*/
	System::Void enh_TextChanged(System::Object^  sender, System::EventArgs ^e);
	System::Void enh_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

	/*
	*  String Util
	*/
	String ^buildHeaderColors();

	String ^AddColorHeaders();
	String ^AddColorHeaders(String ^rtf);
	String ^Replacer(String ^newWord, int x, int y);

	Void FilterByKey(ListBox^lb, String^srch);
	String ^WithColor(String^str);
	String ^WithColor(String^srch, bool bEndSpace);

	String ^getHeader();
	String ^getHeader(bool bWithColor);
	String ^getBody();
	String ^getClosing();
	String ^RTFSPlitter(int h);

	Point ^GetLastWord([Runtime::InteropServices::Out] String^ %s);
	Point ^GetLastWord([Runtime::InteropServices::Out] String^ %s, int before);
};
