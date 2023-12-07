#include "data.h"

#define xAxis 0
#define yAxis 1
#define zAxis 2

#define name "picoboy"

class Demo {
	private:
    U8G2 u8g2;
	byte nameposY;
	public:
    Demo (U8G2 &u8g2P)
    {
		u8g2 = u8g2P;
	}
	
	void stars()
	{
		unsigned long int lastChange = millis();
		const byte numstars = 250;
		const int duration = 7000;
		
		u8g2.clearBuffer();
		u8g2.drawStr(128, nameposY, name);
		u8g2.sendBuffer();
		delay(500);
		
		float stars[numstars][4];
		
		for (int i = 0; i < numstars; i++)
		{
			stars[i][0] = 56;
			stars[i][1] = 32;
			float angle = (random(3600) / 1800.0) * PI;
			float speed = random(100) + 100;
			stars[i][2] = speed * sin(angle);
			stars[i][3] = speed * cos(angle);
		}
		
		u8g2.clearBuffer();
		
		while ((lastChange + duration > millis()))
		{
			u8g2.clearBuffer();
			u8g2.drawStr(128, nameposY, name);
			
			for (int i = 0; i < numstars; i++)
			{
				
				u8g2.drawPixel(stars[i][0], stars[i][1]);
				stars[i][0] += stars[i][2] / 1000;
				stars[i][1] += stars[i][3] / 1000;
				
				stars[i][2] *= 1.1;
				stars[i][3] *= 1.1;
				
				if (stars[i][0] < 0 || stars[i][0] > 128 || stars[i][1] < 0 || stars[i][1] > 64)
				{
					stars[i][0] = 56;
					stars[i][1] = 32;
					float angle = (random(3600) / 1800.0) * PI;
					float speed;
					if (lastChange + (duration - 1200) > millis())
					{
						stars[i][0] = 56;
						stars[i][1] = 32;
						speed = random(100) + 100;
					}
					else
					{
						speed = 0;
						stars[i][0] = 56;
						stars[i][1] = 32;
					}
					stars[i][2] = speed * sin(angle);
					stars[i][3] = speed * cos(angle);
				}
			}
			u8g2.sendBuffer();
		}
	}
	
	void starsSwirl()
	{
		unsigned long int lastChange = millis();
		const byte numstars = 200;
		const int duration = 7000;
		
		float stars[numstars][4];
		float a, b;
		float temp;
		float rotspeed;
		
		for (int i = 0; i < numstars; i++)
		{
			stars[i][0] = 56;
			stars[i][1] = 32;
			float angle = (random(3600) / 1800.0) * PI;
			float speed = random(150) + 150;
			stars[i][2] = speed * sin(angle);
			stars[i][3] = speed * cos(angle);
		}
		
		u8g2.clearBuffer();
		
		while ((lastChange + duration > millis()))
		{
			u8g2.clearBuffer();
			
			u8g2.drawStr(128, nameposY, name);
			rotspeed = 25 + (1.0 * (duration - (millis() - lastChange)) / duration) * 50;
			
			float cosq = cos(PI / rotspeed);
			float sinq = sin(PI / rotspeed);
			for (int i = 0; i < numstars; i++)
			{
				a = stars[i][0] - 56;
				b = stars[i][1] - 32;
				temp = b * cosq - a * sinq;
				a = b * sinq + a * cosq;
				b = temp;
				stars[i][0] = a + 56;
				stars[i][1] = b + 32;
				
				a = stars[i][2];
				b = stars[i][3];
				temp = b * cosq - a * sinq;
				a = b * sinq + a * cosq;
				b = temp;
				stars[i][2] = a;
				stars[i][3] = b;
				
				u8g2.drawPixel(stars[i][0], stars[i][1]);
				stars[i][0] += stars[i][2] / 1000;
				stars[i][1] += stars[i][3] / 1000;
				
				stars[i][2] *= 1.1;
				stars[i][3] *= 1.1;
				
				if (stars[i][0] < 0 || stars[i][0] > 128 || stars[i][1] < 0 || stars[i][1] > 64)
				{
					stars[i][0] = 56;
					stars[i][1] = 32;
					float angle = (random(3600) / 1800.0) * PI;
					float speed;
					if (lastChange + (duration - 1500) > millis())
					{
						stars[i][0] = 56;
						stars[i][1] = 32;
						speed = random(100) + 100;
					}
					else
					{
						speed = 0;
						stars[i][0] = 56;
						stars[i][1] = 32;
					}
					stars[i][2] = speed * sin(angle);
					stars[i][3] = speed * cos(angle);
				}
			}
			u8g2.sendBuffer();
		}
	}
	
