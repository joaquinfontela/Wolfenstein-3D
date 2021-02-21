/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
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
            Editor->setObjectName(QStringLiteral("Editor"));
        Editor->resize(800, 609);
        QIcon icon;
        icon.addFile(QStringLiteral("logo/wolfestein_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        Editor->setWindowIcon(icon);
        Editor->setStyleSheet(QStringLiteral("background-color: rgb(85, 87, 83);"));
        actionNew = new QAction(Editor);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("iconos/new_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(Editor);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("iconos/open_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionsafe = new QAction(Editor);
        actionsafe->setObjectName(QStringLiteral("actionsafe"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("iconos/save_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionsafe->setIcon(icon3);
        actionEXIT = new QAction(Editor);
        actionEXIT->setObjectName(QStringLiteral("actionEXIT"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("iconos/quit_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEXIT->setIcon(icon4);
        actionSave_and_exit = new QAction(Editor);
        actionSave_and_exit->setObjectName(QStringLiteral("actionSave_and_exit"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("iconos/save_and_quit_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_and_exit->setIcon(icon5);
        actionParedes = new QAction(Editor);
        actionParedes->setObjectName(QStringLiteral("actionParedes"));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu Condensed"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        actionParedes->setFont(font);
        actionDecoraciones = new QAction(Editor);
        actionDecoraciones->setObjectName(QStringLiteral("actionDecoraciones"));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu Condensed"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        actionDecoraciones->setFont(font1);
        actionItems = new QAction(Editor);
        actionItems->setObjectName(QStringLiteral("actionItems"));
        actionItems->setFont(font1);
        actionPuertas = new QAction(Editor);
        actionPuertas->setObjectName(QStringLiteral("actionPuertas"));
        actionPuertas->setFont(font1);
        actionZoom_in = new QAction(Editor);
        actionZoom_in->setObjectName(QStringLiteral("actionZoom_in"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("iconos/zoom_in_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_in->setIcon(icon6);
        actionZoom_out = new QAction(Editor);
        actionZoom_out->setObjectName(QStringLiteral("actionZoom_out"));
        QIcon icon7;
        icon7.addFile(QStringLiteral("iconos/zoom_out_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_out->setIcon(icon7);
        actionBorrador = new QAction(Editor);
        actionBorrador->setObjectName(QStringLiteral("actionBorrador"));
        actionBorrador->setFont(font1);
        actionRespawn = new QAction(Editor);
        actionRespawn->setObjectName(QStringLiteral("actionRespawn"));
        actionRespawn->setFont(font1);
        actionParedes_Falsas = new QAction(Editor);
        actionParedes_Falsas->setObjectName(QStringLiteral("actionParedes_Falsas"));
        actionParedes_Falsas->setFont(font1);
        actionSave_as = new QAction(Editor);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionSave_as->setIcon(icon3);
        centralwidget = new QWidget(Editor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        graphics_tiles_container = new QGraphicsView(centralwidget);
        graphics_tiles_container->setObjectName(QStringLiteral("graphics_tiles_container"));
        graphics_tiles_container->setGeometry(QRect(640, 20, 151, 501));
        graphics_map_container = new QGraphicsView(centralwidget);
        graphics_map_container->setObjectName(QStringLiteral("graphics_map_container"));
        graphics_map_container->setGeometry(QRect(15, 21, 611, 501));
        Editor->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Editor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Editor->setStatusBar(statusbar);
        menuBar = new QMenuBar(Editor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuBack_to_Manu = new QMenu(menuBar);
        menuBack_to_Manu->setObjectName(QStringLiteral("menuBack_to_Manu"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        Editor->setMenuBar(menuBar);
        toolBar = new QToolBar(Editor);
        toolBar->setObjectName(QStringLiteral("toolBar"));
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
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
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
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
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
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush10);
        toolBar->setPalette(palette);
        toolBar->setFont(font1);
        Editor->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(Editor);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
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
        Editor->setWindowTitle(QApplication::translate("Editor", "Editor", Q_NULLPTR));
        actionNew->setText(QApplication::translate("Editor", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("Editor", "Open", Q_NULLPTR));
        actionsafe->setText(QApplication::translate("Editor", "Save", Q_NULLPTR));
        actionEXIT->setText(QApplication::translate("Editor", "Exit", Q_NULLPTR));
        actionSave_and_exit->setText(QApplication::translate("Editor", "Save and exit", Q_NULLPTR));
        actionParedes->setText(QApplication::translate("Editor", "Paredes", Q_NULLPTR));
        actionDecoraciones->setText(QApplication::translate("Editor", "Decoraciones", Q_NULLPTR));
        actionItems->setText(QApplication::translate("Editor", "Items", Q_NULLPTR));
        actionPuertas->setText(QApplication::translate("Editor", "Puertas", Q_NULLPTR));
        actionZoom_in->setText(QApplication::translate("Editor", "Zoom in", Q_NULLPTR));
        actionZoom_out->setText(QApplication::translate("Editor", "Zoom out", Q_NULLPTR));
        actionBorrador->setText(QApplication::translate("Editor", "Borrador", Q_NULLPTR));
        actionRespawn->setText(QApplication::translate("Editor", "Respawn", Q_NULLPTR));
        actionParedes_Falsas->setText(QApplication::translate("Editor", "Paredes Falsas", Q_NULLPTR));
        actionSave_as->setText(QApplication::translate("Editor", "Save as", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("Editor", "File", Q_NULLPTR));
        menuBack_to_Manu->setTitle(QApplication::translate("Editor", "Quit", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("Editor", "View", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("Editor", "toolBar", Q_NULLPTR));
        toolBar_2->setWindowTitle(QApplication::translate("Editor", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
