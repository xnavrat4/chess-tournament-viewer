#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <QSettings>
#include <QWebEngineView>
#include <tabsettings.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();

    m_pairingSettingsWidget = new TabSettingsWidget(TabSettings::Pairings, ui->tournamentURLlineEdit->text());
    ui->verticalLayout->addWidget(m_pairingSettingsWidget);


    m_standingsSettingsWidget = new TabSettingsWidget(TabSettings::Standings, ui->tournamentURLlineEdit->text());
    ui->verticalLayout_3->addWidget(m_standingsSettingsWidget);


    m_startingRankSettingsWidget = new TabSettingsWidget(TabSettings::StartingRank, ui->tournamentURLlineEdit->text());
    ui->verticalLayout_5->addWidget(m_startingRankSettingsWidget);



    m_startingRankDialog = new EnhancedDialog(m_startingRankSettingsWidget->tabSettings());
    connect(m_startingRankSettingsWidget, &TabSettingsWidget::signalSettings, m_startingRankDialog, &EnhancedDialog::updateSettings);

    m_pairingsDialog = new EnhancedDialog(m_pairingSettingsWidget->tabSettings());
    connect(m_pairingSettingsWidget, &TabSettingsWidget::signalSettings, m_pairingsDialog, &EnhancedDialog::updateSettings);

    m_standingsDialog = new EnhancedDialog(m_standingsSettingsWidget->tabSettings());
    connect(m_standingsSettingsWidget, &TabSettingsWidget::signalSettings, m_standingsDialog, &EnhancedDialog::updateSettings);



    connect(ui->showPushButton, &QAbstractButton::clicked, this, &MainWindow::onShow);

}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::saveSettings()
{
    QSettings settings;
    settings.beginGroup("General");

    settings.setValue("address", ui->tournamentURLlineEdit->text());
    settings.setValue("fullscreen", ui->checkBox->isChecked());
    settings.endGroup();
}

void MainWindow::loadSettings()
{
    QSettings settings;
    settings.beginGroup("General");

    ui->tournamentURLlineEdit->setText(settings.value("address").toString());
    ui->checkBox->setCheckState(settings.value("fullscreen").toBool() ? Qt::Checked : Qt::Unchecked);
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

