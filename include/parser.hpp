#pragma once
#include "nodes.hpp"

class Parser {
    public:
        static std::shared_ptr<FileNode> parseFile(const std::string& filename);
};
