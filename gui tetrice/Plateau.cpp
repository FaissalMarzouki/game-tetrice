#include "Plateau.h"
#include <conio.h>
#include "Party.h"

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

void Plateau::inserer_right(piece P)
{
	shape_node* NEW = new shape_node(P, NULL, NULL, NULL, NULL, NULL);

	if (size == 0) {
		head = NEW;
		tail = NEW;
		NEW->set_next(NEW);
	}
	else {
		NEW->set_next(head);
		tail->set_next(NEW);
		tail = NEW;
	}
	NEW->imp = size++;
}
void Plateau::inserer_right_shapes(Plateau* p, piece P)
{
	shape_node* new_ptr = p->get_tail();
	// link the main plate tail (new piece)
	// to tail by prev_col
	// to head by next_col
	if (this->size == 0)
	{
		this->head = new_ptr;
		this->tail = new_ptr;


	}
	else
	{
		new_ptr->set_next_shape(this->get_head());
		new_ptr->set_prev_shape(this->get_tail());
		this->head->set_prev_shape(new_ptr);
		this->tail->set_next_shape(new_ptr);
		this->tail = new_ptr;
	}
	new_ptr->isp = size++;

}
void Plateau::inserer_right_colors(Plateau* p, piece P)
{
	shape_node* new_ptr = p->get_tail();
	// link the main plate tail (new piece)
	// to tail by prev_col
	// to head by next_col
	if (this->size == 0)
	{
		this->head = new_ptr;
		this->tail = new_ptr;
		/*new_ptr->set_next_color(this->get_head());
		new_ptr->set_prev_color(this->get_tail());*/


	}
	else
	{
		new_ptr->set_next_color(this->get_head());
		new_ptr->set_prev_color(this->get_tail());
		this->head->set_prev_color(new_ptr);
		this->tail->set_next_color(new_ptr);
		this->tail = new_ptr;
	}
	new_ptr->icp = size++;

}
void Plateau::inserer_left_shapes(Plateau* p, piece P)
{
	shape_node* new_ptr = p->get_head();
	// link the main plate tail (new piece)
	// to tail by prev_col
	// to head by next_col
	if (this->size == 0)
	{
		this->head = new_ptr;
		this->tail = new_ptr;
		new_ptr->set_next_shape(this->get_head());
		new_ptr->set_prev_shape(this->get_tail());


	}
	else
	{
		new_ptr->set_next_shape(this->get_head());
		new_ptr->set_prev_shape(this->get_tail());
		this->head->set_prev_shape(new_ptr);
		this->tail->set_next_shape(new_ptr);
		this->head = new_ptr;
	}
	new_ptr->isp = 0;
	for (int i = 0; i < size + 1; i++)
	{
		new_ptr->isp = i;
		new_ptr = new_ptr->get_next_shape();
	}
	size++;
}
void Plateau::inserer_left_colors(Plateau* p, piece P)
{
	shape_node* new_ptr = p->get_head();
	// link the main plate tail (new piece)
	// to tail by prev_col
	// to head by next_col
	if (this->size == 0)
	{
		this->head = new_ptr;
		this->tail = new_ptr;
		new_ptr->set_next_color(this->get_head());
		new_ptr->set_prev_color(this->get_tail());

	}
	else
	{
		new_ptr->set_next_color(this->get_head());
		new_ptr->set_prev_color(this->get_tail());
		this->head->set_prev_color(new_ptr);
		this->tail->set_next_color(new_ptr);
		this->head = new_ptr;
	}
	for (int i = 0; i < size + 1; i++)
	{
		new_ptr->icp = i;
		new_ptr = new_ptr->get_next_color();
	}
	size++;
}

void Plateau::inserer_left(piece P)
{
	shape_node* NEW = new shape_node(P, NULL, NULL, NULL, NULL, NULL);

	if (size == 0) {
		head = NEW;
		tail = NEW;
		NEW->set_next(NEW);
	}
	else {
		NEW->set_next(head);
		tail->set_next(NEW);

		head = NEW;
	}
	for (int i = 0; i < size + 1; i++)
	{
		NEW->imp = i;
		NEW = NEW->get_next();
	}
	size++;
}

