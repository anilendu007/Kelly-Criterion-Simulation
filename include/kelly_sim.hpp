#pragma once
#include <vector>

namespace kelly {

struct SimParameters {
    double p_win;           // Probability of winning (0.0 to 1.0)
    double payout_ratio;    // Odds payout ratio (b)
    double initial_capital; // Starting bankroll
    double kelly_fraction;  // Risk adjustment multiplier (e.g., 0.5 for Half-Kelly)
    size_t num_trades;      // Horizon steps per path
    size_t num_paths;       // Total Monte Carlo trajectories
};

struct SimResults {
    std::vector<std::vector<double>> all_paths;
    std::vector<double> median_path;
    double expected_log_growth;
};

// Core simulator class using modern RAII and clean encapsulation
class Simulator {
public:
    explicit Simulator(const SimParameters& params);
    
    [[nodiscard]] SimResults run() const;
    [[nodiscard]] double calculate_optimal_f() const;

private:
    SimParameters params_;
};

} // namespace kelly
