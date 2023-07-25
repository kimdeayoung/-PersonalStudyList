#include <assert.h>
#include <stdio.h>
#include "parentheses.h"

#define MAX_SIZE (5)

int main(void)
{
	parenthesis_t parentheses[MAX_SIZE];
	ringbuffer_t ringbuffer;
	size_t len;
    size_t loop_index;

	ringbuffer.max_size = MAX_SIZE;
	ringbuffer.parentheses = parentheses;


    len = find_matching_parentheses(&ringbuffer, "(((]{{{<><><>[more}}{}})");
    
    printf("len: %d\n", len);
    printf("start_index: %d\n", ringbuffer.start_index);
    puts("");
    
    for (loop_index = 0; loop_index < MAX_SIZE; ++loop_index) {
        parenthesis_t loop_parentheses = ringbuffer.parentheses[loop_index];
        
        printf("loop_index: %d\n", loop_index);
        printf("opening_index: %d\n", loop_parentheses.opening_index);
        printf("closing_index: %d\n", loop_parentheses.closing_index);
        puts("");
    }


    len = find_matching_parentheses(&ringbuffer, "}{)(][><");

	assert(len == 0);
	assert(ringbuffer.start_index == 0);

	len = find_matching_parentheses(&ringbuffer, "{{{}}}");

	assert(len == 3);
	assert(ringbuffer.start_index == 0);

	assert(parentheses[0].opening_index == 2);
	assert(parentheses[0].closing_index == 3);

	assert(parentheses[1].opening_index == 1);
	assert(parentheses[1].closing_index == 4);

	assert(parentheses[2].opening_index == 0);
	assert(parentheses[2].closing_index == 5);

	len = find_matching_parentheses(&ringbuffer, " {]}[[i]{)))} ]");

	assert(len == 4);
	assert(ringbuffer.start_index == 0);

	assert(parentheses[0].opening_index == 1);
	assert(parentheses[0].closing_index == 3);

	assert(parentheses[1].opening_index == 5);
	assert(parentheses[1].closing_index == 7);

	assert(parentheses[2].opening_index == 8);
	assert(parentheses[2].closing_index == 12);

	assert(parentheses[3].opening_index == 4);
	assert(parentheses[3].closing_index == 14);

	len = find_matching_parentheses(&ringbuffer, "{this}(bracket;[](){[(><>)");

	assert(len == 5);
	assert(ringbuffer.start_index == 0);

	assert(parentheses[0].opening_index == 0);
	assert(parentheses[0].closing_index == 5);

	assert(parentheses[1].opening_index == 15);
	assert(parentheses[1].closing_index == 16);

	assert(parentheses[2].opening_index == 17);
	assert(parentheses[2].closing_index == 18);

	assert(parentheses[3].opening_index == 23);
	assert(parentheses[3].closing_index == 24);

	assert(parentheses[4].opening_index == 21);
	assert(parentheses[4].closing_index == 25);

	len = find_matching_parentheses(&ringbuffer, "(((]{{{<><><>[more}}{}})");

	assert(len == 8);
	assert(ringbuffer.start_index == 3);

	assert(parentheses[0].opening_index == 20);
	assert(parentheses[0].closing_index == 21);

	assert(parentheses[1].opening_index == 4);
	assert(parentheses[1].closing_index == 22);

	assert(parentheses[2].opening_index == 2);
	assert(parentheses[2].closing_index == 23);

	assert(parentheses[3].opening_index == 6);
	assert(parentheses[3].closing_index == 18);

	assert(parentheses[4].opening_index == 5);
	assert(parentheses[4].closing_index == 19);

puts("test end");
	return 0;
}