	void rotate(float array[][3], int len, float q, byte axis, int xOff, int yOff, int zOff)
	{
		float a, b, temp;
		float cosq = cos(q);
		float sinq = sin(q);
		
		if (axis == xAxis)
		{
			for (int i = 0; i < len; i++)
			{
				a = array[i][1] - yOff;
				b = array[i][2] - zOff;
				temp = a * cosq - b * sinq;
				b = a * sinq + b * cosq;
				a = temp;
				array[i][1] = a + yOff;
				array[i][2] = b + zOff;
			}
		}
		else if (axis == yAxis)
		{
			for (int i = 0; i < len; i++)
			{
				a = array[i][0] - xOff;
				b = array[i][2] - zOff;
				temp = a * cosq - b * sinq;
				b = a * sinq + b * cosq;
				a = temp;
				array[i][0] = a + xOff;
				array[i][2] = b + zOff;
			}
		}
		else if (axis == zAxis)
		{
			for (int i = 0; i < len; i++)
			{
				a = array[i][0] - xOff;
				b = array[i][1] - yOff;
				temp = a * cosq - b * sinq;
				b = a * sinq + b * cosq;
				a = temp;
				array[i][0] = a + xOff;
				array[i][1] = b + yOff;
			}
		}
	}
	
	void sphere()
	{
		unsigned long int lastChange = millis();
		const bool dotted = false;
		const byte circles = 7;
		const byte edges = 22;
		const int duration = 10000;
		const int numpixels = circles * edges + 2;
		const float zOff = 150;
		const float xOff = 0;
		const float yOff = 0;
		const float radius = 67;
		float view_plane = 4;
		float object3d[numpixels][3];
		
		unsigned char object2d[numpixels][2];
		int count = 0;
		
		object3d[count][0] = xOff;
		object3d[count][1] = yOff;
		object3d[count][2] = zOff + radius;
		count++;
		
		for (byte j = 1; j < circles + 1; j++)
		{
			for (byte i = 0; i < edges; i++)
			{
				float phi = (i * PI) / (edges / 2.0);
				float theta = (2 * j * PI) / (2 * (circles + 1));
				object3d[count][0] = xOff + radius * sin(theta) * cos(phi);
				object3d[count][1] = yOff + radius * sin(theta) * sin(phi);
				object3d[count][2] = zOff + radius * cos(theta);
				count++;
			}
		}
		
		object3d[count][0] = xOff;
		object3d[count][1] = yOff;
		object3d[count][2] = zOff - radius;
		
		while ((lastChange + duration > millis() || object2d[0][0] != 56))
		{
			rotate(object3d, numpixels, PI / -60, yAxis, xOff, yOff, zOff);
			rotate(object3d, numpixels, PI / 90, xAxis, xOff, yOff, zOff);
			
			if (view_plane < 58)
			{
				view_plane *= 1.3;
			}
			if (view_plane >= 58)
			{
				view_plane = 58;
			}
			
			for (int i = 0; i < numpixels; i++)
			{
				object2d[i][0] = (unsigned char)((object3d[i][0] * view_plane / object3d[i][2]) + 56);
				object2d[i][1] = (unsigned char)((object3d[i][1] * view_plane / object3d[i][2]) + 32);
			}
			
			u8g2.clearBuffer();
			
			int j = numpixels;
			
			if (millis() > ((lastChange + duration) - j * 40))
			{
				j -= (millis() - ((lastChange + duration) - j * 40)) / 40;
			}
			
			if (dotted)
			{
				
				for (int i = 0; i < j; i++)
				{
					u8g2.drawPixel(object2d[i][0], object2d[i][1]);
				}
			}
			else
			{
				for (int i = 2; i < j; i++)
				{
					if (!((i - 1) % edges == 0))
					{
						u8g2.drawLine(object2d[i][0], object2d[i][1], object2d[i - 1][0], object2d[i - 1][1]);
					}
					else
					{
						if ((i + (edges - 1)) < numpixels)
						{
							u8g2.drawLine(object2d[i][0], object2d[i][1], object2d[i + (edges - 1)][0], object2d[i + (edges - 1)][1]);
						}
					}
				}
				if (j > 1)
				{
					u8g2.drawLine(object2d[1][0], object2d[1][1], object2d[edges][0], object2d[edges][1]);
				}
			}
			u8g2.drawPixel(object2d[0][0], object2d[0][1]);
			if (j == numpixels)
			{
				u8g2.drawPixel(object2d[j - 1][0], object2d[j - 1][1]);
			}
			u8g2.drawStr(128, nameposY, name);
			u8g2.sendBuffer();
		}
	}
	
