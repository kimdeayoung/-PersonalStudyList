#include <assert.h>
#include "cyber_spaceship.h"
#include <stdio.h>

#define CAB_LENGTH (50)

void test_1(void);
void test_cab_length_upto_100(void);

int main(void)
{
    char cab[CAB_LENGTH];
    const char* cluster_start_addresses[5];
    size_t cluster_lengths[5];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;
    int time_in_mins;
    const char* cab_start_address = cab;

    cluster_start_addresses[0] = &cab[8];
    cluster_start_addresses[1] = &cab[1];
    cluster_start_addresses[2] = &cab[13];
    cluster_start_addresses[3] = &cab[33];
    cluster_start_addresses[4] = &cab[38];

    cluster_lengths[0] = 10U;
    cluster_lengths[1] = 22U;
    cluster_lengths[2] = 10U;
    cluster_lengths[3] = 13U;
    cluster_lengths[4] = 10U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 15);
    assert(longest_safe_cluster_start_address == cab_start_address + 18);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5);

    assert(time_in_mins == 7);

    test_1();
    test_cab_length_upto_100();
    return 0;
}

void test_1(void) {
    const char cyber_asteroid_belt[30];
    size_t cab_length;
    const char* cluster_start_address[13];
    size_t cluster_lengths[13];
    
    size_t out_longest_safe_area_length = 0;
		size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
		const char* longest_safe_cluster_start_address;
    
    
    cab_length = 30;
    cluster_start_address[0] = &cyber_asteroid_belt[0];
    cluster_start_address[1] = &cyber_asteroid_belt[0];
    cluster_start_address[2] = &cyber_asteroid_belt[0];
    cluster_start_address[3] = &cyber_asteroid_belt[0];
    cluster_start_address[4] = &cyber_asteroid_belt[0];
    cluster_start_address[5] = &cyber_asteroid_belt[0];
    cluster_start_address[6] = &cyber_asteroid_belt[29];
    cluster_start_address[7] = &cyber_asteroid_belt[24];
    cluster_start_address[8] = &cyber_asteroid_belt[22];
    cluster_start_address[9] = &cyber_asteroid_belt[10];
    cluster_start_address[10] = &cyber_asteroid_belt[6];
    cluster_start_address[11] = &cyber_asteroid_belt[1];
    cluster_start_address[12] = &cyber_asteroid_belt[1];
    cluster_lengths[0] = 30;
    cluster_lengths[1] = 26;
    cluster_lengths[2] = 22;
    cluster_lengths[3] = 10;
    cluster_lengths[4] = 6;
    cluster_lengths[5] = 1;
    cluster_lengths[6] = 1;
    cluster_lengths[7] = 6;
    cluster_lengths[8] = 4;
    cluster_lengths[9] = 14;
    cluster_lengths[10] = 17;
    cluster_lengths[11] = 14;
    cluster_lengths[12] = 29;
    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, cab_length, cluster_start_address, cluster_lengths, 13, out_longest_safe_area_length_p);
    assert(longest_safe_cluster_start_address == &cyber_asteroid_belt[15]);
    assert(out_longest_safe_area_length == 8);
    
    cab_length = 30;
    cluster_start_address[0] = &cyber_asteroid_belt[2];
    cluster_start_address[1] = &cyber_asteroid_belt[3];
    cluster_start_address[2] = &cyber_asteroid_belt[10];
    cluster_start_address[3] = &cyber_asteroid_belt[19];
    cluster_start_address[4] = &cyber_asteroid_belt[23];
    cluster_start_address[5] = &cyber_asteroid_belt[24];
    cluster_start_address[6] = &cyber_asteroid_belt[0];
    cluster_start_address[7] = &cyber_asteroid_belt[0];
    cluster_start_address[8] = &cyber_asteroid_belt[25];
    cluster_lengths[0] = 10;
    cluster_lengths[1] = 12;
    cluster_lengths[2] = 7;
    cluster_lengths[3] = 11;
    cluster_lengths[4] = 1;
    cluster_lengths[5] = 1;
    cluster_lengths[6] = 30;
    cluster_lengths[7] = 30;
    cluster_lengths[8] = 5;
    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, cab_length, cluster_start_address, cluster_lengths, 9, out_longest_safe_area_length_p);
    assert(longest_safe_cluster_start_address == &cyber_asteroid_belt[23]);
    assert(out_longest_safe_area_length == 7);
    
    cab_length = 30;
    cluster_start_address[0] = &cyber_asteroid_belt[2];
    cluster_start_address[1] = &cyber_asteroid_belt[3];
    cluster_start_address[2] = &cyber_asteroid_belt[10];
    cluster_start_address[3] = &cyber_asteroid_belt[19];
    cluster_start_address[4] = &cyber_asteroid_belt[22];
    cluster_start_address[5] = &cyber_asteroid_belt[24];
    cluster_start_address[6] = &cyber_asteroid_belt[0];
    cluster_start_address[7] = &cyber_asteroid_belt[0];
    cluster_start_address[8] = &cyber_asteroid_belt[25];
    cluster_start_address[9] = &cyber_asteroid_belt[19];
    cluster_start_address[10] = &cyber_asteroid_belt[21];
    cluster_lengths[0] = 10;
    cluster_lengths[1] = 12;
    cluster_lengths[2] = 9;
    cluster_lengths[3] = 11;
    cluster_lengths[4] = 2;
    cluster_lengths[5] = 1;
    cluster_lengths[6] = 30;
    cluster_lengths[7] = 30;
    cluster_lengths[8] = 4;
    cluster_lengths[9] = 2;
    cluster_lengths[10] = 1;
    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, cab_length, cluster_start_address, cluster_lengths, 11, out_longest_safe_area_length_p);
    
    assert(longest_safe_cluster_start_address == &cyber_asteroid_belt[19]);
    assert(out_longest_safe_area_length == 10);
    
    printf("test_multi_cluster_overlap clear\n\n");
}

