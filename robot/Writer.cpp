#include "Writer.h"
#include "FileWorker.h"
#include "System.h"
#include "Move.h"

Writer::Writer(Based* p_obj, string name) :Based(p_obj, name) { this->class_num = 5; }

void Writer::signalMethod(string& message)
{
	//message += (string)"\n";
}
void Writer::handlerMethod(string message)
{
	stringstream ss(message);
	char delimeter = ' ';
	string item;
	vector<string> splittedStrings;
	while (getline(ss, item, delimeter)) {
		splittedStrings.push_back(item);
	}
	if (splittedStrings[0] == "WRITE") {
		const char* cstr = splittedStrings[1].c_str();
		robotWrite(cstr[0]);
	}
}
void Writer::robotWrite(char symb)
{
	string str;
	Based* cur = this->getParent();
	Based* p_worker = ((cur->getParent())->searchByName("file_worker"));//ищем указатель на объект, формирующий файл
	FILE* p_file = (((FileWorker*)p_worker)->getFile());//получаем указатель на файл
	p_worker = ((cur->getParent())->searchByName("movement"));
	if (!isalpha(symb)) {
		str = "\nThe letter does not belong to the Latin alphabet: ";//не выводит в файл сам, а выдаёт сигнал об ошибке
		str += symb;
		emitSignal(SIGNAL_D(Writer::signalMethod), str);
	}
	else if (((Move*)p_worker)->getCoordinates()->current_coord == ((Move*)p_worker)->getCoordinates()->prev_coord) {
		str = "\nAttempt to sequentially write to a cell ( " + to_string(((Move*)p_worker)->getCoordinates()->row) + ", " + to_string(((Move*)p_worker)->getCoordinates()->col) + " )";
		emitSignal(SIGNAL_D(Writer::signalMethod), str);
	}
	else {
		fputc(symb, p_file);
		((Move*)p_worker)->getCoordinates()->prev_coord = ((Move*)p_worker)->getCoordinates()->current_coord;
		((Move*)p_worker)->getCoordinates()->current_coord = ((Move*)p_worker)->getCoordinates()->col + ((Move*)p_worker)->getCoordinates()->row;
	}
}