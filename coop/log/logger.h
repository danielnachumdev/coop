//
// Created by t-danachum on 21/05/2024.
//

#ifndef LOCAL_PLAYGROUND_LOGGER_H
#define LOCAL_PLAYGROUND_LOGGER_H

enum LogSeverity {
    DEBUG_LOG_SEVERITY = 1,
    INFO_LOG_SEVERITY = 1 << 1,
    WARN_LOG_SEVERITY = 1 << 2,
    ERROR_LOG_SEVERITY = 1 << 3
};

typedef struct LogMessage {
    const char *logger_name;
    const char *file_name;
    const unsigned int line_number;
    const char *msg;
    enum LogSeverity msg_severity;
} LogMessage;

typedef struct LogConsumer {
    enum LogSeverity target_severity;

    void (*consume)(const char *logger_name, const LogMessage *msg);
} LogConsumer;

typedef struct Logger {
    const char *name;

    void (*log)(const LogMessage *msg);

    LogConsumer *consumers;
    unsigned int num_consumers;

} Logger;

Logger *get_logger(void);

#define _LOG(msg, severity) get_logger()->log(&((LogMessage){get_logger()->name,__FILE__,__LINE__,msg,severity}))
#define _DEBUG(msg) _LOG(msg,DEBUG_LOG_SEVERITY)
#define _INFO(msg) _LOG(msg,INFO_LOG_SEVERITY)
#define _WARN(msg) _LOG(msg,WARN_LOG_SEVERITY)
#define _ERROR(msg) _LOG(msg,ERROR_LOG_SEVERITY)


#endif //LOCAL_PLAYGROUND_LOGGER_H
