/*
 * stm32_long_push_switch.cpp
 *
 *  Created on: 2019/09/20
 *      Author: hajime
 */

#include "stm32_long_push_switch.hpp"

void default_callback_func();

Stm32LongPushSwitch *Stm32LongPushSwitch::last_instance_p_ = nullptr;

Stm32LongPushSwitch::Stm32LongPushSwitch(GPIO_TypeDef *gpio_port, uint16_t gpio_pin, GPIO_PinState switch_state_when_push, unsigned int time_count_param)
{
    // 内部変数の初期化
    gpio_port_ = gpio_port;
    gpio_pin_ = gpio_pin;
    time_count_param_ = time_count_param;
    switch_state_when_push_ = switch_state_when_push;
    time_count_ = 0;
    is_time_out_ = 0;
    callback_func_ = default_callback_func;

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

void Stm32LongPushSwitch::set_event_callback(void (*callback_func)())
{
    callback_func_ = callback_func;

    return;
}

void Stm32LongPushSwitch::interrupt_handler()
{
    if (last_instance_p_ == nullptr) return;

    last_instance_p_->interrupt_routine();

    return;
}

void Stm32LongPushSwitch::set_time_count_param(unsigned int time_count_param)
{
    time_count_param_ = time_count_param;
    time_count_ = 0;
    is_time_out_ = 0;
}

// Private function

void Stm32LongPushSwitch::interrupt_routine()
{
    if (HAL_GPIO_ReadPin(gpio_port_, gpio_pin_) == switch_state_when_push_) {
        if (time_count_ >= time_count_param_ && !is_time_out_) {
            time_count_ = 0;
            callback_func_();
            is_time_out_ = 1;
        }
        else {
            time_count_++;
        }
    }
    else {
        time_count_ = 0;
        is_time_out_ = 0;
    }

    if (previous_instance_p_ == nullptr) return;

    previous_instance_p_->interrupt_routine();

    return;
}

// Static function
void default_callback_func()
{
    // デフォルトでは何もしない
    // ユーザーで定義してset_event_callback関数で上書き
}
