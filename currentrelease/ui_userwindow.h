/********************************************************************************
** Form generated from reading UI file 'userwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERWINDOW_H
#define UI_USERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userwindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *userselect;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_userselect;
    QWidget *beverageselect;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_beverageselect;
    QLabel *label_infobox;
    QWidget *history;
    QTextBrowser *textBrowser_history;
    QWidget *money;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_calc;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_0;
    QPushButton *pushButton_colon;
    QPushButton *pushButton_back;
    QLabel *label_display;
    QPushButton *pushButton_saveTransaction;
    QLabel *label_transactionNotification;
    QLabel *label_transactionID;
    QLabel *label_error;
    QWidget *settings;
    QLineEdit *lineEdit_cl;
    QTextBrowser *textBrowser_clOutput;
    QLabel *label_topNotificationBar;
    QLabel *label_balance;
    QPushButton *pushButton_pageBack;
    QPushButton *pushButton_history;
    QPushButton *pushButton_settings;
    QPushButton *pushButton_addMoney;
    QFrame *line_top;
    QLCDNumber *lcd_clock;

    void setupUi(QMainWindow *userwindow)
    {
        if (userwindow->objectName().isEmpty())
            userwindow->setObjectName(QStringLiteral("userwindow"));
        userwindow->setWindowModality(Qt::NonModal);
        userwindow->resize(480, 800);
        userwindow->setAutoFillBackground(false);
        userwindow->setDocumentMode(false);
        userwindow->setTabShape(QTabWidget::Rounded);
        userwindow->setUnifiedTitleAndToolBarOnMac(false);
        centralWidget = new QWidget(userwindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 45, 481, 706));
        userselect = new QWidget();
        userselect->setObjectName(QStringLiteral("userselect"));
        userselect->setEnabled(true);
        gridLayoutWidget_3 = new QWidget(userselect);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(0, 10, 471, 681));
        gridLayout_userselect = new QGridLayout(gridLayoutWidget_3);
        gridLayout_userselect->setSpacing(6);
        gridLayout_userselect->setContentsMargins(11, 11, 11, 11);
        gridLayout_userselect->setObjectName(QStringLiteral("gridLayout_userselect"));
        gridLayout_userselect->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(userselect);
        beverageselect = new QWidget();
        beverageselect->setObjectName(QStringLiteral("beverageselect"));
        gridLayoutWidget_2 = new QWidget(beverageselect);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 10, 481, 631));
        gridLayout_beverageselect = new QGridLayout(gridLayoutWidget_2);
        gridLayout_beverageselect->setSpacing(6);
        gridLayout_beverageselect->setContentsMargins(11, 11, 11, 11);
        gridLayout_beverageselect->setObjectName(QStringLiteral("gridLayout_beverageselect"));
        gridLayout_beverageselect->setContentsMargins(0, 0, 0, 0);
        label_infobox = new QLabel(beverageselect);
        label_infobox->setObjectName(QStringLiteral("label_infobox"));
        label_infobox->setEnabled(true);
        label_infobox->setGeometry(QRect(0, 650, 481, 51));
        QFont font;
        font.setFamily(QStringLiteral("Lato Semibold"));
        font.setPointSize(12);
        label_infobox->setFont(font);
        label_infobox->setFrameShape(QFrame::NoFrame);
        label_infobox->setFrameShadow(QFrame::Plain);
        label_infobox->setAlignment(Qt::AlignCenter);
        label_infobox->setWordWrap(true);
        label_infobox->setTextInteractionFlags(Qt::NoTextInteraction);
        stackedWidget->addWidget(beverageselect);
        history = new QWidget();
        history->setObjectName(QStringLiteral("history"));
        textBrowser_history = new QTextBrowser(history);
        textBrowser_history->setObjectName(QStringLiteral("textBrowser_history"));
        textBrowser_history->setGeometry(QRect(15, 20, 451, 671));
        stackedWidget->addWidget(history);
        money = new QWidget();
        money->setObjectName(QStringLiteral("money"));
        gridLayoutWidget = new QWidget(money);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(19, 270, 441, 251));
        gridLayout_calc = new QGridLayout(gridLayoutWidget);
        gridLayout_calc->setSpacing(6);
        gridLayout_calc->setContentsMargins(11, 11, 11, 11);
        gridLayout_calc->setObjectName(QStringLiteral("gridLayout_calc"));
        gridLayout_calc->setContentsMargins(6, 0, 6, 0);
        pushButton_1 = new QPushButton(gridLayoutWidget);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setMinimumSize(QSize(80, 70));
        QFont font1;
        font1.setFamily(QStringLiteral("Lato"));
        font1.setPointSize(36);
        pushButton_1->setFont(font1);

        gridLayout_calc->addWidget(pushButton_1, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(80, 70));
        pushButton_2->setFont(font1);

        gridLayout_calc->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(80, 70));
        pushButton_3->setFont(font1);

        gridLayout_calc->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(80, 70));
        pushButton_4->setFont(font1);

        gridLayout_calc->addWidget(pushButton_4, 0, 3, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(80, 70));
        pushButton_5->setFont(font1);

        gridLayout_calc->addWidget(pushButton_5, 1, 0, 1, 1);

        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(80, 70));
        pushButton_6->setFont(font1);

        gridLayout_calc->addWidget(pushButton_6, 1, 1, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(80, 70));
        pushButton_7->setFont(font1);

        gridLayout_calc->addWidget(pushButton_7, 1, 2, 1, 1);

        pushButton_8 = new QPushButton(gridLayoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(80, 70));
        pushButton_8->setFont(font1);

        gridLayout_calc->addWidget(pushButton_8, 1, 3, 1, 1);

        pushButton_9 = new QPushButton(gridLayoutWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(80, 70));
        pushButton_9->setFont(font1);

        gridLayout_calc->addWidget(pushButton_9, 2, 0, 1, 1);

        pushButton_0 = new QPushButton(gridLayoutWidget);
        pushButton_0->setObjectName(QStringLiteral("pushButton_0"));
        pushButton_0->setMinimumSize(QSize(80, 70));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(36);
        pushButton_0->setFont(font2);

        gridLayout_calc->addWidget(pushButton_0, 2, 1, 1, 1);

        pushButton_colon = new QPushButton(gridLayoutWidget);
        pushButton_colon->setObjectName(QStringLiteral("pushButton_colon"));
        pushButton_colon->setMinimumSize(QSize(80, 70));
        pushButton_colon->setFont(font1);

        gridLayout_calc->addWidget(pushButton_colon, 2, 2, 1, 1);

        pushButton_back = new QPushButton(gridLayoutWidget);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));
        pushButton_back->setMinimumSize(QSize(80, 70));
        pushButton_back->setFont(font1);

        gridLayout_calc->addWidget(pushButton_back, 2, 3, 1, 1);

        label_display = new QLabel(money);
        label_display->setObjectName(QStringLiteral("label_display"));
        label_display->setGeometry(QRect(20, 80, 441, 161));
        label_display->setMinimumSize(QSize(100, 100));
        QFont font3;
        font3.setFamily(QStringLiteral("Lato"));
        font3.setPointSize(72);
        label_display->setFont(font3);
        label_display->setFrameShape(QFrame::Box);
        label_display->setFrameShadow(QFrame::Plain);
        label_display->setLineWidth(5);
        label_display->setMidLineWidth(0);
        label_display->setAlignment(Qt::AlignCenter);
        pushButton_saveTransaction = new QPushButton(money);
        pushButton_saveTransaction->setObjectName(QStringLiteral("pushButton_saveTransaction"));
        pushButton_saveTransaction->setGeometry(QRect(20, 540, 441, 71));
        pushButton_saveTransaction->setFont(font1);
        label_transactionNotification = new QLabel(money);
        label_transactionNotification->setObjectName(QStringLiteral("label_transactionNotification"));
        label_transactionNotification->setGeometry(QRect(20, 610, 441, 31));
        QFont font4;
        font4.setFamily(QStringLiteral("Lato"));
        font4.setPointSize(10);
        label_transactionNotification->setFont(font4);
        label_transactionID = new QLabel(money);
        label_transactionID->setObjectName(QStringLiteral("label_transactionID"));
        label_transactionID->setGeometry(QRect(20, 640, 441, 21));
        label_transactionID->setFont(font4);
        label_transactionID->setAlignment(Qt::AlignCenter);
        label_error = new QLabel(money);
        label_error->setObjectName(QStringLiteral("label_error"));
        label_error->setGeometry(QRect(20, 10, 441, 61));
        QFont font5;
        font5.setPointSize(14);
        label_error->setFont(font5);
        label_error->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(money);
        settings = new QWidget();
        settings->setObjectName(QStringLiteral("settings"));
        lineEdit_cl = new QLineEdit(settings);
        lineEdit_cl->setObjectName(QStringLiteral("lineEdit_cl"));
        lineEdit_cl->setGeometry(QRect(10, 670, 461, 26));
        lineEdit_cl->setClearButtonEnabled(false);
        textBrowser_clOutput = new QTextBrowser(settings);
        textBrowser_clOutput->setObjectName(QStringLiteral("textBrowser_clOutput"));
        textBrowser_clOutput->setGeometry(QRect(10, 20, 461, 641));
        textBrowser_clOutput->setFrameShape(QFrame::Panel);
        textBrowser_clOutput->setFrameShadow(QFrame::Plain);
        textBrowser_clOutput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_clOutput->setTabChangesFocus(false);
        textBrowser_clOutput->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        stackedWidget->addWidget(settings);
        label_topNotificationBar = new QLabel(centralWidget);
        label_topNotificationBar->setObjectName(QStringLiteral("label_topNotificationBar"));
        label_topNotificationBar->setEnabled(true);
        label_topNotificationBar->setGeometry(QRect(80, 0, 321, 41));
        label_topNotificationBar->setFont(font5);
        label_topNotificationBar->setFrameShape(QFrame::NoFrame);
        label_topNotificationBar->setFrameShadow(QFrame::Plain);
        label_topNotificationBar->setAlignment(Qt::AlignCenter);
        label_topNotificationBar->setTextInteractionFlags(Qt::NoTextInteraction);
        label_balance = new QLabel(centralWidget);
        label_balance->setObjectName(QStringLiteral("label_balance"));
        label_balance->setGeometry(QRect(410, 0, 71, 41));
        label_balance->setFont(font5);
        label_balance->setTextFormat(Qt::AutoText);
        label_balance->setAlignment(Qt::AlignCenter);
        label_balance->setTextInteractionFlags(Qt::NoTextInteraction);
        pushButton_pageBack = new QPushButton(centralWidget);
        pushButton_pageBack->setObjectName(QStringLiteral("pushButton_pageBack"));
        pushButton_pageBack->setGeometry(QRect(0, 750, 80, 41));
        pushButton_pageBack->setFont(font5);
        pushButton_pageBack->setCursor(QCursor(Qt::OpenHandCursor));
        pushButton_pageBack->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QStringLiteral("../res/icons/arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_pageBack->setIcon(icon);
        pushButton_pageBack->setIconSize(QSize(40, 40));
        pushButton_pageBack->setCheckable(false);
        pushButton_pageBack->setAutoDefault(false);
        pushButton_pageBack->setFlat(true);
        pushButton_history = new QPushButton(centralWidget);
        pushButton_history->setObjectName(QStringLiteral("pushButton_history"));
        pushButton_history->setGeometry(QRect(134, 750, 80, 41));
        pushButton_history->setFont(font5);
        pushButton_history->setCursor(QCursor(Qt::OpenHandCursor));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../res/icons/history.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_history->setIcon(icon1);
        pushButton_history->setIconSize(QSize(40, 40));
        pushButton_history->setFlat(true);
        pushButton_settings = new QPushButton(centralWidget);
        pushButton_settings->setObjectName(QStringLiteral("pushButton_settings"));
        pushButton_settings->setEnabled(false);
        pushButton_settings->setGeometry(QRect(400, 750, 80, 41));
        pushButton_settings->setFont(font5);
        pushButton_settings->setCursor(QCursor(Qt::OpenHandCursor));
        QIcon icon2;
        icon2.addFile(QStringLiteral("../res/icons/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_settings->setIcon(icon2);
        pushButton_settings->setIconSize(QSize(40, 40));
        pushButton_settings->setFlat(true);
        pushButton_addMoney = new QPushButton(centralWidget);
        pushButton_addMoney->setObjectName(QStringLiteral("pushButton_addMoney"));
        pushButton_addMoney->setGeometry(QRect(266, 750, 80, 41));
        pushButton_addMoney->setFont(font5);
        pushButton_addMoney->setCursor(QCursor(Qt::OpenHandCursor));
        QIcon icon3;
        icon3.addFile(QStringLiteral("../res/icons/money.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_addMoney->setIcon(icon3);
        pushButton_addMoney->setIconSize(QSize(40, 40));
        pushButton_addMoney->setFlat(true);
        line_top = new QFrame(centralWidget);
        line_top->setObjectName(QStringLiteral("line_top"));
        line_top->setGeometry(QRect(0, 40, 480, 20));
        line_top->setFrameShape(QFrame::HLine);
        line_top->setFrameShadow(QFrame::Sunken);
        lcd_clock = new QLCDNumber(centralWidget);
        lcd_clock->setObjectName(QStringLiteral("lcd_clock"));
        lcd_clock->setGeometry(QRect(0, 10, 80, 31));
        QFont font6;
        font6.setFamily(QStringLiteral("Lato Semibold"));
        font6.setPointSize(14);
        font6.setKerning(false);
        lcd_clock->setFont(font6);
        lcd_clock->setFrameShape(QFrame::NoFrame);
        lcd_clock->setFrameShadow(QFrame::Plain);
        lcd_clock->setLineWidth(2);
        lcd_clock->setSmallDecimalPoint(false);
        lcd_clock->setSegmentStyle(QLCDNumber::Flat);
        userwindow->setCentralWidget(centralWidget);

        retranslateUi(userwindow);

        stackedWidget->setCurrentIndex(0);
        pushButton_pageBack->setDefault(false);


        QMetaObject::connectSlotsByName(userwindow);
    } // setupUi

    void retranslateUi(QMainWindow *userwindow)
    {
        userwindow->setWindowTitle(QApplication::translate("userwindow", "ags Getr\303\244nkekasse", 0));
        label_infobox->setText(QString());
        pushButton_1->setText(QApplication::translate("userwindow", "1", 0));
        pushButton_2->setText(QApplication::translate("userwindow", "2", 0));
        pushButton_3->setText(QApplication::translate("userwindow", "3", 0));
        pushButton_4->setText(QApplication::translate("userwindow", "4", 0));
        pushButton_5->setText(QApplication::translate("userwindow", "5", 0));
        pushButton_6->setText(QApplication::translate("userwindow", "6", 0));
        pushButton_7->setText(QApplication::translate("userwindow", "7", 0));
        pushButton_8->setText(QApplication::translate("userwindow", "8", 0));
        pushButton_9->setText(QApplication::translate("userwindow", "9", 0));
        pushButton_0->setText(QApplication::translate("userwindow", "0", 0));
        pushButton_colon->setText(QApplication::translate("userwindow", ",", 0));
        pushButton_back->setText(QApplication::translate("userwindow", "\342\207\246", 0));
        label_display->setText(QString());
        pushButton_saveTransaction->setText(QApplication::translate("userwindow", "Geld hinzuf\303\274gen", 0));
        label_transactionNotification->setText(QApplication::translate("userwindow", "<html><head/><body><p align=\"center\">Bitte folgende Buchungsnummer auf dem Geldumschlag angeben:</p></body></html>", 0));
        label_transactionID->setText(QApplication::translate("userwindow", "<html><head/><body><p align=\"center\">#000000</p></body></html>", 0));
        label_error->setText(QString());
        textBrowser_clOutput->setHtml(QApplication::translate("userwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lato Medium'; font-size:11pt; font-weight:400; font-style:normal;\" bgcolor=\"#000000\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        label_topNotificationBar->setText(QApplication::translate("userwindow", "Chris", 0));
        label_balance->setText(QApplication::translate("userwindow", "5,70 \342\202\254", 0));
        pushButton_pageBack->setText(QString());
        pushButton_history->setText(QString());
        pushButton_settings->setText(QString());
        pushButton_addMoney->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class userwindow: public Ui_userwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERWINDOW_H
