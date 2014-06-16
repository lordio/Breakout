#include "Ball.hpp"
#include "Vertex.hpp"

Ball::Ball() : _arr{},
	_buf{},
	_indices{ { 0, 1, 3, 1, 2, 3 } },
	_pos{},
	_motion{},
	_rect{ new Insanity::TRectangle<float>{ -0.025f, -0.025f, 0.05f, 0.05f } } //normally a negative height wouldn't make sense, but it makes things work with OpenGL
{
	vertex vertdata[4]{
		{
			{ -0.025f, 0.025f, 0.5f, 1.0f },
			{ 0.5f, 1.0f, 0.5f, 1.0f }
		},
		{
			{ 0.025f, 0.025f, 0.5f, 1.0f },
			{ 0.5f, 1.0f, 0.5f, 1.0f }
		},
		{
			{ 0.025f, -0.025f, 0.5f, 1.0f },
			{ 0.5f, 1.0f, 0.5f, 1.0f }
		},
		{
			{ -0.025f, -0.025f, 0.5f, 1.0f },
			{ 0.5f, 1.0f, 0.5f, 1.0f }
		}
	};
	_pos[0] = 0.0f;
	_pos[1] = 0.0f;

	_motion[0] = 0.01f;
	_motion[1] = -0.01f;

	glGenVertexArrays(1, &_arr);
	glBindVertexArray(_arr);
	glGenBuffers(1, &_buf);
	glBindBuffer(GL_ARRAY_BUFFER, _buf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertdata), vertdata, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertdata[0]), reinterpret_cast<GLvoid const*>(offsetof(vertex, vert)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertdata[0]), reinterpret_cast<GLvoid const*>(offsetof(vertex, color)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Ball::~Ball()
{
	glDeleteBuffers(1, &_buf);
	glDeleteVertexArrays(1, &_arr);
}

void Ball::Draw(Insanity::IShaderProgram * prog)
{
	prog->SetUniform("pos", _pos);
	glBindVertexArray(_arr);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, _indices.data());
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
void Ball::Update()
{
	_pos[0] += _motion[0];
	_pos[1] += _motion[1];

	_rect->SetX(_pos[0] - 0.025f);
	_rect->SetY(_pos[1] + 0.025f);
}

float Ball::GetX() const
{
	return _pos[0];
}
float Ball::GetY() const
{
	return _pos[1];
}

void Ball::SetX(float x)
{
	_pos[0] = x;
	_rect->SetX(x - 0.05f);
}
void Ball::SetY(float y)
{
	_pos[1] = y;
	_rect->SetY(y + 0.05f);
}

void Ball::ReflectX()
{
	_motion[0] *= -1.0f;
}
void Ball::ReflectY()
{
	_motion[1] *= -1.0f;
}

Insanity::TRectangle<float> const * Ball::GetRect() const
{
	return _rect;
}

float Ball::GetMotionX() const
{
	return _motion[0];
}
float Ball::GetMotionY() const
{
	return _motion[1];
}

void Ball::SetMotionX(float x)
{
	_motion[0] = x;
}
void Ball::SetMotionY(float y)
{
	_motion[1] = y;
}