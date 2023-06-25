
#ifndef OOP_PROJECT_COMMAND_HPP
#define OOP_PROJECT_COMMAND_HPP


#include <vector>
#include <string>

/// This class stores all the commands entered to transform the current image
///
/// The command class is "paired" with the current image in the session
///@see Session::imgCommands

class Command {
private:
    std::vector<std::string> commands; ///< Stores all the current commands.
    std::vector<std::string> redoCommands; ///< Stores all the undone commands until another command is added.

public:
/// Optimizes all the commands in order to make the least possible
/// amount of transformations
///@attention This method **DOESN'T** work.
    void optimizeCommands();
/// Adds the next command needed to be added
/// \param text contains in *string* the command needed to be added.
    void addCommand(const std::string &text);
///removes the last command and adds it to the *redoCommands* vector.
    void undo();
/// removes the last redo command and adds it to the *commands* vector.
    void redo();
/// Getter that returns the *commands* vector
    std::vector<std::string> getCommands() const;
};

#endif //OOP_PROJECT_COMMAND_HPP
