#include <iostream>
#include <cstdio>
#include "Based.h"
#include "System.h"

int main()
{
	System* p_sys = new System(nullptr, "system");
	p_sys->print_tree_objects();
	return(p_sys->execApp());
}