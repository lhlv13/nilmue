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

def rms(wave, zeros):
    """
    Parameters
    ----------
    wave : list
        欲做rms的波型
    zeros: list
        判斷過零點的波型，一般為電壓波型
   

    Returns
    -------
    rms : list
        波型每周期的 rms

    """
    lib = callDll().RMS
    lib.argtypes = [POINTER(Vector), POINTER(Index)]  ## ubuntu 一定要這行唷
    lib.restype = POINTER(Vector)
    args = [
              Vector( (c_double * len(wave))(*wave), len(wave) ),
              Index( (c_uint32 * len(zeros))(*zeros), len(zeros) )
           ]
    output = lib(args[0], args[1])
    output = output[0].array[:output[0].shape]
    return output


def peakEnvelope(wave, zeros):
    """
    Parameters
    ----------
    wave : list
        欲做 電流峰值包絡線 的波型
    zeros: list
        判斷過零點的波型，一般為電壓波型
   

    Returns
    -------
    up : list
        上 峰值包絡線
    down: list
        下 峰直包絡線

    """
    lib = callDll().PeakEnvelope
    lib.argtypes = [POINTER(Vector), POINTER(Index)]  ## ubuntu 一定要這行唷
    lib.restype = POINTER(POINTER(Vector))
    args = [
              Vector( (c_double * len(wave))(*wave), len(wave) ),
              Index( (c_uint32 * len(zeros))(*zeros), len(zeros) )
           ]

    arr_2 = lib(args[0], args[1])
    output = arr_2[0]
    up = output[0].array[:output[0].shape]
    output = arr_2[1]
    down = output[0].array[:output[0].shape]

    return up, down



def main():
    ## 標準 sin 波
    sin = sinWave(A=10, frequency=60, sampling_points_of_T=32, seconds=1)
    ######################################################## 測試 zeroCrossing
    # zeros = zeroCrossing(sin, sampling_points_of_T=32)
    # print("zeroCrossing","-"*40)
    # print(f"size: {len(zeros)}")  ## 輸出61才會有60個區間(60 Hz)
    # print(f"Array : \n{zeros}\n\n")
    # print("Not 32 : ")
    # for i in range(len(zeros)-1):
    #     v = zeros[i+1] - zeros[i]
    #     if v!=32:
    #         print(f"{i} -> {i+1}  : {v}")
    ######################################################## 測試 rms
    # sin = sinWave(A=10, frequency=60, sampling_points_of_T=32, seconds=1)
    # zeros = zeroCrossing(sin, sampling_points_of_T=32)
    # rms_v = rms(sin, zeros)
    # print("rms","-"*40)
    # print(f"size: {len(rms_v)}")  ## 
    # print("Array : ")
    # for i in range(len(rms_v)):
    #     print(f"{rms_v[i]:>.2f}",end=",")
    # print("\n\n")

    ######################################################## 測試 peakEnvelope
    sin = sinWave(A=10, frequency=60, sampling_points_of_T=32, seconds=0.033)
    zeros = zeroCrossing(sin, sampling_points_of_T=32)
    up, down = peakEnvelope(sin, zeros)
    print("peakEnvelope","-"*40)
    print(f"size: {len(up)}, {len(down)}")  ## 長度 : 上包絡線，下包絡線
    print("Array : ")
    print(f"Up : {up}")
    print(f"Down : {down}")
    


    

    ## 畫圖
    # plt.plot(sin, c='b')
    # plt.plot(y, c='r')
    # plt.savefig(r"img/zero.jpg")
    # print(zero)
    # print(len(zero))
    # rms_list = rms(sin, sin, 32)
    # print(rms_list)
    # pass


if __name__ == "__main__":
    main()