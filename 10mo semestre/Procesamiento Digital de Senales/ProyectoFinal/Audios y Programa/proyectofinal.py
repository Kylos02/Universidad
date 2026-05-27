import os
import numpy as np
import matplotlib
matplotlib.use('Agg') 
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy import signal as sig

# --- Configuración global ---
FS = 16000
DURACION_VOZ = 3.0
DIR_RUIDOS = "D:\\Documentos\\Ing en compu\\SEMESTRE 2026-2\\ProcesamientoDigitalSeñales\\ruidos"
DIR_SALIDA = "salida"
DIR_FIGS = os.path.join(DIR_SALIDA, "figs")
 
SNR_CASO_A_DB = 10.0
SNR_CASO_B_DB = 0.0
 
FC_PB = 3400.0
ANCHO_TRANSICION = 500.0
VENTANA_FIR = "hamming"
 
F_NOTCH = 60.0
Q_NOTCH = 30.0
 
# --- Estilo Matplotlib (Reporte IEEE) ---
plt.rcParams.update({
    "font.family": "serif",
    "font.size": 9,
    "axes.labelsize": 9,
    "axes.titlesize": 10,
    "xtick.labelsize": 8,
    "ytick.labelsize": 8,
    "legend.fontsize": 8,
    "lines.linewidth": 1.0,
    "figure.figsize": (3.5, 2.5),
    "savefig.dpi": 300,
    "savefig.bbox": "tight",
    "savefig.pad_inches": 0.02,
})
 
