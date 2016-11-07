#include "frame_data.h"

const int FrameData::maxOfModeNumInFrame = 5;

const QString FrameData::displaySize ( "{ \
		\"navi\" : {\"width\":800, \"height\" : 480}, \
		\"meta\" : {\"width\":1024, \"height\" : 600}, \
		\"hud\" : {\"width\":1280, \"height\" : 720}, \
		\"DEFAULT\" : {\"width\":800, \"height\" : 480} \
}" );

const QString FrameData::displayFrame ( "{ \
	\"Navi1Screen\": \"frame/tempFrame/TempFrameNavi1Screen.qml\", \
	\"Navi2Screen\": \"frame/tempFrame/TempFrameNavi2Screen.qml\", \
	\"Navi3Screen\": \"frame/tempFrame/TempFrameNavi3Screen.qml\", \
	\"Meta1Screen\": \"frame/tempFrame/TempFrameMeta1Screen.qml\", \
	\"Meta2Screen\": \"frame/tempFrame/TempFrameMeta2Screen.qml\", \
	\"Meta3Screen\": \"frame/tempFrame/TempFrameMeta3Screen.qml\", \
	\"Hud0Screen\": \"frame/tempFrame/TempFrameHud0Screen.qml\", \
	\"Hud1Screen\": \"frame/tempFrame/TempFrameHud1Screen.qml\" \
}" );

bool FrameData::getFrameSize(QString displayKind, int &width, int &height)
{

	QJsonObject data = QJsonDocument::fromJson(displaySize.toUtf8()).object();
	if (data.contains(displayKind))
	{
		width = data[displayKind].toObject()["width"].toInt();
		height = data[displayKind].toObject()["height"].toInt();
		return true;
	}
	else
	{
		width = data["DEFAULT"].toObject()["width"].toInt();
		height = data["DEFAULT"].toObject()["height"].toInt();
		return false;
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