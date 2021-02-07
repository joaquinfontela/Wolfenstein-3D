/********************************************************************************
** Form generated from reading UI file 'size_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIZE_WINDOW_H
#define UI_SIZE_WINDOW_H

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

class Ui_size_window
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *dato_altura;
    QLineEdit *dato_anchura;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *size_window)
    {
        if (size_window->objectName().isEmpty())
            size_window->setObjectName(QStringLiteral("size_window"));
        size_window->resize(357, 243);
        pushButton = new QPushButton(size_window);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 190, 89, 25));
        label = new QLabel(size_window);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 0, 301, 61));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label_2 = new QLabel(size_window);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 70, 91, 21));
        QFont font1;
        font1.setPointSize(16);
        label_2->setFont(font1);
        label_3 = new QLabel(size_window);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 130, 81, 21));
        label_3->setFont(font1);
        dato_altura = new QLineEdit(size_window);
        dato_altura->setObjectName(QStringLiteral("dato_altura"));
        dato_altura->setGeometry(QRect(140, 130, 71, 31));
        dato_anchura = new QLineEdit(size_window);
        dato_anchura->setObjectName(QStringLiteral("dato_anchura"));
        dato_anchura->setGeometry(QRect(140, 70, 71, 31));
        label_4 = new QLabel(size_window);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 70, 81, 21));
        label_5 = new QLabel(size_window);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(230, 130, 81, 21));

        retranslateUi(size_window);

        QMetaObject::connectSlotsByName(size_window);
    } // setupUi

    void retranslateUi(QDialog *size_window)
    {
        size_window->setWindowTitle(QApplication::translate("size_window", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("size_window", "Crear", Q_NULLPTR));
        label->setText(QApplication::translate("size_window", "Elije el tama\303\261o del mapa", Q_NULLPTR));
        label_2->setText(QApplication::translate("size_window", "Anchura :", Q_NULLPTR));
        label_3->setText(QApplication::translate("size_window", "Altura : ", Q_NULLPTR));
        label_4->setText(QApplication::translate("size_window", "<html><head/><body><p><span style=\" font-size:16pt;\">Cuadros</span></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("size_window", "<html><head/><body><p><span style=\" font-size:16pt;\">Cuadros</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class size_window: public Ui_size_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIZE_WINDOW_H
