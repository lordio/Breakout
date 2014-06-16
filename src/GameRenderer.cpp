#include "GameRenderer.hpp"
#include "GameWindow.hpp"

#include "Drawable.hpp"

GameRenderer::GameRenderer(GameWindow * win, Insanity::IConfigObject const * cfg) : Renderer{ win, cfg }, _clearColor{ { 0.0f, 0.0f, 0.0f, 0.0f } }, _prog{ CreateShaderProgram() }
{
	_prog->AddShader(Insanity::EShaderType::Vertex, "vtx.glsl");
	_prog->AddShader(Insanity::EShaderType::Fragment, "frg.glsl");
	UseShaderProgram(_prog);
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
	for (Drawable * d : _drawList) d->Draw(_prog);
}