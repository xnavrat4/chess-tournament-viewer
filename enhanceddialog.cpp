#include "enhanceddialog.h"
#include "tabsettings.h"

#include <QHBoxLayout>

EnhancedDialog::EnhancedDialog(TabSettings *settings) :
    m_settings(settings)
{
    this->setWindowFlag(Qt::Window);
    this->setMinimumHeight(200);
    this->setMinimumWidth(400);

    m_layout = new QHBoxLayout();

    this->setLayout(m_layout);
    init();
}

EnhancedDialog::~EnhancedDialog()
{
    m_settings->setGeometry(saveGeometry());
    m_settings->saveToSettings();
}

void EnhancedDialog::init()
{
    QLayoutItem* item;
    while ((item = m_layout->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        if (widget) {
            // Remove the widget from the layout
            m_layout->removeWidget(widget);

            // Delete the widget
            delete widget;
        } else {
            // Remove any non-widget layout items (e.g., spacers)
            delete item;
        }
    }
    m_view = QList<QWebEngineView*>();
    for (int i = 0; i<m_settings->tabCount(); i++){
        auto engineView = new QWebEngineView(this);
        m_view.append(engineView);
        m_layout->addWidget(engineView);
        engineView->load(m_settings->getFullAddress());
        engineView->page()->runJavaScript(QString(QString("window.scrollTo(%1, %2);").arg(m_settings->scrollPosition().x()).arg(m_settings->scrollPosition().y())));
        connect(engineView->page(), &QWebEnginePage::geometryChangeRequested, this, [] (QRect r) {qDebug()<< r;});
        connect(engineView->page(), &QWebEnginePage::scrollPositionChanged, this, [this] (QPointF r) {m_settings->setScrollPosition(r); m_settings->saveToSettings();});
    }
}

void EnhancedDialog::show(bool fullscreen)
{
    init();
    if (fullscreen){
        QDialog::showFullScreen();
    }else {
        QDialog::show();
    }
}

void EnhancedDialog::updateSettings(TabSettings* settings)
{
    m_settings = settings;
}
