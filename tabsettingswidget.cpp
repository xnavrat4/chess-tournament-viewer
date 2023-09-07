#include "tabsettingswidget.h"
#include "ui_tabsettingswidget.h"

TabSettingsWidget::TabSettingsWidget(TabSettings::Mode mode, QString address, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabSettingsWidget)
{
    ui->setupUi(this);

    m_tabSettings = new TabSettings(mode, address);
    m_tabSettings->loadFromSettings();


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

