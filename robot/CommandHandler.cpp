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
	command = "\nERROR command: " + parameters;//�� ������� � ���� ���, � ����� ������ �� ������
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
		emitSignal(SIGNAL_D(CommandHandler::signalMethodInput), parameters);//����� ������� ������� ��� ������������
	}
	else if (command == "WRITE") {
		cin >> parameters;
		parameters = command + ' ' + parameters;
		//cout << parameters << "/n";
		emitSignal(SIGNAL_D(CommandHandler::signalMethodInput), parameters);//����� ������� ������� ��� ������ �������
	}
	else if (command == "END") {
		emitSignal(SIGNAL_D(CommandHandler::signalMethodInput), command);
	}
	else if (command == "SHOWTREE") {
		(cur->getParent())->printReadyTree();
		exit(0);
	}
	else {//������ ������ �� ������ ������, ������� ������� �� ������ ���������
		//����� ������� � ������� ��� ������� ������ ������
		emitSignal(SIGNAL_D(CommandHandler::signalMethodError), command);
	}
}