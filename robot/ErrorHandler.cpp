#include "ErrorHandler.h"
#include "FileWorker.h"
#include "Move.h"

ErrorHandler::ErrorHandler(Based* p_obj, string name) :Based(p_obj, name) { this->class_num = 6; }

void ErrorHandler::handlerMethod(string error)
{
	Based* cur = this;
	Based* p_worker = ((cur->getParent())->searchByName("file_worker"));//ищем указатель на объект, формирующий файл
	FILE* p_file = (((FileWorker*)p_worker)->getFile());//получаем указатель на файл
	const char* cstr = error.c_str();
	fseek(p_file, 0, SEEK_END);//добавляем в конец файла сообщение об ошибке
	fputs(cstr, p_file);
	p_worker = ((cur->getParent())->searchByName("movement"));
	fseek(p_file, (((Move*)p_worker)->getCoordinates()->row - 1) * 12 + (((Move*)p_worker)->getCoordinates()->col) - 1, SEEK_SET);
	/*((Move*)p_worker)->getCoordinates()->prev_coord = ((Move*)p_worker)->getCoordinates()->current_coord;
		((Move*)p_worker)->getCoordinates()->current_coord = ((Move*)p_worker)->getCoordinates()->col + ((Move*)p_worker)->getCoordinates()->row;*/
}