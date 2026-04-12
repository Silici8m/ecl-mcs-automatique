import params as prm
import numpy as np
import matplotlib.pyplot as plt

data = np.load(prm.data_path / "openloop.npz")

measures = data["measures"]
motors_pos = data["motors_pos"]
commands = data["commands"]

ny, nu = measures.shape[1], motors_pos.shape[1]
nb_samples = measures.shape[0]

print(f"Number of outputs (ny): {ny}")
print(f"Number of inputs (nu): {nu}")
print(f"Total number of samples: {nb_samples}")

dmeasures = dmeasures = np.diff(measures, axis=0)
dcommands = np.diff(commands, axis=0)
dy_plus = np.linalg.pinv(dcommands)
du = dmeasures
print(dy_plus.shape, du.shape)
J = du.T @ dy_plus.T
print(J)

"""
nu = motors_pos.shape[1]
fig, axs = plt.subplots(nu, 1, figsize=(10, 2*nu))
for i in range(nu):
    ax = axs[i]
    ax.plot(motors_pos[:, i], label="motors_pos")
    ax.set_title(f"Input {i}")
    ax.legend()
fig.tight_layout()


ny = measures.shape[1]
fig, axs = plt.subplots(ny, 1, figsize=(10, 2*ny))
for i in range(ny):
    ax = axs[i]
    ax.plot(measures[:, i], label="measures")
    ax.set_title(f"Output {i}")
    ax.legend()
fig.tight_layout()
plt.show()

"""