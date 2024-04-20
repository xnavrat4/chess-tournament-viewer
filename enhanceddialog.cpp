#include "enhanceddialog.h"
#include "tabsettings.h"

#include <QHBoxLayout>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QTimer>

EnhancedDialog::EnhancedDialog(TabSettings *settings) :
    m_settings(settings)
{
    this->setWindowFlag(Qt::Window);
    this->setMinimumHeight(200);
    this->setMinimumWidth(400);

    m_layout = new QHBoxLayout(this);
    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, &QTimer::timeout, this, &EnhancedDialog::refreshViews);
    this->setLayout(m_layout);
    init();
}

EnhancedDialog::~EnhancedDialog()
{
    m_settings->setGeometry(saveGeometry());
    m_settings->setScrollPosition(QPointF(m_view.first()->page()->scrollPosition()));
    m_settings->saveToSettings();
}

void EnhancedDialog::init()
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
    m_view = QList<QWebEngineView*>();
    for (int i = 0; i<m_settings->tabCount(); i++){
        auto engineView = new QWebEngineView(this);
        engineView->page()->profile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

        m_view.append(engineView);
        m_layout->addWidget(engineView);
        engineView->load(m_settings->getFullAddress());
        //connect(engineView->page(), &QWebEnginePage::scrollPositionChanged, this, [this] (QPointF r) {m_settings->setScrollPosition(r); m_settings->saveToSettings();});
    }
}

void EnhancedDialog::refreshViews(){
    for(auto view: m_view){
        view->reload();
    }
    //m_settings->setScrollPosition(QPointF(m_view.first()->page()->scrollPosition()));
    m_settings->saveToSettings();
}

void EnhancedDialog::saveScrollPosition(){
    for(auto view: m_view){
        view->reload();
    }
    m_settings->setScrollPosition(QPointF(m_view.first()->page()->scrollPosition()));
    m_settings->saveToSettings();
}

void EnhancedDialog::scrollToPosition()
{
    //engineView->page()->runJavaScript(QString(QString("window.scrollTo(%1, %2);").arg(m_settings->scrollPosition().x()).arg(m_settings->scrollPosition().y())));
}

void EnhancedDialog::show(bool fullscreen)
{
    init();
    if (fullscreen){
        QDialog::showFullScreen();
    }else {
        QDialog::show();
    }
    int refreshRate = m_settings->refreshRate();
    if (refreshRate == 0){
        refreshRate = 5000;
    }
    m_refreshTimer->start(refreshRate * 1000);
}

void EnhancedDialog::updateSettings(TabSettings* settings)
{
    m_settings = settings;
}
