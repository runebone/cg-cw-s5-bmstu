# import numpy as np
import pandas as pd

def generate_tables(file_paths):
    for i, file in enumerate(file_paths):
        data = pd.read_csv(file)
        grouped_data = data.groupby('n_objects')[['n_triangles', 'n_collisions', 'n_draw_calls', 'time_ns']].mean() #.reset_index()
        specific_rows = grouped_data.loc[[26, 46, 86, 106, 126]]
        outfile = f"table_0{i+1}.csv"
        specific_rows.to_csv(outfile)
        print(specific_rows)

file_paths = [
    "tests/test_01.csv",
    "tests/test_02.csv",
    "tests/test_03.csv",
    "tests/test_04.csv",
    "tests/test_05.csv",
    "tests/test_06.csv",
]

generate_tables(file_paths)
