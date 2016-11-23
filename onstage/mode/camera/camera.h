#ifndef CAMERA_H
#define CAMERA_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "cameraDB.h"

using namespace std;

class Camera :public ModeBase
{
public:
	Camera(QString modeID, QObject *loader) :ModeBase(modeID, cameraDB, loader) {};
	static Camera *getInstance(QString modeID, QObject *loader)
	{
		if(it != NULL) return it;
		it =new Camera(modeID, loader);
		return it;
	};
	

private:
	static Camera *it;
};

Camera *Camera::it = NULL;

#endif // !CAMERA_H 