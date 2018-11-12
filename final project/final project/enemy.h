void game_over_fun();
void life_level();
void next_level();
void mesail_draw();


typedef struct soldier_st
{
	int x;
	int index;
} soldier_st;

struct soldier_st soldier[num_of_soldier];


// used to exploision soldiers

void exploison()
{
	boma++;
}

void mesail_draw()
{
	if (mesail_exploision_flag == 0)
		iShowBMP2(mesail_x, mesail_y, "mesaile.bmp",0);
	else
	{
		mesail_exploision_flag++;
		iShowBMP2(mesail_boom_x, mesail_boom_y, "plane_boom.bmp", 0);
		if (mesail_exploision_flag >= 6) mesail_exploision_flag = 0;
	}
}
void aeroplane_draw()
{

	if (plane_exploision_flag == 0)
		iShowBMP2(plane_x, 450, "plane.bmp", 0);
	else
	{
		plane_exploision_flag++;
		iShowBMP2(plane_boom_x, 450, "plane_boom.bmp", 0);
		if (plane_exploision_flag >= 6) plane_exploision_flag = 0;
	}


}

void pause_enemy()
{
	iPauseTimer(pause_fun_aeroplane);
	iPauseTimer(pause_fun_soldier);
	iPauseTimer(pause_fun_truck);
	iPauseTimer(pause_fun_mesail);
}
void resume_enemy()
{
	iResumeTimer(pause_fun_aeroplane);
	iResumeTimer(pause_fun_soldier);
	iResumeTimer(pause_fun_truck);
	iResumeTimer(pause_fun_mesail);
}

// brings  soldiers
void reset_soldier_position(int i)
{
	if (level_new >= 2) distance = 230;

	if (i>num_of_soldier - 1) return;
	soldier[i].x = screenwidth + i* distance;
	soldier[i].index = 0;
	i++;
	plane_x = 1300;
	truck_x = 1250;
	reset_soldier_position(i);
}
void soldier_fun()
{
	if (level_new >= 1 && flag == 1)
	{

		for (i = 0; i<num_of_soldier; i++)
		{
			soldier[i].x -= soldier_speed;
			soldier[i].index++;
			if (soldier[i].index == 7) soldier[i].index = -1;
			soldier[i].index++;
			if (soldier[i].x <= 300)
			{
				soldier_index = 0;
				if (i != 0)
					soldier[i].x = soldier[i - 1].x + distance;
				else
					soldier[i].x = soldier[num_of_soldier - 1].x + distance;
				life--;
				
				if (life <= 0)
				{
					game_over++;

				}
			}
			if (soldier[i].x <= bulletx && soldier[i].x + 180 >= bulletx&&bullety <= 180 && bullety >= 0 && bulletx <= screenwidth)
			{
				boma_x = soldier[i].x;
				soldier_index = 0;
				if (i != 0)
					soldier[i].x = soldier[i - 1].x + distance;
				else
					soldier[i].x = soldier[num_of_soldier - 1].x + distance;
				bulletx = 0;

				bullety = 0;
				bullradius = 0;
				points++;
				timechange = 1;
				timeMax = 0;
				check = 0;
				bullradius = 0;
				exploison();
			}
		}
	}
}

// Used to show plane exploision

void plane_exploison()
{
	plane_exploision_flag++;
}
void mesail_exploison()
{
	mesail_exploision_flag++;
}

// brings enemy plane

void aeroplane()
{
	if (gamestate >= 5 && flag == 1)
	{
		plane_x -= 4;
		if (plane_x <= 300)
		{

			plane_x = 1540;
			life--;
			if (life <= 0)
				game_over++;
		}


		if (plane_x <= bulletx && plane_x + 180 >= bulletx&&bullety <= 599 && bullety >= 450)
		{
			boma_x = plane_x;
			plane_boom_x = plane_x;

			plane_x = 1400;
			bulletx = 0;

			bullety = 0;
			bullradius = 0;
			points++;
			timechange = 1;
			timeMax = 0;
			check = 0;
			points += 2;
			plane_exploison();
		}
	}
}

