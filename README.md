# Document Management System (C++)

A console application for creating, storing, retrieving, updating, and
deleting documents using object-oriented design and file handling.

## Design

* `Document` — data model holding `id`, `title`, `content`, `created_at`,
  `updated_at`. Serializes to a single delimited line for storage.
* `DocumentManager` — persists documents to a flat data file
  (`documents.dat`), one line per document. Handles create / read /
  update / delete and id allocation.
* `main.cpp` — interactive menu-driven driver.

## Build & Run

```bash
make          # build the dms binary
make run      # build and launch the interactive menu
make clean    # remove build artifacts and the data file
```

## Menu

| Option | Action |
|--------|--------|
| 1 | Create a document (title + content) |
| 2 | View a document by ID |
| 3 | Update a document by ID |
| 4 | Delete a document by ID |
| 5 | List all documents |
| 6 | Exit |

## Requirements

* A C++17 compiler (`g++` recommended)
* GNU Make

## License

MIT
