QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    decoration_tile_factory.cpp \
    door_tile_factory.cpp \
    editor.cpp \
    item_tile_factory.cpp \
    main.cpp \
    map_actions.cpp \
    map_canvas.cpp \
    map_painter.cpp \
    map_save.cpp \
    mousetileactions.cpp \
    my_map.cpp \
    open_window.cpp \
    size_window.cpp \
    tile.cpp \
    tiles_container.cpp \
    tileset.cpp \
    wall_tile_factory.cpp

HEADERS += \
    decoration_tile_factory.h \
    door_tile_factory.h \
    editor.h \
    item_tile_factory.h \
    map_actions.h \
    map_canvas.h \
    map_painter.h \
    map_save.h \
    mousetileactions.h \
    my_map.h \
    open_window.h \
    size_window.h \
    tile.h \
    tile_factory.h \
    tiles_container.h \
    tileset.h \
    wall_tile_factory.h

FORMS += \
    editor.ui \
    open_window.ui \
    size_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
