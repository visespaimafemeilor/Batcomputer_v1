#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class BatcomputerException : public std::exception {
protected:
    std::string message;
public:
    explicit BatcomputerException(std::string msg) : message(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
    virtual ~BatcomputerException() noexcept = default;
};

class FileLoadException : public BatcomputerException {
public:
    explicit FileLoadException(const std::string& filename) : BatcomputerException("Failed to load file: " + filename) {}
};

class InvalidDataException : public BatcomputerException {
public:
    explicit InvalidDataException(const std::string& details) : BatcomputerException("Invalid data encountered: " + details) {}
};

class DatabaseOperationException : public BatcomputerException {
public:
    explicit DatabaseOperationException(const std::string& operation) : BatcomputerException("Database operation failed: " + operation) {}
};

#endif // EXCEPTIONS_H

