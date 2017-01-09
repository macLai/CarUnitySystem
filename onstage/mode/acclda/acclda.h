#ifndef ACCLDA_H
#define ACCLDA_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "accldaDB.h"

using namespace std;

class Acclda :public ModeBase
{
public:
	Acclda(QString modeID, QObject *loader) :ModeBase(modeID, accldaDB, loader) {};
	static Acclda *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Acclda(modeID, loader);
		return it;
	};
	

private:
	static Acclda *it;
};

Acclda *Acclda::it = NULL;

#endif // !ACCLDA_H 