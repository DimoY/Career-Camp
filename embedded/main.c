#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
//Segment binary code binded to variables
#define SEVEN_SEG_0   63
#define SEVEN_SEG_1   6
#define SEVEN_SEG_2   91
#define SEVEN_SEG_3   79
#define SEVEN_SEG_4   102
#define SEVEN_SEG_5   109
#define SEVEN_SEG_6   125
#define SEVEN_SEG_7   7
#define SEVEN_SEG_8   127
#define SEVEN_SEG_9   111
#define SEVEN_SEG_DOT 128

//Struct for money
struct amount{
	uint16_t amount1;
	uint16_t amount2;
	uint16_t base;
};
//Add two values together,compatable for number bigger than  9999
void add_value(struct amount* base,struct amount* add){
	char carry = 0;
	base->amount1+=add->amount1;
	if(base->amount1>=base->base){
		carry+=1;
		base->amount1-=base->base;
	}
	base->amount2+=(add->amount2+carry);
}

//Subtract two values, compatable for numbers bigger than 9999
void sub_value(struct amount* base,struct amount* sub){
	if(base->amount2<sub->amount2 && (base->amount2 != sub->amount2 || base->amount1<sub->amount1)){
		printf("Error: cant have negative numbers");
		return;
	}
	base->amount2-=sub->amount2;
	if(base->amount1<sub->amount1){
		base->amount2--;
		base->amount1+=100*100;
	}
	base->amount1-=sub->amount1;
}
//Draw digit 
uint16_t draw_digit(uint8_t position, uint8_t digit_value){
		switch (digit_value)
		{
		case SEVEN_SEG_0:
			printf("0 ");
			break;
		case SEVEN_SEG_1:
			printf("1 ");
			break;
		case SEVEN_SEG_2:
			printf("2 ");
			break;
		case SEVEN_SEG_3:
			printf("3 ");
			break;
		case SEVEN_SEG_4:
			printf("4 ");
			break;
		case SEVEN_SEG_5:
			printf("5 ");
			break;
		case SEVEN_SEG_6:
			printf("6 ");
			break;
		case SEVEN_SEG_7:
			printf("7 ");
			break;
		case SEVEN_SEG_8:
			printf("8 ");
			break;
		case SEVEN_SEG_9:
			printf("9 ");
			break;
		case SEVEN_SEG_DOT:
			printf(". ");
			break;
		}
	
	return 0;
}

//Error checking; transform intregers to custom struct
struct amount* value_to_custom(uint16_t amount2,uint16_t amount1){
	struct amount* val = (struct amount*)malloc(sizeof(struct amount));
	if(val->amount1>9999 && val->amount2>9999){
		printf("Error: init numbers too large for 8 segment display");
		val->amount1 = 0;
		val->amount2 = 0;
	}
	val->amount1 = amount1;
	val->amount2 = amount2;
	val->base = 100*100;
	return val;
}

//get a one digit number and return its representation
uint8_t transform_digit(char a){
	switch (a)
	{
	case 0:
		return SEVEN_SEG_0;
	case 1:
		
		return SEVEN_SEG_1;
	case 2:
		return SEVEN_SEG_2;
	case 3:
		return SEVEN_SEG_3;
	case 4:
		return SEVEN_SEG_4;
	case 5:
		return SEVEN_SEG_5;
	case 6:
		return SEVEN_SEG_6;
	case 7:
		return SEVEN_SEG_7;
	case 8:
		return SEVEN_SEG_8;
	case 9:
		return SEVEN_SEG_9;
	case 10:
		return SEVEN_SEG_DOT;
		
	}
	return 0;
}
// prints the numbers; use only one function
void print(struct amount* base){
	uint16_t left = base->amount1;
	for(char i =0;i<4;i++){
		if(i == 2){
			draw_digit(i,transform_digit(10));
		}
		if(left >0){
			draw_digit(i+i>2,transform_digit(left%10));
		}else{
			break;
		}
		left/=10;
	}
	left  = base->amount2;
	for(char i = 0;i<5;i++){
		if(left >0){
			draw_digit(4+i,transform_digit(left%10));
		}else{
			break;
		}
		left/=10;
	}
}
//simply frees the memory
void free_value(struct amount* base){
	free(base);
}
//set values to zeroes; useful for "C" button
void nulls(struct amount* base){
	base->amount1 = 0;
	base->amount2 = 0;
}
int main(int argc, char const *argv[])
{
	struct amount* val = value_to_custom(100,9101);
	struct amount* val2 = value_to_custom(0,3);
	
	add_value(val,val2);
	sub_value(val,val2);
	free_value(val2);
	print(val);
	free(val);
	return 0;
}
