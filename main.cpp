#include <iostream>
#include <stdexcept>

// Базовий клас для всіх винятків
class CustomException : public std::runtime_error {
public:
    CustomException(const std::string& message) : std::runtime_error(message) {}
};

// Виняток для математичних помилок
class MathException : public CustomException {
public:
    MathException(const std::string& message) : CustomException("Math error: " + message) {}
};

// Виняток для ділення на нуль
class DivisionByZeroException : public MathException {
public:
    DivisionByZeroException() : MathException("Division by zero") {}
};

// Виняток для помилок роботи з файлами
class FileException : public CustomException {
public:
    FileException(const std::string& message) : CustomException("File error: " + message) {}
};

// Виняток для відсутності файлу
class FileNotFoundException : public FileException {
public:
    FileNotFoundException() : FileException("File not found") {}
};

// Виняток для нестачі пам'яті
class MemoryException : public CustomException {
public:
    MemoryException(const std::string& message) : CustomException("Memory error: " + message) {}
};

// Виняток для нестачі пам'яті
class OutOfMemoryException : public MemoryException {
public:
    OutOfMemoryException() : MemoryException("Out of memory") {}
};

int main() {
    try {
        throw DivisionByZeroException();
    } catch (const CustomException& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        throw FileNotFoundException();
    } catch (const CustomException& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        throw OutOfMemoryException();
    } catch (const CustomException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
