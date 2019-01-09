#include <chrono>
#include <iostream>
#include <thread>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/config.hpp>
#include <boost/program_options/environment_iterator.hpp>
#include <boost/program_options/eof_iterator.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/version.hpp>

#include "gameoflife.h"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    po::options_description desc("This is 'Conway's Game of Life'.\n"
                                 "It follows the rules:\n"
                                 "1. Any live cell with fewer than two live neighbors dies, \n   as if by underpopulation.\n"
                                 "2. Any live cell with two or three live neighbors lives on \n   to the next generation.\n"
                                 "3. Any live cell with more than three live neighbors dies, \n   as if by overpopulation.\n"
                                 "4. Any dead cell with exactly three live neighbors becomes \n   a live cell, as if by reproduction.\n\n"
                                 "The Pattern will be generated randomly\n\n"
                                 "Usage: gameoflife [options]\n\nOptions are");
    desc.add_options()("help", "Shows this help");

    desc.add_options()("columns", po::value<int>()->default_value(80), "Rows");
    desc.add_options()("rows", po::value<int>()->default_value(22), "Columns");
    desc.add_options()("density", po::value<double>()->default_value(0.5), "Random density of living cells");
    desc.add_options()("delay", po::value<int>()->default_value(200), "Delay between iterations");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") != 0u)
    {
        std::stringstream str;
        desc.print(str);
        std::cout << str.str();
        exit(1);
    }

    GameOfLife gameoflife(vm["columns"].as<int>(), vm["rows"].as<int>(), vm["density"].as<double>());
    gameoflife.Output();

    while (1)
    {
        gameoflife.Step();
        gameoflife.Output();
        std::this_thread::sleep_for(std::chrono::milliseconds(vm["delay"].as<int>()));
    }
    return 0;
}
