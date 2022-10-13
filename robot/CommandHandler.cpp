#include "CommandHandler.h"
#include "System.h"
#include "Move.h"
#include "Writer.h"
#include "ErrorHandler.h"
#include "ConsoleOut.h"

CommandHandler::CommandHandler(Based* p_obj, string name) :Based(p_obj, name) { this->class_num = 3; }

void CommandHandler::signalMethodInput(string& message)
{
	//message += (string)"\n";
}
void CommandHandler::signalMethodError(string& command)
{
	string parameters = "";
	getline(cin, parameters);
	parameters = command + parameters;
	command = "\nERROR command: " + parameters;//не выводит в файл сам, а выдаёт сигнал об ошибке
}
void CommandHandler::handlerMethod(string message)
{
	string command;
	string parameters = "";
	Based* cur = this;
	cin >> command;
	if (command == "MOVE") {
		getline(cin, parameters);
		parameters = command + parameters;
		//cout << parameters << "/n";
		emitSignal(SIGNAL_D(CommandHandler::signalMethodInput), parameters);//посыл сигнала объекту для передвижения
	}
	else if (command == "WRITE") {
		cin >> parameters;
		parameters = command + ' ' + parameters;
		//cout << parameters << "/n";
		emitSignal(SIGNAL_D(CommandHandler::signalMethodInput), parameters);//посыл сигнала объекту для записи символа
	}
	else if (command == "END") {
		emitSignal(SIGNAL_D(CommandHandler::signalMethodInput), command);
	}
	else if (command == "SHOWTREE") {
		(cur->getParent())->printReadyTree();
		exit(0);
	}
	else {//выдать сигнал об ошибке классу, который выведет об ошибке сообщение
		//посыл сигнала с ошибкой для объекта вывода ошибки
		emitSignal(SIGNAL_D(CommandHandler::signalMethodError), command);
	}
}