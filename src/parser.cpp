#include <parser.hpp>
#include <fstream>
#include <tokens.hpp>
#include <filesystem>

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::shared_ptr<FileNode> Parser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    auto fileNode = std::make_shared<FileNode>();
    fileNode->filename = filename.substr(filename.find_last_of(std::filesystem::path::preferred_separator) + 1);
    bool parsingConditions = true;
    std::string prefix, postfix;

    while (std::getline(file, line)) {
        line = trim(line);
        // Ignore empty lines or lines with comments
        if (line.empty()) continue;
        if (line[0] == TOKEN_COMMENT) continue;

        if (parsingConditions) {
            switch(line[0]) {
                case TOKEN_AND:
                case TOKEN_OR:
                case TOKEN_MAYBE:
				case TOKEN_CONDADD:
                case TOKEN_EQUALS:
                    fileNode->addCondition(std::make_shared<ConditionNode>(line.substr(1), line[0]));
                    break;
                case TOKEN_PREFIX:
                    fileNode->prefix = line.substr(1);
                    break;
                case TOKEN_POSTFIX:
                    fileNode->postfix = line.substr(1);
                    break;
                default:
                    parsingConditions = false;
            }
        }

        if (!parsingConditions) {
            fileNode->addLine(std::make_shared<LineNode>(line));
        }
    }

    return fileNode;
}

