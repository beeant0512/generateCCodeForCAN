#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <list>
#include "Message.h"
#include <regex>
#include "afxwin.h"

using namespace std;

class DBC
{
	public:
		DBC();
		~DBC();
		string getVersion();
		void read(CString fullfile);
		void set_messages(list<Message> value);
		list<Message> get_messages();
	private:
		string version;
		list<Message> messages;
};

