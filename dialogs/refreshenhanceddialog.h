#ifndef REFRESHENHANCEDDIALOG_H
#define REFRESHENHANCEDDIALOG_H

#include "dialogs/enhanceddialog.h"
#include <QTimer>


class RefreshEnhancedDialog : public BaseEnhancedDialog
{
    Q_OBJECT

    QTimer* m_refreshTimer;

public:
    RefreshEnhancedDialog(TabSettings *settings);

    void show(bool fullscreen) override;

protected slots:
    void refreshViews();
};

#endif // REFRESHENHANCEDDIALOG_H
