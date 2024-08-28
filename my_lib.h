/*
 * my_lib.h
 *
 * Created: 17/06/2024 18:46:41
 *  Author: stefa
 */ 


#ifndef MY_LIB_H_
#define MY_LIB_H_


#define set_bit(porta, bit) porta = porta | (1<<bit)
#define clr_bit(porta, bit) porta = porta & ~(1<<bit)


#endif /* MY_LIB_H_ */