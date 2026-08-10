# Kelly Criterion Portfolio Simulation Engine

A multi-language quantitative simulation module exploring risk mitigation, expected value calculations, and continuous log-utility asset growth pathways. 

## Structure
* `kelly_engine.py`: High-level mathematical prototype used for rapid simulation vector verification.
* `kelly_engine.cpp`: Optimized, low-latency execution layout translating the statistical models into native high-performance code.

## Mathematical Formulation

The optimal investment or betting fraction is computed dynamically via:

$f^* = (bp - q) / b$

Where:
* $p$ = Analytical win probability
* $q$ = Analytical loss probability ($1 - p$)
* $b$ = Payout odds ratio


