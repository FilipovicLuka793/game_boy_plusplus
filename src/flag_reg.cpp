#include "../inc/flag_reg.h"
#include <cstdint>

uint8_t Flag_reg::get_reg(){
    uint8_t ret = 0;
    ret = (ret | this->z) << 1;
    ret = (ret | this->n) << 1;
    ret = (ret | this->h) << 1;
    ret = (ret | this->c) << 4;
    return ret;
}

void Flag_reg::set_reg(uint8_t val){
    if((val & 0x80) != 0){
        this->set_zero();
    }
    if((val & 0x40) != 0){
        this->set_subtraction();
    }
    if((val & 0x20) != 0){
        this->set_half_carry();
    }
    if((val & 0x10) != 0){
        this->set_carry();
    }
}

void Flag_reg::set_zero(){
    this->z = true;
}

void Flag_reg::set_subtraction(){
    this->n = true;
}

void Flag_reg::set_half_carry(){
    this->h = true;
}

void Flag_reg::set_carry(){
    this->c = true;
}

bool Flag_reg::get_zero(){
    return this->z;
}

bool Flag_reg::get_subtraction(){
    return this->n;
}

bool Flag_reg::get_half_carry(){
    return this->h;
}

bool Flag_reg::get_carry(){
    return this->c;
}