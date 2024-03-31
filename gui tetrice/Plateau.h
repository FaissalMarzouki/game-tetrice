#pragma once
#include "shape_node.h"
#include "piece.h"

class Plateau
{
private:
	shape_node* head, * tail;
	int size;

public:
	const float middle = 600.0f;
	Plateau();
	~Plateau();
	//getter:
	shape_node* get_head();
	shape_node* get_tail();
	int get_size() const;
	//setter
	void set_head(shape_node*);
	void set_tail(shape_node*);

	//manipulation du liste
	piece* makePosition(piece* P,char b);
	piece* choiseMoon(piece* P);
	void inserer_right(piece *P);
	void inserer_left(piece *P);
	void supprimer3_left();
	void supprimer3_right();
	void supprimer_left();
	void supprimer_right();
	void afficher();
	void drawAll() const;

	//piece supprimer();

};

