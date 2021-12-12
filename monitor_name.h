#include <QString>
#include <vector>

struct MonitorInfo {
  QString name;
  int width;
  int height;
  int x;
  int y;
  double devicePixelRatio;
};

void GetMonitors(std::vector<MonitorInfo> *monitors);
