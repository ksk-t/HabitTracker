/*
 * Point_t.h
 *
 *  Created on: Mar 28, 2021
 *      Author: keisu
 */

#ifndef EXTERNALPERIPHERALS_POINT_H_
#define EXTERNALPERIPHERALS_POINT_H_


struct Point_t
{
	Point_t(uint32_t x_val = 0, uint32_t y_val = 0) : X(x_val), Y(y_val) {};
	uint32_t X{0};
	uint32_t Y{0};
};


#endif /* EXTERNALPERIPHERALS_POINT_H_ */
