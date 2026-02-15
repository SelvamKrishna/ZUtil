#include "../zutil.hpp" // IWYU pragma: keep

#include "../example/file_handling.hpp" // IWYU pragma: keep
#include "../example/logging.hpp"       // IWYU pragma: keep
#include "../example/testing.hpp"       // IWYU pragma: keep

void Playgrond();
void RunAllTests();

int main(void)
{
    std::cout << "Running main application..." << '\n';

#if 1
    RunAllTests();
#else
    Playgrond();
#endif

    return 0;
}

#include <fstream>

void Playgrond()
{
    // Writing to a file
    std::ofstream outFile("example.txt");

    if (!outFile.is_open())
        throw std::runtime_error {"Error opening file for writing!"};

    outFile << "Hello, World!\n";
    outFile << "This is a test file.\n";
    outFile.close();

    // Reading from a file
    std::ifstream inFile("example.txt");
    std::string line;

    if (!inFile.is_open())
        throw std::runtime_error {"Error opening file for reading!"};

    while (std::getline(inFile, line))
        std::cout << line << std::endl;

    inFile.close();
}

void RunAllTests()
{
    example::BasicLogging();
    example::LoggerClass();
    example::OperationScopeLogging();
    // example::OperationFailLogging();  // Uncomment to test operation failure
    // example::BasicAssertion();        // Uncomment to test assertion failure
    example::UnitTesting();
    example::SuiteTesting();
}
