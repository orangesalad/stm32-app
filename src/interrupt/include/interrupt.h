#ifndef _INTERRUPT_H
#define _INTERRUPT_H

template <unsigned int vect_table_sz>
class nvic
{
public:
    nvic()
    {
        // volatile voidPFn_t* origVectorTable = (voidPFn_t*) SCB->VTOR;
        volatile uint32_t *origVectorTable = (uint32_t*) SCB->VTOR;
        // copy the content of the original vector table into the new vector table
        for(uint32_t i = 0; i < vect_table_sz; i++)
        {
            newVectorTable[i] = origVectorTable[i];
        }
        // install the new interrupt vector table
        SCB->VTOR = ((uint32_t) &newVectorTable);
    };

    void register_callback(const unsigned int index, uint32_t addr)
    {
        newVectorTable[index] = addr;
    };

private:
    __attribute__((aligned(0x200))) volatile uint32_t newVectorTable[vect_table_sz];

};

#endif