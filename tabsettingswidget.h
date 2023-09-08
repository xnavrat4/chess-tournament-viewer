#ifndef TABSETTINGSWIDGET_H
#define TABSETTINGSWIDGET_H

#include "tabsettings.h"
#include <QWidget>

namespace Ui {
class TabSettingsWidget;
}

class TabSettingsWidget : public QWidget
{
    Q_OBJECT



public:
    explicit TabSettingsWidget(TabSettings *settings, QWidget *parent = nullptr);
    ~TabSettingsWidget();


    TabSettings *tabSettings() const;

private slots:
    void on_buttonBox_accepted();
    void on_roundSpinBox_valueChanged(int arg1);
    void on_tabCountSpinBox_valueChanged(int arg1);
    void on_roundSpinBox_2_valueChanged(int arg1);

signals:
    void signalSettings(TabSettings* settings);

private:
    Ui::TabSettingsWidget *ui;
    TabSettings* m_tabSettings = nullptr;
};

#endif // TABSETTINGSWIDGET_H
