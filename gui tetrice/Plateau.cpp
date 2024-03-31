#include "Plateau.h"
#include "raylib.h"
#include "piece.h"

Plateau::Plateau()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

Plateau::~Plateau()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

shape_node* Plateau::get_head()
{
	return head;
}

shape_node* Plateau::get_tail()
{
	return tail;
}

int Plateau::get_size() const
{
	return size;
}

void Plateau::set_head(shape_node* tete)
{
	head = tete;
}

void Plateau::set_tail(shape_node* queue)
{
	tail = queue;
}
piece* Plateau::makePosition(piece* P, char b) {
	piece* newPiece = new piece(*P);

	if (b == 'r')
		newPiece->set_X(this->middle + piece::spaceRight);
	else if (b == 'l')
		newPiece->set_X(this->middle - piece::spaceLeft);

	return newPiece; 
}

piece * Plateau::choiseMoon(piece* P) {
	P->set_X(600.0f);
	P->set_Y(100.0f);
	return P;
}
void Plateau::inserer_right(piece* P)
{
	P = makePosition(P, 'r');
	shape_node* NEW = new shape_node(*P, NULL, NULL, NULL, NULL, NULL);

	if (size == 0) {
		head = NEW;
		tail = NEW;
	}
	else {
		NEW->set_next(NULL); // The new piece will be the new tail
		tail->set_next(NEW);
		tail = NEW;
	}
	size++;

	//P.set_X(tail->get_piece().get_X() + piece::space);
	piece::spaceRight += 80.0f;
}

void Plateau::inserer_left(piece* P)
{
	P = makePosition(P, 'l');
	shape_node* NEW = new shape_node(*P, NULL, NULL, NULL, NULL, NULL);

	if (size == 0) {
		head = NEW;
		tail = NEW;
	}
	else {
		NEW->set_next(head); // The new piece will be the new head
		head = NEW;
	}
	size++;

	//P.set_X(head->get_piece().get_X() - piece::space);
	piece::spaceLeft += 80.0f;
}
void Plateau::supprimer3_left()
{

	for (int i = 0; i < 3; i++) {
		supprimer_left();
	}

}

void Plateau::supprimer3_right()
{

	for (int i = 0; i < 3; i++) {
		supprimer_right();
	}

}

void Plateau::supprimer_left()
{
	if (size == 0) {
		std::cout << "la liste est vise" << std::endl;

	}
	else {
		shape_node* supp = head;
		tail->set_next(supp->get_next());
		head = head->get_next();
		supp->set_next(nullptr);
		size--;
		//delete(supp);
	}
}

void Plateau::supprimer_right()
{
	if (size == 0) {
		std::cout << "la liste est vise" << std::endl;

	}
	else {
		shape_node* supp = nullptr;
		shape_node* temp = head;
		for (int i = 0; i < size - 2; i++) {
			temp = temp->get_next();
		}
		tail = temp;
		supp = temp->get_next();
		temp->set_next(head);
		supp->set_next(nullptr);
		size--;
		//delete(supp);



	}


}

void Plateau::afficher()
{
	shape_node* temp = head;
	for (int i = 0; i < size; i++) {
		temp->get_piece().afficher();
		temp = temp->get_next();
	}
}
void Plateau::drawAll() const{
	shape_node* tempo = head;
	for (int i = 0; i < size; i++) {
		tempo->get_piece().draw();
		tempo = tempo->get_next();
	}
}



