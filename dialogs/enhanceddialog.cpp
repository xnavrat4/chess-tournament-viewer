#include "enhanceddialog.h"
#include "settings/tabsettings.h"

#include <QHBoxLayout>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QTimer>

BaseEnhancedDialog::BaseEnhancedDialog(TabSettings *settings) :
    m_settings(settings)
{
    this->setWindowFlag(Qt::Window);
    this->setMinimumHeight(200);
    this->setMinimumWidth(400);

    m_layout = new QHBoxLayout(this);
    init();
}

BaseEnhancedDialog::~BaseEnhancedDialog()
{
    m_settings->setGeometry(saveGeometry());
    m_settings->setScrollPosition(QPointF(m_view.first()->page()->scrollPosition()));
    m_settings->saveToSettings();
}

void BaseEnhancedDialog::clearLayout()
{
    QLayoutItem* item;
    while ((item = m_layout->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        if (widget) {
            m_layout->removeWidget(widget);
            m_view.removeAt(0);
            delete widget;
        } else {
            delete item;
        }
    }
}

void BaseEnhancedDialog::init()
{
    clearLayout();

    for (int i = 0; i<m_settings->tabCount(); i++){
        auto engineView = new QWebEngineView(this);
        engineView->page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

        m_view.append(engineView);
        m_layout->addWidget(engineView);
        engineView->load(m_settings->getFullAddress());
    }
}

bool BaseEnhancedDialog::isVisible()
{
    return m_visible;
}

void BaseEnhancedDialog::show(bool fullscreen)
{
    m_visible = true;
    init();
    fullscreen ? QDialog::showFullScreen() : QDialog::show();
}

void BaseEnhancedDialog::hide()
{
    m_visible = false;
    QDialog::hide();
}

void BaseEnhancedDialog::updateSettings(TabSettings* settings)
{
    m_settings = settings;
    init();
}
