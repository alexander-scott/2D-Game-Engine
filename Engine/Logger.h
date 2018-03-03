#pragma once

#include "spdlog/spdlog.h"

enum LogSeverity
{
	eTrace,
	eDebug,
	eInfo,
	eWarning,
	eError,
	eCritical 
};

class Logger
{
public:
	const std::string filePath = "LogFile.txt"; // Should this be in consts.h?

	Logger()
	{
		_logger = spdlog::basic_logger_mt("GEPAA", filePath);
	}

	void LogMessage(std::string msg, LogSeverity logSeverity)
	{
		switch (logSeverity)
		{
			case LogSeverity::eTrace:
			{
				_logger->trace(msg);
				break;
			}

			case LogSeverity::eInfo:
			{
				_logger->info(msg);
				break;
			}

			case LogSeverity::eWarning:
			{
				_logger->warn(msg);
				break;
			}

			case LogSeverity::eError:
			{
				_logger->error(msg);
				break;
			}

			case LogSeverity::eCritical:
			{
				_logger->critical(msg);
				break;
			}
		}
	}

	void LogMessage(std::string message, std::string systemName, LogSeverity logSeverity)
	{
		std::string msg = "[" + systemName + "]: " + message;
		LogMessage(msg, logSeverity);
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

private:
	std::shared_ptr<spdlog::logger> _logger;
};