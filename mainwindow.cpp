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

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
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

BaseEnhancedDialog* MainWindow::getCurrentDialog(int tabIndex)
{
    switch (tabIndex) {
    case 0:
        return m_startingRankDialog;
    case 1:
        return m_pairingsDialog;
    case 2:
        return m_standingsDialog;
    default:
        return nullptr;
    }
}
void MainWindow::onShow() {
    auto dialog = getCurrentDialog(ui->tabWidget->currentIndex());

    if (dialog->isVisible()){
        dialog->hide();
    }else {
        dialog->show(ui->checkBox->isChecked());
    }
    ui->showPushButton->setText(dialog->isVisible() ? "Hide" : "Show");
}

void MainWindow::onTabChanged(int tabIndex)
{
    auto dialog = getCurrentDialog(tabIndex);
    if (dialog == nullptr){
        return;
    }

    ui->showPushButton->setText(dialog->isVisible() ? "Hide" : "Show");
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
