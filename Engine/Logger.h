#pragma once

#include "spdlog/spdlog.h"

#include "Consts.h"

class Logger
{
public:
	const std::string filePath = "logs/LogFile.txt"; // Should this be in consts.h?

	void LogMessage(std::string message)
	{
		spdlog::basic_logger_mt("UNDEFINED_SYSTEM", filePath)->info(message);
	}

	void LogMessage(std::string message, std::string systemName)
	{
		spdlog::basic_logger_mt(systemName, filePath)->error(message);
	}

	void LogMessage(std::string message, std::string systemName, LogSeverity logSeverity)
	{
		switch (logSeverity)
		{
			case LogSeverity::eTrace:
			{
				spdlog::basic_logger_mt(systemName, filePath)->trace(message);
				break;
			}

			case LogSeverity::eInfo:
			{
				spdlog::basic_logger_mt(systemName, filePath)->info(message);
				break;
			}

			case LogSeverity::eWarning:
			{
				spdlog::basic_logger_mt(systemName, filePath)->warn(message);
				break;
			}

			case LogSeverity::eError:
			{
				spdlog::basic_logger_mt(systemName, filePath)->error(message);
				break;
			}

			case LogSeverity::eCritical:
			{
				spdlog::basic_logger_mt(systemName, filePath)->critical(message);
				break;
			}
		}
	}

	~Logger()
	{
		spdlog::drop_all();
	}

	static Logger& Instance()
	{
		static Logger Instance;
		return Instance;
	}
};