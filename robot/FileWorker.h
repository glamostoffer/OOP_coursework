#pragma once
#ifndef FILEWORKER_H
#define FILEWORKER_H
#include "Based.h"

class FileWorker : public Based//����� ��� ������� �������� ����� � ������������ ��������� �����������
{
private:
	FILE* p_file;
public:
	FileWorker(Based* p_obj, string name = "");
	void signalMethod(string& message);
	void handlerMethod(string message);
	void creatingFile();
	FILE* getFile();
};
#endif