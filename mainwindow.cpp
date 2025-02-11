#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <QDateTime>
#include <QTimer>
#include <QUrl>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QPushButton>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QSettings>
#include <QList>
#include <QString>
#include <QDataStream>
#include <QFile>
#include <QDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    restoreState();

    ui->stackedWidget->setCurrentIndex(0);

    ui->timeInputTemplate->setPlaceholderText("Time input");
    ui->timeInput->setPlaceholderText("Time input");
    ui->templateNameInput->setPlaceholderText("Template name");
    ui->volumeInput->setPlaceholderText("Volume");
    ui->volumeInputHome->setPlaceholderText("Volume");

    dayCheckBoxes = {ui->MondayCheck, ui->TuesdayCheck, ui->WednesdayCheck,
                     ui->ThursdayCheck, ui->FridayCheck, ui->SaturdayCheck, ui->SundayCheck};
    ui->templateDropdown->setCurrentIndex(-1);
    ui->templateDropdownCalendar->setCurrentIndex(-1);

    lastPlayedTime = 0;

    QTimer *timerClk = new QTimer(this);
    connect(timerClk,SIGNAL(timeout()),this,SLOT(clock()));
    timerClk->start(500);

    QTimer *timerCheckSound= new QTimer(this);
    connect(timerCheckSound,SIGNAL(timeout()),this,SLOT(checkTime()));
    timerCheckSound->start(1000);

    QTimer *timerCheckDay= new QTimer(this);
    connect(timerCheckDay,SIGNAL(timeout()),this,SLOT(checkDay()));
    timerCheckDay->start(3000);

    QTimer *timerRefreshCal= new QTimer(this);
    connect(timerCheckDay,SIGNAL(timeout()),this,SLOT(refreshCalendar()));
    timerRefreshCal->start(5000);



    player = new QMediaPlayer(this);

    connect(ui->playSoundBtn, &QPushButton::clicked, this, &MainWindow::playImmediateSound);
    connect(ui->stopSoundBtn, &QPushButton::clicked, this, &MainWindow::stopSound);

    connect(ui->addSoundBtn, &QPushButton::clicked, this, [this](){
        addSound(ui->scheduledSounds,getSoundData((ui->scheduledSounds)));
    });
    connect(ui->addSoundBtnTemplate, &QPushButton::clicked, this, [this](){
        addSound(ui->templateSoundSchedule,getSoundData((ui->templateSoundSchedule)));
    });

    connect(ui->removeSoundBtn, &QPushButton::clicked, this, [this](){
        removeSound(ui->scheduledSounds);
    });
    connect(ui->removeSoundBtnTemplate, &QPushButton::clicked, this, [this](){
        removeSound(ui->templateSoundSchedule);
    });


    connect(ui->actionCalendar_View, &QAction::triggered, this, &MainWindow::CalendarPage);
    connect(ui->actionHome, &QAction::triggered, this, &MainWindow::HomePage);
    connect(ui->actionTemplates, &QAction::triggered, this, &MainWindow::Templates);
    connect(ui->actionSound_Files, &QAction::triggered, this, &MainWindow::SoundFiles);

    connect(ui->setTemplateBtn, &QPushButton::clicked, this, &MainWindow::setNewTemplate);

    connect(ui->templateDropdown, &QComboBox::currentIndexChanged, this, [this](){
        Template blankTemplate;
        viewTemplate(ui->templateSoundSchedule,blankTemplate);
    });

    connect(ui->deleteTemplateBtn, &QPushButton::clicked,this,&MainWindow::deleteTemplate);
    connect(ui->updateTemplateBtn, &QPushButton::clicked,this,&MainWindow::updateTemplate);
    connect(ui->newTemplateBtn, &QPushButton::clicked,this,&MainWindow::newTemplate);
    connect(ui->setTemplateCalendar,&QPushButton::clicked,this,&MainWindow::updateDateTemplateList);
    connect(ui->resetCalendarBtn,&QPushButton::clicked,this,&MainWindow::resetCalendar);

    // populateDefaultTemplates();
    if(dateTemplateList.isEmpty()){
        populateDefaultTemplates();
    }

}