int Plateau::supprimer3_left(Plateau(*color)[4], Plateau(*shape)[4])
{

	if (this->get_size() > 2)
	{
		// verify delatbility
		shape_node* tmp = this->get_head();

		if ((tmp->get_next() == tmp->get_next_color() && tmp->get_next()->get_next() == tmp->get_next()->get_next_color()) && (tmp->get_next() == tmp->get_next_shape() && tmp->get_next()->get_next() == tmp->get_next()->get_next_shape()))
		{
			for (int i = 0; i < 3; i++) {
				supprimer_left(&((*color)[static_cast<int>(this->get_head()->get_piece().get_color()) - 1]), &((*shape)[static_cast<int>(this->get_head()->get_piece().get_shape()) - 1]));
			}
			return 50;
		}
		if ((tmp->get_next() == tmp->get_next_color() && tmp->get_next()->get_next() == tmp->get_next()->get_next_color()) || (tmp->get_next() == tmp->get_next_shape() && tmp->get_next()->get_next() == tmp->get_next()->get_next_shape()))
		{
			for (int i = 0; i < 3; i++) {
				Plateau* c = &((*color)[static_cast<int>(this->get_head()->get_piece().get_color()) - 1]);
				Plateau* s = &((*shape)[static_cast<int>(this->get_head()->get_piece().get_shape()) - 1]);
				supprimer_left(c, s);
			}
			return 10;
		}

	}
	return 0;

}

void show(int tables) {
	shape_node* tmp;
	//switch 
}




