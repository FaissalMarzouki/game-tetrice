#include "Design.h"
#include "raylib.h"
#include <thread>
#include<iostream>
#include <string> // Add this line for std::string
#include <sstream> // Add this line for std::stringstream

std::string intToString(int number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}
float Design::spaceLeft = 0.0f;
float Design::spaceRight = 0.0f;

Design::Design() {

	rotation = 45.0f;
	InitWindow(screenWidth, screenHeight, "Dessiner des formes");
	SetTargetFPS(60);
	font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
	Color colors[] = { BLUE, YELLOW, RED, GREEN };
}

void Design::drawPlateau(Plateau* myP)
{
	shape_node* tempo = myP->get_head();
	//a besoin d'amelioration
	for (int i = 0; i < myP->get_size(); i++) {
		piece* pieceTempo = new piece(tempo->get_piece().get_shape(), tempo->get_piece().get_color(),
			float(80.0f * (i + 1)), float(375.0f));
		drawPiece(*pieceTempo);
		tempo = tempo->get_next();
	}
}
void Design::drawNextPlateau(Plateau* nextFives)
{
	shape_node* tempo = nextFives->get_head();
	//a besoin d'amelioration
	for (int i = 0; i < nextFives->get_size(); i++) {
		piece* pieceTempo = new piece(tempo->get_piece().get_shape(), tempo->get_piece().get_color(),
			float(720.0f + (80.0f * i)), float(140.0f));
		drawPiece(*pieceTempo);
		tempo = tempo->get_next();
	}
}

void Design::drawPiece(piece p) {
	Color raylibColor;
	switch (p.get_color()) {
	case Red:
		raylibColor = RED;
		break;
	case Green:
		raylibColor = GREEN;
		break;
	case Yellow:
		raylibColor = YELLOW;
		break;
	case Blue:
		raylibColor = BLUE;
		break;
	default:
		raylibColor = WHITE;
		break;
	}
	switch (p.get_shape()) {
	case Cercle:
		DrawCircle(static_cast<float>(p.get_X()), static_cast<float>(p.get_Y() + 10), 25.0f, raylibColor);
		break;
	case Rhombus:
		DrawRectanglePro(Rectangle{ static_cast<float>(p.get_X()), static_cast<float>(p.get_Y() + 20), 40.0f, 40.0f }, { 20.0f, 20.0f }, 45.0f, raylibColor);
		break;
	case Square:
		DrawRectangleRec(Rectangle{ static_cast<float>(p.get_X()), static_cast<float>(p.get_Y()), 40.0f, 40.0f }, raylibColor);
		break;
	case Triangle:
		DrawTriangle({ static_cast<float>(p.get_X()), static_cast<float>(p.get_Y() + 40) },
			{ static_cast<float>(p.get_X()) + 60.0f, static_cast<float>(p.get_Y() + 40) },
			{ static_cast<float>(p.get_X()) + 30.0f, static_cast<float>(p.get_Y() + 40) - 55.0f },
			raylibColor);
		break;



	default:
		break;
	}
}

