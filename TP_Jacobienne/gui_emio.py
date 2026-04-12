import tkinter as tk

import numpy as np


# -------------------------------------------------------------------------------
# Process
# -------------------------------------------------------------------------------
def process_gui(shared_ref_ol, shared_start, shared_save, shared_update):
    root = tk.Tk()
    app = EmioRealTimeGUI(root, shared_ref_ol, shared_start, shared_save, shared_update)
    root.protocol("WM_DELETE_WINDOW", app.close_app)
    root.mainloop()

# -------------------------------------------------------------------------------
# GUI Class
# -------------------------------------------------------------------------------
class EmioRealTimeGUI:
    MOTOR_SCALE = np.pi / 2 / 100  # slider [-100..100] -> radians

    def __init__(self, root, shared_ref_ol,  shared_start, shared_save, shared_update): 
        self.root = root
        self.root.title('Emio Real Time Control')
        self.root.geometry("500x350")

        # ------- Variables -------
        # shared
        self.shared_ref_ol = shared_ref_ol
        self.shared_start = shared_start
        self.shared_update = shared_update
        self.shared_save = shared_save

        # local
        self.start = False
        self.active = True

        # ------- Information Frame -------
        info_frame = tk.Frame(root)
        info_frame.pack()
        info = ["Start", "Active"]
        info_values = ["False", "True"]
        self.label_info = {}
        for i, item in enumerate(info):
            self.label_info[item] = tk.Label(
                    info_frame, 
                    text=f"{item}: {info_values[i]}", font=("Arial", 12))
            self.label_info[item].pack(side="left", padx=5, pady=5)

        # ------- Control Frame -------
        self.build_sliders()
        self.build_buttons()


    # --------------------------------------------------------------------------
    # Build methods
    # --------------------------------------------------------------------------
    def build_sliders(self):
        self.label_motors = []
        self.sliders_motor = []
        motor_label_frame = tk.Frame(self.root)
        motor_label_frame.pack()
        motor_slider_frame = tk.Frame(self.root)
        motor_slider_frame.pack()

        self.label_ref = []
        self.sliders_ref = []        
        ref_label_frame = tk.Frame(self.root)
        ref_label_frame.pack()
        ref_slider_frame = tk.Frame(self.root)
        ref_slider_frame.pack()

        for i in range(4):
            self.label_motors.append(
                self._build_label(motor_label_frame, text=f"Motor {i + 1}: 0.00 (rad)")
            )
            self.sliders_motor.append(
                self._build_slider(
                    motor_slider_frame,
                    command=lambda val, idx=i: self._motor_action(val, idx),
                )
            )

    # ----------------------------------------------------------
    def build_buttons(self):
        button_frame = tk.Frame(self.root)
        button_frame.pack(pady=10)

        buttons = [
            ("Start", self.start_action),
            ("Active", self.active_action),
            ("Save", self.save_action),
        ]
        for name, action in buttons:
            tk.Button(button_frame, text=name, command=action).pack(side="left", padx=3)


    # --------------------------------------------------------------------------
    # Slider actions
    # --------------------------------------------------------------------------
    def _motor_action(self, val, index: int):
        if not self.start:
            self.sliders_motor[index].set(0)
            return
        cmd = float(val) * self.MOTOR_SCALE  # radians
        self.label_motors[index].config(text=f"Motor {index + 1}: {cmd:.2f} (rad)")
        if self.active:
            self._push_current_commands()

    # --------------------------------------------------------------------------
    # Button actions
    # --------------------------------------------------------------------------
    def start_action(self):
        if not self.start:
            self.start = True
            self.label_info["Start"].config(text="Start: True")
            with self.shared_start.get_lock():
                self.shared_start.value = self.start
            self._push_current_commands()

    # ----------------------------------------------------------
    def active_action(self):
        if not self.start:
            return
        self.active = not self.active
        self.label_info["Active"].config(text=f"Active: {self.active}")
        if self.active:
            self._push_current_commands()

    # ----------------------------------------------------------
    def save_action(self):
        if not self.start:
            return
        with self.shared_save.get_lock():
            self.shared_save.value = True

    # --------------------------------------------------------------------------
    # Other methods
    # --------------------------------------------------------------------------
    def close_app(self):
        self.root.destroy()

    # ----------------------------------------------------------
    def _build_slider(self, frame, command, from_=-100, to=100):
        slider = tk.Scale(frame, from_=from_, to=to, orient="horizontal", command=command)
        slider.set(0)
        slider.pack(side="left", padx=3, pady=5)
        return slider

    # ----------------------------------------------------------
    def _build_label(self, frame, text):
        label = tk.Label(frame, text=text)
        label.pack(side="left", padx=3, pady=5)
        return label

    # ----------------------------------------------------------
    def _push_current_commands(self):
        pos = [float(slider.get()) for slider in self.sliders_motor]
        with self.shared_ref_ol.get_lock():
            for i in range(4):
                self.shared_ref_ol[i] = pos[i] * self.MOTOR_SCALE

        with self.shared_update.get_lock():
            self.shared_update.value = True

if __name__ == "__main__":
    import multiprocessing as mp
    from time import sleep

    # Shared variables
    shared_ref_ol = mp.Array('d', 4)  # 4 motors
    shared_start = mp.Value('b', False)
    shared_active = mp.Value('b', True)
    shared_update = mp.Value('b', False)
    shared_save = mp.Value('b', False)

    # Start GUI process
    p_gui = mp.Process(target=process_gui, args=(shared_ref_ol, shared_start, shared_save, shared_update))
    p_gui.start()

    # Simulate main control loop
    try:
        while True:
            if shared_start.value:
                print("Start signal received.")
                print("Current motor commands:", list(shared_ref_ol))
                if shared_save.value:
                    print("Save signal received.")
                    shared_save.value = False
            sleep(1)
    except KeyboardInterrupt:
        pass

    p_gui.join()
