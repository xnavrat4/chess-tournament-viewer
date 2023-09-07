#ifndef ENHANCEDDIALOG_H
#define ENHANCEDDIALOG_H

#include "qwebengineview.h"
#include "tabsettings.h"
#include <QObject>
#include <QDialog>
#include <qboxlayout.h>

class EnhancedDialog : public QDialog
{

private:
    QList<QWebEngineView*> m_view;
    QHBoxLayout* m_layout;
    TabSettings* m_settings;

public:
    EnhancedDialog(TabSettings *settings);

    void init();

    void show(bool fullscreen);

public slots:
    void updateSettings(TabSettings* settings);

};

#endif // ENHANCEDDIALOG_H
