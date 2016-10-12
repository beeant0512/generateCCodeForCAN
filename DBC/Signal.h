#pragma once
#include <string>
#include <iostream>

using namespace std;

class Signal
{
public:
public:
	Signal();
	~Signal();
	void set_signal_name(string signal_name);
	void set_multiplexer_indicator(int multiplexer_indicator);
	void set_start_bit(int start_bit);
	void set_signal_size(int signal_size);
	void set_byte_order(string byte_order);
	void set_value_type(string value_type);
	void set_factor(float factor);
	void set_offset(int offset);
	void set_minimum(int minimum);
	void set_maximum(int maximum);
	void set_unit(string unit);
	void set_receiver(string receiver);
	string get_signal_name();
	int get_multiplexer_indicator();
	int get_start_bit();
	int get_signal_size();
	string get_byte_order();
	string get_value_type();
	float get_factor();
	int get_offset();
	int get_minimum();
	int get_maximum();
	string get_unit();
	string get_receiver();
private:
	string signal_name;
	int multiplexer_indicator;
	int start_bit;
	int signal_size;
	string byte_order;
	string value_type;
	float factor;
	int offset;
	int minimum;
	int maximum;
	string unit;
	string receiver;
};

