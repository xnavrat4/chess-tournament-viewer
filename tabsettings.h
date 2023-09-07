#ifndef TABSETTINGS_H
#define TABSETTINGS_H

#include <QString>



class TabSettings
{
public:
    enum Mode {
        StartingRank,
        Standings,
        Pairings
    };

private:
    int m_tabCount = 0;
    int m_roundNumber = 0;
    int m_refreshRate = 0;
    QString m_address;
    Mode m_type;

public:
    TabSettings(Mode mode, QString address);
    void saveToSettings();
    void loadFromSettings();

    int tabCount() const;
    void setTabCount(int newTabCount);

    int roundNumber() const;
    void setRoundNumber(int newRoundNumber);

    QString address() const;
    void setAddress(const QString &newAddress);

    QString getFullAddress();
    int refreshRate() const;
    void setRefreshRate(int newRefreshRate);
};

#endif // TABSETTINGS_H
