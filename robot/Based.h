#pragma once
#ifndef BASED_H
#define BASED_H
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)//��� ��������� ��������� �� ����� ������� �������
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)//��� ��������� ��������� �� ����� ����������� �������

using namespace std;

class Based
{
public:
	typedef void(Based::* TYPE_SIGNAL)(string&);
	typedef void(Based::* TYPE_HANDLER)(string);
protected:
	int class_num;
private:
	string name;//���� ����� �������
	int ready = 0;//���� ���������� �������
	Based* parent_obj = nullptr;//��������� �� ������������ ������
	vector <Based*> subord_obj;//������ ���������� �� �������� �������
	struct connections_struct {
		TYPE_SIGNAL signalMethod;//��������� �� ����� �������
		Based* handler;//��������� �� ������ ������
		TYPE_HANDLER handlerMethod;//��������� �� ����� �����������
	};
	vector <connections_struct> connections;//������ ������ ��������
public:
	Based(Based* p_obj, string name = "");//�����������, ����� ��� � �������� ������� 
	void setName(string name);//����� ����� ��� �������
	string getName();//���������� ���
	int getReady();//����� ����������
	void setReady(int ready);//����� ����������
	void setParent(Based* parent);//����� ��������
	Based* getParent();//���������� ��������� �� ������������ ������
	void printBase();//������� ����� �������� � ����������� �������
	void printTree(int level = 4);//������� ����������� ������
	void printReadyTree(int level = 4);//������� ������ �������� � ������ �� ���������� � ����������� �������
	Based* searchByName(string name);//����� ������� �� �����
	Based* searchByCoord(string coord);//����� �� �����������
	void setConnection(TYPE_SIGNAL signal_method, Based* handler, TYPE_HANDLER handler_method);//����� �������� ����� ��� �������
	void deleteConnection(TYPE_SIGNAL signal_method, Based* handler, TYPE_HANDLER handler_method);//����� �������� ����� ��� �������
	void emitSignal(TYPE_SIGNAL signal_method, string& message);//������ ������� �������� �������
	string getAbsolutePath(string absolute_path = "");//����� ������ ����������� ����
	void setReadyForAll(int ready);//���������� ���� �������� �������� � ����������
	int getClassNum();//��������� ������ ������ �� �������� �������
	~Based();//����������, ������� ��� �������
};
#endif
