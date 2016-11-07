#ifndef FRAME_DATA_HPP
#define FRAME_DATA_HPP

#include <qstring.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
using namespace std;

class FrameData
{
public:
	static bool getFrameSize(QString displayKind, int &width, int &height);
	static QString getFrameLoader(QString frameNo);
	static const int maxOfModeNumInFrame;

private:
	static const QString displaySize;
	static const QString displayFrame;
};

#endif