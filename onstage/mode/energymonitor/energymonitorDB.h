#ifndef ENERGYMONITORDB_H
#define ENERGYMONITORDB_H

#include <qstring.h>

const static QString energymonitorDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"qrc:///energymonitor/view0_full.qml\", \
        \"400|480\": \"qrc:///energymonitor/view0_half.qml\", \
        \"400|240\": \"qrc:///energymonitor/view0_quarter.qml\" \
    } \
}");

#endif