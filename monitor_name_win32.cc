#include <windows.h>

#include <QString>
#include <vector>

struct MonitorData {
  const wchar_t *id;
  MONITORINFOEX info;
  bool found;
};

static BOOL CALLBACK GetMonitorCallback(HMONITOR monitor, HDC, LPRECT,
                                        LPARAM param) {
  MonitorData *data = (MonitorData *)param;

  if (GetMonitorInfoW(monitor, &data->info)) {
    if (wcscmp(data->info.szDevice, data->id) == 0) {
      data->found = true;
      return false;
    }
  }

  return true;
}

#define GENERIC_MONITOR_NAME QStringLiteral("Generic PnP Monitor")

QString GetMonitorName(const QString &id) {
  MonitorData data = {};
  data.id = (const wchar_t *)id.utf16();
  data.info.cbSize = sizeof(data.info);

  EnumDisplayMonitors(nullptr, nullptr, GetMonitorCallback, (LPARAM)&data);
  if (!data.found) {
    return GENERIC_MONITOR_NAME;
  }

  UINT32 numPath, numMode;
  if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &numPath, &numMode) !=
      ERROR_SUCCESS) {
    return GENERIC_MONITOR_NAME;
  }

  std::vector<DISPLAYCONFIG_PATH_INFO> paths(numPath);
  std::vector<DISPLAYCONFIG_MODE_INFO> modes(numMode);

  if (QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &numPath, paths.data(),
                         &numMode, modes.data(), nullptr) != ERROR_SUCCESS) {
    return GENERIC_MONITOR_NAME;
  }

  DISPLAYCONFIG_TARGET_DEVICE_NAME target;
  bool found = false;

  paths.resize(numPath);
  for (size_t i = 0; i < numPath; ++i) {
    const DISPLAYCONFIG_PATH_INFO &path = paths[i];

    DISPLAYCONFIG_SOURCE_DEVICE_NAME s;
    s.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
    s.header.size = sizeof(s);
    s.header.adapterId = path.sourceInfo.adapterId;
    s.header.id = path.sourceInfo.id;

    if (DisplayConfigGetDeviceInfo(&s.header) == ERROR_SUCCESS &&
        wcscmp(data.info.szDevice, s.viewGdiDeviceName) == 0) {
      target.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
      target.header.size = sizeof(target);
      target.header.adapterId = path.sourceInfo.adapterId;
      target.header.id = path.targetInfo.id;
      found = DisplayConfigGetDeviceInfo(&target.header) == ERROR_SUCCESS;
      break;
    }
  }

  if (!found) {
    return GENERIC_MONITOR_NAME;
  }

  return QString::fromWCharArray(target.monitorFriendlyDeviceName);
}