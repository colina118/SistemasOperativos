#include "work.h"
#include <algorithm>
#include <functional>

//struct {
//	bool operator()(Proceso* a, Proceso* b)
//	{
//		return a->getArrival() < b->getArrival();
//	}
//} customLess;

int main()
{
	std::deque<Proceso*> procesos;
	Work archivo;
	procesos = archivo.inserta("texto.txt");
	std::sort(procesos.begin(), procesos.end(), archivo.comparaArrival);
	archivo.print(procesos);
	archivo.roundRobin(procesos);
	//archivo.SJF(procesos);
}