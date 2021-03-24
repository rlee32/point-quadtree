#include "nano_timer.hh"
#include "config.hh"
#include "fileio.hh"

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

    /*
    std::cout << "\nquadtree stats:\n";
    const auto &segments = make_segments(x, y, initial_tour);
    auto quadtree = segment_quadtree::SegmentQuadtree(segments);
    std::cout << "Finished quadtree in " << timer.stop() / 1e9 << " seconds.\n\n";

    quadtree.validate();

    int intersections{0};
    int i{0};
    for (const auto& segment : segments) {
        // segment in the set should not 'intersect'.
        if (quadtree.intersects(segment)) {
            ++intersections;
        }
        std::cout << i << std::endl;
        ++i;
    }
    std::cout << "Found " << intersections << " segments that intersect with others of " << segments.size() << " total." << std::endl;
    */

    return EXIT_SUCCESS;
}
