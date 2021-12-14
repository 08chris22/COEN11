// Christian Garcia COEN 11L Lab 7 Tuesday 2:15PM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE struct node
#define LIST struct list

#define SIZE 10
#define LENGTH 20

struct node
{
        char names[LENGTH];
        int sizes;
        NODE *next;
};

struct list
{
        NODE *head;
        NODE *tail;
};

LIST array[4] = {{NULL, NULL}, {NULL,NULL}, {NULL,NULL}, {NULL,NULL}};

void insert(char *name1, int sizex);
void delete(int sizey);
void list(void);
void fit_in(void);
void changeSize(char *str, int size0, int size1);
void deleteTotal(void);
int duplicate(char *str);
void savefile (char *filename);
void readfile (char *filename);

int main (int argc, char *argv[])
{       
	char name[LENGTH];
        int answer;
	int size, sizey;
	int size0, size1;

	if (argc == 1)
	{
		printf ("No current file.\n");
		return 1;
	}
	
	readfile (argv[1]);

        while (1)
        {       
                printf ("Surf School Waiting List\n Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Search Size\n 5 - Change Size\n 0 - Exit\n");
		scanf ("%d", &answer);

                switch (answer)
                {       
                        case 1: 
				printf ("What is the name for your lesson?\n");
      				scanf ("%s", name);

       				if (duplicate(name) == 1)
       				{
                			printf ("Sorry there is already a lesson with that name. Check back tomorrow.\n");
                			break;
        			}

        			printf ("How many are in your group?\n");
        			scanf ("%d", &size);
                                insert(name, size);
                                break;
                        case 2: 
				printf ("What size?.\n");
        			scanf ("%d", &sizey);
                                delete(sizey);
                                break;
                        case 3: 
                                list();
                                break;
			case 4:
				fit_in();
				break;
			case 5:
				printf ("What is the name of your group?\n");
				scanf ("%s", &name);
				printf ("What is your current group size?\n");
				scanf ("%d", &size0);
				printf ("What is your new group size?\n");
                                scanf ("%d", &size1);
				changeSize(name, size0, size1);
				break;
                        case 0: 
				savefile (argv[1]);
				deleteTotal();
                                return 0;
                        default:
                                printf ("Bad Input!\n");
                }
        
        }

}

void insert (char *name1, int sizex)
{
	NODE *p;
	p = (NODE*)malloc(sizeof(NODE));
	int i;

	p->sizes = sizex;
	strcpy(p->names, name1);

	switch (sizex)
	{
		case 1:
			i = 0;
			break;
		case 2:
			i = 0;
			break;
		case 3:
			i = 1;
			break;
		case 4:
			i = 1;
			break;
		case 5:
			i = 2;
			break;
		case 6:
			i = 2;
			break;
		default:
			i = 3;
			break;
	}

	if (array[i].head == NULL)
	{
		array[i].head = array[i].tail = p;
		p->next = NULL;
	}
	
	else
	{
		array[i].tail->next = p;
		array[i].tail = p;
		p->next = NULL;
	}

        printf ("Your lesson for %s, group of %d is set.\n", name1, sizex);
}

void delete (int sizey)
{
	NODE *p, *q;
	int i, j;

	switch (sizey)
        {
                case 1:
                        i = 0;
                        break;
                case 2:
                        i = 0;
                        break;
                case 3:
                        i = 1;
                        break;
                case 4:
                        i = 1;
                        break;
                case 5:
                        i = 2;
                        break;
                case 6:
                        i = 2;
                        break;
                default:
                        i = 3;
                        break;
        }


	for (j = 0; j <= i; j++)
	{
		p = array[j].head;
		while (p != NULL)
		{
			if (p->sizes <= sizey)
				break;
			q = p;
			p = p->next;
		}

		if (p == NULL)
		{
			printf ("The opening does not fit any group size in the waiting list.\n");
			continue;
		}

		else if (p == array[j].head)
		{
			p = array[j].head;
			array[j].head = p->next;
			printf ("A group was found for the lesson.\n");
			sizey = sizey - p->sizes;
		}

		else if (p == array[j].tail)
		{
			array[j].tail = q;
			q->next = NULL;
			printf ("A group was found for the lesson.\n");
			sizey = sizey - p->sizes;
		}

		else
		{
			q->next = p->next;
			printf ("A group was found for the lesson.\n");
			sizey = sizey - p->sizes;
		}
		free (p);
	
	}
	return;
}

