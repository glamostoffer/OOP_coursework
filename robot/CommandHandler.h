#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include "Based.h"
class CommandHandler : public Based
{
public:
	CommandHandler(Based* p_obj, string name = "");
	void signalMethodInput(string& message);
	void signalMethodError(string& message);
	void handlerMethod(string command);
};
#endif