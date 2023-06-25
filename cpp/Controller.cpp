
#include "../hpp/Controller.hpp"

// TODO ADD THIS TO OPERATOR >>
void Controller::toLowerCase(std::string &input) {
    for (char &c: input) {
        c = std::tolower(c);
    }
}

std::istream &operator>>(std::istream &input, Controller &ctr) {
    std::vector<std::string> outputs;

    std::cout << "Enter input (press Enter to end):\n";

    std::string line;
    std::getline(std::cin, line);

    std::string token;
    std::size_t startPos = 0;
    std::size_t endPos = 0;

    while ((endPos = line.find(' ', startPos)) != std::string::npos) {
        token = line.substr(startPos, endPos - startPos);
        if (token != "") {
            outputs.push_back(token);
            startPos = endPos + 1;
        }
        startPos = endPos + 1;
    }

    token = line.substr(startPos);
    if (token != "") {
        outputs.push_back(token);
    }
//    entered enter
    if (outputs.begin() == outputs.end()) {
        throw std::runtime_error("Not a command!");
    }

    if (outputs[0] != ">") {
        throw std::runtime_error("Not a command!");
    }
//    entered only ">"
    if (outputs.begin() + 1 == outputs.end()) {
        throw std::runtime_error("Invalid command!");
    }
    ctr.toLowerCase(outputs[1]);

    if (outputs[1] == "load") {
        if (outputs.begin() + 2 == outputs.end()) {
            throw std::runtime_error("Invalid load command!");
        }

        std::vector<std::string>::iterator iter = (outputs.begin() + 2);
        std::vector<std::string> temp;
        for (iter; iter < outputs.end(); iter++) {
            temp.push_back(*iter);
        }
        ctr.load(temp);
        return input;
    }

    if (outputs[1] == "list") {
        if (outputs.begin() + 2 == outputs.end()) {
            throw std::runtime_error("Invalid list session command!");
        }
        if (outputs[2] == "session") {
            ctr.listSession();
            return input;
        } else {
            throw std::runtime_error("Invalid list session command!");
        }
    }

    if (outputs[1] == "save") {
        ctr.save();
        return input;
    }

    if (outputs[1] == "rotate") {
        if (outputs.begin() + 2 == outputs.end()) {
            throw std::runtime_error("Invalid rotate command!");
        }
        ctr.toLowerCase(outputs[2]);

        if (outputs[2] == "left") {
            ctr.rotateLeft();
            return input;
        }
        if (outputs[2] == "right") {
            ctr.rotateRight();
            return input;
        } else {
            throw std::runtime_error("Invalid rotate command!");
        }
    }

    if (outputs[1] == "make") {
        if (outputs.begin() + 2 == outputs.end()) {
            throw std::runtime_error("Invalid make collage command!");
        }
        if (outputs[2] == "collage") {
            if (outputs.begin() + 3 == outputs.end()) {
                throw std::runtime_error("Invalid make collage command!");
            }
            if (outputs[3] == "horizontal") {
                if (outputs.begin() + 4 == outputs.end() || outputs.begin() + 5 == outputs.end()) {
                    throw std::runtime_error("Invalid make collage command!");
                }
                ctr.makeCollageHorizontal(outputs[4], outputs[5]);
            }
            if (outputs[3] == "vertical") {
                if (outputs.begin() + 4 == outputs.end() || outputs.begin() + 5 == outputs.end()) {
                    throw std::runtime_error("Invalid make collage command!");
                }
                ctr.makeCollageVertical(outputs[4], outputs[5]);
            } else {
                throw std::runtime_error("Invalid make collage command!");
            }
        } else {
            throw std::runtime_error("Invalid make collage command!");

        }
    }

    if (outputs[1] == "flip") {
        if (outputs.begin() + 2 == outputs.end()) {
            throw std::runtime_error("Invalid flip command!");
        }
        if (outputs[2] == "top") {
            ctr.flipTop();
            return input;
        }
        if (outputs[2] == "left") {
            ctr.flipLeft();
            return input;
        } else {
            throw std::runtime_error("Invalid flip command!");
        }
    }

    if (outputs[1] == "add") {
        if (outputs.begin() + 2 == outputs.end()) {
            throw std::runtime_error("Invalid add command!");
        }
        ctr.add(outputs[2]);
        return input;
    }

    if (outputs[1] == "switch") {
        if (outputs.begin() + 2 == outputs.end() || outputs.begin() + 3 == outputs.end()) {
            throw std::runtime_error("Invalid switch command!");
        }
        if (outputs[2] == "session") {
            int id;
            id = std::stoi(outputs[3]);
            ctr.switchSession(id);
            return input;
        }
    }

    if (outputs[1] == "negative") {
        ctr.negative();
        return input;
    }

    if (outputs[1] == "grayscale") {
        ctr.grayscale();
        return input;
    }

    if (outputs[1] == "monochrome") {
        ctr.monochrome();
        return input;
    }

    if (outputs[1] == "undo") {
        ctr.undo();
        return input;
    }

    if (outputs[1] == "redo") {
        ctr.redo();
        return input;
    }

    if (outputs[1] == "exit") {
        ctr.exit();
        return input;

    } else {
        throw std::runtime_error("Invalid command!");
    }
}

