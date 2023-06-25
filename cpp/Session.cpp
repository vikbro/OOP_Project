
#include "../hpp/Session.hpp"

void Session::add(std::string &path) {
    images.push_back(Image(path));
    imgCommands.push_back(Command());
}

void Session::save() {
//    optimizeCommands();
    executeCommands();

    for (Image &image: images) {
        image.save();
    }
}

Session::Session(size_t id) : id(id) {

}

void Session::listSession() const {
    for (const Image &image: images) {
        std::cout << image.getPath();
        if (image.getFormat() == "P1" || image.getFormat() == "P4") {
            std::cout << " - portable bitmap format" << std::endl;
        }
        if (image.getFormat() == "P2" || image.getFormat() == "P5") {
            std::cout << " - portable graymap format" << std::endl;
        }
        if (image.getFormat() == "P3" || image.getFormat() == "P6") {
            std::cout << " - portable pixmap format" << std::endl;
        }
    }
}

void Session::optimizeCommands() {
    for (Command &commands: imgCommands) {
        commands.optimizeCommands();
    }
}

void Session::grayscale() {
    for (Command &command: imgCommands) {
        command.addCommand("grayscale");
    }
}

void Session::monochrome() {
    for (Command &command: imgCommands) {
        command.addCommand("monochrome");
    }
}

void Session::negative() {
    for (Command &command: imgCommands) {
        command.addCommand("negative");
    }
}

void Session::rotateRight() {
    for (Command &command: imgCommands) {
        command.addCommand("rotate_right");
    }
}

void Session::rotateLeft() {
    for (Command &command: imgCommands) {
        command.addCommand("rotate_left");
    }
}

void Session::flipVertical() {
    for (Command &command: imgCommands) {
        command.addCommand("flip_vertical");
    }
}

void Session::flipHorizontal() {
    for (Command &command: imgCommands) {
        command.addCommand("flip_horizontal");
    }
}

void Session::undo() {
    for (Command &command: imgCommands) {
        command.undo();
    }
}

void Session::redo() {
    for (Command &command: imgCommands) {
        command.redo();
    }
}

size_t Session::getID() const {
    return this->id;
}

void Session::executeCommands() {

    for (int i = 0; i < images.size(); i++) {
        images[i].resetCurrentImage();
        std::vector<std::string> executeCommands = imgCommands[i].getCommands();

        for (std::string &command: executeCommands) {
            if (command == "negative") {
                images[i].negative();
                continue;
            }
            if (command == "grayscale") {
                images[i].grayscale();
                continue;
            }
            if (command == "monochrome") {
                images[i].monochrome();
                continue;
            }
            if (command == "rotate_right") {
                images[i].rotateRight();
                continue;
            }
            if (command == "rotate_left") {
                images[i].rotateLeft();
                continue;
            }
            if (command == "flip_horizontal") {
                images[i].flipHorizontal();
                continue;
            }
            if (command == "flip_vertical") {
                images[i].flipVertical();
                continue;
            } else {
                std::cout << "INVALID EXEC COMMAND" << std::endl;
            }
//            TODO CROP

        }
    }
}

//TODO
void Session::makeCollageHorizontal(const std::string &path1, const std::string &path2) {

}
// TODO
void Session::makeCollageVertical(const std::string &path1, const std::string &path2) {

}





