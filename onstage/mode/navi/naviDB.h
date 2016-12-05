#ifndef NAVIDB_H
#define NAVIDB_H

#include <qstring.h>

const static QString naviDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"qrc:///navi/view0_full.qml\", \
        \"400|480\": \"qrc:///navi/view0_full.qml\", \
        \"400|240\": \"qrc:///navi/view0_full.qml\" \
    } \
}");

#endif