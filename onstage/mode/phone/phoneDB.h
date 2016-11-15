#ifndef PHONEDB_H
#define PHONEDB_H

#include <qstring.h>

const static QString phoneDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"mode/phone/view0_full.qml\", \
        \"400|480\": \"mode/phone/view0_half.qml\", \
        \"400|240\": \"mode/phone/view0_quarter.qml\" \
    } \
}");

#endif