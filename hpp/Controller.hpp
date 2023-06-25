
#ifndef OOP_PROJECT_CONTROLLER_HPP
#define OOP_PROJECT_CONTROLLER_HPP


#include "Session.hpp"

/// Controller class. - Command Input
///
/// The controller class is responsible for reading commands from
/// the console and forward them to the other classes in order to
/// implement the said command. This class could maybe be made a
/// singleton.
class Controller {
private:
    std::vector<Session> sessions; ///< This stores all the sessions during use.
    size_t size; ///<This stores the amount of sessions available.
    size_t currentSession; ///< Stores the current session in use.
    bool stopFlag; ///< Contains a bool value if the programme should be terminated.

private:
/// This is a private method that has the purpose to turn to lowercase
/// all the commands entered through the console
///@param input is a refrence to the string of the command
///needed to be lowercased
    void toLowerCase(std::string &input);

/// Returns a *bool* value depending on weather there are any loaded sessions.
    bool hasInitializedSession();
//    bool checkCommand(size_t ,const std::vector<std::string>& output);

public:
/// Constructor to the Controller class
    Controller();

/// Method that returns a *bool* depending if the process should be
/// stoped or not
    bool getStopFlag() const;

private:
///
    bool load(std::vector<std::string> &outputs);

///
/// \param path takes the path to the image you want to add in the current session.
    void add(std::string path);
///
/// Enters the command *grayscale* in the current session commands.
    void grayscale();
///
/// Enters the commands *monochrome* in the current session commands.
    void monochrome();
/// Enters the commands *negative* in the current session commands.
    void negative();
/// Enters the commands *rotate_left* in the current session commands.
    void rotateLeft();
/// Enters the commands *rotate_right* in the current session commands.
    void rotateRight();
/// Enters the commands *flip_horizontal* in the current session commands.
    void flipTop();
/// Enters the commands *flip_vertical* in the current session commands.
    void flipLeft();
/// Removes the last command in the current session commands.
    void undo();
/// Undoes the removal of the last command in the current session.
    void redo();
/// Saves the Images in the current session.
    void save();

//    TODO crop()
/// Crops an image.
/// @attention This method **DOESN'T** work.
    void crop(int xBeg, int yBeg, int xEnd, int yEnd);
/// Makes a horizontal collage with to images.
/// @attention This method **DOESN'T** work!
    void makeCollageHorizontal(const std::string &path1, const std::string &path2);
/// Makes a vertical collage with to images.
/// @attention This method **DOESN'T** work!
    void makeCollageVertical(const std::string &path1, const std::string &path2);

/// In the console returns all the currently used images.
    void listSession();
/// Switches the currently used session to the one you *desire*.
/// \param sesNum the session ID you want to enter
    void switchSession(size_t sesNum);
/// raises the stopFlag and terminates the programme.
/// @see stopFlag
    void exit();


public:
/// All commands are entered through this operator
    friend std::istream &operator>>(std::istream &input, Controller &ctr);

};


#endif //OOP_PROJECT_CONTROLLER_HPP
