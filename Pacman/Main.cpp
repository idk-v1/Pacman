#include "Window.h"

int main()
{
	int scale = 8 * 2;
	Window window(28 * scale, (31 + 2 + 3) * scale);
	window.start();
}