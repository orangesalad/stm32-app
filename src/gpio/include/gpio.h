#ifndef __GPIO_H
#define __GPIO_H

#include <cppreg.h>

namespace gpio {

    enum GpioPort: std::uint32_t
    {
        PORTA = 0x48000000
    };

    /**
     * @brief gpio_base
     * 
     * @tparam Address 
     */
    template <std::uint32_t Address>
    struct gpio_base
    {
        // // Register pack.
        // // 11 x 32-bits
        using gpio_pack = cppreg::RegisterPack<Address, 11 * 4>;
        
        using moder     = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 0 * 32>;
        using otyper    = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 1 * 32>;
        using ospeedr   = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 2 * 32>;
        using pupdr     = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 3 * 32>;
        using idr       = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 4 * 32>;
        using odr       = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 5 * 32>;
        using bsrr      = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 6 * 32>;
        using lckr      = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 7 * 32>;
        using afrl      = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 8 * 32>;
        using afrh      = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 9 * 32>;
        using brr       = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 10 * 32>;
        using ascr      = cppreg::PackedRegister<gpio_pack, cppreg::RegBitSize::b32, 11 * 32>;
    };

    /**
     * @brief DigitalOut
     * 
     * @tparam Port
     * @tparam Pin 
     */
    template < GpioPort Port, std::uint8_t Pin>
    struct DigitalOut
    {
        using gpiox = gpio_base<Port>;
        // //moder == 0b01
        // //ospeedr == 0b00
        // //pupdr == 0b00
        // //bssr -> 0-15 = set, 16-31 = reset
        using pin_direction = cppreg::Field<typename gpiox::moder, 2u, Pin*2, cppreg::read_write>;
        using pin_speed = cppreg::Field<typename gpiox::ospeedr, 2u, Pin*2, cppreg::read_write>;
        using pin_pull = cppreg::Field<typename gpiox::pupdr, 2u, Pin*2, cppreg::read_write>;
        using pin_set = cppreg::Field<typename gpiox::bsrr, 1u, Pin, cppreg::read_write>;
        using pin_clear = cppreg::Field<typename gpiox::bsrr, 1u, Pin + 16, cppreg::read_write>;

        // // We can now define the static methods of the interface.
        // // The pin output direction is set in the init method.
        inline static void on() {
            pin_set::write(1U);
        };
        inline static void off() {
            pin_clear::write(1u);
        };
        // inline static void toggle() {
        //     pin_toggle::set();   // Set PTOR to 1.
        // };
        inline static void init() {
            off();
            pin_direction::write(1U);
            pin_speed::write(0U);
            pin_pull::write(0U);
        };        
    };
}

#endif