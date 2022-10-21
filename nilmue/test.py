from ctypes import *
import ctypes
import numpy as np
import matplotlib.pyplot as plt
import sys
import os
BASE_DIR = os.path.dirname(os.path.dirname(__file__))
sys.path.append(BASE_DIR)

print("HI")
print(os.path.dirname(__file__))

PATH = "../lib/libnilmue.so"

lib = ctypes.CDLL(PATH)
sin = lib.Sin


