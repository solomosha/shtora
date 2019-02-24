

#include <CustomStepper.h>            // Подключаем библиотеку управления шаговым двигателем. По умолчанию настроена на двигатель 28BYJ-48-5V
CustomStepper stepper(8, 9, 10, 11);  // Указываем пины, к которым подключен драйвер шагового двигателя

#include <iarduino_RTC.h>                                   // Подключаем библиотеку iarduino_RTC для работы с модулями реального времени.
iarduino_RTC time(RTC_DS1307);

#define kolvopovorotov 1




boolean butt_flag = 0;
boolean butt;
unsigned long last_press;




boolean vremya;
boolean h3;



void setup() {
                                            // Ждем готовности модуля отвечать на запросы
  time.begin();                                           // Инициируем работу с модулем.
  time.settime(0, 51, 00, 20, 03, 19, 2);                 // Записываем время в модуль: 0 сек, 51 мин, 21 час, 27, октября, 2015 года, вторник.

  pinMode(4, INPUT_PULLUP);

  stepper.setRPM(12);                 // Устанавливаем кол-во оборотов в минуту
  stepper.setSPR(4075.7728395);           // Устанавливаем кол-во шагов на полный оборот. Максимальное значение 4075.7728395
}

void loop()
{

  butt = digitalRead(4); // считать текущее положение кнопки
  
  h3 = time.gettime("H");



   if (stepper.isDone() && butt == 1 && butt_flag == 0 && millis() - last_press > 100 ) {
      butt_flag = 1;
      stepper.setDirection(CW);         // Устанавливает направление вращения. Может принимать 3 значения: CW - по часовой, CCW - против часовой, STOP
      stepper.rotate(kolvopovorotov);

      last_press = millis();
    }
    if (stepper.isDone() && butt == 0 && butt_flag == 1 && millis() - last_press > 100) {
      butt_flag = 0;
      stepper.setDirection(CCW);         // Устанавливает направление вращения. Может принимать 3 значения: CW - по часовой, CCW - против часовой, STOP
      stepper.rotate(kolvopovorotov);

    }
  stepper.run();
}
