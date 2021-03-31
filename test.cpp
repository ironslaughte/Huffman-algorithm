#include "pch.h"
#include "Huffman encoder.h"

Huffman_encoder encoder;
TEST(TestHuffman, initCase) {
	ASSERT_ANY_THROW(encoder.Print_char_codes()); // empty initialization
}

TEST(TestHuffman, AlphabetCase) {
	std::string input_expr = "zz bbb g yyyy q";
	encoder.Parse(input_expr);
	List list_alph = encoder.GetNodes();
	ASSERT_EQ(list_alph[0]->weight, 1); // num of 'g'
	ASSERT_EQ(list_alph[1]->weight, 1); // num of 'q'
	ASSERT_EQ(list_alph[2]->weight, 2); // num of 'z'
	ASSERT_EQ(list_alph[3]->weight, 3); // num of 'b'
	ASSERT_EQ(list_alph[4]->weight, 4); // num of 'y'
	ASSERT_EQ(list_alph[5]->weight, 4); // num of space 
	// Approximately in this order are the characters in the nodes (sorting is done by the number of occurrences, not by characters)
}
