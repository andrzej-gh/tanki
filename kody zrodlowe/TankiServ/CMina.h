#pragma once
#include "cobiekt.h"

/// klasa dziedziczna klasy CObiekt, definiuje funkcje dla Min
class CMina: public CObiekt 
{
	 public:
		    /// konstruktor klasy CGora, przekazuje polozenie, rodzaj bonusa i nakladanej bitmapy
            CMina(float X, float Y, int BM); 
            virtual int Kolizja();
            virtual void Wybuch();           /// usuwa mine i dalsze przesuwa o jeden w tyl na liscie
};