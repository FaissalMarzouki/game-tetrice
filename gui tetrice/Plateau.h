#pragma once
#include "shape_node.h"
class Plateau
{
private:
	static const int min_supp = 3;
	shape_node* head, * tail;
	int size;

public:
	Plateau();
	~Plateau();
	//getter:
	shape_node* get_head();
	shape_node* get_tail();
	int get_size() const;
	//setter
	void set_head(shape_node*);
	void set_tail(shape_node*);
	void set_size(int s);
	void show(int);

	//manipulation du liste
	void inserer_right(piece P);
	void inserer_left(piece P);
	void inserer_right_shapes(Plateau* p, piece P);
	void inserer_left_shapes(Plateau* p, piece P);
	void inserer_left_colors(Plateau* p, piece P);
	void inserer_right_colors(Plateau* p, piece P);
	int evaluate_plate(Plateau** colors, Plateau** shapes);

	int supprimer3_left(Plateau(*color)[4], Plateau(*shape)[4]);
	int supprimer3_right(Plateau(*color)[4], Plateau(*shape)[4]);
	void supprimer_left(Plateau* color, Plateau* shape);
	void supprimer_right(Plateau* color, Plateau* shape);
	void afficher(bool dis_last);
	void delete_node();

	//piece supprimer();

};