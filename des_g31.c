#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned char uint8;
typedef unsigned long long uint64;

/* ************************************************** TABLES ************************************************** */

/* PC-1 */
int PC1[] = {57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27,
		19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14,  6, 61, 53, 45, 37, 29,
		21, 13,  5, 28, 20, 12, 4};

int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17,  9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7};

int PC2[] = {14, 17, 11, 24,  1,  5,  3, 28,
		15,  6, 21, 10, 23, 19, 12,  4,
		26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32};

int E[] = {32,  1,  2,  3,  4,  5,
		4,  5,  6,  7,  8,  9,
		8,  9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32,  1};

int P[] = {16,  7, 20, 21, 29, 12, 28, 17,
		1, 15, 23, 26,  5, 18, 31, 10,
		2,  8, 24, 14, 32, 27,  3,  9,
		19, 13, 30,  6, 22, 11,  4, 25};

int FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41,  9, 49, 17, 57, 25};

int s[8][4][16] = {
		{ 14, 4,  13, 1, 2,  15, 11, 8,  3,  10, 6,  12, 5,
				9,  0,  7,  0, 15, 7,  4,  14, 2,  13, 1,  10, 6,
				12, 11, 9,  5, 3,  8,  4,  1,  14, 8,  13, 6,  2,
				11, 15, 12, 9, 7,  3,  10, 5,  0,  15, 12, 8,  2,
				4,  9,  1,  7, 5,  11, 3,  14, 10, 0,  6,  13 },

				{ 15, 1,  8,  14, 6,  11, 3, 4,  9,  7,  2,  13, 12,
						0,  5,  10, 3,  13, 4,  7, 15, 2,  8,  14, 12, 0,
						1,  10, 6,  9,  11, 5,  0, 14, 7,  11, 10, 4,  13,
						1,  5,  8,  12, 6,  9,  3, 2,  15, 13, 8,  10, 1,
						3,  15, 4,  2,  11, 6,  7, 12, 0,  5,  14, 9 },

						{ 10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12,
								7,  11, 4,  2,  8,  13, 7,  0,  9,  3,  4,
								6,  10, 2,  8,  5,  14, 12, 11, 15, 1,  13,
								6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12,
								5,  10, 14, 7,  1,  10, 13, 0,  6,  9,  8,
								7,  4,  15, 14, 3,  11, 5,  2,  12 },

								{ 7,  13, 14, 3,  0,  6,  9,  10, 1,  2, 8,  5,  11,
										12, 4,  15, 13, 8,  11, 5,  6,  15, 0, 3,  4,  7,
										2,  12, 1,  10, 14, 9,  10, 6,  9,  0, 12, 11, 7,
										13, 15, 1,  3,  14, 5,  2,  8,  4,  3, 15, 0,  6,
										10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14 },

										{ 2,  12, 4, 1,  7,  10, 11, 6, 8,  5,  3,  15, 13,
												0,  14, 9, 14, 11, 2,  12, 4, 7,  13, 1,  5,  0,
												15, 10, 3, 9,  8,  6,  4,  2, 1,  11, 10, 13, 7,
												8,  15, 9, 12, 5,  6,  3,  0, 14, 11, 8,  12, 7,
												1,  14, 2, 13, 6,  15, 0,  9, 10, 4,  5,  3 },

												{ 12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3, 4, 14,
														7,  5,  11, 10, 15, 4,  2,  7,  12, 9,  5, 6, 1,
														13, 14, 0,  11, 3,  8,  9,  14, 15, 5,  2, 8, 12,
														3,  7,  0,  4,  10, 1,  13, 11, 6,  4,  3, 2, 12,
														9,  5,  15, 10, 11, 14, 1,  7,  6,  0,  8, 13 },

														{ 4,  11, 2,  14, 15, 0,  8, 13, 3,  12, 9,  7,  5,
																10, 6,  1,  13, 0,  11, 7, 4,  9,  1,  10, 14, 3,
																5,  12, 2,  15, 8,  6,  1, 4,  11, 13, 12, 3,  7,
																14, 10, 15, 6,  8,  0,  5, 9,  2,  6,  11, 13, 8,
																1,  4,  10, 7,  9,  5,  0, 15, 14, 2,  3,  12 },

																{ 13, 2,  8, 4,  6,  15, 11, 1,  10, 9, 3, 14, 5,
																		0,  12, 7, 1,  15, 13, 8,  10, 3,  7, 4, 12, 5,
																		6,  11, 0, 14, 9,  2,  7,  11, 4,  1, 9, 12, 14,
																		2,  0,  6, 10, 13, 15, 3,  5,  8,  2, 1, 14, 7,
																		4,  10, 8, 13, 15, 12, 9,  0,  3,  5, 6, 11 }};

