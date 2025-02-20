/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCalendar_View;
    QAction *actionTemplates;
    QAction *actionSound_Files;
    QAction *actionHome;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *HomePage;
    QLabel *CurrentDate_Label;
    QPushButton *playSoundBtn;
    QComboBox *soundComboBox;
    QLabel *playingLabel;
    QPushButton *stopSoundBtn;
    QPushButton *addSoundBtn;
    QTextEdit *timeInput;
    QListWidget *scheduledSounds;
    QPushButton *removeSoundBtn;
    QLabel *nextSound;
    QLabel *currTemplate;
    QTextEdit *volumeInputHome;
    QCheckBox *NextDayCheckHome;
    QCheckBox *repeatBtn;
    QWidget *CalendarPage;
    QVBoxLayout *verticalLayout;
    QComboBox *templateDropdownCalendar;
    QPushButton *setTemplateCalendar;
    QPushButton *resetCalendarBtn;
    QCalendarWidget *calendarWidget;
    QWidget *Templates;
    QLabel *label;
    QListWidget *templateSoundSchedule;
    QComboBox *soundComboBoxTemplate;
    QTextEdit *timeInputTemplate;
    QPushButton *removeSoundBtnTemplate;
    QPushButton *addSoundBtnTemplate;
    QCheckBox *MondayCheck;
    QCheckBox *TuesdayCheck;
    QCheckBox *WednesdayCheck;
    QCheckBox *ThursdayCheck;
    QCheckBox *FridayCheck;
    QCheckBox *SaturdayCheck;
    QCheckBox *SundayCheck;
    QPushButton *setTemplateBtn;
    QComboBox *templateDropdown;
    QTextEdit *templateNameInput;
    QCheckBox *NextDayCheck;
    QTextEdit *volumeInput;
    QPushButton *deleteTemplateBtn;
    QPushButton *newTemplateBtn;
    QPushButton *updateTemplateBtn;
    QLabel *deconflictLabel;
    QWidget *SoundFiles;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuCWOC_Sound_Scheduler;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(629, 672);
        actionCalendar_View = new QAction(MainWindow);
        actionCalendar_View->setObjectName("actionCalendar_View");
        actionTemplates = new QAction(MainWindow);
        actionTemplates->setObjectName("actionTemplates");
        actionSound_Files = new QAction(MainWindow);
        actionSound_Files->setObjectName("actionSound_Files");
        actionHome = new QAction(MainWindow);
        actionHome->setObjectName("actionHome");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        HomePage = new QWidget();
        HomePage->setObjectName("HomePage");
        CurrentDate_Label = new QLabel(HomePage);
        CurrentDate_Label->setObjectName("CurrentDate_Label");
        CurrentDate_Label->setGeometry(QRect(0, 10, 171, 21));
        CurrentDate_Label->setFrameShape(QFrame::Shape::Box);
        playSoundBtn = new QPushButton(HomePage);
        playSoundBtn->setObjectName("playSoundBtn");
        playSoundBtn->setGeometry(QRect(0, 100, 80, 31));
        playSoundBtn->setAutoDefault(true);
        soundComboBox = new QComboBox(HomePage);
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->addItem(QString());
        soundComboBox->setObjectName("soundComboBox");
        soundComboBox->setGeometry(QRect(0, 70, 171, 21));
        playingLabel = new QLabel(HomePage);
        playingLabel->setObjectName("playingLabel");
        playingLabel->setGeometry(QRect(0, 40, 171, 21));
        playingLabel->setFrameShape(QFrame::Shape::Box);
        stopSoundBtn = new QPushButton(HomePage);
        stopSoundBtn->setObjectName("stopSoundBtn");
        stopSoundBtn->setGeometry(QRect(90, 100, 81, 31));
        stopSoundBtn->setAutoDefault(true);
        addSoundBtn = new QPushButton(HomePage);
        addSoundBtn->setObjectName("addSoundBtn");
        addSoundBtn->setGeometry(QRect(0, 220, 171, 21));
        addSoundBtn->setAutoDefault(true);
        timeInput = new QTextEdit(HomePage);
        timeInput->setObjectName("timeInput");
        timeInput->setGeometry(QRect(0, 180, 81, 31));
        scheduledSounds = new QListWidget(HomePage);
        scheduledSounds->setObjectName("scheduledSounds");
        scheduledSounds->setGeometry(QRect(180, 70, 256, 391));
        scheduledSounds->setResizeMode(QListView::ResizeMode::Adjust);
        removeSoundBtn = new QPushButton(HomePage);
        removeSoundBtn->setObjectName("removeSoundBtn");
        removeSoundBtn->setGeometry(QRect(0, 250, 171, 21));
        removeSoundBtn->setAutoDefault(true);
        nextSound = new QLabel(HomePage);
        nextSound->setObjectName("nextSound");
        nextSound->setGeometry(QRect(180, 40, 251, 16));
        nextSound->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        currTemplate = new QLabel(HomePage);
        currTemplate->setObjectName("currTemplate");
        currTemplate->setGeometry(QRect(180, 10, 251, 20));
        currTemplate->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        volumeInputHome = new QTextEdit(HomePage);
        volumeInputHome->setObjectName("volumeInputHome");
        volumeInputHome->setGeometry(QRect(90, 180, 81, 31));
        NextDayCheckHome = new QCheckBox(HomePage);
        NextDayCheckHome->setObjectName("NextDayCheckHome");
        NextDayCheckHome->setGeometry(QRect(10, 280, 111, 18));
        repeatBtn = new QCheckBox(HomePage);
        repeatBtn->setObjectName("repeatBtn");
        repeatBtn->setGeometry(QRect(10, 140, 111, 18));
        stackedWidget->addWidget(HomePage);
        CalendarPage = new QWidget();
        CalendarPage->setObjectName("CalendarPage");
        verticalLayout = new QVBoxLayout(CalendarPage);
        verticalLayout->setObjectName("verticalLayout");
        templateDropdownCalendar = new QComboBox(CalendarPage);
        templateDropdownCalendar->setObjectName("templateDropdownCalendar");

        verticalLayout->addWidget(templateDropdownCalendar);

        setTemplateCalendar = new QPushButton(CalendarPage);
        setTemplateCalendar->setObjectName("setTemplateCalendar");

        verticalLayout->addWidget(setTemplateCalendar);

        resetCalendarBtn = new QPushButton(CalendarPage);
        resetCalendarBtn->setObjectName("resetCalendarBtn");

        verticalLayout->addWidget(resetCalendarBtn);

        calendarWidget = new QCalendarWidget(CalendarPage);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGridVisible(true);

        verticalLayout->addWidget(calendarWidget);

        stackedWidget->addWidget(CalendarPage);
        Templates = new QWidget();
        Templates->setObjectName("Templates");
        label = new QLabel(Templates);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 471, 21));
        label->setFrameShape(QFrame::Shape::Box);
        label->setFrameShadow(QFrame::Shadow::Raised);
        label->setLineWidth(1);
        label->setTextFormat(Qt::TextFormat::MarkdownText);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        templateSoundSchedule = new QListWidget(Templates);
        templateSoundSchedule->setObjectName("templateSoundSchedule");
        templateSoundSchedule->setGeometry(QRect(210, 30, 256, 331));
        templateSoundSchedule->setResizeMode(QListView::ResizeMode::Adjust);
        soundComboBoxTemplate = new QComboBox(Templates);
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->addItem(QString());
        soundComboBoxTemplate->setObjectName("soundComboBoxTemplate");
        soundComboBoxTemplate->setGeometry(QRect(10, 60, 191, 21));
        timeInputTemplate = new QTextEdit(Templates);
        timeInputTemplate->setObjectName("timeInputTemplate");
        timeInputTemplate->setGeometry(QRect(10, 90, 191, 31));
        removeSoundBtnTemplate = new QPushButton(Templates);
        removeSoundBtnTemplate->setObjectName("removeSoundBtnTemplate");
        removeSoundBtnTemplate->setGeometry(QRect(100, 130, 101, 21));
        removeSoundBtnTemplate->setAutoDefault(true);
        addSoundBtnTemplate = new QPushButton(Templates);
        addSoundBtnTemplate->setObjectName("addSoundBtnTemplate");
        addSoundBtnTemplate->setGeometry(QRect(10, 130, 80, 21));
        addSoundBtnTemplate->setAutoDefault(true);
        MondayCheck = new QCheckBox(Templates);
        MondayCheck->setObjectName("MondayCheck");
        MondayCheck->setGeometry(QRect(10, 160, 71, 18));
        TuesdayCheck = new QCheckBox(Templates);
        TuesdayCheck->setObjectName("TuesdayCheck");
        TuesdayCheck->setGeometry(QRect(10, 180, 81, 18));
        WednesdayCheck = new QCheckBox(Templates);
        WednesdayCheck->setObjectName("WednesdayCheck");
        WednesdayCheck->setGeometry(QRect(10, 200, 91, 18));
        ThursdayCheck = new QCheckBox(Templates);
        ThursdayCheck->setObjectName("ThursdayCheck");
        ThursdayCheck->setGeometry(QRect(10, 220, 81, 18));
        FridayCheck = new QCheckBox(Templates);
        FridayCheck->setObjectName("FridayCheck");
        FridayCheck->setGeometry(QRect(10, 240, 71, 18));
        SaturdayCheck = new QCheckBox(Templates);
        SaturdayCheck->setObjectName("SaturdayCheck");
        SaturdayCheck->setGeometry(QRect(10, 260, 81, 18));
        SundayCheck = new QCheckBox(Templates);
        SundayCheck->setObjectName("SundayCheck");
        SundayCheck->setGeometry(QRect(10, 280, 81, 18));
        setTemplateBtn = new QPushButton(Templates);
        setTemplateBtn->setObjectName("setTemplateBtn");
        setTemplateBtn->setGeometry(QRect(10, 400, 191, 21));
        setTemplateBtn->setAutoDefault(true);
        templateDropdown = new QComboBox(Templates);
        templateDropdown->setObjectName("templateDropdown");
        templateDropdown->setGeometry(QRect(10, 30, 191, 21));
        templateNameInput = new QTextEdit(Templates);
        templateNameInput->setObjectName("templateNameInput");
        templateNameInput->setGeometry(QRect(10, 300, 191, 31));
        NextDayCheck = new QCheckBox(Templates);
        NextDayCheck->setObjectName("NextDayCheck");
        NextDayCheck->setGeometry(QRect(90, 280, 111, 18));
        volumeInput = new QTextEdit(Templates);
        volumeInput->setObjectName("volumeInput");
        volumeInput->setGeometry(QRect(90, 160, 111, 31));
        deleteTemplateBtn = new QPushButton(Templates);
        deleteTemplateBtn->setObjectName("deleteTemplateBtn");
        deleteTemplateBtn->setGeometry(QRect(10, 370, 191, 21));
        deleteTemplateBtn->setAutoDefault(true);
        newTemplateBtn = new QPushButton(Templates);
        newTemplateBtn->setObjectName("newTemplateBtn");
        newTemplateBtn->setGeometry(QRect(10, 340, 191, 21));
        newTemplateBtn->setAutoDefault(true);
        updateTemplateBtn = new QPushButton(Templates);
        updateTemplateBtn->setObjectName("updateTemplateBtn");
        updateTemplateBtn->setGeometry(QRect(10, 430, 191, 21));
        updateTemplateBtn->setAutoDefault(true);
        deconflictLabel = new QLabel(Templates);
        deconflictLabel->setObjectName("deconflictLabel");
        deconflictLabel->setGeometry(QRect(210, 370, 251, 81));
        deconflictLabel->setAutoFillBackground(true);
        deconflictLabel->setWordWrap(true);
        stackedWidget->addWidget(Templates);
        SoundFiles = new QWidget();
        SoundFiles->setObjectName("SoundFiles");
        stackedWidget->addWidget(SoundFiles);

        verticalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 629, 17));
        menuCWOC_Sound_Scheduler = new QMenu(menubar);
        menuCWOC_Sound_Scheduler->setObjectName("menuCWOC_Sound_Scheduler");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuCWOC_Sound_Scheduler->menuAction());
        menuCWOC_Sound_Scheduler->addAction(actionHome);
        menuCWOC_Sound_Scheduler->addAction(actionCalendar_View);
        menuCWOC_Sound_Scheduler->addAction(actionTemplates);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionCalendar_View->setText(QCoreApplication::translate("MainWindow", "Calendar View", nullptr));
        actionTemplates->setText(QCoreApplication::translate("MainWindow", "Templates", nullptr));
        actionSound_Files->setText(QCoreApplication::translate("MainWindow", "Sound Files", nullptr));
        actionHome->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        CurrentDate_Label->setText(QCoreApplication::translate("MainWindow", "Current Date & Time", nullptr));
        playSoundBtn->setText(QCoreApplication::translate("MainWindow", "Play Sound", nullptr));
        soundComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Assembly", nullptr));
        soundComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Reveille and To the Colors", nullptr));
        soundComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "ACQ", nullptr));
        soundComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Taps", nullptr));
        soundComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "First Call", nullptr));
        soundComboBox->setItemText(5, QCoreApplication::translate("MainWindow", "6-8 Drum Cadence, 4 minutes", nullptr));
        soundComboBox->setItemText(6, QCoreApplication::translate("MainWindow", "Cadence (BCT), 8 minutes", nullptr));
        soundComboBox->setItemText(7, QCoreApplication::translate("MainWindow", "National Anthem", nullptr));
        soundComboBox->setItemText(8, QCoreApplication::translate("MainWindow", "Retreat", nullptr));
        soundComboBox->setItemText(9, QCoreApplication::translate("MainWindow", "To the Colors", nullptr));
        soundComboBox->setItemText(10, QCoreApplication::translate("MainWindow", "Bonk", nullptr));

        playingLabel->setText(QCoreApplication::translate("MainWindow", " Currently playing: None", nullptr));
        stopSoundBtn->setText(QCoreApplication::translate("MainWindow", "Stop Sound", nullptr));
        addSoundBtn->setText(QCoreApplication::translate("MainWindow", "Add Sound", nullptr));
        removeSoundBtn->setText(QCoreApplication::translate("MainWindow", "Remove Sound", nullptr));
        nextSound->setText(QCoreApplication::translate("MainWindow", "Playing next: ", nullptr));
        currTemplate->setText(QCoreApplication::translate("MainWindow", "Today's Template: ", nullptr));
        volumeInputHome->setPlaceholderText(QString());
        NextDayCheckHome->setText(QCoreApplication::translate("MainWindow", "Play Next Day", nullptr));
        repeatBtn->setText(QCoreApplication::translate("MainWindow", "Repeat", nullptr));
        setTemplateCalendar->setText(QCoreApplication::translate("MainWindow", "Set Template", nullptr));
        resetCalendarBtn->setText(QCoreApplication::translate("MainWindow", "Reset to Default", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Templates", nullptr));
        soundComboBoxTemplate->setItemText(0, QCoreApplication::translate("MainWindow", "Assembly", nullptr));
        soundComboBoxTemplate->setItemText(1, QCoreApplication::translate("MainWindow", "Reveille and To the Colors", nullptr));
        soundComboBoxTemplate->setItemText(2, QCoreApplication::translate("MainWindow", "ACQ", nullptr));
        soundComboBoxTemplate->setItemText(3, QCoreApplication::translate("MainWindow", "Taps", nullptr));
        soundComboBoxTemplate->setItemText(4, QCoreApplication::translate("MainWindow", "First Call", nullptr));
        soundComboBoxTemplate->setItemText(5, QCoreApplication::translate("MainWindow", "6-8 Drum Cadence, 4 minutes", nullptr));
        soundComboBoxTemplate->setItemText(6, QCoreApplication::translate("MainWindow", "Retreat", nullptr));
        soundComboBoxTemplate->setItemText(7, QCoreApplication::translate("MainWindow", "Cadence (BCT), 8 minutes", nullptr));
        soundComboBoxTemplate->setItemText(8, QCoreApplication::translate("MainWindow", "National Anthem", nullptr));
        soundComboBoxTemplate->setItemText(9, QCoreApplication::translate("MainWindow", "To the Colors", nullptr));
        soundComboBoxTemplate->setItemText(10, QCoreApplication::translate("MainWindow", "Bonk", nullptr));

        timeInputTemplate->setPlaceholderText(QString());
        removeSoundBtnTemplate->setText(QCoreApplication::translate("MainWindow", "Remove Sound", nullptr));
        addSoundBtnTemplate->setText(QCoreApplication::translate("MainWindow", "Add Sound", nullptr));
        MondayCheck->setText(QCoreApplication::translate("MainWindow", "Monday", nullptr));
        TuesdayCheck->setText(QCoreApplication::translate("MainWindow", "Tuesday", nullptr));
        WednesdayCheck->setText(QCoreApplication::translate("MainWindow", "Wednesday", nullptr));
        ThursdayCheck->setText(QCoreApplication::translate("MainWindow", "Thursday", nullptr));
        FridayCheck->setText(QCoreApplication::translate("MainWindow", "Friday", nullptr));
        SaturdayCheck->setText(QCoreApplication::translate("MainWindow", "Saturday", nullptr));
        SundayCheck->setText(QCoreApplication::translate("MainWindow", "Sunday", nullptr));
        setTemplateBtn->setText(QCoreApplication::translate("MainWindow", "Set Template", nullptr));
        templateNameInput->setPlaceholderText(QString());
        NextDayCheck->setText(QCoreApplication::translate("MainWindow", "Play Next Day", nullptr));
        volumeInput->setPlaceholderText(QString());
        deleteTemplateBtn->setText(QCoreApplication::translate("MainWindow", "Delete Template", nullptr));
        newTemplateBtn->setText(QCoreApplication::translate("MainWindow", "New Template", nullptr));
        updateTemplateBtn->setText(QCoreApplication::translate("MainWindow", "Update Template", nullptr));
        deconflictLabel->setText(QString());
        menuCWOC_Sound_Scheduler->setTitle(QCoreApplication::translate("MainWindow", "CWOC Sound Scheduler", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
