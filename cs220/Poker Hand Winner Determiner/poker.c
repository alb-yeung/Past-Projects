#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "poker.h"

/* Global instances of the two players */
struct player P1, P2;

/* Parse card from a 2 char input */
struct card parse(const char *card)
{
	if (!(*card)) return;
	/* TASK 14: parse input and store in card data structure. */
	struct card c;
	/* Hint: You could use switch statements here */
	switch(*card){
		case '2' :
			c.val = two;
			break;
		case '3' :
			c.val = three;
			break;
		case '4' :
			c.val = four;
			break;
		case '5' :
			c.val = five;
			break;
		case '6' :
			c.val = six;
			break;
		case '7' :
			c.val = seven;
			break;
		case '8' :
			c.val = eight;
			break;
		case '9' :
			c.val = nine;
			break;
		case 'T' :
			c.val = ten;
			break;
		case 'J' :
			c.val = jack;
			break;
		case 'Q' :
			c.val = queen;
			break;
		case 'K' :
			c.val = king;
			break;
		case 'A' :
			c.val = ace;
			break;
	}
	switch (*(card+1)){
		case 'D' :
			c.suit = diamond;
			break;
		case 'C' :
			c.suit = clubs;
			break;
		case 'H' :
			c.suit = hearts;
			break;
		case 'S' :
			c.suit = spades;
			break;
	}
	return c;
}

/* Count the number of occurrences of each card 2 through Ace */
void count_cards(struct player *p)
{	
	struct card *currentCard = &(p->cards);
	int *cards = &(p->card_count);
	int i = 0;
	while (i < 5){
		struct card temp =  currentCard[i];
		cards[temp.val]++;
		i++;
	}
	/* TASK 13:  
	 * Iterate through the cards and increment the counter for each card
	 */
}

int is_flush(struct player *p)
{
	struct card *cards = &(p->cards);
	int i = 1;
	enum Suit s = cards->val;
	while (i < 5){
		if (cards[i].suit != s) return 0;
		i++;
	}
	/* TASK 12:
	 * Hand is flush if suit of all the cards is the same
	 */
	return 1; /* Return 1 if flush */
}

int is_straight(struct player *p)
{
	/* NOTE: By this stage, the vector must be constructed.
	 * 
	 * The hand is a straight, if the cards are sequential.
	 * A2345 as well as TJQKA are both valid straights, and Ace 
	 * assumes the value of 1 or 13, but not both.
	 */
	 int *cards = &(p->card_count);
	 int i = 0;
	 int count = 0;
	 while (i < 13){
	 	if ((count > 0) && (cards[i] == 0)) return 0;
	 	if (count == 5) return 1;
	 	if (cards[i]) count++;
	 	i++;
	 }
	/* TASK 11: Check for regular straights
 	 * Hint: If this is a straight, player's card_count for i, i+1, i+2, i+3 and i+4 should be 1. */
 	if (cards[0] && cards[1] && cards[2] && cards[3] && cards[12]){
 		p->vector = (p->vector) ^ (1 << 12);
 		return 1;
 	}
	/* Check for A2345
	 * TASK 10: If the hand is A2345, reset the bit for highcard Ace in the player's vector to appropriately reflect that the value of A is not 13. 
	 * Hint: 1 << position will generate a bit mask for the position of Ace. Xoring it with the vector will reset the bit.
	 */

	return 0; /* Return 1 if straight */	
}

int is_straight_flush(struct player *p)
{
	/* TASK 9: Detect straight flush. A straight flush is nothing but a straight and a flush */
	if ((is_flush(p) + is_straight(p)) == 2){
		return 1;
	}
	return 0; /* Return 1 if straight flush */
}
		
