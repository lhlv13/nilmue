# -*- coding: utf-8 -*-
import os 
import sys
BASE_PATH = os.path.dirname(__file__)  ## 根目錄
sys.path.append(BASE_PATH)
from ctypes import *
import ctypes
import numpy as np

class Matrix(Structure):
    _fields_  = [
        ("array", POINTER(POINTER(c_double))),
        ("w", c_uint32),
        ("h", c_uint32)
    ]

class Vector(Structure):
    _fields_  = [
        ("array", POINTER(c_double)),
        ("shape", c_uint32)
    ]

class Index(Structure):
    _fields_  = [
        ("array", POINTER(c_uint32)),
        ("shape", c_uint32)
    ]

def callDll():
    """ 呼叫 DLLPATH 儲存的 dll """
    dll_path = config()["DLLPATH"]
    global BASE_PATH
    dll_path = os.path.join(BASE_PATH, dll_path)  ## 絕對路徑 模組需要
    return ctypes.CDLL(dll_path)
    

def config():
    global BASE_PATH
    path = os.path.join(BASE_PATH, "config")  ## 絕對路徑 模組需要
    path_dict = {}
    with open(path, 'r') as f:
        lines = f.readlines()
        for line in lines:
            l = line.strip().split("=")
            key, value = l[0].strip(), l[1].strip()
            path_dict[key] = value 
    return path_dict


def tolist(array):
    if(isinstance(array, np.ndarray)):
        return array.tolist()
    return array.tolist() if(isinstance(array, np.ndarray))  else array



    
