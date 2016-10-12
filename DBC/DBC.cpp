// DBC.cpp : 实现文件
//

#include "stdafx.h"
#include "DBC.h"

#include "afxdialogex.h"
#include <fstream>
#include <sys/types.h>
#include <cstdlib>
#include "spdlog/spdlog.h"

string REG_VERSION = "^VERSION\\s*\"([\\w\\-\\.]*)\"$";
string REG_MESSAGE = "^BO_\\s*(\\d*)\\s*(\\w*)\\:\\s*(\\d*)\\s*(\\w*)$";
string REG_SIGNAL = "^\\s+SG_\\s+(\\w*)\\s+(\\w*):\\s+(\\d*)\\|(\\d*)\\@(\\d*)(\\+|\\-)\\s+\\(([\\d\\.\\-]*)\\,([\\d\\.\\-]*)\\)\\s+\\[([\\d\\.\\-]*)\\|([\\d\\.\\-]*)\\]\\s+\"([\\W\\w]*)\"\\s+(\\w*)\\s*$";

using namespace std;
namespace spd = spdlog;

DBC::DBC()
{
}


DBC::~DBC()
{
}

string DBC::getVersion() {
	return version;
}

void DBC::read(CString fullfile) {
	ifstream file;
	string line = "";
	list<Message> messages;
	Message message;
	regex reg_version(REG_VERSION);
	regex reg_message(REG_MESSAGE);
	regex reg_signal(REG_SIGNAL);

	smatch sm;
	bool is_version = false;
	bool is_message = false;
	bool is_signal = false;
	bool is_new_message = false;
	string tmp;
	file.open(fullfile);
	if (!file) {
		cout << "DBC文件不存在" << endl;
	}

	if (file) {
		while (getline(file, line))
		{
			is_version = regex_match(line, sm, reg_version);
			if (is_version) {
				version = sm[1];
				continue;
			}

			is_message = regex_match(line, sm, reg_message);
			if (is_message) {
				tmp = sm[1];
				message.set_message_id(atoi(tmp.c_str()));
				message.set_message_name(sm[2]);

				tmp = sm[3];
				message.set_message_size(atoi(tmp.c_str()));

				Signal signal;
				list<Signal> signals;
				while (getline(file, line)) {
					is_signal = regex_match(line, sm, reg_signal);
					if (is_signal) {
						signal.set_signal_name(sm[1]);
						tmp = sm[2];
						signal.set_multiplexer_indicator(atoi(tmp.c_str()));
						tmp = sm[3];
						signal.set_start_bit(atoi(tmp.c_str()));

						tmp = sm[4];
						signal.set_signal_size(atoi(tmp.c_str()));

						signal.set_byte_order(sm[5]);
						signal.set_value_type(sm[6]);

						tmp = sm[7];
						signal.set_factor(atof(tmp.c_str()));

						tmp = sm[8];
						signal.set_offset(atoi(tmp.c_str()));

						tmp = sm[9];
						signal.set_minimum(atoi(tmp.c_str()));

						tmp = sm[10];
						signal.set_maximum(atoi(tmp.c_str()));

						signal.set_unit(sm[11]);
						signal.set_receiver(sm[12]);
						signals.push_back(signal);
						continue;
					}
					message.set_signals(signals);
					break;
				}
				messages.push_back(message);
				continue;
			}



		}
	}
	set_messages(messages);
	file.close();
}

void DBC::set_messages(list<Message> value)
{
	messages = value;
}

list<Message> DBC::get_messages()
{
	return messages;
}

/*
void main() {


	DBC dbc;
	dbc.read("D:\\Beeant\\Desktop\\ZLG_CAN\\Demo\\Demo\\C204.dbc");
	string version = dbc.getVersion();
	cout << "Version : " << version << endl;
	cout << endl;

	int i = 0;
	while (i < 10000) {
		try
		{

			auto rotating_logger = spd::rotating_logger_mt("some_logger_name", "logs/mylogfile", 1048576 * 10, 3);
			for (int i = 0; i < 1000000; ++i)
				rotating_logger->info("{} * {} equals {:>10}", i, i, i*i);

		}
		catch (const spd::spdlog_ex& ex)
		{
			std::cout << "Log failed: " << ex.what() << std::endl;
		}
		i++;
	}

}
*/