#include "checkers/FileChecker.h"

#include <string>

std::optional<FileInfo> FileChecker::check(const FileInfo& prev, const FileInfo& curr) const {
    FileInfo event = curr;

    if (prev.exists && !curr.exists) {
        event.description = "File deleted";
        return event;
    }

    if ((!prev.exists) && curr.exists) {
        event.description = "File exists, size " + std::to_string(curr.size) + " bytes";
        return event;
    }

    if (prev.seen && prev.exists && curr.exists && prev.size != curr.size) {
        event.description = "File changed, new size " + std::to_string(curr.size) + " bytes";
        return event;
    }

    return std::nullopt;
}
