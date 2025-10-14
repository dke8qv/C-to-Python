# C-to-Python

Various examples and short exercises on bridging Python and compiled code

# Estimating π using NumPy

I estimated π by Monte Carlo sampling of 100 million random points inside the unit square. Points within the unit circle (x² + y² < 1) are counted to estimate π as:

π ≈ 4 × (points inside circle) / (total points)

### Results

| Implementation | Time (s) | π Estimate | Speedup |
|----------------|-----------|-------------|----------|
| Pure Python    | 11.6      | 3.14146184     | 1×       |
| C via ctypes   | 1.09      | 3.14147804     | ~10×     |
| NumPy          | 2.2       | 3.14171724     | ~5×     |

### Speed-Up Strategy

- Used **NumPy vectorization** to avoid Python loops.
- Performed all math operations (`x**2 + y**2 < 1`) in **compiled C** via NumPy’s backend.
- Generated random numbers in **bulk**, reducing interpreter overhead.

### Conclusion

The NumPy implementation demonstrates that Python can speed up performance when vectorized operations replace explicit loops. 

  
