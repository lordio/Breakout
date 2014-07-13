#include "Brick.hpp"
#include "Vertex.hpp"

Brick::Brick() :
	_arr{},
	_buf{},
	_indices{ { 0, 1, 3, 1, 2, 3 } },
	_rect{ new Insanity::TRectangle<float>{ 0.0f, 0.0f, 0.3f, 0.1f } },
	_instState{}
{
	//gradient-shaded to tell where each brick begins and ends.
	vertex vertdata[4]{
		{
			{ -0.15f, 0.05f, 0.5f, 1.0f },
			{ 0.5f, 0.0f, 0.0f, 1.0f }
		},
		{
			{ 0.15f, 0.05f, 0.5f, 1.0f },
			{ 0.75f, 0.0f, 0.0f, 1.0f }
		},
		{
			{ 0.15f, -0.05f, 0.5f, 1.0f },
			{ 1.0f, 0.0f, 0.0f, 1.0f }
		},
		{
			{ -0.15f, -0.05f, 0.5f, 1.0f },
			{ 0.5f, 0.0f, 0.0f, 1.0f }
		}
	};

	glGenVertexArrays(1, &_arr);
	glBindVertexArray(_arr);
	glGenBuffers(1, &_buf);
	glBindBuffer(GL_ARRAY_BUFFER, _buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertdata), vertdata, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<GLvoid const*>(offsetof(vertex, vert)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), reinterpret_cast<GLvoid const*>(offsetof(vertex, color)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Brick::~Brick()
{
	glDeleteBuffers(1, &_buf);
	glDeleteVertexArrays(1, &_arr);
}

void Brick::SetBrickState(BrickState const * state)
{
	_instState = state;

	if (_instState)
	{
		_rect->SetX(_instState->pos[0]  - (_rect->GetWidth() / 2));
		_rect->SetY(_instState->pos[1]);
	}
}
void Brick::Draw()
{
	//if no state is set, or the brick is inactive, don't draw anything.
	if (!_instState || !_instState->active) return;

	glUniform2fv(glGetUniformLocation(1, "pos"), 1, _instState->pos);
	//prog->SetUniform("pos", _instState->pos);
	glBindVertexArray(_arr);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, _indices.data());
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

Insanity::TRectangle<float> const * Brick::GetRect() const
{
	return _rect;
}

float Brick::GetWidth() const
{
	return 0.3f;
}
float Brick::GetHeight() const
{
	return 0.1f;
}