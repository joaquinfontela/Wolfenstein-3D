/********************************************************************************
** Form generated from reading UI file 'create_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATE_WINDOW_H
#define UI_CREATE_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_create_window
{
public:
    QPushButton *pushButton;
    QLineEdit *map_id_line;
    QLabel *label;

    void setupUi(QDialog *create_window)
    {
        if (create_window->objectName().isEmpty())
            create_window->setObjectName(QStringLiteral("create_window"));
        create_window->resize(321, 171);
        pushButton = new QPushButton(create_window);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 120, 151, 25));
        map_id_line = new QLineEdit(create_window);
        map_id_line->setObjectName(QStringLiteral("map_id_line"));
        map_id_line->setGeometry(QRect(60, 60, 191, 41));
        label = new QLabel(create_window);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 221, 41));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu Condensed"));
        font.setPointSize(19);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        retranslateUi(create_window);

        QMetaObject::connectSlotsByName(create_window);
    } // setupUi

    void retranslateUi(QDialog *create_window)
    {
        create_window->setWindowTitle(QApplication::translate("create_window", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("create_window", "CREATE MATCH", Q_NULLPTR));
        label->setText(QApplication::translate("create_window", "WRITE A MAP ID : ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class create_window: public Ui_create_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATE_WINDOW_H
