# ⚡ DSP: Discrete-Time Operations (Assignment 1)

**Collaborators:** Angel Pozos & Andrés Silverio  
**Semester:** 2026-2 | **Field:** Digital Signal Processing

---

### 🎯 Project Mission
The objective of this assignment was to transition from theoretical paper-based analysis to digital signal manipulation. We focused on the algorithmic implementation of fundamental discrete operations without relying on high-level libraries for the core logic.

---

### 🛠️ Technical Highlights

#### 🔹 Low-Level Logic (The "No-Shortcuts" Rule)
To ensure a deep understanding of DSP, we avoided using built-in functions like `np.convolve` or `np.correlate`. Instead, we developed:
* **Custom Correlation:** Manual nested loops to compute Autocorrelation and Cross-correlation.
* **Signal Synthesis:** Mathematical generation of $\delta[n]$, $u[n]$, and $r[n]$.
* **Manual Shifting:** Implementing $x[n-k]$ and $x[-n]$ through index manipulation.

#### 🔹 Theoretical Verification
We solved and then digitally verified several key concepts:
* **Energy vs. Power:** Classification of signals based on $E_x$ and $P_x$ convergence.
* **The Nyquist Challenge:** Analysis of the **Aliasing effect** when $f_s < 2f_{max}$ through computational plotting.
* **Signal Stats:** Calculation of Mean, Energy, and RMS values.

---

### 📊 Key Results Captured
* **Fundamental Period ($N$):** Verified for sinusoidal sequences (e.g., $N=12$).
* **Energy Analysis:** Computed $E_x \approx 5.263$ for decaying exponential signals.
* **Symmetry:** Proved that the autocorrelation of a symmetric signal remains symmetric.

---

### ⚙️ Tech Stack
* **Kernel:** Python 3.10+
* **Environment:** Jupyter Notebook / Google Colab
* **Dependencies:** `NumPy` & `Matplotlib`

---

### 📖 How to Run
1. Ensure you have the `.ipynb` and the `.pdf` (theory) in the same directory.
2. Open the notebook and run all cells.
3. Compare the generated graphs with the theoretical results provided in the PDF.
