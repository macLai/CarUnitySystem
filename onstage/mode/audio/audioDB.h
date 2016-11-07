#ifndef AUDIODB_H
#define AUDIODB_H

#include <qstring.h>

const static QString audioDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"mode/audio/view0_full.qml\", \
        \"400|480\": \"mode/audio/view0_half.qml\", \
        \"400|240\": \"mode/audio/view0_quarter.qml\" \
    } \
}");

#endif