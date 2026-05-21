#pragma once

namespace dx3d
{
	class Logger final
	{
	public: 

		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info
		};
		explicit Logger(LogLevel logLevel = LogLevel::Error);

		//Const - doesnt alter the state of the class
		void log(LogLevel level, const char* message) const;

	private:
		LogLevel m_logLevel = LogLevel::Error;
	};


#define DX3DLogError(message)\
	getLogger().log((Logger::LogLevel::Error), message);\

#define DX3DLogErrorAndThrow(message)\
	{\
	DX3DLogError(message);\
	throw std::runtime_error(message);\
	}
}