void MainWindow::HomePage()
{    ui->stackedWidget->setCurrentIndex(0);}
void MainWindow::CalendarPage()
{    ui->stackedWidget->setCurrentIndex(1);}
void MainWindow::Templates()
{    ui->stackedWidget->setCurrentIndex(2);}
void MainWindow::SoundFiles()
{    ui->stackedWidget->setCurrentIndex(3);}





void MainWindow::clock(){
    date_time = QDateTime::currentDateTime();
    QString dateTime_text = date_time.toString();
    ui->CurrentDate_Label->setText(dateTime_text);
}


void MainWindow::checkTime(){
    if(ui->scheduledSounds->count() < 1){
        ui->nextSound->setText("Playing next: None");
        return;
    }

    nextSound();

    if(nextIndex >= ui->scheduledSounds->count()){
        ui->nextSound->setText("Playing next: None");
        return;
    }

    QListWidgetItem* item = ui->scheduledSounds->item(nextIndex);
    ui->nextSound->setText("Playing next: "+item->text());
    QString time = item->text().left(4);
    QString currTime = date_time.toString("hhmm");
    if(time == currTime && currTime != lastPlayedTime){
        QString soundFile = item->text().mid(7);
        if(playSound(soundFile,item->data(Qt::UserRole+2).toString(),item->data(Qt::UserRole+3).toBool())){
            lastPlayedTime = time;
        }
    }
}

void MainWindow::nextSound(){
    int i;
    QDate currDate = QDate::currentDate();
    bool isSameDay;
    if(currDate == dateTemplateList.first().date){
        isSameDay = true;
    }else{
        isSameDay = false;
    }

    for(i = 0;i<ui->scheduledSounds->count();i++){
        QListWidgetItem* item = ui->scheduledSounds->item(i);
        sound soundItem = getItemData(item);
        int timeToPlay = soundItem.time.toInt();
        int currTime = date_time.toString("hhmm").toInt();
        bool playNextDay = soundItem.playTmr;
        if(playNextDay && isSameDay){
            break;
        }else if(currTime <= timeToPlay){
            if(currTime == lastPlayedTime.toInt()){
                i++;
                break;
            }
            break;
        }
    }
    nextIndex = i;
}





void MainWindow::playImmediateSound(){
    QString soundFile = ui->soundComboBox->currentText();
    QString volume = ui->volumeInputHome->toPlainText();
    playSound(soundFile,volume,false);
}


bool MainWindow::playSound(QString soundFile, QString volumeStr, bool playNextDay){
    QAudioOutput *audioOutput = new QAudioOutput;
    currentSoundFile = soundFile;
    QDate currDate = QDate::currentDate();

    if (soundFile.isEmpty()){ return false; }

    if(playNextDay){
        if(currDate == dateTemplateList.first().date){
            return false;
        }
    }

    if(!checkVolumeFormat(volumeStr)){ return false; }
    float volume;
    if(volumeStr.length()==0){
        volume = 1.0;
    }else{
        volume = volumeStr.toFloat()/100;
    }

    audioOutput->setVolume(volume);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/Sounds/Sounds/"+soundFile+".mp3"));

    player->play();

    ui->playingLabel->setText("Currently Playing: "+soundFile);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this, &soundFile, &volumeStr](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            if(ui->repeatBtn->isChecked()){
                player->play();
            }else{
                ui->playingLabel->setText("Currently Playing: None");
            }
        }
    });
    return true;
}

void MainWindow::stopSound(){
    player->stop();
    ui->playingLabel->setText("Currently Playing: None");
}





sound MainWindow::getSoundData(QListWidget *listWidget){
    sound newSound;
    QString volume;
    if(listWidget == ui->templateSoundSchedule){
        newSound.soundName = ui->soundComboBoxTemplate->currentText();
        newSound.time = ui->timeInputTemplate->toPlainText();
        volume = ui->volumeInput->toPlainText();
        newSound.playTmr = ui->NextDayCheck->isChecked();
    }else{
        newSound.soundName = ui->soundComboBox->currentText();
        newSound.time = ui->timeInput->toPlainText();
        volume = ui->volumeInputHome->toPlainText();
        newSound.playTmr = ui->NextDayCheckHome->isChecked();
    }
    if(!checkVolumeFormat(volume) || volume.length()==0){
        newSound.volume = 100.0;
    }else{
        newSound.volume = volume.toFloat();
    }
    return newSound;
}