# --- 1. Síntesis de voz (Fuente-Filtro) ---
def generar_voz_sintetica(fs=FS, duracion=DURACION_VOZ, semilla=42):
    rng = np.random.default_rng(semilla)
    N = int(fs * duracion)
    t = np.arange(N) / fs
 
    F0 = 120.0
    vibrato = 3.0 * np.sin(2 * np.pi * 5 * t)
    F0_t = F0 + vibrato
    fase = 2 * np.pi * np.cumsum(F0_t) / fs
 
    fase_mod = np.mod(fase, 2 * np.pi)
    impulsos = np.zeros(N)
    cruces = np.where(np.diff(fase_mod) < -np.pi)[0]
    impulsos[cruces] = 1.0
 
    envolvente = np.zeros(N)
    silabas = [(0.10, 0.85), (1.05, 1.80), (2.00, 2.75)]
    for ini, fin in silabas:
        n_ini = int(ini * fs)
        n_fin = min(int(fin * fs), N)
        if n_fin <= n_ini:
            continue
        rampa = np.ones(n_fin - n_ini)
        n_ramp = int(0.03 * fs)
        n_ramp = min(n_ramp, (n_fin - n_ini) // 2)
        rampa[:n_ramp] = np.linspace(0, 1, n_ramp)
        rampa[-n_ramp:] = np.linspace(1, 0, n_ramp)
        envolvente[n_ini:n_fin] = rampa
 
    fuente = impulsos * envolvente
 
    formantes = {
        "a": [(700, 90),  (1100, 110), (2500, 170)],
        "i": [(300, 70),  (2300, 100), (3000, 150)],
        "u": [(350, 60),  (800,  90),  (2400, 150)],
    }
    vocales_por_silaba = ["a", "i", "u"]
 
    voz = np.zeros(N)
    for k, (ini, fin) in enumerate(silabas):
        n_ini = int(ini * fs)
        n_fin = min(int(fin * fs), N)
        if n_fin <= n_ini:
            continue
        seg = fuente[n_ini:n_fin].copy()
        v = vocales_por_silaba[k % len(vocales_por_silaba)]
        for f_c, ancho in formantes[v]:
            r = np.exp(-np.pi * ancho / fs)
            theta = 2 * np.pi * f_c / fs
            b = [1 - r]
            a = [1, -2 * r * np.cos(theta), r * r]
            seg = sig.lfilter(b, a, seg)
        voz[n_ini:n_fin] = seg
 
    # Modelo de decaimiento glotal
    a_glotal = [1.0, -0.94]
    voz = sig.lfilter([1.0], a_glotal, voz)
 
    voz = voz + 0.001 * rng.standard_normal(N)
    voz = voz / np.max(np.abs(voz)) * 0.7
    return voz.astype(np.float32), fs
 
# --- 2. Utilidades de I/O ---
def cargar_voz(ruta=None, fs_objetivo=FS):
    if ruta is not None and os.path.exists(ruta):
        fs, x = wavfile.read(ruta)
        dtype_original = x.dtype
        x = x.astype(float)
        if x.ndim > 1:
            x = x.mean(axis=1)
        if np.issubdtype(dtype_original, np.integer):
            x = x / np.max(np.abs(x) + 1e-12)
        print(f"[voz] cargada de {ruta}: fs={fs}, N={len(x)}")
 
        if fs != fs_objetivo:
            print(f"[voz] resampleando {fs} Hz -> {fs_objetivo} Hz ...")
            from math import gcd
            g = gcd(fs_objetivo, fs)
            up = fs_objetivo // g
            down = fs // g
            x = sig.resample_poly(x, up, down)
            fs = fs_objetivo
            print(f"[voz] resampleada: fs={fs}, N={len(x)}")
 
        return x.astype(np.float32), fs
    else:
        print("[voz] generando voz sintetica de prueba...")
        return generar_voz_sintetica(fs=fs_objetivo)
 
def cargar_ruido(ruta, N_objetivo, fs_objetivo=FS):
    fs, r = wavfile.read(ruta)
    dtype_original = r.dtype
    r = r.astype(float)
    if r.ndim > 1:
        r = r.mean(axis=1)
    if np.issubdtype(dtype_original, np.integer):
        r = r / np.max(np.abs(r) + 1e-12)
 
    if fs != fs_objetivo:
        print(f"[ruido] resampleando {fs} Hz -> {fs_objetivo} Hz ...")
        from math import gcd
        g = gcd(fs_objetivo, fs)
        up = fs_objetivo // g
        down = fs // g
        r = sig.resample_poly(r, up, down)
        fs = fs_objetivo
 
    if len(r) >= N_objetivo:
        r = r[:N_objetivo]
    else:
        reps = int(np.ceil(N_objetivo / len(r)))
        r = np.tile(r, reps)[:N_objetivo]
    return r.astype(np.float32), fs
 
# --- 3. Construcción de señal ruidosa ---
def calcular_alpha_para_snr(x, r, snr_db):
    P_x = np.mean(x ** 2)
    P_r = np.mean(r ** 2)
    alpha = np.sqrt(P_x / (P_r * 10 ** (snr_db / 10.0)))
    return alpha
 
def crear_senal_ruidosa(x, r, snr_db):
    alpha = calcular_alpha_para_snr(x, r, snr_db)
    return x + alpha * r, alpha
 
# --- 4. Análisis espectral ---
def calcular_espectro(x, fs):
    X = np.fft.rfft(x)
    f = np.fft.rfftfreq(len(x), d=1 / fs)
    return f, np.abs(X)
 
def magnitud_db(mag, ref=None):
    if ref is None:
        ref = np.max(mag) + 1e-12
    return 20 * np.log10(mag / ref + 1e-12)
 
# --- 5. Diseño de filtros ---
def disenar_fir_pasa_bajas(fc, ancho_trans, fs, ventana="hamming"):
    M = int(np.ceil(3.3 * fs / ancho_trans))
    if M % 2 == 0:
        M += 1
    h = sig.firwin(M, cutoff=fc, window=ventana, fs=fs)
    return h, M
 
def aplicar_fir_fase_compensada(x, h):
    M = len(h)
    retardo = (M - 1) // 2
    y = sig.lfilter(h, [1.0], x)
    y = np.concatenate([y[retardo:], np.zeros(retardo)])
    return y
 
def disenar_notch_iir(f0, Q, fs):
    b, a = sig.iirnotch(w0=f0 / (fs / 2), Q=Q)
    return b, a
 
# --- 6. Métricas ---
def ecm(x, y):
    return float(np.mean((x - y) ** 2))
 
def snr_db(x_limpia, x_observada):
    P_s = np.mean(x_limpia ** 2)
    P_n = np.mean((x_observada - x_limpia) ** 2)
    return 10 * np.log10(P_s / (P_n + 1e-12))
 
# --- 7. Generación de gráficos ---
def fig_voz_tiempo(x, fs, ruta_salida):
    t = np.arange(len(x)) / fs
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(3.5, 3.5))
 
    ax1.plot(t, x, linewidth=0.5)
    ax1.set_xlabel("Tiempo [s]")
    ax1.set_ylabel("Amplitud")
    ax1.set_title("(a) Senal completa")
    ax1.grid(alpha=0.3)
    ax1.set_xlim(0, t[-1])
 
    # Zoom de 80 ms
    i0 = int(1.20 * fs)
    i1 = i0 + int(0.080 * fs)
    ax2.plot(t[i0:i1] * 1000, x[i0:i1], linewidth=0.8)
    ax2.set_xlabel("Tiempo [ms]")
    ax2.set_ylabel("Amplitud")
    ax2.set_title("(b) Acercamiento (80 ms)")
    ax2.grid(alpha=0.3)
 
    plt.tight_layout()
    plt.savefig(ruta_salida)
    plt.close()
 
