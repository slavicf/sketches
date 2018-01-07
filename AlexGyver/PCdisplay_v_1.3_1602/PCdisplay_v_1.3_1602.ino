/*
  Модифицировано под дисплей 1602 klykov.net vk.com/ms262 instagram.com/klykovnet

  Блок электроники для крутого моддинга вашего ПК, возможности:
  - Вывод основных параметров железа на внешний LCD дисплей
  - Температура: CPU, GPU, материнская плата, самый горячий HDD
  - Уровень загрузки: CPU, GPU, RAM, видеопамять
  - Графики изменения вышеперечисленных параметров по времени
  - Температура с внешних датчиков (DS18B20)
  - Текущий уровень скорости внешних вентиляторов
  - Управление большим количеством 12 вольтовых 2, 3, 4 проводных вентиляторов
  - Автоматическое управление скоростью пропорционально температуре
  - Ручное управление скоростью из интерфейса программы
  - Управление RGB светодиодной лентой
  - Управление цветом пропорционально температуре (синий - зелёный - жёлтый - красный)
  - Ручное управление цветом из интерфейса программы

  Программа HardwareMonitorPlus  https://github.com/AlexGyver/PCdisplay
  - Запустить OpenHardwareMonitor.exe
  - Options/Serial/Run - запуск соединения с Ардуиной
  - Options/Serial/Config - настройка параметров работы
    - PORT address - адрес порта, куда подключена Ардуина
    - TEMP source - источник показаний температуры (процессор, видеокарта, максимум проц+видео, датчик 1, датчик 2)
    - FAN min, FAN max - минимальные и максимальные обороты вентиляторов, в %
    - TEMP min, TEMP max - минимальная и максимальная температура, в градусах Цельсия
    - Manual FAN - ручное управление скоростью вентилятора в %
    - Manual COLOR - ручное управление цветом ленты
    - LED brightness - управление яркостью ленты
    - CHART interval - интервал обновления графиков

   Что идёт в порт: 0-CPU temp, 1-GPU temp, 2-mother temp, 3-max HDD temp, 4-CPU load, 5-GPU load, 6-RAM use, 7-GPU memory use,
   8-maxFAN, 9-minFAN, 10-maxTEMP, 11-minTEMP, 12-manualFAN, 13-manualCOLOR, 14-fanCtrl, 15-colorCtrl, 16-brightCtrl, 17-LOGinterval, 18-tempSource
*/
// ------------------------ НАСТРОЙКИ ----------------------------
// настройки пределов скорости и температуры по умолчанию (на случай отсутствия связи)
byte speedMIN = 10, speedMAX = 90, tempMIN = 30, tempMAX = 70;
#define DRIVER_VERSION 1    // 0 - маркировка драйвера кончается на 4АТ, 1 - на 4Т
#define COLOR_ALGORITM 0    // 0 или 1 - разные алгоритмы изменения цвета (строка 222)
#define ERROR_DUTY 90       // скорость вентиляторов при потере связи
// ------------------------ НАСТРОЙКИ ----------------------------

// ----------------------- ПИНЫ ---------------------------
#define FAN_PIN 9           // на мосфет вентиляторов
#define R_PIN 5             // на мосфет ленты, красный
#define G_PIN 3             // на мосфет ленты, зелёный
#define B_PIN 6             // на мосфет ленты, синий
#define BTN1 A3             // первая кнопка
#define BTN2 A2             // вторая кнопка
#define SENSOR_PIN 14       // датчик температуры
// ----------------------- ПИНЫ ---------------------------

// -------------------- БИБЛИОТЕКИ ---------------------
#include <OneWire.h>            // библиотека протокола датчиков
#include <DallasTemperature.h>  // библиотека датчика
#include <string.h>             // библиотека расширенной работы со строками
#include <Wire.h>               // библиотека для соединения
#include <LiquidCrystal_I2C.h>  // библтотека дислея
#include <TimerOne.h>           // библиотека таймера
// -------------------- БИБЛИОТЕКИ ---------------------

