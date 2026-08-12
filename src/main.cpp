#include "kelly_sim.hpp"
#include <iostream>
#include <iomanip>

int main() {
    // Configure a typical quantitative edge profile
    kelly::SimParameters params{
        0.53,    // 53% win rate
        1.0,     // 1:1 Risk-Reward ratio
        10000.0, // Starting capital
        0.5,     // Half-Kelly execution (safer, handles estimation error)
        500,     // 500 trading horizons
        1000     // 1000 parallel universe trajectories
    };

    kelly::Simulator sim(params);
    double target_f = sim.calculate_optimal_f();
    
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "============= JANE STREET FTTP KELLY SIMULATOR =============\n";
    std::cout << "Target Allocation Fraction (f*): " << (target_f * 100.0) << "%\n";

    kelly::SimResults results = sim.run();

    std::cout << "Expected Log Growth Rate:        " << results.expected_log_growth << "\n";
    std::cout << "Initial Portfolio Value:         $" << params.initial_capital << "\n";
    std::cout << "Median Ending Portfolio Value:   $" << results.median_path.back() << "\n";
    std::cout << "============================================================\n";

    return 0;
}
