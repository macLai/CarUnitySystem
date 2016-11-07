TEMPLATE = app

QT += qml quick widgets \
        websockets \
        webview \
        multimedia multimediawidgets

CONFIG += c++11

SOURCES += main.cpp \
                frame/frame.cpp \
                frame/frame_data.cpp \
                mode/mode_base.cpp \
                mode/mode_data.cpp \
                mode/mode_enter.cpp \
                mode/modeDB.cpp \
                socket/server_link.cpp

HEADERS  +=     frame/frame.h \
                frame/frame_data.h \
                mode/mode_base.h \
                mode/mode_data.h \
                mode/mode_enter.h \
                mode/modeDB.h \
                mode/navi/navi.h \
                mode/navi/naviDB.h \
                mode/audio/audio.h \
                mode/audio/audioDB.h \
                mode/aircon/aircon.h \
                mode/aircon/airconDB.h \
                socket/server_link.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