	void sphereForever()
	{
		const byte circles = 7;
		const byte edges = 22;
		
		const int numpixels = circles * edges + 2;
		const float zOff = 150;
		const float xOff = 0;
		const float yOff = 0;
		const float radius = 48;
		float view_plane = 64;
		float object3d[numpixels][3];
		
		unsigned char object2d[numpixels][2];
		int count = 0;
		
		object3d[count][0] = xOff;
		object3d[count][1] = yOff;
		object3d[count][2] = zOff + radius;
		count++;
		
		for (byte j = 1; j < circles + 1; j++)
		{
			for (byte i = 0; i < edges; i++)
			{
				float phi = (i * PI) / (edges / 2.0);
				float theta = (2 * j * PI) / (2 * (circles + 1));
				object3d[count][0] = xOff + radius * sin(theta) * cos(phi);
				object3d[count][1] = yOff + radius * sin(theta) * sin(phi);
				object3d[count][2] = zOff + radius * cos(theta);
				count++;
			}
		}
		
		object3d[count][0] = xOff;
		object3d[count][1] = yOff;
		object3d[count][2] = zOff - radius;
	}
	
	void draw_cube(unsigned char cube2d[][2])
	{
		u8g2.drawLine(cube2d[0][0], cube2d[0][1], cube2d[1][0], cube2d[1][1]);
		u8g2.drawLine(cube2d[0][0], cube2d[0][1], cube2d[2][0], cube2d[2][1]);
		u8g2.drawLine(cube2d[0][0], cube2d[0][1], cube2d[4][0], cube2d[4][1]);
		u8g2.drawLine(cube2d[1][0], cube2d[1][1], cube2d[5][0], cube2d[5][1]);
		u8g2.drawLine(cube2d[1][0], cube2d[1][1], cube2d[3][0], cube2d[3][1]);
		u8g2.drawLine(cube2d[2][0], cube2d[2][1], cube2d[6][0], cube2d[6][1]);
		u8g2.drawLine(cube2d[2][0], cube2d[2][1], cube2d[3][0], cube2d[3][1]);
		u8g2.drawLine(cube2d[4][0], cube2d[4][1], cube2d[6][0], cube2d[6][1]);
		u8g2.drawLine(cube2d[4][0], cube2d[4][1], cube2d[5][0], cube2d[5][1]);
		u8g2.drawLine(cube2d[7][0], cube2d[7][1], cube2d[6][0], cube2d[6][1]);
		u8g2.drawLine(cube2d[7][0], cube2d[7][1], cube2d[3][0], cube2d[3][1]);
		u8g2.drawLine(cube2d[7][0], cube2d[7][1], cube2d[5][0], cube2d[5][1]);
	}
	
