#include "notifier/EventNotifier.h"

EventNotifier::EventNotifier(const std::shared_ptr<ILogger>& logger)
    : logger_(logger) {}

void EventNotifier::notify(const FileInfo& event) {
    logger_->log("Event: " + event.path);
}

void EventNotifier::onFileEvent(const FileInfo& event) {
    notify(event);
}
