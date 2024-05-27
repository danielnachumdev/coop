//
// Created by t-danachum on 21/05/2024.
//

#include <stddef.h>
#include <stdio.h>
#include "logger.h"
#include "../memory/allocator.h"

static Logger *global_logger = NULL;


void default_log(const LogMessage *m) {
    Logger *l = get_logger();
    for (unsigned int i = 0; i < l->num_consumers; ++i)
        if ((l->consumers[i].target_severity & m->msg_severity) != 0)
            l->consumers[i].consume(l->name, m);
}

void default_consume_all(const char *logger_name, const LogMessage *msg) {
    const char *severity = "DEBUG";
    if (msg->msg_severity == INFO_LOG_SEVERITY)
        severity = "INFO";
    else if (msg->msg_severity == WARN_LOG_SEVERITY)
        severity = "WARN";
    else if (msg->msg_severity == ERROR_LOG_SEVERITY)
        severity = "ERROR";
    fprintf(stdout, "[%s-%s]: %s at line %d: %s", logger_name, severity, msg->file_name, msg->line_number, msg->msg);
}

void default_consume_error(const char *logger_name, const LogMessage *msg) {
    fprintf(stderr, "[%s-ERROR]: %s at line %d: %s", logger_name, msg->file_name, msg->line_number, msg->msg);
}

Logger *init_logger(void) {
    Logger *res = acquire(sizeof(Logger));
    if (res == NULL) return NULL;
    res->name = "GlobalLogger";
    res->log = default_log;
    res->consumers = acquire(sizeof(LogConsumer) * 2);
    if (res->consumers == NULL) {
        release(res);
        return NULL;
    }
    res->consumers[0] = (LogConsumer) {
            ERROR_LOG_SEVERITY,
            default_consume_error
    };
    res->consumers[1] = (LogConsumer) {
            DEBUG_LOG_SEVERITY | WARN_LOG_SEVERITY | INFO_LOG_SEVERITY,
            default_consume_all
    };
    res->num_consumers = 2;
    return res;
}

Logger *get_logger(void) {
    if (global_logger != NULL) return global_logger;
    global_logger = init_logger();
    return global_logger;
}
