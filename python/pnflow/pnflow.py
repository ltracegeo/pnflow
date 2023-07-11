import ctypes
import os
import platform

if platform.system() == "Windows":
    library_filename = "pnflow.lib"
else:
    library_filename = "libpnflow.so"

current_dir = os.path.abspath(os.path.dirname(__file__))
pnflow_libc = ctypes.cdll.LoadLibrary(os.path.join(current_dir, library_filename))
pnflow_libc.pnflow.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
pnflow_libc.pnflow.restype = ctypes.c_char_p

def pnflow(config: str, link1: str, link2: str, node1: str, node2: str):
    return pnflow_libc.pnflow(
        config.encode("UTF-8"),
        link1.encode("UTF-8"),
        link2.encode("UTF-8"),
        node1.encode("UTF-8"),
        node2.encode("UTF-8"),
    ).decode('ascii')
