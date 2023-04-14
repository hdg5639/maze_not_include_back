#include <stdio.h>
#include <stdlib.h>
#define MAZE_SIZE 12
#define WAY 100
int back_count = 0, counter = 0;
typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element data[MAZE_SIZE];
	int top;
} StackType;

typedef struct {
	element data[WAY];
	int top;
}WayPath;

void init_path(WayPath* w) {
	w->top = -1;
}

void init_stack(StackType* s)
{
	s->top = -1;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (MAZE_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

void Wpush(WayPath* w, element item) {
	w->data[++(w->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element Wpop(WayPath* s) {
	return s->data[(s->top)--];
}


element here = { 1,0 }, entry = { 1,0 }, memory = { 0, 0 }, delete = {0 ,0};

char maze[MAZE_SIZE][MAZE_SIZE] = {
		{'1','1','1','1','1','1','1','1','1','1'},
		{'e','1','0','1','0','0','0','1','0','1'},
		{'0','0','0','1','0','0','0','1','0','1'},
		{'0','1','0','0','0','1','1','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','0','0','1','0','1','1'},
		{'1','0','1','1','1','0','1','1','0','1'},
		{'1','1','0','0','0','0','0','0','0','x'},
		{'1','1','1','1','1','1','1','1','1','1'}
};

void push_loc(StackType* s, int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
	else {
		counter++;
	}
}

void Wpush_loc(WayPath* w, int r, int c) {
	if (r < 0 || c < 0) return;
	element tmp;
	tmp.r = r;
	tmp.c = c;
	Wpush(w, tmp);
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c ", maze[r][c]);
		}
		printf("\n");
	}
	printf("-------------------");
}


int main() {
	int r, c;
	StackType s;
	WayPath w;
	init_stack(&s);
	init_path(&w);
	WayPath M;
	init_path(&M);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		Wpush(&w, here);
		maze[r][c] = '.';
		printf("\n%d, %d\n", here.r, here.c);
		maze_print(maze);
		counter = 0;
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		if (counter < 3) {
			Wpush_loc(&M, r, c);
		}
		if (counter == 4) {
			back_count++;
			memory = Wpop(&M);
			while ((delete.r != memory.r) && (delete.c != memory.c)) {
				delete = Wpop(&w);
			}
		}
		if (is_empty(&s)) {
			printf("\nFail!\n");
			printf("Back count: %d\n", back_count);
			return;
		}
		else 
			here = pop(&s);
	}
	printf("\nSuccess!\n");
	printf("Back count: %d\n", back_count);
	printf("\nThe path is:\n");
	for (int i = 0; i <= w.top; i++) {
		printf("(%d,%d)->", w.data[i].r, w.data[i].c);
	}
	printf("(x,x)\n");
	system("pause");
	exit(1);
	return 0;
}