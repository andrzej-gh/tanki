#pragma once
#include "cobiekt.h"

/// klasa dziedziczna klasy CObiekt, definiuje funkcje dla Gor
class CGora: public CObiekt 
{
	 public:
            /// konstruktor klasy CGora, przekazuje polozenie, wielkosc, ksztalt,  rodzaj bonusa i nakladanej bitmapy/// konstruktor klasy CGora, przekazuje polozenie, wielkosc, ksztalt,  rodzaj bonusa i nakladanej bitmapy
            CGora(float X, float Y, float SKLADOWA, int FIGURE, int BM); 
            virtual int Kolizja();
            virtual void Wybuch();
};