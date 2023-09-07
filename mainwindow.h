#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "enhanceddialog.h"
#include <QHBoxLayout>
#include <QMainWindow>
#include <tabsettingswidget.h>

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
    void onShow();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    TabSettingsWidget* m_pairingSettingsWidget = nullptr;
    TabSettingsWidget* m_standingsSettingsWidget = nullptr;
    TabSettingsWidget* m_startingRankSettingsWidget = nullptr;

    EnhancedDialog* m_pairingsDialog = nullptr;
    EnhancedDialog* m_startingRankDialog = nullptr;
    EnhancedDialog* m_standingsDialog = nullptr;

};
#endif // MAINWINDOW_H
