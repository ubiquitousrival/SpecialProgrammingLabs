import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, CheckButtons
from scipy import signal

noise_cache = None
last_noise_params = (0, 0) 

t = np.linspace(0, 10, 1000)
fs = 1.0 / (t[1] - t[0]) 

DEFAULTS = {
    'amplitude': 1.0,
    'frequency': 1.5,
    'phase': 0.0,
    'noise_mean': 0.0,
    'noise_covariance': 0.1,
    'show_noise': True,
    'filter_cutoff': 5.0, 
    'filter_order': 4
}

def harmonic_with_noise(t, amplitude, frequency, phase, noise_mean, noise_covariance, show_noise):
    global noise_cache, last_noise_params
    
    clean_signal = amplitude * np.sin(frequency * t + phase)
    
    current_noise_params = (noise_mean, noise_covariance)
    
    if noise_cache is None or current_noise_params != last_noise_params:
        noise_cache = np.random.normal(noise_mean, np.sqrt(noise_covariance), len(t))
        last_noise_params = current_noise_params
        
    if show_noise:
        noisy_signal = clean_signal + noise_cache
    else:
        noisy_signal = clean_signal
        
    return clean_signal, noisy_signal

def filter_signal(input_signal, cutoff_hz, order):
    nyquist_freq = 0.5 * fs
    normal_cutoff = cutoff_hz / nyquist_freq
    
    if normal_cutoff >= 1.0:
        normal_cutoff = 0.99
        
    b, a = signal.butter(order, normal_cutoff, btype='low', analog=False)

    filtered_signal = signal.filtfilt(b, a, input_signal)
    return filtered_signal

fig, ax = plt.subplots(figsize=(12, 8))
plt.subplots_adjust(left=0.25, bottom=0.45, top=0.9) 

clean_sig, noisy_sig = harmonic_with_noise(
    t, DEFAULTS['amplitude'], DEFAULTS['frequency'], DEFAULTS['phase'],
    DEFAULTS['noise_mean'], DEFAULTS['noise_covariance'], DEFAULTS['show_noise']
)
filtered_sig = filter_signal(
    noisy_sig, DEFAULTS['filter_cutoff'], DEFAULTS['filter_order']
)

l_clean, = ax.plot(t, clean_sig, 'b--', label='Чиста гармоніка', alpha=0.7)
l_noisy, = ax.plot(t, noisy_sig, 'orange', label='Зашумлений сигнал', alpha=0.8)
l_filtered, = ax.plot(t, filtered_sig, 'purple', label='Відфільтрований сигнал', linewidth=2.5)

ax.set_title('Інтерактивний аналіз гармоніки та фільтрації')
ax.set_xlabel('Час (t)')
ax.set_ylabel('Амплітуда y(t)')
ax.legend(loc='upper right')
ax.grid(True)
ax.set_ylim([-3, 3]) 

ax_amp = plt.axes([0.15, 0.30, 0.65, 0.03])
ax_freq = plt.axes([0.15, 0.25, 0.65, 0.03])
ax_phase = plt.axes([0.15, 0.20, 0.65, 0.03])
ax_n_mean = plt.axes([0.15, 0.15, 0.65, 0.03])
ax_n_cov = plt.axes([0.15, 0.10, 0.65, 0.03])
ax_f_cutoff = plt.axes([0.15, 0.05, 0.65, 0.03])

s_amp = Slider(ax_amp, 'Amplitude', 0.1, 5.0, valinit=DEFAULTS['amplitude'])
s_freq = Slider(ax_freq, 'Frequency (ω)', 0.1, 10.0, valinit=DEFAULTS['frequency'])
s_phase = Slider(ax_phase, 'Phase (φ)', 0.0, 2 * np.pi, valinit=DEFAULTS['phase'])
s_noise_mean = Slider(ax_n_mean, 'Noise Mean', -0.5, 0.5, valinit=DEFAULTS['noise_mean'])
s_noise_cov = Slider(ax_n_cov, 'Noise Covariance', 0.0, 1.0, valinit=DEFAULTS['noise_covariance'])
s_filter_cutoff = Slider(ax_f_cutoff, 'Filter Cutoff (Hz)', 0.1, 20.0, valinit=DEFAULTS['filter_cutoff'])

ax_check = plt.axes([0.85, 0.25, 0.1, 0.04])
check_button = CheckButtons(ax_check, ['Show Noise'], [DEFAULTS['show_noise']])

ax_reset = plt.axes([0.85, 0.20, 0.1, 0.04])
reset_button = Button(ax_reset, 'Reset')

def update(val):
    amp = s_amp.val
    freq = s_freq.val
    phase = s_phase.val
    n_mean = s_noise_mean.val
    n_cov = s_noise_cov.val
    f_cutoff = s_filter_cutoff.val
    show_noise = check_button.get_status()[0] 
    
    clean_sig, active_sig = harmonic_with_noise(t, amp, freq, phase, n_mean, n_cov, show_noise)
    
    filtered_sig = filter_signal(active_sig, f_cutoff, DEFAULTS['filter_order'])
    
    l_clean.set_ydata(clean_sig)
    l_noisy.set_ydata(active_sig)
    l_filtered.set_ydata(filtered_sig)
    
    max_val = max(np.max(active_sig), amp) * 1.2
    min_val = min(np.min(active_sig), -amp) * 1.2
    ax.set_ylim([min_val - 0.1, max_val + 0.1])
    
    fig.canvas.draw_idle()

def reset(event):
    """
    Викликається при натисканні кнопки Reset. (Завдання 6)
    """
    global noise_cache
    noise_cache = None
    
    s_amp.reset()
    s_freq.reset()
    s_phase.reset()
    s_noise_mean.reset()
    s_noise_cov.reset()
    s_filter_cutoff.reset()
    
    check_button.set_active(0) 
    if not DEFAULTS['show_noise']: 
        check_button.set_active(0)
    
    update(None)

s_amp.on_changed(update)
s_freq.on_changed(update)
s_phase.on_changed(update)
s_noise_mean.on_changed(update)
s_noise_cov.on_changed(update)
s_filter_cutoff.on_changed(update)
check_button.on_clicked(update)
reset_button.on_clicked(reset)

instructions = """
Як користуватися програмою:
1. Синій пунктир: чиста гармоніка
   y(t) = A * sin(ω*t + φ).
2. Помаранчева лінія: сигнал з
   доданим шумом.
3. Фіолетова лінія: результат
   фільтрації помаранчевої лінії.
4. Слайдери "Amplitude", "Frequency",
   "Phase" змінюють чисту гармоніку.
5. Слайдери "Noise Mean",
   "Noise Covariance" змінюють
   параметри шуму.
   (Шум регенерується тільки
   при зміні цих двох слайдерів).
6. Чекбокс "Show Noise"
   вмикає/вимикає додавання шуму.
7. Слайдер "Filter Cutoff (Hz)"
   налаштовує фільтр (чим нижче,
   тим "гладший" результат).
8. Кнопка "Reset" повертає
   всі налаштування до початкових.
"""
fig.text(0.01, 0.98, instructions, verticalalignment='top', fontsize=8, wrap=False)

plt.show()