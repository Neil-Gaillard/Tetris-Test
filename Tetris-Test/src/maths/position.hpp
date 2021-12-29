#pragma once

namespace maths {

	struct position
	{
	private:
		int m_pos_x_;
		int m_pos_y_;

	public:
		position();
		position(int x, int y);

		inline int get_x_pos() const { return this->m_pos_x_; }
		inline int get_y_pos() const { return this->m_pos_y_; }

		inline void set_x_pos(const int x) { this->m_pos_x_ = x; }
		inline void set_y_pos(const int y) { this->m_pos_y_ = y; }

		friend position operator+(position a, const position& b);
		friend position operator-(position a, const position& b);

		bool operator==(const position& pos) const;
		bool operator!=(const position& pos) const;

		position& operator+=(const position& pos);
		position& operator-=(const position& pos);

	private:
		position& add(const position& other);
		position& substract(const position& other);
	};

}