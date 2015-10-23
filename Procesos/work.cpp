#include "work.h"

std::deque<Proceso*> Work::inserta(std::string texto)
{
	std::deque<Proceso*> procesos;
	std::fstream archivo;
	archivo.open(texto, std::fstream::in);
	archivo >> quantum;
	archivo.ignore(1, '\n');

	
	while (!archivo.eof())
	{
		std::string nombre;
		float arrival;
		float burst;
		archivo >> nombre;
		if (nombre == "" || nombre == " ")
		{
			break;
		}
		archivo >> arrival;
		archivo >> burst;
		Proceso * procesoTemp = new Proceso(nombre, arrival, burst, false, 0.0);
		procesos.push_back(procesoTemp);
	}
	return procesos;
}

bool Work::comparaArrival(Proceso* a, Proceso* b)
{
	/*if (a->getArrival() == b->getArrival())
	{
		return a->getBurst() < b->getBurst();
	}
	else
	{*/
		return a->getArrival() < b->getArrival();
	//}
}

bool Work::comparaBurst(Proceso* a, Proceso* b)
{
	if (a->getRemaining() == b->getRemaining())
	{
		return a->getArrival() < b->getArrival();
	}
	else
	{
		return a->getRemaining() < b->getRemaining();
	}
}

bool Work::comparaNombre(Proceso* a, Proceso* b)
{
	return a->getName() < b->getName();
}

Work::Work()
{

}

void Work::print(std::deque<Proceso*> procesos)
{
	std::cout << quantum << std::endl;
	for (auto i : procesos)
	{
		std::cout << " " << i->getName() << " " << i->getArrival() << " " << i->getRemaining() <<  std::endl;
	}
}

void Work::SJF(std::deque<Proceso*> procesos)
{
	float tiempoActual = procesos[0]->getArrival();
	float espera = 0;
	float temp;
	size_t i = 0;
	std::vector<std::string> nombre;
	std::vector<float> duracion;
	std::vector<Proceso*> wait;
	std::deque<Proceso*> queueProcesos;
	Proceso * procesoTemp = new Proceso();
	Proceso * procesoActual = new Proceso();
	while (i != -1)
	{
		/*std::cout << std::endl;
		this->print(queueProcesos);*/
		if (queueProcesos.empty())
		{
			procesoActual = procesos[0];
			procesos.pop_front();
			//queueProcesos.push_back(procesoActual);
		}
		else
		{
			std::sort(queueProcesos.begin(), queueProcesos.end(), this->comparaBurst);
			procesoActual = queueProcesos[0];
			queueProcesos.pop_front();
		}
		if (!procesos.empty() && procesoActual->getRemaining() + tiempoActual > procesos[0]->getArrival())
		{
			procesoTemp = procesos[0];
			temp = procesoActual->getRemaining();
			procesos.pop_front();
			procesoActual->setRemaining(procesoActual->getRemaining() - (procesoTemp->getArrival() - tiempoActual));
			tiempoActual += procesoTemp->getArrival() - tiempoActual;
			nombre.push_back(procesoActual->getName());
			duracion.push_back(temp - procesoActual->getRemaining());
			for (int j = 0; j < queueProcesos.size(); j++)
			{
				queueProcesos[j]->setWait(temp - procesoActual->getRemaining());
			}
			queueProcesos.push_back(procesoTemp);
			queueProcesos.push_back(procesoActual);
			std::sort(queueProcesos.begin(), queueProcesos.end(), this->comparaBurst);
		}
		/*else if (!procesos.empty() && procesoActual->getRemaining() + tiempoActual < procesos[0]->getArrival())
		{
			tiempoActual += procesoActual->getRemaining();
			for (int j = 0; j < queueProcesos.size(); j++)
			{
				queueProcesos[j]->setWait(procesoActual->getRemaining());
			}
			nombre.push_back(procesoActual->getName());
			duracion.push_back(procesoActual->getRemaining());
		}*/
		else
		{
			tiempoActual += procesoActual->getRemaining();
			for (int j = 0; j < queueProcesos.size(); j++)
			{
				queueProcesos[j]->setWait(procesoActual->getRemaining());
			}
			nombre.push_back(procesoActual->getName());
			duracion.push_back(procesoActual->getRemaining());
			wait.push_back(procesoActual);
		}
		if (procesos.empty() && queueProcesos.empty())
		{
			i = -1;
		}
	}
	int pos = 0;
	std::cout << "Shortest Job first" << std::endl;
	for (auto j : nombre)
	{
		std::cout << "Nombre: "  << j << " " << "tiempo: " << duracion[pos++] << " | " << std::flush;
	}
	std::cout << std::endl;
	std::cout << "Tiempos de espera" << std::endl;
	std::sort(wait.begin(), wait.end(), this->comparaNombre);
	for (auto j : wait)
	{
		std::cout << j->getName() << " " << j->getWait() << std::endl;
		espera += j->getWait();
	}
	espera = espera / (wait.size());
	std::cout << "Espera Promedio: " << espera << std::endl;
}

