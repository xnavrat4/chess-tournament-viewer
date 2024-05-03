#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include <QWebEngineView>
#include <dialogs/refreshenhanceddialog.h>
#include <settings/tabsettings.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();
    auto url = ui->tournamentURLlineEdit->text();

    createTab(url, m_pairingSettingsWidget, m_pairingsDialog, TabSettings::Pairings, ui->verticalLayout);
    createTab(url, m_standingsSettingsWidget, m_standingsDialog, TabSettings::Standings, ui->verticalLayout_3);
    createTab(url, m_startingRankSettingsWidget, m_startingRankDialog, TabSettings::StartingRank, ui->verticalLayout_5);

    connect(ui->showPushButton, &QAbstractButton::clicked, this, &MainWindow::onShow);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete m_standingsSettingsWidget;
    delete m_standingsDialog;
    delete m_pairingSettingsWidget;
    delete m_pairingsDialog;
    delete m_startingRankDialog;
    delete m_startingRankSettingsWidget;
    delete ui;
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("General");

    settings.setValue("address", ui->tournamentURLlineEdit->text());
    settings.setValue("fullscreen", ui->checkBox->isChecked());
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}

void MainWindow::loadSettings()
{
    QSettings settings;
    settings.beginGroup("General");

    ui->tournamentURLlineEdit->setText(settings.value("address").toString());
    ui->checkBox->setCheckState(settings.value("fullscreen").toBool() ? Qt::Checked : Qt::Unchecked);
    restoreGeometry(settings.value("geometry").toByteArray());
    settings.endGroup();
}

void MainWindow::onShow()
{
    m_startingRankDialog->hide();
    m_standingsDialog->hide();
    m_pairingsDialog->hide();

    auto isFullScreen = ui->checkBox->isChecked();

    switch (ui->tabWidget->currentIndex()) {
    case 0:
        m_startingRankDialog->show(isFullScreen);
        break;
    case 1:
        m_pairingsDialog->show(isFullScreen);
        break;
    case 2:
        m_standingsDialog->show(isFullScreen);
        break;
    default:
        break;
    }
}


void MainWindow::on_pushButton_clicked()
{
    saveSettings();
}

void MainWindow::createTab(QString url, TabSettingsWidget*& settingsWidget, BaseEnhancedDialog*& dialog, TabSettings::Mode settingsType, QVBoxLayout*& layout)
{
    auto settings = new TabSettings(settingsType, url);
    settings->loadFromSettings();
    settingsWidget = new TabSettingsWidget(settings);
    layout->addWidget(settingsWidget);

    dialog = settingsType == TabSettings::Pairings ? new RefreshEnhancedDialog(settings) : new BaseEnhancedDialog(settings);
    connect(settingsWidget, &TabSettingsWidget::signalSettings, dialog, &BaseEnhancedDialog::updateSettings);
}
