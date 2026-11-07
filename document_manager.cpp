#include "document_manager.h"

#include <algorithm>
#include <fstream>
#include <iostream>

DocumentManager::DocumentManager(std::string storage_path)
    : storage_path_(std::move(storage_path)) {
    // Seed next_id_ from existing storage so ids stay unique across runs.
    std::vector<Document> docs = load_all();
    for (const auto& d : docs) {
        if (d.id >= next_id_) {
            next_id_ = d.id + 1;
        }
    }
}

int DocumentManager::create_document(std::string title, std::string content) {
    int id = allocate_id();
    Document doc(id, std::move(title), std::move(content));
    std::vector<Document> docs = load_all();
    docs.push_back(doc);
    rewrite(docs);
    return id;
}

std::optional<Document> DocumentManager::get_document(int id) const {
    std::vector<Document> docs = load_all();
    for (const auto& d : docs) {
        if (d.id == id) {
            return d;
        }
    }
    return std::nullopt;
}

bool DocumentManager::update_document(int id,
                                      std::string title,
                                      std::string content) {
    std::vector<Document> docs = load_all();
    bool found = false;
    for (auto& d : docs) {
        if (d.id == id) {
            d.title = std::move(title);
            d.content = std::move(content);
            std::time(&d.updated_at);
            found = true;
            break;
        }
    }
    if (!found) {
        return false;
    }
    rewrite(docs);
    return true;
}

bool DocumentManager::delete_document(int id) {
    std::vector<Document> docs = load_all();
    auto it = std::remove_if(docs.begin(), docs.end(),
                             [id](const Document& d) { return d.id == id; });
    if (it == docs.end()) {
        return false;
    }
    docs.erase(it, docs.end());
    rewrite(docs);
    return true;
}

std::vector<Document> DocumentManager::list_documents() const {
    return load_all();
}

size_t DocumentManager::count() const {
    return load_all().size();
}

void DocumentManager::rewrite(const std::vector<Document>& docs) {
    std::ofstream ofs(storage_path_, std::ios::trunc);
    if (!ofs) {
        std::cerr << "Error: could not open storage file for writing: "
                  << storage_path_ << "\n";
        return;
    }
    for (const auto& d : docs) {
        ofs << d.serialize() << "\n";
    }
}

std::vector<Document> DocumentManager::load_all() const {
    std::vector<Document> docs;
    std::ifstream ifs(storage_path_);
    if (!ifs) {
        // No storage file yet — treat as empty.
        return docs;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        docs.push_back(Document::deserialize(line));
    }
    return docs;
}

int DocumentManager::allocate_id() {
    return next_id_++;
}
