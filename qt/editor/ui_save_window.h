/********************************************************************************
** Form generated from reading UI file 'save_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVE_WINDOW_H
#define UI_SAVE_WINDOW_H

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

class Ui_save_window
{
public:
    QLabel *label;
    QLineEdit *name_value;
    QPushButton *pushButton;

    void setupUi(QDialog *save_window)
    {
        if (save_window->objectName().isEmpty())
            save_window->setObjectName(QStringLiteral("save_window"));
        save_window->resize(332, 188);
        label = new QLabel(save_window);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 321, 71));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu Condensed"));
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        name_value = new QLineEdit(save_window);
        name_value->setObjectName(QStringLiteral("name_value"));
        name_value->setGeometry(QRect(40, 70, 261, 41));
        pushButton = new QPushButton(save_window);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 130, 89, 25));

        retranslateUi(save_window);

        QMetaObject::connectSlotsByName(save_window);
    } // setupUi

    void retranslateUi(QDialog *save_window)
    {
        save_window->setWindowTitle(QApplication::translate("save_window", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("save_window", "Elije un nombre para tu mapa:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("save_window", "Guardar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class save_window: public Ui_save_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVE_WINDOW_H
