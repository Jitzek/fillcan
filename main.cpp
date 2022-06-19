#include "apps/compute_pipeline/app.hpp"
#include "apps/simple_triangle/app.hpp"
#include "apps/simple_cube/app.hpp"
#include "apps/simple_texture/app.hpp"
#include "apps/simple_model/app.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    // app::App app{};
    // compute_pipeline::App app{};
    // simple_triangle::App app{};
    // simple_cube::App app{};
    simple_texture::App app{};
    // simple_model::App app{};

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}