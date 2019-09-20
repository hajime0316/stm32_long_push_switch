/*
 * stm32_long_push_switch.hpp
 *
 *  Created on: 2019/09/20
 *      Author: hajime
 */

#ifndef STM32_LONG_PUSH_SWITCH_HPP_
#define STM32_LONG_PUSH_SWITCH_HPP_

#include "main.h"

class Stm32LongPushSwitch {
  private:
    GPIO_TypeDef *gpio_port_;
    uint16_t gpio_pin_;
    unsigned int time_count_param_;
    unsigned int time_count_;
    GPIO_PinState switch_state_when_push_;

  public:
    Stm32LongPushSwitch(GPIO_TypeDef *, uint16_t, GPIO_PinState, unsigned int);
    ~Stm32LongPushSwitch();
    void event_callback();      // スイッチ長押しした時に呼ばれる関数
                                     // ユーザーが定義する
    static void interrupt_handler(); // 割り込みハンドラ
                                     // TIM割り込み関数の中でコール
    void set_time_count_param(unsigned int);

  private:
    // 全インスタンスにアクセスするためのポインタ．
    // 割り込みルーチンの中で使う．
    Stm32LongPushSwitch *previous_instance_p_;              // 自身の前に生成されたインスタンスへのポインタ
                                                            // 前のインスタンスがない場合はnull
    static Stm32LongPushSwitch *last_instance_p_; // 最後に生成したインスタンスへのポインタ

    // interrupt_handler関数から呼び出される関数
    void interrupt_routine();
};

#endif // STM32_LONG_PUSH_SWITCH_HPP_
