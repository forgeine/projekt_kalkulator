#include <iostream>
#include <allegro5/allegro.h>				//biblioteki allegro
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <cmath>							//sqrt itp.
#include <cstdlib>							//konwertowanie stringow
#include <string>		
#include <cstring>
#include <stdio.h>							//wyswietlanie i wczytywanie
#include <stdlib.h>							//konwertowanie stringow
#include <vector>							// przypisywanie kolorów
#include <sstream>
#include <iomanip>

using namespace std;

#define width 500							//definiowanie  wielkosci okna
#define height 750
#define op 	if(wynik=='S'){for (int j = 0; j < 9; j++) {tablica[j] = '\0';} tablica[0] = '0'; i = 0; wynik = 0;} tablica[i] = operacja; i++; operacja = 0;
#define clear	if(operacja=='+' ||operacja=='-'||operacja=='*'||operacja=='/'||operacja=='S' ||operacja=='^' || operacja =='=' ){ \
					for (int j = 0; j < 9; j++) \
					{tablica[j] = '\0';}\
				tablica[0] = '0'; i = 0; operacja = '\0';}

const int buttonWidth = 100;				//wartosci do rysowania
const int buttonHeight = 100;
const int buttonSpacing = 20;
const int numRows = 5;
const int numCols = 4;

struct Calculator {							//struktura do wykonywania dzialan
	double liczba_1;
	double liczba_2;
};

void Add(struct Calculator* calculator) {												//dzialania
	calculator->liczba_1 = calculator->liczba_1 + calculator->liczba_2;
}
void Substract(struct Calculator* calculator) {
	calculator->liczba_1 = calculator->liczba_1 - calculator->liczba_2;
}
void Multiply(struct Calculator* calculator) {
	calculator->liczba_1 = calculator->liczba_1 * calculator->liczba_2;
}
void Divide(struct Calculator* calculator) {
	calculator->liczba_1 = calculator->liczba_1 / calculator->liczba_2;
}
void Potega(struct Calculator* calculator) {
	calculator->liczba_1 = pow(calculator->liczba_1, calculator->liczba_2);
}
void Pierwiastek(struct Calculator* calculator) {
	calculator->liczba_1 = sqrt(calculator->liczba_1);
}

vector<ALLEGRO_COLOR> playerColors(20, al_map_rgb(255, 255, 255));						//przypisywanie kolorow wektorowo

void setPlayerColor(int index) {
	if (index >= 0 && index < playerColors.size()) {
		playerColors[index] = al_map_rgb(255, 255, 255);
	}
}

void setPlayerColor(ALLEGRO_COLOR& color) {
	color = al_map_rgb(255, 255, 255);
}
vector<ALLEGRO_COLOR> colorAliases = { al_map_rgb(255, 255, 255), al_map_rgb(200, 200, 200),
									   al_map_rgb(0, 0, 0), al_map_rgb(50, 50, 50) };

