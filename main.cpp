#include <iostream>
#include <string>
#include <limits>

#include "document.h"
#include "document_manager.h"

static void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

static void print_menu() {
    std::cout << "\n=== Document Management System ===\n";
    std::cout << "1. Create document\n";
    std::cout << "2. View document by ID\n";
    std::cout << "3. Update document by ID\n";
    std::cout << "4. Delete document by ID\n";
    std::cout << "5. List all documents\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose an option: ";
}

static std::string read_line(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int main() {
    DocumentManager manager("documents.dat");

    while (true) {
        print_menu();
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string title = read_line("Enter title: ");
            std::string content = read_line("Enter content: ");
            int id = manager.create_document(title, content);
            std::cout << "Document created with ID " << id << "\n";
            pause();
        } else if (choice == "2") {
            std::string sid = read_line("Enter document ID: ");
            try {
                int id = std::stoi(sid);
                auto doc = manager.get_document(id);
                if (doc) {
                    std::cout << "\nID: " << doc->id << "\n";
                    std::cout << "Title: " << doc->title << "\n";
                    std::cout << "Created: " << doc->created_at << "\n";
                    std::cout << "Updated: " << doc->updated_at << "\n";
                    std::cout << "Content:\n" << doc->content << "\n";
                } else {
                    std::cout << "Document not found.\n";
                }
            } catch (...) {
                std::cout << "Invalid ID.\n";
            }
            pause();
        } else if (choice == "3") {
            std::string sid = read_line("Enter document ID: ");
            try {
                int id = std::stoi(sid);
                std::string title = read_line("Enter new title: ");
                std::string content = read_line("Enter new content: ");
                if (manager.update_document(id, title, content)) {
                    std::cout << "Document updated.\n";
                } else {
                    std::cout << "Document not found.\n";
                }
            } catch (...) {
                std::cout << "Invalid ID.\n";
            }
            pause();
        } else if (choice == "4") {
            std::string sid = read_line("Enter document ID: ");
            try {
                int id = std::stoi(sid);
                if (manager.delete_document(id)) {
                    std::cout << "Document deleted.\n";
                } else {
                    std::cout << "Document not found.\n";
                }
            } catch (...) {
                std::cout << "Invalid ID.\n";
            }
            pause();
        } else if (choice == "5") {
            auto docs = manager.list_documents();
            std::cout << "\nStored documents (" << docs.size() << "):\n";
            if (docs.empty()) {
                std::cout << "  (none)\n";
            }
            for (const auto& d : docs) {
                std::cout << "  [" << d.id << "] " << d.title
                          << " (updated: " << d.updated_at << ")\n";
            }
            pause();
        } else if (choice == "6") {
            std::cout << "Goodbye.\n";
            break;
        } else {
            std::cout << "Invalid option, try again.\n";
        }
    }

    return 0;
}
