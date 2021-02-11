/********************************************************************************
** Form generated from reading UI file 'save_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVE_WINDOW_H
#define UI_SAVE_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_save_window
{
public:
    QLabel *label;
    QLineEdit *name_value;
    QPushButton *pushButton;

    void setupUi(QDialog *save_window)
    {
        if (save_window->objectName().isEmpty())
            save_window->setObjectName(QString::fromUtf8("save_window"));
        save_window->resize(332, 188);
        label = new QLabel(save_window);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 321, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        name_value = new QLineEdit(save_window);
        name_value->setObjectName(QString::fromUtf8("name_value"));
        name_value->setGeometry(QRect(40, 70, 261, 41));
        pushButton = new QPushButton(save_window);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 130, 89, 25));

        retranslateUi(save_window);

        QMetaObject::connectSlotsByName(save_window);
    } // setupUi

    void retranslateUi(QDialog *save_window)
    {
        save_window->setWindowTitle(QApplication::translate("save_window", "Dialog", nullptr));
        label->setText(QApplication::translate("save_window", "Elije un nombre para tu mapa:", nullptr));
        pushButton->setText(QApplication::translate("save_window", "Guardar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class save_window: public Ui_save_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVE_WINDOW_H
