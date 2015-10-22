#pragma once
#include "Proceso.h"
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

class Work
{
private:
	
public:
	float quantum;
	std::deque<Proceso*> inserta(std::string texto);
	void print(std::deque<Proceso*>);
	static bool comparaArrival(Proceso*, Proceso*);
	static bool comparaBurst(Proceso*, Proceso*);
	static bool comparaNombre(Proceso*, Proceso*);
	void SJF(std::deque<Proceso*>);
	void roundRobin(std::deque<Proceso*>);
	Work();
};