#ifndef ENHANCEDDIALOG_H
#define ENHANCEDDIALOG_H

#include "qwebengineview.h"
#include "tabsettings.h"
#include <QObject>
#include <QDialog>
#include <qboxlayout.h>
#include <QNetworkCookie>

class EnhancedDialog : public QDialog
{
private:
    QList<QWebEngineView*> m_view;
    QHBoxLayout* m_layout;
    TabSettings* m_settings;
    QTimer* m_refreshTimer;

public:
    EnhancedDialog(TabSettings *settings);
    ~EnhancedDialog();

    void init();

    void show(bool fullscreen);

public slots:
    void updateSettings(TabSettings* settings);

private slots:
    void saveScrollPosition();
    void refreshViews();
    void scrollToPosition();
};

#endif // ENHANCEDDIALOG_H
