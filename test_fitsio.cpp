#include <vector>
#include <chrono>

#include <fmt/format.h>
#include <fitsio.h>

int f_vector_based_read(char* filename);
int f_carray_based_read(char* filename);

int main(int argc, char** argv) {
    if (argc < 2) {
        fmt::print("Usage: {} <filename>\n", argv[0]);
        return 1;
    }
    fmt::print("Running vector based example first...");
    f_vector_based_read(argv[1]);
    fmt::print("Running carray based example second...");
    f_carray_based_read(argv[1]);
}

int f_vector_based_read(char* filename) {
    int status = 0;
    fitsfile* fptr;
    int dims = 2;
    std::vector<int64_t> imageSize(dims);
    std::vector<float> data_vector;
    data_vector.reserve(1024 * 1024 * 1024);
    std::vector<int64_t> startPix = {{1, 1}};

    // Open image and get data size. File is assumed to be 2D
    fits_open_file(&fptr, filename, READONLY, &status);
    fits_get_img_sizell(fptr, dims, imageSize.data(), &status);
    auto num_pixels = imageSize[0] * imageSize[1];

    // Frame::FillImageCache timing is just the memory allocation and reading part
    auto t_start = std::chrono::high_resolution_clock::now();
    // To get an idea of how much faster the reading process could be without the cost of initialising std::vector to zero,
    // change this to "reserve" (for testing only...technically undefined behaviour!)
    data_vector.resize(num_pixels);
    fits_read_pixll(fptr, TFLOAT, startPix.data(), num_pixels, nullptr, data_vector.data(), nullptr, &status);
    auto t_end = std::chrono::high_resolution_clock::now();
    
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
    auto rate = num_pixels / (double) dt;
    fmt::print("{:.1f} MB file read in {:.1f} ms at {:.1f} MPix/s\n", num_pixels * sizeof(float) * 1.0e-6, dt * 1.0e-3, rate);

    fits_close_file(fptr, &status);
    return status;
}

int f_carray_based_read(char* filename) {
    int status = 0;
    fitsfile* fptr;
    int dims = 2;
    int64_t imageSize[dims];
    float* data_carray;
    // std::vector<float> data_vector;
    int64_t startPix[2] = {1, 1};

    // Open image and get data size. File is assumed to be 2D
    fits_open_file(&fptr, filename, READONLY, &status);
    fits_get_img_sizell(fptr, dims, imageSize, &status);
    auto num_pixels = imageSize[0] * imageSize[1];

    // Frame::FillImageCache timing is just the memory allocation and reading part
    auto t_start = std::chrono::high_resolution_clock::now();
    // To get an idea of how much faster the reading process could be without the cost of initialising std::vector to zero,
    // change this to "reserve" (for testing only...technically undefined behaviour!)
    data_carray = new float[num_pixels];
    fits_read_pixll(fptr, TFLOAT, startPix, num_pixels, nullptr, data_carray, nullptr, &status);
    auto t_end = std::chrono::high_resolution_clock::now();
    
    auto dt = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
    auto rate = num_pixels / (double) dt;
    fmt::print("{:.1f} MB file read in {:.1f} ms at {:.1f} MPix/s\n", num_pixels * sizeof(float) * 1.0e-6, dt * 1.0e-3, rate);

    fits_close_file(fptr, &status);
    
    delete[] data_carray;
    return status;
}