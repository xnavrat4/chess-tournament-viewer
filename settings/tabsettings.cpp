#include "tabsettings.h"

#include <QSettings>

int TabSettings::refreshRate() const
{
    return m_refreshRate;
}

void TabSettings::setRefreshRate(int newRefreshRate)
{
    m_refreshRate = newRefreshRate;
}

QByteArray TabSettings::geometry() const
{
    return m_geometry;
}

void TabSettings::setGeometry(const QByteArray &newGeometry)
{
    m_geometry = newGeometry;
}

QPointF TabSettings::scrollPosition() const
{
    return m_scrollPosition;
}

void TabSettings::setScrollPosition(QPointF newScrollPosition)
{
    m_scrollPosition = newScrollPosition;
}

TabSettings::Mode TabSettings::type() const
{
    return m_type;
}

TabSettings::TabSettings(Mode mode, QString address):
    m_address(address),
    m_type(mode)
{

}

void TabSettings::saveToSettings()
{
    QSettings settings;
    settings.beginGroup("TabSettings" + QString::number(m_type));
    settings.setValue("tabCount", m_tabCount);
    settings.setValue("roundNumber", m_roundNumber);
    settings.setValue("refreshRate", m_refreshRate);
    settings.setValue("geometry", m_geometry);
    settings.setValue("scroll", m_scrollPosition);
    //settings.setValue("address", m_address);
    settings.endGroup();
}

void TabSettings::loadFromSettings()
{
    QSettings settings;
    settings.beginGroup("TabSettings" + QString::number(m_type));
    m_tabCount = settings.value("tabCount").toInt();
    m_roundNumber = settings.value("roundNumber").toInt();
    m_refreshRate = settings.value("refreshRate").toInt();
    m_geometry = settings.value("geometry").toByteArray();
    m_scrollPosition = settings.value("scroll").toPointF();
    //m_address = settings.value("address").toString();
}


int TabSettings::tabCount() const
{
    return m_tabCount;
}

void TabSettings::setTabCount(int newTabCount)
{
    m_tabCount = newTabCount;
}

int TabSettings::roundNumber() const
{
    return m_roundNumber;
}

void TabSettings::setRoundNumber(int newRoundNumber)
{
    m_roundNumber = newRoundNumber;
}

QString TabSettings::address() const
{
    return m_address;
}

void TabSettings::setAddress(const QString &newAddress)
{
    m_address = newAddress;
}

QString TabSettings::getFullAddress()
{
    auto suffix = QString();
    switch(m_type){
    case StartingRank:
        suffix = "lan=5&art=0";
        break;
    case Standings:
        suffix = QString("lan=5&art=1&rd=%1").arg(m_roundNumber);
        break;
    case Pairings:
        suffix = QString("lan=5&art=2&rd=%1").arg(m_roundNumber);
        break;
    default:break;
    }

    return m_address + "?" + suffix;
}
