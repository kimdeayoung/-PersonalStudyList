#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    size_t cab_loop_length;
    const char* check_location;

    size_t cluster_check_loop_length;
    unsigned int searched_cluster_count;

    const char* start_point;
    unsigned int safe_area_length = 0;

    const char* out_longest_safe_area_location;

    *out_longest_safe_area_length = 0;
    if (cab_length == 0) {
        return NULL;
    } else if (cluster_count == 0) {
        *out_longest_safe_area_length = cab_length;
        return cab_start_location;
    }

    for (cab_loop_length = 0; cab_loop_length < cab_length; ++cab_loop_length) {
        check_location = cab_start_location + cab_loop_length;
        searched_cluster_count = 0;

        for (cluster_check_loop_length = 0; cluster_check_loop_length < cluster_count; ++cluster_check_loop_length) {
            if (cluster_start_locations[cluster_check_loop_length] <= check_location && cluster_start_locations[cluster_check_loop_length] + cluster_lengths[cluster_check_loop_length] > check_location) {
                ++searched_cluster_count;
            }
        }

        if (searched_cluster_count % 2 == 0) {
            if (safe_area_length++ == 0) {
                start_point = check_location;
            }
        } else {
            if (*out_longest_safe_area_length <= safe_area_length) {
                out_longest_safe_area_location = start_point;
                *out_longest_safe_area_length = safe_area_length;
            }
            safe_area_length = 0;
        }
    }

    if (*out_longest_safe_area_length <= safe_area_length) {
        out_longest_safe_area_location = start_point;
        *out_longest_safe_area_length = safe_area_length;
    }

    return out_longest_safe_area_location;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    size_t cab_loop_length;
    const char* check_location;

    size_t cluster_check_loop_length;
    unsigned int searched_cluster_count;

    int is_not_safe_area = 0;
    unsigned int area_length = 0;

    int safe_area_value = 0;
    int unsafe_area_value = 0;

    double travel_time;
    int result_value;

    double cal_result1;
    double cal_result2;
    
    if (cab_length == 0) {
        return 0;
    } else if (cluster_count == 0) {
        travel_time = (double)cab_length / 10.0;
        goto cal_result;
    }

    for (cab_loop_length = 0; cab_loop_length < cab_length; ++cab_loop_length) {
        check_location = cab_start_location + cab_loop_length;
        searched_cluster_count = 0;

        for (cluster_check_loop_length = 0; cluster_check_loop_length < cluster_count; ++cluster_check_loop_length) {
            if (cluster_start_locations[cluster_check_loop_length] <= check_location && cluster_start_locations[cluster_check_loop_length] + cluster_lengths[cluster_check_loop_length] > check_location) {
                ++searched_cluster_count;
            }
        }

        if (searched_cluster_count % 2 != is_not_safe_area) {
            if (area_length > 0) {
                if (is_not_safe_area == 0) {
                    safe_area_value += area_length;
                } else {
                    unsafe_area_value += area_length;
                }
            }
            area_length = 0;
            if (is_not_safe_area == 0) {
                is_not_safe_area = 1;
            } else {
                is_not_safe_area = 0;
            }
        }
        ++area_length;
    }

    if (area_length > 0) {
        if (is_not_safe_area == 0) {
            safe_area_value += area_length;
        } else {
            unsafe_area_value += area_length;
        }
    }
    travel_time = ((double)safe_area_value) / 10.0 + ((double)unsafe_area_value) / 5.0;
cal_result:
    result_value = (int)travel_time;

    cal_result1 = (double)result_value;
    cal_result2 = (double)(result_value + 1);
    if (travel_time - cal_result1 >= cal_result2 - travel_time) {
        result_value += 1;
    }
    return result_value;
}
