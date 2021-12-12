

#include <QGuiApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

#include "monitor_name.h"

void GenerateJson(QJsonObject &root,
                  const std::vector<MonitorInfo> &monitorInfos) {
  QJsonArray monitors;
  for (const MonitorInfo &monitorInfo : monitorInfos) {
    QJsonObject monitor;
    monitor["name"] = monitorInfo.name;
    monitor["width"] = monitorInfo.width;
    monitor["height"] = monitorInfo.height;
    monitor["x"] = monitorInfo.x;
    monitor["y"] = monitorInfo.y;
    monitors.append(monitor);
  }
  root["monitors"] = monitors;
}

int main(int argc, char *argv[]) {
  QGuiApplication a(argc, argv);

  std::vector<MonitorInfo> monitors;
  GetMonitors(&monitors);

  QJsonObject gameObject;
  GenerateJson(gameObject, monitors);

  QTextStream out(stdout);
  out << QJsonDocument(gameObject).toJson();

  return 0;
}