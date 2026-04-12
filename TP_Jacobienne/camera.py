import json

import cv2 as cv
import numpy as np
import params as prm
from emioapi._depthcamera import DepthCamera


# ------------------------------------------------------------------------------
# Process
# ------------------------------------------------------------------------------
def process_camera(shared_markers_pos, shared_start, 
                   event_frame, event_measure):
    """Update tracker position."""
    camera = setup_camera()

    init_pos = np.zeros((3 * prm.nb_markers, 1))
    pos = np.zeros((3 * prm.nb_markers, 1))
    start = False

    while True:
        # get frame from camera
        ret = camera.get_frame()
        event_frame.set()

        if not ret:
            raise RuntimeError("Camera frame not received")

        pos = process_frame(camera, pos)

        if start:
            pos -= init_pos
            with shared_markers_pos.get_lock():
                shared_markers_pos[:] = pos.flatten()
            event_measure.set()

        else:
            init_pos = pos
            with shared_start.get_lock():
                start = shared_start.value

        k = cv.waitKey(1)
        if k == ord('q'):
            camera.quit()
            break


# ------------------------------------------------------------------------------
# Helpers
# ------------------------------------------------------------------------------
def setup_camera():
    json_path = prm.data_path / "cameraparameter.json"
    with json_path.open('r') as fp:
        json_parameters = json.load(fp)
    camera = DepthCamera(
        show_video_feed=True,
        tracking=True,
        compute_point_cloud=False,
        parameter=json_parameters)
    camera.set_fps(prm.fps)
    camera.set_depth_min(0)
    camera.set_depth_max(1000)
    camera.open()
    return camera


# -------------------------------------------------------
def process_frame(camera, last_pos):
    camera.process_frame()
    if len(camera.trackers_pos) == prm.nb_markers:
        pos = np.array(camera.trackers_pos).reshape(prm.nb_markers, 3).copy()
        pos = pos.astype(np.float64)
        return pos
    return last_pos