int main()
{

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);									//aliasy kolorow
	ALLEGRO_COLOR white2 = al_map_rgb(200, 200, 200);
	ALLEGRO_COLOR black2 = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR black = al_map_rgb(50, 50, 50);
	ALLEGRO_COLOR playerColor = white;

	struct Calculator calculator;														//wywolanie struktury
	const float FPS = 60.0;
	al_init();																			//inicjalizacja funkcji allegro
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	ALLEGRO_DISPLAY* display = al_create_display(width, height);						//wielkosc okna
	al_set_window_title(display, "Kalkulator");											//tytul

	ALLEGRO_COLOR kolor = al_map_rgb(255, 255, 255);									//aliasy kolorow
	ALLEGRO_COLOR hover = al_map_rgb(200, 200, 200);
	//ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

	ALLEGRO_FONT* font = al_load_font("cambria.ttc", 100, NULL);						//aliasy czcionek
	ALLEGRO_FONT* font_small = al_load_font("cambria.ttc", 80, NULL);

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();							//stworzenie kolejki eventow
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);

	char tablica[10];																	//tablica obslugujaca wyswietlacz
	for (int j = 0; j < 9; j++) {												
		tablica[j] = '\0';
	}
	tablica[0] = '0';

	int x = 0, y = 0, i = 0;
	const char* znaki[] = { "C", "<-", "S", "^", "7", "8", "9", "*", "4", "5", "6", "/", "1", "2", "3", "-" , "0", ".", "=", "+"};	//tablica znakow kalkulatora
	char operacja = 0;
	char wynik = 0;
	int count = 0;
	bool kropka = false;
	bool sprawdz = false;
	int bufferSize;
	const char* wyswietlacz = tablica;			//zamiana tablicy stalej na const aby wyswietlac
	calculator.liczba_1 = 0.0;					// inicjowanie zmiennych ze struktury
	calculator.liczba_2 = 0.0;
	bool run = true;
	bool test = true;
	while (run) {								//glowna petla
		int n = strlen(tablica);
		for (int k = 0; k < 9; k++) {
			if (tablica[k] == '-') { sprawdz = true; }
		}
		ALLEGRO_COLOR playerColor = colorAliases[0];
		al_clear_to_color(al_map_rgb(0, 0, 0));											//kolor tla
		ALLEGRO_EVENT events;															//inicjalizacja eventow
		al_wait_for_event(event_queue, &events);
		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			return 0;
		}
		if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {								//pozycja myszki
			x = events.mouse.x;
			y = events.mouse.y;
		}
		if (i == 9) {																//ograniczenie dlugosci wyswietlacza
			i--;
			tablica[i] = '\0';
		}
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {						//event z wyboru klawiszy myszka

	//------------------------------- cyfry ------------------------------------------------
				if (x > 40 && x < 130 && y > 290 && y < 380) {
					clear;
					operacja = '7';
					op;
				}
				else if (x > 150 && x < 240 && y > 290 && y < 380) {
					clear;
					operacja = '8';
					op;
				}
				else if (x > 260 && x < 350 && y > 290 && y < 380) {
					clear;
					operacja = '9';
					op;
				}
				else if (x > 40 && x < 130 && y > 400 && y < 490) {
					clear;
					operacja = '4';
					op;
				}
				else if (x > 150 && x < 240 && y > 400 && y < 490) {
					clear;
					operacja = '5';
					op;
				}
				else if (x > 260 && x < 350 && y > 400 && y < 490) {
					clear;
					operacja = '6';
					op;
				}
				else if (x > 40 && x < 130 && y > 510 && y < 600) {
					clear;
					operacja = '1';
					op;
				}
				else if (x > 150 && x < 240 && y > 510 && y < 600) {
					clear;
					operacja = '2';
					op;
				}
				else if (x > 260 && x < 350 && y > 510 && y < 600) {
					clear;
					operacja = '3';
					op;
				}
				//#####################################		0	#########################################
				else if (x > 40 && x < 130 && y > 620 && y < 710) {
					clear;
					if (operacja == '.') {										
						tablica[i] = '0';
						i++;
					}
					else {
						clear;
						operacja = '0';
						if (kropka == true) {									//dostosowanie sie do kropki
							tablica[i] = '0';
							i++;

						}
						else if (kropka == false) {								//ograniczenie zer z przodu liczby
							if (tablica[0] != '0') {
								tablica[i] = '0';
								i++;
							}
							else {
								tablica[i] = '0';
							}
						}
						operacja = 0;
					}
				}
				//#####################################		.	#########################################
				else if (x > 150 && x < 240 && y > 620 && y < 710) {
					clear;
					operacja = '.';
					for (int k = 0; k < 9; k++) {						//zapamietanie istnienia kropki i jej ogranczenie
						if (tablica[k] == '.') {
							kropka = true;
							operacja = 0;
						}
					}
					if (kropka == false) {
						if (i == 0) {
							tablica[i] = '0';
							i++;
						}
						tablica[i] = '.';
						i++;
					}
				}
				//----------------------------- KLAWISZE FUNKCYJNE --------------------------------
				//#####################################		C	#########################################
				if (x > 40 && x < 130 && y > 180 && y < 270) {
					operacja = 'C';
					for (int j = 0; j < 9; j++) {					//wyczyszczenie wszelkich operacji i zmiennych
						tablica[j] = '\0';
					}
					tablica[0] = '0';
					kropka = false;
					sprawdz = false;
					operacja = 0;
					wynik = 0;
					i = 0;
					count = 0;
					calculator.liczba_1 = 0.0;
					calculator.liczba_2 = 0.0;
				}
				//#####################################		<-	#########################################
				else if (x > 150 && x < 240 && y > 180 && y < 270) {
					operacja = '<';
					if (wynik == 'S') {					
						for (int j = 0; j < 9; j++) {
							tablica[j] = '\0';
						}
						calculator.liczba_1 = 0.0;
						tablica[0] = '0';
						//wynik = 0;
					}
						if (calculator.liczba_1 != '\0' && calculator.liczba_2 != '\0') {		//wyzerowanie liczby otrzymanej
							for (int j = 0; j < 9; j++) {
								tablica[j] = '\0';
							}
							calculator.liczba_1 = 0.0;
							tablica[0] = '0';
						}
						else {
							if (i - 1 < 0) {
								i++;
							}
							if (tablica[i - 1] == '.') {										//Pilnowanie jednej kropki
								kropka = false;
							}
							tablica[i - 1] = 0;
							if (i - 1 == 0) {
								tablica[0] = '0';
							}
							i--;
						}
					
				}
				//#####################################		S	#########################################
				else if (x > 260 && x < 350 && y > 180 && y < 270) {
					if (operacja == 'S') {
						if ("ERROR") {												//zarzadzanie errorem dla liczb < 0
							for (int j = 0; j < 9; j++) {
								tablica[j] = '\0';
							}
							tablica[0] = '0';
							operacja = 0;
						}
					}
					else {
						operacja = 'S';
						wynik = operacja;
						double liczba1 = stod(wyswietlacz);							//przerobienie tablicy charow na double i przypisanie jej do liczby ze struktury
						calculator.liczba_1 = liczba1;
						if (calculator.liczba_1 < 0) {
							sprintf_s(tablica, "ERROR");
						}
						else {
							Pierwiastek(&calculator);											//dzialanie
							//bufferSize = snprintf(nullptr, 0, "%f", calculator.liczba_1);
							snprintf(tablica, 9, "%g", calculator.liczba_1);					
							operacja = 0;
						}
					}
				}
				//#####################################		^	#########################################
				else if (x > 370 && x < 460 && y > 180 && y < 270) {
					double liczba1 = stod(wyswietlacz);
					calculator.liczba_1 = liczba1;							//przypisanie liczby 1 z wprowadzonych cyfr
					tablica[0] = '0';										//wyzerowanie tablicy
					for (int j = 1; j < 9; j++) {
						tablica[j] = '\0';
					}
					if (operacja == '^') {								
						double liczba2 = stod(wyswietlacz);					//przypisanie drugiej liczby
						calculator.liczba_2 = liczba2;
						tablica[0] = '0';
						for (int j = 1; j < 9; j++) {						//wyzerowanie tablicy
							tablica[j] = '\0';
						}
						Potega(&calculator);								//dzialanie
						bufferSize = snprintf(nullptr, 0, "%f", calculator.liczba_1);
						snprintf(tablica, bufferSize + 1, "%g", calculator.liczba_1);	//wyswietlanie wyniku w postaci liczba_1
						calculator.liczba_2 = '\0';
					}
					else {
						operacja = '^';										//dla poprzednich dzialan innych niz to
						wynik = operacja;

						if (count == 0 && calculator.liczba_1 == '\0' || operacja == 'C') {
							count++;
						}
						else {
							count = 0;
							double liczba2 = stod(wyswietlacz);				//dodanie drugiej liczby, do istniejacej powstalej z wyniku poprzedniej operacji
							calculator.liczba_2 = liczba2;
							tablica[0] = '0';
							for (int j = 1; j < 9; j++) {					//wyzerowanie
								tablica[j] = '\0';
							}
						}
					}
				}
				//#####################################		*	#########################################		//w kazdej innej operacji dzieje sie to samo
				else if (x > 370 && x < 460 && y > 290 && y < 380) {
					double liczba1 = stod(wyswietlacz);
					calculator.liczba_1 = liczba1;
					tablica[0] = '0';
					for (int j = 1; j < 9; j++) {
						tablica[j] = '\0';
					}
					if (operacja == '*') {
						double liczba2 = stod(wyswietlacz);
						calculator.liczba_2 = liczba2;
						tablica[0] = '0';
						for (int j = 1; j < 9; j++) {
							tablica[j] = '\0';
						}
						Multiply(&calculator);
						bufferSize = snprintf(nullptr, 0, "%f", calculator.liczba_1);
						snprintf(tablica, bufferSize + 1, "%g", calculator.liczba_1);
						calculator.liczba_2 = '\0';
					}
					else {
						operacja = '*';
						wynik = operacja;

						if (count == 0 && calculator.liczba_1 == '\0' || operacja == 'C') {
							count++;
						}
						else {
							count = 0;
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							tablica[0] = '0';
							for (int j = 1; j < 9; j++) {
								tablica[j] = '\0';
							}
						}
					}
				}
				//#####################################		/	#########################################
				else if (x > 370 && x < 460 && y > 400 && y < 490) {
					double liczba1 = stod(wyswietlacz);
					calculator.liczba_1 = liczba1;
					tablica[0] = '0';
					for (int j = 1; j < 9; j++) {
						tablica[j] = '\0';
					}
					if (operacja == '/') {
						double liczba2 = stod(wyswietlacz);
						calculator.liczba_2 = liczba2;
						if (calculator.liczba_2 == 0) {
							sprintf_s(tablica, "ERROR");
						}
						tablica[0] = '0';
						for (int j = 1; j < 9; j++) {
							tablica[j] = '\0';
						}
						Divide(&calculator);
						bufferSize = snprintf(nullptr, 0, "%f", calculator.liczba_1);
						snprintf(tablica, bufferSize + 1, "%g", calculator.liczba_1);
						calculator.liczba_2 = '\0';
					}
					else {
						operacja = '/';
						wynik = operacja;

						if (count == 0 && calculator.liczba_1 == '\0' || operacja == 'C') {
							count++;
						}
						else {
							count = 0;
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							tablica[0] = '0';
							for (int j = 1; j < 9; j++) {
								tablica[j] = '\0';
							}
						}
					}
				}
				//#####################################		-	#########################################
				else if (x > 370 && x < 460 && y > 510 && y < 600) {
					double liczba1 = stod(wyswietlacz);
					calculator.liczba_1 = liczba1;
					tablica[0] = '0';
					for (int j = 1; j < 9; j++) {
						tablica[j] = '\0';
					}
					if (operacja == '-') {
						double liczba2 = stod(wyswietlacz);
						calculator.liczba_2 = liczba2;
						tablica[0] = '0';
						for (int j = 1; j < 9; j++) {
							tablica[j] = '\0';
						}
						Substract(&calculator); 							
						bufferSize = snprintf(nullptr, 0, "%f", calculator.liczba_1);
						snprintf(tablica, bufferSize + 1, "%g", calculator.liczba_1);
						calculator.liczba_2 = '\0';
					}
					else {
						operacja = '-';
						wynik = operacja;
						
						if (count == 0 && calculator.liczba_1 == '\0' || operacja == 'C') {
							count++;
						}
						else {
							count = 0;
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							tablica[0] = '0';
							for (int j = 1; j < 9; j++) {
								tablica[j] = '\0';
							}
						}
					}
				}
				//#####################################		=	#########################################
				else if (x > 260 && x < 350 && y > 620 && y < 710) {			//wykonywanie dzialan po kliknieciu znaku rownosci
					operacja = wynik;
					if (operacja == '+') {										//dana operacja
						if (calculator.liczba_2 == '\0') {						//przydzielenie liczby 2 jesli jest pusta
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							Add(&calculator);									//operacja
						}
						else {
							Add(&calculator);									//operacja jesli liczba nie jest pusta
						}
						count = 0;												//dla innych tak samo
					}
					if (operacja == '-') {
						if (calculator.liczba_2 == '\0') {
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							Substract(&calculator);
						}
						else {
							Substract(&calculator);
						}
					}
					if (operacja == '*') {
						if (calculator.liczba_2 == '\0') {
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							Multiply(&calculator);
						}
						else {
							Multiply(&calculator);
						}
					}
					if (operacja == '/') {
						if (calculator.liczba_2 == '\0') {
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							Divide(&calculator);
						}
						else {
							Divide(&calculator);
						}
					}
					if (operacja == '^') {
						if (calculator.liczba_2 == '\0') {
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							Potega(&calculator);
						}
						else {
							Potega(&calculator);
						}
					}
					if (operacja == 'S') {
						if (calculator.liczba_2 == '\0') {
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							Pierwiastek(&calculator);
						}
						else {
							Pierwiastek(&calculator);
						}
						operacja = '=';
					}
					else { i = 0;}														//polecenie dla innych znakow											
					if (calculator.liczba_1 > 1000000) {								//notacja wykladnicza dla duzych i malych liczb
						snprintf(tablica, 9, "%.1e", calculator.liczba_1);
					}
					else if (calculator.liczba_1 < (-100000)) {
						snprintf(tablica, 9, "%.1e", calculator.liczba_1); 
					}
					else {
						snprintf(tablica, 9, "%g", calculator.liczba_1);
					}
				}
				//#####################################		+	#########################################
				else if (x > 370 && x < 460 && y > 620 && y < 710) {
					double liczba1 = stod(wyswietlacz);
					calculator.liczba_1 = liczba1;
					tablica[0] = '0';
					for (int j = 1; j < 9; j++) {
						tablica[j] = '\0';
					}
					if (operacja == '+') {
						double liczba2 = stod(wyswietlacz);
						calculator.liczba_2 = liczba2;
						tablica[0] = '0';
						for (int j = 1; j < 9; j++) {
							tablica[j] = '\0';
						}
						Add(&calculator);
						bufferSize = snprintf(nullptr, 0, "%f", calculator.liczba_1);
						snprintf(tablica, bufferSize + 1, "%g", calculator.liczba_1);
						calculator.liczba_2 = '\0';
					}
					else {
						operacja = '+';
						wynik = operacja;

						if (count == 0 && calculator.liczba_1 == '\0' || operacja == 'C') {
							count++;
						}
						else {
							count = 0;
							double liczba2 = stod(wyswietlacz);
							calculator.liczba_2 = liczba2;
							tablica[0] = '0';
							for (int j = 1; j < 9; j++) {
								tablica[j] = '\0';
							}
						}
						/*if (calculator.liczba_1 != '\0' && calculator.liczba_2 != '\0') {
							Substract(&calculator);
							cout << "wynik odej: " << calculator.liczba_1 << endl;
							bufferSize = snprintf(nullptr, 0, "%f", calculator.liczba_1);
							snprintf(tablica, bufferSize + 1, "%g", calculator.liczba_1);
						}*/
					}
				}
		}

		//--------------------------------------------------------------------------------------------------------------
		//------------------------------------------ Rysowanie ---------------------------------------------------------
		//--------------------------------------------------------------------------------------------------------------
		al_draw_filled_rectangle(20, 20, 480, 140, kolor);										//rysowanie wyswietlacza
		al_draw_textf(font, black, 475, 20, ALLEGRO_ALIGN_RIGHT, "%s", wyswietlacz);

		int x1 = 40;																			//zmienne do petli rysujacej kafelki operacji i cyferek
		int y1 = 180; 
		int da = 90; 
		int ds = 90; 
		int spacing = 110; 

		for (int i = 0; i < 20; i++) {
			al_draw_filled_rounded_rectangle(x1, y1, x1 + da, y1 + ds, 20, 20, playerColors[i]);	//rysowanie ksztaltu

			al_draw_text(font_small, colorAliases[2], x1+43 , y1-5 , ALLEGRO_ALIGN_CENTRE, znaki[i]);	//znaki z tablicy

			if (x > x1 && x < x1 + da && y > y1 && y < y1 + ds) {										//sprawdzanie posyzcji myszki, hover
				playerColors[i] = colorAliases[1];
			}
			else {
				playerColors[i] = colorAliases[0];
				al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
			}
			x1 += spacing;
			if (i % 4 == 3) {
				y1 += spacing;
				x1 = 40;
			}
		}
		al_flip_display();																		//aktualizowanie wyswietlacza
	}
}