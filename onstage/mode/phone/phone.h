#ifndef PHONE_H
#define PHONE_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "phoneDB.h"

using namespace std;

class Phone :public ModeBase
{
public:
	Phone(QString modeID) :ModeBase(modeID, phoneDB) {};
	static Phone *getInstance(QString modeID)
	{
		if(it != NULL) return it;
		it =new Phone(modeID);
		return it;
	};
	

private:
	static Phone *it;
};

Phone *Phone::it = NULL;

#endif // !PHONE_H 