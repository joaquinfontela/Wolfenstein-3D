QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PathFactory.cpp \
    YAMLConversor.cpp \
    decoration_tile_factory.cpp \
    door_tile_factory.cpp \
    editor.cpp \
    fake_wall_tile_factory.cpp \
    item_tile_factory.cpp \
    main.cpp \
    map_actions.cpp \
    map_canvas.cpp \
    map_painter.cpp \
    map_save.cpp \
    map_scene.cpp \
    open_window.cpp \
    save_window.cpp \
    size_window.cpp \
    tile_container_actions.cpp \
    tile_item.cpp \
    tiles_container.cpp \
    wall_tile_factory.cpp 

HEADERS += \
    PathFactory.h \
    YAMLConversor.h \
    decoration_tile_factory.h \
    door_tile_factory.h \
    editor.h \
    fake_wall_tile_factory.h \
    item_tile_factory.h \
    map_actions.h \
    map_canvas.h \
    map_painter.h \
    map_save.h \
    map_scene.h \
    open_window.h \
    save_window.h \
    size_window.h \
    tile_container_actions.h \
    tile_factory.h \
    tile_item.h \
    tiles_container.h \
    wall_tile_factory.h

FORMS += \
    editor.ui \
    open_window.ui \
    save_window.ui \
    size_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    ../../common/src/YAML/config.yaml
