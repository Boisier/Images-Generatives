//
//  ShaderProgram.cpp
//  IMACMAN
//
//  Created by Valentin Dufois on 30/12/2017.
//  Copyright © 2017 Valentin Dufois. All rights reserved.
//

#include "ShaderProgram.hpp"

#include "Utils/ShaderProgram.hpp"
#include "Core/AppObject.hpp"
#include "Engines/RessourcesEngine/RessourcesEngine.hpp"
#include "Elements/Shader.hpp"

ShaderProgram::ShaderProgram(std::string vsPath, std::string fsPath): m_programID(glCreateProgram()), m_vsPath(vsPath), m_fsPath(fsPath)
{
	//Load shaders
	rId vsRId = App->ressourcesEngine->loadAsset(vsPath, SHADER);
	rId fsRId = App->ressourcesEngine->loadAsset(fsPath, SHADER);

	m_vsShader = *App->ressourcesEngine->getAsset(vsRId);
	m_fsShader = *App->ressourcesEngine->getAsset(fsRId);

	//Bind shaders
	glAttachShader(m_programID, m_vsShader->getShaderID());
	glAttachShader(m_programID, m_fsShader->getShaderID());

	//Compile program
	glLinkProgram(m_programID);

	GLint status;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &status);

	if(status != GL_TRUE)
	{
		//Compile error, display message
		throw std::runtime_error("Unable to compile program : " + getCompileLog());
		return;
	}
}

void ShaderProgram::use() const
{
	if(ShaderProgram::currentProgram == m_programID)
		return;

	glUseProgram(m_programID);
	ShaderProgram::currentProgram = m_programID;
}

//UNIFORMS
void ShaderProgram::setUniformMat4(const std::string &uniformName, const glm::mat4 &value)
{
	//The program needs to be binded in order to pass uniforms
	use();

	//Get location
	GLuint uniLoc = getUniformLocation(uniformName);

	//Pass uniform
	glUniformMatrix4fv(uniLoc, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniformUint(const std::string &uniformName, const uint &value)
{
	//The program needs to be binded in order to pass uniforms
	use();

	//Get location
	GLuint uniLoc = getUniformLocation(uniformName);


	//Pass uniform
	glUniform1i(uniLoc, value);
}


GLuint ShaderProgram::getUniformLocation(const std::string &uniformName)
{
	//Is this uniform already located ?
	if(m_uniformLocations.find(uniformName) != m_uniformLocations.end())
		return m_uniformLocations[uniformName];

	GLuint uniLoc = glGetUniformLocation(m_programID, uniformName.c_str());
	m_uniformLocations.insert(std::pair<std::string, GLuint>(uniformName, uniLoc));

	return uniLoc;
}


const std::string ShaderProgram::getCompileLog() const
{
	GLint length;
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &length);
	char* log = new char[length];

	glGetProgramInfoLog(m_programID, length, 0, log);

	std::string logString(log);
	delete [] log;

	return logString;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_programID);
}

GLuint ShaderProgram::currentProgram = 0;
