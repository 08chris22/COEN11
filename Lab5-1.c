// Christian Garcia COEN 11L Lab 5 Tuesday 2:15PM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE struct node

#define SIZE 10
#define LENGTH 20

void insert(void);
void delete(void);
void list(void);
void fit_in(void);
int duplicate(char *str);

struct node
{
	char names[LENGTH];
	int sizes;
	NODE *next;
};

NODE *head = NULL;
NODE *tail = NULL;

int main()
{       
        int answer;       
        while (1)
        {       
                printf ("Surf School Waiting List\n Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Search Size\n 0 - Exit\n");
		scanf ("%d", &answer);
                switch (answer)
                {       
                        case 1: 
                                insert();
                                break;
                        case 2: 
                                delete();
                                break;
                        case 3: 
                                list();
                                break;
			case 4:
				fit_in();
				break;
                        case 0: 
                                return 0;
                        default:
                                printf ("Bad Input!\n");
                }
        
        }

}

void insert (void)
{
        char name[LENGTH];
        int size;
	NODE *p;
	p = (NODE*)malloc(sizeof (NODE));

	if (p->sizes > 10)
        {
                printf ("Sorry lessons are full.\n");
                return;
        }

        printf ("What is the name for your lesson?\n");
        scanf ("%s", name);
	if (duplicate(name) == 1)
	{
		printf ("Sorry there is already a lesson with that name. Check back tomorrow.\n");
		return;
	}

        printf ("How many are in your group?\n");
        scanf ("%d", &size);
	p->sizes = size;
	strcpy(p->names, name);
	if (head == NULL)
	{
		p->next = NULL;
		tail = head = p;
		return;
	}
	else
	{
		p->next = NULL;
		tail->next = p;
		tail = p;
		return;
	}
	free(p);
        printf ("Your lesson for %s, group of %d is set.\n", name, size);
}

void delete (void)
{
	int size;
	NODE *p, *q;
	p = q = head;

	if (head == NULL)
	{
		printf ("There are currently no lessons scheduled.\n");
		return;
	}

        printf ("What size?.\n");
        scanf ("%d", &size);

	while (p != NULL)
	{
		if (p->sizes <= size)
		{	
			if (p == NULL)
			{
				printf ("The opening does not fit any group size in the waiting list.\n");
				return;
			}

			if (p == head)
			{
				head = p->next;
				printf ("A group was found for the lesson.\n");
				size = size - p->sizes;
			}

			else if (p == tail)
			{
				tail = q;
				q->next = NULL;
				printf ("A group was found for the lesson.\n");
				size = size - p->sizes;
			}
	
			else
			{
				q->next = p->next;
				printf ("A group was found for the lesson.\n");
				size = size - p->sizes;

			}
			free (p);
		}
		q = p;
        	p = p->next;
	}
}

void list (void)
{
	NODE *p;
	p = head;

	if (head == NULL)
        {
                printf ("There are currently no lessons scheduled.\n");
                return;
        }

	while (p != NULL)
	{
		printf ("%s %d\n", p->names, p->sizes);
		p = p->next;
	}
	return;
}

void fit_in (void)
{
	int size;
	NODE *p;
	p = head;

	if (head == NULL)
        {
                printf ("There are currently no lessons scheduled.\n");
                return;
        }

	printf ("What group size would you like to search for?\n");
	scanf ("%d", &size);

	while (p != NULL)
	{
		if (p->sizes <= size)
			printf("%s %d\n", p->names, p->sizes);
		p = p->next;
	}
	return;
}

int duplicate(char *str)
{
	NODE *p;
	p = head;
	
	while (p != NULL)
	{
		if (strcmp(str, p->names) == 0)
			return 1;
		p = p-> next;
	}
	return 0;
}
