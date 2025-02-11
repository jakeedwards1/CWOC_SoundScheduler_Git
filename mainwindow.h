#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMediaPlayer>
#include <qcalendarwidget.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qdatetime.h>
#include <QString>
#include <qlistwidget.h>
#include <qtextedit.h>
#include <QList>

struct sound {
    QString soundName;
    QString time;
    float volume;
    bool playTmr;
};

struct Template{
    QString templateName;
    QList<sound> playlist;
    bool daysPlayed[7];
};

struct DateTemplate {
    QDate date;
    QString templateName;
};


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void clock();

    bool playSound(QString soundFile, QString volumeStr, bool playNextDay);
    void playImmediateSound();
    void stopSound();
    void addSound(QListWidget *listWidget, sound soundToAdd);
    void removeSound(QListWidget *listWidget);

    void sortListWidget(QListWidget* listWidget);

    void nextSound();
    void checkTime();
    bool checkVolumeFormat(QString volumeInput);
    bool checkTimeFormat(QString timeToAdd);
    sound getSoundData(QListWidget *listWidget);
    sound getItemData(QListWidgetItem *item);
    sound retriveSoundData(QListWidget *listWidget, int index);
    void checkDay();

    void CalendarPage();
    void HomePage();
    void Templates();
    void SoundFiles();

    void closeEvent(QCloseEvent *event);
    void restoreState();

    void setNewTemplate();
    void viewTemplate(QListWidget *listWidget,Template displayTemplate);
    void deleteTemplate();
    void updateTemplate();
    void newTemplate();
    bool deconflictTemplates(Template newTemplate);
    Template returnTemplate(QString templateName);

    void updateCalendar();
    void populateDefaultTemplates();
    void refreshCalendar();
    void updateDateTemplateList();
    void resetCalendar();


private:
    Ui::MainWindow *ui;
    QString currentSoundFile;
    QMediaPlayer *player;
    QDateTime date_time;
    QString lastPlayedTime;
    QList<Template> allTemplates;
    int nextIndex = 0;
    QVector<QCheckBox*> dayCheckBoxes;
    Template prevTemplate;
    QList<DateTemplate> dateTemplateList;
};
#endif // MAINWINDOW_H
