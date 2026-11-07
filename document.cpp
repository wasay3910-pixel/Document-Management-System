#include "document.h"

#include <sstream>

Document::Document(int id, std::string title, std::string content)
    : id(id),
      title(std::move(title)),
      content(std::move(content)) {
    std::time(&created_at);
    updated_at = created_at;
}

std::string Document::serialize() const {
    std::ostringstream oss;
    oss << id << "|"
        << title << "|"
        << created_at << "|"
        << updated_at << "|"
        << content;
    return oss.str();
}

Document Document::deserialize(const std::string& line) {
    Document doc;
    std::istringstream iss(line);
    std::string field;

    // id
    std::getline(iss, field, '|');
    doc.id = std::stoi(field);

    // title
    std::getline(iss, doc.title, '|');

    // created_at
    std::getline(iss, field, '|');
    doc.created_at = static_cast<std::time_t>(std::stoll(field));

    // updated_at
    std::getline(iss, field, '|');
    doc.updated_at = static_cast<std::time_t>(std::stoll(field));

    // content (remainder of the line, may itself contain '|')
    std::getline(iss, doc.content);
    return doc;
}
