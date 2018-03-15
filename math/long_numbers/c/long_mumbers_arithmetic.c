#include <long_numbers.h>

int add_integer_128(uint8_t *A, uint8_t *B, uint8_t *R)
{
	int i;
	uint8_t carry;
	if (!A || !B || !R) {
	//	perror("");
		return -1;
	}

	carry = 0;
	for (i = 0; i < 128; i++) {
		R[i] = A[i] + B[i] + carry;
		carry = (R[i] < A[i] || R[i] < B[i]) ? 1 : 0;
	}

	return carry;
}

int sub_integer_128(uint8_t *A, uint8_t *B, uint8_t *R)
{
	int i;
	uint8_t borrow;
	if (!A || !B || !R) {
	//	perror("");
		return -1;
	}

	borrow = 0;
	for (i = 0; i < 128; i++) {
		R[i] = A[i] - B[i] - borrow;
		borrow = (R[i] < A[i] || R[i] < B[i]) ? 1 : 0;
	}

	return borrow;
}
