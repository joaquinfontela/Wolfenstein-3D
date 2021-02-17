/********************************************************************************
** Form generated from reading UI file 'join_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOIN_WINDOW_H
#define UI_JOIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_join_window
{
public:
    QScrollArea *id_scroll;
    QWidget *id_container;
    QPushButton *join_button;
    QLabel *label;

    void setupUi(QDialog *join_window)
    {
        if (join_window->objectName().isEmpty())
            join_window->setObjectName(QStringLiteral("join_window"));
        join_window->resize(400, 300);
        id_scroll = new QScrollArea(join_window);
        id_scroll->setObjectName(QStringLiteral("id_scroll"));
        id_scroll->setGeometry(QRect(30, 70, 321, 151));
        id_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        id_scroll->setWidgetResizable(true);
        id_container = new QWidget();
        id_container->setObjectName(QStringLiteral("id_container"));
        id_container->setGeometry(QRect(0, 0, 305, 149));
        id_scroll->setWidget(id_container);
        join_button = new QPushButton(join_window);
        join_button->setObjectName(QStringLiteral("join_button"));
        join_button->setGeometry(QRect(120, 240, 141, 25));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu Condensed"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        join_button->setFont(font);
        label = new QLabel(join_window);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 231, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu Condensed"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label->setFont(font1);

        retranslateUi(join_window);

        QMetaObject::connectSlotsByName(join_window);
    } // setupUi

    void retranslateUi(QDialog *join_window)
    {
        join_window->setWindowTitle(QApplication::translate("join_window", "Dialog", Q_NULLPTR));
        join_button->setText(QApplication::translate("join_window", "JOIN", Q_NULLPTR));
        label->setText(QApplication::translate("join_window", "Choose a Match ID :", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class join_window: public Ui_join_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOIN_WINDOW_H
