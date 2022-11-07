# -*- coding: utf-8 -*-
"""
Created on Fri Nov  4 17:48:09 2022

@author: Yuyi
"""

# -*- coding: utf-8 -*-
from ctypes import *
from config import Vector, callDll
import matplotlib.pyplot as plt
from standardwave import *
import matplotlib.pyplot as plt


def minMaxScaling(wave):
    """
    Parameters
    ----------
    wave : list
        欲做rms的波型
    base_wave: list
        判斷過零點的波型，一般為電壓波型
    sampling_points_of_T : uint32_t
        每周期波形的採樣點數

    Returns
    -------
    rms : list
        波型每周期的 rms

    """
    lib = callDll().MinMaxScaling
    lib.argtypes = [POINTER(Vector)]  ## ubuntu 一定要這行唷
    lib.restype = POINTER(Vector)
    args = [
              Vector( (c_double * len(wave))(*wave), len(wave) )
           ]
    output = lib(args[0])
    output = output[0].array[:output[0].shape]
    return output


def main():
    x = [0, 1, 2, 3, 4, 5]
    min_max = minMaxScaling(x)
    print(min_max)
    pass


if __name__ == "__main__":
    main()