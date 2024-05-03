#include "refreshenhanceddialog.h"

RefreshEnhancedDialog::RefreshEnhancedDialog(TabSettings *settings)
    : BaseEnhancedDialog(settings)
{
    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, &QTimer::timeout, this, &RefreshEnhancedDialog::refreshViews);
    this->setLayout(m_layout);
}

void RefreshEnhancedDialog::show(bool fullscreen)
{
    BaseEnhancedDialog::show(fullscreen);
    int refreshRate = m_settings->refreshRate();
    if (refreshRate == 0){
        refreshRate = 5000;
    }
    m_refreshTimer->start(refreshRate * 1000);
}

void RefreshEnhancedDialog::refreshViews(){
    for(auto view: m_view){
        view->reload();
    }
    //m_settings->setScrollPosition(QPointF(m_view.first()->page()->scrollPosition()));
    m_settings->saveToSettings();
}

