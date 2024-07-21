#include <nodes.hpp>

void FileNode::addCondition(const std::shared_ptr<ConditionNode>& condition) {
    conditions.push_back(condition);
}

void FileNode::addLine(const std::shared_ptr<LineNode>& line) {
    lines.push_back(line);
}