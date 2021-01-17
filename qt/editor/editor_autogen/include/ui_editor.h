/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Editor
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionsafe;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionEXIT;
    QAction *actionSave_and_exit;
    QAction *actionParedes;
    QAction *actionDecoraciones;
    QAction *actionItems;
    QAction *actionPuertas;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionBorrador;
    QWidget *centralwidget;
    QScrollArea *map_scroll;
    QWidget *map_container;
    QFrame *element_container;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuBack_to_Manu;
    QMenu *menuView;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QString::fromUtf8("Editor"));
        Editor->resize(800, 609);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/game_icon/logo/wolfestein_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Editor->setWindowIcon(icon);
        actionNew = new QAction(Editor);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/iconos/new_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(Editor);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/iconos/open_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionsafe = new QAction(Editor);
        actionsafe->setObjectName(QString::fromUtf8("actionsafe"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/iconos/save_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsafe->setIcon(icon3);
        actionCopy = new QAction(Editor);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/iconos/copy_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon4);
        actionPaste = new QAction(Editor);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/iconos/paste_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon5);
        actionUndo = new QAction(Editor);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/iconos/undo_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon6);
        actionRedo = new QAction(Editor);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/iconos/redo_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon7);
        actionEXIT = new QAction(Editor);
        actionEXIT->setObjectName(QString::fromUtf8("actionEXIT"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/iconos/quit_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEXIT->setIcon(icon8);
        actionSave_and_exit = new QAction(Editor);
        actionSave_and_exit->setObjectName(QString::fromUtf8("actionSave_and_exit"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/iconos/save_and_quit_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_and_exit->setIcon(icon9);
        actionParedes = new QAction(Editor);
        actionParedes->setObjectName(QString::fromUtf8("actionParedes"));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        actionParedes->setFont(font);
        actionDecoraciones = new QAction(Editor);
        actionDecoraciones->setObjectName(QString::fromUtf8("actionDecoraciones"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        actionDecoraciones->setFont(font1);
        actionItems = new QAction(Editor);
        actionItems->setObjectName(QString::fromUtf8("actionItems"));
        actionPuertas = new QAction(Editor);
        actionPuertas->setObjectName(QString::fromUtf8("actionPuertas"));
        actionZoom_in = new QAction(Editor);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/iconos/zoom_in_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_in->setIcon(icon10);
        actionZoom_out = new QAction(Editor);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/iconos/zoom_out_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_out->setIcon(icon11);
        actionBorrador = new QAction(Editor);
        actionBorrador->setObjectName(QString::fromUtf8("actionBorrador"));
        centralwidget = new QWidget(Editor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        map_scroll = new QScrollArea(centralwidget);
        map_scroll->setObjectName(QString::fromUtf8("map_scroll"));
        map_scroll->setGeometry(QRect(20, 20, 611, 501));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(map_scroll->sizePolicy().hasHeightForWidth());
        map_scroll->setSizePolicy(sizePolicy);
        map_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        map_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        map_scroll->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        map_scroll->setWidgetResizable(false);
        map_container = new QWidget();
        map_container->setObjectName(QString::fromUtf8("map_container"));
        map_container->setEnabled(true);
        map_container->setGeometry(QRect(0, 0, 624, 505));
        map_container->setMaximumSize(QSize(16777215, 16777215));
        map_container->setCursor(QCursor(Qt::ArrowCursor));
        map_scroll->setWidget(map_container);
        element_container = new QFrame(centralwidget);
        element_container->setObjectName(QString::fromUtf8("element_container"));
        element_container->setGeometry(QRect(639, 21, 151, 501));
        element_container->setFrameShape(QFrame::StyledPanel);
        element_container->setFrameShadow(QFrame::Raised);
        Editor->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Editor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Editor->setStatusBar(statusbar);
        menuBar = new QMenuBar(Editor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuBack_to_Manu = new QMenu(menuBar);
        menuBack_to_Manu->setObjectName(QString::fromUtf8("menuBack_to_Manu"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        Editor->setMenuBar(menuBar);
        toolBar = new QToolBar(Editor);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setFont(font1);
        Editor->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuBack_to_Manu->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionsafe);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuBack_to_Manu->addAction(actionEXIT);
        menuBack_to_Manu->addAction(actionSave_and_exit);
        menuView->addAction(actionZoom_in);
        menuView->addAction(actionZoom_out);
        toolBar->addSeparator();
        toolBar->addAction(actionParedes);
        toolBar->addSeparator();
        toolBar->addAction(actionDecoraciones);
        toolBar->addSeparator();
        toolBar->addAction(actionItems);
        toolBar->addSeparator();
        toolBar->addAction(actionPuertas);
        toolBar->addSeparator();
        toolBar->addAction(actionBorrador);

        retranslateUi(Editor);

        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QMainWindow *Editor)
    {
        Editor->setWindowTitle(QApplication::translate("Editor", "Editor", nullptr));
        actionNew->setText(QApplication::translate("Editor", "New", nullptr));
        actionOpen->setText(QApplication::translate("Editor", "Open", nullptr));
        actionsafe->setText(QApplication::translate("Editor", "Save", nullptr));
        actionCopy->setText(QApplication::translate("Editor", "Copy", nullptr));
#ifndef QT_NO_SHORTCUT
        actionCopy->setShortcut(QApplication::translate("Editor", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionPaste->setText(QApplication::translate("Editor", "Paste", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPaste->setShortcut(QApplication::translate("Editor", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionUndo->setText(QApplication::translate("Editor", "Undo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("Editor", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("Editor", "Redo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("Editor", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
        actionEXIT->setText(QApplication::translate("Editor", "Exit", nullptr));
        actionSave_and_exit->setText(QApplication::translate("Editor", "Save and exit", nullptr));
        actionParedes->setText(QApplication::translate("Editor", "Paredes", nullptr));
        actionDecoraciones->setText(QApplication::translate("Editor", "Decoraciones", nullptr));
        actionItems->setText(QApplication::translate("Editor", "Items", nullptr));
        actionPuertas->setText(QApplication::translate("Editor", "Puertas", nullptr));
        actionZoom_in->setText(QApplication::translate("Editor", "Zoom in", nullptr));
        actionZoom_out->setText(QApplication::translate("Editor", "Zoom out", nullptr));
        actionBorrador->setText(QApplication::translate("Editor", "Borrador", nullptr));
        menuFile->setTitle(QApplication::translate("Editor", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("Editor", "Edit", nullptr));
        menuBack_to_Manu->setTitle(QApplication::translate("Editor", "Quit", nullptr));
        menuView->setTitle(QApplication::translate("Editor", "View", nullptr));
        toolBar->setWindowTitle(QApplication::translate("Editor", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
