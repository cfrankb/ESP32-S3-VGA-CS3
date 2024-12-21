# Hardware

## ESP32-S3

https://vi.aliexpress.com/item/1005006418608267.html

## Dupont cables

https://www.aliexpress.com/item/1005004611997111.html


## VGA Adaptor


https://vi.aliexpress.com/item/1005005279582020.html

![Image](images/20241221_100637-crop.jpg "icon")


Create a resistor ladder
Colors are stored as 16bits (B5G6R5)


| GPIO Pin | Role  | Resistor | VGA Pin |
| -------- | ----- | -------- | ------- |
| 1        | hsync | 47R      | 13      |
| 2        | vsync | 47R      | 14      |
| 4        | red   | 8k       | 1       |
| 5        | red   | 4k       |
| 6        | red   | 2k       |
| 7        | red   | 1k       |
| 8        | red   | 512R     |
| 9        | green | 16k      | 2       |
| 10       | green | 8k       |
| 11       | green | 4k       |
| 12       | green | 2k       |
| 13       | green | 1k       |
| 14       | green | 512R     |
| 15       | blue  | 8k       | 3       |
| 16       | blue  | 4k       |
| 17       | blue  | 2k       |
| 18       | blue  | 1k       |
| 21       | blue  | 512R     |
| GND      | -     | -        | 5, 10   |







## Joystick

https://www.aliexpress.com/item/32345829014.html

| JOYSTICK | wirecolor | GPIO Pin |
| -------- | --------- | -------- |
| VRX      | brown     | 35       |
| VRY      | white     | 34       |
| SW       | blue      | 26       |
| GRN      | black     | GRN      |
| VCC      | red       | 3.3v     |

The above configuration is for the ESP32S3.
Pin out will vary per model. Check log output.

