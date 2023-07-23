QT += charts qml quick serialport

HEADERS += \
    datasource.h \
    tft43A.h \
    hilorecibidor.h

SOURCES += \
    main.cpp \
    datasource.cpp \
    tft43A.cpp \
    hilorecibidor.cpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    qml/qmloscilloscope/*

target.path = $$[QT_INSTALL_EXAMPLES]/charts/qmloscilloscope
INSTALLS += target
