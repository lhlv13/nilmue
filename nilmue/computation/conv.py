# -*- coding: utf-8 -*-
import os 
import sys
sys.path.append(os.path.dirname(__file__))
from ctypes import *
from config import Vector, callDll





def convolution(array, kernel, stride=1):
    lib = callDll().Conv1d
    lib.argtypes = [POINTER(Vector), POINTER(Vector), c_uint32]  ## ubuntu 一定要這行唷
    lib.restype = POINTER(Vector)
    args = [
              Vector( (c_double * len(array))(*array), len(array) ),
              Vector( (c_double * len(kernel))(*kernel), len(kernel) ),
              c_uint32(stride)
           ]
    output = lib(args[0], args[1], args[2])
    conv = output[0].array[:output[0].shape]
    return conv


def main():
    import numpy as np
    
    array = np.arange(10)
    kernel = np.array([0.5, 1, 2])
    conv = convolution(array, kernel, stride=1)
    print(conv)
    print(len(conv))
    pass


if __name__ == "__main__":
    main()