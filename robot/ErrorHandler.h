#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include "Based.h"
class ErrorHandler : public Based
{
public:
	ErrorHandler(Based* p_obj, string name = "");
	void handlerMethod(string message);
};
#endif