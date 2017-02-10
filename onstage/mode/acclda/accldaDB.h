#ifndef ACCLDADB_H
#define ACCLDADB_H

#include <qstring.h>

const static QString accldaDB("{ \
	\"default\": \"view0\", \
    \"view0\": { \
        \"800|480\": \"qrc:///acclda/view0_full.qml\", \
        \"400|480\": \"qrc:///acclda/view0_half.qml\", \
        \"400|240\": \"qrc:///acclda/view0_quarter.qml\", \
        \"300|300\": \"qrc:///acclda/view0_hud.qml\" \
    } \
}");

#endif