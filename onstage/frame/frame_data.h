#ifndef FRAME_DATA_HPP
#define FRAME_DATA_HPP

#include <qstring.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
using namespace std;

class FrameData
{
public:
	static void getDisplaySize(QString displayKind, int &width, int &height);
	static QString getFrameLoader(QString frameNo);
	static int maxOfModeNumInFrame;

private:
	static const QString displaySize;
	static const QString displayFrame;
};

#endif