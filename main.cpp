#include <iostream>
#include "graphics.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <string>
using namespace std;



int randomGem()				//generating a random gem
{
	int ret;
	ret = rand()%5 + 1;
	return ret;
}

void randomizeArray(int array[][8])			//randomizing array for random gems
{
srand(time(0));
int temp;

	for (int i = 0; i < 8; i++)
	{
		for  (int j = 0; j < 8; j++)
		{
			temp = randomGem();
			array[i][j] = temp;
			
		}
	}
	
}

void printArray(int array[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

void grid()					//displaying grid
{	
	int tempx = 70;
	int tempy = 70;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			setcolor(DARKGRAY);
			rectangle(tempx + 60*i, tempy + 60*j, tempx + 60*i + 60, tempy + 60*j + 60);
		}
	}	
}

void displayArray(int array[][8])			//displaying array of integers as gems
{
	int tempx = 100;  //top left
	int tempy = 100;
	int colores;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{	
			if (array[i][j] == 1)
				readimagefile("red2.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);  //gem images imported
			else if (array[i][j] == 2)
				readimagefile("blue2.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == 3)
				readimagefile("green2.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == 4)
				readimagefile("yellow2.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == 5)
				readimagefile("cyan2.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);	
			else if (array[i][j] == 6)
				readimagefile("flamered.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == 7)
				readimagefile("flameblue.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == 8)
				readimagefile("flamegreen.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == 9)
				readimagefile("flameyellow.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == 10)
				readimagefile("flamecyan.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);	
			else if (array[i][j] == 0)
				readimagefile("blackblackblackblack.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			else if (array[i][j] == -1)
				readimagefile("destroyergem.jpg", tempx + 60*i - 20, tempy + 60*j - 20, tempx + 60*i + 20, tempy + 60*j + 20);
			

			
				
								
	}	
}
}

void destroy(int array[][8],int gem, int &score)		//takes a gem, and destroys all of that particular gem from the board
{
	for(int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (array[i][j] == gem)
			{
				array[i][j] = 0;
				score = score + 20;
			}
		}
	}
	
}

void mySwap(int array[][8], int gem1x, int gem1y, int gem2x, int gem2y, int &score) //for swapping gems
{
	int g1i = (gem1x - 70)/60;					//conversion gem coords to i and j of arrays
	int g1j = (gem1y - 70)/60;
	int g2i = (gem2x - 70)/60;
	int g2j = (gem2y - 70)/60;
	swap(array[g1i][g1j], array[g2i][g2j]);	
	if(array[g1i][g1j] == -1)					//checking if the swap is made with a destroyer gem
	{
		array[g1i][g1j] = 0;
		destroy(array,array[g2i][g2j], score);
	
	}
	else if(array[g2i][g2j] == -1)
	{
		array[g2i][g2j] = 0;
		destroy(array,array[g1i][g1j], score);
		
	}
}
		

int flame(int gem)		//assigning flame gems according to color of gems (red gem becomes red flame gem)
{
	if (gem == 1)
	{
		return 6;
	}
	if (gem == 2)
	{
		return 7;
	}
	if (gem == 3)
	{
		return 8;
	}
	if (gem == 4)
	{
		return 9;
	}
	if (gem == 5)
	{
		return 10;
	}
return 0;	
}
		
		
void checkElbow(int array[][8], int &score, int turncounter)			//check for elbows 
{
	for(int j = 0; j < 6; j++)
	{
		for(int i = 0; i < 6; i++)
		{
			if(array[i][j] == array[i+1][j] && array[i][j] == array[i+2][j])
			{
				if(array[i][j] == array[i][j+1] && array[i][j] == array[i][j+2])
				{
					array[i][j] = -1;
					
					array[i+1][j] = 0;
					array[i+2][j] = 0;
					
					array[i][j+1] = 0;
					array[i][j+2] = 0;
				}
				if(array[i+2][j] == array[i+2][j+1] && array[i+2][j] == array[i+2][j+2])
				{
					array[i+2][j] = -1;
					
					array[i+1][j] = 0;
					array[i][j] = 0;
					
					array[i+2][j+1] = 0;
					array[i+2][j+2] = 0;
					
				}
				if(array[i][j] == array[i][j-1] && array[i][j] == array[i][j-2])
				{
					array[i][j] = -1;
					
					array[i+1][j] = 0;
					array[i+2][j] = 0;
					
					array[i][j-1] = 0;
					array[i][j-2] = 0;	
				}
				if(array[i+2][j] == array[i+2][j-1] && array[i+2][j] == array[i+2][j-2])
				{
					array[i+2][j] = -1;
					
					array[i+1][j] = 0;
					array[i][j] = 0;
					
					array[i+2][j-1] = 0;
					array[i+2][j-2] = 0;
					
				}


			}
		}
		
	}	
}	


	
		
void horizontalFlameMatch(int array[][8], int &score, int turncounter)			//horizontal match for flame gems and corresponding color gems	
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (array[i][j]%5 == array[i+1][j]%5 && array[i][j]%5 == array[i+2][j]%5)
			{
				if (array[i][j] != 0)
				{
					array[i][j-1] = 0;
					array[i+1][j-1] = 0;
					array[i+2][j-1] = 0;
					
					array[i][j] = 0;
					array[i+1][j] = 0;
					array[i+2][j] = 0;
					
					array[i][j+1] = 0;
					array[i+1][j+1] = 0;
					array[i+2][j+1] = 0;
					
					if (turncounter > 0)
					{
					score = score + 150;
					}
				}
			}
			
		}
	}
}

void verticalFlameMatch(int array[][8], int &score, int turncounter)			//vertical match for flame gems and corresponding color gems	
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (array[i][j]%5 == array[i][j+1]%5 && array[i][j]%5 == array[i][j+2]%5)		
			{
				if (array[i][j] != 0)						//modulus used because mod of flame gems and corresponding color gems are equal
				{
					array[i-1][j] = 0;
					array[i-1][j+1] = 0;
					array[i-1][j+2] = 0;
					
					array[i][j] = 0;
					array[i][j+1] = 0;
					array[i][j+2] = 0;
					
					array[i+1][j] = 0;
					array[i+1][j+1] = 0;
					array[i+1][j+2] = 0;
					
					
					if (turncounter > 0)
					{
					score = score + 150;
					}
				}
			}
			
		}
	}
}
			
		
void vertical4Match(int array[][8], int &score, int turncounter)			//matching 4 same vertical gems
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (array[i][j] == array[i][j+1] && array[i][j] == array[i][j+2] && array[i][j] == array[i][j+3])
			{
				array[i][j] = 0;
				array[i][j+1] = flame(array[i][j+1]);
				array[i][j+2] = 0;
				array[i][j+3] = 0;
				if (turncounter > 0)
					score = score + 100;
			}
			
		}
	}
			
}

