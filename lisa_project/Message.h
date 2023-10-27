#pragma once

#include <string>

class Message{
	int code; // 0 for success, >1 for errors
	std::string message;
	
public:
	Message(int code, std::string message);
	int getCode();
	std::string getMessage();
};
