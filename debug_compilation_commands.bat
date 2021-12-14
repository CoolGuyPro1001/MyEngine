rm -rf build
mkdir build
cd build
cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Debug
mingw32-make -j5
cd ..

[OpenGL Error] D:\Development\C++\Edit64\Engine\src\Graphics\Graphics.cpp:182: Invalid Operation
glUseProgram(g_shader_programs[0])
[OpenGL Error] D:\Development\C++\Edit64\Engine\src\Graphics\Texture.cpp:181: Invalid Operation
glUniform1i(tex_uniform_id, 0)
[OpenGL Error] D:\Development\C++\Edit64\Engine\src\Graphics\Graphics.cpp:193: Invalid Operation
glUniform1i(object_num_uniform, object_count)
[OpenGL Error] D:\Development\C++\Edit64\Engine\src\Graphics\Graphics.cpp:193: Invalid Operation
glUniform1i(object_num_uniform, object_count)
[OpenGL Error] D:\Development\C++\Edit64\Engine\src\Graphics\Graphics.cpp:193: Invalid Operation
glUniform1i(object_num_uniform, object_count)
[OpenGL Error] D:\Development\C++\Edit64\Engine\src\Graphics\Graphics.cpp:201: Invalid Operation