	void printcube(float cube3d[][3], unsigned char cube2d[][2], float &view_plane, bool shrink, bool grow)
	{
		if (grow == true)
		{
			if (view_plane < 58)
			{
				view_plane *= 1.05;
			}
			if (view_plane >= 58)
			{
				view_plane = 58;
			}
		}
		else if (shrink == true)
		{
			view_plane /= 1.05;
		}
		
		for (byte i = 0; i < 8; i++)
		{
			cube2d[i][0] = (unsigned char)((cube3d[i][0] * view_plane / cube3d[i][2]) + 56);
			cube2d[i][1] = (unsigned char)((cube3d[i][1] * view_plane / cube3d[i][2]) + 32);
		}
		
		u8g2.clearBuffer();
		draw_cube(cube2d);
		u8g2.drawStr(128, nameposY, name);
		u8g2.sendBuffer();
	}
	
	void cube()
	{
		unsigned long int lastChange = millis();
		const unsigned int duration = 10000;
		const float zOff = 150;
		const float xOff = 0;
		const float yOff = 0;
		const float size = 40;
		float view_plane = 64;
		
		float cube3d[8][3] = {
			{xOff - size, yOff + size, zOff - size},
			{xOff + size, yOff + size, zOff - size},
			{xOff - size, yOff - size, zOff - size},
			{xOff + size, yOff - size, zOff - size},
			{xOff - size, yOff + size, zOff + size},
			{xOff + size, yOff + size, zOff + size},
			{xOff - size, yOff - size, zOff + size},
		{xOff + size, yOff - size, zOff + size}};
		
		unsigned char cube2d[8][2];
		
		u8g2.clearBuffer();
		u8g2.drawStr(128, nameposY, name);
		u8g2.drawPixel(56, 32);
		u8g2.sendBuffer();
		delay(100);
		view_plane = 4;
		rotate(cube3d, 8, 2 * PI / 8, 1, xOff, yOff, zOff);
		while ((lastChange + duration > millis()))
		{
			rotate(cube3d, 8, 2 * PI / -240, yAxis, xOff, yOff, zOff);
			rotate(cube3d, 8, 2 * PI / 200, xAxis, xOff, yOff, zOff);
			rotate(cube3d, 8, 2 * PI / 180, zAxis, xOff, yOff, zOff);
			if (millis() < lastChange + 5000)
			{
				printcube(cube3d, cube2d, view_plane, false, true);
			}
			else if (millis() > lastChange + duration - 950)
			{
				printcube(cube3d, cube2d, view_plane, true, false);
			}
			else
			{
				printcube(cube3d, cube2d, view_plane, false, false);
			}
		}
		u8g2.clearBuffer();
		u8g2.drawStr(128, nameposY, name);
		u8g2.drawPixel(56, 32);
		u8g2.sendBuffer();
		delay(200);
	}
	
