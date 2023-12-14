# import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def process_and_plot_data(file_paths):
    # perm = [2, 4, 1, 5, 3, 0]
    colors = ['tab:red', 'tab:orange', 'tab:green', 'tab:blue', 'tab:purple', 'tab:pink']
    markers = ['+', '^', 's', 'o', 'x', 'D']
    line_styles = ['-', '--', '-.', ':', (0, (5, 10)), (0, (3, 10, 1, 10))]

    _, axes = plt.subplots(2, 2, figsize=(14, 10))

    # for i, file in enumerate(file_paths):
    for fi, i in enumerate([2, 4, 1, 5, 3, 0]):
        if fi in [4, 5]: continue
        # if fi in [0, 1, 2]: continue
        # data = pd.read_csv(file)
        data = pd.read_csv(file_paths[fi])
        grouped_data = data.groupby('n_objects')[['n_triangles', 'n_collisions', 'n_draw_calls', 'time_ns']].mean().reset_index()

        # grouped_data['time_ns'] = list(map(lambda x: x / 10, grouped_data['time_ns']))

        axes[0, 0].plot(grouped_data['n_objects'], grouped_data['n_triangles'], marker=markers[i], color=colors[i], label=f'Тест {fi+1}', linestyle=line_styles[i])
        axes[0, 1].plot(grouped_data['n_objects'], grouped_data['n_collisions'], marker=markers[i], color=colors[i], label=f'Тест {fi+1}', linestyle=line_styles[i])
        axes[1, 0].plot(grouped_data['n_objects'], grouped_data['n_draw_calls'], marker=markers[i], color=colors[i], label=f'Тест {fi+1}', linestyle=line_styles[i])
        axes[1, 1].plot(grouped_data['n_objects'], grouped_data['time_ns'], marker=markers[i], color=colors[i], label=f'Тест {fi+1}', linestyle=line_styles[i])

    # axes[0, 0].set_title('Average Number of Triangles vs Number of Objects')
    axes[0, 0].set_xlabel('Количество объектов')
    axes[0, 0].set_ylabel('Среднее количество треугольников')
    axes[0, 0].set_yscale('log')

    # axes[0, 1].set_title('Average Number of Collisions vs Number of Objects')
    axes[0, 1].set_xlabel('Количество объектов')
    axes[0, 1].set_ylabel('Среднее количество коллизий')
    # axes[0, 1].set_yscale('log')

    # axes[1, 0].set_title('Average Number of Draw Calls vs Number of Objects')
    axes[1, 0].set_xlabel('Количество объектов')
    axes[1, 0].set_ylabel('Среднее количество вызовов функций отрисовки OpenGL')
    axes[1, 0].set_yscale('log')

    # axes[1, 1].set_title('Average Time (ns) vs Number of Objects')
    axes[1, 1].set_xlabel('Количество объектов')
    axes[1, 1].set_ylabel('Среднее время генерации кадра (мс)')
    axes[1, 1].set_yscale('log')

    for ax in axes.flat:
        ax.legend()

    plt.tight_layout()
    plt.show()

# file_paths = [
#     "test_03.csv",
#     "test_05.csv",
#     "test_02.csv",
#     "test_06.csv",
#     "test_04.csv",
#     "test_01.csv",
# ]

file_paths = [
    # "tests/test_01.csv",
    "benchmark.csv",
    "tests/test_02.csv",
    "tests/test_03.csv",
    "tests/test_04.csv",
    "tests/test_05.csv",
    "tests/test_06.csv",
]

process_and_plot_data(file_paths)
