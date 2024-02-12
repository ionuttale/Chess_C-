#include "SFML/Graphics.hpp"
#include<iostream>
#include<fstream>
#include<time.h>
#include<dos.h>
#include<cstdlib>
#include<stdlib.h>
#include<string.h>

using namespace sf;

std::fstream fin("tabla.in", std::ios::in);

Text s_mat;

int tabla[8][8], tur;  //tur==0 => albele |   | tur==2 => negrele
int x1_rege, y1_rege, x2_rege, y2_rege;  //pozitiile regilor
bool sah_mat1 = false, sah_mat2 = false, k = true;

#define turn_n -1
#define cal_n -2
#define nebun_n -3
#define regina_n -4
#define rege_n -5
#define pion_n -6

#define turn_a 1
#define cal_a 2
#define nebun_a 3
#define regina_a 4
#define rege_a 5
#define pion_a 6

RenderWindow window(VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "The Chess!", Style::Fullscreen);
//RenderWindow window(VideoMode(1366, 768), "The Chess!", Style::Fullscreen);

void tabla_init();

void afisare();

void asezare1();
void asezare2();

//Copiere matrice pentru a stabili ce mutari blocheaza sahul. Daca nu exista nicio mutare, atunci jocul se incheie.

bool sah(int x, int y, int xp, int yp, int val1, int val) {
	bool k;
	k = false;
	int a, b;
	a = tabla[y][x];
	b = tabla[yp][xp];
	tabla[yp][xp] = val1;
	tabla[y][x] = val;
	//std::cout << "\nS:" << x << y << '\n';
	//pioni
	if ((tabla[y - 1][x - 1] == pion_n || tabla[y - 1][x + 1] == pion_n) && tabla[y][x] == rege_a)
		k = true;
	if ((tabla[y + 1][x - 1] == pion_a || tabla[y + 1][x + 1] == pion_a) && tabla[y][x] == rege_n)
		k = true;
	//pioni

	//cal
	if ((tabla[y + 1][x - 2] == cal_n || tabla[y + 2][x - 1] == cal_n || tabla[y + 2][x + 1] == cal_n || tabla[y + 1][x + 2] == cal_n || tabla[y - 1][x + 2] == cal_n || tabla[y - 2][x + 1] == cal_n || tabla[y - 2][x - 1] == cal_n || tabla[y - 1][x - 2] == cal_n) && tabla[y][x] == rege_a)
		k = true;
	if ((tabla[y + 1][x - 2] == cal_a || tabla[y + 2][x - 1] == cal_a || tabla[y + 2][x + 1] == cal_a || tabla[y + 1][x + 2] == cal_a || tabla[y - 1][x + 2] == cal_a || tabla[y - 2][x + 1] == cal_a || tabla[y - 2][x - 1] == cal_a || tabla[y - 1][x - 2] == cal_a) && tabla[y][x] == rege_n)
		k = true;
	//cal

	//turn
		//negru
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && tabla[y - 1 - i][x] == turn_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y - i - 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && tabla[y + 1 + i][x] == turn_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y + i + 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x - 1 - i >= 0 && tabla[y][x - 1 - i] == turn_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x + 1 + i <= 7 && tabla[y][x + 1 + i] == turn_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y][x + 1 + i] != 0)
				break;
		//negru
		//alb
	for (int i = 0; i <= 6; i++) 
		if (y - 1 - i >= 0 && tabla[y - 1 - i][x] == turn_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y - i - 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && tabla[y + 1 + i][x] == turn_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y - i - 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x - 1 - i >= 0 && tabla[y][x - 1 - i] == turn_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x + 1 + i <= 7 && tabla[y][x + 1 + i] == turn_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y][x + 1 + i] != 0)
				break;
		//alb
	//turn
	
	//nebun
		//negru
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x - 1 - i >= 0 && tabla[y - 1 - i][x - 1 - i] == nebun_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y - i - 1][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x - 1 - i >= 0 && tabla[y + 1 + i][x - 1 - i] == nebun_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y + i + 1][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x + 1 + i <= 7 && tabla[y - 1 - i][x + 1 + i] == nebun_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y - 1 - i][x + 1 + i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x + 1 + i <= 7 && tabla[y + 1 + i][x + 1 + i] == nebun_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y + 1 + i][x + 1 + i] != 0)
				break;
		//negru
		//alb
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x - 1 - i >= 0 && tabla[y - 1 - i][x - 1 - i] == nebun_a && tabla[y][x] == rege_n)
			k = true;
	else
		if (tabla[y - i - 1][x - 1 - i] != 0)
			break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x - 1 - i >= 0 && tabla[y + 1 + i][x - 1 - i] == nebun_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y + i + 1][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x + 1 + i <= 7 && tabla[y - 1 - i][x + 1 + i] == nebun_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y - 1 - i][x + 1 + i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x + 1 + i <= 7 && tabla[y + 1 + i][x + 1 + i] == nebun_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y + 1 + i][x + 1 + i] != 0)
				break;
		//alb
	//nebun

	//regina
		//neagra
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && tabla[y - 1 - i][x] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y - i - 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && tabla[y + 1 + i][x] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y + i + 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x - 1 - i >= 0 && tabla[y][x - 1 - i] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x + 1 + i <= 7 && tabla[y][x + 1 + i] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y][x + 1 + i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x - 1 - i >= 0 && tabla[y - 1 - i][x - 1 - i] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y - i - 1][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x - 1 - i >= 0 && tabla[y + 1 + i][x - 1 - i] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y + i + 1][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x + 1 + i <= 7 && tabla[y - 1 - i][x + 1 + i] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y - 1 - i][x + 1 + i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x + 1 + i <= 7 && tabla[y + 1 + i][x + 1 + i] == regina_n && tabla[y][x] == rege_a)
			k = true;
		else
			if (tabla[y + 1 + i][x + 1 + i] != 0)
				break;
		//neagra
		//alba
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && tabla[y - 1 - i][x] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y - i - 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && tabla[y + 1 + i][x] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y + i + 1][x] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x - 1 - i >= 0 && tabla[y][x - 1 - i] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (x + 1 + i <= 7 && tabla[y][x + 1 + i] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y][x + 1 + i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x - 1 - i >= 0 && tabla[y - 1 - i][x - 1 - i] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y - i - 1][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x - 1 - i >= 0 && tabla[y + 1 + i][x - 1 - i] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y + i + 1][x - 1 - i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y - 1 - i >= 0 && x + 1 + i <= 7 && tabla[y - 1 - i][x + 1 + i] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y - 1 - i][x + 1 + i] != 0)
				break;
	for (int i = 0; i <= 6; i++)
		if (y + 1 + i <= 7 && x + 1 + i <= 7 && tabla[y + 1 + i][x + 1 + i] == regina_a && tabla[y][x] == rege_n)
			k = true;
		else
			if (tabla[y + 1 + i][x + 1 + i] != 0)
				break;
		//alba
	//regina
	tabla[y][x] = a;
	tabla[yp][xp] = b;
	return k;
}

bool mutare_valida(int x, int y, int prevx, int prevy);

