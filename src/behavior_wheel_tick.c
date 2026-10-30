/*
 * Emits one REL_WHEEL event of `param1` steps per press, so an encoder detent
 * maps to exactly one wheel click instead of a timed &msc glide.
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_wheel_tick

#include <zephyr/device.h>
#include <zephyr/input/input.h>
#include <drivers/behavior.h>

#include <zmk/behavior.h>

static int on_wheel_tick_pressed(struct zmk_behavior_binding *binding,
                                 struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);

    return input_report_rel(dev, INPUT_REL_WHEEL, (int32_t)binding->param1, true, K_FOREVER);
}

static int on_wheel_tick_released(struct zmk_behavior_binding *binding,
                                  struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_wheel_tick_driver_api = {
    .binding_pressed = on_wheel_tick_pressed,
    .binding_released = on_wheel_tick_released,
};

#define WHEEL_TICK_INST(n)                                                                         \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,                                \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_wheel_tick_driver_api);

DT_INST_FOREACH_STATUS_OKAY(WHEEL_TICK_INST)
