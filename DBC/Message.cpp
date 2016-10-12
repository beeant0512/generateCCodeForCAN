#include "stdafx.h"
#include "Message.h"


Message::Message()
{
}


Message::~Message()
{
}

int Message::get_message_id()
{
	return message_id;
}

string Message::get_message_name()
{
	return message_name;
}

int Message::get_message_size()
{
	return message_size;
}

string Message::get_transmitter()
{
	return transmitter;
}

list<Signal> Message::get_signals()
{
	return signals;
}

void Message::set_message_id(int value)
{
	message_id = value;
}

void Message::set_message_name(string value)
{
	message_name = value;
}

void Message::set_message_size(int value)
{
	message_size = value;
}

void Message::set_transmitter(string value)
{
	transmitter = value;
}

void Message::set_signals(list<Signal> value)
{
	signals = value;
}
