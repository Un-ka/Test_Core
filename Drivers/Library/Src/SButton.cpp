#include "SButton.h"
#include "STM32.h"

// ==================== CONSTRUCTOR ====================
SButton::SButton(GPIO_TypeDef *GPIOx_IN, uint16_t GPIO_Pin_IN, bool type, bool dir)
{
    _GPIOx_IN     = GPIOx_IN;
    _GPIO_Pin_IN  = GPIO_Pin_IN;
    flags.noPin   = false;

#if defined(STM32F030x6)
  if(_GPIOx_IN == GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  if(_GPIOx_IN == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
  if(_GPIOx_IN == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  if(_GPIOx_IN == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
  if(_GPIOx_IN == GPIOF) RCC->AHBENR |= RCC_AHBENR_GPIOFEN;

  uint32_t I;
  uint16_t D;

  // Инициализируем вывод IN
  I = 0;
  D = _GPIO_Pin_IN;
  while(I < 16) { D = D >> 1; if(D == 0) break; I++; }                          // Подсчитываем номер бита который соответствует настраиваемому выводу
  _GPIOx_IN->MODER    &= ~(0b11 << (I * 2));                                    // Затираем биты порта устанавливая порт на вход
  _GPIOx_IN->OSPEEDR  |=  0b11 << (I * 2);                                      // Врубаем максимальную скорость порта

  if(type)
  {
    _GPIOx_IN->PUPDR &= ~(0b11 << (I * 2));                                     // Сбрасываем регистр подтяжки
    _GPIOx_IN->PUPDR |=  0b10 << (I * 2);                                       // Подтягиваем вывод к земле
  }
  else
  {
    _GPIOx_IN->PUPDR &= ~(0b11 << (I * 2));                                     // Сбрасываем регистр подтяжки
    _GPIOx_IN->PUPDR |=  0b01 << (I * 2);                                       // Подтягиваем вывод к питанию
  }

#endif // defined(STM32F030x6)

  flags.type      = type;
  flags.mode      = false;
  flags.tickMode  = false;
  flags.inv_state = dir;
}

// ==================== SET ====================
void SButton::setDebounce(uint16_t debounce)
{
  _debounce = debounce;
}
void SButton::setTimeout(uint16_t new_timeout)
{
  _timeout = new_timeout;
}
void SButton::setClickTimeout(uint16_t new_timeout)
{
  _click_timeout = new_timeout;
}
void SButton::setStepTimeout(uint16_t step_timeout)
{
  _step_timeout = step_timeout;
}

void SButton::setDirection(bool dir)
{
  flags.inv_state = dir;
}
void SButton::setTickMode(bool tickMode)
{
  flags.tickMode = tickMode;
}

// ==================== IS ====================
bool SButton::isPress()
{
  if(flags.tickMode) SButton::tick();
  if(flags.isPress_f)
  {
    flags.isPress_f = false;
    return true;
  }
  else return false;
}
bool SButton::isRelease()
{
  if(flags.tickMode) SButton::tick();
  if(flags.isRelease_f)
  {
    flags.isRelease_f = false;
    return true;
  }
  else return false;
}
bool SButton::isClick()
{
  if(flags.tickMode) SButton::tick();
  if(flags.isOne_f)
  {
    flags.isOne_f = false;
    return true;
  }
  else return false;
}
bool SButton::isHolded()
{
  if(flags.tickMode) SButton::tick();
  if(flags.isHolded_f)
  {
    flags.isHolded_f = false;
    return true;
  }
  else return false;
}
bool SButton::isHold()
{
  if(flags.tickMode) SButton::tick();
  if(flags.step_flag) return true;
  else return false;
}
bool SButton::state()
{
  if(flags.tickMode) SButton::tick();
  return btn_state;
}
bool SButton::isSingle()
{
  if(flags.tickMode) SButton::tick();
  if(flags.counter_flag && last_counter == 1)
  {
    last_counter = 0;
    flags.counter_flag = false;
    return true;
  }
  else return false;
}
bool SButton::isDouble()
{
  if(flags.tickMode) SButton::tick();
  if(flags.counter_flag && last_counter == 2)
  {
    flags.counter_flag = false;
    last_counter = 0;
    return true;
  }
  else return false;
}
bool SButton::isTriple()
{
  if(flags.tickMode) SButton::tick();
  if(flags.counter_flag && last_counter == 3)
  {
    flags.counter_flag = false;
    last_counter = 0;
    return true;
  }
  else return false;
}
bool SButton::hasClicks()
{
  if(flags.tickMode) SButton::tick();
  if(flags.counter_flag)
  {
    flags.counter_flag = false;
    return true;
  }
  else return false;
}
uint8_t SButton::getClicks()
{
  uint8_t thisCount = last_counter;
  last_counter = 0;
  return thisCount;
}
uint8_t SButton::getHoldClicks()
{
  if(flags.tickMode) SButton::tick();
  return flags.hold_flag ? last_hold_counter : 0;
}
bool SButton::isStep(uint8_t clicks)
{
  if(flags.tickMode) SButton::tick();
  if(btn_counter == clicks && flags.step_flag && (millis() - btn_timer >= _step_timeout))
  {
    btn_timer = millis();
    return true;
  }
  else return false;
}

void SButton::resetStates()
{
  flags.isPress_f = false;
  flags.isRelease_f = false;
  flags.isOne_f = false;
  flags.isHolded_f = false;
  flags.step_flag = false;
  flags.counter_flag = false;
  last_hold_counter = 0;
  last_counter = 0;
}

// ==================== TICK ====================
void SButton::tick(bool state)
{
  flags.mode = true;
  btn_state = state ^ flags.inv_state;
  SButton::tick();
  flags.mode = false;
}

void SButton::tick()
{
  // читаем пин
#if defined(STM32F030x6)
  if(!flags.mode && !flags.noPin)
    btn_state = !(_GPIOx_IN->IDR & _GPIO_Pin_IN) ^ (flags.inv_state ^ flags.type);
#endif //defined(STM32F030x6)
  uint32_t thisMls = millis();

  // нажатие
  if(btn_state && !btn_flag)
  {
    if(!flags.btn_deb)
    {
      flags.btn_deb = true;
      btn_timer = thisMls;
    }
    else
    {
      if(thisMls - btn_timer >= _debounce)
      {
        btn_flag = true;
        flags.isPress_f = true;
        flags.oneClick_f = true;
      }
    }
  }
  else
  {
    flags.btn_deb = false;
  }

  // отпускание
  if(!btn_state && btn_flag)
  {
    btn_flag = false;
    if(!flags.hold_flag) btn_counter++;
    flags.hold_flag = false;
    flags.isRelease_f = true;
    btn_timer = thisMls;
    if(flags.step_flag)
    {
      last_counter = 0;
      btn_counter = 0;
      flags.step_flag = false;
    }
    if(flags.oneClick_f)
    {
      flags.oneClick_f = false;
      flags.isOne_f = true;
    }
  }

  // кнопка удерживается
  if(btn_flag && btn_state && (thisMls - btn_timer >= _timeout) && !flags.hold_flag)
  {
    flags.hold_flag = true;
    last_hold_counter = btn_counter;
    //btn_counter = 0;
    //last_counter = 0;
    flags.isHolded_f = true;
    flags.step_flag = true;
    flags.oneClick_f = false;
    btn_timer = thisMls;
  }

  // обработка накликивания
  if((thisMls - btn_timer >= _click_timeout) && (btn_counter != 0))
  {
    last_counter = btn_counter;
    btn_counter = 0;
    flags.counter_flag = true;
  }
}
