#ifndef NAVI_H
#define NAVI_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "naviDB.h"

using namespace std;

class Navi :public ModeBase
{
public:
	Navi(QString modeID, QObject *loader) :ModeBase(modeID, naviDB, loader) {};
	static Navi *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Navi(modeID, loader);
		return it;
	};
	

private:
	static Navi *it;
};

Navi *Navi::it = NULL;

#endif // !NAVI_H 