# -*- coding: utf-8 -*-
"""
Created on Tue Nov  8 00:57:40 2022

@author: Yuyi
"""
import sys
path = r"E:\\"     ## 填入自己放 nilmue資料夾 的路徑
sys.path.append(path)

import nilmue as ni
import matplotlib.pyplot as plt


def main():
    sin = ni.computation.sinWave(A=10, frequency=60, sampling_points_of_T=32, seconds=1)
    cos = ni.computation.cosWave(A=10, frequency=60, sampling_points_of_T=32, seconds=1)
    zeros = ni.computation.zeroCrossing(sin, sampling_points_of_T=32)
    rms_v = ni.computation.rms(sin, zeros)
    vi = ni.computation.viTrajectory(sin, cos)
    plt.imshow(vi)
    plt.title("V-I")
    plt.show()

if __name__ == "__main__":
    main()

