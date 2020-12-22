
/* Includes ------------------------------------------------------------------*/
#include "STM32.h"
#include "SButton.h"

#define SW_SET_Pin    GPIO_Port_7
#define SW_SET_Port   GPIOA
#define READY_Pin     GPIO_Port_1
#define READY_Port    GPIOB
#define SW_DOWN_Pin   GPIO_Port_9
#define SW_DOWN_Port  GPIOA
#define SW_UP_Pin     GPIO_Port_10
#define SW_UP_Port    GPIOA



uint32_t Temp_micros, Temp_millis;

int main(void)
{
  SystemClock_Config();                                                         // Обязательная функция. Необходима для инициализации
                                                                                // тактового генератора и ситемного таймера SysTick

  // Инициализация клавиатуры, способ немного отличен от библиотеки Алекса
  SButton Butt_Up(SW_UP_Port, SW_UP_Pin, HIGH_PULL, NORM_OPEN);                 // Назначаем кнопку Up
  Butt_Up.setTickMode(AUTO);                                                    // Включаем для неё автоматический опрос
  SButton Butt_Down(SW_DOWN_Port, SW_DOWN_Pin, HIGH_PULL, NORM_OPEN);           // Назначам кнопку Down
  Butt_Down.setTickMode(AUTO);                                                  // Включаем для неё автоматический опрос
  SButton Butt_Set(SW_SET_Port, SW_SET_Pin, HIGH_PULL, NORM_OPEN);              // Назначаем кнопку Set
  Butt_Set.setTickMode(AUTO);                                                   // Включаем для неё автоматический опрос

  /*
   * Вся остальная работа с кнопками так же как и в оригинальной библиотеке Алекса
   */

  while (1)
  {
    Temp_millis = millis();
    delay(100);
    Temp_millis = millis();
    Temp_micros = micros();
    delay(1);
    Temp_micros = micros();

  }
}


