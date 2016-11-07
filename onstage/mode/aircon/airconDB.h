#ifndef AIRCONDB_H
#define AIRCONDB_H

#include <qstring.h>

const static QString airconDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"mode/aircon/view0_full.qml\", \
        \"400|480\": \"mode/aircon/view0_half.qml\", \
        \"400|240\": \"mode/aircon/view0_quarter.qml\" \
    } \
}");

#endif