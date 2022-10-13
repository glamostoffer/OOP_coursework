#include "ConsoleOut.h"
#include "FileWorker.h"

ConsoleOut::ConsoleOut(Based* p_obj, string name) : Based(p_obj, name) { this->class_num = 7; }

void ConsoleOut::handlerMethod(string message)
{
	if (message == "END") {
		Based* cur = this;
		char str[100];
		Based* p_worker = ((cur->getParent())->searchByName("file_worker"));//���� ��������� �� ������, ����������� ����
		FILE* p_file = (((FileWorker*)p_worker)->getFile());//�������� ��������� �� ����
		fseek(p_file, 0, SEEK_SET);//������ ������ � ��������� ���������, ����� ��������� ������� ����
		while (fgets(str, 100, p_file) != NULL) {//����� �����, ���� �� ����� �� ����� �����
			cout << str;
		}
		fclose(p_file);
	}
}