void horizontal4Match(int array[][8], int &score, int turncounter)			//matching 4 same horizontal gems
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (array[i][j] == array[i+1][j] && array[i][j] == array[i+2][j] && array[i+3][j] == array[i][j])
			{
				array[i][j] = 0;
				array[i+1][j] = flame(array[i+1][j]);
				array[i+2][j] = 0;
				array[i+3][j] = 0;
				if (turncounter > 0)
					score = score + 100;
			}
			
		}
	}
			
}

void verticalMatch(int array[][8], int &score, int turncounter)			//to check if a vertical match is made, replaces all matched values with 0
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (array[i][j] == array[i][j+1] && array[i][j] == array[i][j+2])
			{
				if (array[i][j]!= 0)
				{
					array[i][j] = 0;
					array[i][j+1] = 0;
					array[i][j+2] = 0;
					if (turncounter > 0)
					{
					score = score + 50;
					}
				}
				
			}
		}
	}
}

void horizontalMatch(int array[][8], int &score, int turncounter)			//to check if a horizontal match is made, replaces all matches values with 0
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (array[i][j] == array[i+1][j] && array[i][j] == array[i+2][j])
			{
				if (array[i][j] != 0)
				{
					array[i][j] = 0;
					array[i+1][j] = 0;
					array[i+2][j] = 0;
					if (turncounter > 0)
					{
					score = score + 50;
					}
				}
			}
			
		}
	}
}
		
				
void replaceBlacks(int array[][8])				//pulls all 0 values to the first row and then replaces them with random gems
{

		for (int i = 0; i<8 ; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (array[i][j] == 0)
				{
					int trackrow = j;
					while(trackrow != 0)
					{
						swap(array[i][trackrow], array[i][trackrow-1]);
						trackrow--;
					}
					if (trackrow == 0)
					{
						array[i][0] = randomGem();
					}
				}
			}
		}
	
	
}


bool timer(int inputtime)			
{
		static int cleared = 2;
		static int i = inputtime * 3;
		int displayi = i / 3;
		//sleep(1);
		if (i%3 == 0)
		{
			
			string time = "TIME: ";
			string numtime = to_string(displayi);
			time = time + numtime;
			char displaytime[100] = {};
			strcpy(displaytime, time.c_str());
			//setcolor(BLACK);
			//rectangle(600,300,1000,1000);
			//setfillstyle(SOLID_FILL, BLACK);
			//floodfill(600,300,BLACK);
			settextstyle(BOLD_FONT, HORIZ_DIR, 5);
			setcolor(YELLOW);
			if(i < 300 && cleared == 2)
			{
				cleardevice();
				cleared--;
			}
			
			if (i < 30 && cleared == 1)
			{
				cleardevice();
				cleared--;
			}
			outtextxy(600,300,displaytime);
		}
		i--;
		if (i < 0)
		{
			return true;
		}
		return false;
}