void posibilitati2(int prevx, int prevy) {
	int x, y;
	if (tur == 0) {
		switch (tabla[prevy][prevx]) {
		case pion_a:
			if (mutare_valida(prevx, prevy - 1, prevx, prevy)) {
				x = prevx;
				y = prevy - 1;
				//std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			if (mutare_valida(prevx, prevy - 2, prevx, prevy)) {
				x = prevx;
				y = prevy - 2;
				//std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			if (mutare_valida(prevx - 1, prevy - 1, prevx, prevy)) {
				x = prevx - 1;
				y = prevy - 1;
				//std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			if (mutare_valida(prevx + 1, prevy - 1, prevx, prevy)) {
				x = prevx + 1;
				y = prevy - 1;
			//	std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			break;
		case turn_a:
			for (int i = 1; i <= 7; i++) {
				if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
					x = prevx + i;
					y = prevy;
			//		std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
					x = prevx - i;
					y = prevy;
			//		std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
					x = prevx;
					y = prevy + i;
			//		std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
					x = prevx;
					y = prevy - i;
			//		std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			break;
		case cal_a:
			if (mutare_valida(prevx - 1, prevy - 2, prevx, prevy)) {
				x = prevx - 1;
				y = prevy - 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy - 2, prevx, prevy)) {
				x = prevx + 1;
				y = prevy - 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 1, prevy + 2, prevx, prevy)) {
				x = prevx - 1;
				y = prevy + 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy + 2, prevx, prevy)) {
				x = prevx + 1;
				y = prevy + 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 2, prevy - 1, prevx, prevy)) {
				x = prevx - 2;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 2, prevy - 1, prevx, prevy)) {
				x = prevx + 2;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 2, prevy + 1, prevx, prevy)) {
				x = prevx - 2;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 2, prevy + 1, prevx, prevy)) {
				x = prevx + 2;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			break;
		case nebun_a:
			for (int i = 1; i <= 7; i++) {
				if (prevx - i >= 0 && prevy - i >= 0) {
					if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
						x = prevx - i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx - i >= 0 && prevy + i <= 7) {
					if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
						x = prevx - i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy - i >= 0) {
					if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
						x = prevx + i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy + i <= 7) {
					if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
						x = prevx + i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
			}
			break;
		case regina_a:
			for (int i = 1; i <= 7; i++) {
				if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
					x = prevx + i;
					y = prevy;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
					x = prevx - i;
					y = prevy;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
					x = prevx;
					y = prevy + i;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
					x = prevx;
					y = prevy - i;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevx - i >= 0 && prevy - i >= 0) {
					if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
						x = prevx - i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx - i >= 0 && prevy + i <= 7) {
					if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
						x = prevx - i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy - i >= 0) {
					if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
						x = prevx + i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy + i <= 7) {
					if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
						x = prevx + i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
			}
			break;
		case rege_a:
			if (mutare_valida(prevx - 1, prevy, prevx, prevy)) {
				x = prevx - 1;
				y = prevy;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 1, prevy - 1, prevx, prevy)) {
				x = prevx - 1;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx, prevy - 1, prevx, prevy)) {
				x = prevx;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy - 1, prevx, prevy)) {
				x = prevx + 1;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy, prevx, prevy)) {
				x = prevx + 1;
				y = prevy;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy + 1, prevx, prevy)) {
				x = prevx + 1;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx, prevy + 1, prevx, prevy)) {
				x = prevx;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 1, prevy + 1, prevx, prevy)) {
				x = prevx - 1;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			break;
		}
	}
	if (tur == 1) {
		switch (tabla[prevy][prevx]) {
		case pion_n:
			if (mutare_valida(prevx, prevy + 1, prevx, prevy)) {
				x = prevx;
				y = prevy + 1;
				std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			if (mutare_valida(prevx, prevy + 2, prevx, prevy)) {
				x = prevx;
				y = prevy + 2;
				std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			if (mutare_valida(prevx - 1, prevy + 1, prevx, prevy)) {
				x = prevx - 1;
				y = prevy + 1;
				std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			if (mutare_valida(prevx + 1, prevy + 1, prevx, prevy)) {
				x = prevx + 1;
				y = prevy + 1;
				std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
				y = 80 + y * 74;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
			}
			break;
		case turn_n:
			for (int i = 1; i <= 7; i++) {
				if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
					x = prevx + i;
					y = prevy;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
					x = prevx - i;
					y = prevy;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
					x = prevx;
					y = prevy + i;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
					x = prevx;
					y = prevy - i;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			break;
		case cal_n:
			if (mutare_valida(prevx - 1, prevy - 2, prevx, prevy)) {
				x = prevx - 1;
				y = prevy - 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy - 2, prevx, prevy)) {
				x = prevx + 1;
				y = prevy - 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 1, prevy + 2, prevx, prevy)) {
				x = prevx - 1;
				y = prevy + 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy + 2, prevx, prevy)) {
				x = prevx + 1;
				y = prevy + 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 2, prevy - 1, prevx, prevy)) {
				x = prevx - 2;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 2, prevy - 1, prevx, prevy)) {
				x = prevx + 2;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 2, prevy + 1, prevx, prevy)) {
				x = prevx - 2;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 2, prevy + 1, prevx, prevy)) {
				x = prevx + 2;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			break;
		case nebun_n:
			for (int i = 1; i <= 7; i++) {
				if (prevx - i >= 0 && prevy - i >= 0) {
					if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
						x = prevx - i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx - i >= 0 && prevy + i <= 7) {
					if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
						x = prevx - i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy - i >= 0) {
					if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
						x = prevx + i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy + i <= 7) {
					if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
						x = prevx + i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
			}
			break;
		case regina_n:
			for (int i = 1; i <= 7; i++) {
				if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
					x = prevx + i;
					y = prevy;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
					x = prevx - i;
					y = prevy;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
					x = prevx;
					y = prevy + i;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
					x = prevx;
					y = prevy - i;
					std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
				if (prevx - i >= 0 && prevy - i >= 0) {
					if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
						x = prevx - i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx - i >= 0 && prevy + i <= 7) {
					if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
						x = prevx - i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy - i >= 0) {
					if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
						x = prevx + i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
				if (prevx + i <= 7 && prevy + i <= 7) {
					if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
						x = prevx + i;
						y = prevy + i;
						x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
						y = 80 + y * 74;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
				}
			}
			break;
		case rege_n:
			if (mutare_valida(prevx - 1, prevy, prevx, prevy)) {
				x = prevx - 1;
				y = prevy;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 1, prevy - 1, prevx, prevy)) {
				x = prevx - 1;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx, prevy - 1, prevx, prevy)) {
				x = prevx;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy - 1, prevx, prevy)) {
				x = prevx + 1;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy, prevx, prevy)) {
				x = prevx + 1;
				y = prevy;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx + 1, prevy + 1, prevx, prevy)) {
				x = prevx + 1;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx, prevy + 1, prevx, prevy)) {
				x = prevx;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			if (mutare_valida(prevx - 1, prevy + 1, prevx, prevy)) {
				x = prevx - 1;
				y = prevy + 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 340) + (x * 74);
					y = 80 + y * 74;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
				}
			}
			break;
		}
	}
	window.display();
}

