#include <stdio.h>
#include <stdlib.h>

// Create a new file
void createFile(char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        return;
    }
    printf("File created successfully!\n");
    fclose(fp);
}

// View file content
void viewFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("\n--- File Content ---\n");
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    printf("\n--- End ---\n");
    fclose(fp);
}

// Append text to file
void appendFile(char *filename) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("Enter text to add: ");
    char text[500];
    getchar(); // Clear buffer  getchar()
    fgets(text, 500, stdin);    //fgets()
    printf("%s this is your text\n", text);
    fprintf(fp, "%s", text);
    printf("Text added successfully!\n");
    fclose(fp);
}

// Copy file
void copyFile(char *source, char *dest) {
    FILE *src = fopen(source, "r");
    if (src == NULL) {
        printf("Error opening source file!\n");
        return;
    }
    
    FILE *dst = fopen(dest, "a");
    if (dst == NULL) {
        printf("Error creating destination file!\n");
        fclose(src);
        return;
    }
    
    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }
    
    printf("File copied successfully!\n");
    fclose(src);
    fclose(dst);
}


// Delete file
void deleteFile(char *filename) {
    if (remove(filename) == 0) {
        printf("File deleted successfully!\n");
    } else {
        printf("Error deleting file!\n");
    }
}

int main() {
    int choice;
    char filename[100], dest[100];
    
    printf("*** FILE OPERATIONS ***\n");
    
    while (1) {
        printf("\n1. Create File\n");
        printf("2. View File\n");
        printf("3. Append Text\n");
        printf("4. Copy-Paste File\n");
        printf("5. Delete File\n");
        printf("0. Exit\n");
        
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            printf("Goodbye!\n");
            break;
        }
        
        switch (choice) {
            case 1:
                printf("Enter filename: ");
                scanf("%s", filename);
                createFile(filename);
                break;
                
            case 2:
                printf("Enter filename: ");
                scanf("%s", filename);
                viewFile(filename);
                break;
                
            case 3:
                printf("Enter filename: ");
                scanf("%s", filename);
                appendFile(filename);
                break;
                
            case 4:
                printf("Enter source file: ");
                scanf("%s", filename);
                printf("Enter destination file: ");
                scanf("%s", dest);
                copyFile(filename, dest);
                break;
                
            case 5:
                printf("Enter filename: ");
                scanf("%s", filename);
                deleteFile(filename);
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}