bool Controller::getStopFlag() const {
    return this->stopFlag;
}

void Controller::add(std::string path) {

    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    this->sessions[currentSession - 1].add(path);
}

bool Controller::load(std::vector<std::string> &files) {
    //Switching sessions might not work intended
    try {
        size++;
        currentSession = size;
//        currentSession++;
        this->sessions.push_back(Session(currentSession));
        std::vector<std::string>::iterator iter = (files.begin());

        for (iter; iter < files.end(); iter++) {
            add(*iter);
        }
        std::cout << "Session with ID: " << currentSession << " started" << std::endl;
        return true;
    } catch (const std::exception &ex) {
// Probably not working correctly
        this->sessions.pop_back();
        currentSession--;
        throw std::runtime_error(ex.what());

    }
}

void Controller::switchSession(size_t sesNum) {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    if (sesNum > this->sessions.size() || sesNum < 1) {
        throw std::runtime_error("Invalid session ID");
    }
    currentSession = sesNum;
    std::cout << "Switched session to session with ID: " << currentSession << std::endl;
}

void Controller::listSession() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    std::cout << "Files in session with ID " << currentSession << ":" << std::endl;
    sessions[currentSession - 1].listSession();
}

void Controller::grayscale() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].grayscale();
}

void Controller::exit() {
    this->stopFlag = true;
}

void Controller::monochrome() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].monochrome();
}

void Controller::negative() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].negative();
}

void Controller::rotateLeft() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].rotateLeft();
}

void Controller::rotateRight() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].rotateRight();
}

void Controller::flipTop() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].flipHorizontal();
}

void Controller::flipLeft() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].flipVertical();
}

void Controller::undo() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].undo();
}

void Controller::redo() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].redo();
}

void Controller::makeCollageHorizontal(const std::string &path1, const std::string &path2) {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].makeCollageHorizontal(path1, path2);
}

void Controller::makeCollageVertical(const std::string &path1, const std::string &path2) {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].makeCollageHorizontal(path1, path2);
}

void Controller::save() {
    if (this->hasInitializedSession() == false) {
        throw std::runtime_error("NO initialized session! \"load\" a session");
    }
    sessions[currentSession - 1].save();
}

//TODO maybe throw exception?
bool Controller::hasInitializedSession() {
    if (sessions.empty()) {
        return false;
    }
    return true;
}

Controller::Controller() {
    this->currentSession = 0;
    this->stopFlag = false;
    this->size = sessions.size();
}

void Controller::crop(int xBeg, int yBeg, int xEnd, int yEnd) {

    return;
}
