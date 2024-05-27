//
// Created by danie on 17/05/2024.
//

#ifndef MACROPYTHON_LOGGER_H
#define MACROPYTHON_LOGGER_H

typedef enum LOG_LEVEL {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
} LOG_LEVEL;

typedef struct LogMessage {
    const char *msg;
    const LOG_LEVEL level;
} LogMessage;
struct Logger;
typedef struct Consumer {
    LOG_LEVEL level;

    void (*on_notify)(const struct Logger *logger, const LogMessage *msg);
} Consumer;

typedef struct Logger {
    const char *name;
    Consumer *consumers;
    long unsigned int consumer_size;
    long unsigned int consumers_length;

    void (*debug)(const char *msg);

    void (*info)(const char *msg);

    void (*warn)(const char *msg);

    void (*error)(const char *msg);

    Consumer *(*add_consumer)(const Consumer *consumer);

    void (*broadcast)(const LogMessage *msg);
} Logger;

Logger *get_logger();

#define _DEBUG(msg) get_logger()->debug(msg)
#define _INFO(msg) get_logger()->info(msg)
#define _WARN(msg) get_logger()->warn(msg)
#define _ERROR(msg) get_logger()->error(msg)
#define LOG_DEBUG_VERBOSE(msg) get_logger()->debug(concatenate_strings(5,__FILE__," ",STR(__LINE__)," ",msg).nullable)
#define LOG_INFO_VERBOSE(msg) get_logger()->info(concatenate_strings(5,__FILE__," ",STR(__LINE__)," ",msg).nullable)
#define LOG_WARN_VERBOSE(msg) get_logger()->warn(concatenate_strings(5,__FILE__," ",STR(__LINE__)," ",msg).nullable)
#define LOG_ERROR_VERBOSE(msg) get_logger()->error(concatenate_strings(5,__FILE__," ",STR(__LINE__)," ",msg).nullable)

#endif //MACROPYTHON_LOGGER_H
