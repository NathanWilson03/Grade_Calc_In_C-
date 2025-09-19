#include <stdio.h>


/* using weight and score only to  the score of 
 * one assignment */
double calc_assign_val(int score, int weight) {

    double weight_percentage = weight / 100.0;
    return score * weight_percentage;
}

/* method to find lowest assignment value 
 * from the weight and score d
 * array, the needed array size and 
 * num of assignments
 */
double drop_lowest_value(double scores[], int array_size, int assign_nums[]) {

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

    /* resizing array by shifting elements from
     * point of min left
     */
    for(i = index_of_min; i < array_size -1; i++){
	    scores[i] = scores[i + 1];
	    assign_nums[i] = assign_nums[i + 1];
    }
    return min_value;
}

/* calculating the numeric score off of all assign scores, corresponding days late, the 
 * constant points off(or late pentalty) and num_assign as the array size */
double calc_numeric_score(int scores[], int days_late[], int points_off, int num_assign){
	int i;
	double total = 0.0;
	for(i = 0; i < num_assign; i++) {
		int adjusted = (double)scores[i] - points_off * days_late[i];

		/* if the score goes negative */
		if( adjusted < 0 ){
			adjusted = 0;
		} else {
			total += adjusted;
		}

	}

	return total / num_assign;
}


int main() {
    /* class information and increment vars */
    int i, num_assign, num_to_drop, late_deduction;  

    double final_score;
    char stats_option;

    /* individual assignment info */ 
    int assign_num, days_late, score, weight, total_weight = 0, total_late = 0;

    scanf("%d %d %c", &late_deduction, &num_to_drop, &stats_option);
    scanf("%d", &num_assign);

    int assign_nums[num_assign], weight_array[num_assign], late_array[num_assign], original_scores[num_assign];
    double numeric_scores[num_assign], dropped_val, average, score_sum = 0.0;

    for (i = 0; i < num_assign; i++) {
        scanf("%d, %d, %d, %d", &assign_num, &score, &weight, &days_late);

        /* total weight needs to be 100 at end */
        total_weight += weight;
        total_late += days_late;

	original_scores[i] = score;
        /*  weighted score */ 
        numeric_scores[i] = calc_assign_val(score, weight);

        /* store individual assignment info */
        assign_nums[i] = assign_num;
        weight_array[i] = weight;
        late_array[i] = days_late;
    }

    /* make sure weights add up */
    if( total_weight == 100 ) {


    /* creating var so num_assign is 
     * not changed in the following method */
    int assign_after_drop = num_assign;

    /* summing numeric scores */
    for(i=0; i< num_assign; i++) {
        score_sum += numeric_scores[i];
    }

    /* before we change the numeric_scores with functions lets copy them 
     * now for the output */
    double output_array[num_assign];
    for(i=0; i < num_assign; i++){
	    output_array[i] = numeric_scores[i];
    }

    /* adjusting sum after dropping the lowest values */ 
    for(i=0; i < num_to_drop; i++) {
	/* don't think I need to keep track of this dropped_val but I am */
	dropped_val = drop_lowest_value(numeric_scores, assign_after_drop, assign_nums);
	/* adjusting the array size */
    	assign_after_drop--;
    }

    /* spent an hour wondering why tf. Now turns out we compute the score not weighted...tf?!*/
    final_score = calc_numeric_score(original_scores, late_array, late_deduction, assign_after_drop);

    printf("Numeric Score: %f\n", final_score);
    printf("Points Penalty Per Day Late: %d\n", late_deduction);
    printf("Number of Assignments Dropped: %d\n", num_to_drop);
    printf("Values Provided:\nAssignment, Score, Weight, Days Late\n");
    for(i = 0; i < num_assign; i++){
	printf("%d, %d, %d, %d\n", assign_nums[i], original_scores[i], weight_array[i], late_array[i]);
    }
  
    /* if weights don't add up */
    } else {
	    printf("ERROR: Invalid values provided");
    }
}
