#ifndef MOVE_H
#define MOVE_H
#include "Based.h"
class Move : public Based
{
private:
	struct coordinates{
		int col = 0;
		int row = 0;
		int current_coord = 0;
		int prev_coord = 0;
	};
	coordinates* p_struct;
public:
	Move(Based* p_obj, string name = "");
	void signalMethod(string& message);
	void handlerMethod(string message);
	void robotMoving(int row, int col);
	coordinates* getCoordinates();
};
#endif