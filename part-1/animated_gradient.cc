// Marcus McKinstry
// marcmckinstry@csu.fullerton.edu
// @heyyyitsmarcus
// Partners: @pachmi

#include <Magick++.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "animated_gradient_functions.h"

// The width of the image is the number of columns.
const int kImageWidth{512};
// The height of the image is the number of rows.
const int kImageHeight{512};
// The number of images in our flipbook animation.
const int kNumberOfImages = 10;

int main(int argc, char* argv[]) {
  // Initialize the GraphicsMagick library. It must be the first thing
  // that happens in the main function.
  // Do not change or remove the line below.
  Magick::InitializeMagick(*argv);
  // X: convert the command line arguments to a
  // std::vector of std::strings.
  std::vector<std::string> arguments(argv, argv + argc);
  // X: Check to make sure you have enough arguments. If you have
  // too few, print an error message and exit.
  if (arguments.size() < 2) {
    std::cout << "Please provide a path to a file"
              << "\n";
    return 1;
  }
  // X: Declare a std::string variable named output_file_name.
  std::string output_file_name;
  // X: Assign the first argument to output_file_name
  output_file_name = arguments.at(1);
  // X: Declare a std::string variable named image_format and
  // initialize it to ".gif"
  std::string image_format{".gif"};
  // X: Using HasMatchingFileExtension(), check to see if
  // output_file_name has the extension defined as image_format. If
  // output_file_name does not, then print an error message and return 1.
  if (!(HasMatchingFileExtension(output_file_name, image_format))) {
    std::cout << output_file_name
              << " is missing the required file extension .gif."
              << "\n";
    return 1;
  }
  // Lookup Table
  // X: Declare a std::vector of doubles, name the variable
  // sine_lookup_table.
  std::vector<double> sine_lookup_table;
  // X: call BuildSineLookupTable() with kImageWidth, assign the return value
  // to sine_lookup_table
  sine_lookup_table = BuildSineLookupTable(kImageWidth);
  // X: Declare a Magick::ColorRGB variable named white and set it's
  // color to white which means setting each color channel to 1.
  // For example:
  Magick::ColorRGB white(1, 1, 1);
  // Magick::ColorRGB white(1, 1, 1);

  // X: Declare a std::vector of Magick::Image, name the variable images.
  std::vector<Magick::Image> images;
  // X: Declare a double variable named blue_step. Intialize it to M_PI
  // divided by kNumberOfImages. Remember to convert kNumberOfImages to a double
  // to avoid integer division.
  double blue_step{M_PI / static_cast<double>(kNumberOfImages)};
  // X: Declare an int variable named row_col_step and initialize it to
  // kImageWidth / kNumberOfImages.
  int row_col_step = kImageWidth / kNumberOfImages;

  for (int current_image = 0; current_image < kNumberOfImages;
       current_image++) {
    // X: Declare a Magick::Image variable named image. Initialize it to be
    // kImageWidth by kImageHeight and fill it with white. See Lab 10 for an
    // example.
    Magick::Image image(Magick::Geometry(kImageWidth, kImageHeight), white);
    std::cerr << "Image " << current_image + 1 << "...";
    // Initialize the current image
    // Calculate the blue color for the given image
    // X: Declare a double named blue and assign it the blue value needed for
    // the current image. This value is the sine of blue_step * current_image
    double blue = sin(blue_step * current_image);
    for (int column = 0; column < image.columns(); column++) {
      for (int row = 0; row < image.rows(); row++) {
        int current_step = (current_image * row_col_step);
        double red = sine_lookup_table.at((row + current_step) % kImageWidth);
        double green =
            sine_lookup_table.at((column + current_step) % kImageHeight);
        Magick::ColorRGB color{red, green, blue};
        image.pixelColor(column, row, color);
      }
    }
    images.push_back(image);
    std::cerr << "completed.\n";
  }
  // X: Write the images to an output file using Magick::writeImages()
  // For example:
  // Magick::writeImages(images.begin(), images.end(), output_file_name);
  Magick::writeImages(images.begin(), images.end(), output_file_name);

  return 0;
}
