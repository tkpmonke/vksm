#!/bin/sh

g++ vksm.cpp -I. -o vksm  -Ithird_party/shaderc/include -L third_party/shaderc/bin/libshaderc -l shaderc_combined
