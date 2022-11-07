# -*- coding: utf-8 -*-
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
    return ctypes.CDLL(dll_path)
    

def config():
    config = "./config"
    path_dict = {}
    with open(config, 'r') as f:
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



    
