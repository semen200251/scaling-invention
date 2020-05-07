#include<GL/glut.h>
#include<stdio.h>

int num_button = 0;
int k = 0;
int count_keys = 1;
int status_botton = 0;
int status[15];
int d = 0;
int g = 0;
typedef struct
{
	float x;
	float y;
	char Name[20];
	float Color[3];
	float HihlightColor[3];
	int status;
	int count_key;
}PNT;
PNT button[40];
int readLine(char** str, FILE* stream)
{
	int c = 0;
	int i = 0;
	int size = 50;

	*str = malloc(size);
	if (!(*str))
		return -1;

	while ((c = getc(stream)) != EOF && c != 26)
	{
		if (i >= size - 1)
		{
			char* l = realloc(*str, size + 50);

			size += 50;

			if (!l)
				return -1;
			*str = l;
		}

		if (c == '\n')
		{
			(*str)[i] = 0;
			return 0;
		}

		(*str)[i] = (char)c;
		i++;
	}

	(*str)[i] = 0;

	if (i)
		return 2;

	return 1;
}
int window_processing(char* str, int* posotion_window_x, int* posotion_window_y)
{
	unsigned int len = strlen(str);
	const char window[] = "WindowPosition=(";
	int a = 16;
	if (strstr(str, window))
	{
		if (isdigit(str[a]))
		{
			*posotion_window_x = atoi(str + a);
			while (isdigit(str[a]))
			{
				a++;
			}

			*posotion_window_y = atoi(str + a + 1);
		}
	}
	return 0;
}

int button_start(char* str)
{
	unsigned int len = strlen(str);
	const char button_position[] = "ButtonPosition=(";
	const char button_color[] = "Color=";
	const char button_hihlightColor[] = "Hihlightcolor=";
	const char button_name[] = "Name=";
	int p = 6;
	int g = 0;
	int v = 5;
	int z = 0;
	int e = 14;
	int a = 16;
	int b = 0;
	int q = 0;
	if (strstr(str, button_position))
	{
		if (isdigit(str[a]))
		{
			button[num_button].x = (float)atof(str + a);
			while (isdigit(str[a]))
			{
				a++;
			}
			button[num_button].y = (float)atof(str + a + 1);
		}
	}
	if (strstr(str, button_color))
	{
		for (int i = 0;i < 3;i++)
		{
			button[num_button].Color[g] = (float)atof(str + p);
			p += 4;
			g++;
		}
		g = 0;
	}
	if (strstr(str, button_name))
	{
		for (unsigned int i = v;i < strlen(str);i++)
		{
			button[num_button].Name[z] = str[i];
			z++;
		}
	}
	if (strstr(str, button_hihlightColor))
	{
		for (int i = 0;i < 3;i++)
		{
			button[num_button].HihlightColor[g] = (float)atof(str + e);
			e += 4;
			g++;
		}
	}
	if (isdigit(str[0]))
	{
		if (k == 0)
		{
			button[num_button].status = atoi(str);
			k = 1;
		}
		else
		{
			button[num_button].count_key = atoi(str);
			k = 0;
			num_button++;
		}
	}
	return 0;
}

void renderBitmapString(float x, float y, int h)
{
	glColor3d(button[h].HihlightColor[0], button[h].HihlightColor[1], button[h].HihlightColor[2]);
	glRasterPos2f(x, y);
	for (int i = 0;button[h].Name[i] != '\0';i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, button[h].Name[i]);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0;i < num_button;i++)
	{
		if (status_botton == button[i].status)
		{
			glColor3f(button[i].Color[0], button[i].Color[1], button[i].Color[2]);
			glBegin(GL_POLYGON);
			glVertex2f(button[i].x - 150, button[i].y + 30);
			glVertex2f(button[i].x - 150, button[i].y - 30);
			glVertex2f(button[i].x + 150, button[i].y - 30);
			glVertex2f(button[i].x + 150, button[i].y + 30);
			glColor3d(button[i].HihlightColor[0], button[i].HihlightColor[1], button[i].HihlightColor[2]);
			glEnd();
		}
	}
	for (int i = 0;i < num_button;i++)
	{
		if (status_botton == button[i].status)
		{
			unsigned int len = strlen(button[i].Name);
			renderBitmapString(button[i].x - (float)(len*0.5*12), button[i].y-6, i);
		}
	}
	glutSwapBuffers();
}
void processSpecialKeys(int key, int xx, int yy)
{

	   int a;
	   int b;
	    for (int i = 0;i < num_button;i++)
		{
			if (button[i].status == status_botton)
			{
				a = button[i].count_key;
				if (g == 0)
				{
					count_keys = a;
				}
				break;
			}
		}
		for (int i = 0;i < num_button;i++)
		{
			if (button[i].status == status_botton)
			{
				b = button[i].count_key;
			}
		}
		switch (key)
		{
		case GLUT_KEY_UP:
			count_keys--;
			g = 1;
			if (count_keys < a)
				count_keys = a;
			break;
		case GLUT_KEY_DOWN:
			count_keys++;
			g = 1;
			if (count_keys > b)
				count_keys = b;
			break;
		case GLUT_KEY_RIGHT:
			status[d] = status_botton;
			g = 0;
			d++;
			status_botton = button[count_keys - 1].count_key;
			display();
			break;
		case GLUT_KEY_LEFT:
			g = 0;
			d--;
			status_botton = status[d];
			display();
			break;
        }
}
void processNormalKeys(unsigned char key, int x, int y) {
	int a;
	int b;
	for (int i = 0;i < num_button;i++)
	{
		if (button[i].status == status_botton)
		{
			a = button[i].count_key;
			if (g == 0)
			{
				count_keys = a;
			}
			break;
		}
	}
	for (int i = 0;i < num_button;i++)
	{
		if (button[i].status == status_botton)
		{
			b = button[i].count_key;
		}
	}
	if (key == 13)
	{
		int k = 0;
		for (int i = 0;i < num_button;i++)
		{
			if (button[i].status == button[count_keys - 1].count_key)
			{
				k = 1;
			}
		}
		if (k == 1)
		{
			status[d] = status_botton;
			g = 0;
			d++;
			status_botton = button[count_keys - 1].count_key;
			display();
		}
	}
	if (key == 27)
	{
		g = 0;
		d--;
		status_botton = status[d];
		display();
	}
}





int main(int argc, char** argv)
{
	int posotion_window_x = 0;
	int posotion_window_y = 0;
	FILE* stream = stdin;
	fopen_s(&stream, "menu.txt", "r");
	char* str = NULL;
	int var = 0;
	while (!var)
	{
		var = readLine(&str, stream);
		if (var == 1)
		{
			free(str);
			break;
		}
		window_processing(str, &posotion_window_x, &posotion_window_y);
		button_start(str);
		free(str);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(480, 480);
	glutInitWindowPosition(posotion_window_x, posotion_window_y);
	glViewport(0, 0, 480, 480);
	glutCreateWindow("Menu");
	gluOrtho2D(0, 480, 0, 480);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*glutReshapeFunc(reshape);*/
	glutMainLoop();
	return 1;
}
