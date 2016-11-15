#ifndef CAMERA_H
#define CAMERA_H

#include "../mode_base.h"
#include "../mode_data.h"
#include "cameraDB.h"

using namespace std;

class Camera :public ModeBase
{
public:
	Camera(QString modeID) :ModeBase(modeID, cameraDB) {};
	static Camera *getInstance(QString modeID)
	{
		if(it != NULL) return it;
		it =new Camera(modeID);
		return it;
	};
	

private:
	static Camera *it;
};

Camera *Camera::it = NULL;

#endif // !CAMERA_H 