/* How to use the program */
char* info = "Please write the following to use the program correctly:\n\
MODES:\n\
encrypt for encryption\n\
decrypt for decryption\n\
For Encryption write:\n\
./des [mode] [input_plain_file] [key_hex_file] [output_plain_file]\n\
For Decryption write:\n\
./des [mode] [input_plain_file] [key_hex_file] [output_plain_file]\n";


/* Function to get the current time in seconds */
double time_sec()
{

	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (ts.tv_sec+ts.tv_nsec*1e-9);

}

/* Extract bit i from a variable (0->63) */
uint8 getBit(uint64 var, uint8 i){
	return (var >> (63 - i)) & 0x01;
}

/* Function to permutate input block according to the permutation table */
uint64 permute(uint64 in, uint8 out_size, int table[], uint8 offset){
	uint64 out = 0;
	uint8 i;

	for (i = 0; i < out_size; i++)
	{
		out |= getBit(in, table[i] - 1 + offset); /* The offset is always equal to zero except when doing the expansion permutation*/
		if (i != out_size - 1)
		{
			out <<= 1;
		}
	}

	/* Shift the key bits to the left (1->out_size) (add zeroes to the right) */
	out <<= (64 - out_size);

	return out;
}

/* Left circular shift */
uint64 left_shift(uint64 key, uint8 round){
	uint8 i, temp;
	uint64 shiftedKey = 0;

	/* Shifting the left half of the key */
	temp = getBit(key, 0);
	for (i = 1; i < 28; i++)
	{
		shiftedKey |= getBit(key, i);
		shiftedKey <<= 1;
	}
	shiftedKey |= temp;
	shiftedKey <<= 1;

	/* Shifting the right half bits of the key */
	temp = getBit(key, 28);
	for (i = 29; i < 56; i++)
	{
		shiftedKey |= getBit(key, i);
		shiftedKey <<= 1;
	}
	shiftedKey |= temp;

	/* Shift the key 8 bits to the left (1->56) (add zeroes to the right) */
	shiftedKey <<= 8;

	/* If we are in rounds 1, 2, 9, or 16. Then shift one more time */
	switch(round)
	{
	case 1:
	case 2:
	case 9:
	case 16:
		break;
	default:
		shiftedKey = left_shift(shiftedKey, 1);
		break;
	}

	return shiftedKey;
}

/* S-box code to convert from 48-bit to 32-bit */
uint64 s_box(uint64 input)
{
	uint64 output = 0;
	uint8 number_of_shifts = 28;

	for(uint8 i = 0; i < 8; i++){

		uint8 outer_value = ((input & (1ULL<<63)) >> 62) | ( (input & (1ULL<<58)) >> 58);
		uint8 inner_value = (input & ((0x78ULL) << 56)) >> 59;

		output = output | (s[i][outer_value][inner_value]) << number_of_shifts;
		number_of_shifts -= 4;

		input = input << 6;
	}

	output <<= 32;
	return output;
}

