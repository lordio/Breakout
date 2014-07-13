#include "GameRenderer.hpp"
#include "GameWindow.hpp"

#include "Drawable.hpp"

#include <gel.hpp>
#include <TString.hpp>

#include <fstream>

#include <cassert>

namespace
{
	void _AddShader(GLuint program, GLenum shaderType, Insanity::String const& fileName)
	{
		GLuint shader{ glCreateShader(shaderType) };

		std::ifstream shaderFile{ fileName };
		assert(shaderFile);

		Insanity::String text{};
		{
			char tmp{};
			while ((tmp = shaderFile.get()) != EOF) text += tmp;
		}
		char const * ctext = text.c_str();
		glShaderSource(shader, 1, &ctext, nullptr);
		glCompileShader(shader);
		glAttachShader(program, shader);
		glDeleteShader(shader);
	}
}

GameRenderer::GameRenderer(GameWindow * win, Insanity::IConfigObject const * cfg) : Renderer{ win, cfg }, _clearColor{ { 0.0f, 0.0f, 0.0f, 0.0f } }
{
	GLuint shaderProgram = glCreateProgram();
	_AddShader(shaderProgram, GL_VERTEX_SHADER, "../../../bin/Win32/Debug/vtx.glsl");
	_AddShader(shaderProgram, GL_FRAGMENT_SHADER, "../../../bin/Win32/Debug/frg.glsl");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

GameRenderer::~GameRenderer()
{
}

void GameRenderer::Add(Drawable * draw)
{
	_drawList.push_back(draw);
}

void GameRenderer::Render()
{
	Renderer::Render();

	ClearColorBuffer(_clearColor.data());
	for (Drawable * d : _drawList) d->Draw();
}