
#include "../hpp/Image.hpp"

//
//const std::vector<std::vector<Pixel>> &Image::getOriginalImg() const {
//    return originalImg;
//}
//
//const std::vector<std::vector<Pixel>> &Image::getCurrentImg() const {
//    return currentImg;
//}
//

const std::string &Image::getFormat() const {
    return format;
}

const std::string &Image::getPath() const {
    return path;
}

//int Image::getCurrentWidth() const {
//    return currentWidth;
//}
//
//int Image::getCurrentHeight() const {
//    return currentHeight;
//}
//
//int Image::getMaxVal() const {
//    return maxVal;
//}
//
void Image::loadHeader(std::ifstream &is) {
    is >> this->format;
    if (!(format == "P1" ||
          format == "P2" ||
          format == "P3"))
        //        format != "P4" ||
        //        format != "P5" ||
        //        format != "P6")
    {
        throw std::runtime_error("Invalid file (header)");
    }
//    char ch;
    char ch = is.get();
    ch = is.get();
    do {
        if (ch == '#') {
            is.unget();
            getComment(is);
        }
        ch = is.get();
    } while (ch == '#');
    is.unget();
    is.unget();
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
    is >> this->width >> this->height;
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
//    currentWidth = width;
//    currentHeight = height;

    ch = is.get();
    ch = is.get();
    do {
        if (ch == '#') {
            is.unget();
            getComment(is);
        }
        ch = is.get();
    } while (ch == '#');
    is.unget();
    is.unget();

    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }

    if (this->format == "P2" || this->format == "P3") {
        is >> maxVal;
    }
    if (maxVal < 0 || maxVal > 255) {
        throw std::runtime_error("Max Value out of bounds");
    }
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
}

void Image::getComment(std::ifstream &is) const {
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }

    char ch = is.get();
    if (ch == '#') {
        while (ch != '\n') {
            ch = is.get();
            if (!is.good()) {
                throw std::runtime_error("Error reading file");
            }
        }
    }

    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
}

//Gross method
void Image::loadImg() {
//    Patch of code to fix what I didn't consider at first
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    file >> this->format;
    if (!file.good()) {
        throw std::runtime_error("Unable to read file");
    }

//    if (format == "P4") { loadP4(is); return; }
    if (format == "P5") {
        loadP5(file);
        file.close();
        return;
    }

    if (format == "P6") {
        loadP6(file);
        file.close();
        return;
    }

    file.close();

//    Patch of code to fix what I didn't consider at first

    std::ifstream is(path, std::ios::in);
    if (!is.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    loadHeader(is);
    if (format == "P1") { loadP1(is); }
    else if (format == "P2") { loadP2(is); }
    else if (format == "P3") { loadP3(is); }
    else {
        throw std::runtime_error("Invalid file format");
    };

    is.close();
}

Image::Image(const std::string &path) {
    isHorizontalCollage = false;
    this->path = path;
    maxVal = 1;
    loadImg();
}

Image::Image(const std::string &path1, const std::string &path2, bool is) {
    throw std::runtime_error("Functionality of this constructor is NOT implemented!");

    isHorizontalCollage = false;
    this->path = path;
    maxVal = 1;
    loadImg();
}

Image::~Image() = default;

void Image::loadP1(std::ifstream &is) {
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }

    char ch = is.get();
    ch = is.get();
    do {
        if (ch == '#') {
            is.unget();
            getComment(is);
        }
        ch = is.get();
    } while (ch == '#');
    is.unget();

    std::vector<Pixel> temp;

    int num = 0;
    is.unget();
    is.unget();
//    ch = is.get();
//    ch = is.get();

    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (is.eof()) {
                throw std::runtime_error("Error reading file");
            }
            is >> num;
            if (num < 0 || num > 1) {
                throw std::runtime_error("Pixel value out of bounds");
            }
            temp.push_back(Pixel((bool) num));
            num = 0;
        }
        this->originalImg.push_back(temp);
        temp.clear();
    }
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
}

void Image::loadP2(std::ifstream &is) {
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
    char ch = is.get();
    ch = is.get();
    do {
        if (ch == '#') {
            is.unget();
            getComment(is);
        }
        ch = is.get();
    } while (ch == '#');
    is.unget();

    std::vector<Pixel> temp;

    int num = 0;
    is.unget();
    is.unget();
//    ch = is.get();
//    ch = is.get();

    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (is.eof()) {
                throw std::runtime_error("Error reading file");
            }
            is >> num;
            if (num < 0 || num > maxVal) {
                throw std::runtime_error("Pixel value out of bounds");
            }
            temp.push_back(Pixel(num));
            num = 0;
        }
        this->originalImg.push_back(temp);
        temp.clear();
    }
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
}