void MainWindow::addSound(QListWidget *listWidget, sound soundToAdd){
    if(!checkTimeFormat(soundToAdd.time)){  return;  }
    QString currentText = soundToAdd.time + " - " + soundToAdd.soundName;
    QListWidgetItem *item = new QListWidgetItem(currentText);

    item->setData(Qt::UserRole,QVariant(soundToAdd.soundName));
    item->setData(Qt::UserRole+1,QVariant(soundToAdd.time));
    item->setData(Qt::UserRole+2,QVariant(soundToAdd.volume));
    item->setData(Qt::UserRole+3,QVariant(soundToAdd.playTmr));
    sound soundItem = getItemData(item);
    // QString toolTipText = QString("Volume: %1\nPlay Play Tmr: %2")
    //                           .arg(soundItem.volume)
    //                           .arg(soundItem.playTmr ? "Yes" : "No");
    // item->setToolTip(toolTipText);
    listWidget->addItem(item);
    sortListWidget(listWidget);
}



void MainWindow::sortListWidget(QListWidget* listWidget){

    if (!listWidget) {
        qDebug() << "listWidget is null!";
        return;
    }

    QList<sound> todaySounds;
    QList<sound> tomorrowSounds;

    // Extract sound data from each item in the list
    int widgetLength = listWidget->count();
    for (int i = 0; i < widgetLength; ++i) {
        QListWidgetItem* tempItem = listWidget->item(i);
        if (!tempItem) {
            qDebug() << "Invalid item in listWidget at index" << i;
            continue;
        }

        sound soundItem = getItemData(tempItem);
        if (soundItem.playTmr) {
            tomorrowSounds.append(soundItem);
        } else {
            todaySounds.append(soundItem);
        }
    }

    // Sort both lists by time
    std::sort(todaySounds.begin(), todaySounds.end(), [](const sound& a, const sound& b) {
        return a.time < b.time;
    });
    std::sort(tomorrowSounds.begin(), tomorrowSounds.end(), [](const sound& a, const sound& b) {
        return a.time < b.time;
    });

    // Clear the listWidget safely
    listWidget->clear();

    // Add sorted items back into the listWidget
    auto addSoundToWidget = [listWidget](const sound& soundItem) {
        QString currentText = soundItem.time + " - " + soundItem.soundName;
        QListWidgetItem* newItem = new QListWidgetItem(currentText, listWidget);
        newItem->setData(Qt::UserRole, QVariant(soundItem.soundName));
        newItem->setData(Qt::UserRole + 1, QVariant(soundItem.time));
        newItem->setData(Qt::UserRole + 2, QVariant(soundItem.volume));
        newItem->setData(Qt::UserRole + 3, QVariant(soundItem.playTmr));
    };

    for (const sound& s : todaySounds) {
        addSoundToWidget(s);
    }
    for (const sound& s : tomorrowSounds) {
        addSoundToWidget(s);
    }

}


sound MainWindow::getItemData(QListWidgetItem *item){
    sound soundItem;
    soundItem.soundName = item->data(Qt::UserRole).toString();
    soundItem.time = item->data(Qt::UserRole+1).toString();
    soundItem.volume = item->data(Qt::UserRole+2).toFloat();
    soundItem.playTmr = item->data(Qt::UserRole+3).toBool();
    return soundItem;
}

void MainWindow::removeSound(QListWidget *listWidget)
{
    QListWidgetItem *item = listWidget->currentItem();  // Get the selected item
    delete listWidget->takeItem(listWidget->row(item));  // Remove the item
}


bool MainWindow::checkTimeFormat(QString timeToAdd){
    QString hours = timeToAdd.left(2);
    QString minutes = timeToAdd.mid(2);
    if(hours.length()!=2 || minutes.length()!=2){
        return false;
    }
    bool okHour; bool okMin;
    int hoursInt = hours.toInt(&okHour,10);
    int minsInt = minutes.toInt(&okMin,10);
    if(hoursInt > 23 || minsInt > 59 || !okMin || !okHour || hoursInt < 0 || minsInt < 0){
        return false;
    }
    return true;
}

bool MainWindow::checkVolumeFormat(QString volumeInput){
    if(volumeInput.length()==0){
        return true;
    }
    bool okVol;
    int vol = volumeInput.toInt(&okVol,10);
    if(vol > 100 || vol < 0 || !okVol){
        return false;
    }
    return true;
}




