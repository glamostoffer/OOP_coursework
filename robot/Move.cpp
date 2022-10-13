#include "Move.h"
#include "FileWorker.h"
#include "System.h"

Move::Move(Based* p_obj, string name) :Based(p_obj, name) {
	this->class_num = 4;
	p_struct = new coordinates;
}

void Move::signalMethod(string& message)
{
	//message += (string)"\n";
}
void Move::handlerMethod(string message)
{
	stringstream ss(message);
	char delimeter = ' ';
	string item;
	vector<string> splittedStrings;
	while (getline(ss, item, delimeter)) {
		splittedStrings.push_back(item);
	}
	if (splittedStrings[0] == "MOVE") {
		/*string word;
		istringstream iss(message, istringstream::in);*/
		vector<string> words_vector;
		words_vector.push_back(splittedStrings[1]);
		words_vector.push_back(splittedStrings[2]);
		robotMoving(stoi(words_vector[1]), stoi(words_vector[0]));
	}
}
void Move::robotMoving(int row, int col)
{
	Based* cur = this;
	Based* p_worker = ((cur->getParent())->searchByName("file_worker"));//ищем указатель на объект, формирующий файл
	FILE* p_file = (((FileWorker*)p_worker)->getFile());//получаем указатель на файл
	if (col > 10 || col < 1 || row > 10 || row < 1) {
		string str = "\nCoordinate is wrong ( " + to_string(col) + ", " + to_string(row) + " )";//не выводит в файл сам, а выдаёт сигнал об ошибке
		emitSignal(SIGNAL_D(Move::signalMethod), str);
	}
	else {
		fseek(p_file, (col - 1) * 12 + (row - 1), SEEK_SET);//передвигаем курсор по заданным координатам(странный момент, непонятно работает)
		p_struct->prev_coord = p_struct->current_coord;
		p_struct->current_coord = col + row;
		p_struct->col = row;
		p_struct->row = col;
	}
}

Move::coordinates* Move::getCoordinates() { return p_struct; }