#pragma once
#include <iostream>
#include <string>

class Proceso
{
private:
	float arrival;
	float burst;
	float timeRemaining;
	float wait;
	bool finished;
	std::string name;
public:
	Proceso();
	Proceso(std::string, float, float, bool, float);

	std::string getName();
	float getArrival();
	float getWait();
	float getBurst();
	float getRemaining();
	bool getFinished();

	void setRemaining(float);
	void setFinished(bool);
	void setWait(float);

	bool operator<(const Proceso & p) const;
	bool operator>(const Proceso & p) const;
	bool operator==(const Proceso & p) const;
	bool operator>=(const Proceso & p) const;
	bool operator<=(const Proceso & p) const;

};