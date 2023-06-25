
#ifndef OOP_PROJECT_IMAGE_HPP
#define OOP_PROJECT_IMAGE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "Pixel.hpp"
//#include "Commands.hpp"

/// The Image class is where all the important transformations happen
///
/// This class is responsible for all image realated things

class Image {
private:
    // could be const?
    std::vector<std::vector<Pixel>> originalImg; ///< This is a matrix in which all the original image pixel data is stored
    ///<@note This matrix should be of const value since we don't wont to change the original image.
    std::vector<std::vector<Pixel>> currentImg; ///< This is a matrix which stores all the current image pixel data.
    std::string format; ///< Holds the original image format (*P1,P2, ..etc.*).
    std::string path; ///< Stored the original image file path.
    // could be const?
    int width; ///< Stored the width of the original image.
    // could be const?
    int height; ///< Stored the height of the original image.
    int currentWidth; /// <Stores the current image width.
    int currentHeight; ///< Stores the current image height.
    int maxVal; ///< Stores the max value of the image.
//    TODO
    bool isHorizontalCollage; ///< Stores *bool* value if the Image is a collage of two images
    /// @note If isHorizontalCollage = true and the Image class is initialized through


public:
/// Image constructor
/// \param path is a reference to the path of the current image
    Image(const std::string &path);

/// A constructor handling cases for image collage
/// \param path1 path of the first image file
/// \param path2 path of the second image file
/// @attention This constructor doesnt work its only a concept
    Image(const std::string &path1, const std::string &path2, bool is);

///Image destructor (default)
    ~Image();

public:
//    const std::vector<std::vector<Pixel>> &getOriginalImg() const;

//    const std::vector<std::vector<Pixel>> &getCurrentImg() const;
/// Getter method that returns the format of the image
    const std::string &getFormat() const;
/// Getter method that returns> the path of the image
    const std::string &getPath() const;
//
//    int getCurrentWidth() const;
//
//    int getCurrentHeight() const;
//
//    int getMaxVal() const;

private:
/// Loads the header of the image
/// @note This function could be made to work more efficiently
    void loadHeader(std::ifstream &);

    void getComment(std::ifstream &) const;

/// Returns a string with the the new file location
    std::string getNewPath();

/// Load a **P1** formatted image
    void loadP1(std::ifstream &);

/// Load a **P2** formatted image
    void loadP2(std::ifstream &);

/// Load a **P3** formatted image
    void loadP3(std::ifstream &);

//    void loadP4(std::ifstream&);
/// Load a **P5** formatted image
    void loadP5(std::ifstream &);

/// Load a **P6** formatted image
    void loadP6(std::ifstream &);

/// Save an image with format **P1**.
/// @param out is the output file stream where the image will be saved.
    void saveP1(std::ofstream &out);

/// Save an image with format **P2**
/// @param out is the output file stream where the image will be saved.
    void saveP2(std::ofstream &out);

/// Save an image with format **P3**.
/// @param out is the output file stream where the image will be saved.
    void saveP3(std::ofstream &out);

//    void saveP4(std::string& newPath);
/// Save an image with format **P5**
///@note it is not consistent with saveP1(),saveP2(),saveP3().
    void saveP5(std::string &newPath);

/// Save an image with format **P6**
///@note it is not consistent with saveP1(),saveP2(),saveP3().

    void saveP6(std::string &newPath);

/// Turns an image with format **P1** negative.
    void negativeP1();

/// Turns an image with format **P2** negative.
    void negativeP2();

/// Turns an image with format **P3** negative.
    void negativeP3();
/// Turns an image with format **P2** negative.

    void monochromeP2();
/// Turns an image with format **P3** negative.

    void monochromeP3();

/// a method made for debugging purposes.
    void print() const;

public:
/// Loads image info from the path that was given.
/// @note This function could be made to work more efficiently.
    void loadImg();

/// Resets the currentImg to the originalImg and it's with and height.
    void resetCurrentImage();

public:
/// Turns the currentImg pixel values to gray values.
    void grayscale();

/// Turns the currentImg pixel values to black/white values.
    void monochrome();

/// Turns the currentImg pixel values to inverse values.
    void negative();

/// Rotates the currentImg to the right and also swaps currentWidth and currentHeight.
    void rotateRight();

/// Rotates the currentImg to the left and also swaps currentWidth and currentHeight.
    void rotateLeft();

/// Flips the matrix on its y axis.
    void flipVertical();

/// Flips the matrix on its x axis.
    void flipHorizontal();

// TODO
/// Crops the image to a new size.
/// @attention This method **DOESN'T** work!
    void crop(int xBeg, int yBeg, int xEnd, int yEnd);

/// Saves the image depending on what format it is.
    void save();

};


#endif //OOP_PROJECT_IMAGE_HPP
