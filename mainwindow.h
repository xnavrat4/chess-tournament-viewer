#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialogs/enhanceddialog.h"
#include <QHBoxLayout>
#include <QMainWindow>
#include <settings/tabsettingswidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void saveSettings();
    void loadSettings();

private slots:
    BaseEnhancedDialog *getCurrentDialog(int tabIndex);
    void onShow();
    void on_pushButton_clicked();
    void onTabChanged(int tabIndex);

private:
    Ui::MainWindow *ui;

    TabSettingsWidget* m_pairingSettingsWidget = nullptr;
    TabSettingsWidget* m_standingsSettingsWidget = nullptr;
    TabSettingsWidget* m_startingRankSettingsWidget = nullptr;
    
    BaseEnhancedDialog* m_pairingsDialog = nullptr;
    BaseEnhancedDialog* m_startingRankDialog = nullptr;
    BaseEnhancedDialog* m_standingsDialog = nullptr;

    void createTab(QString url, TabSettingsWidget*& settingsWidget, BaseEnhancedDialog*& dialog, TabSettings::Mode settingsType, QVBoxLayout*& layout);
};
#endif // MAINWINDOW_H
