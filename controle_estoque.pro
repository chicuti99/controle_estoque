QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fm_editarprodvenda.cpp \
    fm_gestaocolaboradores.cpp \
    fm_gestaoestoque.cpp \
    fm_gestaovendas.cpp \
    fm_log.cpp \
    fm_nova_venda.cpp \
    funcoes_globais.cpp \
    main.cpp \
    fm_principal.cpp

HEADERS += \
    Conexao.h \
    fm_editarprodvenda.h \
    fm_gestaocolaboradores.h \
    fm_gestaoestoque.h \
    fm_gestaovendas.h \
    fm_log.h \
    fm_nova_venda.h \
    fm_principal.h \
    funcoes_globais.h \
    variaveis_globais.h

FORMS += \
    fm_editarprodvenda.ui \
    fm_gestaocolaboradores.ui \
    fm_gestaoestoque.ui \
    fm_gestaovendas.ui \
    fm_log.ui \
    fm_nova_venda.ui \
    fm_principal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    art.qrc