/* Doing one round from the 16 rounds */
uint64 des_round(uint64 inputBlock, uint64 key){
	uint64 outputBlock = 0;
	uint8 i;

	/* Adding the right half of the old cipher to the left of the new one */
	for(i = 32; i < 64; i++)
	{
		outputBlock |= getBit(inputBlock, i);
		outputBlock <<= 1;
	}

	/* Expanding the right half of the old input into 48 bits and XORing it with the subkey */
	key = key ^ permute(inputBlock, 48, E, 32);

	/* Substitute the result using the S-Box and converting it into 32 bit again */
	key = s_box(key);

	/* Permute the result using P table */
	key = permute(key, 32, P, 0);

	/* XORing the result with the left half of the input */
	key = key ^ inputBlock;

	/* Adding the left half XORed with the result to the output */
	for(i = 0; i < 32; i++)
	{
		outputBlock |= getBit(key, i);
		if(i != 31)
		{
			outputBlock <<= 1;
		}
	}

	return outputBlock;
}

/* Encrypt or Decrypt */
uint64 encDec(uint64 input, uint64 *subkey, uint8 *mode){
	uint64 output = 0;
	uint8 round;
	uint8 i;

	/* Passing input block through IP */
	output = permute(input, 64, IP, 0);

	// Permutating the subkeys and doing the DES 16 encryption rounds
	for(round = 0; round < 16; round++)
	{
		/* Encrypt */
		if(strcmp(mode, "encrypt") == 0)
		{
			output = des_round(output, permute(subkey[round], 48, PC2, 0));
		}

		/* Decrypt */
		else if(strcmp(mode, "decrypt") == 0)
		{
			output = des_round(output, permute(subkey[15 - round], 48, PC2, 0));
			/* Error */
		}else
		{
			printf("Error: Invalid mode!\n");
			printf("%s", info);
			exit(0);
		}
	}

	/* 32-bit swap */
	for(i = 0; i < 32; i++)
	{
		uint8 temp = getBit(output, 0);
		output <<= 1;
		output |= temp;
	}

	/* Inverse initial permutation */
	output = permute(output, 64, FP, 0);

	return output;
}

