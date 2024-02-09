#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
};

struct TreeNode {
    struct Student data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createStudentNode(int id, const char* name) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data.id = id;
    strncpy(newNode->data.name, name, sizeof(newNode->data.name));
    newNode->data.name[sizeof(newNode->data.name) - 1] = '\0'; 
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* root, int id, const char* name) {
    
    if (root == NULL) {
        return createStudentNode(id, name);
    }

    
    if (id < root->data.id) {
        root->left = insert(root->left, id, name);
    } else if (id > root->data.id) {
        root->right = insert(root->right, id, name);
    }

    // return the (unchanged) node pointer
    return root;
}

struct TreeNode* findMin(struct TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}


struct TreeNode* deleteStudent(struct TreeNode* root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->data.id) {
        root->left = deleteStudent(root->left, id);
    } else if (id > root->data.id) {
        root->right = deleteStudent(root->right, id);
    } else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteStudent(root->right, temp->data.id);
    }

    return root;
}


// Function to find a student by ID in the binary search tree
struct TreeNode* findStudent(struct TreeNode* root, int id) {
    if (root == NULL || root->data.id == id) {
        return root;
    }

    if (id < root->data.id) {
        return findStudent(root->left, id);
    }

    return findStudent(root->right, id);
}

// Function to find a student by name in the binary search tree
struct TreeNode* findStudentByName(struct TreeNode* root, const char* name) {
    if (root == NULL) {
        return NULL;
    }

    int compareResult = strcmp(name, root->data.name);
    if (compareResult == 0) {
        return root; 
    } else if (compareResult < 0) {
        return findStudentByName(root->left, name);
    } else {
        return findStudentByName(root->right, name);
    }
}

// Function to change the name of a student by ID
int changeStudentName(struct TreeNode* root, int id, const char* newName) {
    struct TreeNode* studentNode = findStudent(root, id);
    
    if (studentNode != NULL) {
        
        strncpy(studentNode->data.name, newName, sizeof(studentNode->data.name));
        studentNode->data.name[sizeof(studentNode->data.name) - 1] = '\0'; 
        return 1; 
    } else {
        return 0;
    }
}

void displayStudent(struct Student student) {
    printf("Student ID: %d, Name: %s\n", student.id, student.name);
}



// Function to perform an inorder traversal of the binary search tree
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        displayStudent(root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct TreeNode* root = NULL;
    
    int choice;
    int id, success;
    char name[50], new_name[50];
    struct TreeNode* foundStudent;
    
    do {
        printf("Binary Search Tree Operations:\n");
        printf("1. Insert Student\n");
        printf("2. Find Student by ID\n");
        printf("3. Find Student by Name\n");
        printf("4. Change Student Name\n");
        printf("5. Delete\n");
        printf("6. Display Data\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &id);
                printf("Enter student name: ");
                scanf("%s", name);
                root = insert(root, id, name);
                printf("Student inserted successfully.\n");
                break;

            case 2:
                printf("Enter student ID to find: ");
                scanf("%d", &id);
                foundStudent = findStudent(root, id);
                if (foundStudent != NULL) {
                    printf("Student found by ID:\n");
                    displayStudent(foundStudent->data);
                } else {
                    printf("Student with ID %d not found.\n", id);
                }
                break;

            case 3:
                printf("Enter student name to find: ");
                scanf("%s", name);
                foundStudent = findStudentByName(root, name);
                if (foundStudent != NULL) {
                    printf("Student found by name:\n");
                    displayStudent(foundStudent->data);
                } else {
                    printf("Student with name '%s' not found.\n", name);
                }
                break;

            case 4:
                printf("Enter student ID to change name: ");
                scanf("%d", &id);
                printf("Enter the new name: ");
                scanf("%s", new_name);
                success = changeStudentName(root, id, new_name);
                if (success) {
                    printf("Student name changed successfully:\n");
                    displayStudent(findStudent(root, id)->data);
                } else {
                    printf("Student with ID %d not found.\n", id);
                }
                break;

            
            case 5:
                printf("Enter student ID to delete: ");
                scanf("%d", &id);
                root = deleteStudent(root, id);
                printf("Student with ID %d deleted successfully.\n", id);
            break;
            case 6:
               
                printf("All Students in the binary search tree:\n");
                inorderTraversal(root);
                break;
            case 7:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }while(choice!=8);
} 
