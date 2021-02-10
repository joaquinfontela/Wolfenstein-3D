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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
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
    QAction *actionEXIT;
    QAction *actionSave_and_exit;
    QAction *actionParedes;
    QAction *actionDecoraciones;
    QAction *actionItems;
    QAction *actionPuertas;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionBorrador;
    QAction *actionRespawn;
    QAction *actionParedes_Falsas;
    QAction *actionSave_as;
    QWidget *centralwidget;
    QGraphicsView *graphics_tiles_container;
    QGraphicsView *graphics_map_container;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuBack_to_Manu;
    QMenu *menuView;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QString::fromUtf8("Editor"));
        Editor->resize(800, 609);
        QIcon icon;
        icon.addFile(QString::fromUtf8("logo/wolfestein_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Editor->setWindowIcon(icon);
        Editor->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 87, 83);"));
        actionNew = new QAction(Editor);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("iconos/new_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(Editor);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("iconos/open_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionsafe = new QAction(Editor);
        actionsafe->setObjectName(QString::fromUtf8("actionsafe"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("iconos/save_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsafe->setIcon(icon3);
        actionEXIT = new QAction(Editor);
        actionEXIT->setObjectName(QString::fromUtf8("actionEXIT"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("iconos/quit_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEXIT->setIcon(icon4);
        actionSave_and_exit = new QAction(Editor);
        actionSave_and_exit->setObjectName(QString::fromUtf8("actionSave_and_exit"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("iconos/save_and_quit_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_and_exit->setIcon(icon5);
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
        actionItems->setFont(font1);
        actionPuertas = new QAction(Editor);
        actionPuertas->setObjectName(QString::fromUtf8("actionPuertas"));
        actionPuertas->setFont(font1);
        actionZoom_in = new QAction(Editor);
        actionZoom_in->setObjectName(QString::fromUtf8("actionZoom_in"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("iconos/zoom_in_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_in->setIcon(icon6);
        actionZoom_out = new QAction(Editor);
        actionZoom_out->setObjectName(QString::fromUtf8("actionZoom_out"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("iconos/zoom_out_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_out->setIcon(icon7);
        actionBorrador = new QAction(Editor);
        actionBorrador->setObjectName(QString::fromUtf8("actionBorrador"));
        actionBorrador->setFont(font1);
        actionRespawn = new QAction(Editor);
        actionRespawn->setObjectName(QString::fromUtf8("actionRespawn"));
        actionRespawn->setFont(font1);
        actionParedes_Falsas = new QAction(Editor);
        actionParedes_Falsas->setObjectName(QString::fromUtf8("actionParedes_Falsas"));
        actionParedes_Falsas->setFont(font1);
        actionSave_as = new QAction(Editor);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionSave_as->setIcon(icon3);
        centralwidget = new QWidget(Editor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphics_tiles_container = new QGraphicsView(centralwidget);
        graphics_tiles_container->setObjectName(QString::fromUtf8("graphics_tiles_container"));
        graphics_tiles_container->setGeometry(QRect(640, 20, 151, 501));
        graphics_map_container = new QGraphicsView(centralwidget);
        graphics_map_container->setObjectName(QString::fromUtf8("graphics_map_container"));
        graphics_map_container->setGeometry(QRect(15, 21, 611, 501));
        Editor->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Editor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Editor->setStatusBar(statusbar);
        menuBar = new QMenuBar(Editor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuBack_to_Manu = new QMenu(menuBar);
        menuBack_to_Manu->setObjectName(QString::fromUtf8("menuBack_to_Manu"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        Editor->setMenuBar(menuBar);
        toolBar = new QToolBar(Editor);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(85, 87, 83, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(247, 247, 247, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(119, 119, 119, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(159, 159, 159, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        QBrush brush8(QColor(0, 0, 0, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush9(QColor(239, 239, 239, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush10(QColor(0, 0, 0, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush10);
#endif
        toolBar->setPalette(palette);
        toolBar->setFont(font1);
        Editor->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(Editor);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        Editor->addToolBar(Qt::TopToolBarArea, toolBar_2);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuBack_to_Manu->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionsafe);
        menuFile->addAction(actionSave_as);
        menuBack_to_Manu->addAction(actionEXIT);
        menuBack_to_Manu->addAction(actionSave_and_exit);
        menuView->addAction(actionZoom_in);
        menuView->addAction(actionZoom_out);
        toolBar->addSeparator();
        toolBar->addAction(actionParedes);
        toolBar->addSeparator();
        toolBar->addAction(actionParedes_Falsas);
        toolBar->addSeparator();
        toolBar->addAction(actionItems);
        toolBar->addSeparator();
        toolBar->addAction(actionPuertas);
        toolBar->addSeparator();
        toolBar->addAction(actionRespawn);
        toolBar->addSeparator();
        toolBar->addAction(actionDecoraciones);
        toolBar->addSeparator();
        toolBar->addAction(actionBorrador);
        toolBar->addSeparator();

        retranslateUi(Editor);

        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QMainWindow *Editor)
    {
        Editor->setWindowTitle(QApplication::translate("Editor", "Editor", nullptr));
        actionNew->setText(QApplication::translate("Editor", "New", nullptr));
        actionOpen->setText(QApplication::translate("Editor", "Open", nullptr));
        actionsafe->setText(QApplication::translate("Editor", "Save", nullptr));
        actionEXIT->setText(QApplication::translate("Editor", "Exit", nullptr));
        actionSave_and_exit->setText(QApplication::translate("Editor", "Save and exit", nullptr));
        actionParedes->setText(QApplication::translate("Editor", "Paredes", nullptr));
        actionDecoraciones->setText(QApplication::translate("Editor", "Decoraciones", nullptr));
        actionItems->setText(QApplication::translate("Editor", "Items", nullptr));
        actionPuertas->setText(QApplication::translate("Editor", "Puertas", nullptr));
        actionZoom_in->setText(QApplication::translate("Editor", "Zoom in", nullptr));
        actionZoom_out->setText(QApplication::translate("Editor", "Zoom out", nullptr));
        actionBorrador->setText(QApplication::translate("Editor", "Borrador", nullptr));
        actionRespawn->setText(QApplication::translate("Editor", "Respawn", nullptr));
        actionParedes_Falsas->setText(QApplication::translate("Editor", "Paredes Falsas", nullptr));
        actionSave_as->setText(QApplication::translate("Editor", "Save as", nullptr));
        menuFile->setTitle(QApplication::translate("Editor", "File", nullptr));
        menuBack_to_Manu->setTitle(QApplication::translate("Editor", "Quit", nullptr));
        menuView->setTitle(QApplication::translate("Editor", "View", nullptr));
        toolBar->setWindowTitle(QApplication::translate("Editor", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QApplication::translate("Editor", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