def fig_comparacion_ruidosa(x, x_A, x_B, fs, ruta_salida):
    fig, axes = plt.subplots(3, 1, figsize=(3.5, 3.8), sharex=True)
    i0 = int(1.20 * fs)
    i1 = i0 + int(0.150 * fs)
    t_ms = (np.arange(i0, i1) - i0) / fs * 1000
 
    for ax, sig_, titulo in zip(
        axes,
        [x, x_A, x_B],
        ["Voz limpia", f"Caso A (SNR={SNR_CASO_A_DB:.0f} dB)",
         f"Caso B (SNR={SNR_CASO_B_DB:.0f} dB)"],
    ):
        ax.plot(t_ms, sig_[i0:i1], linewidth=0.7)
        ax.set_ylabel("Amplitud")
        ax.set_title(titulo, fontsize=8)
        ax.grid(alpha=0.3)
    axes[-1].set_xlabel("Tiempo [ms]")
    plt.tight_layout()
    plt.savefig(ruta_salida)
    plt.close()
 
def fig_espectros(x, x_B, fs, ruta_salida):
    f_x, mag_x = calcular_espectro(x, fs)
    f_b, mag_b = calcular_espectro(x_B, fs)
    ref = max(mag_x.max(), mag_b.max())
 
    fig, ax = plt.subplots(figsize=(3.5, 2.5))
    ax.plot(f_x, magnitud_db(mag_x, ref), label="Voz limpia", linewidth=0.7)
    ax.plot(f_b, magnitud_db(mag_b, ref), label="Ruidosa (Caso B)", linewidth=0.7, alpha=0.8)
    ax.axvline(FC_PB, color="k", linestyle="--", linewidth=0.8, label=f"$f_c$ = {FC_PB:.0f} Hz")
    ax.set_xlabel("Frecuencia [Hz]")
    ax.set_ylabel("Magnitud [dB]")
    ax.set_xlim(0, fs / 2)
    ax.set_ylim(-80, 5)
    ax.legend(loc="upper right")
    ax.grid(alpha=0.3)
    plt.tight_layout()
    plt.savefig(ruta_salida)
    plt.close()
 
def fig_respuesta_filtro(h, fs, ruta_salida):
    w, H = sig.freqz(h, worN=4096, fs=fs)
    fig, ax = plt.subplots(figsize=(3.5, 2.5))
    ax.plot(w, 20 * np.log10(np.abs(H) + 1e-12), linewidth=1.0)
    ax.axvline(FC_PB, color="r", linestyle="--", linewidth=0.8, label=f"$f_c$ = {FC_PB:.0f} Hz")
    ax.set_xlabel("Frecuencia [Hz]")
    ax.set_ylabel("$|H(e^{j\\omega})|$ [dB]")
    ax.set_xlim(0, fs / 2)
    ax.set_ylim(-100, 5)
    ax.legend()
    ax.grid(alpha=0.3)
    plt.tight_layout()
    plt.savefig(ruta_salida)
    plt.close()
 
