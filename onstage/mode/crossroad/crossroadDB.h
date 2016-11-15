#ifndef CROSSROADDB_H
#define CROSSROADDB_H

#include <qstring.h>

const static QString crossroadDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"mode/crossroad/view0_half.qml\", \
        \"400|480\": \"mode/crossroad/view0_half.qml\", \
        \"400|240\": \"mode/crossroad/view0_quarter.qml\" \
    } \
}");

#endif