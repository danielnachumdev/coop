//
// Created by danie on 17/05/2024.
//
#include <stddef.h>
#include <memory.h>
#include "logger.h"
#include "../memory//allocator.h"
#include "../exceptions/exception.h"

static Logger *global_logger = NULL;

void logger_default_debug(const char *msg) {
    if (global_logger == NULL || msg == NULL)return;
    global_logger->broadcast(&((LogMessage) {.msg=msg, .level=DEBUG}));
}

void logger_default_info(const char *msg) {
    if (global_logger == NULL || msg == NULL)return;
    global_logger->broadcast(&((LogMessage) {.msg=msg, .level=INFO}));
}

void logger_default_warning(const char *msg) {
    if (global_logger == NULL || msg == NULL)return;
    global_logger->broadcast(&((LogMessage) {.msg=msg, .level=WARNING}));
}

void logger_default_error(const char *msg) {
    if (global_logger == NULL || msg == NULL)return;
    global_logger->broadcast(&((LogMessage) {.msg=msg, .level=ERROR}));
}

void logger_default_notify_all(const LogMessage *msg) {
    if (global_logger == NULL || msg == NULL)return;

    for (long unsigned int i = 0; i < global_logger->consumer_size; ++i) {
        const Consumer *cur = global_logger->consumers + i;
        if (cur->level == msg->level)
            cur->on_notify(global_logger, msg);
    }
}

void default_notify_debug(const Logger *logger, const LogMessage *msg) {
    fprintf(stdout, "[%s-DEBUG]: %s", logger->name, msg->msg);
}

void default_notify_info(const Logger *logger, const LogMessage *msg) {
    fprintf(stdout, "[%s-INFO]: %s", logger->name, msg->msg);
}

void default_notify_warning(const Logger *logger, const LogMessage *msg) {
    fprintf(stdout, "[%s-WARNING]: %s", logger->name, msg->msg);
}

void default_notify_error(const Logger *logger, const LogMessage *msg) {
    fprintf(stderr, "[%s-ERROR]: %s", logger->name, msg->msg);
}

Consumer *logger_default_add_consumer(const Consumer *consumer) {
    if (global_logger->consumer_size >= global_logger->consumers_length) {
        long unsigned int new_length = global_logger->consumers_length * 2;
        Consumer *ptr = acquire(sizeof(Consumer) * new_length).nullable;
        if (ptr == NULL) easy_throw("FailedAllocation", "Failed Adding another consumer");
        memcpy(ptr, global_logger->consumers, sizeof(Consumer) * global_logger->consumers_length);
        get_allocator()->free(global_logger->consumers);;
        global_logger->consumers = ptr;
        global_logger->consumers_length = new_length;
    }

    global_logger->consumers[global_logger->consumer_size] = *consumer;
    global_logger->consumer_size += 1;
    return &global_logger->consumers[global_logger->consumer_size - 1];
}

void init_logger() {
    global_logger = acquire(sizeof(Logger)).nullable;
    if (global_logger == NULL) easy_throw("Failed Allocation", "Failed initializing the global_logger");
    global_logger->name = "GlobalLogger";
    global_logger->debug = logger_default_debug;
    global_logger->info = logger_default_info;
    global_logger->warn = logger_default_warning;
    global_logger->error = logger_default_error;
    global_logger->broadcast = logger_default_notify_all;
    global_logger->add_consumer = logger_default_add_consumer;
    global_logger->consumers = acquire(sizeof(Consumer) * 4).nullable;
    if (global_logger->consumers == NULL) easy_throw("FailedAllocation", "Failed initializing the global_logger");
    // Explicitly not using global_logger->add_consumer
    global_logger->consumers[0].level = DEBUG;
    global_logger->consumers[0].on_notify = default_notify_debug;
    global_logger->consumers[1].level = INFO;
    global_logger->consumers[1].on_notify = default_notify_info;
    global_logger->consumers[2].level = WARNING;
    global_logger->consumers[2].on_notify = default_notify_warning;
    global_logger->consumers[3].level = ERROR;
    global_logger->consumers[3].on_notify = default_notify_error;
    global_logger->consumer_size = 4;
    global_logger->consumers_length = 4;
}

Logger *get_logger() {
    if (global_logger != NULL) return global_logger;
    init_logger();
    return global_logger;
}

#include "logger.h"
