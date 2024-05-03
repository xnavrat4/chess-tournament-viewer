#ifndef ENHANCEDDIALOG_H
#define ENHANCEDDIALOG_H

#include "qwebengineview.h"
#include "settings/tabsettings.h"
#include <QObject>
#include <QDialog>
#include <qboxlayout.h>
#include <QNetworkCookie>

class BaseEnhancedDialog : public QDialog
{

protected:
    QList<QWebEngineView*> m_view;
    QHBoxLayout* m_layout;
    TabSettings* m_settings;
    bool m_visible = false;

    void clearLayout();

public:
    BaseEnhancedDialog(TabSettings *settings);
    ~BaseEnhancedDialog();

    void init();

    bool isVisible();

    virtual void show(bool fullscreen);
    void hide();

public slots:
    void updateSettings(TabSettings* settings);
};

#endif // ENHANCEDDIALOG_H
