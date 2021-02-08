/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *centralwidget;
    QPushButton *button_join;
    QLineEdit *dato_ip;
    QLineEdit *dato_puerto;
    QLineEdit *dato_game;
    QPushButton *button_create;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Login->sizePolicy().hasHeightForWidth());
        Login->setSizePolicy(sizePolicy);
        Login->setMaximumSize(QSize(800, 600));
        Login->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(Login);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        button_join = new QPushButton(centralwidget);
        button_join->setObjectName(QStringLiteral("button_join"));
        button_join->setGeometry(QRect(600, 530, 171, 41));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu Condensed"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        button_join->setFont(font);
        dato_ip = new QLineEdit(centralwidget);
        dato_ip->setObjectName(QStringLiteral("dato_ip"));
        dato_ip->setGeometry(QRect(600, 330, 171, 41));
        dato_puerto = new QLineEdit(centralwidget);
        dato_puerto->setObjectName(QStringLiteral("dato_puerto"));
        dato_puerto->setGeometry(QRect(600, 380, 171, 41));
        dato_game = new QLineEdit(centralwidget);
        dato_game->setObjectName(QStringLiteral("dato_game"));
        dato_game->setGeometry(QRect(600, 430, 171, 41));
        button_create = new QPushButton(centralwidget);
        button_create->setObjectName(QStringLiteral("button_create"));
        button_create->setGeometry(QRect(600, 480, 171, 41));
        button_create->setFont(font);
        Login->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Login);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Login->setMenuBar(menubar);
        statusbar = new QStatusBar(Login);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Login->setStatusBar(statusbar);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QMainWindow *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", Q_NULLPTR));
        button_join->setText(QApplication::translate("Login", "JOIN MATCH", Q_NULLPTR));
        button_create->setText(QApplication::translate("Login", "CREATE MATCH", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
