#pragma once

#include "grafik.h"


class Test : public grafik::Listener
{
public:
	Test() : Listener()
	{
		m_x_old = 0;
		m_y_old = 0;

		m_pos_x = 0;
		m_pos_y = 0;
	}

	void onEvent(void* data) override;
	void onEvent() override;
private:
	bool m_init = false;

	int m_x_old;
	int m_y_old;

	float m_pos_x;
	float m_pos_y;

};

