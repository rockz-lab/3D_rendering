#pragma once

#include "grafik.h"


 struct collisionData : public grafik::eventData
{
	collisionData() : eventData()
	{
		type = grafik::COLLISION;
	}

	float set_pos[2];
	float pos[2];
};

class testPoint : public grafik::GameObject
{
public:
	testPoint() : GameObject()
	{
		m_cursor_x_old = 0;
		m_cursor_y_old = 0;

		m_pos_x = 0;
		m_pos_y = 0;
	}

	void onEvent(void* data) override;
	void onEvent() override;

	void getPos(float& x, float& y)
	{
		x = m_pos_x;
		y = m_pos_y;
	}
	void getPrevPos(float& x, float& y)
	{
		x = m_prevPos_x;
		y = m_prevPos_y;
	}

private:
	void onMouseMove(void* data);
	
	bool m_init = false;

	int m_cursor_x_old;
	int m_cursor_y_old;

	float m_pos_x;
	float m_pos_y;

	float m_prevPos_x;
	float m_prevPos_y;

	float m_speed = 1.23;
};

struct Bounds
{
	int x_min;
	int x_max;

	int y_min;
	int y_max;
};

class testBounds : public grafik::eventNode
{
public:
	testBounds(Bounds& bounds) : eventNode()
	{
		m_bounds = bounds;
	}

	void addCollider(testPoint* point)
	{
		m_colliders.push_back(point);
	}

	void checkColls()
	{
		for (auto& col : m_colliders)
		{
			float x_query;
			float y_query;
			col->getPos(x_query, y_query);

			if (   x_query < m_bounds.x_min
				|| x_query > m_bounds.x_max
				|| y_query < m_bounds.y_min
				|| y_query > m_bounds.y_max )
			{
				// send an event

				collisionData data;
				data.type = grafik::COLLISION;

				// current position
				data.pos[0] = x_query;
				data.pos[1] = y_query;

				x_query = (x_query < m_bounds.x_min) ? m_bounds.x_min : x_query;
				x_query = (x_query > m_bounds.x_max) ? m_bounds.x_max : x_query;
				y_query = (y_query < m_bounds.y_min) ? m_bounds.y_min : y_query;
				y_query = (y_query > m_bounds.y_max) ? m_bounds.y_max : y_query;

				data.set_pos[0] = x_query;
				data.set_pos[1] = y_query;
				// previous position
				//float xPrev, yPrev;
				//col->getPrevPos(xPrev, yPrev);
				publishEvent(&data);

			}
		}
	}
private:
	std::vector<testPoint*> m_colliders;
	Bounds m_bounds;
};

