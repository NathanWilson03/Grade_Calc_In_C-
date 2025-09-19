#include <stdio.h>
/* assign info has calculated
 * value and assignment number
 */

/* to make sure weights add up to 100 */
int check_valid(int num_assign, int weights[]){
	int i, weight_sum = 0;
	for(i = 0; i < num_assign; i++) {
		weight_sum += weights[i];
	}
	/* returns 1 if true */
	return weight_sum == 100;
}


double calculate_assign_val(int score, int weight) {

    double weight_percentage = weight / 100.0;
    return score * weight_percentage;
}

/* method to find lowest assignment value 
 * from the weight and score calculated
 * array, the needed array size and 
 * num of assignments
 */
double drop_lowest_value(double scores[], int array_size, int assign_nums[]) {

    int i;
    double min_value = 100;
    int index_of_min = 0;

    for (i = 0; i <= array_size; i++) {
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

    /* resizing array by shifting elements from
     * point of min left
     */
    for(i = index_of_min; i < array_size -1; i++){
	    scores[i] = scores[i + 1];
	    assign_nums[i] = assign_nums[i + 1];
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
    double numeric_scores[num_assign], dropped_val, average, score_sum = 0.0;

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

    /* make sure weights add up */
    if( check_valid(num_assign, weight_array) == 0 ) {


    /* creating var so num_assign is 
     * not changed in the following method */
    int assign_after_drop = num_assign;

    /* summing numeric scores */
    for(i=0; i< num_assign; i++) {
        score_sum += numeric_scores[i];
    }

    /* adjusting sum after dropping the lowest values */ 
    for(i=0; i < num_to_drop; i++) {
	dropped_val = drop_lowest_value(numeric_scores, assign_after_drop, assign_nums);
    	assign_after_drop--;
	score_sum -= dropped_val;


    }


    average = score_sum / assign_after_drop;

    printf("the lowest value is: %f\n", dropped_val); 

    /* if weights don't add up */
    } else {
	    printf("ERROR: Invalid values provided");
    }
}
