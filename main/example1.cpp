// пример добавлен исключительно в ознакомительных целях
// the example was added for informational purposes only

#include "VGA.h"
#include <esp_log.h>
#include <FONT_9x16.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

static const char *TAG = "example1";

VGA vga;

int scale = 2;

void delay(int ms)
{
	int _ms = ms + (portTICK_PERIOD_MS - 1);
	auto xTicksToDelay = _ms / portTICK_PERIOD_MS;
	vTaskDelay(xTicksToDelay);
}

static void delay(void)
{
	for (int i = 0; i < 1000; i++)
	{
		__asm__ __volatile__("nop");
	}
}

extern "C" void app_main(void)
{
	const PinConfig pins(-1, -1, 6, 7, 8, -1, -1, -1, 12, 13, 14, -1, -1, -1, 18, 21, 1, 2); // R G B h v

	//	Mode mode = Mode::MODE_640x480x60;
	Mode mode = Mode::MODE_320x240x60;

	// if (!vga.init(pins, mode, 16, 3))
	if (!vga.init(pins, mode, 16, 4))
		while (1)
			delay(1);

	if (!vga.start())
	{
		ESP_LOGE(TAG, "vga start failed");
	}

	// for (int y = 0; y < 480; y++)
	//	for (int x = 0; x < 640; x++)
	//		vga.dotdit(x, y, x, y, 255 - x);

	vga.setFont(FONT_9x16);
	// vga.start();

	// delay(5000);

	while (1)
	{
		auto rgb = rand();
		ESP_LOGI(TAG, "vga clear: %.4x", rgb & 0xfff);
		vga.clear(rgb);
		delay(1000);
		// for (int count = 0; count < 1000; count++)
		//	vga.dot(rand() % 640, rand() % 480, rand() % 255);
		//	delay(1000);
		continue;

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 10000; count++)
			vga.line(rand() % 640, rand() % 480, rand() % 640, rand() % 480, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 10000; count++)
			vga.tri(rand() % 640, rand() % 480, rand() % 640, rand() % 480, rand() % 640, rand() % 480, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 1000; count++)
		{
			//			vga.fillTri(rand() % 640, rand() % 480, rand() % 640, rand() % 480, rand() % 640, rand() % 480, rand() % 255);
			//			if ((count & 0xfff) == 0)
			//				vTaskDelay(1);
		}
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 10000; count++)
			vga.rect(rand() % 640, rand() % 480, rand() % 640, rand() % 480, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 100; count++)
			vga.fillRect(rand() % 640, rand() % 480, rand() % 640, rand() % 480, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 1000; count++)
			vga.circle(rand() % 640, rand() % 480, rand() % 100, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 500; count++)
			vga.fillCircle(rand() % 640, rand() % 480, rand() % 50, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 10000; count++)
			vga.ellipse(rand() % 640, rand() % 480, rand() % 100, rand() % 100, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 100; count++)
			vga.fillEllipse(rand() % 640, rand() % 480, rand() % 100, rand() % 100, rand() % 255);
		vga.clear(0);
		delay(1000);

		vga.clear(0);
		delay(1000);
		for (int count = 0; count < 100000; count++)
			vga.mouse(rand() % 640, rand() % 480);
		vga.clear(0);
		delay(1000);

		for (int count = 0; count < 1000; count++)
		{
			static int c = 0;
			static int d = 1;
			c += d;
			if (c == 0 || c == 255)
				d = -d;

			char text[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						   0, 0, 0, 0, 0, 0};

			for (int i = 0; i < 256; i++)
				text[i] = 33 + (i + (c >> 2));
			vga.setCursor(8, 48);
			vga.setTextColor(vga.rgb(c, 255 - c, 255), vga.rgb(0, c / 2, 127 - c / 2));
			vga.print(text);
			vga.setCursor(8, 148);
			vga.print(text);
			vga.setCursor(8, 248);
			vga.print(text);
			vga.setCursor(8, 348);
			vga.print(text);
		}
		delay(4000);
	}
}