#include "Based.h"

using namespace std;

Based::Based(Based* p_obj, string name)
{
	this->name = name;
	parent_obj = p_obj;
	if (p_obj)
		p_obj->subord_obj.push_back(this);
}

void Based::setName(string name)
{
	this->name = name;
}
string Based::getName()
{
	return name;
}
void Based::printBase()
{
	if (!parent_obj) cout << name;
	if (subord_obj.size() != 0) {
		cout << endl << name;
		for (int i = 0; i < subord_obj.size(); i++) {
			cout << "  " << subord_obj[i]->getName();
		}
		subord_obj[subord_obj.size() - 1]->printBase();
	}
}
void Based::setParent(Based* parent)
{
	if (parent_obj && parent) {
		for (int i = 0; i < parent_obj->subord_obj.size(); i++) {
			if (parent_obj->subord_obj[i] == this) {
				parent_obj->subord_obj.erase(parent_obj->subord_obj.begin() + i);
				break;
			}
		}
		parent_obj = parent;

		parent->subord_obj.push_back(this);
	}
}
Based* Based::getParent()
{
	return parent_obj;
}
void Based::printTree(int level)
{
	cout << getName();
	for (int i = 0; i < subord_obj.size(); i++) {
		cout << endl;
		for (int j = 0; j < level; j++) cout << " ";
		subord_obj[i]->printTree(level + 4);
	}
}
void Based::printReadyTree(int level)
{
	cout << getName();
	if (ready != 0) cout << " is ready";
	else cout << " is not ready";
	for (int i = 0; i < subord_obj.size(); i++) {
		cout << endl;
		for (int j = 0; j < level; j++) {
			cout << " ";
		}
		subord_obj[i]->printReadyTree(level + 4);
	}
}
int Based::getReady()
{
	return ready;
}
void Based::setReady(int ready)
{
	if ((parent_obj == nullptr) || (parent_obj != nullptr && parent_obj->getReady() != 0)) {
		if (ready == 0) {
			for (int i = 0; i < subord_obj.size(); i++) {
				subord_obj[i]->setReady(0);
			}
		}
		this->ready = ready;
	}
}
Based* Based::searchByName(string name)
{
	if (this->name == name) {
		return this;
	}
	for (int i = 0; i < subord_obj.size(); i++) {
		Based* child = subord_obj[i]->searchByName(name);
		if (child != nullptr) return child;
	}
	return nullptr;
}
Based* Based::searchByCoord(string coord)
{
	if (coord == "") return nullptr;
	Based* cur_obj = this;
	string name;
	if (coord == ".") return this;//по условию возрващаем текущий, если получили "."
	if (coord[0] == '/') {
		while (cur_obj->getParent() != nullptr) cur_obj = cur_obj->getParent();//доходим до корневого объекта
		if (coord == "/") return cur_obj;//возвращаем его по требованию команды
		if (coord[0] == '/' && coord[1] == '/') {//по третьему типу команды ищем объект по имени от корневого
			name = coord.substr(2);
			return cur_obj->searchByName(name);//возвращаем указатель на объект, найденный по имени
		}
	}
	for (int i = (coord[0] == '/' ? 1 : 0); i <= coord.length(); i++) {
		if (i == coord.length() || coord[i] == '/') {
			Based* obj = nullptr;
			for (int j = 0; j < cur_obj->subord_obj.size(); j++) {//проходимся по подчинённым объектам
				if ((cur_obj->subord_obj[j])->getName() == name) {//если имя j-го подчинённого объекта равно имени искомого
					obj = cur_obj->subord_obj[j];//присваиваем локальному указателю значение указателя этого подчинённого объека
					break;
				}
			}
			cur_obj = obj;
			if (cur_obj == nullptr) return cur_obj;//возвращаем nullptr если не нашли такой объект
			name = "";
		}
		else name += coord[i];
	}
	return cur_obj;
}
void Based::setConnection(TYPE_SIGNAL signal_method, Based* handler, TYPE_HANDLER handler_method) {
	for (int i = 0; i < connections.size(); i++) {//цикл для исключения повторного установления связи
		if (connections[i].signalMethod == signal_method && connections[i].handlerMethod == handler_method) return;
	}
	connections_struct connection;
	connection.signalMethod = signal_method;
	connection.handler = handler;
	connection.handlerMethod = handler_method;
	connections.push_back(connection);
}
void Based::deleteConnection(TYPE_SIGNAL signal_method, Based* handler, TYPE_HANDLER handler_method) {
	for (int i = 0; i < connections.size(); i++) {
		if (connections[i].signalMethod == signal_method && connections[i].handlerMethod == handler_method) {
			connections.erase(connections.begin() + i);
			return;
		}
	}
}
void Based::emitSignal(TYPE_SIGNAL signal_method, string& message) {
	if (getReady() == 0) return;//если сигнала нет если готовность объекта = 0 или нет связных объектов
	if (connections.empty()) return;
	(this->*signal_method)(message);
	for (int i = 0; i < connections.size(); i++) {
		if (connections[i].signalMethod == signal_method && connections[i].handler->getReady() != 0) {
			(connections[i].handler->*(connections[i].handlerMethod))(message);
		}
	}
}
string Based::getAbsolutePath(string absolute_path) {
	if (parent_obj == nullptr) return "/";//если текущий объект - корневой
	return parent_obj->getAbsolutePath("/") + name + absolute_path;
}
int Based::getClassNum() {
	return class_num;
}
void Based::setReadyForAll(int ready) {
	this->setReady(ready);
	for (int i = 0; i < subord_obj.size(); i++) {
		subord_obj[i]->setReadyForAll(ready);
	}
}
Based::~Based()
{
	for (int i = 0; i < subord_obj.size(); i++) {
		delete subord_obj[i];
	}
}