#pragma once
#include <string>
#include <vector>
#include <memory>
#include "nodes.hpp"
#include <unordered_map>

class StringGenerator {
    public:
        std::string generate(const std::vector<std::shared_ptr<FileNode>>& files, const std::string &interconnect);
    private:
        bool evaluateConditions(const std::vector<std::shared_ptr<ConditionNode>>& conditions, const std::string& finalString, const std::unordered_map<std::string, std::string> &selected_lines, std::string &prev_line);
        std::string selectRandomLine(const std::vector<std::shared_ptr<LineNode>>& lines);
};