int Plateau::evaluate_plate(Plateau** colors, Plateau** shapes) {
	shape_node* pos = this->head;
	///////////////////////////////////////////////////
	//      evaluate and delete based on shapes      //
	///////////////////////////////////////////////////

	for (shape_node* tmp = get_head(), *prev = get_tail(); tmp->imp < size - 2; prev = tmp, tmp = tmp->get_next())
	{
		// base on shapes
		if (tmp->imp + 1 == tmp->get_next_shape()->imp && tmp->get_next_shape()->get_next_shape()->imp == tmp->get_next_shape()->imp + 1) {
			int score = 10;
			int i = static_cast<int>(tmp->get_piece().get_shape()) - 1;

			//tmp = tmp->get_next_shape()->get_next_shape();
			while (tmp->imp + 1 == tmp->get_next_shape()->imp)
			{
				// change the sizes of each plate
				this->size--;
				int index_color = static_cast<int>(tmp->get_piece().get_color()) - 1;
				colors[index_color]->set_size(colors[index_color]->get_size() - 1);
				shapes[i]->set_size(shapes[i]->get_size() - 1);
				//change the heads if demanded
				if (tmp == this->get_head())
				{
					if (tmp != this->get_tail())
					{
						this->head = head->get_next();
					}
					else
					{
						this->set_head(nullptr);
						this->set_tail(nullptr);
					}

				}
				else if (tmp == this->get_tail())
				{
					shape_node* ttt = prev;
					this->tail = ttt;
				}
				if (tmp == colors[index_color]->get_head()) {
					if (tmp != colors[index_color]->get_tail())
					{
						colors[index_color]->set_head(tmp->get_next_color());
					}
					else
					{
						colors[index_color]->set_head(nullptr);
						colors[index_color]->set_tail(nullptr);
					}
				}
				else if (tmp == colors[index_color]->get_tail())
				{
					shape_node* ttt = tmp->get_prev_color();
					colors[index_color]->set_tail(ttt);
				}
				if (tmp == shapes[i]->get_head()) {
					if (tmp != shapes[i]->get_tail())
					{
						shapes[i]->set_head(tmp->get_next_shape());
					}
					else
					{
						shapes[i]->set_head(nullptr);
						shapes[i]->set_tail(nullptr);
					}
				}
				else if (tmp == shapes[i]->get_tail())
				{
					shape_node* ttt = tmp->get_prev_shape();
					shapes[i]->set_tail(ttt);
				}
				//change the nexts 
				prev->set_next(tmp->get_next());
				tmp->get_prev_color()->set_next_color(tmp->get_next_color());
				tmp->get_prev_shape()->set_next_shape(tmp->get_next_shape());
				//change the prevs
				tmp->get_next_color()->set_prev_color(tmp->get_prev_color());
				tmp->get_next_shape()->set_prev_shape(tmp->get_prev_shape());
				shape_node* del = tmp;
				tmp = tmp->get_next_shape();
				delete del;
				score += 30;
			}
			// corigger hadsjhi iwlli fhal lfo9

			// change the sizes of each plate
			this->size--;
			int index_color = static_cast<int>(tmp->get_piece().get_color()) - 1;
			colors[index_color]->set_size(colors[index_color]->get_size() - 1);
			shapes[i]->set_size(shapes[i]->get_size() - 1);
			//change the heads if demanded
			if (tmp == this->get_head())
			{
				if (tmp != this->get_tail())
				{
					this->head = head->get_next();
				}
				else
				{
					this->set_head(nullptr);
					this->set_tail(nullptr);
				}

			}
			else if (tmp == this->get_tail())
			{
				shape_node* ttt = prev;
				this->tail = ttt;
			}
			if (tmp == colors[index_color]->get_head()) {
				if (tmp != colors[index_color]->get_tail())
				{
					colors[index_color]->set_head(tmp->get_next_color());
				}
				else
				{
					colors[index_color]->set_head(nullptr);
					colors[index_color]->set_tail(nullptr);
				}
			}
			else if (tmp == colors[index_color]->get_tail())
			{
				shape_node* ttt = tmp->get_prev_color();
				colors[index_color]->set_tail(ttt);
			}
			if (tmp == shapes[i]->get_head()) {
				if (tmp != shapes[i]->get_tail())
				{
					shapes[i]->set_head(tmp->get_next_shape());
				}
				else
				{
					shapes[i]->set_head(nullptr);
					shapes[i]->set_tail(nullptr);
				}
			}
			else if (tmp == shapes[i]->get_tail())
			{
				shape_node* ttt = tmp->get_prev_shape();
				shapes[i]->set_tail(ttt);
			}




			//change the nexts 
			prev->set_next(tmp->get_next());
			tmp->get_prev_color()->set_next_color(tmp->get_next_color());
			tmp->get_prev_shape()->set_next_shape(tmp->get_next_shape());
			//change the prevs
			tmp->get_next_color()->set_prev_color(tmp->get_prev_color());
			tmp->get_next_shape()->set_prev_shape(tmp->get_prev_shape());
			shape_node* del = tmp;
			tmp = tmp->get_next_shape();
			delete del;
			score += 30;
			// based on shapes : alll the imps after prev will be increased and same for icps and isps 
			// imp and isp of all the pieces with same shape after prev
			// 
			int imp_diff = this->get_tail()->imp - this->get_size();
			int isp_diff = shapes[i]->get_tail()->imp - shapes[i]->get_size();
			while (prev->get_next() != this->get_head())
			{
				//avancer en avant
				prev = prev->get_next();
				// increase imp by difference
				prev->imp -= imp_diff;
				if (prev->get_piece().get_shape() == shapes[i]->get_head()->get_piece().get_shape()) {
					prev->isp -= isp_diff;
				}
				int index_color = static_cast<int>(prev->get_piece().get_color()) - 1;
				int icp_diff = colors[index_color]->get_tail()->imp - colors[index_color]->get_size();
				if (icp_diff)
				{
					prev->icp -= icp_diff;
				}
			}

			return (score + evaluate_plate(colors, shapes));
		}
		// based on colors
		if (tmp->imp + 1 == tmp->get_next_color()->imp && tmp->get_next_color()->get_next_color()->imp == tmp->get_next_color()->imp + 1) {
			int score = 10;
			int i = static_cast<int>(tmp->get_piece().get_color()) - 1;
			//tmp = tmp->get_next_shape()->get_next_shape();
			while (tmp->imp + 1 == tmp->get_next_color()->imp)
			{
				// change the sizes of each plate
				this->size--;
				int index_shape = static_cast<int>(tmp->get_piece().get_shape()) - 1;
				shapes[index_shape]->set_size(shapes[index_shape]->get_size() - 1);
				colors[i]->set_size(colors[i]->get_size() - 1);
				//change the heads if demanded
				if (tmp == this->get_head())
				{
					if (tmp != this->get_tail())
					{
						this->head = head->get_next();
						this->get_tail()->set_next(head);
					}
					else
					{
						this->set_head(nullptr);
						this->set_tail(nullptr);
					}

				}
				else if (tmp == this->get_tail())
				{
					shape_node* ttt = prev;
					this->tail = ttt;
				}
				if (tmp == shapes[index_shape]->get_head()) {
					if (tmp != shapes[index_shape]->get_tail())
					{
						shapes[index_shape]->get_tail()->set_next_shape(tmp->get_next_shape());
						tmp->get_next_shape()->set_prev_shape(shapes[index_shape]->get_tail());
						shapes[index_shape]->set_head(tmp->get_next_shape());
					}
					else
					{
						shapes[index_shape]->set_head(nullptr);
						shapes[index_shape]->set_tail(nullptr);
					}
				}
				else if (tmp == shapes[index_shape]->get_tail())
				{
					shape_node* ttt = tmp->get_prev_shape();
					shapes[index_shape]->set_tail(ttt);
				}
				if (tmp == colors[i]->get_head()) {
					if (tmp != colors[i]->get_tail())
					{
						colors[i]->get_tail()->set_next_color(tmp->get_next_color());
						tmp->get_next_color()->set_prev_color(colors[i]->get_tail());
						colors[i]->set_head(tmp->get_next_color());
					}
					else
					{
						colors[i]->set_head(nullptr);
						colors[i]->set_tail(nullptr);
					}
				}
				else if (tmp == colors[i]->get_tail())
				{
					shape_node* ttt = tmp->get_prev_color();
					colors[i]->set_tail(ttt);
				}




				//change the nexts 
				prev->set_next(tmp->get_next());
				tmp->get_prev_color()->set_next_color(tmp->get_next_color());
				tmp->get_prev_shape()->set_next_shape(tmp->get_next_shape());
				//change the prevs
				tmp->get_next_color()->set_prev_color(tmp->get_prev_color());
				tmp->get_next_shape()->set_prev_shape(tmp->get_prev_shape());
				shape_node* del = tmp;
				tmp = tmp->get_next_color();
				delete del;
				score += 30;
			}
			// corigger hadsjhi iwlli fhal lfo9

			// change the sizes of each plate
			this->size--;
			int index_shape = static_cast<int>(tmp->get_piece().get_shape()) - 1;
			shapes[index_shape]->set_size(shapes[index_shape]->get_size() - 1);
			colors[i]->set_size(colors[i]->get_size() - 1);
			//change the heads if demanded
			if (tmp == this->get_head())
			{
				if (tmp != this->get_tail())
				{
					this->head = head->get_next();
				}
				else
				{
					this->set_head(nullptr);
					this->set_tail(nullptr);
				}

			}
			else if (tmp == this->get_tail())
			{
				shape_node* ttt = prev;
				this->tail = ttt;
			}
			if (tmp == shapes[index_shape]->get_head()) {
				if (tmp != shapes[index_shape]->get_tail())
				{
					shapes[index_shape]->set_head(tmp->get_next_shape());
				}
				else
				{
					shapes[index_shape]->set_head(nullptr);
					shapes[index_shape]->set_tail(nullptr);
				}
			}
			else if (tmp == shapes[index_shape]->get_tail())
			{
				shape_node* ttt = tmp->get_prev_shape();
				shapes[index_shape]->set_tail(ttt);
			}
			if (tmp == colors[i]->get_head()) {
				if (tmp != colors[i]->get_tail())
				{
					colors[i]->set_head(tmp->get_next_color());
				}
				else
				{
					colors[i]->set_head(nullptr);
					colors[i]->set_tail(nullptr);
				}
			}
			else if (tmp == colors[i]->get_tail())
			{
				shape_node* ttt = tmp->get_prev_color();
				colors[i]->set_tail(ttt);
			}




			//change the nexts 
			prev->set_next(tmp->get_next());
			tmp->get_prev_color()->set_next_color(tmp->get_next_color());
			tmp->get_prev_shape()->set_next_shape(tmp->get_next_shape());
			//change the prevs
			tmp->get_next_color()->set_prev_color(tmp->get_prev_color());
			tmp->get_next_shape()->set_prev_shape(tmp->get_prev_shape());
			shape_node* del = tmp;
			tmp = tmp->get_next_shape();
			// based on shapes : alll the imps after prev will be increased and same for icps and isps 
			// imp and icp of all the pieces with same color after prev
			// 
			int imp_diff = this->get_tail()->imp - this->get_size();
			int icp_diff = colors[i]->get_tail()->imp - colors[i]->get_size();
			while (prev->get_next() != this->get_head())
			{
				//avancer en avant
				prev = prev->get_next();
				// increase imp by difference
				prev->imp -= imp_diff;
				if (prev->get_piece().get_color() == colors[i]->get_head()->get_piece().get_color()) {
					prev->icp -= icp_diff;
				}
				int index_shape = static_cast<int>(prev->get_piece().get_shape()) - 1;
				int isp_diff = shapes[index_shape]->get_tail()->imp - shapes[index_shape]->get_size();
				if (isp_diff)
				{
					prev->isp -= isp_diff;
				}
			}
			delete del;
			score += 30;
			return (score + evaluate_plate(colors, shapes));
		}

		// correct imps icps isps 
	}
	return 0;

}