/* This is the main function that converts the player's hand into weighted unsigned long number. 
It is a 55bit vector as shown below (2 is the LSB and StraightFlush is the MSB) */
/* 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A, 22, 33, 44, 55, 66, 77, 88, 99, TT, JJ, QQ, KK, AA,
222, 333, 444, 555, 666, 777, 888, 999, TTT, JJJ, QQQ, KKK, AAA, Straight, Flush, 2222, 3333, 
4444, 5555, 6666, 7777, 8888, 9999, TTTT, JJJJ, QQQQ, KKKK, AAAA, StraightFlush */
/* The number of occurrences of each number in the hand is first calculated in count_cards. 
Then, depending on the numeber of occurrences, the corresponding bit in the bit-vector is set. 
In order to find the winner, a simple comparison of the bit vectors (i.e., unsigned long integers) will suffice! */
void eval_strength(struct player *p)
{
	unsigned int straight_or_flush_possible;
	unsigned int i;
	straight_or_flush_possible = 1;
	/*
	 * TASK 6: Invoke the function to count the occurrences of each card
	 */
	 count_cards(p);
	/*
	 * TASK 7: Iterate through the card_count array, and set the appropriate bit in the bit vector.
	 * For example, if the hand is JH JS 3C AH 4H, set the 23rd bit to indicate a pair of jacks, and 2nd, 3rd and 13th bit to indicate 3, 4 and A respectively. */
	unsigned int *card_count = &(p->card_count);
	unsigned long *vector = &(p->vector);
	i = 0;
	while (i < 13){
		switch(card_count[i]){
			case 1:
				*vector += (1 << i);
				break;
			case 2:
				*vector += (1 << (i+13));
				straight_or_flush_possible = 0;
				break;
			case 3:
				*vector += (1 << (i+26));
				straight_or_flush_possible = 0;
				break;
			case 4:
				*vector += (1 << (i+41));
				straight_or_flush_possible = 0;
				break;
		}
		i++;
	}

	if (!(straight_or_flush_possible)) return;
	if (is_straight(p)) *vector += (1 << 39);
	if (is_flush(p)) *vector += (1 << 40);
	if (is_straight_flush(p)) *vector = (1 << 55);
	/* TASK 8:
	 * Check if this is a straight, flush or a straight flush, and set the appropriate bit in the vector.
	 */
}

/* Parse each hand in the input file, evaluate the strengths of hands and identify a winner by comparing the weighted vectors */
void compare_hands(FILE *fp)
{
	char p1[5][3];
	char p2[5][3];
	int i;
	FILE *output;
	output = fopen("Output.txt","w+");
	while(fscanf(fp, "%s %s %s %s %s %s %s %s %s %s", 
		&p1[0][0], &p1[1][0], &p1[2][0], &p1[3][0], &p1[4][0], 
		&p2[0][0], &p2[1][0], &p2[2][0], &p2[3][0], &p2[4][0]) == 10) {
		memset(&P1, 0, sizeof(struct player));
		memset(&P2, 0, sizeof(struct player));
		for(i = 0; i < 5; i++) {
			P1.cards[i] = parse(&p1[i][0]);
			P2.cards[i] = parse(&p2[i][0]);
		}
		/* TASK 4: Invoke eval_strength for each player */
		eval_strength(&P1);
		eval_strength(&P2);
		/* TASK 5: Report the winner (e.g., "Player 1 wins") depending on whoever has the higher vector */
		if (P1.vector > P2.vector)
			fprintf(output, "Player 1 wins \n");
		else fprintf(output, "Player 2 wins \n");
	}
	fclose(fp);
	fclose(output);
}

int main(int argc, char *argv[])
{
	FILE *fp;

	if (argc < 2){
		printf("Please supply a input file name\n");
		return;
	}
	if (argc > 2){
		printf("Too many arguments\n");
		return;
	}
	/* TASK 2: Validate command line arguments and try to open the file. Exit on failure. */
	if (fopen(argv[1],"r")){
		fp = fopen(argv[1],"r");
		printf("%s opened\n",argv[1]);
	}else{
		printf("%s is not a valid file. Please supply a valid file name.\n", argv[1]);
		return;
	}
	/* TASK 3: Invoke the compare hands function */
	compare_hands(fp);
	return 0;
}
	
