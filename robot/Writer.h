#ifndef WRITER_H
#define WRITER_H
#include "Based.h"
class Writer : public Based
{
public:
	Writer(Based* p_obj, string name = "");
	void signalMethod(string& message);
	void handlerMethod(string message);
	void robotWrite(char symb);
};
#endif