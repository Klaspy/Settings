#include "settings.h"

Settings &Settings::instance()
{
    static Settings stgs;
    return stgs;
}

Settings::~Settings()
{
}

QVariant Settings::getSetting(QString name, QString category, QVariant defValue)
{
    m_settings->sync();
    if (category != "") category += "/";
    if (m_settings->allKeys().contains(category + name))
    {
        return m_settings->value(category + name, defValue);
    }
    return QVariant();
}

void Settings::setSetting(QString category, QString name, QVariant value)
{
    if (category != "") category += "/";
    return m_settings->setValue(category + name, value);
}

void Settings::initSettings(QMultiMap<QString, QString> fields)
{
    foreach (QString category, fields.keys())
    {
        category.remove("/");
        if (category != "") category += "/";
        foreach (QString field, fields.values(category))
        {
            if (!m_settings->contains(category  + field))
            {
                m_settings->setValue(category + field, "");
            }
        }
    }
}

Settings::Settings()
{
    m_settings = new QSettings(QCoreApplication::applicationDirPath() + "/settings.ini", QSettings::Format::IniFormat, this);
}
