############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
############################################################
open_project FPGA_Convolution
add_files FPGA_Convolution/design/template/constants.h
add_files FPGA_Convolution/design/template/convolution_template.h
add_files FPGA_Convolution/design/template/fully_connected_template.h
add_files network.cpp
add_files FPGA_Convolution/design/network.h
add_files FPGA_Convolution/design/template/pooling_template.h
add_files -tb FPGA_Convolution/test_bench/fully_connected_tb.h
add_files -tb FPGA_Convolution/test_bench/main_tb.cpp
add_files -tb FPGA_Convolution/test_bench/pooling_tb.h
open_solution "Basic"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./FPGA_Convolution/Basic/directives.tcl"
csim_design -compiler gcc
csynth_design
cosim_design
export_design -format ip_catalog
