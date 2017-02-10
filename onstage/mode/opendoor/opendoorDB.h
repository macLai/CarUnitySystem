#ifndef OPENDOORDB_H
#define OPENDOORDB_H

#include <qstring.h>

const static QString opendoorDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"qrc:///opendoor/view0_full.qml\", \
        \"400|480\": \"qrc:///opendoor/view0_half.qml\", \
        \"400|240\": \"qrc:///opendoor/view0_quarter.qml\", \
        \"300|300\": \"qrc:///opendoor/view0_hud.qml\" \
    } \
}");

#endif