void Image::loadP3(std::ifstream &is) {
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
    char ch = is.get();
    ch = is.get();
    do {
        if (ch == '#') {
            is.unget();
            getComment(is);
        }
        ch = is.get();
    } while (ch == '#');
    is.unget();

    is.unget();
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }

    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    std::vector<Pixel> temp;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (is.eof()) {
                throw std::runtime_error("Error reading file");

            }
            is >> num1;
            is >> num2;
            is >> num3;

            if ((num1 >= 0 && num1 <= maxVal) && (num2 >= 0 && num2 <= maxVal) && (num3 >= 0 && num3 <= maxVal)) {
                temp.push_back(Pixel(num1, num2, num3));
            } else {
                throw std::runtime_error("Pixel value out of bounds");
            }
            num1 = 0;
            num2 = 0;
            num3 = 0;
        }
        this->originalImg.push_back(temp);
        temp.clear();
    }
    if (!is.good()) {
        throw std::runtime_error("Error reading file");
    }
}

void Image::print() const {
    std::cout << format << std::endl;
    std::cout << currentWidth << " " << currentHeight << std::endl;

    if (format == "P1" || format == "P4") {

        for (int y = 0; y < currentHeight; ++y) {
            for (int x = 0; x < currentWidth; ++x) {
                std::cout << currentImg[y][x].val0 << " ";
            }
            std::cout << std::endl;
        }
    }

    if (format == "P2" || format == "P5") {
        std::cout << maxVal << std::endl;

        for (int y = 0; y < currentHeight; ++y) {
            for (int x = 0; x < currentWidth; ++x) {
                std::cout << currentImg[y][x].val1 << " ";
            }
            std::cout << std::endl;
        }
    }
    if (format == "P3" || format == "P6") {
        std::cout << maxVal << std::endl;

        for (int y = 0; y < currentHeight; ++y) {
            for (int x = 0; x < currentWidth; ++x) {
                std::cout << currentImg[y][x].val1 << " ";
                std::cout << currentImg[y][x].val2 << " ";
                std::cout << currentImg[y][x].val3 << " ";
            }
            std::cout << std::endl;
        }
    }
}

//TODO if P3 is gray check?
//TODO check if all three values are equal

void Image::grayscale() {
    if (format == "P3" || format == "P6") {
        int acc = 0;
        for (int y = 0; y < currentHeight; ++y) {
            for (int x = 0; x < currentWidth; ++x) {
                acc += currentImg[y][x].val1;
                acc += currentImg[y][x].val2;
                acc += currentImg[y][x].val3;
                acc /= 3;

                currentImg[y][x].val1 = acc;
                currentImg[y][x].val2 = acc;
                currentImg[y][x].val3 = acc;

                acc = 0;
            }
        }
    }
    return;
}

//TODO if image is already monochrome
void Image::monochrome() {
    if (format == "P2" || format == "P5") {
        monochromeP2();
    }
    if (format == "P3" || format == "P6") {
        monochromeP3();
    }
    return;
}

void Image::monochromeP2() {
    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            if (currentImg[y][x].val1 < (maxVal / 2)) {
                currentImg[y][x].val1 = 0;
                continue;
            }
            if (currentImg[y][x].val1 >= (maxVal / 2)) {
//                   val1 = maxVal?
                currentImg[y][x].val1 = maxVal;
                continue;
            }
        }
    }
}

void Image::monochromeP3() {
    int acc = 0;
    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            acc += currentImg[y][x].val1;
            acc += currentImg[y][x].val2;
            acc += currentImg[y][x].val3;
            acc /= 3;
            if (acc >= maxVal / 2) {
                currentImg[y][x].val1 = 255;
                currentImg[y][x].val2 = 255;
                currentImg[y][x].val3 = 255;
            }
            if (acc < maxVal / 2) {
                currentImg[y][x].val1 = 0;
                currentImg[y][x].val2 = 0;
                currentImg[y][x].val3 = 0;
            }
            acc = 0;
        }
    }
}

void Image::negative() {
    if (format == "P1" || format == "P4") { negativeP1(); }
    if (format == "P2" || format == "P5") { negativeP2(); }
    if (format == "P3" || format == "P6") { negativeP3(); }
}

