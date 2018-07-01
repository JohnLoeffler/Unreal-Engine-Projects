#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Containers/Queue.h"

class IPlatformFile;

class Logger {
public:
  enum LogLevel {
    _INFO_, _ERROR_, _WARNING_, _CRITICAL_, _DEBUG_
  } Level;

  /***/
private :
  struct Log {
    LogLevel Level;
    FString Msg, TimeStamp;
    Log() {}
    Log(LogLevel Lvl, FString Msg, FString Stmp) {
      Level = Lvl; this->Msg = Msg; TimeStamp = Stmp;
    }
  };

  //  Dedicated methods
  bool Write(Log log);
  
  Logger();
  virtual ~Logger();
  IPlatformFile& PlatformFile;
  
protected:
  
  /** A Queue for incoming longs, Critical gets its own queue and priority */
  TQueue<Log> OtherLogs, CriticalLogs;

  /** File Paths to the Log different Log files*/
  FString InfoF, ErrorF, WarningF, DebugF, CritF;
  
public:
  static Logger* GetLogger(LogLevel Level = _INFO_) {
    static Logger* Instance = new Logger();
    Instance->Level = Level;
    return Instance;
  }

  void AddLog(LogLevel Level, FString fname, int32 lineno, FString fxname, FString Message);
  bool ClearQueues();
  Logger(Logger const&) = delete;
  void operator=(Logger const&) = delete;
};


#define LOGDIR "A:/GithubRepos/Unreal-Engine-Projects/"

#define _INF Logger::LogLevel::_INFO_
#define _ERR Logger::LogLevel::_ERROR_
#define _WARN Logger::LogLevel::_WARNING_
#define _CRIT Logger::LogLevel::_CRITICAL_
#define _DBUG Logger::LogLevel::_DEBUG_

#define LOG(_Level_, _Message_) Logger::GetLogger()->AddLog(_Level_, __FILE__, __LINE__, __FUNCTION__, _Message_)

#endif  //  LOGGER_H

