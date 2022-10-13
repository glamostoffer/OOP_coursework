#include "FileWorker.h"

FileWorker::FileWorker(Based* p_obj, string name) :Based(p_obj, name) { this->class_num = 2; }

void FileWorker::signalMethod(string& message)
{
	cout << "\nSignal from " << getAbsolutePath();
	message += " (class: 2)";
}
void FileWorker::handlerMethod(string message)
{
	cout << "\nSignal to " << getAbsolutePath() << " Text: " << message;
}
void FileWorker::creatingFile()
{
	p_file = fopen("field.txt", "w+");//создаём файл
	if (p_file == NULL) {//при ошибки в создании выводим сообщение и завершаем работу
		cout << "File field.txt not create";
		exit(0);
	}
	for (int i = 0; i < 9; i++) {//формируем исходные данные
		fputs("8888888888\n", p_file);
	}
	fputs("8888888888", p_file);
}
FILE* FileWorker::getFile()
{
	return(p_file);
}