#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "stb_image_write.h"
#include "stb_image.h"

void exeToPng(const std::string &exePath, const std::string &pngPath) {
    std::ifstream exeFile(exePath, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(exeFile), {});
    exeFile.close();

    size_t dataSize = buffer.size();
    size_t imageSize = static_cast<size_t>(std::sqrt(dataSize)) + 1;

    std::vector<unsigned char> image(imageSize * imageSize * 3, 0);
    for (size_t i = 0; i < dataSize; ++i) {
        image[i * 3] = buffer[i];
    }

    stbi_write_png(pngPath.c_str(), imageSize, imageSize, 3, image.data(), imageSize * 3);
}

void pngToExe(const std::string &pngPath, const std::string &exePath) {
    int width, height, channels;
    unsigned char *image = stbi_load(pngPath.c_str(), &width, &height, &channels, 3);
    if (!image) {
        std::cerr << "Failed to load PNG file" << std::endl;
        return;
    }

    size_t dataSize = width * height;
    std::vector<unsigned char> buffer(dataSize, 0);
    for (size_t i = 0; i < dataSize; ++i) {
        buffer[i] = image[i * 3];
    }

    std::ofstream exeFile(exePath, std::ios::binary);
    exeFile.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    exeFile.close();

    stbi_image_free(image);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <mode> <input> <output>\n";
        std::cerr << "Modes: \n";
        std::cerr << "  to_png   - Convert .exe to .png\n";
        std::cerr << "  to_exe   - Convert .png to .exe\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string inputPath = argv[2];
    std::string outputPath = argv[3];

    if (mode == "to_png") {
        exeToPng(inputPath, outputPath);
    } else if (mode == "to_exe") {
        pngToExe(inputPath, outputPath);
    } else {
        std::cerr << "Unknown mode: " << mode << std::endl;
        return 1;
    }

    return 0;
}
