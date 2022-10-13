#pragma once
#ifndef CONSOLEOUT_H
#define CONSOLEOUT_H
#include "Based.h"
#include "System.h"

class ConsoleOut : public Based
{
public:
	ConsoleOut(Based* p_obj, string name = "");
	void handlerMethod(string message);
};
#endif