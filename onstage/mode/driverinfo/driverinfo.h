#ifndef DRIVERINFO_H
#define DRIVERINFO_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "driverinfoDB.h"

using namespace std;

class Driverinfo :public ModeBase
{
public:
	Driverinfo(QString modeID, QObject *loader) :ModeBase(modeID, driverinfoDB, loader) {};
	static Driverinfo *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Driverinfo(modeID, loader);
		return it;
	};
	

private:
	static Driverinfo *it;
};

Driverinfo *Driverinfo::it = NULL;

#endif // !DRIVERINFO_H 