void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings templateSettings("CWOC", "Templates");

    QVariantList templateDataList;

    for (const Template &t : allTemplates) {
        QVariantMap templateData;
        templateData["templateName"] = t.templateName;

        // Convert daysPlayed array to QVariantList
        QVariantList daysPlayedList;
        for (int i = 0; i < 7; ++i) {
            daysPlayedList.append(t.daysPlayed[i]);
        }
        templateData["daysPlayed"] = daysPlayedList;

        // Convert playlist to QVariantList
        QVariantList playlistDataList;
        for (const sound &s : t.playlist) {
            QVariantMap soundData;
            soundData["soundName"] = s.soundName;
            soundData["time"] = s.time;
            soundData["volume"] = s.volume;
            soundData["playTmr"] = s.playTmr;
            playlistDataList.append(soundData);
        }
        templateData["playlist"] = playlistDataList;

        // Add this template's data to the list
        templateDataList.append(templateData);
    }

    // Save the entire list of templates
    templateSettings.setValue("Templates", templateDataList);

    QSettings calendarList("CWOC", "Calendar");

    QVariantList dateTemplateDataList;
    for (const auto &entry : dateTemplateList) {
        QVariantMap dateEntry;
        dateEntry["date"] = entry.date.toString(Qt::ISODate);  // Convert QDate to a string format
        dateEntry["templateName"] = entry.templateName;
        dateTemplateDataList.append(dateEntry);
    }

    // Save the date template list
    calendarList.setValue("DateTemplates", dateTemplateDataList);

}


void MainWindow::restoreState() {
    QSettings templateSettings("CWOC", "Templates");
    QSettings calendarList("CWOC", "Calendar");

    // ---- Restore allTemplates ----
    QVariantList templateDataList = templateSettings.value("Templates").toList();
    allTemplates.clear();
    for (const QVariant &templateDataVariant : templateDataList) {
        QVariantMap templateData = templateDataVariant.toMap();

        Template t;
        t.templateName = templateData["templateName"].toString();

        // Load daysPlayed
        QVariantList daysPlayedList = templateData["daysPlayed"].toList();
        for (int i = 0; i < 7 && i < daysPlayedList.size(); ++i) {
            t.daysPlayed[i] = daysPlayedList[i].toBool();
        }

        // Load playlist
        QVariantList playlistDataList = templateData["playlist"].toList();
        for (const QVariant &soundDataVariant : playlistDataList) {
            QVariantMap soundData = soundDataVariant.toMap();

            sound s;
            s.soundName = soundData["soundName"].toString();
            s.time = soundData["time"].toString();
            s.volume = soundData["volume"].toFloat();
            s.playTmr = soundData["playTmr"].toBool();
            t.playlist.append(s);
        }

        allTemplates.append(t);
    }

    // Update dropdowns with restored templates
    for (const Template &t : allTemplates) {
        ui->templateDropdown->addItem(t.templateName);
        ui->templateDropdownCalendar->addItem(t.templateName);
    }

    // ---- Restore dateTemplateList ----
    QVariantList dateTemplateDataList = calendarList.value("DateTemplates").toList();
    dateTemplateList.clear();

    for (const QVariant &dateEntryVariant : dateTemplateDataList) {
        QVariantMap dateEntry = dateEntryVariant.toMap();

        DateTemplate entry;
        entry.date = QDate::fromString(dateEntry["date"].toString(), Qt::ISODate);  // Convert string back to QDate
        entry.templateName = dateEntry["templateName"].toString();

        dateTemplateList.append(entry);
    }

    updateCalendar();  // Refresh UI with restored data
}




sound MainWindow::retriveSoundData(QListWidget *listWidget, int index){
    sound currSound;
    QListWidgetItem* item = listWidget->item(index);
    currSound.soundName = item->data(Qt::UserRole).toString();
    currSound.time = item->data(Qt::UserRole+1).toString();
    currSound.volume = item->data(Qt::UserRole+2).toFloat();
    currSound.playTmr = item->data(Qt::UserRole+3).toBool();
    return currSound;
}