void Image::rotateRight() {
    int rows = currentImg.size();
    int cols = currentImg[0].size();

    std::swap(this->currentWidth, this->currentHeight);

    std::vector<std::vector<Pixel>> rotated(cols, std::vector<Pixel>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = currentImg[i][j];
        }
    }
    currentImg = rotated;
}

void Image::rotateLeft() {
    int rows = currentImg.size();
    int cols = currentImg[0].size();

    std::swap(this->currentHeight, this->currentWidth);

    std::vector<std::vector<Pixel>> rotated(cols, std::vector<Pixel>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = cols - 1; j >= 0; --j) {
            rotated[cols - 1 - j][i] = currentImg[i][j];
        }
    }
    currentImg = rotated;
}

void Image::flipVertical() {
    int rows = currentImg.size();
    int cols = currentImg[0].size();

    std::vector<std::vector<Pixel>> flippedMatrix(rows, std::vector<Pixel>(cols));

    for (int i = 0; i < rows; ++i) {
        flippedMatrix[i] = currentImg[rows - 1 - i];
    }
    currentImg = flippedMatrix;

}

void Image::flipHorizontal() {
    std::vector<std::vector<Pixel>> flippedMatrix;

    for (const auto &row: currentImg) {
        std::vector<Pixel> flippedRow(row.rbegin(), row.rend());
        flippedMatrix.push_back(flippedRow);
    }
    currentImg = flippedMatrix;
}

void Image::crop(int xBeg, int yBeg, int xEnd, int yEnd) {

}

void Image::save() {
    std::string newPath = getNewPath();

//    if (format == "P4") {
//        saveP4(newPath);
//    }
    if (format == "P5") {
        saveP5(newPath);
        return;
    }
    if (format == "P6") {
        saveP6(newPath);
        return;
    }

    std::ofstream out(newPath, std::ios::out);
    if (!out) {
        throw std::runtime_error("Couldn't open file to save");

    }

    out << format << '\n';
    out << currentWidth << ' ' << currentHeight << '\n';

    if ((format != "P1")) {
        out << maxVal << '\n';
    }

//save pixel data
    if (format == "P1") {
        saveP1(out);
    }
    if (format == "P2") {
        saveP2(out);
    }
    if (format == "P3") {
        saveP3(out);
    }

    out.close();
}

void Image::negativeP1() {
    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            if (currentImg[y][x].val0 == 0) {
                currentImg[y][x].val0 = 1;
//                continue;
            } else if (currentImg[y][x].val0 == 1) {
                currentImg[y][x].val0 = 0;
//                continue;
            } else throw std::runtime_error("INVALID Pixel value P1");
        }
    }
}

void Image::negativeP2() {
    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            currentImg[y][x].val1 = maxVal - currentImg[y][x].val1;
        }
    }
}

void Image::negativeP3() {
    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            currentImg[y][x].val1 = maxVal - currentImg[y][x].val1;
            currentImg[y][x].val2 = maxVal - currentImg[y][x].val2;
            currentImg[y][x].val3 = maxVal - currentImg[y][x].val3;
        }
    }
}

//TODO should also be possible to do without spaces and new line
void Image::saveP1(std::ofstream &out) {
    if (!out.good()) {
        throw std::runtime_error("Error reading file");
    }
    int lastPixel = currentWidth * currentHeight;
    int currPixel = 0;

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            out << currentImg[y][x].val0;
            currPixel++;
            if (currPixel < lastPixel) {
                out << ' ';
            }
        }
        out << '\n';
    }
    if (!out.good()) {
        throw std::runtime_error("Error reading file");
    }
}

//TODO
void Image::saveP2(std::ofstream &out) {
    if (!out.good()) {
        throw std::runtime_error("Error reading file");
    }
    int lastPixel = currentWidth * currentHeight;
    int currPixel = 0;

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            out << currentImg[y][x].val1;
            currPixel++;
            if (currPixel < lastPixel) {
                out << ' ';
            }
        }
        out << '\n';
    }
    if (!out.good()) {
        throw std::runtime_error("Error reading file");
    }
}

//TODO
void Image::saveP3(std::ofstream &out) {
    if (!out.good()) {
        throw std::runtime_error("Error reading file");
    }
    int lastPixel = currentWidth * currentHeight;
    int currPixel = 0;

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            out << currentImg[y][x].val1 << ' ';
            out << currentImg[y][x].val2 << ' ';
            out << currentImg[y][x].val3;
            currPixel++;
            if (currPixel < lastPixel) {
                out << ' ';
            }
        }
        out << '\n';
    }
    if (!out.good()) {
        throw std::runtime_error("Error reading file");
    }
}