void Design::supprimer_left_sample(Plateau* p)
{


	shape_node* supp = p->get_head();
	p->get_tail()->set_next(supp->get_next());
	p->set_head(p->get_head()->get_next());
	supp->set_next(nullptr);
	p->set_size(p->get_size() - 1);
	delete(supp);
}
shape_node** Design::create_gpi() {
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
shape_node** Design::create_spi(int index) {
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
shape_node** Design::create_cpi(int index) {
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
void Design::merge(shape_node* arr[], int left, int mid, int right) {
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
shape_node** Design::mergeSort(shape_node* arr[], int left, int right) {
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
void Design::debug_copy(shape_node** tab, int size, shape_node** res) {
	for (size_t i = 0; i < size; i++)
	{
		res[i] = tab[i];
	}

}
void Design::decallage_gauche(int choice, int& score)
{
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

	score = game_pieces.evaluate_plate(tmpc, tmps);

	return;

}
/*render next pieces en plateaux et mettre en render principale*/
void Design::render()
{
	int score = 0;
	//insertion de pateau de 5 prochains pieces
	for (int i = 0; i < 5; i++)
	{
		piece randShape(4, 4);
		nextFivePiece->inserer_right(randShape);
	}
	bool exitFlag = false;
	bool started = false;
	bool paused = false;
	bool gameover = false;
	int gameoverTimer = 600;
	int totalTime = 3600;
	bool about = false;
	bool controle = false;
	// Total time in 3600 seconds
	int currentTime = totalTime;
	// Current time starts at the total time

	while (WindowShouldClose() != true && !exitFlag) {
		if (nextFivePiece->get_size() == 4) {
			piece randShape(4, 4);
			nextFivePiece->inserer_right(randShape);
		}
		/*------------------------------------------------------------*/
		BeginDrawing();
		ClearBackground(BLACK);

		int index_c = (int)(nextFivePiece->get_head()->get_piece().get_color() - 1);
		int index_sh = (int)(nextFivePiece->get_head()->get_piece().get_shape() - 1);



		//
		Rectangle newGameButton = { screenWidth / 2 - 100, 180, 200, 50 };
		Rectangle loadGameButton = { screenWidth / 2 - 100, 250, 200, 50 };
		Rectangle highScoreButton = { screenWidth / 2 - 100, 320, 200, 50 };
		Rectangle controlesButton = { screenWidth / 2 - 100, 390, 200, 50 };
		Rectangle aboutButton = { screenWidth / 2 - 100, 460, 200, 50 };
		Rectangle Exit = { screenWidth / 2 - 100, 530, 200, 50 };
		Rectangle quit = { screenWidth / 2 - 100, 650, 200, 50 };

		// Draw buttons
		if (!started && !about && !controle) {

			DrawText("Tevalide Game", screenWidth / 2 - MeasureText("Main Menu", 40) / 2, 50, 40, WHITE);
			DrawRectangleRec(newGameButton, DARKGREEN);
			DrawText("New Game", newGameButton.x + 20, newGameButton.y + 15, 20, GREEN);

			DrawRectangleRec(loadGameButton, SKYBLUE);
			DrawText("Load Game", loadGameButton.x + 20, loadGameButton.y + 15, 20, DARKBLUE);

			DrawRectangleRec(highScoreButton, DARKPURPLE);
			DrawText("High Score", highScoreButton.x + 20, highScoreButton.y + 15, 20, PURPLE);

			DrawRectangleRec(controlesButton, DARKBROWN);
			DrawText("Controls", controlesButton.x + 20, controlesButton.y + 15, 20, LIGHTGRAY);

			DrawRectangleRec(aboutButton, DARKGRAY);
			DrawText("About", aboutButton.x + 20, aboutButton.y + 15, 20, LIGHTGRAY);

			DrawRectangleRec(Exit, MAROON);
			DrawText("Exit", Exit.x + 20, Exit.y + 15, 20, BLACK);



		}
		// Check for button clicks
		if ((started || (CheckCollisionPointRec(GetMousePosition(), newGameButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))))
		{
			if (IsKeyPressed(KEY_SPACE))
				paused = !paused;
			DrawRectangleRec(quit, MAROON);
			DrawText("Quit", quit.x + 20, quit.y + 15, 20, BLACK);

			int timeRemaining = max(0, currentTime);
			if (!paused) {
				if (game_pieces.get_size() <= 15)
				{
					if (nextFivePiece->get_size() == 5 && !exitFlag)
					{
						userInput(index_c, index_sh, score);
					}
					//fonction de pause le jeu 
					// fonction de pause le jeu (game over) avant de sortie si si le size de plateau == 15 pieces  
					//marquer les points a chaque supression

					scene(timeRemaining);

					DrawText(TextFormat("%d", score), 150, 130, 30, BLACK);

					started = true;

					drawNextPlateau(nextFivePiece);
					drawPlateau(&game_pieces);
					currentTime--;
					//fonction save()
				}
				else {
					DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 40) / 2, screenHeight / 2 - 20, 40, RED);
					gameoverTimer--; // Decrement the timer
					DrawText(TextFormat("TRY AGAIN: %ds", gameoverTimer / 60), screenWidth / 2 - MeasureText("Timer: 10s", 20) / 2, screenHeight / 2 + 20, 20, RED);
					if (gameoverTimer == 0 || IsKeyPressed(KEY_ENTER))
					{
						started = false;
					}
				}

			}
			else
			{
				DrawText("Paused", 400, 200, 40, GREEN);
				scene(timeRemaining);
				started = true;
			}
			if (timeRemaining <= 0) {
				started = false;
				exitFlag = true;
			}
		}
		else if (started || (CheckCollisionPointRec(GetMousePosition(), loadGameButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
		{
			// fonction load()  
		}
		else if (started || (CheckCollisionPointRec(GetMousePosition(), highScoreButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
		{
			//fontion of best_score() 
		}
		else if (controle || (CheckCollisionPointRec(GetMousePosition(), controlesButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
		{
			//affichage les informations de controle

			// Draw the title
			DrawRectangleRec({ screenWidth / 2 - 200, 20, 400, 50 }, WHITE);
			DrawText("About", screenWidth / 2 - MeasureText("About", 40) / 2, 25, 40, BLACK);

			// Draw the keyboard layout section
			DrawRectangleRec({ 50, 100, 800, 40 }, WHITE);
			DrawText("Keyboard Layout:", 60, 110, 30, BLACK);

			// Draw the movement keys
			DrawRectangleRec({ 50, 150, 300, 80 }, WHITE); // Left Arrow Key
			DrawText("<-", 120, 180, 40, BLACK);
			DrawText("Insert Left", 60, 240, 20, BLACK);

			DrawRectangleRec({ 400, 150, 300, 80 }, WHITE); // Right Arrow Key
			DrawText("->", 470, 180, 40, BLACK);
			DrawText("Insert Right", 410, 240, 20, BLACK);

			DrawRectangleRec({ 750, 150, 300, 80 }, WHITE); // Space Key
			DrawText("|___space___|", 820, 180, 20, BLACK);
			DrawText("Pause", 820, 240, 20, BLACK);

			// Draw the shift keys
			DrawRectangleRec({ 50, 250, 300, 80 }, WHITE); // D Key
			DrawText("D", 120, 280, 40, BLACK);
			DrawText("Press 'D' + Number", 60, 340, 15, WHITE); // Explanation
			DrawText("to Shift", 120, 360, 15, WHITE); // Explanation

			// Draw the decallage keys
			DrawRectangleRec({ 400, 250, 300, 80 }, WHITE); // 0 Key
			DrawText("0", 470, 280, 40, BLACK);
			DrawText("Decallage Red", 410, 330, 20, BLACK);

			DrawRectangleRec({ 750, 250, 300, 80 }, WHITE); // 1 Key
			DrawText("1", 820, 280, 40, BLACK);
			DrawText("Decallage Green", 760, 330, 20, BLACK);

			DrawRectangleRec({ 50, 350, 300, 80 }, WHITE); // 2 Key
			DrawText("2", 120, 380, 40, BLACK);
			DrawText("Decallage Yellow", 60, 430, 20, BLACK);

			DrawRectangleRec({ 400, 350, 300, 80 }, WHITE); // 3 Key
			DrawText("3", 470, 380, 40, BLACK);
			DrawText("Decallage Blue", 420, 430, 20, BLACK);

			DrawRectangleRec({ 750, 350, 300, 80 }, WHITE); // 4 Key
			DrawText("4", 820, 380, 40, BLACK);
			DrawText("Decallage Circle", 760, 430, 20, BLACK);

			DrawRectangleRec({ 50, 450, 300, 80 }, WHITE); // 5 Key
			DrawText("5", 120, 480, 40, BLACK);
			DrawText("Decallage Diamond", 60, 530, 20, BLACK);

			DrawRectangleRec({ 400, 450, 300, 80 }, WHITE); // 6 Key
			DrawText("6", 470, 480, 40, BLACK);
			DrawText("Decallage Square", 420, 530, 20, BLACK);

			DrawRectangleRec({ 750, 450, 300, 80 }, WHITE); // 7 Key
			DrawText("7", 820, 480, 40, BLACK);
			DrawText("Decallage Triangle", 760, 530, 20, BLACK);


			controle = true;

		}
		else if (about || (CheckCollisionPointRec(GetMousePosition(), aboutButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
		{
			//affichage les metadonnee de jeu

			about = true;

		}
		else if (started || (CheckCollisionPointRec(GetMousePosition(), Exit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
		{
			//fontion comfirmation 
			exitFlag = true;
		}
		/*-----------------------------------------*/




		EndDrawing();
	}

	CloseWindow();
}
Design::~Design() {
}



void Design::scene(int timeRemaining)
{
	DrawTextEx(font, "Score", { 100, 50 }, 38, 2, WHITE);
	DrawRectangleRounded({ 100, 120, 170, 60 }, 0.3, 6, RAYWHITE); // score
	DrawTextEx(font, "NEXT \n\nSHAPE", { 700, 15 }, 38, 2, WHITE);
	DrawTextEx(font, "Time", { 400, 15 }, 38, 2, WHITE);
	DrawRectangleRounded({ 380, 80, 170, 60 }, 0.3, 6, RAYWHITE); // time
	DrawText(TextFormat("%02d:%02d", timeRemaining / 60, timeRemaining % 60), 400, 85, 38, BLACK);
	DrawRectangleRounded({ 0, 340, screenWidth, 100 }, 0.3, 6, RAYWHITE);
}

void Design::userInput(int index_c, int index_sh, int& score)
{
	//insertion par des button fleshes droit et gauche
	if (IsKeyPressed(KEY_RIGHT)) {
		game_pieces.inserer_right(nextFivePiece->get_head()->get_piece());
		colors_heads[index_c].inserer_right_colors(&game_pieces, nextFivePiece->get_tail()->get_piece());
		shapes_heads[index_sh].inserer_right_shapes(&game_pieces, nextFivePiece->get_tail()->get_piece());
		//supression des des pieces identique 
		score += game_pieces.supprimer3_right(&colors_heads, &shapes_heads);
		supprimer_left_sample(nextFivePiece);


	}
	else if (IsKeyPressed(KEY_LEFT)) {
		game_pieces.inserer_left(nextFivePiece->get_head()->get_piece());
		colors_heads[index_c].inserer_left_colors(&game_pieces, nextFivePiece->get_tail()->get_piece());
		shapes_heads[index_sh].inserer_left_shapes(&game_pieces, nextFivePiece->get_tail()->get_piece());
		//supression des des pieces identique 
		score += game_pieces.supprimer3_left(&colors_heads, &shapes_heads);
		supprimer_left_sample(nextFivePiece);

	}

	//fontion decalage a gauche 
	// 
	// 
	if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
		/*
		note:
		switch based on choice :
		KEY0 = > decallage rouge;
		KEY1 = > decallage vert;
		KEY2 = > decallage jaune;
		KEY3 = > decallage blue;
		KEY4 = > decallage cercle;
		KEY5 = > decallage losange;
		KEY6 = > decallage carre;
		KEY7 = > decallage triangle;
		*/

		if (IsKeyPressed(KEY_ZERO))
			// Decallage rouge
			decallage_gauche(0, score);
		else if (IsKeyPressed(KEY_ONE))
			// Decallage vert
			decallage_gauche(1, score);
		else if (IsKeyPressed(KEY_TWO))
			// Decallage jaune
			decallage_gauche(2, score);
		else if (IsKeyPressed(KEY_THREE))
			// Decallage blue
			decallage_gauche(3, score);
		else if (IsKeyPressed(KEY_FOUR))
			// Decallage cercle
			decallage_gauche(4, score);
		else if (IsKeyPressed(KEY_FIVE))
			// Decallage losange
			decallage_gauche(5, score);
		else if (IsKeyPressed(KEY_SIX))
			// Decallage carre
			decallage_gauche(6, score);
		else if (IsKeyPressed(KEY_SEVEN))
			// Decallage triangle
			decallage_gauche(7, score);
	}
}