void MainWindow::setNewTemplate(){
    Template newTemplate;
    for(int i=0;i<ui->templateSoundSchedule->count();i++){
        newTemplate.playlist.append(retriveSoundData(ui->templateSoundSchedule,i));
    }
    for(int i=0;i<7;i++){
        newTemplate.daysPlayed[i] = dayCheckBoxes[i]->isChecked();
    }

    QString templateNameStr = ui->templateNameInput->toPlainText();
    if(templateNameStr.length()==0){return;}
    newTemplate.templateName=templateNameStr;
    if(deconflictTemplates(newTemplate)){
        allTemplates.append(newTemplate);
        ui->templateDropdown->addItem(newTemplate.templateName);
        ui->templateDropdownCalendar->addItem(newTemplate.templateName);
        ui->templateSoundSchedule->clear();
        for(int i=0;i<7;i++){
            dayCheckBoxes[i]->setCheckState(Qt::Unchecked);
        }
        ui->templateNameInput->clear();
    }
}

void MainWindow::viewTemplate(QListWidget *listWidget,Template displayTemplate){
    if(listWidget == ui->scheduledSounds){
        if(ui->currTemplate->text().mid(18) == displayTemplate.templateName){
            return;
        }
        ui->currTemplate->setText("Today's Template: " + displayTemplate.templateName);
    }

    if(listWidget==ui->templateSoundSchedule){
        QString templateName = ui->templateDropdown->currentText();
        for(int i=0;i<allTemplates.size();i++){
            if(allTemplates[i].templateName == templateName){
                displayTemplate = allTemplates[i];
                break;
            }
        }
        for(int i=0;i<7;i++){
            if(displayTemplate.daysPlayed[i]){
                dayCheckBoxes[i]->setCheckState(Qt::Checked);
            }else{
                dayCheckBoxes[i]->setCheckState(Qt::Unchecked);
            }
        }
    }

    listWidget->clear();
    for(int i=0;i<displayTemplate.playlist.size();i++){
        addSound(listWidget,displayTemplate.playlist.at(i));
    }
}

void MainWindow::deleteTemplate(){
    QString templateName = ui->templateDropdown->currentText();
    for(int i=0;i<allTemplates.length();i++){
        if(allTemplates[i].templateName==templateName){
            allTemplates.removeAt(i);
        }
    }
    ui->templateDropdown->removeItem(ui->templateDropdown->currentIndex());
    for(int i=0;i<ui->templateDropdownCalendar->count();i++){
        if(ui->templateDropdownCalendar->itemText(i) == templateName){
            ui->templateDropdownCalendar->removeItem(i);
        }
    }

}

void MainWindow::updateTemplate(){
    QString templateName = ui->templateDropdown->currentText();
    for (int i = 0; i < allTemplates.size(); i++) {
        if (allTemplates[i].templateName == templateName) {
            Template test;
            test.templateName = allTemplates[i].templateName;
            // Update the days played
            for(int k=0;k<7;k++){
                test.daysPlayed[k]=dayCheckBoxes[k]->isChecked();
            }
            if(!deconflictTemplates(test)){ return; }
            for(int k=0;k<7;k++){
                allTemplates[i].daysPlayed[k]=dayCheckBoxes[k]->isChecked();
            }

            // Clear the existing playlist
            allTemplates[i].playlist.clear();

            // Add updated sounds from the scheduledSounds widget
            for (int j = 0; j < ui->templateSoundSchedule->count(); j++) {
                QListWidgetItem *tempItem = ui->templateSoundSchedule->item(j);

                // Extract sound data from the item and append to the playlist
                sound tempSound = getItemData(tempItem);
                allTemplates[i].playlist.append(tempSound);
            }


            if(ui->templateNameInput->toPlainText().length() != 0){
                allTemplates[i].templateName.clear();
                allTemplates[i].templateName = ui->templateNameInput->toPlainText();
            }
            // deconflictTemplates(allTemplates[i]);
            ui->templateNameInput->clear();
            int index = ui->templateDropdown->currentIndex();
            ui->templateDropdown->setItemText(index,allTemplates[i].templateName);

            // Break after updating the first matching template
            break;
        }
    }
}

bool MainWindow::deconflictTemplates(Template newTemplate){
    QList<QString> dayOfWeek = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
    for(Template checkTemplate : allTemplates){
        for(int i=0;i<7;i++){
            if(checkTemplate.daysPlayed[i] && newTemplate.daysPlayed[i] && checkTemplate.templateName != newTemplate.templateName){
                ui->deconflictLabel->setText("The template "+checkTemplate.templateName+" already is scheduled for "+dayOfWeek[i]+", please update the templates so there are no conflicts");
                return false;
            }
        }
    }
    ui->deconflictLabel->clear();
    return true;
}

