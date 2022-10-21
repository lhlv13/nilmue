# -*- coding: utf-8 -*-

import ctypes
from ctypes import *
import numpy as np
from numpy.ctypeslib import ndpointer
import matplotlib.pyplot as plt

##----------------------------------------------------------------
DLL_PATH = "../lib/libnilmue.so"

##----------------------------------------------------------------
def callDll(dll_path):
    return ctypes.CDLL(dll_path)
    
class Vector(Structure):
    _fields_  = [
        ("array", POINTER(c_double)),
        ("shape", c_uint32)
    ]


def c_sinWave(A, frequency, sampling_points_of_T, seconds, phi=0, isShow=False):
    """
    Parameters
    ----------
    A : double
        振幅
    frequency : double
        頻率
    sampling_points_of_T : double
        每周期採樣點數
    seconds : double
        採樣秒數
    phi : double, optional
        相位 The default is 0.
    isShow : boolean, optional
        是否顯示圖片 The default is False.

    Returns
    -------
    sin : list
        一個 sin 波形

    """
    global DLL_PATH
    lib = callDll(DLL_PATH)
    lib.Sin.argtypes = [c_double, c_double, c_double, c_double, c_double]
    lib.Sin.restype = POINTER(Vector)
    
    output = lib.Sin(A, frequency, sampling_points_of_T, seconds, phi)
    sin = output[0].array[:output[0].shape]
    if isShow:
        plt.title(f"Standard Sin_{A}_{frequency}_{sampling_points_of_T}")
        plt.plot(sin)
        plt.xlabel("Sampling Points")
        plt.ylabel("Altitude")
        plt.show()
        
    return sin


def c_cosWave(A, frequency, sampling_points_of_T, seconds, phi=0, isShow=False):
    """
    Parameters
    ----------
    A : double
        振幅
    frequency : double
        頻率
    sampling_points_of_T : double
        每周期採樣點數
    seconds : double
        採樣秒數
    phi : double, optional
        相位 The default is 0.
    isShow : boolean, optional
        是否顯示圖片 The default is False.

    Returns
    -------
    cos : list
        一個 cos 波形

    """
    global DLL_PATH
    lib = callDll(DLL_PATH)
    lib.Cos.argtypes = [c_double, c_double, c_double, c_double, c_double]
    lib.Cos.restype = POINTER(Vector)
    
    output = lib.Cos(A, frequency, sampling_points_of_T, seconds, phi)
    cos = output[0].array[:output[0].shape]
    if isShow:
        plt.title(f"Standard Cos_{A}_{frequency}_{sampling_points_of_T}")
        plt.plot(cos)
        plt.xlabel("Sampling Points")
        plt.ylabel("Altitude")
        plt.show()
        
    return cos



def c_zeroCrossing(wave, sampling_points_of_T):
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
    global DLL_PATH
    lib = callDll(DLL_PATH).ZeroCrossing
    lib.restype = POINTER(Vector)
    args = [
              Vector( (c_double * len(wave))(*wave), len(wave) ),
              c_uint32(sampling_points_of_T)
           ]
    
    output = lib(args[0], args[1])
    zeros = output[0].array[:output[0].shape]
    return zeros


def c_conv1d(array, kernel, step=1):
    global DLL_PATH
    lib = callDll(DLL_PATH).Conv1d
    lib.restype = POINTER(Vector)
    args = [
              Vector( (c_double * len(array))(*array), len(array) ),
              Vector( (c_double * len(kernel))(*kernel), len(kernel) ),
              c_uint32(step)
           ]
    output = lib(args[0], args[1], args[2])
    conv = output[0].array[:output[0].shape]
    return conv


    
def main():
    sin = c_sinWave(A=10, frequency=60, sampling_points_of_T=32, seconds=1, phi=0)
    # plt.plot(sin)
    # plt.title("Standard Sin")
    # plt.savefig("test.jpg")
    #cos = c_cosWave(A=10, frequency=60, sampling_points_of_T=32, seconds=0.015, phi=0, isShow=True)
    zeros = c_zeroCrossing(sin, sampling_points_of_T=32)
    print(zeros, len(zeros))
    ## Convolution
    # array = [1,1,1,1,1]
    # kernel = [1,21,1]
    # print("start:")
    # conv = c_conv1d(array, kernel, 1)
    
    # print(conv)
    
    pass


if __name__ == "__main__":
    main()
    
    
