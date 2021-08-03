#include <api/logging/Log.hpp>
#include <api/logging/Logger.hpp>
#include <cstdarg>

namespace sf
{

void
log (ELogSeverity sevr, const char *str, va_list vlist)
{
  Logger::getInstance ().logMsg (sevr, str, vlist);
}

void
logM (const char *str, ...)
{
  va_list vlist;
  va_start (vlist, str);
  log (ELogSeverity::Msg, str, vlist);
  va_end (vlist);
}

void
logW (const char *str, ...)
{
  va_list vlist;
  va_start (vlist, str);
  log (ELogSeverity::Warn, str, vlist);
  va_end (vlist);
}

void
logE (const char *str, ...)
{
  va_list vlist;
  va_start (vlist, str);
  log (ELogSeverity::Error, str, vlist);
  va_end (vlist);
}

}