def fig_filtrada(x, x_B, y_B, fs, ruta_salida):
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(3.5, 4.0))
 
    i0 = int(1.20 * fs)
    i1 = i0 + int(0.150 * fs)
    t_ms = (np.arange(i0, i1) - i0) / fs * 1000
    ax1.plot(t_ms, x_B[i0:i1], label="Ruidosa B", linewidth=0.6, alpha=0.7)
    ax1.plot(t_ms, y_B[i0:i1], label="Filtrada", linewidth=0.8)
    ax1.plot(t_ms, x[i0:i1], label="Limpia", linewidth=0.8, linestyle="--", alpha=0.8)
    ax1.set_xlabel("Tiempo [ms]")
    ax1.set_ylabel("Amplitud")
    ax1.set_title("(a) Comparacion temporal")
    ax1.legend(loc="upper right", fontsize=7)
    ax1.grid(alpha=0.3)
 
    f_b, mag_b = calcular_espectro(x_B, fs)
    f_y, mag_y = calcular_espectro(y_B, fs)
    ref = mag_b.max()
    ax2.plot(f_b, magnitud_db(mag_b, ref), label="Ruidosa B", linewidth=0.6, alpha=0.7)
    ax2.plot(f_y, magnitud_db(mag_y, ref), label="Filtrada", linewidth=0.8)
    ax2.set_xlabel("Frecuencia [Hz]")
    ax2.set_ylabel("Magnitud [dB]")
    ax2.set_xlim(0, fs / 2)
    ax2.set_ylim(-80, 5)
    ax2.set_title("(b) Espectros de magnitud")
    ax2.legend(loc="upper right", fontsize=7)
    ax2.grid(alpha=0.3)
 
    plt.tight_layout()
    plt.savefig(ruta_salida)
    plt.close()
 
