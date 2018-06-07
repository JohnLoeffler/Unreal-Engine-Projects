#include "Logger.h"
#include <iostream>
#include <sstream>

Logger::Logger() {
  OPENINFO_F;
  OPENERROR_F;
  OPENWARNING_F;
  OPENCRITICAL_F;
  OPENDEBUG_F;
}

Logger::~Logger() {
  if (OutputLogs() == 1) {

  }
}

/* Need to find better way to lock logs during insertion operations */
void Logger::Write(LogLevel Level, const char *fname, int lineno, const char *fxname, const char* Message) {
  std::lock_guard<std::mutex> LogGuard(LogMutex);
  std::stringstream SS, msg;

  msg << fname << "(" << lineno << "): IN->" << fxname << "| " << Message;

  switch (Level) {
    case _INFO_:
      SS << "[ INFO ] : " << msg.str();
      Info.push_back(SS.str());
      break;
    case _ERROR_:
      SS << "[ ERROR ] : " << msg.str();
      Error.push_back(SS.str());
      break;
    case _WARNING_:
      SS << "[ WARNING ] : " << msg.str();
      Warning.push_back(SS.str());
      break;
    case _DEBUG_:
      SS << "[ DEBUG ] : " << msg.str();
      Debug.push_back(SS.str());
      break;
    case _CRITICAL_:
      SS << "[ CRITICAL ] : " << msg.str();
      std::cerr << SS.str() << std::endl;
      Critical.push_back(SS.str());
      break;
    default:
      break;
  }
}

int Logger::OutputLogs() {
  std::stringstream SS;
  if (!Info.empty()) {
    LOG(_DBUG, "Info is not empty...\n");
    for (auto itr = Info.begin(); itr != Info.end(); ++itr) {
      SS << *itr << std::endl;
    }
    InfoLog << SS.str();
    SS.clear();
    CLOSEINFO_F;
  }
  if (!Error.empty()) {
    LOG(_DBUG, "Error is not empty...\n");
    for (auto itr = Error.begin(); itr != Error.end(); ++itr) {
      SS << *itr << std::endl;
    }
    ErrorLog << SS.str();
    SS.clear();
    CLOSEERROR_F;
  }
  if (!Warning.empty()) {
    LOG(_DBUG, "Warning is not empty...\n");
    for (auto itr = Warning.begin(); itr != Warning.end(); ++itr) {
      SS << *itr << std::endl;
    }
    WarningLog << SS.str();
    SS.clear();
    CLOSEWARNING_F;
  }
  if (!Critical.empty()) {
    LOG(_DBUG, "Critical is not empty...\n");
    for (auto itr = Critical.begin(); itr != Critical.end(); ++itr) {
      std::cerr << *itr << std::endl;
      SS << *itr << std::endl;
    }
    CriticalLog << SS.str();
    SS.clear();
    CLOSECRITICAL_F;
  }
  if (!Debug.empty()) {
    LOG(_DBUG, "Debug is not empty...\n");
    for (auto itr = Debug.begin(); itr != Debug.end(); ++itr) {
      SS << *itr << std::endl;
      std::cout << *itr << std::endl;
    }
    DebugLog << SS.str();
    SS.clear();
    CLOSEDEBUG_F;
  }
  //std::cin.get();
  return 1;
}
