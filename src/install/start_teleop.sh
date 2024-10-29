#!/bin/bash

export LD_LIBRARY_PATH=./install/lib:./install/bin:$LD_LIBRARY_PATH

./install/bin/aimrt_main --cfg_file_path=./cfg/teleop.cfg
