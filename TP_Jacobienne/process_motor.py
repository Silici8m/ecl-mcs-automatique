import time

import numpy as np
import params as prm
from emioapi import EmioMotors


J = [
 [  0.15392758, -15.23605736,   0.90122982,  10.08235593],
 [  6.05181807,  -3.43414785,   3.26312587,  -6.23320649],
 [  9.11500643,  -2.19256931, -11.43952226,   0.44666148]]

# ------------------------------------------------------------------------------
# Process
# ------------------------------------------------------------------------------
def process_motors(shared_markers_pos, shared_ref_ol, shared_save, shared_update, event_frame, event_measure):
    """pySimblocks runner process.
    """
    init_angles = np.array([0., 0., 0., 0.])
    motors = setup_motors(init_angles)

    # Initialize variables
    measure = np.zeros((prm.nb_markers * 3, 1))
    command = np.zeros((4, 1))
    if prm.mode == "jacobian":
        ref = np.zeros((3, 1))

    measures_list = []
    motors_pos_list = []
    commands_list = []
    if prm.mode == "jacobian":
        ref_list = []
        
        
    while True:
        event_frame.wait()
        event_frame.clear()
        
        event_measure.wait()
        event_measure.clear()

        #-----------------------------------------------------------------------
        # Read data
        #-----------------------------------------------------------------------
        with shared_markers_pos.get_lock():
            measure[:, 0] = shared_markers_pos[:]

        with shared_update.get_lock():
            if shared_update.value:
                if prm.mode == "openloop":
                    command[:, 0] = shared_ref_ol[:]
                else:
                    ref[:, 0] = shared_ref_ol[:3]
                    ref[:, 0] *= 100.
                shared_update.value = False

        motors_pos = get_motors_position(motors, init_angles)

        # ----------------------------------------------------------------------
        # TODO: compute command law from measure and ref.
        # ----------------------------------------------------------------------
        if prm.mode == "jacobian":
            # update command variable: desired position of motors based on Jacobian
            # command = 
            pass

        # ----------------------------------------------------------------------
        send_motors_command(motors, command, init_angles)
        
        #-----------------------------------------------------------------------
        # Store and Save
        #-----------------------------------------------------------------------
        measures_list.append(measure.copy())
        motors_pos_list.append(motors_pos.copy())
        commands_list.append(command.copy())
        if prm.mode == "jacobian":
            ref_list.append(ref.copy())

        with shared_save.get_lock():
            if shared_save.value:
                nb_measures = len(measures_list)
                if prm.mode == "openloop":
                    np.savez(
                            prm.data_path / "openloop.npz", 
                            measures=np.array(measures_list).reshape(nb_measures, -1),
                            motors_pos=np.array(motors_pos_list).reshape(nb_measures, -1),
                            commands=np.array(commands_list).reshape(nb_measures, -1),
                        )
                elif prm.mode == "jacobian":
                    np.savez(
                            prm.data_path / "jacobian.npz", 
                            measures=np.array(measures_list).reshape(nb_measures, -1),
                            motors_pos=np.array(motors_pos_list).reshape(nb_measures, -1),
                            commands=np.array(commands_list).reshape(nb_measures, -1),
                            ref=np.array(ref_list).reshape(nb_measures, -1),
                        )
                shared_save.value = False
                print(f"Data saved successfully with {nb_measures} measures.")


# ------------------------------------------------------------------------------
# Helpers
# ------------------------------------------------------------------------------

# -------------------------------------------------------
def setup_motors(init_angles=[0, 0, 0, 0]):
    motors = EmioMotors()
    while not motors.open():
        print("Waiting for motors to open...")
        time.sleep(1)
    print("Motors opened successfully.")
    time.sleep(1)
    motors.angles = init_angles
    return motors

# -------------------------------------------------------
def send_motors_command(motors, command, init_angles=np.array([0, 0, 0, 0])):
    command = command.flatten()
    motors.angles = [command[0] + init_angles[0], init_angles[1] + command[1],
                     command[2] + init_angles[2], init_angles[3] + command[3]]

# -------------------------------------------------------
def get_motors_position(motors, init_angles=np.array([0, 0, 0, 0])):
    motors_pos = np.array(motors.angles) - init_angles
    return motors_pos.reshape((-1, 1))