void list (void)
{
	NODE *p;
	int i;

	printf ("1-2 People: \n");
	p = array[0].head;
	if (p == NULL)
                        printf ("There are no lessons with this group size scheduled.\n");
	while (p != NULL)
	{
       		printf ("%s %d\n", p->names, p->sizes);
               	p = p->next;
	}

	printf ("3-4 People: \n");
	p = array[1].head;
	if (p == NULL)
                        printf ("There are no lessons with this group size scheduled.\n");
	while (p != NULL)
	{
                printf ("%s %d\n", p->names, p->sizes);
                p = p->next;
	}
	
	printf ("5-6 People: \n");
        p = array[2].head;
	if (p == NULL)
                        printf ("There are no lessons with this group size scheduled.\n");
	while (p != NULL)
	{
                printf ("%s %d\n", p->names, p->sizes);
                p = p->next;
	}
	
	printf ("6+ People: \n");
        p = array[3].head;
	if (p == NULL)
                        printf ("There are no lessons with this group size scheduled.\n");
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
	p = (NODE*)malloc(sizeof(NODE));
	int i;

	printf ("What group size would you like to search for?\n");
	scanf ("%d", &size);

	for (i = 0; i < 4; i++)
	{
		p = array[i].head;
		while (p != NULL)
		{
			if (p->sizes <= size)
				printf("%s %d\n", p->names, p->sizes);
			p = p->next;
		}
	}
	return;
}

int duplicate (char *str)
{
	NODE *p;
	int i;
	
	for (i = 0; i < 4; i++)
	{
		p = array[i].head;
		while (p != NULL)
		{
			if (strcmp(str, p->names) == 0)
				return 1;
			p = p->next;
		}
	}
	return 0;
}

void deleteTotal (void)
{
	NODE *p, *q;
	int i;

	for (i = 0; i < 4; i++)
	{
		p = array[i].head;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			free (q);
		}
	}
	printf ("Saved.\n");
	return;
}

void changeSize (char str[], int size0, int size1)
{
	NODE *p, *q;
	int i;
	int temp;
	
	while (array[size0].head != NULL)
	{
		if (strcmp(str, p->names) == 0)
		{
			p->sizes = size1;
			p->next = NULL;
			array[size1].tail->next = p;
			array[size1].tail = p;
			return;
		}
		else
		{
			printf("Group not found in list.\n");
			return;
		}
	}
	return;
}

void savefile (char *filename)
{
	FILE *fp;
	NODE *p;
	int i;

	fp = fopen(filename, "w");

	while (fp == NULL)
	{
		printf ("File could not be opened.\n");
		return;
	}
	
	fprintf (fp, "Group Name\tGroup Size\n");
	fprintf (fp, "-------------------------------\n");

	for (i = 0; i < 4; i++)
	{
		p = array[i].head;
		while (p != NULL)
		{
			fprintf (fp, "%s\t%d\n", p -> names, p -> sizes);
			p = p -> next;
		}
	}
	fclose (fp);
}

void readfile (char *filename)
{
	FILE *fp;
	char fileName [20];
	int fileSize;

	fp = fopen(filename, "r");

	while (fp == NULL)
		return;
	
	fseek (fp, 53, SEEK_SET);
	
	while (fscanf (fp, "%s %d", fileName, &fileSize) == 2)
			insert(fileName, fileSize);
	return;
}