void posibilitati1(int prevx, int prevy, bool desenare) {
	int x, y;
	sah_mat1 = true; //albe
	sah_mat2 = true; //negre
	if(tur==0){
		switch (tabla[prevy][prevx]) {
		case pion_a:
			if (mutare_valida(prevx, prevy - 1, prevx, prevy)) {
				x = prevx;
				y = prevy - 1;
				//std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
				y = 120 + y * 85;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
				sah_mat1 = false;
			}
			if (mutare_valida(prevx, prevy - 2, prevx, prevy)) {
				x = prevx;
				y = prevy - 2;
				std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
				y = 120 + y * 85;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
				sah_mat1 = false;
			}
			if (prevx - 1 >= 0 && prevx + 1 <= 7) {
				if (mutare_valida(prevx - 1, prevy - 1, prevx, prevy)) {
					x = prevx - 1;
					y = prevy - 1;
					//std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (mutare_valida(prevx + 1, prevy - 1, prevx, prevy)) {
					x = prevx + 1;
					y = prevy - 1;

					//std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			break;
		case turn_a:
			for (int i = 1; i <= 7; i++) {
				if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
					x = prevx + i;
					y = prevy;
					//	std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
					x = prevx - i;
					y = prevy;

					//	std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
					x = prevx;
					y = prevy + i;

					//	std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
					x = prevx;
					y = prevy - i;

					//	std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			break;
		case cal_a:
			if (mutare_valida(prevx - 1, prevy - 2, prevx, prevy)) {
				x = prevx - 1;
				y = prevy - 2;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx + 1, prevy - 2, prevx, prevy)) {
				x = prevx + 1;
				y = prevy - 2;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx - 1, prevy + 2, prevx, prevy)) {
				x = prevx - 1;
				y = prevy + 2;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx + 1, prevy + 2, prevx, prevy)) {
				x = prevx + 1;
				y = prevy + 2;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx - 2, prevy - 1, prevx, prevy)) {
				x = prevx - 2;
				y = prevy - 1;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx + 2, prevy - 1, prevx, prevy)) {
				x = prevx + 2;
				y = prevy - 1;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx - 2, prevy + 1, prevx, prevy)) {
				x = prevx - 2;
				y = prevy + 1;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx + 2, prevy + 1, prevx, prevy)) {
				x = prevx + 2;
				y = prevy + 1;

				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			break;
		case nebun_a:
			for (int i = 1; i <= 7; i++) {
				if (prevx - i >= 0 && prevy - i >= 0) {
					if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
						x = prevx - i;
						y = prevy - i;

						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (prevx - i >= 0 && prevy + i <= 7) {
					if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
						x = prevx - i;
						y = prevy + i;

						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (prevx + i <= 7 && prevy - i >= 0) {
					if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
						x = prevx + i;
						y = prevy - i;

						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (prevx + i <= 7 && prevy + i <= 7) {
					if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
						x = prevx + i;
						y = prevy + i;

						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
			}
			break;
		case regina_a:
			for (int i = 1; i <= 7; i++) {
				if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
					x = prevx + i;
					y = prevy;

					//std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
					x = prevx - i;
					y = prevy;

					//std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
					x = prevx;
					y = prevy + i;

					//std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
					x = prevx;
					y = prevy - i;

					//	std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
				if (prevx - i >= 0 && prevy - i >= 0) {
					if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
						x = prevx - i;
						y = prevy - i;
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (prevx - i >= 0 && prevy + i <= 7) {
					if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
						x = prevx - i;
						y = prevy + i;

						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (prevx + i <= 7 && prevy - i >= 0) {
					if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
						x = prevx + i;
						y = prevy - i;

						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (prevx + i <= 7 && prevy + i <= 7) {
					if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
						x = prevx + i;
						y = prevy + i;

						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
			}
			break;
		case rege_a:
			if (mutare_valida(prevx - 1, prevy, prevx, prevy)) { //&& !sah(prevx-1, prevy)) {
				x = prevx - 1;
				y = prevy;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx - 1, prevy - 1, prevx, prevy)) {// && !sah(prevx - 1, prevy - 1)) {
				x = prevx - 1;
				y = prevy - 1;
				if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat1 = false;
				}
			}
			if (mutare_valida(prevx, prevy - 1, prevx, prevy)){ //&& !sah(prevx, prevy-1)) {
					x = prevx;
					y = prevy - 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (mutare_valida(prevx + 1, prevy - 1, prevx, prevy)){// && !sah(prevx + 1, prevy - 1)) {
					x = prevx + 1;
					y = prevy - 1;
						if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
								y = 120 + y * 85;
								CircleShape circle(150);
								circle.setRadius(10);
								circle.setPosition(x, y);
								circle.setFillColor(Color(0, 255, 127, 250));
								window.draw(circle);
								sah_mat1 = false;
						}
				}
				if (mutare_valida(prevx+1, prevy, prevx, prevy)){// && !sah(prevx + 1, prevy)) {
					x = prevx + 1;
					y = prevy;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (mutare_valida(prevx + 1, prevy + 1, prevx, prevy)){// && !sah(prevx + 1, prevy + 1)) {
					x = prevx + 1;
					y = prevy + 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (mutare_valida(prevx, prevy + 1, prevx, prevy)){// && !sah(prevx, prevy + 1)) {
					x = prevx;
					y = prevy + 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				if (mutare_valida(prevx - 1, prevy + 1, prevx, prevy)){// && !sah(prevx - 1, prevy + 1)) {
					x = prevx - 1;
					y = prevy + 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat1 = false;
					}
				}
				break;
			}
		}
	if (tur == 1) {
		switch (tabla[prevy][prevx]) {
		case pion_n:
			if (mutare_valida(prevx, prevy + 1, prevx, prevy)) {
				x = prevx;
				y = prevy + 1;
				//std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
				y = 120 + y * 85;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
				sah_mat2 = false;
			}
			if (mutare_valida(prevx, prevy + 2, prevx, prevy)) {
				x = prevx;
				y = prevy + 2;
				//std::cout << x << y << '\n';
				x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
				y = 120 + y * 85;
				CircleShape circle(150);
				circle.setRadius(10);
				circle.setPosition(x, y);
				circle.setFillColor(Color(0, 255, 127, 250));
				window.draw(circle);
				sah_mat2 = false;
			}
			if (prevx - 1 >= 0 && prevx + 1 <= 7) {
				if (mutare_valida(prevx - 1, prevy + 1, prevx, prevy)) {
					x = prevx - 1;
					y = prevy + 1;

				//	std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat2 = false;
				}
				if (mutare_valida(prevx + 1, prevy + 1, prevx, prevy)) {
					x = prevx + 1;
					y = prevy + 1;

					//std::cout << x << y << '\n';
					x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
					y = 120 + y * 85;
					CircleShape circle(150);
					circle.setRadius(10);
					circle.setPosition(x, y);
					circle.setFillColor(Color(0, 255, 127, 250));
					window.draw(circle);
					sah_mat2 = false;
				}
			}	
			break;
			case turn_n:
				for (int i = 1; i <= 7; i++) {
					if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
						x = prevx + i;
						y = prevy;

					//	std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
					if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
						x = prevx - i;
						y = prevy;

					//	std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
					if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
						x = prevx;
						y = prevy + i;

					//	std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
					}
					if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
						x = prevx;
						y = prevy - i;

						//std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				break;
			case cal_n:
				if (mutare_valida(prevx - 1, prevy - 2, prevx, prevy)) {
					x = prevx - 1;
					y = prevy - 2;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx + 1, prevy - 2, prevx, prevy)) {
					x = prevx + 1;
					y = prevy - 2;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx - 1, prevy + 2, prevx, prevy)) {
					x = prevx - 1;
					y = prevy + 2;

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx + 1, prevy + 2, prevx, prevy)) {
					x = prevx + 1;
					y = prevy + 2;

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx - 2, prevy - 1, prevx, prevy)) {
					x = prevx - 2;
					y = prevy - 1;

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx + 2, prevy - 1, prevx, prevy)) {
					x = prevx + 2;
					y = prevy - 1;

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx - 2, prevy + 1, prevx, prevy)) {
					x = prevx - 2;
					y = prevy + 1;

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx + 2, prevy + 1, prevx, prevy)) {
					x = prevx + 2;
					y = prevy + 1;

					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				break;
			case nebun_n:
				for (int i = 1; i <= 7; i++) {
					if (prevx - i >= 0 && prevy - i >= 0) {
						if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
							x = prevx - i;
							y = prevy - i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
					if (prevx - i >= 0 && prevy + i <= 7) {
						if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
							x = prevx - i;
							y = prevy + i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
					if (prevx + i <= 7 && prevy - i >= 0) {
						if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
							x = prevx + i;
							y = prevy - i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
					if (prevx + i <= 7 && prevy + i <= 7) {
						if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
							x = prevx + i;
							y = prevy + i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
				}
				break;
			case regina_n:
				for (int i = 1; i <= 7; i++) {
					if (prevx + i <= 7 && mutare_valida(prevx + i, prevy, prevx, prevy)) {
						x = prevx + i;
						y = prevy;

						//std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
					if (prevx - i >= 0 && mutare_valida(prevx - i, prevy, prevx, prevy)) {
						x = prevx - i;
						y = prevy;

						//std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
					if (prevy + i <= 7 && mutare_valida(prevx, prevy + i, prevx, prevy)) {
						x = prevx;
						y = prevy + i;

					//	std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
					if (prevy - i >= 0 && mutare_valida(prevx, prevy - i, prevx, prevy)) {
						x = prevx;
						y = prevy - i;

					//	std::cout << x << y << '\n';
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
					if (prevx - i >= 0 && prevy - i >= 0) {
						if (mutare_valida(prevx - i, prevy - i, prevx, prevy)) {
							x = prevx - i;
							y = prevy - i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
					if (prevx - i >= 0 && prevy + i <= 7) {
						if (mutare_valida(prevx - i, prevy + i, prevx, prevy)) {
							x = prevx - i;
							y = prevy + i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
					if (prevx + i <= 7 && prevy - i >= 0) {
						if (mutare_valida(prevx + i, prevy - i, prevx, prevy)) {
							x = prevx + i;
							y = prevy - i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
					if (prevx + i <= 7 && prevy + i <= 7) {
						if (mutare_valida(prevx + i, prevy + i, prevx, prevy)) {
							x = prevx + i;
							y = prevy + i;

							x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
							y = 120 + y * 85;
							CircleShape circle(150);
							circle.setRadius(10);
							circle.setPosition(x, y);
							circle.setFillColor(Color(0, 255, 127, 250));
							window.draw(circle);
							sah_mat2 = false;
						}
					}
				}
				break;
			case rege_n:
				if (mutare_valida(prevx - 1, prevy, prevx, prevy)){ //&& !sah(prevx-1, prevy )) {
					x = prevx - 1;
					y = prevy;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx - 1, prevy - 1, prevx, prevy)){// && !sah(prevx-1, prevy-1)) {
					x = prevx - 1;
					y = prevy - 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx, prevy - 1, prevx, prevy)){ //&& !sah(prevx, prevy-1)) {
					x = prevx;
					y = prevy - 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx + 1, prevy - 1, prevx, prevy)){// && !sah(prevx+1, prevy-1)) {
					x = prevx + 1;
					y = prevy - 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx + 1, prevy, prevx, prevy)){// && !sah(prevx+1, prevy)) {
					x = prevx + 1;
					y = prevy;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx + 1, prevy + 1, prevx, prevy)){// && !sah(prevx+1, prevy+1)) {
					x = prevx + 1;
					y = prevy + 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx, prevy + 1, prevx, prevy)){ //&& !sah(prevx, prevy+1)) {
					x = prevx;
					y = prevy + 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				if (mutare_valida(prevx - 1, prevy + 1, prevx, prevy)){// && !sah(prevx-1, prevy+1)) {
					x = prevx - 1;
					y = prevy + 1;
					if (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
						x = (VideoMode::getDesktopMode().width / 2 - 330) + (x * 85);
						y = 120 + y * 85;
						CircleShape circle(150);
						circle.setRadius(10);
						circle.setPosition(x, y);
						circle.setFillColor(Color(0, 255, 127, 250));
						window.draw(circle);
						sah_mat2 = false;
					}
				}
				break;
		}
	}
	if(desenare)
		window.display();
}

/*bool verificare() {
	k = false;
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++) {
			if (tur == 0 && tabla[i][j] > 0) {
				switch (tabla[i][j]) {
				case pion_a:
					if (mutare_valida(j, i - 1, j, i))
						sah_mat1 = false;
					if (mutare_valida(j, i - 2, j, i))
						sah_mat1 = false;
					if (j - 1 >= 0 && j + 1 <= 7) {
						if (mutare_valida(j - 1, i - 1, j, i))
							sah_mat1 = false;
						if (mutare_valida(j + 1, i - 1, j, i))
							sah_mat1 = false;
					}
					break;
				case turn_a:
					for (int p = 1; p <= 7; p++) {
						if (j + p <= 7 && mutare_valida(j + p, i, j, i))
							sah_mat1 = false;
						if (j - p >= 0 && mutare_valida(j - p, i, j, i))
							sah_mat1 = false;
						if (i + p <= 7 && mutare_valida(j, i + p, j, i))
							sah_mat1 = false;
						if (i - p >= 0 && mutare_valida(j, i - p, j, i))
							sah_mat1 = false;
					}
					break;
				case cal_a:
					if (mutare_valida(j - 1, i - 2, j, i))
						sah_mat1 = false;
					if (mutare_valida(j + 1, i - 2, j, i))
						sah_mat1 = false;
					if (mutare_valida(j - 1, i + 2, j, i))
						sah_mat1 = false;
					if (mutare_valida(j + 1, i + 2, j, i))
						sah_mat1 = false;
					if (mutare_valida(j - 2, i - 1, j, i))
						sah_mat1 = false;
					if (mutare_valida(j + 2, i - 1, j, i))
						sah_mat1 = false;
					if (mutare_valida(j - 2, i + 1, j, i))
						sah_mat1 = false;
					if (mutare_valida(j + 2, i + 1, j, i))
						sah_mat1 = false;
					break;
				case nebun_a:
					for (int p = 1; p <= 7; p++) {
						if (j - p >= 0 && i - p >= 0)
							if (mutare_valida(j - p, i - p, i, j))
								sah_mat1 = false;
						if (j - p >= 0 && i + p <= 7)
							if (mutare_valida(j - p, i + p, i, j))
								sah_mat1 = false;
						if (j + k <= 7 && i - k >= 0)
							if (mutare_valida(j + p, i - p, j, i))
								sah_mat1 = false;
						if (j + k <= 7 && i + k <= 7)
							if (mutare_valida(j + p, i + p, i, j))
								sah_mat1 = false;
					}
					break;
				case regina_a:
					for (int p = 1; p <= 7; p++) {
						if (j + p <= 7 && mutare_valida(j + p, i, j, i))
							sah_mat1 = false;
						if (j - p >= 0 && mutare_valida(j - p, i, j, i))
							sah_mat1 = false;
						if (i + p <= 7 && mutare_valida(j, i + p, j, i))
							sah_mat1 = false;
						if (i - p >= 0 && mutare_valida(j, i - p, j, i))
							sah_mat1 = false;
						if (j - p >= 0 && i - p >= 0)
							if (mutare_valida(j - p, i - p, i, j))
								sah_mat1 = false;
						if (j - p >= 0 && i + p <= 7)
							if (mutare_valida(j - p, i + p, i, j))
								sah_mat1 = false;
						if (j + p <= 7 && i - p >= 0)
							if (mutare_valida(j + p, i - p, j, i))
								sah_mat1 = false;
						if (j + p <= 7 && i + p <= 7)
							if (mutare_valida(j + p, i + p, i, j))
								sah_mat1 = false;
					}
					break;
				case rege_a:
					if (mutare_valida(j - 1, i, j, i)) //&& !sah(prevx-1, prevy)) 
						sah_mat1 = false;
					if (mutare_valida(j - 1, i - 1, j, i)) // && !sah(prevx - 1, prevy - 1)) {
						sah_mat1 = false;
					if (mutare_valida(j, i - 1, j, i))//&& !sah(prevx, prevy-1)) {
						sah_mat1 = false;
					if (mutare_valida(j + 1, i - 1, j, i))
						sah_mat1 = false;
					if (mutare_valida(j + 1, i, j, i))
						sah_mat1 = false;
					if (mutare_valida(j + 1, i + 1, j, i))
						sah_mat1 = false;
					if (mutare_valida(j, i + 1, j, i))
						sah_mat1 = false;
					if (mutare_valida(j - 1, i + 1, j, i))
						sah_mat1 = false;
					break;
				}
				if (!sah_mat1) {
					k = true;
					break;
				}
				else
					s_mat.setString("Sah mat! Albele castiga!");
			}
		}
		return k;
}*/

bool mutare_valida(int x, int y, int prevx, int prevy) {
	if (tabla[prevy][prevx] < 0 && tabla[y][x] >= 0) {
		if (tabla[prevy][prevx] == pion_n) {
			if (prevy == 1 && y - prevy == 2 && x == prevx && tabla[y][x] == 0 && tabla[prevy + 1][prevx] == 0 && y > prevy && !sah(x2_rege, y2_rege, x, y, pion_n, rege_n))
				return 1;
			if (y - prevy == 1 && x == prevx && tabla[y][x] == 0 && y > prevy && !sah(x2_rege, y2_rege, x, y, pion_n, rege_n)) {
				if (tabla[prevy + 1][prevx] == 0)
					return 1;
			}
		//	if(y==prevy+1 && x==prevx-1 && tabla[y][x]>0 && !sah(x2_rege, y2_rege, x, y, pion_n, rege_n))
			//	return 1;
			if (y == prevy + 1 && (x == prevx - 1 || x == prevx + 1) && tabla[y][x] > 0 && !sah(x2_rege, y2_rege, x, y, pion_n, rege_n))
				return 1;
			return 0;
		}
		if (tabla[prevy][prevx] == turn_n) {
			if (x == prevx && !sah(x2_rege, y2_rege, x, y, turn_n, rege_n)) {
				if (prevy < y) {
					for (int i = prevy+1; i < y; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
				if (prevy > y) {
					for (int i = y+1; i < prevy; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
			}
			if (y == prevy && !sah(x2_rege, y2_rege, x, y, turn_n, rege_n)) {
				if (prevx < x) {
					for (int i = prevx + 1; i < x; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
				if (prevx > x) {
					for (int i = x + 1; i < prevx; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
			}
		}
		if (tabla[prevy][prevx] == cal_n) {
			if (y == prevy + 2 && (x == prevx + 1 || x == prevx - 1) && !sah(x2_rege, y2_rege, x, y, cal_n, rege_n))
				return 1;
			if (y == prevy + 1 && (x == prevx + 2 || x == prevx - 2) && !sah(x2_rege, y2_rege, x, y, cal_n, rege_n))
				return 1;
			if (y == prevy - 1 && (x == prevx + 2 || x == prevx - 2) && !sah(x2_rege, y2_rege, x, y, cal_n, rege_n))
				return 1;
			if (y == prevy - 2 && (x == prevx + 1 || x == prevx - 1) && !sah(x2_rege, y2_rege, x, y, cal_n, rege_n))
				return 1;
			return 0;
		}
		if (tabla[prevy][prevx] == nebun_n) {
			if (abs(x - prevx) == abs(y - prevy) && !sah(x2_rege, y2_rege, x, y, nebun_n, rege_n)) {
				if (prevx > x) { // mutare spre stanga
					if (prevy > y) { //mutare sus
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy - i][prevx - i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy + i][prevx - i] != 0)
								return 0;
						return 1;
					}
				}
				if (prevx < x) { //mutare dreapta
					if (prevy > y) { //mutare sus
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy - i][prevx + i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy + i][prevx + i] != 0)
								return 0;
						return 1;
					}
				}
			}
		}
		if (tabla[prevy][prevx] == regina_n) {
			if (x == prevx && !sah(x2_rege, y2_rege, x, y, regina_n, rege_n)) {
				if (prevy < y) {
					for (int i = prevy + 1; i < y; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
				if (prevy > y) {
					for (int i = y + 1; i < prevy; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
			}
			if (y == prevy) {
				if (prevx < x && !sah(x2_rege, y2_rege, x, y, regina_n, rege_n)) {
					for (int i = prevx + 1; i < x; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
				if (prevx > x) {
					for (int i = x + 1; i < prevx; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
			}
			if (abs(x - prevx) == abs(y - prevy) && !sah(x2_rege, y2_rege, x, y, regina_n, rege_n)) {
				if (prevx > x) { // mutare spre stanga
					if (prevy > y) { //mutare sus
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy - i][prevx - i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy + i][prevx - i] != 0)
								return 0;
						return 1;
					}
				}
				if (prevx < x) { //mutare dreapta
					if (prevy > y) { //mutare sus
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy - i][prevx + i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy + i][prevx + i] != 0)
								return 0;
						return 1;
					}
				}
				return 0;
			}
		}
		if (tabla[prevy][prevx] == rege_n) {
			if (x == prevx && y == prevy + 1 && !sah(prevx, prevy + 1, 0, 0, tabla[0][0], rege_n))
				return 1;
			if (x == prevx && y == prevy - 1 && !sah(prevx, prevy - 1, 0, 0, tabla[0][0], rege_n))
				return 1;
			if (y == prevy && x == prevx + 1 && !sah(prevx + 1, prevy, 0, 0, tabla[0][0], rege_n))
				return 1;
			if (y == prevy && x == prevx - 1 && !sah(prevx - 1, prevy, 0, 0, tabla[0][0], rege_n))
				return 1;
			if (abs(x - prevx) == 1 && abs(y - prevy) == 1)
				if (!sah(x, y, 0, 0, tabla[0][0], rege_n))
					return 1;
			return 0;
		}
	}
	if (tabla[prevy][prevx] > 0 && tabla[y][x] <= 0) {
		if (tabla[prevy][prevx] == pion_a) {
			if (prevy == 6 && prevy - y == 2 && x == prevx && tabla[y][x] == 0 && tabla[prevy-1][prevx]==0 && y < prevy && !sah(x1_rege, y1_rege, x, y, pion_a, rege_a))
				return 1;
			if (prevy - y == 1 && x == prevx && tabla[y][x] == 0 && y < prevy && !sah(x1_rege, y1_rege, x, y, pion_a, rege_a)) {
				if (tabla[prevy - 1][prevx] == 0)
					return 1;
			}
			if (y == prevy - 1 && (x == prevx - 1 || x == prevx + 1) && tabla[y][x] < 0 && !sah(x1_rege, y1_rege, x, y, pion_a, rege_a))
				return 1;
			return 0;
		}
		if (tabla[prevy][prevx] == turn_a) {
			if (x == prevx && !sah(x1_rege, y1_rege, x, y, turn_a, rege_a)) {
				if (prevy < y) {
					for (int i = prevy + 1; i < y; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
				if (prevy > y) {
					for (int i = y + 1; i < prevy; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
			}
			if (y == prevy && !sah(x1_rege, y1_rege, x, y, turn_a, rege_a)) {
				if (prevx < x) {
					for (int i = prevx + 1; i < x; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
				if (prevx > x) {
					for (int i = x + 1; i < prevx; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
			}
		}
		if (tabla[prevy][prevx] == cal_a) {
			if (y == prevy + 2 && (x == prevx + 1 || x == prevx - 1))
				return 1;
			if (y == prevy + 1 && (x == prevx + 2 || x == prevx - 2))
				return 1;
			if (y == prevy - 1 && (x == prevx + 2 || x == prevx - 2))
				return 1;
			if (y == prevy - 2 && (x == prevx + 1 || x == prevx - 1))
				return 1;
			return 0;
		}
		if (tabla[prevy][prevx] == nebun_a) {
			if (abs(x - prevx) == abs(y - prevy) && !sah(x1_rege, y1_rege, x, y, nebun_a, rege_a)) {
				if (prevx > x) { // mutare spre stanga
					if (prevy > y) { //mutare sus
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy - i][prevx - i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy + i][prevx - i] != 0)
								return 0;
						return 1;
					}
				}
				if (prevx < x) { //mutare dreapta
					if (prevy > y) { //mutare sus
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy - i][prevx + i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy + i][prevx + i] != 0)
								return 0;
						return 1;
					}
				}
			}
		}
		if (tabla[prevy][prevx] == regina_a) {
			if (x == prevx && !sah(x1_rege, y1_rege, x, y, regina_a, rege_a)) {
				if (prevy < y) {
					for (int i = prevy + 1; i < y; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
				if (prevy > y) {
					for (int i = y + 1; i < prevy; i++)
						if (tabla[i][x] != 0)
							return 0;
					return 1;
				}
			}
			if (y == prevy && !sah(x1_rege, y1_rege, x, y, regina_a, rege_a)) {
				if (prevx < x) {
					for (int i = prevx + 1; i < x; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
				if (prevx > x) {
					for (int i = x + 1; i < prevx; i++)
						if (tabla[y][i] != 0)
							return 0;
					return 1;
				}
			}
			if (abs(x - prevx) == abs(y - prevy) && !sah(x1_rege, y1_rege, x, y, regina_a, rege_a)) {
				if (prevx > x) { // mutare spre stanga
					if (prevy > y) { //mutare sus
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy - i][prevx - i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < prevx - x; i++)
							if (tabla[prevy + i][prevx - i] != 0)
								return 0;
						return 1;
					}
				}
				if (prevx < x) { //mutare dreapta
					if (prevy > y) { //mutare sus
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy - i][prevx + i] != 0)
								return 0;
						return 1;
					}
					if (prevy < y) { //mutare jos
						for (int i = 1; i < x - prevx; i++)
							if (tabla[prevy + i][prevx + i] != 0)
								return 0;
						return 1;
					}
				}
				return 0;
			}
		}
		if (tabla[prevy][prevx] == rege_a) {
			if (x == prevx && y == prevy + 1 && !sah(prevx, prevy + 1, 0, 0, tabla[0][0], rege_a))
				return 1;
			if (x == prevx && y == prevy - 1 && !sah(prevx, prevy - 1, 0, 0, tabla[0][0], rege_a))
				return 1;
			if (y == prevy && x == prevx + 1 && !sah(prevx + 1, prevy, 0, 0, tabla[0][0], rege_a))
				return 1;
			if (y == prevy && x == prevx - 1 && !sah(prevx - 1, prevy, 0, 0, tabla[0][0], rege_a))
				return 1;
			if (abs(x - prevx) == 1 && abs(y - prevy) == 1)
				if (!sah(x, y, 0, 0, tabla[0][0], rege_a))
					return 1;
			return 0;
		}
	}
	return 0;
}

void mutare(int x, int y, int prevx, int prevy) {
	bool k;
	//std::cout << "Rege a: " << y1_rege << " " << x1_rege << " \nRege n: " << y2_rege << " " << x2_rege << '\n';
	if (tur == 0) {
			if (tabla[prevy][prevx] > 0 && tabla[y][x] != rege_n && mutare_valida(x, y, prevx, prevy)) {
				if (y == 0 && tabla[prevy][prevx] == pion_a)
					tabla[prevy][prevx] = regina_a;
				tur = 1;
				tabla[y][x] = tabla[prevy][prevx];
				tabla[prevy][prevx] = 0;
			//std::cout << "\n" << x1_rege << " " << y1_rege << '\n';
			}
			/*if (sah_mat1) {
				s_mat.setString("Sah mat! Negrele castiga!");
				window.draw(s_mat);
			}*/
			//Verificare sah mat pentru albe si incheiere joc

	}
	if (tur == 1) {
		//posibilitati1(posx, posy, false);
			if (tabla[prevy][prevx] < 0 && tabla[y][x] != rege_a && mutare_valida(x, y, prevx, prevy)) {
				if (y == 7 && tabla[prevy][prevx] == pion_n)
					tabla[prevy][prevx] = regina_n;
				tur = 0;
				tabla[y][x] = tabla[prevy][prevx];
				tabla[prevy][prevx] = 0;
				/*if (sah_mat2) {
					s_mat.setString("Sah mat! Albele castiga");
					window.draw(s_mat);
				}*/
			}
	}
	//afisare();
}

void afisare() {
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++)
			std::cout << tabla[i][j] << " ";
		std::cout << '\n';
	}
	std::cout << '\n';
}

void player1a() {  //0- alb si rezolutie 1980
	Vector2i pos;
	Event e;
	int prevx = -1, prevy = -1, x = -1, y = -1;
	window.pollEvent(e);
	while (Mouse::isButtonPressed(Mouse::Left)) {
		if (prevx == -1 && prevy == -1) {
			prevx = Mouse::getPosition(window).x;
			prevy = Mouse::getPosition(window).y;
			prevx = (prevx - (VideoMode::getDesktopMode().width / 2 - 360)) / 85;
			prevy = (prevy - 70) / 85;
			//std::cout << prevy << " " << prevx << '\n';
		}
		posibilitati1(prevx, prevy, true);
		pos.x = Mouse::getPosition(window).x;
		pos.y = Mouse::getPosition(window).y;
		x = (pos.x - (VideoMode::getDesktopMode().width / 2 - 360)) / 85;
		y = (pos.y - 70) / 85;
		//std::cout << y << " " << x << '\n';
		//posibilitati(prevx, prevy);
		sleep(milliseconds(100));
	}
	if (prevx != -1 && x>=0 && x<=7 && y>=0 && y<=7) {
		mutare(x, y, prevx, prevy);
		//afisare();
	}
}

void player1b() { //rezolutie mica
	Vector2i pos;
	Event e;
	int prevx = -1, prevy = -1, x = -1, y = -1;
	window.pollEvent(e);
	while (Mouse::isButtonPressed(Mouse::Left)) {
		if (prevx == -1 && prevy == -1) {
			prevx = Mouse::getPosition(window).x;
			prevy = Mouse::getPosition(window).y;
			prevx = (prevx - (VideoMode::getDesktopMode().width / 2 - 358)) / 74;
			prevy = (prevy - 50) / 74;
			//std::cout << prevy << " " << prevx << '\n';
		}
		posibilitati2(prevx, prevy);
		pos.x = Mouse::getPosition(window).x;
		pos.y = Mouse::getPosition(window).y;
		x = (pos.x - (VideoMode::getDesktopMode().width / 2 - 358)) / 74;
		y = (pos.y - 50) / 74;
		//std::cout << y << " " << x << '\n';
		//posibilitati(prevx, prevy);
		sleep(milliseconds(100));
	}
	if (prevx != -1 && x >= 0 && x <= 7 && y >= 0 && y <= 7) {
		mutare(x, y, prevx, prevy);
		//afisare();
	}
}

void player2a() {   //1- negru
	Vector2i pos;
	Event e;
	int prevx = -1, prevy = -1, x = -1, y = -1;
	window.pollEvent(e);
	while (Mouse::isButtonPressed(Mouse::Left)) {
		if (prevx == -1 && prevy == -1) {
			prevx = Mouse::getPosition(window).x;
			prevy = Mouse::getPosition(window).y;
			prevx = (prevx - (VideoMode::getDesktopMode().width / 2 - 360)) / 85;
			prevy = (prevy - 70) / 85;
			//std::cout << prevy << " " << prevx << '\n';
		}
		posibilitati1(prevx, prevy, true);
		pos.x = Mouse::getPosition(window).x;
		pos.y = Mouse::getPosition(window).y;
		x = (pos.x - (VideoMode::getDesktopMode().width / 2 - 360)) / 85;
		y = (pos.y - 70) / 85;
		//posibilitati(prevx, prevy);
		//std::cout << y << " " << x << '\n';
		sleep(milliseconds(100));
	}
	if (prevx != -1 && x >= 0 && x <= 7 && y >= 0 && y <= 7) {
		mutare(x, y, prevx, prevy);
		//afisare();
	}
}

void player2b() {
	Vector2i pos;
	Event e;
	int prevx = -1, prevy = -1, x = -1, y = -1;
	window.pollEvent(e);
	while (Mouse::isButtonPressed(Mouse::Left)) {
		if (prevx == -1 && prevy == -1) {
			prevx = Mouse::getPosition(window).x;
			prevy = Mouse::getPosition(window).y;
			prevx = (prevx - (VideoMode::getDesktopMode().width / 2 - 358)) / 74;
			prevy = (prevy - 60) / 74;
			//std::cout << prevy << " " << prevx << '\n';
		}
		posibilitati2(prevx, prevy);
		pos.x = Mouse::getPosition(window).x;
		pos.y = Mouse::getPosition(window).y;
		x = (pos.x - (VideoMode::getDesktopMode().width / 2 - 358)) / 74;
		y = (pos.y - 60) / 74;
		//posibilitati(prevx, prevy);
		//std::cout << y << " " << x << '\n';
		sleep(milliseconds(100));
	}
	if (prevx != -1 && x >= 0 && x <= 7 && y >= 0 && y <= 7) {
		mutare(x, y, prevx, prevy);
		//afisare();
	}
}

void logic() {
	//char t[100];
	Text randul;
	
	Event e;
	tabla_init();
	//window.display();
		if (tur == 0) {
			//strcat_s(t, " albele");
			//randul.setString(t);
			//randul.setCharacterSize(24);
			//randul.setPosition(50, 50);
			//randul.setFillColor(Color::Red);
			//window.display();
			if (VideoMode::getDesktopMode().width <= 1400 && VideoMode::getDesktopMode().height <= 800)
				player1b();
			else
				player1a();
		}
		else {
			if (VideoMode::getDesktopMode().width <= 1400 && VideoMode::getDesktopMode().height <= 800)
				player2b();
			else
				player2a();
		}
	while (window.pollEvent(e)) {
		if (e.type == Event::Closed)
			window.close();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();
	}
}

int main() {
	Font font;
	if (!font.loadFromFile("font.ttf"))
	{
		std::cerr << "Fontul nu s-a incarcat corect" << std::endl;
		return -1;
	}
	Event e;
	Texture t2;
	Text randul, text, instructiuni;
	t2.loadFromFile("imagini/tabla.png");
	Sprite s(t2);
	if (VideoMode::getDesktopMode().width <= 1400 && VideoMode::getDesktopMode().height <= 800) {
		s.setPosition(VideoMode::getDesktopMode().width / 2 - 400, 20);
		s.scale(1.3, 1.3);
		randul.setCharacterSize(20);
		randul.setPosition(20, VideoMode::getDesktopMode().height / 2 - 45);
		randul.setFillColor(Color::White);
		text.setCharacterSize(20);
		text.setPosition(VideoMode::getDesktopMode().width - 50, 100);
		text.setFillColor(Color::White);
		s_mat.setCharacterSize(20);
		s_mat.setPosition(VideoMode::getDesktopMode().width - 50, 100);
		s_mat.setFillColor(Color::White);
	}
	else {
		s.setPosition(VideoMode::getDesktopMode().width / 2 - 400, 50);
		s.scale(1.5, 1.5);
		randul.setCharacterSize(30);
		randul.setPosition(50, VideoMode::getDesktopMode().height / 2 - 150);
		randul.setFillColor(Color::White);
		text.setCharacterSize(30);
		text.setPosition(VideoMode::getDesktopMode().width/2-50, VideoMode::getDesktopMode().height-200);
		text.setFillColor(Color::White);
		instructiuni.setCharacterSize(30);
		instructiuni.setPosition(50, VideoMode::getDesktopMode().height / 2 - 100);
		instructiuni.setFillColor(Color::White);
		s_mat.setCharacterSize(30);
		s_mat.setPosition(VideoMode::getDesktopMode().width - 300, 100);
		s_mat.setFillColor(Color::White);
	}
	text.setFont(font);
	instructiuni.setFont(font);
	instructiuni.setString("Iesire-> tasta Esc");
	text.setString("Sah!");
	s_mat.setFont(font);
	int prevx, prevy;
	while (window.isOpen()) {
		/*prevx = Mouse::getPosition(window).x;
		prevy = Mouse::getPosition(window).y;
		std::cout << prevy << " " << prevx << '\n';*/
		window.clear();
		if (tur == 0) {
			randul.setFont(font);
			randul.setString("Urmatoarea mutare: albele");
		}
		else {
			randul.setFont(font);
			randul.setString("Urmatoarea mutare: negrele");
		}
		window.draw(s);
		window.draw(randul);
		window.draw(instructiuni);
		if (sah(x1_rege, y1_rege, 0, 0, tabla[0][0], rege_a) || sah(x2_rege, y2_rege, 0, 0, tabla[0][0], rege_n) && k)
			window.draw(text);
		if (VideoMode::getDesktopMode().width <= 1400 && VideoMode::getDesktopMode().height <= 800)
			asezare2();
		else
			asezare1();
		logic();
		window.display();
		//window.display();
		//logic();
	}
}

void asezare1() {
	float x, y;
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
	t1.loadFromFile("imagini/turn_A.png");
	t2.loadFromFile("imagini/cal_A.png");
	t3.loadFromFile("imagini/nebun_A.png");
	t4.loadFromFile("imagini/regina_A.png");
	t5.loadFromFile("imagini/rege_A.png");
	t6.loadFromFile("imagini/pion_A.png");
	t7.loadFromFile("imagini/turn_N.png");
	t8.loadFromFile("imagini/cal_N.png");
	t9.loadFromFile("imagini/nebun_N.png");
	t10.loadFromFile("imagini/regina_N.png");
	t11.loadFromFile("imagini/rege_N.png");
	t12.loadFromFile("imagini/pion_N.png");
	Sprite s1(t1), s2(t2), s3(t3), s4(t4), s5(t5), s6(t6), s7(t7), s8(t8), s9(t9), s10(t10), s11(t11), s12(t12);
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++) 
			switch (tabla[i][j]) {
				case turn_a:
					x = (VideoMode::getDesktopMode().width / 2 - 350 )+ (j * 85);
					y = 60 + i * 85;
					s1.setPosition(x, y);
					s1.setScale(0.35, 0.35);
					window.draw(s1);
					break;
				case nebun_a:
					x = (VideoMode::getDesktopMode().width / 2 - 350) + (j * 85);
					y = 60 + i * 85;
					s3.setPosition(x, y);
					s3.setScale(0.35, 0.35);
					window.draw(s3);
					break;
				case cal_a:
					x = (VideoMode::getDesktopMode().width / 2 - 350) + (j * 85);
					y = 60 + i * 85;
					s2.setPosition(x, y);
					s2.setScale(0.35, 0.35);
					window.draw(s2);
					break;
				case regina_a:
					x = (VideoMode::getDesktopMode().width / 2 - 350) + (j * 85);
					y = 60 + i * 85;
					s4.setPosition(x, y);
					s4.setScale(0.35, 0.35);
					window.draw(s4);
					break;
				case rege_a:
					x1_rege = j;
					y1_rege = i;
					x = (VideoMode::getDesktopMode().width / 2 - 350) + (j * 85);
					y = 60 + i * 85;
					s5.setPosition(x, y);
					s5.setScale(0.35, 0.35);
					window.draw(s5);
					break;
				case pion_a:
					x = (VideoMode::getDesktopMode().width / 2 - 345) + (j * 85);
					y = 60 + i * 85;
					s6.setPosition(x, y);
					s6.setScale(0.35, 0.35);
					window.draw(s6);
					break;
				case turn_n:
					x = (VideoMode::getDesktopMode().width / 2 - 345) + (j * 85);
					y = 60 + i * 85;
					s7.setPosition(x, y);
					s7.setScale(0.35, 0.35);
					window.draw(s7);
					break;
				case cal_n:
					x = (VideoMode::getDesktopMode().width / 2 - 345) + (j * 85);
					y = 60 + i * 85;
					s8.setPosition(x, y);
					s8.setScale(0.35, 0.35);
					window.draw(s8);
					break;
				case regina_n:
					x = (VideoMode::getDesktopMode().width / 2 - 345) + (j * 85);
					y = 60 + i * 85;
					s10.setPosition(x, y);
					s10.setScale(0.35, 0.35);
					window.draw(s10);
					break;
				case rege_n:
					x2_rege = j;
					y2_rege = i;
					x = (VideoMode::getDesktopMode().width / 2 - 345) + (j * 85);
					y = 60 + i * 85;
					s11.setPosition(x, y);	
					s11.setScale(0.35, 0.35);
					window.draw(s11);
					break;
				case pion_n:
					x = (VideoMode::getDesktopMode().width / 2 - 345) + (j * 85);
					y = 60 + i * 85;
					s12.setPosition(x, y);
					s12.setScale(0.35, 0.35);
					window.draw(s12);
					break;
				case nebun_n:
					x = (VideoMode::getDesktopMode().width / 2 - 345) + (j * 85);
					y = 60 + i * 85;
					s9.setPosition(x, y);
					s9.setScale(0.35, 0.35);
					window.draw(s9);
					break;
			}
}

void asezare2() {
	float x, y;
	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
	t1.loadFromFile("imagini/turn_A.png");
	t2.loadFromFile("imagini/cal_A.png");
	t3.loadFromFile("imagini/nebun_A.png");
	t4.loadFromFile("imagini/regina_A.png");
	t5.loadFromFile("imagini/rege_A.png");
	t6.loadFromFile("imagini/pion_A.png");
	t7.loadFromFile("imagini/turn_N.png");
	t8.loadFromFile("imagini/cal_N.png");
	t9.loadFromFile("imagini/nebun_N.png");
	t10.loadFromFile("imagini/regina_N.png");
	t11.loadFromFile("imagini/rege_N.png");
	t12.loadFromFile("imagini/pion_N.png");
	Sprite s1(t1), s2(t2), s3(t3), s4(t4), s5(t5), s6(t6), s7(t7), s8(t8), s9(t9), s10(t10), s11(t11), s12(t12);
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			switch (tabla[i][j]) {
			case turn_a:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s1.setPosition(x, y);
				s1.setScale(0.3, 0.3);
				window.draw(s1);
				break;
			case nebun_a:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s3.setPosition(x, y);
				s3.setScale(0.3, 0.3);
				window.draw(s3);
				break;
			case cal_a:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s2.setPosition(x, y);
				s2.setScale(0.3, 0.3);
				window.draw(s2);
				break;
			case regina_a:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s4.setPosition(x, y);
				s4.setScale(0.3, 0.3);
				window.draw(s4);
				break;
			case rege_a:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				x1_rege = x;
				y1_rege = y;
				s5.setPosition(x, y);
				s5.setScale(0.3, 0.3);
				window.draw(s5);
				break;
			case pion_a:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 25 + i * 74;
				s6.setPosition(x, y);
				s6.setScale(0.3, 0.3);
				window.draw(s6);
				break;
			case turn_n:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s7.setPosition(x, y);
				s7.setScale(0.3, 0.3);
				window.draw(s7);
				break;
			case cal_n:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s8.setPosition(x, y);
				s8.setScale(0.3, 0.3);
				window.draw(s8);
				break;
			case regina_n:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s10.setPosition(x, y);
				s10.setScale(0.3, 0.3);
				window.draw(s10);
				break;
			case rege_n:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				x2_rege = x;
				y2_rege = y;
				s11.setPosition(x, y);
				s11.setScale(0.3, 0.3);
				window.draw(s11);
				break;
			case pion_n:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s12.setPosition(x, y);
				s12.setScale(0.3, 0.3);
				window.draw(s12);
				break;
			case nebun_n:
				x = (VideoMode::getDesktopMode().width / 2 - 358) + (j * 74);
				y = 30 + i * 74;
				s9.setPosition(x, y);
				s9.setScale(0.3, 0.3);
				window.draw(s9);
				break;
			}
}

void tabla_init() {
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			fin >> tabla[i][j];
}
