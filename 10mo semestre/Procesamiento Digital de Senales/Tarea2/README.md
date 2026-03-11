⚡ DSP: Discrete Fourier Series (Assignment 2)

Collaborators: Angel Pozos & Andrés Silverio
Semester: 2026-2 | Field: Digital Signal Processing

🎯 Project Mission

The objective of this assignment was to implement the Discrete Fourier Series (DFS) for periodic discrete-time signals from scratch. We focused on the mathematical computation of frequency-domain coefficients and signal reconstruction without relying on high-level Fast Fourier Transform (FFT) libraries to truly understand the core mechanics of frequency analysis.

🛠️ Technical Highlights

🔹 Low-Level Logic (The "No-FFT" Rule)

To ensure a deep mathematical understanding of the Fourier series, we strictly avoided using built-in functions like `np.fft.fft`. Instead, we developed:
* **Manual DFS Analysis:** Computing Fourier coefficients $X[k]$ manually using direct inner products and complex exponentials via `np.sum` and `np.dot`.
* **Signal Synthesis (Inverse DFS):** Reconstructing the time-domain signal $\hat{x}[n]$ entirely from its calculated frequency components.
* **Error Evaluation:** Calculating the Root-Mean-Square Error (RMSE) to mathematically quantify the precision of our manual reconstruction against the original signals.

🔹 Theoretical Verification

We generated and analyzed three different periodic discrete signals (Square, Triangle, and Sum of Sinusoids) over a single period, verifying:
* **Magnitude & Phase Spectra:** Plotting $|X[k]|$ and $\angle X[k]$ to visualize dominant frequencies and structural phase shifts.
* **Coefficient Truncation:** Observing how retaining only the $M$ largest coefficients affects the physical shape and sharpness of the reconstructed signal.

📊 Key Results Captured

* **Signal B (Triangle Wave, N=48):** Demonstrated that keeping only the largest coefficients maintains the general shape with extremely low error, though slight sharpness is lost at the peaks.
* **Signal C (Sum of Sinusoids, N=64):** Successfully isolated the 3 dominant magnitude coefficients ($k=1, 2, 3$) and their symmetric counterparts, mapping perfectly to the original frequencies.
* **High-Precision Reconstruction:** Achieved a near-perfect signal synthesis with an RMSE of $\approx 7.34 \times 10^{-15}$ for the sinusoidal sum.

⚙️ Tech Stack

* **Kernel:** Python 3.10+
* **Environment:** Jupyter Notebook / Google Colab
* **Dependencies:** NumPy & Matplotlib

📖 How to Run

1.  Clone the repository and open the `PozosSilverio_Tarea2.ipynb` file. *(Note: This repository is self-contained; only the `.ipynb` file is required).*
2.  Run all cells sequentially.
3.  Analyze the generated stem plots for the magnitude/phase spectra and the overlay comparisons between the original and reconstructed signals.
