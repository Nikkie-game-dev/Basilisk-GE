#include "Log.h"

#include <spdlog/sinks/rotating_file_sink.h>

#define MAX_LOGS 3
#define MAX_LOG_SIZE (1024 * 1024)

namespace basilisk
{
    std::shared_ptr<spdlog::logger>& Log::Print()
    {
        static auto log = Log();
        
        return log.Logger;
    }
    Log::~Log()
    {
        Logger->info("Game closed \n\n\n\n\n");
    }

    Log::Log()
    {
        const auto console = std::make_shared<spdlog::sinks::wincolor_stderr_sink_st>();
        const auto errorDump = std::make_shared<spdlog::sinks::rotating_file_sink_st>("logs/dump.log", MAX_LOG_SIZE, MAX_LOGS);
        std::vector<spdlog::sink_ptr> sinks{console, errorDump};

        Logger = std::make_shared<spdlog::logger>("DEF_LOG", sinks.begin(), sinks.end());
        spdlog::register_logger(Logger);
        
        // Auto flush on error
        Logger->flush_on(spdlog::level::err);
    }
}