int Plateau::supprimer3_right(Plateau(*color)[4], Plateau(*shape)[4])
{
	if (this->get_size() > 2)
	{
		// verify delatbility
		shape_node* tmp = this->get_tail();
		if ((tmp == tmp->get_prev_color()->get_next() && tmp->get_prev_color() == tmp->get_prev_color()->get_prev_color()->get_next()) && (tmp == tmp->get_prev_shape()->get_next() && tmp->get_prev_shape() == tmp->get_prev_shape()->get_prev_shape()->get_next()))
		{
			for (int i = 0; i < 3; i++) {
				supprimer_right(&((*color)[static_cast<int>(this->get_tail()->get_piece().get_color()) - 1]), &((*shape)[static_cast<int>(this->get_tail()->get_piece().get_shape()) - 1]));
			}
			return 50;
		}
		if ((tmp == tmp->get_prev_color()->get_next() && tmp->get_prev_color() == tmp->get_prev_color()->get_prev_color()->get_next()) || (tmp == tmp->get_prev_shape()->get_next() && tmp->get_prev_shape() == tmp->get_prev_shape()->get_prev_shape()->get_next()))
		{
			for (int i = 0; i < 3; i++) {
				Plateau* c = &((*color)[static_cast<int>(this->get_tail()->get_piece().get_color()) - 1]);
				Plateau* s = &((*shape)[static_cast<int>(this->get_tail()->get_piece().get_shape()) - 1]);
				supprimer_right(c, s);
			}
			return 10;
		}

	}
	return 0;

}

