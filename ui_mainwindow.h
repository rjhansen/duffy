/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Jul 7 16:14:15 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionClose;
    QAction *actionQuit;
    QAction *actionHelp_index;
    QAction *actionAbout_Duffy;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *showing;
    QComboBox *knownToggle;
    QComboBox *fileType;
    QLabel *changedSince;
    QDateEdit *dateEdit;
    QTreeWidget *treeWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(613, 430);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Duffy.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/Document-new.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/Document-open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/Document-save.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionSave_as->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/Document-save-as.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon4);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionClose->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/Document-close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon5);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/System-log-out.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon6);
        actionHelp_index = new QAction(MainWindow);
        actionHelp_index->setObjectName(QString::fromUtf8("actionHelp_index"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/Help-browser.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp_index->setIcon(icon7);
        actionAbout_Duffy = new QAction(MainWindow);
        actionAbout_Duffy->setObjectName(QString::fromUtf8("actionAbout_Duffy"));
        actionAbout_Duffy->setIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        showing = new QLabel(centralWidget);
        showing->setObjectName(QString::fromUtf8("showing"));
        showing->setEnabled(true);

        horizontalLayout->addWidget(showing);

        knownToggle = new QComboBox(centralWidget);
        knownToggle->setObjectName(QString::fromUtf8("knownToggle"));
        knownToggle->setEnabled(true);

        horizontalLayout->addWidget(knownToggle);

        fileType = new QComboBox(centralWidget);
        fileType->setObjectName(QString::fromUtf8("fileType"));
        fileType->setEnabled(true);

        horizontalLayout->addWidget(fileType);

        changedSince = new QLabel(centralWidget);
        changedSince->setObjectName(QString::fromUtf8("changedSince"));
        changedSince->setEnabled(true);

        horizontalLayout->addWidget(changedSince);

        dateEdit = new QDateEdit(centralWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setEnabled(true);

        horizontalLayout->addWidget(dateEdit);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        treeWidget = new QTreeWidget(centralWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setEnabled(true);

        verticalLayout->addWidget(treeWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 613, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionClose);
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionHelp_index);
        menuHelp->addAction(actionAbout_Duffy);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Sgt. Duffy", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionHelp_index->setText(QApplication::translate("MainWindow", "Help index", 0, QApplication::UnicodeUTF8));
        actionAbout_Duffy->setText(QApplication::translate("MainWindow", "About Duffy", 0, QApplication::UnicodeUTF8));
        showing->setText(QApplication::translate("MainWindow", "Showing", 0, QApplication::UnicodeUTF8));
        knownToggle->clear();
        knownToggle->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "known", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "unknown", 0, QApplication::UnicodeUTF8)
        );
        fileType->clear();
        fileType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "files", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "executables", 0, QApplication::UnicodeUTF8)
        );
        changedSince->setText(QApplication::translate("MainWindow", "changed since", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "MD5 hash", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Modified", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Filename", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
