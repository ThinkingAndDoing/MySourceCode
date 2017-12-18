#include "gettable.h"

int main()
{
	GetTable atable;
	atable.Read("Data.lst");
	atable.Write("maxmin.csv","max.csv","especial.csv");
	return 0;
}