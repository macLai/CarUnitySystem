#ifndef CAMERADB_H
#define CAMERADB_H

#include <qstring.h>

const static QString cameraDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"qrc:///camera/view0_full.qml\", \
        \"400|480\": \"qrc:///camera/view0_full.qml\", \
        \"400|240\": \"qrc:///camera/view0_full.qml\" \
    } \
}");

#endif