#pragma once

#include <string>
#include <list>
#include "Signal.h"

using namespace std;

class Message
{
public:
	Message();
	~Message();
	int get_message_id();
	string get_message_name();
	int get_message_size();
	string get_transmitter();
	list<Signal> get_signals();
	void set_message_id(int message_id);
	void set_message_name(string message_name);
	void set_message_size(int message_size);
	void set_transmitter(string transmitter);
	void set_signals(list<Signal> signals);
private:
	int message_id;
	string message_name;
	int message_size;
	string transmitter;
	list<Signal> signals;
};