/* Encrypt or Decrypt according to the mode selected*/
void des(char *mode, char *inputfile, char *keyFilePath, char *outputPlainFilePath){
	FILE *inputFile, *keyFile, *outputPlainFile;
	uint8 i = 0;
	uint64 inputBlock = 0, outputBlock = 0, keyBlock = 0, subkey[16];
	uint8 noOfShifts;
	uint64 mask;

	/* Open input file */
	inputFile = fopen(inputfile, "r");
	if(inputFile == NULL)
	{
		printf("Error: Couldn't open the input file '%s'!\n", inputfile);
		printf("%s", info);
		exit(0);
	}

	/* Open key file */
	keyFile = fopen(keyFilePath, "r");
	if(keyFile == NULL)
	{
		printf("Error: Couldn't open the key file '%s'!\n", keyFilePath);
		printf("%s", info);
		exit(0);
	}

	/* Open output Plain Text file */
	outputPlainFile = fopen(outputPlainFilePath, "w");
	if(outputPlainFile == NULL)
	{
		printf("Error: Could't open the output file '%s'!\n", outputPlainFilePath);
		printf("%s", info);
		exit(0);
	}

	uint8 key_size = 0;
	char c = fgetc(keyFile);
	/* Read 8 bytes from the key file and change from string to HEX format */
	while(c != EOF)
	{
		for(i = 0; i < 16; i++)
		{
			switch(c)
			{
			case '0':
				keyBlock |= 0b0000;
				key_size++;
				break;
			case '1':
				keyBlock |= 0b0001;
				key_size++;
				break;
			case '2':
				keyBlock |= 0b0010;
				key_size++;
				break;
			case '3':
				keyBlock |= 0b0011;
				key_size++;
				break;
			case '4':
				keyBlock |= 0b0100;
				key_size++;
				break;
			case '5':
				keyBlock |= 0b0101;
				key_size++;
				break;
			case '6':
				keyBlock |= 0b0110;
				key_size++;
				break;
			case '7':
				keyBlock |= 0b0111;
				key_size++;
				break;
			case '8':
				keyBlock |= 0b1000;
				key_size++;
				break;
			case '9':
				keyBlock |= 0b1001;
				key_size++;
				break;
			case 'A': case 'a':
				keyBlock |= 0b1010;
				key_size++;
				break;
			case 'B': case 'b':
				keyBlock |= 0b1011;
				key_size++;
				break;
			case 'C': case 'c':
				keyBlock |= 0b1100;
				key_size++;
				break;
			case 'D': case 'd':
				keyBlock |= 0b1101;
				key_size++;
				break;
			case 'E': case 'e':
				keyBlock |= 0b1110;
				key_size++;
				break;
			case 'F': case 'f':
				keyBlock |= 0b1111;
				key_size++;
				break;
			default:
				break;
			}
			if(i < 15)
			{
				keyBlock <<= 4;
				c = fgetc(keyFile);
			}
		}
		c = fgetc(keyFile);
		if((key_size == 16) && (c == '\n'))
		{
			break;
		}
	}
	
	/* Check that the key is 64-bit */
	if(key_size != 16)
	{
		printf("Key size is not equal to 64-bit!");
		exit(0);
	}

	/* Permutate the key by converting it from 64-bit to 56-bit through PC-1*/
	uint64 effectiveKey = permute(keyBlock, 56, PC1, 0);

	/* Generating the subkeys */
	subkey[0] = left_shift(effectiveKey, 1);
	for (i = 1; i <= 15; i++)
	{
		subkey[i] = left_shift(subkey[i - 1], i + 1);
	}

	/* Read all of the data inside the input file and allocate it in heap */
	fseek(inputFile, 0L, SEEK_END);
	uint64 databytes = ftell(inputFile);
	fseek(inputFile, 0L, SEEK_SET);

	uint8 *data = (uint8*)calloc(databytes, sizeof(char));

	fread(data, sizeof(char), databytes, inputFile);

	uint64 numberOfBytesRemaining = databytes;

	noOfShifts = 56;
	mask = 0xFF00000000000000;
	
	/* Read 8 bytes from the input plain file */
	while(numberOfBytesRemaining != 0)
	{
		inputBlock = 0;
		for(i = 0; i < 8; i++)
		{
			if(numberOfBytesRemaining > 0){
				uint8 test = *data;
				inputBlock |= test;
			}

			if(i < 7)
			{
				inputBlock <<= 8;
			}

			data++;
			if(numberOfBytesRemaining > 0){
				numberOfBytesRemaining--;
			}

		}

		/* Encrypt/Decrypt the input block */
		outputBlock = encDec(inputBlock, subkey, mode);

		/* Print 8 bytes to the output Plain File*/
		noOfShifts = 56;
		mask = 0xFF00000000000000;

		for(i = 0; i < 8; i++){
			fprintf(outputPlainFile,"%c", (uint8)((outputBlock & mask) >> noOfShifts));
			noOfShifts -= 8;
			mask >>= 8;
		}
	}

	/* Closing files */
	fclose(inputFile);
	fclose(keyFile);
	fclose(outputPlainFile);

}

int main(int argc, char* argv[]){

	/* Get the starting time */
	double start_time = time_sec();

	char    *mode;
	char    *inputstream;
	char    *keystream;
	char    *outputPlainstream;

	if(argc == 5)
	{
		mode = argv[1];
		inputstream = argv[2];
		keystream = argv[3];
		outputPlainstream = argv[4];
	}
	else
	{
		printf("Please enter a valid number of arguments!\n");
		printf("%s", info);
		exit(0);
	}
	des(mode, inputstream, keystream, outputPlainstream);

	/* Print the current time - the starting time to get the elapsed time in seconds */
	printf("Done in %f seconds\n", time_sec() - start_time);

	return 0;
}

