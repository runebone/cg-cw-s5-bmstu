import pandas as pd
import matplotlib.pyplot as plt

def process_and_plot_data(file_paths):
    colors = ['tab:red', 'tab:orange', 'tab:green', 'tab:blue', 'tab:purple', 'tab:pink']
    markers = ['+', '^', 's', 'o', 'x', 'D']
    line_styles = ['-', '--', '-.', ':', (0, (5, 10)), (0, (3, 10, 1, 10))]

    # Create figures for each plot type
    plt.figure(figsize=(7, 5))
    for fi, file in enumerate(file_paths):
        # if fi in [4, 5]: continue
        if fi in [0, 1, 2]: continue
        data = pd.read_csv(file)
        grouped_data = data.groupby('n_objects')[['n_triangles']].mean().reset_index()
        plt.plot(grouped_data['n_objects'], grouped_data['n_triangles'], marker=markers[fi], color=colors[fi], label=f'Опыт {fi+1}', linestyle=line_styles[fi])
    plt.xlabel('Количество объектов')
    plt.ylabel('Среднее количество треугольников')
    plt.yscale('log')
    plt.legend()
    plt.grid(True)
    plt.savefig('plot_triangles.pdf')

    plt.figure(figsize=(7, 5))
    for fi, file in enumerate(file_paths):
        # if fi in [4, 5]: continue
        if fi in [0, 1, 2]: continue
        data = pd.read_csv(file)
        grouped_data = data.groupby('n_objects')[['n_collisions']].mean().reset_index()
        plt.plot(grouped_data['n_objects'], grouped_data['n_collisions'], marker=markers[fi], color=colors[fi], label=f'Опыт {fi+1}', linestyle=line_styles[fi])
    plt.xlabel('Количество объектов')
    plt.ylabel('Среднее количество коллизий')
    plt.legend()
    plt.grid(True)
    plt.savefig('plot_collisions.pdf')

    plt.figure(figsize=(7, 5))
    for fi, file in enumerate(file_paths):
        # if fi in [4, 5]: continue
        if fi in [0, 1, 2]: continue
        data = pd.read_csv(file)
        grouped_data = data.groupby('n_objects')[['n_draw_calls']].mean().reset_index()
        plt.plot(grouped_data['n_objects'], grouped_data['n_draw_calls'], marker=markers[fi], color=colors[fi], label=f'Опыт {fi+1}', linestyle=line_styles[fi])
    plt.xlabel('Количество объектов')
    plt.ylabel('Среднее количество вызовов функций отрисовки OpenGL')
    plt.yscale('log')
    plt.legend()
    plt.grid(True)
    plt.savefig('plot_draw_calls.pdf')

    plt.figure(figsize=(7, 5))
    for fi, file in enumerate(file_paths):
        # if fi in [4, 5]: continue
        if fi in [0, 1, 2]: continue
        data = pd.read_csv(file)
        grouped_data = data.groupby('n_objects')[['time_ns']].mean().reset_index()
        plt.plot(grouped_data['n_objects'], grouped_data['time_ns'], marker=markers[fi], color=colors[fi], label=f'Опыт {fi+1}', linestyle=line_styles[fi])
    plt.xlabel('Количество объектов')
    plt.ylabel('Среднее время генерации кадра, нс')
    plt.yscale('log')
    plt.legend()
    plt.grid(True)
    plt.savefig('plot_time.pdf')

file_paths = [
    "tests/test_01.csv",
    "tests/test_02.csv",
    "tests/test_03.csv",
    # "benchmark.csv",
    # "bm.csv",
    "tests/test_04.csv",
    "tests/test_05.csv",
    "tests/test_06.csv",
]

process_and_plot_data(file_paths)
