
#ifndef OOP_PROJECT_SESSION_HPP
#define OOP_PROJECT_SESSION_HPP


#include "Image.hpp"
#include "Command.hpp"

/// The Session class stores all the Images in use.
///
/// The Session class stores the Images and the transformation commands paired with them
/// This class also executes all the image transformation commands.
class Session {
private:
    std::vector<Image> images; ///< Stores the currently used images.
    std::vector<Command> imgCommands; ///< Stored the currently applied transformation commands.
//    TODO this should be const
    const size_t id; ///< Stored the session ID.

public:
/// Returns the session ID
    size_t getID() const;

private:
/// This command applies the Command::optimizeCommands() to all the imaged and their transformation commands.
    void optimizeCommands();

/// This command executes all the current transformations on the current images.
    void executeCommands();

public:
/// Constructor to the Session class
    Session(size_t id);

/// In the console returns all the currently used images.
    void listSession() const;

//    TODO
/// Makes a horizontal collage with to images.
/// @attention This method **DOESN'T** work!
    void makeCollageHorizontal(const std::string &path1, const std::string &path2);

/// Makes a vertical collage with to images.
/// @attention This method **DOESN'T** work!
    void makeCollageVertical(const std::string &path1, const std::string &path2);

/// \param path takes the path to the image you want to add in the current session.
    void add(std::string &path);
/// Saves the Images in the current session.

    void save();
/// Removes the last command in the current session commands.

    void undo();
/// Undoes the removal of the last command in the current session.

    void redo();
/// Enters the command *grayscale* in the current session commands.

    void grayscale();
/// Enters the commands *monochrome* in the current session commands.

    void monochrome();
/// Enters the commands *negative* in the current session commands.

    void negative();
/// Enters the commands *rotate_right* in the current session commands.

    void rotateRight();
/// Enters the commands *rotate_left* in the current session commands.

    void rotateLeft();
/// Enters the commands *flip_vertical* in the current session commands.

    void flipVertical();
/// Enters the commands *flip_horizontal* in the current session commands.

    void flipHorizontal();

//    TODO crop
//    void crop(int xBeg, int yBeg, int xEnd, int yEnd);

};


#endif //OOP_PROJECT_SESSION_HPP
