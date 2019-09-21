/*
 * stm32_long_push_switch.cpp
 *
 *  Created on: 2019/09/20
 *      Author: hajime
 */

#include "stm32_long_push_switch.hpp"

Stm32LongPushSwitch *Stm32LongPushSwitch::last_instance_p_ = nullptr;

Stm32LongPushSwitch::Stm32LongPushSwitch(GPIO_TypeDef *gpio_port, uint16_t gpio_pin, GPIO_PinState switch_state_when_push, unsigned int time_count_param)
{
    // 内部変数の初期化
    gpio_port_ = gpio_port;
    gpio_port_ = gpio_port;
    time_count_param_ = time_count_param;
    GPIO_PinState switch_state_when_push_ = switch_state_when_push;
    time_count_ = 0;

    // pointerの初期化
    previous_instance_p_ = last_instance_p_;
    last_instance_p_ = this;
}

Stm32LongPushSwitch::~Stm32LongPushSwitch()
{
    if (last_instance_p_ == nullptr) {
        return;
    }

    if (last_instance_p_ == this) {
        last_instance_p_ = this->previous_instance_p_;
        return;
    }

    Stm32LongPushSwitch *i_p = last_instance_p_;
    while (true) {
        if (i_p->previous_instance_p_ == this) {
            i_p->previous_instance_p_ = this->previous_instance_p_;
            return;
        }
        else {
            i_p = i_p->previous_instance_p_;
            continue;
        }
    }
}

__weak void Stm32LongPushSwitch::event_callback()
{
    // デフォルトでは何もしない
    // ユーザー側で定義する
}

void Stm32LongPushSwitch::interrupt_handler()
{
}

void Stm32LongPushSwitch::set_time_count_param(unsigned int time_count_param)
{
}

void interrupt_routine()
{
}
