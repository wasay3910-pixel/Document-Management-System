#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

#include <string>
#include <vector>
#include <optional>
#include "document.h"

// Manages create/store/retrieve/delete of documents using file handling.
// Documents are persisted as one line per document in a data file.
class DocumentManager {
public:
    explicit DocumentManager(std::string storage_path = "documents.dat");

    // Create a new document and persist it. Returns the assigned id.
    int create_document(std::string title, std::string content);

    // Retrieve a document by id. std::nullopt if not found.
    std::optional<Document> get_document(int id) const;

    // Update an existing document's title/content. Returns false if not found.
    bool update_document(int id,
                         std::string title,
                         std::string content);

    // Delete a document by id. Returns false if not found.
    bool delete_document(int id);

    // List all stored documents (metadata only, content omitted).
    std::vector<Document> list_documents() const;

    // Total number of stored documents.
    size_t count() const;

private:
    std::string storage_path_;
    int next_id_ = 1;

    // Rewrite the whole storage file from the in-memory document list.
    void rewrite(const std::vector<Document>& docs);

    // Load all documents from the storage file.
    std::vector<Document> load_all() const;

    // Assign and bump the next id.
    int allocate_id();
};

#endif // DOCUMENT_MANAGER_H
