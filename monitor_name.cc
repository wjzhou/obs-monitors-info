
#include "monitor_name.h"

#include <QGuiApplication>
#include <QScreen>
#include <vector>

#ifdef _WIN32
QString GetMonitorName(const QString &id);
#endif

void GetMonitors(std::vector<MonitorInfo> *monitors) {
  QList<QScreen *> screens = QGuiApplication::screens();
  for (int i = 0; i < screens.size(); i++) {
    QScreen *screen = screens[i];
    QRect screenGeometry = screen->geometry();
    qreal ratio = screen->devicePixelRatio();
    QString name = "";
#ifdef _WIN32
    name = GetMonitorName(screen->name());
#elif defined(__APPLE__)
    name = screen->name();
#else
    name = screen->model().simplified();

    if (name.length() > 1 && name.endsWith("-")) name.chop(1);
#endif
    name = name.simplified();

    monitors->push_back({
        name,                     // name
        screenGeometry.width(),   // width
        screenGeometry.height(),  // height
        screenGeometry.x(),       // x
        screenGeometry.y(),       // y
        ratio,                    // devicePixelRatio
    });
  }
}