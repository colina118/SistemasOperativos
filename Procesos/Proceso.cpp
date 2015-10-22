#include "Proceso.h"

Proceso::Proceso(std::string _nombre, float _arrival, float _burst, bool _finished, float _wait) : name(_nombre), arrival(_arrival), burst(_burst), finished(_finished), wait(_wait) { timeRemaining = _burst; }

Proceso::Proceso()
{

}

std::string Proceso::getName()
{
	return name;
}
float Proceso::getArrival()
{
	return arrival;
}
float Proceso::getWait()
{
	return wait;
}
float Proceso::getBurst()
{
	return burst;
}
float Proceso::getRemaining()
{
	return timeRemaining;
}
bool Proceso::getFinished()
{
	return finished;
}

void Proceso::setRemaining(float _remaining)
{
	timeRemaining = _remaining;
}
void Proceso::setFinished(bool _finished)
{
	finished = _finished;
}
void Proceso::setWait(float _wait)
{
	wait += _wait;
}
bool Proceso::operator<(const Proceso & p)const 
{
	return this->burst < p.burst; 
}
bool Proceso::operator>(const Proceso & p)const
{ 
	return this->burst > p.burst; 
}
bool Proceso::operator==(const Proceso & p)const 
{ 
	return this->burst == p.burst; 
}
bool Proceso::operator>=(const Proceso & p)const 
{ 
	return this->burst >= p.burst;
}
bool Proceso::operator<=(const Proceso & p)const 
{ 
	return this->burst <= p.burst;
}