#include "nano_timer.hh"
#include "config.hh"
#include "fileio.hh"
#include "point_quadtree/point_quadtree.hh"
#include "point_quadtree/box_maker.hh"

#include <filesystem>
#include <iostream>
#include <optional>
#include <string>

int main(int argc, const char** argv)
{
    if (argc == 1) {
        std::cout << "Arguments: config_file_path" << std::endl;
    }

    // Read config file.
    const std::string config_path = (argc == 1) ? "config.txt" : argv[1];
    std::cout << "Reading config file: " << config_path << std::endl;
    Config config(config_path);

    // Read input files.
    const std::optional<std::string> tsp_file_path_string = config.get("tsp_file_path");
    if (not tsp_file_path_string) {
        std::cout << "tsp_file_path not specified.\n";
        return EXIT_FAILURE;
    }
    const std::optional<std::filesystem::path> tsp_file_path(*tsp_file_path_string);
    const auto [x, y] = fileio::read_coordinates(*tsp_file_path_string);
    const auto initial_tour = fileio::initial_tour(x.size(), config.get("tour_file_path"));

    // Make quad tree.
    NanoTimer timer;
    timer.start();

    // Initial tour length calculation.
    point_quadtree::Domain domain(x, y);
    std::cout << "domain aspect ratio: " << domain.xdim(0) / domain.ydim(0) << std::endl;
    std::cout << "bounding x, y dim: "
        << domain.xdim(0) << ", " << domain.ydim(0)
        << std::endl;

    std::cout << "\nquadtree stats:\n";
    const auto root{point_quadtree::make_quadtree(x, y, domain)};
    std::cout << "node ratio: "
        << static_cast<double>(point_quadtree::count_nodes(root))
            / point_quadtree::count_points(root)
        << std::endl;
    std::cout << "Finished quadtree in " << timer.stop() / 1e9 << " seconds.\n\n";

    point_quadtree::validate(root);

    point_quadtree::BoxMaker box_maker(x, y);
    for (int i{0}; i < int(x.size()); ++i) {
        constexpr double RADIUS{10};
        std::cout << i << ", " << root.get_points(i, box_maker(i, RADIUS)).size() << std::endl;
    }

    return EXIT_SUCCESS;
}