void Work::roundRobin(std::deque<Proceso*> procesos)
{
	float tiempoActual = procesos[0]->getArrival();
	float espera = 0;
	float temp;
	size_t i = 0;
	std::vector<std::string> nombre;
	std::vector<float> duracion;
	std::vector<Proceso*> wait;
	std::deque<Proceso*> queueProcesos;
	Proceso * procesoTemp = new Proceso();
	Proceso * procesoActual = new Proceso();
	
	while (i != -1)
	{
		if (queueProcesos.empty())
		{
			procesoActual = procesos[0];
			procesos.pop_front();
		}
		else
		{
			procesoActual = queueProcesos[0];
			queueProcesos.pop_front();
		}
		if (procesoActual->getRemaining() > quantum)
		{
			for (int j = 0; j < queueProcesos.size(); j++)
			{
				queueProcesos[j]->setWait(quantum);
			}
			for (int j = 0; j < procesos.size(); j++)
			{
				if (procesos[j]->getArrival() <= tiempoActual + quantum)
				{
					procesoTemp = procesos[j];
					procesoTemp->setWait(quantum - (procesoTemp->getArrival() - tiempoActual));
					queueProcesos.push_back(procesoTemp);
					procesos.pop_front();
					j--;
				}
			}
			procesoActual->setRemaining(procesoActual->getRemaining() - quantum);
			queueProcesos.push_back(procesoActual);
			nombre.push_back(procesoActual->getName());
			duracion.push_back(quantum);
			tiempoActual += quantum;
		}
		else
		{
			for (int j = 0; j < queueProcesos.size(); j++)
			{
				queueProcesos[j]->setWait(procesoActual->getRemaining());
			}
			for (int j = 0; j < procesos.size(); j++)
			{
				if (procesos[j]->getArrival() <= tiempoActual + procesoActual->getRemaining())
				{
					procesoTemp = procesos[j];
					procesoTemp->setWait(procesoActual->getRemaining() - (procesoTemp->getArrival() - tiempoActual));
					queueProcesos.push_back(procesoTemp);
					procesos.pop_front();
					j--;
				}
			}
			nombre.push_back(procesoActual->getName());
			duracion.push_back(procesoActual->getRemaining());
			wait.push_back(procesoActual);
			tiempoActual += procesoActual->getRemaining();
		}
		if (procesos.empty() && queueProcesos.empty())
		{
			i = -1;
		}
	}
	int pos = 0;
	std::cout << "Round Robin" << std::endl;
	for (auto j : nombre)
	{
		std::cout << "Nombre: " << j << " Tiempo: " << duracion[pos++] << " | " << std::flush;
	}
	std::cout << std::endl;
	std::cout << "Tiempos de espera" << std::endl;
	std::sort(wait.begin(), wait.end(), this->comparaNombre);
	for (auto j : wait)
	{
		std::cout << j->getName() << " " << j->getWait() << std::endl;
		espera += j->getWait();
	}
	espera = espera / (wait.size());
	std::cout << "Espera Promedio: " << espera << std::endl;
}