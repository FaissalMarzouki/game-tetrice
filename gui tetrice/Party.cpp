#include "Party.h"

Party::Party(int choice) {
	system("cls");
	switch (choice)
	{
	case 1:
		Tetriste();
		break;
	case 2:
		std::cout << Tepatrice();
		break;
	case 3:
		Tecontent();
		break;
	case 4:
		std::cout << "Tavalide";
		break;
	case 5:
		std::cout << "Bonus";
	default:
		break;
	}
	_getch();
}
Party::Party(int choice, std::chrono::seconds dur) {
	this->party_time = dur;
	system("cls");
	switch (choice)
	{
	case 1:
		Tetriste();
		break;
	case 2:
		std::cout << "Tepatrice";
		break;
	case 3:
		std::cout << "Tecontent";
		break;
	case 4:
		std::cout << "Tavalide";
		break;
	case 5:
		std::cout << "Bonus";
	default:
		break;
	}
	_getch();
}

void Party::pause_menu(bool ai = false, bool score = false) {
	// tab = 
	std::string options[] = { "Continue","Save Game","Exit" };
	Menu m(options, 3);
	int choice = m.get_choice();
	switch (choice)
	{
	case 1:
		paused = false;
		system("cls");
		init_scene(0, ai, score);
		Menu::gotoxy(2, 2, ' ');
		//Menu::gotoxy(5, 5, "DEBUGGING: after afficher goto");
		game_pieces.afficher(false);
		break;
	case 2:
		save_game();
		break;
	case 3:
		paused = true;
		exited = true;
	default:
		break;
	}
}
void Party::save_game() {

	std::cout << "\nDEBUGGING: Game was saved";
	exited = true;

	_getch();
}
int Party::Tepatrice() {
	this->Type = tepatrice;

	init_scene(1, false, true);
	std::thread thread_object(&Party::handle_time, this);

	while (!exited)
	{
		while (!paused) {
			////////////////////////////////////////////////
			///    handle player input and upadates      ///
			///////////////////////////////////////////////
			player_action(false, true, false);



			////////////////////////////////////////////
			///    Render game pieces in scene      ///
			///////////////////////////////////////////
			while (using_cursor) {}
			using_cursor = true;
			// erase old game pieces from console and show new state
			Menu::gotoxy(2, 2, "                                          ");
			Menu::gotoxy(2, 2, ' ');
			//Menu::gotoxy(5, 5, "DEBUGGING: after afficher goto");
			game_pieces.afficher(false);
			//Menu::gotoxy(5, 6, "DEBUGGING: after afficher fasle");
			using_cursor = false;






			/////////////////////////////////////////////////////
			///    Render and update  next pieces in scene    ///
			/////////////////////////////////////////////////////
			this->next_pieces.inserer_left(piece(4, 4));
			while (using_cursor) {}
			using_cursor = true;
			Menu::gotoxy(0, 0, "                  ");
			Menu::gotoxy(0, 0, " ");
			next_pieces.afficher(true);
			using_cursor = false;

			/////////////////////////////////////////////////////
			///      render the colors and shapes lists       ///
			/////////////////////////////////////////////////////
			render_colorsANDshapes();


		}

	}

	thread_object.join();
	std::cout << "\nDEBUGGING: tetris exit";
	_getch();
	return -1;
}
int Party::Tecontent() {
	this->Type = tecontent;
	//std::cout << "\nDEBUGGING: start";
	/*
		***tag : Wonderful Code .SOF.
		usual std::thread(func_name); didn't work
	*/
	init_scene(1, false, true);
	std::thread thread_object(&Party::handle_time, this);

	while (!exited)
	{
		while (!paused) {
			////////////////////////////////////////////////
			///    handle player input and upadates      ///
			///////////////////////////////////////////////
			player_action(false, true, true);

			//evaluate plate and delete triplets

			//update list and score delete triplets and all 


			// and show it on the screen



			////////////////////////////////////////////
			///    Render game pieces in scene      ///
			///////////////////////////////////////////
			while (using_cursor) {}
			using_cursor = true;
			// erase old game pieces from console and show new state
			Menu::gotoxy(2, 2, "                                          ");
			Menu::gotoxy(2, 2, ' ');
			//Menu::gotoxy(5, 5, "DEBUGGING: after afficher goto");
			game_pieces.afficher(false);
			//Menu::gotoxy(5, 6, "DEBUGGING: after afficher fasle");
			using_cursor = false;






			/////////////////////////////////////////////////////
			///    Render and update  next pieces in scene    ///
			/////////////////////////////////////////////////////
			this->next_pieces.inserer_left(piece(4, 4));
			while (using_cursor) {}
			using_cursor = true;
			Menu::gotoxy(0, 0, "                  ");
			Menu::gotoxy(0, 0, " ");
			next_pieces.afficher(true);
			using_cursor = false;

			/////////////////////////////////////////////////////
			///      render the colors and shapes lists       ///
			/////////////////////////////////////////////////////
			render_colorsANDshapes();


		}

	}

	thread_object.join();
	std::cout << "\nDEBUGGING: tetris exit";
	_getch();
	return -1;
}
void Party::chose_decallage() {
	Menu::gotoxy(0, 4, "Chose a color or a shape :\n");
	// print options 
	Menu::gotoxy(0, 5, ' ');
	cout << "\033[31m" << "RED   " << "\033[0m" << "\033[32m" << " GREEN " << "\033[0m" << "\033[33m" << " YELLOW" << "\033[0m" << "\033[34m" << " BLUE  " << "\033[0m" << " CERCLE" << " RHOMBU" << " SQUARE" << " TRIANGLE";

	char in = 'a';
	int choice = 0;
	Menu::gotoxy(0, 5, '>');
	do
	{
		in = _getch();
		if (in == 77 && choice < 7) {
			Menu::gotoxy(choice * 7, 5, ' ');
			Menu::gotoxy(++choice * 7, 5, '>');
		}
		else if (in == 75 && choice > 0)
		{
			Menu::gotoxy(choice * 7, 5, ' ');
			Menu::gotoxy(--choice * 7, 5, '>');
		}

	} while (in != 'e');
	Menu::gotoxy(0, 4, "                                            \n                                                                           ");
	/*
	note to saad :
	switch based on choice :
	0 => decallage rouge;
	1 => decallage vert;
	2 => decallage jaune;
	3 => decallage blue;
	4 => decallage cercle;
	5 => decallage losange;
	6 => decallage carre ;
	7 => decallage triangle;

	*/
	decallage_gauche(choice);
	////////////////////////////////////////////
	///    Render game pieces in scene      ///
	///////////////////////////////////////////


	// erase old game pieces from console and show new state
	Menu::gotoxy(2, 2, "                                          ");
	Menu::gotoxy(2, 2, ' ');
	//Menu::gotoxy(5, 5, "DEBUGGING: after afficher goto");
	game_pieces.afficher(false);
	//Menu::gotoxy(5, 6, "DEBUGGING: after afficher fasle");

	/////////////////////////////////////////////////////
	///      render the colors and shapes lists       ///
	/////////////////////////////////////////////////////
	render_colorsANDshapes();
}
void Party::debug_copy(shape_node** tab, int size, shape_node** res) {
	for (size_t i = 0; i < size; i++)
	{
		res[i] = tab[i];
	}

}
void Party::decallage_gauche(int choice) {
	shape_node** gpi = new shape_node * [game_pieces.get_size()];
	gpi = create_gpi();
	if (choice < 4)// color
	{
		//////////////////////////////////////
		//          initialisation          //
		// ///////////////////////////////////
		int size_cpi = colors_heads[choice].get_size();
		if (size_cpi < 2)return;

		// etablit tout les spi
		shape_node** spis[4];
		for (int i = 0; i < 4; i++)
		{
			spis[i] = create_spi(i);
		}
		// eablit le cpi de coleur
		shape_node** cpi = create_cpi(choice);


		//////////////////////////////////////////////////////////
		//          sort the color and fix color head & tail          //
		//////////////////////////////////////////////////////////
		shape_node* first_copy = cpi[0];
		int tmp_imp = cpi[size_cpi - 1]->imp;
		colors_heads[choice].set_tail(first_copy);
		colors_heads[choice].set_head(first_copy->get_next_color());
		/*shape_node* debug_arr_1[16];
		debug_copy(cpi, size_cpi, debug_arr_1);*/
		for (int i = 1; i < size_cpi; i++)
		{
			int tmp_i = cpi[i]->imp;
			cpi[i]->imp = first_copy->imp;
			first_copy->imp = tmp_i;
			cpi[i]->icp--;
			first_copy->icp++;
			cpi[i - 1] = cpi[i];

		}
		cpi[size_cpi - 1] = first_copy;
		/*shape_node* debug_arr[16];
		debug_copy(cpi, size_cpi, debug_arr);*/



		//////////////////////////////////////////////////////////
		//        sort the gpi and fix main head & tail        //
		//////////////////////////////////////////////////////////


		int size_gpi = game_pieces.get_size();



		//                                          first element
		// set propper tail
		if (game_pieces.get_tail()->get_piece().get_color() == cpi[0]->get_piece().get_color()) {
			game_pieces.set_tail(cpi[size_cpi - 1]);
			// rightly configure the previous element
			// if the game piec before last one is different from shape we set it's next to the new tail otherwise we let it be
			if (gpi[size_gpi - 2]->get_piece().get_color() != game_pieces.get_tail()->get_piece().get_color())
			{
				gpi[size_gpi - 2]->set_next(game_pieces.get_tail());
			}
			// since it's tail the next elemnt is the new head if it changes and the same head if # color
			if (game_pieces.get_head()->get_piece().get_color() == cpi[size_cpi - 1]->get_piece().get_color())
			{
				game_pieces.get_tail()->set_next(cpi[0]);
			}
			else
			{
				game_pieces.get_tail()->set_next(game_pieces.get_head());
			}
		}
		else
		{
			// check the nature of previous shape
			int index_prev = cpi[size_cpi - 1]->imp - 1;
			// set the prev next
			// the prev element is no the same shape as our shifting so we affect him the current shap as next
			if (gpi[index_prev]->get_piece().get_color() != cpi[size_cpi - 1]->get_piece().get_color())
			{
				gpi[index_prev]->set_next(cpi[size_cpi - 1]);
			}
			cpi[size_cpi - 1]->set_next(gpi[cpi[size_cpi - 1]->imp + 1]);
		}
		// affect new gpi 
		gpi[cpi[size_cpi - 1]->imp] = cpi[size_cpi - 1];

		//                      midlle elements 
		for (int j = size_cpi - 2; j > 0; j--)
		{
			// set the current spi next to gpi + 1
			cpi[j]->set_next(gpi[cpi[j]->imp + 1]);

			// if the prev element is of different shape affect him the spi j as next
			if (gpi[cpi[j]->imp - 1]->get_piece().get_color() != cpi[j]->get_piece().get_color())
			{
				gpi[cpi[j]->imp - 1]->set_next(cpi[j]);
			}

			//afect gpi[spij->imp] the value spij
			gpi[cpi[j]->imp] = cpi[j];

		}

		//                      first element 
		cpi[0]->set_next(gpi[cpi[0]->imp + 1]);
		if (cpi[0]->imp == 0)
		{
			// if it's first change head and change tails next 
			game_pieces.set_head(cpi[0]);
			game_pieces.get_tail()->set_next(cpi[0]);
		}
		else
		{
			//if not the prev element in gpi should take him as next
			gpi[cpi[0]->imp - 1]->set_next(cpi[0]);
		}

		gpi[cpi[0]->imp] = cpi[0];




		/////////////////////////////////////////////////////////////////
		//        sort shapes based on imp and fix head an tail        //
		/////////////////////////////////////////////////////////////////
		//shape_node* debug_arr_shapes[4][10];
		int size;
		for (int i = 0; i < 4; i++)
		{
			size = shapes_heads[i].get_size();
			spis[i] = mergeSort(spis[i], 0, size - 1);

			//debug_copy(spis[i], size, debug_arr_shapes[i]);
			// set propper nexts and prev shapes
			if (size)
			{
				spis[i][0]->set_next_shape((size > 1) ? spis[i][1] : spis[i][0]);
				spis[i][0]->isp = 0;
				spis[i][0]->set_prev_shape((size > 1) ? spis[i][size - 1] : spis[i][0]);
				for (int j = 1; j < size - 1; j++)
				{
					spis[i][j]->set_next_shape(spis[i][j + 1]);
					spis[i][j]->set_prev_shape(spis[i][j - 1]);
					spis[i][j]->isp = j;
				}
				spis[i][size - 1]->set_next_shape((size > 1) ? spis[i][0] : spis[i][size - 1]);
				spis[i][size - 1]->set_prev_shape((size > 1) ? spis[i][size - 2] : spis[i][size - 1]);
				spis[i][size - 1]->isp = size - 1;
				shapes_heads[i].set_head(spis[i][0]);
				shapes_heads[i].set_tail(spis[i][size - 1]);
			}

			//debug_copy(spis[i], size, debug_arr_shapes[i]);

		}







	}
	else
	{
		//////////////////////////////////////
		//          initialisation          //
		// ///////////////////////////////////
		//decallage de forme d'indice choice%4
		// etablit tout les cpi
		choice = choice % 4;
		shape_node** cpis[4];
		for (int i = 0; i < 4; i++)
		{
			cpis[i] = create_cpi(i);
		}
		// eablit le spi de forme 
		shape_node** spi = create_spi(choice);
		int size_spi = shapes_heads[choice].get_size();
		if (size_spi < 2)return;
		/*shape_node* debug_spi[10];
		debug_copy(spi, size_spi, debug_spi);*/







		//////////////////////////////////////////////////////////
		//      sort the shapes and fix shape head & tail       //
		//////////////////////////////////////////////////////////
		shape_node* first_copy = spi[0];
		/*shape_node* debug_gpi[10];
		debug_copy(gpi, size_spi, debug_gpi);*/
		int tmp_imp = spi[size_spi - 1]->imp;
		shapes_heads[choice].set_tail(first_copy);
		shapes_heads[choice].set_head(first_copy->get_next_shape());
		/*shape_node* debug_arr_1[16];
		debug_copy(spi, size_spi, debug_arr_1);*/
		for (int i = 1; i < size_spi; i++)
		{
			int tmp_i = spi[i]->imp;
			spi[i]->imp = first_copy->imp;
			first_copy->imp = tmp_i;
			spi[i]->isp--;
			first_copy->isp++;
			spi[i - 1] = spi[i];

		}
		spi[size_spi - 1] = first_copy;
		/*shape_node* debug_arr[16];
		debug_copy(spi, size_spi, debug_arr);*/



		//////////////////////////////////////////////////////////
		//        sort the gpi and fix main head & tail        //
		//////////////////////////////////////////////////////////
		int size_gpi = game_pieces.get_size();
		/*shape_node* debug_arr_gpi_1[16];
		debug_copy(gpi, size_gpi, debug_arr_gpi_1);*/
		shape_node* prev_first_imp = gpi[spi[0]->imp];
		shape_node* tmp_spi_last = new shape_node(spi[size_spi - 1]->get_piece(), spi[size_spi - 1]->get_next(), spi[size_spi - 1]->get_next_shape(), spi[size_spi - 1]->get_next_color(), spi[size_spi - 1]->get_prev_shape(), spi[size_spi - 1]->get_prev_color());
		/*shape_node* debug_arr_spi_1[16];
		debug_copy(spi, size_spi, debug_arr_spi_1);*/


		//                                          first element
		// set propper tail
		if (game_pieces.get_tail()->get_piece().get_shape() == spi[0]->get_piece().get_shape()) {
			game_pieces.set_tail(spi[size_spi - 1]);
			// rightly configure the previous element
			// if the game piec before last one is different from shape we set it's next to the new tail otherwise we let it be
			if (gpi[size_gpi - 2]->get_piece().get_shape() != game_pieces.get_tail()->get_piece().get_shape())
			{
				gpi[size_gpi - 2]->set_next(game_pieces.get_tail());
			}
			// since it's tail the next elemnt is the new head if it changes and the same head if # color
			if (game_pieces.get_head()->get_piece().get_shape() == spi[size_spi - 1]->get_piece().get_shape())
			{
				game_pieces.get_tail()->set_next(spi[0]);
			}
			else
			{
				game_pieces.get_tail()->set_next(game_pieces.get_head());
			}
		}
		else
		{
			// check the nature of previous shape
			int index_prev = spi[size_spi - 1]->imp - 1;
			// set the prev next
			// the prev element is no the same shape as our shifting so we affect him the current shap as next
			if (gpi[index_prev]->get_piece().get_shape() != spi[size_spi - 1]->get_piece().get_shape())
			{
				gpi[index_prev]->set_next(spi[size_spi - 1]);
			}
			spi[size_spi - 1]->set_next(gpi[spi[size_spi - 1]->imp + 1]);
		}
		// affect new gpi 
		gpi[spi[size_spi - 1]->imp] = spi[size_spi - 1];
		/*debug_copy(gpi, size_gpi, debug_arr_gpi_1)*/;

		//                      midlle elements 
		for (int j = size_spi - 2; j > 0; j--)
		{
			// set the current spi next to gpi + 1
			spi[j]->set_next(gpi[spi[j]->imp + 1]);

			// if the prev element is of different shape affect him the spi j as next
			if (gpi[spi[j]->imp - 1]->get_piece().get_shape() != spi[j]->get_piece().get_shape())
			{
				gpi[spi[j]->imp - 1]->set_next(spi[j]);
			}

			//afect gpi[spij->imp] the value spij
			gpi[spi[j]->imp] = spi[j];

		}

		//                      first element 
		spi[0]->set_next(gpi[spi[0]->imp + 1]);
		if (spi[0]->imp == 0)
		{
			// if it's first change head and change tails next 
			game_pieces.set_head(spi[0]);
			game_pieces.get_tail()->set_next(spi[0]);
		}
		else
		{
			//if not the prev element in gpi should take him as next
			gpi[spi[0]->imp - 1]->set_next(spi[0]);
		}

		gpi[spi[0]->imp] = spi[0];




		/////////////////////////////////////////////////////////////////
		//        sort colors based on imp and fix head an tail        //
		/////////////////////////////////////////////////////////////////
		shape_node* debug_arr_shapes[4][3];
		int size;
		for (int i = 0; i < 4; i++)
		{
			size = colors_heads[i].get_size();
			cpis[i] = mergeSort(cpis[i], 0, size - 1);

			debug_copy(cpis[i], size, debug_arr_shapes[i]);
			// set propper nexts and prev shapes
			if (size)
			{
				cpis[i][0]->set_next_color((size > 1) ? cpis[i][1] : cpis[i][0]);
				cpis[i][0]->icp = 0;
				cpis[i][0]->set_prev_color((size > 1) ? cpis[i][size - 1] : cpis[i][0]);
				for (int j = 1; j < size - 1; j++)
				{
					cpis[i][j]->set_next_color(cpis[i][j + 1]);
					cpis[i][j]->set_prev_color(cpis[i][j - 1]);
					cpis[i][j]->icp = j;
				}
				cpis[i][size - 1]->set_next_color((size > 1) ? cpis[i][0] : cpis[i][size - 1]);
				cpis[i][size - 1]->set_prev_color((size > 1) ? cpis[i][size - 2] : cpis[i][size - 1]);
				cpis[i][size - 1]->icp = size - 1;
				colors_heads[i].set_head(cpis[i][0]);
				colors_heads[i].set_tail(cpis[i][size - 1]);
			}

			debug_copy(cpis[i], size, debug_arr_shapes[i]);

		}


	}
	Plateau* tmpc[4]; Plateau* tmps[4];
	for (int i = 0; i < 4; i++)
	{
		tmpc[i] = &colors_heads[i];
		tmps[i] = &shapes_heads[i];
	}
	shape_node* debug_arr_gpi_1[16];
	//keeppp 
	debug_copy(gpi, game_pieces.get_size(), debug_arr_gpi_1);
	if (this->Type != tepatrice)
	{
		this->score = game_pieces.evaluate_plate(tmpc, tmps);
	}
	else
	{
		game_pieces.evaluate_plate(tmpc, tmps);
	}

	return;

}
void Party::merge(shape_node* arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temporary arrays
	shape_node** L = new shape_node * [n1];
	shape_node** R = new shape_node * [n2];

	// Copy data to temporary arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	// Merge the temporary arrays back into arr[left..right]
	int i = 0; // Initial index of first subarray
	int j = 0; // Initial index of second subarray
	int k = left; // Initial index of merged subarray

	while (i < n1 && j < n2) {
		if (L[i]->imp <= R[j]->imp) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

shape_node** Party::mergeSort(shape_node* arr[], int left, int right) {
	if (left < right) {
		// Same as (left+right)/2, but avoids overflow
		int mid = left + (right - left) / 2;

		// Sort first and second halves
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		// Merge the sorted halves
		merge(arr, left, mid, right);
	}
	return arr;
}

shape_node** Party::create_gpi() {
	shape_node** gpi = new shape_node * [game_pieces.get_size()];
	shape_node* tmp = game_pieces.get_head();
	int size = game_pieces.get_size();
	for (int i = 0; i < size; i++)
	{
		gpi[i] = tmp;
		tmp = tmp->get_next();
	}
	return gpi;
}
shape_node** Party::create_spi(int index) {
	int size = shapes_heads[index].get_size();
	shape_node** spi = new shape_node * [size];
	shape_node* tmp = shapes_heads[index].get_head();
	for (int i = 0; i < size; i++)
	{
		spi[i] = tmp;
		tmp = tmp->get_next_shape();
	}
	return spi;
}
shape_node** Party::create_cpi(int index) {
	int size = colors_heads[index].get_size();
	shape_node** cpi = new shape_node * [size];
	shape_node* tmp = colors_heads[index].get_head();
	for (int i = 0; i < size; i++)
	{
		cpi[i] = tmp;
		tmp = tmp->get_next_color();
	}
	return cpi;
}
int Party::Tetriste() {
	this->Type = tetriste;
	//std::cout << "\nDEBUGGING: start";
	/*
	tag : Wonderful Code .SOF.
	usual std::thread(func_name); didn't work
	*/
	init_scene(1, false, false);
	std::thread thread_object(&Party::handle_time, this);

	while (!exited)
	{
		while (!paused) {
			////////////////////////////////////////////////
			///    handle player input and upadates      ///
			///////////////////////////////////////////////
			player_action(false, false, false);

			//evaluate plate and delete triplets

			//update list and score delete triplets and all 


			// and show it on the screen



			////////////////////////////////////////////
			///    Render game pieces in scene      ///
			///////////////////////////////////////////
			while (using_cursor) {}
			using_cursor = true;
			// erase old game pieces from console and show new state
			Menu::gotoxy(2, 2, "                                          ");
			Menu::gotoxy(2, 2, ' ');
			//Menu::gotoxy(5, 5, "DEBUGGING: after afficher goto");
			game_pieces.afficher(false);
			//Menu::gotoxy(5, 6, "DEBUGGING: after afficher fasle");
			using_cursor = false;






			/////////////////////////////////////////////////////
			///    Render and update  next pieces in scene    ///
			/////////////////////////////////////////////////////
			this->next_pieces.inserer_left(piece(4, 4));
			while (using_cursor) {}
			using_cursor = true;
			Menu::gotoxy(0, 0, "                  ");
			Menu::gotoxy(0, 0, " ");
			next_pieces.afficher(true);
			using_cursor = false;




			/////////////////////////////////////////////////////
			///      render the colors and shapes lists       ///
			/////////////////////////////////////////////////////
			render_colorsANDshapes();


		}

	}

	thread_object.join();
	std::cout << "\nDEBUGGING: tetris exit";
	_getch();
	return -1;
}
void Party::render_colorsANDshapes() {
	Menu::gotoxy(0, 3 + 6, "                                    ");
	Menu::gotoxy(0, 4 + 6, "                                    ");
	Menu::gotoxy(0, 5 + 6, "                                    ");
	Menu::gotoxy(0, 6 + 6, "                                    ");
	Menu::gotoxy(0, 7 + 6, "                                    ");
	Menu::gotoxy(0, 8 + 6, "                                    ");
	Menu::gotoxy(0, 9 + 6, "                                    ");
	Menu::gotoxy(0, 16, "                                    ");
	Menu::gotoxy(0, 17, "                                    ");
	Menu::gotoxy(0, 18, "                                    ");
	Menu::gotoxy(0, 9, "____________colors___________\n");
	for (int i = 0; i < 4; i++)
	{

		shape_node* tmp = colors_heads[i].get_head();
		shape_node* tail = colors_heads[i].get_tail();
		do
		{
			try
			{

				if (tmp)
				{
					tmp->get_piece().afficher();
					tmp = tmp->get_next_color();
				}
			}
			catch (...)
			{
				tmp == NULL;
			}


		} while (tmp != colors_heads[i].get_head());
		cout << endl;
	}
	cout << "______________sahpes____________\n";
	for (int i = 0; i < 4; i++)
	{
		shape_node* tmp = shapes_heads[i].get_head();
		do
		{
			try
			{

				if (tmp)
				{
					tmp->get_piece().afficher();
					tmp = tmp->get_next_shape();
				}
			}
			catch (...)
			{
				//tmp == NULL;
			}

		} while (tmp != shapes_heads[i].get_head());
		cout << endl;
	}
}

void Party::player_action(bool ai = false, bool dec = false, bool score = false) {

	int index_c = (int)(next_pieces.get_tail()->get_piece().get_color() - 1);
	int index_sh = (int)(next_pieces.get_tail()->get_piece().get_shape() - 1);

	// add while to enter either g or d and ignore the other inputs 
	char choice = 'a';
	do {
		using_cursor = true;
		choice = _getch();
		switch (choice)
		{
		case 'p':
			paused = true;
			pause_menu(ai, score);
			break;
		case 'd':
			if (dec)
			{
				chose_decallage();
			}
			break;
		default:
			break;
		}
		using_cursor = false;
	} while (choice != 75 && choice != 77);
	switch (choice)
	{
	case 75:
		//add right next_piece to game pieces 
		this->game_pieces.inserer_left(next_pieces.get_tail()->get_piece());
		// add it to the left of color and shape plates
		this->colors_heads[index_c].inserer_left_colors(&this->game_pieces, next_pieces.get_tail()->get_piece());
		this->shapes_heads[index_sh].inserer_left_shapes(&this->game_pieces, next_pieces.get_tail()->get_piece());
		this->score += this->game_pieces.supprimer3_left(&colors_heads, &shapes_heads);
		break;
	case 77:
		//add right next_piece to game pieces 
		this->game_pieces.inserer_right(next_pieces.get_tail()->get_piece());
		// add it to the right of color and shape plates
		this->colors_heads[index_c].inserer_right_colors(&this->game_pieces, next_pieces.get_tail()->get_piece());
		this->shapes_heads[index_sh].inserer_right_shapes(&this->game_pieces, next_pieces.get_tail()->get_piece());
		this->score += this->game_pieces.supprimer3_right(&(this->colors_heads), &(this->shapes_heads));

		break;

	}
	this->next_pieces.set_size(next_pieces.get_size() - 1);
	shape_node* prv = next_pieces.get_head();
	while (prv->get_next() != next_pieces.get_tail()) {
		prv = prv->get_next();
	}
	next_pieces.set_tail(prv);
	delete prv->get_next();
}
// next : L C
void Party::init_scene(int size, bool ai, bool score) {
	system("cls");
	Menu::gotoxy(Menu::timer_x, Menu::timer_y, "                                                    ");

	Menu::gotoxy(0, Menu::timer_y - 1, ' ');
	cout << "Time :";
	if (score)
	{
		Menu::gotoxy(14, Menu::timer_y - 1, ' ');
		cout << "Score : " << this->score;
	}
	//generated the waiting quee
	for (int i = 0; i < size; i++)
	{
		this->next_pieces.inserer_left(piece(4, 4));
	}
	//this->next_elements = new shape_node[i];
	Menu::gotoxy(0, 0, ' ');
	this->next_pieces.afficher(true);
}


void Party::handle_time() {
	//start game & timer
	//std::chrono::seconds time_elapsed = std::chrono::seconds(0);

	while (!exited) {
		std::chrono::system_clock::time_point old;
		int time = 120;
		old = std::chrono::system_clock::now();

		while (!paused)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			Menu::gotoxy(Menu::timer_x, Menu::timer_y - 1, "     ");
			Menu::gotoxy(Menu::timer_x, Menu::timer_y - 1, ' ');
			cout << --time;
			if (this->Type != tetriste && this->Type != tepatrice)
			{
				Menu::gotoxy(14, Menu::timer_y - 1, ' ');
				cout << "Score : " << this->score;
			}


		}
		auto time_elapsed = std::chrono::system_clock::now() - old;
		auto time_rest = this->party_time - time_elapsed;
		this->party_time = std::chrono::duration_cast<std::chrono::seconds>(time_rest);
		//party_time = std::chrono::seconds(std::chrono::duration_cast<std::chrono::seconds > (party_time).count() - std::chrono::duration_cast<std::chrono::seconds>(this->party_time).count());
		//std::cout << "\nDEBUGGING: time elapsed since pause or start  : " << std::chrono::duration_cast<std::chrono::seconds>(time_elapsed).count();
		//std::cout << "\nDEBUGGING: time left calculated  out of 2mins  : " << std::chrono::duration_cast<std::chrono::seconds>(time_rest).count();
		//std::cout << "\nDEBUGGING: time left affected  out of 2mins  : " << std::chrono::duration_cast<std::chrono::seconds>(time_rest).count();
		//_getch();
		/*pause_menu();*/


	}
	//end game & timer
}