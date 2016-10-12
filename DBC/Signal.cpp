#include "stdafx.h"
#include "Signal.h"


Signal::Signal()
{
}


Signal::~Signal()
{
}

void Signal::set_signal_name(string value)
{
	signal_name = value;
}

void Signal::set_multiplexer_indicator(int value)
{
	multiplexer_indicator = value;
}

void Signal::set_start_bit(int value)
{
	start_bit = value;
}

void Signal::set_signal_size(int value)
{
	signal_size = value;
}

void Signal::set_byte_order(string value)
{
	byte_order = value;
}

void Signal::set_value_type(string value)
{
	value_type = value;
}

void Signal::set_factor(float value)
{
	factor = value;
}

void Signal::set_offset(int value)
{
	offset = value;
}

void Signal::set_minimum(int value)
{
	minimum = value;
}

void Signal::set_maximum(int value)
{
	maximum = value;
}

void Signal::set_unit(string value)
{
	unit = value;
}

void Signal::set_receiver(string value)
{
	receiver = value;
}

string Signal::get_signal_name()
{
	return signal_name;
}

int Signal::get_multiplexer_indicator()
{
	return multiplexer_indicator;
}

int Signal::get_start_bit()
{
	return start_bit;
}

int Signal::get_signal_size()
{
	return signal_size;
}

string Signal::get_byte_order()
{
	return byte_order;
}

string Signal::get_value_type()
{
	return value_type;
}

float Signal::get_factor()
{
	return factor;
}

int Signal::get_offset()
{
	return offset;
}

int Signal::get_minimum()
{
	return minimum;
}

int Signal::get_maximum()
{
	return maximum;
}

string Signal::get_unit()
{
	return unit;
}

string Signal::get_receiver()
{
	return receiver;
}
