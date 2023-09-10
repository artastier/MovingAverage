# Moving Average Filters

This repository regroups 5 moving average filters (Tripe Exponential Smoothing is coming).
These filters have been designed to perform an online smoothing of real-time data (Ex: Data from a sensor).
All the following equations have been extracted from [Moving Average](https://en.wikipedia.org/wiki/Moving_average).
## Basic Moving Average
### Inputs
* Sampling frequency (Hz)
* Duration over which averaging is to be performed (s)

From these two parameters, we can determine the number of points on which we can apply smoothing.

### Computation
#### Cumulative moving average
Until reaching the subset size wanted, we perform a cumulative moving average using the following recursive
relationship between the current and the previous mean:

$m_{n} = \frac{1}{n+1}.(n.m_{n-1} + x_{n})$, where $x_{n}$ represents the discrete signal to treat.

## Simple Moving Median
## Simple Exponential Smoothing
## Double Exponential Smoothing
## User Interface