// -------- АВТОВЫБОР ОПРЕДЕЛЕНИЯ ДИСПЛЕЯ-------------
// Если кончается на 4Т - это 0х27. Если на 4АТ - 0х3f
#if (DRIVER_VERSION)
LiquidCrystal_I2C lcd(0x27, 16, 2);
#else
LiquidCrystal_I2C lcd(0x3f, 16, 2);
#endif
// -------- АВТОВЫБОР ОПРЕДЕЛЕНИЯ ДИСПЛЕЯ-------------

#define printByte(args)  write(args);
#define TEMPERATURE_PRECISION 9
// настройка даьчтков
OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress Thermometer1, Thermometer2;

// стартовый логотип
byte logo0[8] = {0b00011, 0b00110,  0b01110,  0b11111,  0b11011,  0b11001,  0b00000,  0b00000};
byte logo1[8] = {0b10000, 0b00001,  0b00001,  0b00001,  0b00000,  0b10001,  0b11011,  0b11111};
byte logo2[8] = {0b11100, 0b11000,  0b10001,  0b11011,  0b11111,  0b11100,  0b00000,  0b00000};
byte logo3[8] = {0b00000, 0b00001,  0b00011,  0b00111,  0b01101,  0b00111,  0b00010,  0b00000};
byte logo4[8] = {0b11111, 0b11111,  0b11011,  0b10001,  0b00000,  0b00000,  0b00000,  0b00000};
byte logo5[8] = {0b00000, 0b10000,  0b11000,  0b11100,  0b11110,  0b11100,  0b01000,  0b00000};
// значок градуса!!!! lcd.write(223);
byte degree[8] = {0b11100,  0b10100,  0b11100,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000};
// правый край полосы загрузки
byte right_empty[8] = {0b11111,  0b00001,  0b00001,  0b00001,  0b00001,  0b00001,  0b00001,  0b11111};
// левый край полосы загрузки
byte left_empty[8] = {0b11111,  0b10000,  0b10000,  0b10000,  0b10000,  0b10000,  0b10000,  0b11111};
// центр полосы загрузки
byte center_empty[8] = {0b11111, 0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111};
// блоки для построения графиков
byte row8[8] = {0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row7[8] = {0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row6[8] = {0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row5[8] = {0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row4[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111};
byte row3[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111};
byte row2[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111};
byte row1[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111};

char inData[82];       // массив входных значений (СИМВОЛЫ)
int PCdata[20];        // массив численных значений показаний с компьютера
byte PLOTmem[6][16];   // массив для хранения данных для построения графика (16 значений для 6 параметров)
byte blocks, halfs;
byte index = 0;
int display_mode = 6;
String string_convert;
unsigned long timeout, blink_timer, plot_timer;
boolean lightState, reDraw_flag = 1, updateDisplay_flag, updateTemp_flag, timeOut_flag = 1;
int duty, LEDcolor;
int k, b, R, G, B, Rf, Gf, Bf;
byte mainTemp;
byte lines[] = {4, 5, 7, 6};
byte plotLines[] = {0, 1, 4, 5, 6, 7};    // 0-CPU temp, 1-GPU temp, 2-CPU load, 3-GPU load, 4-RAM load, 5-GPU memory
String perc;
unsigned long sec;
unsigned int mins, hrs;
byte temp1, temp2;
boolean btn1_sig, btn2_sig, btn1_flag, btn2_flag;

// Названия для легенды графиков
const char plot_0[] = "CPU";
const char plot_1[] = "GPU";
const char plot_2[] = "RAM";

const char plot_3[] = "temp";
const char plot_4[] = "load";
const char plot_5[] = "mem";
// названия ниже должны совпадать с массивами сверху и идти по порядку!
static const char *plotNames0[]  = {
  plot_0, plot_1, plot_0, plot_1, plot_2, plot_1
};
static const char *plotNames1[]  = {
  plot_3, plot_3, plot_4, plot_4, plot_4, plot_5
};
// 0-CPU temp, 1-GPU temp, 2-CPU load, 3-GPU load, 4-RAM load, 5-GPU memory