# --- 8. Pipeline Principal ---
def main():
    os.makedirs(DIR_SALIDA, exist_ok=True)
    os.makedirs(DIR_FIGS, exist_ok=True)
 
    # Cargar/generar voz
    ruta_voz = os.path.join(DIR_SALIDA, "voz_original.wav")
    x, fs = cargar_voz(
        ruta=ruta_voz if os.path.exists(ruta_voz) else None,
        fs_objetivo=FS,
    )
    N = len(x)
    print(f"[voz] N={N}, fs={fs}, duracion={N/fs:.2f} s")
 
    if not os.path.exists(ruta_voz):
        wavfile.write(ruta_voz, fs, x)
        print(f"[voz] sintetica guardada en {ruta_voz}")
 
    # Cargar ruido blanco
    ruta_blanco = os.path.join(DIR_RUIDOS, "ruido_blanco.wav")
    r, fs_r = cargar_ruido(ruta_blanco, N_objetivo=N, fs_objetivo=fs)
    assert fs_r == fs, "Frecuencias de muestreo distintas tras resampling."
 
    # Generar Casos A y B
    x_A, alpha_A = crear_senal_ruidosa(x, r, SNR_CASO_A_DB)
    x_B, alpha_B = crear_senal_ruidosa(x, r, SNR_CASO_B_DB)
    print(f"[ruido] alpha_A = {alpha_A:.4f}  (SNR_A = {SNR_CASO_A_DB} dB)")
    print(f"[ruido] alpha_B = {alpha_B:.4f}  (SNR_B = {SNR_CASO_B_DB} dB)")
 
    wavfile.write(os.path.join(DIR_SALIDA, "voz_ruidosa_A.wav"), fs, x_A.astype(np.float32))
    wavfile.write(os.path.join(DIR_SALIDA, "voz_ruidosa_B.wav"), fs, x_B.astype(np.float32))
 
    # Diseño y aplicación de filtro FIR Pasa-Bajas
    h, M = disenar_fir_pasa_bajas(FC_PB, ANCHO_TRANSICION, fs, VENTANA_FIR)
    print(f"[filtro] FIR pasa-bajas, fc={FC_PB} Hz, M={M} taps (ventana {VENTANA_FIR})")
 
    y_A = aplicar_fir_fase_compensada(x_A, h)
    y_B = aplicar_fir_fase_compensada(x_B, h)
 
    wavfile.write(os.path.join(DIR_SALIDA, "voz_filtrada_A.wav"), fs, y_A.astype(np.float32))
    wavfile.write(os.path.join(DIR_SALIDA, "voz_filtrada_B.wav"), fs, y_B.astype(np.float32))
 
    # Cálculo de métricas
    ecm_A_in = ecm(x, x_A);  ecm_A_out = ecm(x, y_A)
    ecm_B_in = ecm(x, x_B);  ecm_B_out = ecm(x, y_B)
    snr_A_in = snr_db(x, x_A);  snr_A_out = snr_db(x, y_A)
    snr_B_in = snr_db(x, x_B);  snr_B_out = snr_db(x, y_B)
 
    print("\n=== METRICAS ===")
    print(f"{'':12s} {'SNR_in':>10s} {'SNR_out':>10s} {'ECM_in':>12s} {'ECM_out':>12s}")
    print(f"{'Caso A':12s} {snr_A_in:10.2f} {snr_A_out:10.2f} {ecm_A_in:12.2e} {ecm_A_out:12.2e}")
    print(f"{'Caso B':12s} {snr_B_in:10.2f} {snr_B_out:10.2f} {ecm_B_in:12.2e} {ecm_B_out:12.2e}")
    print(f"\nMejora SNR Caso A: {snr_A_out - snr_A_in:+.2f} dB")
    print(f"Mejora SNR Caso B: {snr_B_out - snr_B_in:+.2f} dB")
 
    # Sección Extra: Filtro Notch IIR (60 Hz)
    ruta_tono = os.path.join(DIR_RUIDOS, "ruido.wav")
    if os.path.exists(ruta_tono):
        print("\n=== SECCION EXTRA: notch 60 Hz ===")
        tono, _ = cargar_ruido(ruta_tono, N_objetivo=N, fs_objetivo=fs)
        alpha_t = calcular_alpha_para_snr(x, tono, 0.0)
        x_tono = x + alpha_t * tono
        b_n, a_n = disenar_notch_iir(F_NOTCH, Q_NOTCH, fs)
        y_tono = sig.filtfilt(b_n, a_n, x_tono)
        
        print(f"  SNR antes  = {snr_db(x, x_tono):.2f} dB")
        print(f"  SNR despues= {snr_db(x, y_tono):.2f} dB")
        print(f"  Mejora     = {snr_db(x, y_tono) - snr_db(x, x_tono):+.2f} dB")
        
        wavfile.write(os.path.join(DIR_SALIDA, "voz_tono60.wav"), fs, x_tono.astype(np.float32))
        wavfile.write(os.path.join(DIR_SALIDA, "voz_tono60_filtrada.wav"), fs, y_tono.astype(np.float32))
 
    # Exportar figuras PDF
    print("\n[figs] generando figuras PDF...")
    fig_voz_tiempo(x, fs, os.path.join(DIR_FIGS, "voz_completa.pdf"))
    fig_comparacion_ruidosa(x, x_A, x_B, fs, os.path.join(DIR_FIGS, "comparacion_ruidosa.pdf"))
    fig_espectros(x, x_B, fs, os.path.join(DIR_FIGS, "espectros_comparacion.pdf"))
    fig_respuesta_filtro(h, fs, os.path.join(DIR_FIGS, "respuesta_filtro.pdf"))
    fig_filtrada(x, x_B, y_B, fs, os.path.join(DIR_FIGS, "filtrada_comparacion.pdf"))
    print(f"[figs] guardadas en {DIR_FIGS}/")
    print("\n=== LISTO ===")
 
if __name__ == "__main__":
    main()