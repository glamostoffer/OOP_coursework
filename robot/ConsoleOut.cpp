#include "ConsoleOut.h"
#include "FileWorker.h"

ConsoleOut::ConsoleOut(Based* p_obj, string name) : Based(p_obj, name) { this->class_num = 7; }

void ConsoleOut::handlerMethod(string message)
{
	if (message == "END") {
		Based* cur = this;
		char str[100];
		Based* p_worker = ((cur->getParent())->searchByName("file_worker"));//ищем указатель на объект, формирующий файл
		FILE* p_file = (((FileWorker*)p_worker)->getFile());//получаем указатель на файл
		fseek(p_file, 0, SEEK_SET);//курсор ставим в начальное положение, чтобы корректно считать файл
		while (fgets(str, 100, p_file) != NULL) {//вывод строк, пока не дойдём до конца файла
			cout << str;
		}
		fclose(p_file);
	}
}