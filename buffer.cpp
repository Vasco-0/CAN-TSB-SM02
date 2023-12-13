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

#include "buffer.h"
#include <math.h>
#include <stdbool.h>

void buffer_append_int8(uint8_t* buffer, int8_t number, int32_t *index) {
	buffer[(*index)++] = number;
}

void buffer_append_uint8(uint8_t* buffer, uint8_t number, int32_t *index) {
	buffer[(*index)++] = number;
}

void buffer_append_int16_motorola(uint8_t* buffer, int16_t number, int32_t *index) {
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_int16_intel(uint8_t* buffer, int16_t number, int32_t *index) {
	buffer[(*index)++] = number;
	buffer[(*index)++] = number >> 8;
}

void buffer_append_uint16_motorola(uint8_t* buffer, uint16_t number, int32_t *index) {
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_uint16_intel(uint8_t* buffer, uint16_t number, int32_t *index) {
	buffer[(*index)++] = number;
	buffer[(*index)++] = number >> 8;
}

void buffer_append_int32_motorola(uint8_t* buffer, int32_t number, int32_t *index) {
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_int32_intel(uint8_t* buffer, int32_t number, int32_t *index) {
	buffer[(*index)++] = number;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 24;
}

void buffer_append_uint32_motorola(uint8_t* buffer, uint32_t number, int32_t *index) {
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_uint32_intel(uint8_t* buffer, uint32_t number, int32_t *index) {
	buffer[(*index)++] = number;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 24;
}

void buffer_append_int64_motorola(uint8_t* buffer, int64_t number, int32_t *index) {
	buffer[(*index)++] = number >> 56;
	buffer[(*index)++] = number >> 48;
	buffer[(*index)++] = number >> 40;
	buffer[(*index)++] = number >> 32;
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_int64_intel(uint8_t* buffer, int64_t number, int32_t *index) {
	buffer[(*index)++] = number;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 32;
	buffer[(*index)++] = number >> 40;
	buffer[(*index)++] = number >> 48;
	buffer[(*index)++] = number >> 56;
}

void buffer_append_uint64_motorola(uint8_t* buffer, uint64_t number, int32_t *index) {
	buffer[(*index)++] = number >> 56;
	buffer[(*index)++] = number >> 48;
	buffer[(*index)++] = number >> 40;
	buffer[(*index)++] = number >> 32;
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number;
}

void buffer_append_uint64_intel(uint8_t* buffer, uint64_t number, int32_t *index) {
	buffer[(*index)++] = number;
	buffer[(*index)++] = number >> 8;
	buffer[(*index)++] = number >> 16;
	buffer[(*index)++] = number >> 24;
	buffer[(*index)++] = number >> 32;
	buffer[(*index)++] = number >> 40;
	buffer[(*index)++] = number >> 48;
	buffer[(*index)++] = number >> 56;
}

void buffer_append_float8(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int8(buffer, (int16_t)(number * scale), index);
}

void buffer_append_float16_motorola(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int16_motorola(buffer, (int16_t)(number * scale), index);
}

void buffer_append_float16_intel(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int16_intel(buffer, (int16_t)(number * scale), index);
}

void buffer_append_float32_motorola(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int32_motorola(buffer, (int32_t)(number * scale), index);
}

void buffer_append_float32_intel(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int32_intel(buffer, (int32_t)(number * scale), index);
}

void buffer_append_double64_motorola(uint8_t* buffer, double number, double scale, int32_t *index) {
	buffer_append_int64_motorola(buffer, (int64_t)(number * scale), index);
}

void buffer_append_double64_intel(uint8_t* buffer, double number, double scale, int32_t *index) {
	buffer_append_int64_intel(buffer, (int64_t)(number * scale), index);
}

void buffer_append_float32_auto_motorola(uint8_t* buffer, float number, int32_t *index) {
	int e = 0;
	float sig = frexpf(number, &e);
	float sig_abs = fabsf(sig);
	uint32_t sig_i = 0;

	if (sig_abs >= 0.5) {
		sig_i = (uint32_t)((sig_abs - 0.5f) * 2.0f * 8388608.0f);
		e += 126;
	}

	uint32_t res = ((e & 0xFF) << 23) | (sig_i & 0x7FFFFF);
	if (sig < 0) {
		res |= 1 << 31;
	}

	buffer_append_uint32_motorola(buffer, res, index);
}

void buffer_append_float32_auto_intel(uint8_t* buffer, float number, int32_t *index) {
	int e = 0;
	float sig = frexpf(number, &e);
	float sig_abs = fabsf(sig);
	uint32_t sig_i = 0;

	if (sig_abs >= 0.5) {
		sig_i = (uint32_t)((sig_abs - 0.5f) * 2.0f * 8388608.0f);
		e += 126;
	}

	uint32_t res = ((e & 0xFF) << 23) | (sig_i & 0x7FFFFF);
	if (sig < 0) {
		res |= 1 << 31;
	}

	buffer_append_uint32_intel(buffer, res, index);
}

int8_t buffer_get_int8(const uint8_t *buffer, int32_t *index) {
	return (int8_t) buffer[(*index)++];
}

uint8_t buffer_get_uint8(const uint8_t *buffer, int32_t *index) {
	return (uint8_t) buffer[(*index)++];
}

int16_t buffer_get_int16_motorola(const uint8_t *buffer, int32_t *index) {
	int16_t res =	((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}

int16_t buffer_get_int16_intel(const uint8_t *buffer, int32_t *index) {
	int16_t res =	((uint16_t) buffer[*index + 1]) << 8 |
					((uint16_t) buffer[*index]);
	*index += 2;
	return res;
}

uint16_t buffer_get_uint16_motorola(const uint8_t *buffer, int32_t *index) {
	uint16_t res = 	((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}

uint16_t buffer_get_uint16_intel(const uint8_t *buffer, int32_t *index) {
	uint16_t res = 	((uint16_t) buffer[*index + 1]) << 8 |
					((uint16_t) buffer[*index]);
	*index += 2;
	return res;
}

int32_t buffer_get_int32_motorola(const uint8_t *buffer, int32_t *index) {
	int32_t res =	((uint32_t) buffer[*index]) << 24 |
					((uint32_t) buffer[*index + 1]) << 16 |
					((uint32_t) buffer[*index + 2]) << 8 |
					((uint32_t) buffer[*index + 3]);
	*index += 4;
	return res;
}

int32_t buffer_get_int32_intel(const uint8_t *buffer, int32_t *index) {
	int32_t res =	((uint32_t) buffer[*index + 3]) << 24 |
					((uint32_t) buffer[*index + 2]) << 16 |
					((uint32_t) buffer[*index + 1]) << 8 |
					((uint32_t) buffer[*index]);
	*index += 4;
	return res;
}

uint32_t buffer_get_uint32_motorola(const uint8_t *buffer, int32_t *index) {
	uint32_t res =	((uint32_t) buffer[*index]) << 24 |
					((uint32_t) buffer[*index + 1]) << 16 |
					((uint32_t) buffer[*index + 2]) << 8 |
					((uint32_t) buffer[*index + 3]);
	*index += 4;
	return res;
}

uint32_t buffer_get_uint32_intel(const uint8_t *buffer, int32_t *index) {
	uint32_t res =	((uint32_t) buffer[*index + 3]) << 24 |
					((uint32_t) buffer[*index + 2]) << 16 |
					((uint32_t) buffer[*index + 1]) << 8 |
					((uint32_t) buffer[*index]);
	*index += 4;
	return res;
}

int64_t buffer_get_int64_motorola(const uint8_t *buffer, int32_t *index) {
	int64_t res =	((uint64_t) buffer[*index]) << 56 |
					((uint64_t) buffer[*index + 1]) << 48 |
					((uint64_t) buffer[*index + 2]) << 40 |
					((uint64_t) buffer[*index + 3]) << 32 |
					((uint64_t) buffer[*index + 4]) << 24 |
					((uint64_t) buffer[*index + 5]) << 16 |
					((uint64_t) buffer[*index + 6]) << 8 |
					((uint64_t) buffer[*index + 7]);
	*index += 8;
	return res;
}

int64_t buffer_get_int64_intel(const uint8_t *buffer, int32_t *index) {
	int64_t res =	((uint64_t) buffer[*index + 7]) << 56 |
					((uint64_t) buffer[*index + 6]) << 48 |
					((uint64_t) buffer[*index + 5]) << 40 |
					((uint64_t) buffer[*index + 4]) << 32 |
					((uint64_t) buffer[*index + 3]) << 24 |
					((uint64_t) buffer[*index + 2]) << 16 |
					((uint64_t) buffer[*index + 1]) << 8 |
					((uint64_t) buffer[*index]);
	*index += 8;
	return res;
}

uint64_t buffer_get_uint64_motorola(const uint8_t *buffer, int32_t *index) {
	uint64_t res =	((uint64_t) buffer[*index]) << 56 |
					((uint64_t) buffer[*index + 1]) << 48 |
					((uint64_t) buffer[*index + 2]) << 40 |
					((uint64_t) buffer[*index + 3]) << 32 |
					((uint64_t) buffer[*index + 4]) << 24 |
					((uint64_t) buffer[*index + 5]) << 16 |
					((uint64_t) buffer[*index + 6]) << 8 |
					((uint64_t) buffer[*index + 7]);
	*index += 8;
	return res;
}

uint64_t buffer_get_uint64_intel(const uint8_t *buffer, int32_t *index) {
	uint64_t res =	((uint64_t) buffer[*index + 7]) << 56 |
					((uint64_t) buffer[*index + 6]) << 48 |
					((uint64_t) buffer[*index + 5]) << 40 |
					((uint64_t) buffer[*index + 4]) << 32 |
					((uint64_t) buffer[*index + 3]) << 24 |
					((uint64_t) buffer[*index + 2]) << 16 |
					((uint64_t) buffer[*index + 1]) << 8 |
					((uint64_t) buffer[*index]);
	*index += 8;
	return res;
}

float buffer_get_float8(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int8(buffer, index) / scale;
}

float buffer_get_ufloat8(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_uint8(buffer, index) / scale;
}

float buffer_get_float16_motorola(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int16_motorola(buffer, index) / scale;
}

float buffer_get_float16_intel(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int16_intel(buffer, index) / scale;
}

float buffer_get_ufloat16_intel(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_uint16_intel(buffer, index) / scale;
}

float buffer_get_float32_motorola(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int32_motorola(buffer, index) / scale;
}

float buffer_get_float32_intel(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int32_intel(buffer, index) / scale;
}

double buffer_get_double64_motorola(const uint8_t *buffer, double scale, int32_t *index) {
    return (double)buffer_get_int64_motorola(buffer, index) / scale;
}

double buffer_get_double64_intel(const uint8_t *buffer, double scale, int32_t *index) {
    return (double)buffer_get_int64_intel(buffer, index) / scale;
}

float buffer_get_float32_auto_motorola(const uint8_t *buffer, int32_t *index) {
	uint32_t res = buffer_get_uint32_motorola(buffer, index);

	int e = (res >> 23) & 0xFF;
	uint32_t sig_i = res & 0x7FFFFF;
	bool neg = res & (1 << 31);

	float sig = 0.0;
	if (e != 0 || sig_i != 0) {
		sig = (float)sig_i / (8388608.0 * 2.0) + 0.5;
		e -= 126;
	}

	if (neg) {
		sig = -sig;
	}

	return ldexpf(sig, e);
}

float buffer_get_float32_auto_intel(const uint8_t *buffer, int32_t *index) {
	uint32_t res = buffer_get_uint32_intel(buffer, index);

	int e = (res >> 23) & 0xFF;
	uint32_t sig_i = res & 0x7FFFFF;
	bool neg = res & (1 << 31);

	float sig = 0.0;
	if (e != 0 || sig_i != 0) {
		sig = (float)sig_i / (8388608.0 * 2.0) + 0.5;
		e -= 126;
	}

	if (neg) {
		sig = -sig;
	}

	return ldexpf(sig, e);
}
