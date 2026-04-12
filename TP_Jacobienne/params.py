from pathlib import Path
import numpy as np

nb_markers = 1
order = 5
fps = 30
mode = "openloop" # "openloop" or "jacobian"

path = Path(__file__).resolve()
data_path = path.parent / "data"

# TODO: Remplacer par la valeur calculée dans read_data.py
J = np.zeros((3,4))
J_inv = np.zeros((4, 3))

