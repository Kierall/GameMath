#include "MainMenu.h"
#include "sfwdraw.h"

void menu::mUpdate()
{
	
}

void menu::mDraw()
{
	sfw::drawTexture(mainPic, 400, 300, 800, 600);

	
	//sfw::drawTexture(mainPic, 400, 300, 800, 600);
}

void start::update()
{
	if (sfw::getKey('S'))
	{
		enable = false;
	}
	
}

int start::quit()
{
	if (sfw::getKey('Q'))
	{
		exit = true;
		
	}
	while (exit == true)
	{
		return -1;
	}
}

void start::draw()
{
	sfw::drawString(font, "[C]ontrols", 50, 210, 30, 30, 0, '\000', GREEN);
	sfw::drawString(font, "[S]tart", 100, 90, 30, 30,0,'\000',GREEN);
	sfw::drawString(font, "[Esc] to exit", 10, 150, 30, 30, 0, '\000', GREEN);
}

void death::draw()
{
	sfw::drawTexture(GameOver, 400, 300, 800, 600);
}



void controls::update()
{
	if (sfw::getKey('C'))
	{
		enable = true;
	}
	if (sfw::getKey('B'))
	{
		enable = false;
	}
}

void controls::draw()
{
	
	sfw::drawTexture(Controls, 400, 300, 800, 600);
}
