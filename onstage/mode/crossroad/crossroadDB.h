#ifndef CROSSROADDB_H
#define CROSSROADDB_H

#include <qstring.h>

const static QString crossroadDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"qrc:///crossroad/view0_full.qml\", \
        \"400|480\": \"qrc:///crossroad/view0_half.qml\", \
        \"400|240\": \"qrc:///crossroad/view0_quarter.qml\", \
        \"300|300\": \"qrc:///crossroad/view0_hud.qml\" \
    } \
}");

#endif