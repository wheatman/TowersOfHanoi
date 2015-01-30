#include <stdio.h>
#include <stdlib.h>

typedef struct stack_s {
	struct stack_s *down;
	int value;
} Stack;

typedef struct head_h {
	struct stack_s *start;
} Head;

void display(Stack* stack);

Stack* Stack_init(int val) {
	Stack *node = malloc(sizeof(*node));
	node->down = NULL;
	node->value = val;
	return node;
}
Head* Head_init() {
	Head *head = malloc(sizeof(*head));
	head->start = NULL;
	return head;
}

void Push(Head* head, int newVal){
	if (head->start){
		Stack* newStack = Stack_init(newVal);
		newStack->down = head->start;
		head->start = newStack;
	} else {
		Stack* newStack = Stack_init(newVal);
		head->start = newStack;
	}
}

int Pop(Head* head){
	int oldTop = head->start->value;
	head->start = head->start->down;
	return oldTop;
}
int Peak(Head* head){
	return head->start->value;
}

void display(Stack* stack){
	printf("%d ", stack->value);
	if (stack->down){
		display(stack->down);
	}
}
int hightStack(Stack* stack){
	if (stack->down){
		return 1+hightStack(stack->down);
	} else {
		return 1;
	}

}
int hight(Head* head){
	if (head->start){return hightStack(head->start);}
	else {return 0;}
}
void displayHead(Head* head){
	display(head->start);
	printf("\n");
}
void displayGame(Head* tower1, Head* tower2, Head* tower3){
	if(tower1->start){displayHead(tower1);}
	else {printf("empty \n");}
	if(tower2->start){displayHead(tower2);}
	else {printf("empty \n");}
	if(tower3->start){displayHead(tower3);}
	else {printf("empty \n");}
} 
void move(int numberToMove, Head* from, Head* buffer, Head* goal, Head* tower1, Head* tower2, Head* tower3){
	//displayGame(tower1, tower2, tower3);
	//printf("\n");
	if (numberToMove == 1){
		Push(goal, Pop(from));
	} else {
		move(numberToMove-1, from, goal, buffer, tower1, tower2, tower3);
		Push(goal, Pop(from));
		move(numberToMove-1, buffer, from, goal, tower1, tower2, tower3);
	}
}
int countMoves(int numberToMove, Head* from, Head* buffer, Head* goal){
		if (numberToMove == 1){
			return 1;
	} else {
		return 1+2*countMoves(numberToMove-1, from, goal, buffer);
	}

}

int main(){
	Head* tower1 = Head_init();
	Head* tower2 = Head_init();
	Head* tower3 = Head_init();
	int TowerSize = 10;
	for (int i = TowerSize-1; i>=0; i--){
		Push(tower1, i);
	}
	printf("%d \n", countMoves(TowerSize, tower1, tower2, tower3));
	// printf("\n");
	// move(TowerSize, tower1, tower2, tower3, tower1, tower2, tower3);
	// displayGame(tower1, tower2, tower3);
	return 0;
}