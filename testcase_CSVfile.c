#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read a CSV file and store data in a 2D array
void read_csv(char *filename, char ***data, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    // Count the number of rows and columns
    int row_count = 0;
    int col_count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        row_count++;
        char *token = strtok(line, ",");
        while (token) {
            col_count = (col_count > 0) ? col_count : 1;
            token = strtok(NULL, ",");
        }
    }
    rewind(file);

    // Allocate memory for the 2D array
    *data = (char **)malloc(row_count * sizeof(char *));
    for (int i = 0; i < row_count; i++) {
        (*data)[i] = (char *)malloc(col_count * sizeof(char *));
    }

    // Read the data into the 2D array
    int row = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        int col = 0;
        while (token) {
            strcpy((*data)[row][col], token);
            token = strtok(NULL, ",");
            col++;
        }
        row++;
    }

    fclose(file);
    *rows = row_count;
    *cols = col_count;
}

// Test case 1: Check if the file exists
void test_file_exists() {
    assert(access("book_data.csv", F_OK) == 0);
    printf("Test case 1 passed: File exists\n");
}

// Test case 2: Check if the file has the correct number of rows
void test_row_count() {
    int rows, cols;
    char ***data;
    read_csv("book_data.csv", &data, &rows, &cols);
    assert(rows == 10); // Assuming 10 rows in the file
    printf("Test case 2 passed: Row count is correct\n");
}

// Test case 3: Check if the file has the correct number of columns
void test_col_count() {
    int rows, cols;
    char ***data;
    read_csv("book_data.csv", &data, &rows, &cols);
    assert(cols == 6); // Assuming 6 columns in the file
    printf("Test case 3 passed: Column count is correct\n");
}

// Test case 4: Check if the data in the file is correct
void test_data() {
    int rows, cols;
    char ***data;
    read_csv("book_data.csv", &data, &rows, &cols);
    // Check the data in each cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Assuming the data is correct
            assert(strcmp((*data)[i][j], "expected_value") == 0);
        }
    }
    printf("Test case 4 passed: Data is correct\n");
}

int main() {
    test_file_exists();
    test_row_count();
    test_col_count();
    test_data();
    return 0;
}