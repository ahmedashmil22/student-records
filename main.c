#include <stdio.h>
#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATA_FILE "students.txt"

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
    printf("-------------------------------\n");

    for (int i=0; i<count; i++)
    {
        printf("\nStudent id: %d\n", list[i].id);
        printf("Student name: %s\n", list[i].name);
        printf("Student marks: %.2f\n", list[i].marks);
    }
}

int find_student(const struct student *list, int count, int id)
{
    for (int i=0; i<count; i++)
    {
        if (list[i].id == id) return i;
    }
    return -1;
}

int delete_student(struct student *list, int *count, int id)
{
    int idx = find_student(list, *count, id);

    if (idx == -1) return -1;

    for (int i=idx; i<*count-1; i++)
    {
        list[i] = list[i+1];
    }
    *count = *count - 1;
    return 0;
}

int save_students(const char *path, const struct student *list, int count)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        printf("Could not open %s for writing\n", path);
        return -1;
    }

    fprintf(fp, "%d\n", count);

    for (int i=0; i<count; i++)
    {
        fprintf(fp, "%d %s %f\n", list[i].id, list[i].name, list[i].marks);
    }

    fclose(fp);
    return 0;
}

int load_students(const char *path, struct student *list, int *count)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        *count = 0;
        return 0;
    }

    int n;
    if (fscanf(fp, "%d", &n) != 1 || n < 0 || n > MAX_STUDENTS)
    {
        printf("Invalid data file\n");
        fclose(fp);
        *count = 0;
        return -1;
    }

    int loaded = 0;
    for (int i=0; i<n; i++)
    {
        if (fscanf(fp, "%d %49s %f", &list[i].id, list[i].name, &list[i].marks) != 3) break;
        loaded++;
    }
    fclose(fp);
    *count = loaded;
    return 0;
}

int main(void)
{
    struct student students[MAX_STUDENTS];
    int count = 0;
    int choice = 0;

    load_students(DATA_FILE, students, &count);

    printf("Students Record Manager\n");
    printf(" \n");

    while (choice != 5)
    {
        printf(" \n");
        printf("Choices: ");
        printf("\n1. Add student\n2. List students\n3. Search student\n4. Delete student\n5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }

        switch(choice)
        {
            case 1:
                add_student(students, &count);
                break;
            case 2:
                list_students(students, count);
                break;
            case 3:
            {
                int id;
                printf("Enter id: ");
                if (scanf("%d", &id) != 1)
                {
                    printf("Invalid id\n");
                    break;
                }

                int idx = find_student(students, count, id);

                if (idx == -1) printf("Student not in our record\n");
                else 
                {
                    printf("\nName - %s\n", students[idx].name);
                    printf("Marks = %.2f\n", students[idx].marks);
                }
                break;
            }
            case 4:
            {
                int id;
                printf("Enter student's id you want to delete: ");
                if (scanf("%d", &id) != 1)
                {
                    printf("Invalid id\n");
                    break;
                }
                if (delete_student(students, &count, id) == 0)
                {
                    printf("DELETED\n");
                } 
                else printf("Student not in our record\n");
                break;
            }
            case 5:
            printf("Bye\n");
            break;
            default:
            printf("Invalid choice\n");
        }
        save_students(DATA_FILE, students, count);
    }
    return 0;
}