	void drawText()
	{
		int width = sizeof logo / sizeof logo[0];
		char segment;
		for (int h = -112; (h < width + 1); h += 3)
		{
			u8g2.clearBuffer();
			if (-56 - (h) > 0)
			{
				u8g2.drawPixel(-56 - (h), 32);
			}
			for (int i = h; i < h + 112; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (i >= 0 && i < width)
					{
						segment = logo[i][j];
						if (segment & 1)
						{
							u8g2.drawPixel(i - h, 0 + 12 + j * 8);
						}
						if (segment & 2)
						{
							u8g2.drawPixel(i - h, 1 + 12 + j * 8);
						}
						if (segment & 4)
						{
							u8g2.drawPixel(i - h, 2 + 12 + j * 8);
						}
						if (segment & 8)
						{
							u8g2.drawPixel(i - h, 3 + 12 + j * 8);
						}
						if (segment & 16)
						{
							u8g2.drawPixel(i - h, 4 + 12 + j * 8);
						}
						if (segment & 32)
						{
							u8g2.drawPixel(i - h, 5 + 12 + j * 8);
						}
						if (segment & 64)
						{
							u8g2.drawPixel(i - h, 6 + 12 + j * 8);
						}
						if (segment & 128)
						{
							u8g2.drawPixel(i - h, 7 + 12 + j * 8);
						}
					}
					else
					{
						delayMicroseconds(20);
					}
				}
			}
			u8g2.drawStr(128, nameposY, name);
			u8g2.sendBuffer();
			delay(5);
		}
	}
	
	void danceMacarena()
	{
		int width = sizeof dance / sizeof dance[0];
		char segment;
		for (int h = 0; (h < width); h += 30)
		{
			u8g2.clearBuffer();
			for (int i = h; i < h + 30; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (i >= 0 && i < width)
					{
						segment = dance[i][j];
						if (segment & 1)
						{
							u8g2.drawPixel(41 + i - h, 0 + 6 + j * 8);
						}
						if (segment & 2)
						{
							u8g2.drawPixel(41 + i - h, 1 + 6 + j * 8);
						}
						if (segment & 4)
						{
							u8g2.drawPixel(41 + i - h, 2 + 6 + j * 8);
						}
						if (segment & 8)
						{
							u8g2.drawPixel(41 + i - h, 3 + 6 + j * 8);
						}
						if (segment & 16)
						{
							u8g2.drawPixel(41 + i - h, 4 + 6 + j * 8);
						}
						if (segment & 32)
						{
							u8g2.drawPixel(41 + i - h, 5 + 6 + j * 8);
						}
						if (segment & 64)
						{
							u8g2.drawPixel(41 + i - h, 6 + 6 + j * 8);
						}
						if (segment & 128)
						{
							u8g2.drawPixel(41 + i - h, 7 + 6 + j * 8);
						}
					}
					else
					{
						delayMicroseconds(20);
					}
				}
			}
			u8g2.drawStr(128, nameposY, name);
			u8g2.sendBuffer();
			delay(60);
		}
	}
	
	void doubleFlash(bool macarenaMan)
	{
		char segment;
		int width = sizeof dance / sizeof dance[0];
		u8g2.setContrast(255);
		u8g2.clearBuffer();
		u8g2.drawBox(0, 0, 128, 64);
		u8g2.sendBuffer();
		digitalWrite(LEDR, HIGH);
		digitalWrite(LEDG, HIGH);
		digitalWrite(LEDY, HIGH);
		delay(30);
		
		u8g2.clearBuffer();
		if (macarenaMan)
		{
			for (int i = 0; i < 31; i++)
			{
				
				for (int j = 0; j < 6; j++)
				{
					if (i >= 0 && i < width)
					{
						segment = dance[i + 2099][j];
						if (segment & 1)
						{
							u8g2.drawPixel(41 + i, 0 + 6 + j * 8);
						}
						if (segment & 2)
						{
							u8g2.drawPixel(41 + i, 1 + 6 + j * 8);
						}
						if (segment & 4)
						{
							u8g2.drawPixel(41 + i, 2 + 6 + j * 8);
						}
						if (segment & 8)
						{
							u8g2.drawPixel(41 + i, 3 + 6 + j * 8);
						}
						if (segment & 16)
						{
							u8g2.drawPixel(41 + i, 4 + 6 + j * 8);
						}
						if (segment & 32)
						{
							u8g2.drawPixel(41 + i, 5 + 6 + j * 8);
						}
						if (segment & 64)
						{
							u8g2.drawPixel(41 + i, 6 + 6 + j * 8);
						}
						if (segment & 128)
						{
							u8g2.drawPixel(41 + i, 7 + 6 + j * 8);
						}
					}
				}
			}
		}
		
		u8g2.drawStr(128, nameposY, name);
		digitalWrite(LEDR, LOW);
		digitalWrite(LEDG, LOW);
		digitalWrite(LEDY, LOW);
		u8g2.sendBuffer();
		delay(100);
		if (!macarenaMan)
		{
			delay(100);
		}
		
		u8g2.clearBuffer();
		u8g2.drawBox(0, 0, 128, 64);
		u8g2.setContrast(31);
		u8g2.sendBuffer();
		digitalWrite(LEDR, HIGH);
		digitalWrite(LEDG, HIGH);
		digitalWrite(LEDY, HIGH);
		delay(30);
		digitalWrite(LEDR, LOW);
		digitalWrite(LEDG, LOW);
		digitalWrite(LEDY, LOW);
	}
	
	
	void drawDmc(void)
	{
		unsigned long int lastChange = millis();
		const int duration = 10000;
		const float zOff = 150;
		const float xOff = 0;
		const float yOff = 0;
		float view_plane = 56;
		const int numpixels = sizeof c_dmc / sizeof c_dmc[0];
		float dmc[numpixels][3];
		unsigned char object2d[numpixels][2];
		
		for (int i = 0; i < numpixels; i++)
		{
			dmc[i][0] = c_dmc[i][0] / 2;
			dmc[i][1] = c_dmc[i][1] / 2;
			dmc[i][2] = zOff;
		}
		
		int angle = 0;
		int rotangle = 3;
		
		rotate(dmc, numpixels, PI / 10, xAxis, xOff, yOff, zOff);
		
		while ((lastChange + duration > millis()))
		{
			angle = (angle + rotangle) % 360;
			rotate(dmc, numpixels, rotangle * (PI / 180), yAxis, xOff, yOff, zOff);
			rotate(dmc, numpixels, 1.5 * sin(angle * (PI / 180)) * PI / 100, zAxis, xOff, yOff, zOff);
			
			for (int i = 0; i < numpixels; i++)
			{
				object2d[i][0] = (unsigned char)((4 * dmc[i][0] * view_plane / dmc[i][2]) + 56);
				object2d[i][1] = (unsigned char)((4 * dmc[i][1] * view_plane / dmc[i][2]) + 32);
			}
			
			u8g2.clearBuffer();
			for (int i = 0; i < numpixels; i++)
			{
				u8g2.drawPixel(object2d[i][0], object2d[i][1]);
			}
			
			u8g2.drawStr(128, nameposY, name);
			u8g2.sendBuffer();
		}
	}
	
	int zbuffer[sizeof c_model / sizeof c_model[0]];
	
	void rotatemodel(float array[][3][3], int len, float q, byte axis, int xOff, int yOff, int zOff)
	{
		float a, b, temp;
		float cosq = cos(q);
		float sinq = sin(q);
		
		for (int j = 0; j < 3; j++)
		{
			if (axis == xAxis)
			{
				for (int i = 0; i < len; i++)
				{
					a = array[i][j][1] - yOff;
					b = array[i][j][2] - zOff;
					temp = a * cosq - b * sinq;
					b = a * sinq + b * cosq;
					a = temp;
					array[i][j][1] = a + yOff;
					array[i][j][2] = b + zOff;
				}
			}
			else if (axis == yAxis)
			{
				for (int i = 0; i < len; i++)
				{
					a = array[i][j][0] - xOff;
					b = array[i][j][2] - zOff;
					temp = a * cosq - b * sinq;
					b = a * sinq + b * cosq;
					a = temp;
					array[i][j][0] = a + xOff;
					array[i][j][2] = b + zOff;
				}
			}
			else if (axis == zAxis)
			{
				for (int i = 0; i < len; i++)
				{
					a = array[i][j][0] - xOff;
					b = array[i][j][1] - yOff;
					temp = a * cosq - b * sinq;
					b = a * sinq + b * cosq;
					a = temp;
					array[i][j][0] = a + xOff;
					array[i][j][1] = b + yOff;
				}
			}
		}
	}
	
	void drawmodel(unsigned char model2d[][3][2], int triangles)
	{
		for (int i = 0; i < triangles; i++)
		{
			int max = 0;
			int maxindex = -1;
			
			for (int k = 0; k < triangles; k++)
			{
				if (zbuffer[k] >= max)
				{
					max = zbuffer[k];
					maxindex = k;
				}
			}
			zbuffer[maxindex] = 0;
			
			u8g2.setDrawColor(0);
			u8g2.drawTriangle(model2d[maxindex][0][0], model2d[maxindex][0][1], model2d[maxindex][1][0], model2d[maxindex][1][1], model2d[maxindex][2][0], model2d[maxindex][2][1]);
			u8g2.setDrawColor(1);
			// 0-1
			u8g2.drawLine(model2d[maxindex][0][0], model2d[maxindex][0][1], model2d[maxindex][1][0], model2d[maxindex][1][1]);
			// 1-2
			u8g2.drawLine(model2d[maxindex][1][0], model2d[maxindex][1][1], model2d[maxindex][2][0], model2d[maxindex][2][1]);
			// 2-0
			u8g2.drawLine(model2d[maxindex][2][0], model2d[maxindex][2][1], model2d[maxindex][0][0], model2d[maxindex][0][1]);
		}
	}
	
	void printmodel(float model[][3][3], unsigned char model2d[][3][2], float view_plane, int triangles)
	{
		for (int i = 0; i < triangles; i++)
		{
			for (byte j = 0; j < 3; j++)
			{
				model2d[i][j][0] = (unsigned char)((model[i][j][0] * view_plane / model[i][j][2]) + 56);
				model2d[i][j][1] = (unsigned char)((model[i][j][1] * view_plane / model[i][j][2]) + 32);
			}
			zbuffer[i] = model[i][0][2] + model[i][1][2] + model[i][2][2];
		}
		
		u8g2.clearBuffer();
		drawmodel(model2d, triangles);
		u8g2.drawStr(128, nameposY, name);
		u8g2.sendBuffer();
	}
	
	void eff_model()
	{
		unsigned long int lastChange = millis();
		const unsigned int duration = 10000;
		const float zOff = 250;
		const float xOff = 0;
		const float yOff = -0;
		float view_plane = 50;
		int triangles = sizeof c_model / sizeof c_model[0];
		float model[triangles][3][3];
		unsigned char model2d[triangles][3][2];
		
		for (int i = 0; i < triangles; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				model[i][j][0] = c_model[i][j][0] + xOff;
				model[i][j][1] = c_model[i][j][1] + yOff;
				model[i][j][2] = c_model[i][j][2] + zOff;
			}
		}
		
		rotatemodel(model, triangles, 2 * PI / 3.5, xAxis, xOff, yOff, zOff);
		int angle = 0;
		int rotangle = -5;
		
		while ((lastChange + duration > millis()))
		{
			angle = (angle + rotangle) % 360;
			rotatemodel(model, triangles, rotangle * (PI / 180), yAxis, xOff, yOff, zOff);
			rotatemodel(model, triangles, 1.5 * sin(angle * (PI / 180)) * PI / 100, zAxis, xOff, yOff, zOff);
			printmodel(model, model2d, view_plane, triangles);
		}
	}
	
	void standard()
	{
		u8g2.setFont(u8g2_font_pieceofcake_mel_tr);
		nameposY = 31 + (u8g2.getStrWidth(name) / 2);
		u8g2.setFontDirection(3);
	}
	
	
	
	void run(void)
	{
		set_sys_clock_khz(48000, true);
		u8g2.setDisplayRotation(U8G2_R0);	
		u8g2.setContrast(32);
		u8g2.setFontDirection(3);
		u8g2.setFont(u8g2_font_pieceofcake_mel_tr);
		
		nameposY = 31 + (u8g2.getStrWidth(name) / 2);
		while(true){
			run2();
			}
	}
	
	void run2(void)
	{
		
		stars();
		
		sphere();
		
		starsSwirl();
		
		cube();
		
		drawText();
		
		doubleFlash(false);
		
		drawDmc();
		
		doubleFlash(true);
		
		danceMacarena();
		
		doubleFlash(false);
		
		eff_model();
		
		doubleFlash(false);
	}
	};	