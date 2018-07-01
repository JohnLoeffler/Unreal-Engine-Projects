#include "Logger.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include <iostream>
#include <sstream>
#include "Runnable.h"

Logger::Logger() : PlatformFile(FPlatformFileManager::Get().GetPlatformFile()){
  FString TimeStamp = FDateTime::Now().ToString();
  InfoF.Append(FString(LOGDIR));
  InfoF.Append("Blockbreaker/Source/Blockbreaker/LogFiles/Info/InfoLog_"); 
  InfoF.Append(TimeStamp);
  InfoF.Append(".log");
  ErrorF.Append(FString(LOGDIR));
  ErrorF.Append("Blockbreaker/Source/Blockbreaker/LogFiles/Error/ErrorLog_");
  ErrorF.Append(TimeStamp);
  ErrorF.Append(".log");
  WarningF.Append(FString(LOGDIR));
  WarningF.Append("Blockbreaker/Source/Blockbreaker/LogFiles/Warning/WarningLog_");
  WarningF.Append(TimeStamp);
  WarningF.Append(".log");
  DebugF.Append(FString(LOGDIR));
  DebugF.Append("Blockbreaker/Source/Blockbreaker/LogFiles/Debug/DebugLog_");
  DebugF.Append(TimeStamp);
  DebugF.Append(".log");
  CritF.Append(FString(LOGDIR));
  CritF.Append("Blockbreaker/Source/Blockbreaker/LogFiles/Critical/CriticalLog_");
  CritF.Append(TimeStamp);
  CritF.Append(".log");
}

Logger::~Logger() {
  ClearQueues();
}

bool Logger::Write(Log log){
  FString Time = FDateTime::Now().GetTimeOfDay().ToString();
  IFileHandle* Handle;
  FString str;
  switch (log.Level) {
    case _ERR:
      str = "ERROR|: " + log.Msg + "\n";
      Handle = PlatformFile.OpenWrite((TEXT("%s"), *ErrorF), true);
      if (!Handle->Write((const uint8*)TCHAR_TO_ANSI(*str), str.Len())) {
        str = "Error writing string to Error file:\n\t" + str + "\n";
        UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
      }
      delete Handle;
      break;
    case _WARN:
      str = "WARNING|: " + log.Msg + "\n";
      Handle = PlatformFile.OpenWrite((TEXT("%s"), *WarningF), true);
      if (!Handle->Write((const uint8*)TCHAR_TO_ANSI(*str), str.Len())) {
        str = "Error writing string to Warning file:\n\t" + str + "\n";
        UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
      }
      delete Handle;
      break;
    case _DBUG:
      str = "DEBUG|: " + log.Msg + "\n";
      Handle = PlatformFile.OpenWrite((TEXT("%s"), *DebugF), true);
      if (!Handle->Write((const uint8*)TCHAR_TO_ANSI(*str), str.Len())) {
        str = "Error writing string to Debugging file:\n\t" + str + "\n";
        LOG(_ERR, str);
      }
      delete Handle;
      break;
    case _CRIT:
      str = "CRITICAL|: " + log.Msg + "\n";
      Handle = PlatformFile.OpenWrite((TEXT("%s"), *CritF), true);
      if (!Handle->Write((const uint8*)TCHAR_TO_ANSI(*str), str.Len())) {
        str = "Error writing string to Critical file:\n\t" + str + "\n";
        UE_LOG(LogTemp, Error, TEXT("%s"), *str);
      }
      delete Handle;
      break;
    default:
    case _INF:
      str = "INFO|: " + log.Msg + "\n";
      Handle = PlatformFile.OpenWrite((TEXT("%s"), *InfoF), true);
      if (!Handle->Write((const uint8*)TCHAR_TO_ANSI(*str), str.Len())) {
        str = "Error writing string to Info file:\n\t" + str + "\n";
        LOG(_ERR, str);
      }
      delete Handle;
      break;
  }
  return false;
}

/* Need to find better way to lock logs during insertion operations */
void Logger::AddLog(LogLevel Level, FString fname, int32 lineno, FString fxname, FString Message) {
  FString MSG = fname + "("; 
  MSG.AppendInt(lineno);
  MSG.Append("): IN->" + fxname + "| " + Message);
  switch (Level) {
    case _CRIT:
      UE_LOG(LogTemp, Warning, TEXT("|CRITICAL| %s"), *MSG);
      CriticalLogs.Enqueue(Log(Level, MSG, FDateTime::Now().GetTimeOfDay().ToString()));
      break;
    default:
      OtherLogs.Enqueue(Log(Level, MSG, FDateTime::Now().GetTimeOfDay().ToString()));
      break;
  }
}

bool Logger::ClearQueues(){
  Log Lg;
  while(!CriticalLogs.IsEmpty()){
    CriticalLogs.Dequeue(Lg);
    Write(Lg);
  }
  while(!OtherLogs.IsEmpty()){
    OtherLogs.Dequeue(Lg);
    Write(Lg);
  }
  if (CriticalLogs.IsEmpty() && OtherLogs.IsEmpty()) {
    return true;
  } else {
    return false;
  }
}

