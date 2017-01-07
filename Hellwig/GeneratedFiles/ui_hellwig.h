/********************************************************************************
** Form generated from reading UI file 'hellwig.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLWIG_H
#define UI_HELLWIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HellwigClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget_Data;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTableWidget *tableWidget_MatrixR;
    QTableWidget *tableWidget_MatrixR0;
    QSpacerItem *verticalSpacer;
    QWidget *tab_3;
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_comb_num;
    QLabel *label_best_comb;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QFormLayout *formLayout;
    QLabel *label_4;
    QComboBox *comboBox_comb;
    QLabel *label_int_cap;
    QLabel *label_indv_cap;
    QListWidget *listWidget_indv_cap;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_calc_hellwig;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *HellwigClass)
    {
        if (HellwigClass->objectName().isEmpty())
            HellwigClass->setObjectName(QStringLiteral("HellwigClass"));
        HellwigClass->resize(524, 218);
        centralWidget = new QWidget(HellwigClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        tableWidget_Data = new QTableWidget(tab);
        tableWidget_Data->setObjectName(QStringLiteral("tableWidget_Data"));
        tableWidget_Data->horizontalHeader()->setDefaultSectionSize(70);
        tableWidget_Data->horizontalHeader()->setMinimumSectionSize(15);
        tableWidget_Data->horizontalHeader()->setStretchLastSection(true);
        tableWidget_Data->verticalHeader()->setDefaultSectionSize(23);

        horizontalLayout->addWidget(tableWidget_Data);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        splitter = new QSplitter(tab_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableWidget_MatrixR = new QTableWidget(splitter);
        tableWidget_MatrixR->setObjectName(QStringLiteral("tableWidget_MatrixR"));
        splitter->addWidget(tableWidget_MatrixR);
        tableWidget_MatrixR->horizontalHeader()->setDefaultSectionSize(70);
        tableWidget_MatrixR->horizontalHeader()->setMinimumSectionSize(15);
        tableWidget_MatrixR->horizontalHeader()->setStretchLastSection(true);
        tableWidget_MatrixR->verticalHeader()->setDefaultSectionSize(23);
        tableWidget_MatrixR->verticalHeader()->setStretchLastSection(true);
        tableWidget_MatrixR0 = new QTableWidget(splitter);
        tableWidget_MatrixR0->setObjectName(QStringLiteral("tableWidget_MatrixR0"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget_MatrixR0->sizePolicy().hasHeightForWidth());
        tableWidget_MatrixR0->setSizePolicy(sizePolicy);
        tableWidget_MatrixR0->setMaximumSize(QSize(100, 16777215));
        splitter->addWidget(tableWidget_MatrixR0);
        tableWidget_MatrixR0->horizontalHeader()->setVisible(false);
        tableWidget_MatrixR0->horizontalHeader()->setDefaultSectionSize(70);
        tableWidget_MatrixR0->horizontalHeader()->setMinimumSectionSize(15);
        tableWidget_MatrixR0->horizontalHeader()->setStretchLastSection(true);
        tableWidget_MatrixR0->verticalHeader()->setDefaultSectionSize(23);
        tableWidget_MatrixR0->verticalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(splitter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout = new QGridLayout(tab_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        frame = new QFrame(tab_3);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_comb_num = new QLabel(frame);
        label_comb_num->setObjectName(QStringLiteral("label_comb_num"));

        verticalLayout_3->addWidget(label_comb_num);

        label_best_comb = new QLabel(frame);
        label_best_comb->setObjectName(QStringLiteral("label_best_comb"));

        verticalLayout_3->addWidget(label_best_comb);


        gridLayout->addWidget(frame, 0, 0, 1, 3);

        frame_2 = new QFrame(tab_3);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        comboBox_comb = new QComboBox(frame_2);
        comboBox_comb->setObjectName(QStringLiteral("comboBox_comb"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox_comb);


        verticalLayout_4->addLayout(formLayout);

        label_int_cap = new QLabel(frame_2);
        label_int_cap->setObjectName(QStringLiteral("label_int_cap"));

        verticalLayout_4->addWidget(label_int_cap);

        label_indv_cap = new QLabel(frame_2);
        label_indv_cap->setObjectName(QStringLiteral("label_indv_cap"));

        verticalLayout_4->addWidget(label_indv_cap);

        listWidget_indv_cap = new QListWidget(frame_2);
        listWidget_indv_cap->setObjectName(QStringLiteral("listWidget_indv_cap"));

        verticalLayout_4->addWidget(listWidget_indv_cap);


        gridLayout->addWidget(frame_2, 0, 3, 3, 1);

        horizontalSpacer = new QSpacerItem(46, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton_calc_hellwig = new QPushButton(tab_3);
        pushButton_calc_hellwig->setObjectName(QStringLiteral("pushButton_calc_hellwig"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/calculator.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_calc_hellwig->setIcon(icon);
        pushButton_calc_hellwig->setFlat(true);

        gridLayout->addWidget(pushButton_calc_hellwig, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(46, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 98, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        gridLayout->setColumnStretch(3, 1);
        tabWidget->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tabWidget);

        HellwigClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(HellwigClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HellwigClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(HellwigClass);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(HellwigClass);
    } // setupUi

    void retranslateUi(QMainWindow *HellwigClass)
    {
        HellwigClass->setWindowTitle(QApplication::translate("HellwigClass", "Hellwig", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("HellwigClass", "Data", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("HellwigClass", "R | R0", 0));
        label_comb_num->setText(QApplication::translate("HellwigClass", "Combinations number: 0", 0));
        label_best_comb->setText(QApplication::translate("HellwigClass", "Best combination: 0", 0));
        label_4->setText(QApplication::translate("HellwigClass", "Combination:", 0));
        label_int_cap->setText(QApplication::translate("HellwigClass", "Integral capacity: H0 = 0", 0));
        label_indv_cap->setText(QApplication::translate("HellwigClass", "Individual capacity:", 0));
        pushButton_calc_hellwig->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("HellwigClass", "Hellwig", 0));
    } // retranslateUi

};

namespace Ui {
    class HellwigClass: public Ui_HellwigClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLWIG_H
