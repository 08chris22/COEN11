//Christian Garcia Lab 2 COEN 11 Tuesday 2:15PM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

void insert(void);
void delete(void);
void list(void);

char names [SIZE][LENGTH];
int sizes[SIZE];
int counter=0;

int main() 
{
	int answer;
	int flag=0;
	int i;

	while (1)
	{
		printf ("Surfing Lesson Scheduler\n Menu\n 1 - Insert\n 2 - Delete\n 3 - List\n 0 - Exit\n");
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
			case 0:
				return 1;
			default:
				printf ("Bad Input!\n");
		}

	}

}

void insert (void)
{	
	char name[LENGTH];
	int size;
	
	if (counter==SIZE)
	{
		printf ("There are no availble slots at the moment.\n");
		return;
	}

	printf ("What is the name for your lesson?\n");        
	scanf ("%s", name); 
	printf ("How many are in your group?\n");
	scanf ("%d", &size); 
	strcpy (names[counter], name); 
	sizes[counter] = size;          
	counter++;
	printf ("Your lesson for %s, group of %d is sscheduled.\n", name, size);
		
}	
		
void delete (void)
{
	int i, j;
	int size;
	int flag=0;
	if (counter==0)
	{
		printf ("There are currently no lessons.\n");
		return;
	}
 		
	printf ("What group size?.\n");       
	scanf ("%d", &size); 

	for (i=0;i<counter;i++) 
	{
		if (size >= sizes[i])
		{
			flag=1;
			printf("%s with a group of %d, is getting into an opening of size %d.\n", names[i], sizes[i], size);
			size -= sizes[i];     
			for (j=i; j<counter; j++)
			{
				strcpy (names[j], names[j+1]);
				sizes[j] = sizes[j+1];
			}
			counter--;
			i--;
		}
	}

	if (flag==0)
		printf("The opening does not fit any group size in the waiting list.\n");
}

void list (void)
{
	int i;
	if (counter==0)
	{
		printf ("There are no lessons at the moment.\n");
		return;
	}

	for (i=0;i<counter;i++)
	{
		printf ("%s %d\n", names[i], sizes[i]);
	}
}
