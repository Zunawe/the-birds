#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <map>
#include <string>
#include <vector>

#include "material.h"
#include "mesh.h"
#include "renderer.h"

Renderer loadObj(const char *filepath);
void loadObj(const char *filepath, Renderer &renderer);
Mesh loadMeshFromObj(const char *filepath);
Mesh loadMeshFromObj(const char *filepath, std::vector<unsigned int> &materialIndices);
Mesh loadMeshFromObj(const char *filepath, std::vector<unsigned int> &materialIndices, std::vector<Material> &materials);
std::map<std::string, Material> loadMaterialsFromMtl(const char *filepath);

template<typename Out>
void split(const std::string &s, char delim, Out result);
std::vector<std::string> split(const std::string &s, char delim);
void trim(std::string &s);

#endif
