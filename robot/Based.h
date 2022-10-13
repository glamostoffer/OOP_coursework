#pragma once
#ifndef BASED_H
#define BASED_H
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)//для получения указатель на метод сигнала объекта
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)//для получения указатель на метод обработчика объекта

using namespace std;

class Based
{
public:
	typedef void(Based::* TYPE_SIGNAL)(string&);
	typedef void(Based::* TYPE_HANDLER)(string);
protected:
	int class_num;
private:
	string name;//поле имени объекта
	int ready = 0;//поле готовности объекта
	Based* parent_obj = nullptr;//указатель на родительский объект
	vector <Based*> subord_obj;//массив указателей на дочерние объекты
	struct connections_struct {
		TYPE_SIGNAL signalMethod;//указатель на метод сигнала
		Based* handler;//указатель на второй объект
		TYPE_HANDLER handlerMethod;//указатель на метод обработчика
	};
	vector <connections_struct> connections;//массив связей объектов
public:
	Based(Based* p_obj, string name = "");//конструктор, задаёт имя и родителя объекта 
	void setName(string name);//метод задаёт имя объекта
	string getName();//возвращает имя
	int getReady();//задаёт готовность
	void setReady(int ready);//задаёт готовность
	void setParent(Based* parent);//задаёт родителя
	Based* getParent();//возвращает указатель на родительский объект
	void printBase();//выводит имена объектов в иерархичном порядке
	void printTree(int level = 4);//выводит иерархичное дерево
	void printReadyTree(int level = 4);//выводит дерево объектов и статус их готовности в иерархичном порядке
	Based* searchByName(string name);//поиск объекта по имени
	Based* searchByCoord(string coord);//поиск по координатам
	void setConnection(TYPE_SIGNAL signal_method, Based* handler, TYPE_HANDLER handler_method);//метод создание связи для сигнала
	void deleteConnection(TYPE_SIGNAL signal_method, Based* handler, TYPE_HANDLER handler_method);//метод удаления связи для сигнала
	void emitSignal(TYPE_SIGNAL signal_method, string& message);//выдача сигнала текущего объекта
	string getAbsolutePath(string absolute_path = "");//метод вывода абсолютного пути
	void setReadyForAll(int ready);//приведение всех объектов иерархии в готовность
	int getClassNum();//получение номера класса от текущего объекта
	~Based();//деструктор, удаляет все объекты
};
#endif
