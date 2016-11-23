#include "frame_data.h"

int FrameData::maxOfModeNumInFrame = 3;

const QString FrameData::displaySize ( "{ \
		\"navi\" : {\"width\":800, \"height\" : 480, \"num\" : 3}, \
		\"meta\" : {\"width\":1024, \"height\" : 600, \"num\" : 3}, \
		\"hud\" : {\"width\":1280, \"height\" : 720, \"num\" : 0}, \
		\"DEFAULT\" : {\"width\":800, \"height\" : 480, \"num\" : 0} \
}" );

const QString FrameData::displayFrame ( "{ \
	\"navi\": \"frame/tempFrame/TempFrameNaviScreen.qml\", \
	\"meta\": \"frame/tempFrame/TempFrameMetaScreen.qml\", \
	\"hud\": \"frame/tempFrame/TempFrameHudScreen.qml\" \
}" );

void FrameData::getDisplaySize(QString displayKind, int &width, int &height)
{

	QJsonObject data = QJsonDocument::fromJson(displaySize.toUtf8()).object();
	if (data.contains(displayKind))
	{
		width = data[displayKind].toObject()["width"].toInt();
		height = data[displayKind].toObject()["height"].toInt();
		maxOfModeNumInFrame = data[displayKind].toObject()["num"].toInt();
	}
	else
	{
		width = data["DEFAULT"].toObject()["width"].toInt();
		height = data["DEFAULT"].toObject()["height"].toInt();
		maxOfModeNumInFrame = data["DEFAULT"].toObject()["num"].toInt();
	}

};

QString FrameData::getFrameLoader(QString frameNo)
{
	QJsonObject data = QJsonDocument::fromJson(displayFrame.toUtf8()).object();
	if (data.contains(frameNo))
	{
		return data[frameNo].toString();
	}
	else return NULL;
}
