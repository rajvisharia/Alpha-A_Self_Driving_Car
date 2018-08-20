#!/bin/bash

# 
# This file executes from the build directory by the Eclipse "Pre Build" step
#

python ../_can_dbc/dbc_parse.py -i ../../alpha_dbc.dbc -s DRIVER > ../_can_dbc/generated_can.h