void truck_fun()
{
	if (level_new >= 3 && flag == 1)
	{
		truck_x -= 4;
		if (truck_x <= 300)
		{
			truck_index = 0;
			truck_x = 1240;
			life--;
			if (life <= 0)
				game_over++;
		}
		if (truck_index == 0) truck_index = 1;
		else if (truck_index == 1) truck_index = 0;
		else if (truck_index == 3) truck_index = 2;
		else if (truck_index == 2) truck_index = 3;
		else if (truck_index == 5) truck_index = 4;
		else if (truck_index == 4)truck_index = 5;

		if (truck_x <= bulletx && truck_x + 460 >= bulletx&&bullety <= 220 && bullety >= 0 && bulletx <= screenwidth)
		{
			if (truck_index<4)
			{
				if (truck_index % 2 != 0)
					truck_index++;
				else 
					truck_index += 2;
				bulletx = 0;

				bullety = 0;
				bullradius = 0;
				points++;
				timechange = 1;
				timeMax = 0;
				check = 0;
			}
			else
			{
				boma_x = truck_x;
				truck_x = 1240;
				truck_index = 0;

				bulletx = 0;

				bullety = 0;
				bullradius = 0;
				points++;
				timechange = 1;
				timeMax = 0;
				check = 0;
				points++;

				exploison();
			}
		}
	}
}

void mesail()
{
	if (level_new ==10 && flag == 1)
	{
		mesail_x -= 4;
		if (mesail_y < 220) mesail_y = mesail_y + 220;
		else if (mesail_y>450) mesail_y = mesail_y - 150;
		if (mesail_x <= 300)
		{
			mesail_x = 1240;
			mesail_y = rand() % 600;
			if (mesail_y < 220) mesail_y = mesail_y + 220;
			else if (mesail_y>450) mesail_y = mesail_y - 150;
			life -= 1;
			if (life <= 0)
				game_over++;
		}
		if (mesail_x <= bulletx && (mesail_x + mesail_width) >= bulletx && bullety <= mesail_y + mesail_height && bullety >= mesail_y && bulletx <= screenwidth)
		{
			
			mesail_boom_x = mesail_x;
			mesail_boom_y = mesail_y;
			mesail_x = 1260;
			mesail_y = rand()%600; 
			if (mesail_y < 220) mesail_y = mesail_y + 220;
			else if (mesail_y>450) mesail_y = mesail_y - 150;
			bulletx = 0;
			bullety = 0;
			bullradius = 0;
			points++;
			timechange = 1;
			timeMax = 0;
			check = 0;
			mesail_exploison();
		}
	}

}

void game_over_fun()
{
	if (game_over == 1)
	{
		iPauseTimer(pause_fun_aeroplane);
		iPauseTimer(pause_fun_soldier);
		iPauseTimer(pause_fun_truck);
		iSetColor(0, 255, 100);
		iFilledRectangle(600, 300, 150, 50);
		iSetColor(255, 25, 25);
		iText(620, 320, "Game Over !", GLUT_BITMAP_TIMES_ROMAN_24);
		sorthighscore();
	}
}

void next_level()
{
	if (points >= level1_points*level_new)
	{
		pause_enemy();
		iShowBMP(480, 300, "completebutton.bmp");
		iSetColor(25, 25, 25);
		sprintf(level_complete, "Level %d completed", level_new);
		iText(520, 320, level_complete, GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 0, 255);
		iText(520, 220, "Press R to continue", GLUT_BITMAP_TIMES_ROMAN_24);



	}
}



void life_level()
{
	sprintf_s(life_s, "Life = %d", life);
	//iSetColor(25, 25, 255);
	//iFilledRectangle(0, 560, 100, 50);
	iShowBMP(0, 570, "points.bmp");
	iSetColor(255, 255, 255);
	iText(20, 580, life_s, GLUT_BITMAP_TIMES_ROMAN_10);
	sprintf_s(point_s, "Points =  %d", points);
	//iSetColor(25, 25, 255);
	//iFilledRectangle(105, 560, 100, 50);
	iShowBMP(100, 570, "points.bmp");
	iSetColor(255, 255, 255);
	iText(115, 580, point_s, GLUT_BITMAP_TIMES_ROMAN_10);
	iShowBMP(200, 570, "points.bmp");
	sprintf_s(level_s, "Level = %d", level_new);
	iText(215, 580, level_s, GLUT_BITMAP_TIMES_ROMAN_10);
}


void soldier_level1()
{
	for (i = 0; i<6; i++)
	{
		iShowBMP2(soldier[i].x, 0, soldier_pic[soldier[i].index], 0);

	}
	if (boma != 0)
	{
		boma++;
		printf("%d\n", boma);
		iShowBMP2(boma_x, 0, "boom.bmp", 0);
		if (boma >= exploison_time) boma = 0;
	}

}






void truck_draw()
{
	iShowBMP2(truck_x, 0, truck[truck_index], 255);
	if (boma != 0)
	{
		boma++;
		printf("%d\n", boma);
		iShowBMP2(boma_x, 0, "boom.bmp", 0);
		if (boma >= exploison_time) boma = 0;
	}
}
