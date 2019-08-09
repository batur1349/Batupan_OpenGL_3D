#ifndef PCH_H
#define PCH_H

// System Includes
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <map>

// GLEW Includes
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW Includes
#include <GLFW/glfw3.h>

// Other Includes
#include <SOIL2.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

// GLM Mathematics Includes
#define GLM_FORCE_CTOR_INIT
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#endif //PCH_H