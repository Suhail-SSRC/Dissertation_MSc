#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

std::vector<std::string> readFileToHex(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    std::vector<unsigned char> buffer(size);
    if (file.read((char*)buffer.data(), size)) {
        std::vector<std::string> hexes;
        for (int i = 0; i < size; ++i) {
            std::stringstream ss;
            ss << std::hex << (int)buffer[i];
            hexes.push_back(ss.str());
            
            if (i % 1000 == 0) {  // Update progress bar every 1000 bytes
                std::cout << "\rReading and converting to hex: " << std::fixed << std::setprecision(2) << (100.0 * i / size) << "%";
                std::cout.flush();
            }
        }
        std::cout << "\rReading and converting to hex: 100%\n";
        
        file.close();
        return hexes;
    } else {
        throw std::runtime_error("Error reading the file");
    }
}

// Function to get the size of the vector
size_t getVectorSize(const std::vector<std::string>& vec) {
    return vec.size();
}

int main() {
    std::string filename = "SEcomplete.pdf"; // Replace this with the path to your file
    std::vector<std::string> hexArr = readFileToHex(filename);

    // Output the hexadecimal representation of the file to a text file
    std::ofstream outputFile("SE_array.txt");
    for (const auto& hex : hexArr) {
        outputFile << hex << " ";
    }

    // Get and print the size of the vector
    size_t size = getVectorSize(hexArr);
    std::cout << "Size of the vector is: " << size << std::endl;

    outputFile.close();
    return 0;
}
