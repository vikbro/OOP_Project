
#ifndef OOP_PROJECT_PIXEL_HPP
#define OOP_PROJECT_PIXEL_HPP
/// A structure that stores pixel values
///
/// Even though all the elements are public they are private in the Image class
struct Pixel {
public:
    bool val0; ///< Stores the binary value of a Binary Pixel
    int val1; ///< Stores the **Red** value of pixel and **Gray** value
              ///< @note This member has a double purpose
    int val2; ///< Stores **Green** value of pixel
    int val3; ///< Stores **Blue** value of pixel

    Pixel() {
        int val1 = -1;
    }
/// A constructor that is used if the image is binary (*.pbm*)
    Pixel(bool val) {
        this->val0 = val;

        this->val1 = 0;
        this->val2 = 0;
        this->val3 = 0;
    }
/// A constructor that is used if the image is gray (*.pgm*)
    Pixel(int val){
        this->val0 = false;

        this->val1 = val;
        this->val2 = 0;
        this->val3 = 0;
    }
/// A constructor that is used if the image is RGB (*.ppm*)
    Pixel(int val1, int val2, int val3) {
        this->val0 = false;

        this->val1 = val1;
        this->val2 = val2;
        this->val3 = val3;
    }
};

#endif //OOP_PROJECT_PIXEL_HPP
