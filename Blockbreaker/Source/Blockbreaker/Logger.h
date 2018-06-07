#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "CoreMinimal.h"

#include <fstream>  //  Can't forward declare classes in specific namespaces
#include <mutex>    //      unfortunately, so they have to go here
#include <vector>   //


class Logger {
public:
  enum LogLevel {
    _INFO_, _ERROR_, _WARNING_, _CRITICAL_, _DEBUG_
  } Level;

private:
  Logger();
  virtual ~Logger();
  std::ofstream InfoLog, ErrorLog, WarningLog, CriticalLog, DebugLog;
  std::mutex LogMutex;
protected:
  std::vector<std::string> Info, Error, Warning, Critical, Debug;
public:
  static Logger* GetLogger(LogLevel Level = _INFO_) {
    static Logger* Instance = new Logger();
    Instance->Level = Level;
    return Instance;
  }

  void Write(LogLevel Level, const char *fname, int lineno, const char *fxname, const char* Message);
  int OutputLogs();
  Logger(Logger const&) = delete;
  void operator=(Logger const&) = delete;
};

#define _INF Logger::GetLogger()->_INFO_
#define _ERR Logger::GetLogger()->_ERROR_
#define _WARN Logger::GetLogger()->_WARNING_
#define _CRIT Logger::GetLogger()->_CRITICAL_
#define _DBUG Logger::GetLogger()->_DEBUG_

#define ERROR_F "ErrorLog.txt"
#define INFO_F "InfoLog.txt"
#define WARNING_F "WarningLog.txt"
#define CRITICAL_F "CriticalLog.txt"
#define DEBUG_F "DebugLog.txt"

#define OPENINFO_F InfoLog.open(INFO_F, std::ofstream::out | std::ofstream::app);
#define OPENERROR_F ErrorLog.open(ERROR_F, std::ofstream::out | std::ofstream::app);
#define OPENWARNING_F WarningLog.open(WARNING_F, std::ofstream::out | std::ofstream::app);
#define OPENCRITICAL_F CriticalLog.open(CRITICAL_F, std::ofstream::out | std::ofstream::app);
#define OPENDEBUG_F DebugLog.open(DEBUG_F, std::ofstream::out | std::ofstream::app);

#define CLOSEINFO_F InfoLog.close();
#define CLOSEERROR_F InfoLog.close();
#define CLOSEWARNING_F InfoLog.close();
#define CLOSECRITICAL_F InfoLog.close();
#define CLOSEDEBUG_F InfoLog.close();

#define LOG(_Level_, _Message_) Logger::GetLogger()->Write(_Level_, __FILE__, __LINE__, __FUNCTION__, _Message_)

#endif  //  LOGGER_H

