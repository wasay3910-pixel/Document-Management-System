#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <ctime>

// A single document stored on disk.
// Fields: id, title, content, created_at, updated_at.
class Document {
public:
    int id;
    std::string title;
    std::string content;
    std::time_t created_at;
    std::time_t updated_at;

    Document(int id = 0,
             std::string title = "",
             std::string content = "");

    // Serialize this document to a single text line for storage.
    // Format: id|title|created_at|updated_at|content
    std::string serialize() const;

    // Deserialize a document from a serialized line.
    static Document deserialize(const std::string& line);
};

#endif // DOCUMENT_H