void MainWindow::newTemplate(){
    ui->templateSoundSchedule->clear();
    ui->timeInputTemplate->clear();
    ui->templateDropdown->setCurrentIndex(-1);
    ui->templateNameInput->clear();
    ui->volumeInput->clear();
    for(int i=0;i<7;i++){
        dayCheckBoxes[i]->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::checkDay(){
    if(nextIndex < ui->scheduledSounds->count()){
        return;
    }
    QString templateName = dateTemplateList.first().templateName;

    for(const Template &templateItem : allTemplates){
        if(templateItem.templateName == templateName){
            viewTemplate(ui->scheduledSounds,templateItem);
            return;
        }
    }
}


void MainWindow::updateCalendar() {
    QTextCharFormat format;
    QCalendarWidget *calendar = ui->calendarWidget;

    for (const DateTemplate &item : dateTemplateList) {
        QDate date = item.date;

        // Ensure the date is within the calendar's range
        if (calendar->minimumDate() <= date && date <= calendar->maximumDate()) {
            format = calendar->dateTextFormat(date); // Get current format
            format.setToolTip(item.templateName);    // Add a tooltip with the template name
            format.setFontItalic(true);              // Example styling
            format.setForeground(Qt::blue);          // Optional: Change text color
            calendar->setDateTextFormat(date, format);
            // qDebug() << "Formatted date:" << date.toString() << "with template:" << item.templateName;
        } else {
            // qDebug() << "Date out of range:" << date.toString();
        }
    }

    calendar->update(); // Force refresh of the calendar
}




void MainWindow::populateDefaultTemplates() {
    // Define default templates for each day of the week
    QMap<int, QString> defaultTemplates;
    for (const Template &templateItem : allTemplates) {
        for (int i = 0; i < 7; i++) {
            if (templateItem.daysPlayed[i]) {
                defaultTemplates[Qt::Monday + i] = templateItem.templateName;
            }
        }
    }
    // Get the range for the next 30 days
    QDate currentDate = QDate::currentDate();
    QDate endDate = currentDate.addDays(30);

    // Populate the list with specific dates and templates
    for (QDate date = currentDate; date <= endDate; date = date.addDays(1)) {
        int dayOfWeek = date.dayOfWeek();
        if (defaultTemplates.contains(dayOfWeek)) {
            dateTemplateList.append({date, defaultTemplates[dayOfWeek]});
        }
    }
    updateCalendar();
}


void MainWindow::resetCalendar(){
    QCalendarWidget *calendar = ui->calendarWidget;
    calendar->setToolTip("");
    calendar->setDateTextFormat(QDate(), QTextCharFormat());
    calendar->setStyleSheet("");
    dateTemplateList.clear();
    populateDefaultTemplates();
}


void MainWindow::updateDateTemplateList(){
    QString templateName = ui->templateDropdownCalendar->currentText();
    QDate selectedDate = ui->calendarWidget->selectedDate();

    for(int i=0;i<dateTemplateList.count();i++){
        if(selectedDate == dateTemplateList[i].date){
            dateTemplateList[i].templateName = templateName;
            break;
        }else if(dateTemplateList[i].date > selectedDate){
            if(i==0){
                dateTemplateList.prepend({selectedDate,templateName});
            }else{
                dateTemplateList.insert(i,{selectedDate,templateName});
            }
            break;
        }
    }
    updateCalendar();
}


void MainWindow::refreshCalendar(){
    QDate currentDate = QDate::currentDate();
    if(dateTemplateList.first().date != currentDate){
        dateTemplateList.removeFirst();
        QDate nextDate = currentDate.addDays(30);
        for(Template currTemplate : allTemplates){
            if(currTemplate.daysPlayed[nextDate.dayOfWeek()]){
                dateTemplateList.append({nextDate, currTemplate.templateName});
            }
        }
    }
}


Template MainWindow::returnTemplate(QString templateName){
    for(const Template &templateItem : allTemplates){
        if(templateItem.templateName == templateName){
            return templateItem;
        }
    }
    return allTemplates[0];
}




MainWindow::~MainWindow()
{
    delete ui;
}








