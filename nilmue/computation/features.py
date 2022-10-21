# -*- coding: utf-8 -*-
from ctypes import *
from config import Vector, Index, callDll
from standardwave import sinWave
import numpy as np
import matplotlib.pyplot as plt

def zeroCrossing(wave, sampling_points_of_T):
    """
    Parameters
    ----------
    wave : list
        欲找零交越點的波形
    sampling_points_of_T : uint32_t
        每周期波形的採樣點數

    Returns
    -------
    zeros : list
        零交越的採樣點位置

    """
    lib = callDll().ZeroCrossing
    lib.argtypes = [POINTER(Vector), c_uint32]  ## ubuntu 一定要這行唷
    lib.restype = POINTER(Index)
    args = [
              Vector( (c_double * len(wave))(*wave), len(wave) ),
              c_uint32(sampling_points_of_T)
           ]
    output = lib(args[0], args[1])
    zeros = output[0].array[:output[0].shape]
    return zeros

def rms(wave, base_wave, sampling_points_of_T):
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
    lib = callDll().RMS
    lib.argtypes = [POINTER(Vector), POINTER(Vector), c_uint32]  ## ubuntu 一定要這行唷
    lib.restype = POINTER(Vector)
    args = [
              Vector( (c_double * len(wave))(*wave), len(wave) ),
              Vector( (c_double * len(wave))(*wave), len(wave) ),
              c_uint32(sampling_points_of_T)
           ]
    output = lib(args[0], args[1], args[2])
    output = output[0].array[:output[0].shape]
    return output







def main():
    
    sin = sinWave(A=10, frequency=60, sampling_points_of_T=32, seconds=1)
    zero = zeroCrossing(sin, sampling_points_of_T=32)
    x = [i for i in range(len(sin))]
    y = np.zeros(len(x))
    for i in zero:
        y[int(i)] = 10
        
    # plt.plot(sin, c='b')
    # plt.plot(y, c='r')
    # plt.savefig(r"img/zero.jpg")
    print(zero)
    # print(len(zero))
    rms_list = rms(sin, sin, 32)
    print(rms_list)
    pass


if __name__ == "__main__":
    main()