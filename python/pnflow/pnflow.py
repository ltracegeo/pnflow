import ctypes
import os

current_dir = os.path.abspath(os.path.dirname(__file__))
pnflow_libc = ctypes.cdll.LoadLibrary(os.path.join(current_dir, "pnflow.lib"))
pnflow_libc.pnflow.argtypes = [ctypes.c_char_p]

def pnflow(config: str):
    pnflow_libc.pnflow(config.encode("UTF-8"))
