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
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <mutex>

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
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

#endif //PCH_H