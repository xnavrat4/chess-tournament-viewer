#include "tabsettingswidget.h"
#include "ui_tabsettingswidget.h"

TabSettingsWidget::TabSettingsWidget(TabSettings* settings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabSettingsWidget),
    m_tabSettings(settings)
{
    ui->setupUi(this);

    ui->roundSpinBox->setValue(m_tabSettings->roundNumber());
    ui->roundSpinBox_2->setValue(m_tabSettings->refreshRate());
    ui->tabCountSpinBox->setValue(m_tabSettings->tabCount());

}

TabSettingsWidget::~TabSettingsWidget()
{
    m_tabSettings->saveToSettings();
    delete ui;
}

TabSettings *TabSettingsWidget::tabSettings() const
{
    return m_tabSettings;
}

void TabSettingsWidget::on_buttonBox_accepted()
{
    m_tabSettings->saveToSettings();
    emit signalSettings(m_tabSettings);
}


void TabSettingsWidget::on_roundSpinBox_valueChanged(int arg1)
{
    m_tabSettings->setRoundNumber(arg1);
}


void TabSettingsWidget::on_tabCountSpinBox_valueChanged(int arg1)
{
    m_tabSettings->setTabCount(arg1);
}


void TabSettingsWidget::on_roundSpinBox_2_valueChanged(int arg1)
{
    m_tabSettings->setRefreshRate(arg1);
}