void Plateau::delete_node()
{
	//head
	////color
	////shape

	//tail
	////color
	////shape
}

void Plateau::supprimer_left(Plateau* color, Plateau* shape)
{
	// delete trace from main plate
	shape_node* supp = head;
	if (size == 1) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		head = head->get_next();
		tail->set_next(head);
	}
	size--;

	// delete trace from color plate
	if (color->get_size() == 1) {
		color->set_head(nullptr);
		color->set_tail(nullptr);
	}
	else {
		color->get_tail()->set_next_color(color->get_head()->get_next_color());
		color->set_head(color->get_head()->get_next_color());
		color->get_head()->set_prev_color(color->get_tail());
	}
	color->set_size(color->get_size() - 1);

	// delete trace from shape plate
	if (shape->get_size() == 1) {
		shape->set_head(nullptr);
		shape->set_tail(nullptr);
	}
	else {
		shape->get_tail()->set_next_shape(shape->get_head()->get_next_shape());
		shape->set_head(shape->get_head()->get_next_shape());
		shape->get_head()->set_prev_shape(shape->get_tail());
	}
	shape->set_size(shape->get_size() - 1);
	delete supp;
}

void Plateau::supprimer_right(Plateau* color, Plateau* shape)
{
	// delete trace from main plate
	shape_node* supp = tail;
	if (size == 1) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		shape_node* prv = tail->get_prev_color();
		while (prv->get_next() != tail) {
			prv = prv->get_next();
		}
		tail = prv;
		tail->set_next(head);
	}
	size--;

	// delete trace from color plate
	if (color->get_size() == 1) {
		color->set_head(nullptr);
		color->set_tail(nullptr);
	}
	else {
		color->set_tail(supp->get_prev_color());
		color->get_tail()->set_next_color(supp->get_next_color());
		color->get_head()->set_prev_color(color->get_tail());
	}
	color->set_size(color->get_size() - 1);

	// delete trace from shape plate
	if (shape->get_size() == 1) {
		shape->set_head(nullptr);
		shape->set_tail(nullptr);
	}
	else {
		shape->set_tail(supp->get_prev_shape());
		shape->get_tail()->set_next_shape(supp->get_next_shape());
		shape->get_head()->set_prev_shape(shape->get_tail());
	}
	shape->set_size(shape->get_size() - 1);
	delete supp;


}

void Plateau::afficher(bool dis_last = false)
{
	shape_node* temp = head;
	for (int i = 0; i < size; i++) {
		if (dis_last && tail == temp)
		{
			cout << " -> ";
		}
		temp->get_piece().afficher();
		temp = temp->get_next();
	}
}
void Plateau::set_size(int s) {
	this->size = s;
}