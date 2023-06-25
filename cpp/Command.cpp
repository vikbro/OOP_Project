
#include "../hpp/Command.hpp"

//TODO OPTIMIZE COMMANDS ON SAVE EXECUTION
void Command::optimizeCommands(){

}

void Command::addCommand(const std::string& text) {
    commands.push_back(text);
}

void Command::undo() {
    if (!commands.empty()) {
        redoCommands.push_back(commands.back());
        commands.pop_back();
    }
}

void Command::redo() {
    if (!redoCommands.empty()) {
        commands.push_back(redoCommands.front());
        redoCommands.erase(redoCommands.begin());
    }
}

std::vector<std::string> Command::getCommands() const {
    return this->commands;
}