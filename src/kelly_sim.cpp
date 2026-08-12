#include "kelly_sim.hpp"
#include <algorithm>
#include <random>
#include <cmath>

namespace kelly {

Simulator::Simulator(const SimParameters& params) : params_(params) {}

double Simulator::calculate_optimal_f() const {
    // Kelly Formula: f* = (p * b - q) / b
    double q = 1.0 - params_.p_win;
    double edge = (params_.p_win * params_.payout_ratio) - q;
    double raw_f = edge / params_.payout_ratio;
    
    // Bounds check: Do not bet if edge is negative, clamp to zero
    return std::max(0.0, raw_f * params_.kelly_fraction);
}

SimResults Simulator::run() const {
    SimResults results;
    results.all_paths.reserve(params_.num_paths);
    
    double f = calculate_optimal_f();
    
    // Thread-safe random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(params_.p_win);

    // Theoretical expected log growth rate per trial
    double q = 1.0 - params_.p_win;
    results.expected_log_growth = params_.p_win * std::log(1.0 + f * params_.payout_ratio) + 
                                  q * std::log(1.0 - f);

    for (size_t i = 0; i < params_.num_paths; ++i) {
        std::vector<double> path;
        path.reserve(params_.num_trades + 1);
        
        double current_capital = params_.initial_capital;
        path.push_back(current_capital);

        for (size_t t = 0; t < params_.num_trades; ++t) {
            if (current_capital <= 1e-6) { // Handle bankruptcy margin
                current_capital = 0.0;
                path.push_back(0.0);
                continue;
            }

            bool win = dist(gen);
            if (win) {
                current_capital += current_capital * f * params_.payout_ratio;
            } else {
                current_capital -= current_capital * f;
            }
            path.push_back(current_capital);
        }
        results.all_paths.push_back(std::move(path));
    }

    // Calculate Median Path across all trajectories for each time step
    results.median_path.resize(params_.num_trades + 1);
    for (size_t t = 0; t <= params_.num_trades; ++t) {
        std::vector<double> step_values;
        step_values.reserve(params_.num_paths);
        
        for (size_t i = 0; i < params_.num_paths; ++i) {
            step_values.push_back(results.all_paths[i][t]);
        }
        
        size_t median_idx = params_.num_paths / 2;
        std::nth_element(step_values.begin(), step_values.begin() + median_idx, step_values.end());
        results.median_path[t] = step_values[median_idx];
    }

    return results;
}

} // namespace kelly
