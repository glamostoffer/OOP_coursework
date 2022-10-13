#include "System.h"
#include "Based.h"
#include "FileWorker.h"
#include "CommandHandler.h"
#include "Move.h"
#include "Writer.h"
#include "ErrorHandler.h"
#include "ConsoleOut.h"
#include <iostream>

System::System(Based* p_obj, string name) : Based(p_obj, name)
{
	this->class_num = 1;
}

void System::print_tree_objects()
{
	new FileWorker(this, "file_worker");
	new CommandHandler(this, "command_handler");
	new Move(this, "movement");
	new Writer(searchByName("movement"), "write");
	new ErrorHandler(this, "error_handler");
	new ConsoleOut(this, "cout");

	Based* signal_obj, * handler_obj;
	signal_obj = this;
	handler_obj = searchByName("command_handler");
	signal_obj->setConnection(SIGNAL_D(System::signalMethod), handler_obj, HANDLER_D(CommandHandler::handlerMethod));
	signal_obj = searchByName("movement");
	handler_obj = searchByName("error_handler");
	signal_obj->setConnection(SIGNAL_D(Move::signalMethod), handler_obj, HANDLER_D(ErrorHandler::handlerMethod));
	signal_obj = searchByName("write");
	signal_obj->setConnection(SIGNAL_D(Writer::signalMethod), handler_obj, HANDLER_D(ErrorHandler::handlerMethod));
	signal_obj = searchByName("command_handler");
	handler_obj = searchByName("write");
	signal_obj->setConnection(SIGNAL_D(CommandHandler::signalMethodInput), handler_obj, HANDLER_D(Writer::handlerMethod));
	handler_obj = searchByName("movement");
	signal_obj->setConnection(SIGNAL_D(CommandHandler::signalMethodInput), handler_obj, HANDLER_D(Move::handlerMethod));
	handler_obj = searchByName("cout");
	signal_obj->setConnection(SIGNAL_D(CommandHandler::signalMethodInput), handler_obj, HANDLER_D(ConsoleOut::handlerMethod));
	handler_obj = searchByName("error_handler");
	signal_obj->setConnection(SIGNAL_D(CommandHandler::signalMethodError), handler_obj, HANDLER_D(ErrorHandler::handlerMethod));
	handler_obj = this;
	signal_obj->setConnection(SIGNAL_D(CommandHandler::signalMethodInput), handler_obj, HANDLER_D(System::handlerMethod));
	//создание остальных объектов, учитывая иерархию
	//засунуть потом в обработку команды "SHOWTREE":
	//    printReadyTree();
	//    exit(0);
}

int System::execApp()
{
	Based* signal_obj;
	string message = "";

	setReadyForAll(1);
	signal_obj = searchByName("file_worker");
	(((FileWorker*)signal_obj)->creatingFile());

	int i = 9;
	while (getReady()) {
		emitSignal(SIGNAL_D(System::signalMethod), message);
	}
	//emitSignal(SIGNAL_D(System::signalMethod), command);
	return 0;
}
void System::signalMethod(string& message)
{
}
void System::handlerMethod(string message)
{
	//cout << message << '\n';
	if (message == "END")
	{
		setReady(0);
	}
}