std::string Image::getNewPath() {

    std::time_t currentTime = std::time(nullptr);

    std::string timeString = std::asctime(std::localtime(&currentTime));

    std::string year = timeString.substr(20, 4);
    std::string month = timeString.substr(4, 3);
    std::string day = timeString.substr(8, 2);
    std::string hour = timeString.substr(11, 2);
    std::string minute = timeString.substr(14, 2);
    std::string second = timeString.substr(17, 2);

    std::string iso8601String = "_" + year + "_" + month + "_" + day + "_" + hour + "_" + minute + "_" + second;

    std::string newPath = path;
    newPath.pop_back();
    newPath.pop_back();
    newPath.pop_back();
    newPath.pop_back();

    newPath += iso8601String;
    if (format == "P1" || format == "P4") {
        newPath += ".pbm";
    }
    if (format == "P2" || format == "P5") {
        newPath += ".pgm";
    }
    if (format == "P3" || format == "P6") {
        newPath += ".ppm";
    }

    std::cout << "Path of new image: " << newPath << std::endl;

    return newPath;
}

void Image::resetCurrentImage() {
    currentWidth = width;
    currentHeight = height;
    this->currentImg = this->originalImg;
}

void Image::loadP5(std::ifstream &file) {
//    reads file that don't have any comments
    file >> width >> height;
    file >> maxVal;
    if (maxVal < 0 || maxVal > 255) {
        throw std::runtime_error("Max Value out of bounds");
    }
    file.ignore();

    std::vector<Pixel> temp;
    uint8_t num1;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (file.eof()) {
                throw std::runtime_error("Error reading file (EOF)");
            }
            file.read(reinterpret_cast<char *>(&num1), sizeof(num1));
            if (num1 < 0 || num1 > maxVal) {
                throw std::runtime_error("Pixel value out of bounds");
            }
            temp.push_back(Pixel((int) num1));
        }
        originalImg.push_back(temp);
        temp.clear();
    }
}

void Image::loadP6(std::ifstream &file) {
//    reads file that don't have any comments
    file >> width >> height;
    file >> maxVal;
    if (maxVal < 0 || maxVal > 255) {
        throw std::runtime_error("Max Value out of bounds");
    }
    file.ignore();

    std::vector<Pixel> temp;
    uint8_t num1;
    uint8_t num2;
    uint8_t num3;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (file.eof()) {
                throw std::runtime_error("Error reading file (EOF)");
            }
            file.read(reinterpret_cast<char *>(&num1), sizeof(num1));
            file.read(reinterpret_cast<char *>(&num2), sizeof(num2));
            file.read(reinterpret_cast<char *>(&num3), sizeof(num3));
            if ((num1 >= 0 && num1 <= maxVal) && (num2 >= 0 && num2 <= maxVal) && (num3 >= 0 && num3 <= maxVal)) {
                temp.push_back(Pixel((int) num1, (int) num2, (int) num3));
            } else {
                throw std::runtime_error("Pixel value out of bounds");
            }
        }
        originalImg.push_back(temp);
        temp.clear();
    }
}

void Image::saveP5(std::string &newPath) {
    std::ofstream file(newPath, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could ot open file");
    }
    file << format << '\n';
    file << currentWidth << ' ' << currentHeight << '\n';
    file << maxVal << '\n';

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            if (!file.good()) {
                throw std::runtime_error("Error writing in file");
            }
            file.write(reinterpret_cast<char *> (&currentImg[y][x].val1), sizeof(uint8_t));
        }
    }
    file.close();
}

void Image::saveP6(std::string &newPath) {
    std::ofstream file(newPath, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could ot open file");
    }
    file << format << '\n';
    file << currentWidth << ' ' << currentHeight << '\n';
    file << maxVal << '\n';

    for (int y = 0; y < currentHeight; ++y) {
        for (int x = 0; x < currentWidth; ++x) {
            if (!file.good()) {
                throw std::runtime_error("Error writing in file");
            }
            file.write(reinterpret_cast<char *> (&currentImg[y][x].val1), sizeof(uint8_t));
            file.write(reinterpret_cast<char *> (&currentImg[y][x].val2), sizeof(uint8_t));
            file.write(reinterpret_cast<char *> (&currentImg[y][x].val3), sizeof(uint8_t));
        }
    }
    file.close();
}

//TODO CROP