void gameover(int totalscore)				//displays total score and a gameover screen
{
	
	readimagefile("gameover.jpg",100,100,900,500);
	string score = "YOUR SCORE WAS: ";						
	string numscore = to_string(totalscore);
	score = score + numscore;
	char displayscore[100];
	strcpy(displayscore, score.c_str());
	settextstyle(2, HORIZ_DIR, 8);
	setcolor(YELLOW);
	outtextxy(350,350,displayscore);
	
	
	sleep(5);
}

		
		
int main(){
	int inputtime;
	cout << "Enter time duration in seconds: ";
	cin >> inputtime;
	
	bool gameopen = 1;
	int totalscore = 0;
	int cursorx = 70 , cursory = 70;				//cursor starting value
	int totalarray[8][8];
	randomizeArray(totalarray);
	//printArray(totalarray);
	initwindow(1000, 650, "Jewel Rush");
	
	readimagefile("menumenu.jpg",0,0,1000,800);				//entering screen
	delay(4000);
	cleardevice();
	
	int turncounter = 0;
	bool gem1selected = 0;
	int gem1x = 0;
	int gem1y = 0;
	
	int gem2x = 0;
	int gem2y = 0;
	
	while(gameopen)
	{
		
		grid();
		

		setcolor(YELLOW);
		rectangle(cursorx, cursory, cursorx + 60, cursory + 60);
		if (gem1selected ==  1){										//if a gem is selected, turn that box to red to show what is selected
			setcolor(RED);
			rectangle(gem1x, gem1y, gem1x + 60, gem1y + 60);	
		}
		
		if (gem2x != 0)													//if a second gem is selected, turn that to lightred 
		{
			setcolor(LIGHTRED);
			rectangle(gem2x, gem2y, gem2x + 60, gem2y + 60);
		}
		
		
	
		//delay(50);
		displayArray(totalarray);

		
		if(GetAsyncKeyState(VK_RIGHT) && cursorx < 480 ){
			if (gem1selected == 1){
				if (cursorx < gem1x + 60)					//to make sure only adjacent gems can be selected as gem 2
		 			cursorx += 60;
		 	}
		 	else
		 		cursorx +=60;
		 	turncounter++;
		 	}
		if(GetAsyncKeyState(VK_LEFT) && cursorx > 70){
			if (gem1selected == 1){
				if(cursorx > gem1x - 60)
					cursorx -=60;
			}
		else
			cursorx -= 60;
		turncounter++;
		}
		if(GetAsyncKeyState(VK_DOWN) && cursory < 480){
			if(gem1selected == 1){
				if (cursory < gem1y + 60)
					cursory += 60;
			}
		else
			cursory +=60;
		turncounter++;
		}
		if(GetAsyncKeyState(VK_UP) && cursory > 70){
			if (gem1selected == 1){
				if (cursory > gem1y - 60)
					cursory -=60;
			}
		else
			cursory -=60;
		turncounter++;
		}
		if(GetAsyncKeyState(VK_RETURN))
		{
			if (gem1selected == 0)			//if gem 1 is selected
			{
				gem1x = cursorx;
				gem1y = cursory;
				gem1selected = 1;
			}
			else							//if gem 2 is selected
			{
				gem2x = cursorx;
				gem2y = cursory;
			}			
		}
		if(GetAsyncKeyState(VK_ESCAPE))			//game closes if escape is pressed
		{
			gameopen = 0;
		}
		
		if (gem1selected == 1 && gem2x != 0){			//if both gems selected

			mySwap(totalarray, gem1x, gem1y, gem2x, gem2y, totalscore);			//send coords of both gems along with the array for swapping
			gem1selected = 0;
			gem1x = 0;
			gem2x = 0;
			gem1y = 0;
			gem2y = 0;
				
			
		}
		
	checkElbow(totalarray, totalscore, turncounter);
		replaceBlacks(totalarray);
	vertical4Match(totalarray, totalscore, turncounter);
		replaceBlacks(totalarray);
	horizontal4Match(totalarray, totalscore, turncounter);
		replaceBlacks(totalarray);
	verticalMatch(totalarray, totalscore, turncounter);
		replaceBlacks(totalarray);
	horizontalMatch(totalarray, totalscore, turncounter);
		replaceBlacks(totalarray);
	horizontalFlameMatch(totalarray,totalscore,turncounter);
		replaceBlacks(totalarray);
	verticalFlameMatch(totalarray,totalscore,turncounter);
		replaceBlacks(totalarray);
	
	string score = "SCORE: ";						//displaying score
	string numscore = to_string(totalscore);
	score = score + numscore;
	char displayscore[100];
	strcpy(displayscore, score.c_str());
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(YELLOW);
	outtextxy(600,200,displayscore);
	
	bool timeout = timer(inputtime);
	
	if (timeout == 1)				//if time runs out, game over
	{
		gameopen = 0;
	}

	if (gameopen == 0)			
	{
		gameover(totalscore);
	}

}
	closegraph();
	
	return 0;
}