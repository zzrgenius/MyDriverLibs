/********************************************************************************
** Form generated from reading UI file 'changebinfile.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEBINFILE_H
#define UI_CHANGEBINFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeBinFile
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *fileSizeEdit;
    QLabel *label_4;
    QLineEdit *crcEdit;
    QWidget *widget1;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLineEdit *fileNameEdit;
    QPushButton *choiceFileBtn;
    QLabel *label_2;
    QComboBox *pageComBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *startBtn;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChangeBinFile)
    {
        if (ChangeBinFile->objectName().isEmpty())
            ChangeBinFile->setObjectName(QStringLiteral("ChangeBinFile"));
        ChangeBinFile->resize(400, 300);
        centralWidget = new QWidget(ChangeBinFile);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 150, 361, 121));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 30, 189, 61));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        fileSizeEdit = new QLineEdit(widget);
        fileSizeEdit->setObjectName(QStringLiteral("fileSizeEdit"));

        gridLayout->addWidget(fileSizeEdit, 0, 1, 1, 1);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        crcEdit = new QLineEdit(widget);
        crcEdit->setObjectName(QStringLiteral("crcEdit"));

        gridLayout->addWidget(crcEdit, 1, 1, 1, 1);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(20, 20, 361, 121));
        gridLayout_2 = new QGridLayout(widget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        fileNameEdit = new QLineEdit(widget1);
        fileNameEdit->setObjectName(QStringLiteral("fileNameEdit"));

        gridLayout_2->addWidget(fileNameEdit, 0, 1, 1, 2);

        choiceFileBtn = new QPushButton(widget1);
        choiceFileBtn->setObjectName(QStringLiteral("choiceFileBtn"));

        gridLayout_2->addWidget(choiceFileBtn, 0, 3, 1, 1);

        label_2 = new QLabel(widget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        pageComBox = new QComboBox(widget1);
        pageComBox->setObjectName(QStringLiteral("pageComBox"));

        gridLayout_2->addWidget(pageComBox, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        startBtn = new QPushButton(widget1);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setEnabled(false);

        gridLayout_2->addWidget(startBtn, 2, 3, 1, 1);

        ChangeBinFile->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChangeBinFile);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChangeBinFile->setStatusBar(statusBar);

        retranslateUi(ChangeBinFile);

        QMetaObject::connectSlotsByName(ChangeBinFile);
    } // setupUi

    void retranslateUi(QMainWindow *ChangeBinFile)
    {
        ChangeBinFile->setWindowTitle(QApplication::translate("ChangeBinFile", "ChangeBinFile", nullptr));
        groupBox->setTitle(QApplication::translate("ChangeBinFile", "\346\226\207\344\273\266\344\277\241\346\201\257", nullptr));
        label_3->setText(QApplication::translate("ChangeBinFile", "\346\226\207\344\273\266\345\244\247\345\260\217", nullptr));
        label_4->setText(QApplication::translate("ChangeBinFile", "\346\225\260\346\215\256CRC16", nullptr));
        label->setText(QApplication::translate("ChangeBinFile", "\345\216\237\345\247\213Bin\346\226\207\344\273\266", nullptr));
        choiceFileBtn->setText(QApplication::translate("ChangeBinFile", "\351\200\211\346\213\251", nullptr));
        label_2->setText(QApplication::translate("ChangeBinFile", "\345\210\206\351\241\265\345\244\247\345\260\217", nullptr));
        startBtn->setText(QApplication::translate("ChangeBinFile", "\345\220\257\345\212\250\350\275\254\346\215\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangeBinFile: public Ui_ChangeBinFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEBINFILE_H
