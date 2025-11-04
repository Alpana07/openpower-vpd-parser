#include "logger.hpp"

#include <sstream>

namespace vpd
{
std::shared_ptr<Logger> Logger::m_loggerInstance;

void Logger::logMessage(std::string_view i_message,
                        const PlaceHolder& i_placeHolder,
                        const types::PelInfoTuple* i_pelTuple,
                        const std::source_location& i_location)
{
    std::ostringstream l_log;
    l_log << "FileName: " << i_location.file_name() << ","
          << " Line: " << i_location.line() << " " << i_message;

    if (i_placeHolder == PlaceHolder::COLLECTION)
    {
#ifdef ENABLE_FILE_LOGGING
        if(m_fileStream.is_open())	
            m_fileStream << l_log.str() << std::endl;
#else
        std::cout << l_log.str() << std::endl;
#endif
	    // Log it to a specific place.
        //m_logFileHandler->writeLogToFile(i_placeHolder);
    }
    else if (i_placeHolder == PlaceHolder::PEL)
    {
        if (i_pelTuple)
        {
            // LOG PEL
            // This should call create PEL API from the event logger.
            return;
        }
        std::cout << "Pel info tuple required to log PEL for message <" +
                         l_log.str() + ">"
                  << std::endl;
    }
    else
    {
        // Default case, let it go to journal.
        std::cout << l_log.str() << std::endl;
    }
}

namespace logging
{
void logMessage(std::string_view message, [[maybe_unused]]const std::source_location& location)
{
	/*
    std::ostringstream log;
    log << "FileName: " << location.file_name() << ","
        << " Line: " << location.line() << " " << message;

    std::cout << log.str() << std::endl;
    */
	Logger::getLoggerInstance()->logMessage(message);
}
} // namespace logging
} // namespace vpd
