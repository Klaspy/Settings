#include "settings.h"

Settings &Settings::instance()
{
    static Settings stgs;
    return stgs;
}

Settings::~Settings()
{
}

QVariant Settings::getSetting(QString category, QString name, QVariant defValue)
{
    m_settings->sync();
    if (category != "") category += "/";

    return m_settings->value(category + name, defValue);
}

void Settings::setSetting(QString category, QString name, QVariant value)
{
    if (category != "") category += "/";
    return m_settings->setValue(category + name, value);
}

void Settings::initValue(QString category, QString name, QVariant value)
{
    if (category != "") category += "/";
    if (!m_settings->contains(category + name))
    {
        m_settings->setValue(category + name, value);
    }
}

Settings::Settings()
{
    m_settings = new QSettings(QCoreApplication::applicationDirPath() + "/settings.ini", QSettings::Format::IniFormat, this);
}
