#include "Paddle.hpp"
#include "Vertex.hpp"

Paddle::Paddle() : _arr{},
	_buf{},
	_indices{ {0,1,3,1,2,3} },
	_pos{},
	_motion{},
	_rect{ new Insanity::TRectangle<float>{ -0.15f, -0.75f, 0.3f, 0.1f } }
{
	//only need the vertex data in the ctor, to initialize the buffer.
	vertex vertdata[4]{
		{
			{ -0.15f, 0.05f, 0.5f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 1.0f }
		},
		{
			{ 0.15f, 0.05f, 0.5f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 1.0f }
		},
		{
			{ 0.15f, -0.05f, 0.5f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 1.0f }
		},
		{
			{ -0.15f, -0.05f, 0.5f, 1.0f },
			{ 1.0f, 1.0f, 0.0f, 1.0f }
		}
	};
	_pos[0] = 0.0f;
	_pos[1] = -0.75f;

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
Paddle::~Paddle()
{
	glDeleteBuffers(1, &_buf);
	glDeleteVertexArrays(1, &_arr);
}

void Paddle::Draw()
{
	glUniform2fv(glGetUniformLocation(1, "pos"), 1, _pos);
	//prog->SetUniform("pos", _pos);
	glBindVertexArray(_arr);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, _indices.data());
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Paddle::Update()
{
	_pos[0] += _motion;

	_rect->SetX(_pos[0] - 0.15f);
}

void Paddle::Move(float x)
{
	_motion = x;
}

float Paddle::GetX() const
{
	return _pos[0];
}
void Paddle::SetX(float x)
{
	_pos[0] = x;
	_rect->SetX(x - 0.15f);
}

Insanity::TRectangle<float> const * Paddle::GetRect() const
{
	return _rect;
}

float Paddle::GetY() const
{
	return _pos[1];
}