#include <stdio.h>
#define MAX_STUDENTS 100
#define NAME_LEN 50

struct student
{
 int id;
 char name[NAME_LEN];
 float marks;   
};

int add_student(struct student *list, int *count)
{

    if (*count == MAX_STUDENTS)
    {
        printf("Student list is full\n");
        return -1;
    }

    printf("Enter id: ");
    if (scanf("%d", &list[*count].id) != 1)
    {
        printf("Invalid id\n");
        return -1;
    }

    printf("Enter name: ");
    if (scanf("%49s", list[*count].name) != 1)
    {
        printf("Invalid name\n");
        return -1;
    }

    printf("Enter marks: ");
    if (scanf("%f", &list[*count].marks) != 1)
    {
        printf("Invalid marks\n");
        return -1;
    }
    *count = *count + 1;

    return 0;
}

void list_students(const struct student *list, int count)
{
    if (count == 0)
    {
        printf("No students found\n");
        return;
    }
    printf("-------------------------------");

    for (int i=0; i<count; i++)
    {
        printf("\nStudent id: %d\n", list[i].id);
        printf("Student id: %s\n", list[i].name);
        printf("Student id: %.2f\n", list[i].marks);
    }
}

int main()
{
    struct student students[MAX_STUDENTS];
    int count = 0;
    int choice = 0;

    printf("Students Record Manager\n");

    while (choice != 3)
    {
        printf("\n1. Add student\n2. List students\n3. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }
        // printf("--------------------------------");

        switch(choice)
        {
            case 1:
                add_student(students, &count);
                break;
            case 2:
                list_students(students, count);
                break;
            case 3:
                printf("Bye\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}