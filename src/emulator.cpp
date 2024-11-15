#include "../inc/emulator.h"

bool Emulator::read_cart(char* path){
    return this->cart.read_cart(path);
}