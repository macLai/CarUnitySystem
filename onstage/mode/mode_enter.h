#ifndef MODE_ENTER_H
#define MODE_ENTER_H

using namespace std;
#include <string>
#include <qobject.h>

class ModeEnter
{
public:
	ModeEnter(){};
	static ModeEnter *getInstance();
	void initialize();
	void updateMode(QString activeModeListStr);
private:
	static ModeEnter *it;
};

#endif MODE_ENTER_H