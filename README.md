# Backtester

A console app for backtesting trading strategies. Provides menu-driven configuration and summary report

## Overview

Backtests selected strategy based on selected dataset. Upon finishing prints summary (strategy and data file name, win rate, balance, realized PnL etc.). Initial default configuration can be changed in menu

## Strategies

### Simple Moving Average (SMA)

Based on a 14-period simple moving average
Buy signal: price closes above the SMA
Sell signal: price closes below the SMA
Risk-managed mode is disabled

### Engulfing Candle

Looks for strong moves in one direction followed by an engulfing candle in the opposite direction
Buy signal: bullish engulfing candle
Sell signal: bearish engulfing candle
Risk-managed mode is enabled

## Data Files and Directory

CSV data file (OHLC dataset) should have the following format
Date,Open,High,Low,Close

If the CLI data path is empty or invalid ./data is tried, then ../data

## Requirements

* CMake >= 3.15
* C++17 compiler
* Terminal supporting ANSI escape codes

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/backtester [<path/to/data-dir>]
```

## Project Structure

* src/ implementation files
* include/ headers
* data/ sample datasets
* CMakeLists.txt build config

## Notes

* Initial wallet balance is 10000.0
* Risk per trade is 1% of total balance for risk-managed strategies
* Default risk:reward ratio is set to 1:2 for risk-managed strategies (implemented as kDefaultRiskReward = 0.5)
* Strategy with disabled risk management opens a position every time with full balance according to received buy/sell signal and closes the previous one in opposite direction
