#include <iostream>
#include "hpp/Controller.hpp"

int main() {
//        ../Images/image.pbm
//    ../Images/image2.pgm
//    ../Images/amogus_txt.ppm
//    > load ../Images/corrupt/corrupt-comment-eof.pbm
//    > load ../Images/corrupt/corrupt-comment-eof.pbm
//    > load ../Images/magic_man_txt.ppm ../Images/magic_man_txt.pgm
//    > load ../Images/magic_man_txt.ppm ../Images/magic_man_txt.pgm ../Images/magic_man_raw.ppm
//    > load ../Images/magic_man_txt.pgm

    Controller ctr;
    do {
        try {
            std::cin >> ctr;
            std::cout << "--------------" << std::endl;
        } catch (const std::exception &ex) {
            std::cout << "ERROR MSG ========" << std::endl;
            std::cerr << ex.what() << std::endl;
            std::cout << "==================" << std::endl;
        }
    } while (!ctr.getStopFlag());

    return 0;
}
