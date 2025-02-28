# AMPHINICY technologies – C++ technical interview preparation
## Library Management System

The following repocitorty is a C++ application for managing a library collection. This system allows users to add, search, borrow, return, and remove books while persisting data between sessions. 

## Table of Contents

- [Features](#features)
- [Dependencies](#dependencies)
- [Building and Running](#building-and-running)
  - [Using the Automated Script](#using-the-automated-script)
  - [Manual Building](#manual-building)
- [Usage](#usage)
- [Data Storage](#data-storage)
- [Third-Party Libraries](#third-party-libraries)
- [License](#license)

## Features

- Add books to the library with title, author, year, and availability status
- Search for books by ID, title, or author
- Borrow and return books (update availability status)
- Display all books in the library
- Remove books from the library
- Data persistence using JSON file storage

## Dependencies

- C++17 standard library
- nlohmann/json (included as a header-only library)

## Building and Running

### Using the Automated Script

The easiest way to build and run the application is with the provided shell script:

```bash
# Make the script executable if needed
chmod +x run.sh

# Build and run the application
./run.sh

# To only run the application (if already built)
./run.sh run
```

The script will:
1. Detect your operating system
2. Check for required build tools (make, g++)
3. Download the necessary JSON library if not already present
4. Compile the project
5. Offer to run the application

### Manual Building

If you prefer to build the project manually:

```bash
# Create necessary directories
mkdir -p bin obj data deps/include/nlohmann

# Download JSON library if needed
curl -o deps/include/nlohmann/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp

# Build the project
make

# Run the application
./bin/library_management_system
```

## Usage

Upon starting the application, you'll be presented with a menu:

```
Library Management System
-------------------------
1. Add a new book
2. Search for a book
3. Borrow a book
4. Return a book
5. Display all books
6. Remove a book
0. Exit
Enter your choice:
```

Navigate the menu by entering the number corresponding to your desired action.

## Data Storage

The application stores library data in JSON format at `data/books.json`. This file is created automatically if it doesn't exist and is updated whenever changes are made to the library collection.

## Third-Party Libraries

### nlohmann/json

This project uses the JSON for Modern C++ library by Niels Lohmann.

- Project: https://github.com/nlohmann/json
- License: MIT License
- Version: Latest (automatically downloaded by the run script)

The MIT License states:

```
Copyright (c) 2013-2022 Niels Lohmann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## License

This project is released under the MIT License. See the LICENSE file for details.
