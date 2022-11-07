# -*- coding: utf-8 -*-
"""
Created on Mon Nov  7 22:13:56 2022

@author: Yuyi
"""

import os 
import sys
path = os.path.dirname(os.path.dirname(__file__))  ## 檔案所在資料夾
for i in range(3):
    path = os.path.dirname(path)
sys.path.append(path)
print(path)
from nilmue.nilmue.computation.conv import *
from nilmue.nilmue.computation.features import *
from nilmue.nilmue.computation.standardwave import *
from nilmue.nilmue.computation.tool import *

