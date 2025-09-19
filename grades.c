#include <stdio.h>
/* assign info has calculated
 * value and assignment number
 */
#define assign_info 4

double calculate_assign_val(int score, int weight) {

    double weight_percentage = weight / 100.0;
    return score * weight_percentage;
}

/* method to find lowest assignment value 
 * from the weight and score calculated
 * array, the needed array size and 
 * num of assignments
 */
double find_lowest_value(double scores[], int array_size, int assign_nums[]) {

    int i;
    double min_value = 100;
    int index_of_min = 0;

    for (i = 0; i < array_size; i++) {
        /* getting the min value  */ 
        if (scores[i] < min_value) {
            min_value = scores[i];
            index_of_min = i;
        } 
        /* if they are equal */ 
        else if (scores[i] == min_value) {
            /* compare the associated num with the assign num at the index of the min */
            if (assign_nums[i] < assign_nums[index_of_min]) {
                /* if it is less then its new min */ 
                min_value = scores[i];
                index_of_min = i;
            }
        }
    }
    return min_value;
}

int main() {
    /* class information and increment vars */
    int i, num_assign, num_to_drop, late_deduction;
    char stats_option;

    /* individual assignment info */ 
    int assign_num, days_late, score, weight, total_weight = 0, total_late = 0;

    scanf("%d %d %c", &late_deduction, &num_to_drop, &stats_option);
    scanf("%d", &num_assign);

    int assign_nums[num_assign], weight_array[num_assign], late_array[num_assign];
    double numeric_scores[num_assign], dropped_value;

    for (i = 0; i < num_assign; i++) {
        scanf("%d, %d, %d, %d", &assign_num, &score, &weight, &days_late);

        /* total weight needs to be 100 at end */
        total_weight += weight;
        total_late += days_late;

        /* calculate weighted score */ 
        numeric_scores[i] = calculate_assign_val(score, weight);

        /* store individual assignment info */
        assign_nums[i] = assign_num;
        weight_array[i] = weight;
        late_array[i] = days_late;
    }

    dropped_value = find_lowest_value(numeric_scores, num_assign, assign_nums);

    printf("the lowest value is: %f\n", dropped_value); 
}
