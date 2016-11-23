#ifndef PHONE_H
#define PHONE_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "phoneDB.h"

using namespace std;

class Phone :public ModeBase
{
public:
	Phone(QString modeID, QObject *loader) :ModeBase(modeID, phoneDB, loader) {};
	static Phone *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Phone(modeID, loader);
		return it;
	};
	

private:
	static Phone *it;
};

Phone *Phone::it = NULL;

#endif // !PHONE_H 