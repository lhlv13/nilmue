# -*- coding: utf-8 -*-
from ctypes import *
from config import Vector, callDll
import matplotlib.pyplot as plt

def sinWave(A, frequency, sampling_points_of_T, seconds, phi=0.0, isShow=False):
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
    
    lib = callDll()
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




def cosWave(A, frequency, sampling_points_of_T, seconds, phi=0, isShow=False):
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

    lib = callDll()
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


def main():
    sin = sinWave(A=10, frequency=60, sampling_points_of_T=32, seconds=1)
    print(len(sin))
    plt.plot(sin)
    plt.savefig("./test2.jpg")
    pass


if __name__ == "__main__":
    main()