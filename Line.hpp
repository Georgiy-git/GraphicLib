#pragma once

#include "Panel.hpp"


/* ��������� ������.
* ��� ����������� ���������� �����.
*/

class Line : public Panel
{
public:
	Line(const std::string& line, SDL_Renderer* render, float corner_x, float corner_y,
		float multiplier = 1,
		float distance = 5, float distance_of_border_w = 20, float distance_of_border_h = 20);

	void event_process(SDL_Event* event) override;

	// ���������� �����, ������ ������.
	void set_text(const std::string& text);

	// �������� ����� � ��� �������������.
	void append_text(const std::string& text);

	// �������� ����� ������.
	const std::string& get_text();

	// ���������� ����� ��� ���� �����.
	static void set_font(SDL_Texture* font);

	// ���������� ����� �� ���������.
	// ���������� ��������� �� ���� �����, ���������� ��� ��������
	// �� ������������ ������ ��� �������������.
	static SDL_Texture* set_default_font(SDL_Renderer* render);

	// ���������� ����������� ����� ��� ���� ������.
	void set_special_font(SDL_Texture* font);

private:
	static inline SDL_Texture* font;

	SDL_Texture* special_font = nullptr;

	float multiplier;
	std::string line;
	int symbol_w = 60;
	int symbol_h = 100;
};

