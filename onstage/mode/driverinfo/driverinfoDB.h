#ifndef DRIVERINFODB_H
#define DRIVERINFODB_H

#include <qstring.h>

const static QString driverinfoDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"qrc:///driverinfo/view0_full.qml\", \
        \"400|480\": \"qrc:///driverinfo/view0_half.qml\", \
        \"400|240\": \"qrc:///driverinfo/view0_quarter.qml\" \
    } \
}");

#endif