void test_cab_length_upto_100(void)
{
    /* 0 cluster */
    {
        const char cyber_asteroid_belt[100];
        int time_in_mins;
        size_t out_longest_safe_area_length = 0;
        size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
        const char* longest_safe_cluster_start_address;
        size_t i;
        longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, 0, NULL, NULL, 0, out_longest_safe_area_length_p);
        assert(longest_safe_cluster_start_address == NULL);
        assert(*out_longest_safe_area_length_p == 0);
        time_in_mins = get_travel_time(cyber_asteroid_belt, 0, NULL, NULL, 0);
        assert(time_in_mins == 0);
        for (i = 1; i <= 100; i++) {
            longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, i, NULL, NULL, 0, out_longest_safe_area_length_p);
            assert(longest_safe_cluster_start_address == cyber_asteroid_belt);
            assert(*out_longest_safe_area_length_p == i);
            time_in_mins = get_travel_time(cyber_asteroid_belt, i, NULL, NULL, 0);
            assert(time_in_mins == (i + 5) / 10); /* check if your double value is like x.4999... < x.5 */
        }
    }
    /* 2 clusters */
    {
        const char cyber_asteroid_belt[100];
        int time_in_mins;
        const char* cluster_start_addresses[2];
        size_t cluster_lengths[2];
        size_t out_longest_safe_area_length = 0;
        size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
        const char* longest_safe_cluster_start_address;
        size_t i;
        cluster_start_addresses[0] = &cyber_asteroid_belt[0];
        cluster_start_addresses[1] = &cyber_asteroid_belt[0];
        for (i = 1; i <= 100; i++) {
            cluster_lengths[0] = i;
            cluster_lengths[1] = i;
            longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, i, cluster_start_addresses, cluster_lengths, 2, out_longest_safe_area_length_p);
            assert(longest_safe_cluster_start_address == cyber_asteroid_belt);
            assert(*out_longest_safe_area_length_p == i);
            time_in_mins = get_travel_time(cyber_asteroid_belt, i, cluster_start_addresses, cluster_lengths, 2);
            assert(time_in_mins == (i + 5) / 10); 
        }
    }
    /* 1 cluster */
    {
        const char cyber_asteroid_belt[100];
        int time_in_mins;
        const char* cluster_start_addresses[1];
        size_t cluster_lengths[1];
        size_t out_longest_safe_area_length = 0;
        size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
        const char* longest_safe_cluster_start_address;
        size_t i;
        cluster_start_addresses[0] = &cyber_asteroid_belt[0];
        for (i = 1; i <= 100; i++) {
            cluster_lengths[0] = i;
            longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, i, cluster_start_addresses, cluster_lengths, 1, out_longest_safe_area_length_p);
            
            assert(*out_longest_safe_area_length_p == 0);
            time_in_mins = get_travel_time(cyber_asteroid_belt, i, cluster_start_addresses, cluster_lengths, 1);
            assert(time_in_mins == (i * 2 + 5) / 10); /* check if your double value is like x.9999... < x+1 */
        }
    }
    printf("test_cab_length_upto_100 clear\n\n");
}

