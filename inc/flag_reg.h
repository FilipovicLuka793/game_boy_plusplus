#ifndef _FLAG_REG_H_
#define _FLAG_REG_H_

#include <cstdint>
class Flag_reg {

    private:

    bool z; //Zero flag
    bool n; //Subtraction flag
    bool h; //Half carry flag
    bool c; //Carry flag

    public:

    uint8_t get_reg();
    void set_reg(uint8_t val);

    void set_zero(bool z);
    void set_subtraction(bool n);
    void set_half_carry(bool h);
    void set_carry(bool c);

    bool get_zero();
    bool get_subtraction();
    bool get_half_carry();
    bool get_carry();

};

#endif