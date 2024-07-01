#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string.h>

#define VKSM_VERTEX_DEFINITION_TOKEN std::string("#vert")
#define VKSM_FRAGMENT_DEFINITION_TOKEN std::string("#frag")
#define VKSM_SHADER_END_TOKEN '~'


void vksmInterpretShaderFile(const char* location);
void vksmCompile(std::string vert, std::string frag, std::string name);
