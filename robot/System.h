#ifndef __SYSTEM_H
#define __SYSTEM_H
#include "Based.h"

using namespace std;

class System : public Based//класс  для объекта "система"
{
public:
	System(Based* p_obj, string name = "");
	void print_tree_objects();
	int execApp();
	void signalMethod(string& message);
	void handlerMethod(string message);
	Based::TYPE_SIGNAL getSignalMethod(Based* pointer);
	Based::TYPE_HANDLER getHandlerMethod(Based* pointer);
};
#endif
