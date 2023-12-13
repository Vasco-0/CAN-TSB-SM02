/*
	Copyright 2012-2018 Benjamin Vedder	benjamin@vedder.se
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */
    
#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

// Intel is little-endian which means that the least-significant byte is stored first
// Motorola is big-endian which means that the most-significant byte is stored first  

// By Default CAN TSB Library uses Motorola Byte order, some boat componets like the MGM controller use Intel byte order.

// Event though new code should make used of either motorola or intel function the if none is specificed motorola is used
// This way this code is still compatible with all the old code. When all code have been ported the const auto declaration at 
// the end of this file can be deleted

void buffer_append_int8(uint8_t* buffer, int8_t number, int32_t *index);
void buffer_append_uint8(uint8_t* buffer, uint8_t number, int32_t *index);
void buffer_append_int16_motorola(uint8_t* buffer, int16_t number, int32_t *index);
void buffer_append_int16_intel(uint8_t* buffer, int16_t number, int32_t *index);
void buffer_append_uint16_motorola(uint8_t* buffer, uint16_t number, int32_t *index);
void buffer_append_uint16_intel(uint8_t* buffer, uint16_t number, int32_t *index);
void buffer_append_int32_motorola(uint8_t* buffer, int32_t number, int32_t *index);
void buffer_append_int32_intel(uint8_t* buffer, int32_t number, int32_t *index);
void buffer_append_uint32_motorola(uint8_t* buffer, uint32_t number, int32_t *index);
void buffer_append_uint32_intel(uint8_t* buffer, uint32_t number, int32_t *index);
void buffer_append_int64_motorola(uint8_t* buffer, int64_t number, int32_t *index);
void buffer_append_int64_intel(uint8_t* buffer, int64_t number, int32_t *index);
void buffer_append_uint64_motorola(uint8_t* buffer, uint64_t number, int32_t *index);
void buffer_append_uint64_intel(uint8_t* buffer, uint64_t number, int32_t *index);
void buffer_append_float8(uint8_t* buffer, float number, float scale, int32_t *index);
void buffer_append_float16_motorola(uint8_t* buffer, float number, float scale, int32_t *index);
void buffer_append_float16_intel(uint8_t* buffer, float number, float scale, int32_t *index);
void buffer_append_float32_motorola(uint8_t* buffer, float number, float scale, int32_t *index);
void buffer_append_float32_intel(uint8_t* buffer, float number, float scale, int32_t *index);
void buffer_append_double64_motorola(uint8_t* buffer, double number, double scale, int32_t *index);
void buffer_append_double64_intel(uint8_t* buffer, double number, double scale, int32_t *index);
void buffer_append_float32_auto_motorola(uint8_t* buffer, float number, int32_t *index);
void buffer_append_float32_auto_intel(uint8_t* buffer, float number, int32_t *index);
int8_t buffer_get_int8(const uint8_t *buffer, int32_t *index);
uint8_t buffer_get_uint8(const uint8_t *buffer, int32_t *index);
int16_t buffer_get_int16_motorola(const uint8_t *buffer, int32_t *index);
int16_t buffer_get_int16_intel(const uint8_t *buffer, int32_t *index);
uint16_t buffer_get_uint16_motorola(const uint8_t *buffer, int32_t *index);
uint16_t buffer_get_uint16_intel(const uint8_t *buffer, int32_t *index);
int32_t buffer_get_int32_motorola(const uint8_t *buffer, int32_t *index);
int32_t buffer_get_int32_intel(const uint8_t *buffer, int32_t *index);
uint32_t buffer_get_uint32_motorola(const uint8_t *buffer, int32_t *index);
uint32_t buffer_get_uint32_intel(const uint8_t *buffer, int32_t *index);
int64_t buffer_get_int64_motorola(const uint8_t *buffer, int32_t *index);
int64_t buffer_get_int64_intel(const uint8_t *buffer, int32_t *index);
uint64_t buffer_get_uint64_motorola(const uint8_t *buffer, int32_t *index);
uint64_t buffer_get_uint64_intel(const uint8_t *buffer, int32_t *index);
float buffer_get_float8(const uint8_t *buffer, float scale, int32_t *index);
float buffer_get_ufloat8(const uint8_t *buffer, float scale, int32_t *index);
float buffer_get_float16_motorola(const uint8_t *buffer, float scale, int32_t *index);
float buffer_get_float16_intel(const uint8_t *buffer, float scale, int32_t *index);
float buffer_get_ufloat16_intel(const uint8_t *buffer, float scale, int32_t *index);
float buffer_get_float32_motorola(const uint8_t *buffer, float scale, int32_t *index);
float buffer_get_float32_intel(const uint8_t *buffer, float scale, int32_t *index);
double buffer_get_double64_motorola(const uint8_t *buffer, double scale, int32_t *index);
double buffer_get_double64_intel(const uint8_t *buffer, double scale, int32_t *index);
float buffer_get_float32_auto_motorola(const uint8_t *buffer, int32_t *index);
float buffer_get_float32_auto_intel(const uint8_t *buffer, int32_t *index);

const auto buffer_append_int16 = buffer_append_int16_motorola;
const auto buffer_append_uint16 = buffer_append_uint16_motorola;
const auto buffer_append_int32 = buffer_append_int32_motorola;
const auto buffer_append_uint32 = buffer_append_uint32_motorola;
const auto buffer_append_int64 = buffer_append_int64_motorola;
const auto buffer_append_uint64 = buffer_append_uint64_motorola;
const auto buffer_append_float16 = buffer_append_float16_motorola;
const auto buffer_append_float32 = buffer_append_float32_motorola;
const auto buffer_append_double64 = buffer_append_double64_motorola;
const auto buffer_append_float32_auto = buffer_append_float32_auto_motorola;
const auto buffer_get_int16 = buffer_get_int16_motorola;
const auto buffer_get_uint16 = buffer_get_uint16_motorola;
const auto buffer_get_int32 = buffer_get_int32_motorola;
const auto buffer_get_uint32 = buffer_get_uint32_motorola;
const auto buffer_get_int64 = buffer_get_int64_motorola;
const auto buffer_get_uint64 = buffer_get_uint64_motorola;
const auto buffer_get_float16 = buffer_get_float16_motorola;
const auto buffer_get_float32 = buffer_get_float32_motorola;
const auto buffer_get_double64 = buffer_get_double64_motorola;
const auto buffer_get_float32_auto = buffer_get_float32_auto_motorola;

#endif /* BUFFER_H_ */
