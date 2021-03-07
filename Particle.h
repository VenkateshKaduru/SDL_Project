#pragma once

namespace venk {

	struct Particle{
		double m_x;
		double m_y;

		/*double m_xspeed;
		double m_yspeed;*/
	private:
		double m_speed;
		double m_direction;
	private:
		void init();

	public:
		Particle();
		virtual ~Particle();
		void update(int interval);
	};

}

