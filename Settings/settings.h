#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVariant>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings &instance();

    ~Settings();

    QVariant getSetting(QString categoty, QString name, QVariant defValue = QVariant());
    void setSetting(QString categoty, QString name, QVariant value);
    void initValue(QString category, QString name, QVariant value);

private:
    // Singleton
    Settings();
    Settings(const Settings&);
    Settings& operator=(const Settings&);

    QSettings *m_settings;
};

#ifdef QML_ENABLED
#include <QQmlEngine>
#include <QQmlContext>

class SettingsQmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit SettingsQmlHelper(QQmlEngine *parent);

public slots:
    QVariant getSetting(QString category, QString name, QVariant defValue = QVariant());
    void setSetting(QString categoty, QString name, QVariant value);
    void initValue(QString category, QString name, QVariant value);
};

#endif

#endif // SETTINGS_H
