#ifndef __GPIO_H
#define __GPIO_H

#include <cppreg.h>

namespace gpio {

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

}

#endif