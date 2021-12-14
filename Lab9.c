// Christian Garcia COEN 11L Lab 9 Tuesday 2:15PM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE struct node
#define LIST struct list

#include <pthread.h>
#include <unistd.h>

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

pthread_mutex_t lock;
LIST array[4] = {{NULL, NULL}, {NULL,NULL}, {NULL,NULL}, {NULL,NULL}};

void insert(char *name1, int sizex);
void delete(int sizey);
void list(void);
void fit_in(void);
void deleteTotal(NODE *p);
int duplicate(char *str);
void savefile (char *filename);
void readfile (char *filename);
void backlist (NODE *p);
void backname (NODE *p);
void *autosave (void *arg);
void readautosave (char *filename);

void revword (char *array);

int main (int argc, char *argv[])
{       
	char name[LENGTH];
        int answer;
	int size, sizey;
	int i;
	NODE *p;

	if (argc == 1)
	{
		printf ("No current file.\n");
		readfile ("init");
	}
	
	else
		readfile (argv[1]);

	pthread_t thread;

	if (argc == 3)
		pthread_create (&thread, NULL, autosave, (void *) argv[2]);

	else
		pthread_create (&thread, NULL, autosave, (void *) "temp.bin");
	
	pthread_mutex_init (&lock, NULL);

        while (1)
        {       
                printf ("Surf School Waiting List\n Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 4 - Search Size\n 5 - Show Lessons Backwards\n 6 - Show Names Backwards\n 7 - Read Binary\n 0 - Exit\n");
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
				pthread_mutex_lock (&lock);
                                delete(sizey);
				pthread_mutex_unlock (&lock);
                                break;
                        case 3: 
                                list();
                                break;
			case 4:
				fit_in();
				break;
			case 5:
				printf("Name\tParty Size\n");
				printf("---------------------\n");
				for (i = 4; i >= 0; i--)
				{
					p = array[i].head;
					backlist(p);
				}
				break;
			case 6:
				printf ("Name\n");
				printf ("-------\n");
				for (i = 0; i < 4; i++)
				{
					p = array[i].head;
					backname(p);
				}
				break;
			case 7:
				printf ("Reading Binary\n");
				readautosave (argv[2]);
				break;
                        case 0: 
				if (argc == 1)
				{
					savefile ("init");
					printf ("Success\n");
				}
				else
				{
					savefile (argv[1]);
					printf ("Succes\n");
				}
			
				pthread_mutex_lock (&lock);
				printf ("Gaining\n");
				pthread_cancel (thread);
				printf ("Canceling\n");
				pthread_mutex_unlock (&lock);
				printf ("Success\n");
				savefile (argv[1]);
				printf ("Success\n");

				for (i = 0; i < 4; i++)
				{
					p = array[i].head;
					deleteTotal(p);
				}
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

	if (p == (NODE *) NULL)
	{
		printf ("Error\n");
		return;
	}

	pthread_mutex_lock (&lock);

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

	pthread_mutex_unlock (&lock);

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

void deleteTotal (NODE *p)
{
	if (p == NULL)
	{
		return;
	}

	deleteTotal (p->next);
	free(p);
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

void backlist (NODE *p)
{
	if (p == NULL)
	{
		return;
	}
	
	backlist (p->next);
	
	printf ("%s\t%d\n", p->names, p->sizes);
	return; 
}

void backname (NODE *p)
{
	if (p == NULL)
		return;

	revword (p->names);
	printf("\n");
	backname (p->next);
	return;
}

void revword (char *array)
{
	if (*array == '\0')
		return;
	revword (array + 1);
	printf ("%c", *array);
}

void *autosave (void *arg)
{
	FILE *infp;
	int i;
	NODE *p;

	while (1)
	{
		sleep(15);

		if ((infp = fopen((char *) arg, "wb")) == NULL)
			printf ("Error\n");
		
		else
		{
			pthread_mutex_lock (&lock);
			printf ("\n");
			printf ("Saving\n");
			for (i = 0; i < 4; i++)
			{
				p = array[i].head;
				while (p != NULL)
				{
					fwrite (p, sizeof (NODE), 1, infp);
					p = p -> next;
				}
			}
			printf ("Complete\n");
			printf ("\n");
			pthread_mutex_unlock (&lock);
		}
		fclose (infp);
	}
}

void readautosave (char *fileName)
{
	FILE *infp;
	NODE p;
	
	pthread_mutex_lock (&lock);
	
	infp = fopen (fileName, "rb");

	if (infp == NULL)
	{		
		printf ("Error\n");
		return;
	}
	
	pthread_mutex_unlock (&lock);
	
	printf("Name\tParty Size\n");
	printf("----------------------\n");
	
	while (fread(&p, sizeof(NODE), 1, infp) == 1)
	{
		printf ("%s\t%d\n", p.names, p.sizes);
	}
		
	fclose (infp);
	return;
}
	
