#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

namespace py = pybind11;

py::array load_image(const std::string &filename) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    if (!data) throw std::runtime_error("Failed to load image");

    py::capsule free_when_done(data, [](void *f) { stbi_image_free(f); });

    return py::array(
        py::buffer_info(
            data,
            sizeof(unsigned char),
            py::format_descriptor<unsigned char>::format(),
            3,
            {height, width, channels},
            {sizeof(unsigned char) * width * channels,
             sizeof(unsigned char) * channels,
             sizeof(unsigned char)}
        ),
        free_when_done
    );
}

bool save_png(const std::string &filename, py::array img) {
    py::buffer_info info = img.request();
    if (info.ndim != 3)
        throw std::runtime_error("Expected 3D array (H x W x C)");

    int height = info.shape[0];
    int width  = info.shape[1];
    int channels = info.shape[2];

    return stbi_write_png(filename.c_str(), width, height, channels,
                          info.ptr, width * channels) != 0;
}

bool save_jpg(const std::string &filename, py::array img, int quality = 90) {
    py::buffer_info info = img.request();
    if (info.ndim != 3)
        throw std::runtime_error("Expected 3D array (H x W x C)");

    int height = info.shape[0];
    int width  = info.shape[1];
    int channels = info.shape[2];

    return stbi_write_jpg(filename.c_str(), width, height, channels,
                          info.ptr, quality) != 0;
}

PYBIND11_MODULE(stb_image_wrapper, m) {
    m.doc() = "Python wrapper for stb_image and stb_image_write";
    m.def("load_image", &load_image, "Load an image into a NumPy array");
    m.def("save_png", &save_png, "Save NumPy array as PNG");
    m.def("save_jpg", &save_jpg, "Save NumPy array as JPEG",
          py::arg("filename"), py::arg("img"), py::arg("quality") = 90);
}
