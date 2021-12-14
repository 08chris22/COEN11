//Christian Garcia Lab 4 COEN 11L 2:15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define LENGTH 20

void insert(void);
void delete(void);
void list(void);
void fit_in(void);
int duplicate(char*);

typedef union extra
{
	char phone[10];
	int age;
	float avg;
}EXTRA;

typedef struct entry
{
	char names[LENGTH];
	int sizes;
	int occasion;
	EXTRA extra_info;
}ENTRY;

ENTRY group[SIZE];
int counter=0;

int main()
{       
        int answer;
        int flag=0;
        int i;
        
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
	ENTRY *p = group;
        char name[LENGTH];
	int i;
        int size;
	int flag=0;
	int answer;

        if (counter==SIZE)
        {
                printf ("There are no availble slots at the moment.\n");
                return;
        }

        printf ("What is the name for your lesson?\n");
        scanf ("%s", name);
	for (i=0;i<counter;i++)
	{
		if (strcmp(name,group[i].names)==0)
		{
			printf ("There is already a lesson under that name.\n");
			return;
			i=counter;
		}
	}
        printf ("How many are in your group?\n");
       	scanf ("%d", &size); 
	printf ("What is the max age?\n");
	scanf ("%d", &answer);
		if (answer < 18)
		{
			printf ("What is an emergency contact phone number?\n");
			scanf ("%s", group[counter].extra_info.phone);
		}
			
		if (answer > 65)
		{
			printf ("What is the age of the youngest in the group?\n");
			scanf ("%d", &group[counter].extra_info.age);
		}
	
		if (answer >= 18 && answer <= 65)
		{
			printf ("What is the average age of the group?\n");
			scanf ("%f", &group[counter].extra_info.avg);
		}

       	strcpy (group[counter].names, name);
       	group[counter].sizes = size; 
	group[counter].occasion = answer;
       	counter++;
       	printf ("Your lesson for %s, group of %d is set.\n", name, size);
}

void delete (void)
{
	ENTRY *p=group;
	int i,j;
        int size;
        int flag=0;
        if (counter==0)
        {
                printf ("There are currently no lessons.\n");
                return;
        }

        printf ("What size?.\n");
        scanf ("%d", &size); 

        for (i=0;i<counter;i++)
        {
                if (size >= group[i].sizes)
                {
                        flag=1;
                        printf("%s with a party of %d, is getting into an opening of size %d.\n", group[i].names, group[i].sizes, size);
                        size -= group[i].sizes;
                        for (j=i; j<counter; j++)
                        {
                                strcpy (group[j].names, group[j+1].names);
                                group[j].sizes = group[j+1].sizes;
				strcpy (group[j].extra_info.phone, group[j+1].extra_info.phone);
				group[j].occasion = group[j+1].occasion;
				group[j].extra_info.age = group[j+1].extra_info.age;
				group[j].extra_info.avg = group[j+1].extra_info.avg;
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
	ENTRY *p=group;
	int i;

        if (counter==0)
        {
                printf ("There are no lessons scheduled at the moment.\n");
                return;
        }

        for (i=0;i<counter;i++)
        {
		if (group[i].occasion < 18)
		{
			printf ("%s Group Size - %d Max Age - %d Emergency Contact -  %s\n", group[i].names, group[i].sizes, group[i].occasion, group[i].extra_info.phone);
		}
		if (group[i].occasion > 65)
		{
			printf ("%s Group Size - %d Max Age - %d Min Age - %d\n", group[i].names, group[i].sizes, group[i].occasion, group[i].extra_info.age);
		}
		if (group[i].occasion >= 18 && group[i].occasion <= 65)
		{
			printf ("%s Group Size - %d Max Age - %d Avg Age - %f\n", group[i].names, group[i].sizes, group[i].occasion, group[i].extra_info.avg);
		}
        }
}

void fit_in (void)
{
	ENTRY *p=group;
	int i;
	int size;
	int flag=0;

	if (counter==0)
	{
		printf ("There are currently no lessons.\n");
		return;
	}

	printf ("What group size would you like to search for?\n");
	scanf ("%d", &size);

	for (i=0;i<counter;i++)
	{
		if (size >= group[i].sizes)
		{
			flag=1;
			printf("%s , %d\n", group[i].names, group[i].sizes);
		}
	}
	if (flag==0)
		printf("There are no lessons that match those conditions.\n");
}
