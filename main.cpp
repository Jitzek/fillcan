#include "apps/compute_pipeline_test/app.hpp"
#include "apps/simple_triangle/app.hpp"
#include "apps/simple_cube/app.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    // app::App app{};
    // app_compute_pipeline_test::App app{};
    // simple_triangle::App app{};
    simple_cube::App app{};

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}