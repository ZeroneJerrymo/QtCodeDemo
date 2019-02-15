#include "hallon.h"
#include "hallonplugin.h"

#include <QtPlugin>

HALLOnPlugin::HALLOnPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void HALLOnPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool HALLOnPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *HALLOnPlugin::createWidget(QWidget *parent)
{
    return new HALLOn(parent);
}

QString HALLOnPlugin::name() const
{
    return QLatin1String("HALLOn");
}

QString HALLOnPlugin::group() const
{
    return QLatin1String("");
}

QIcon HALLOnPlugin::icon() const
{
    return QIcon();
}

QString HALLOnPlugin::toolTip() const
{
    return QLatin1String("");
}

QString HALLOnPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool HALLOnPlugin::isContainer() const
{
    return false;
}

QString HALLOnPlugin::domXml() const
{
    return QLatin1String("<widget class=\"HALLOn\" name=\"hALLOn\">\n</widget>\n");
}

QString HALLOnPlugin::includeFile() const
{
    return QLatin1String("hallon.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(hallonplugin, HALLOnPlugin)
#endif // QT_VERSION < 0x050000
