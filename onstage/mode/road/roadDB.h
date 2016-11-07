#ifndef ROADDB_H
#define ROADDB_H

#include <qstring.h>

const static QString naviDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"mode/navi/view0_full.qml\", \
        \"400|480\": \"mode/navi/view0_half.qml\", \
        \"400|240\": \"mode/navi/view0_quarter.qml\" \
    } \
}");

#endif