#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
private:
	/**
	 * Program ID generated at constructor.
	 */
	unsigned int ID;
public:

	/**
	 * Read and create ProgramID after compiling shaders from paths.
	 * @param vertexPath path to load vertex shader.
	 * @param fragmentPath path to load fragment shader.
	 */
	Shader(const char* vertexPath, const char* fragmentPath);

	/**
	 * Activate the shader.
	 */
	void use();

	/**
	 * Set a uniform bool variable's value.
	 * @param name variable's name.
	 * @param value varaible's new value.
	 */
	void setBool(const std::string& name, bool value) const;

	/**
	 * Set a uniform int variable's value.
	 * @param name variable's name.
	 * @param value varaible's new value.
	 */
	void setInt(const std::string& name, int value) const;

	/**
	 * Set a uniform float variable's value
	 * @param name variable's name
	 * @param value varaible's new value
	 */
	void setFloat(const std::string& name, float value) const;
};