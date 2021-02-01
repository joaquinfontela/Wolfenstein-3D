/********************************************************************************
** Form generated from reading UI file 'open_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPEN_WINDOW_H
#define UI_OPEN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_open_window
{
public:
    QPushButton *open_boton;
    QListWidget *map_saved_container;
    QLabel *label;

    void setupUi(QDialog *open_window)
    {
        if (open_window->objectName().isEmpty())
            open_window->setObjectName(QString::fromUtf8("open_window"));
        open_window->resize(572, 339);
        open_boton = new QPushButton(open_window);
        open_boton->setObjectName(QString::fromUtf8("open_boton"));
        open_boton->setGeometry(QRect(130, 290, 321, 25));
        map_saved_container = new QListWidget(open_window);
        map_saved_container->setObjectName(QString::fromUtf8("map_saved_container"));
        map_saved_container->setGeometry(QRect(40, 80, 491, 192));
        map_saved_container->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        label = new QLabel(open_window);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 10, 431, 41));
        QFont font;
        font.setPointSize(22);
        label->setFont(font);

        retranslateUi(open_window);

        QMetaObject::connectSlotsByName(open_window);
    } // setupUi

    void retranslateUi(QDialog *open_window)
    {
        open_window->setWindowTitle(QApplication::translate("open_window", "Dialog", nullptr));
        open_boton->setText(QApplication::translate("open_window", "Abrir", nullptr));
        label->setText(QApplication::translate("open_window", "Selecciona un mapa :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class open_window: public Ui_open_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPEN_WINDOW_H
