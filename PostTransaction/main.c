#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 6

struct package
{
    char* id;
    int weight;
};

typedef struct package package;

struct post_office
{
    int min_weight;
    int max_weight;
    package* packages;
    int packages_count;
};

typedef struct post_office post_office;

struct town
{
    char* name;
    post_office* offices;
    int offices_count;
};

typedef struct town town;


int my_strcmp(char* a, char *b){
  while(*a && (*a == *b)){
    a++;
    b++;
  }
  return (unsigned char)*a - (unsigned char)*b;
}

void print_all_packages(town t) {
  printf("%s:\n", t.name);
  // go through all the post offices
  for (int i = 0; i < t.offices_count; i++)
  {
    printf("\t%d:\n", i);
    // go through all the packages
    for (int j = 0; j < (t.offices + i)->packages_count; j++)
    {
      printf("\t\t%s\n", t.offices[i].packages[j].id);
    }
  }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
  // go through all the packages from the source town
  post_office *src_post_office = &source->offices[source_office_index];
  post_office *tar_post_office = &target->offices[target_office_index];

  int count = 0;
  for (int i = 0; i < src_post_office->packages_count; i++)
  {
    // check if the package ith meets the conditions of the target offices
    if((src_post_office->packages[i].weight >= tar_post_office->min_weight) && (src_post_office->packages[i].weight <= tar_post_office->max_weight)){
      // increase the packages count of the target by one
      tar_post_office->packages = (package *)realloc(tar_post_office->packages, sizeof(package) * (tar_post_office->packages_count + 1));

      // update the packages count by one
      tar_post_office->packages_count++;

      // copy the content of the package ith to the last position of the target
      tar_post_office->packages[tar_post_office->packages_count- 1] = src_post_office->packages[i];

      count++;

    }else {
        // Shift the package to the left if it doesn't meet the criteria
        src_post_office->packages[i - count] = src_post_office->packages[i];
    }
  }
  // update the packages count of the src
  src_post_office->packages_count -= count;
  src_post_office->packages = (package *)realloc(src_post_office->packages, 
        sizeof(package) * src_post_office->packages_count);
}

town town_with_most_packages(town* towns, int towns_count) {

  int max = 0;
  int temp1 = 0;
  town temp = towns[0];
  for (int j = 0; j < towns[0].offices_count; j++){
      max += towns[0].offices[j].packages_count;
  }
  for (int i = 1; i < towns_count; i++)
  {
    temp1 = 0;
    for (int j = 0; j < towns[i].offices_count; j++)
    {
      temp1 += towns[i].offices[j].packages_count;
    }
    if(max < temp1){
      max = temp1;
      temp = towns[i];
    }
  }
  return temp;
}

town* find_town(town* towns, int towns_count, char* name) {
  for (int i = 0; i < towns_count; i ++){
     if(my_strcmp(towns[i].name, name) == 0){
      // do something
      return &towns[i];
     }
  }
  return NULL;
}

int main()
{
    int towns_count;
    scanf("%d", &towns_count);
    town* towns = malloc(sizeof(town)*towns_count);
    for (int i = 0; i < towns_count; i++) {
        towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
        for (int j = 0; j < towns[i].offices_count; j++) {
            scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
            for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }
    int queries;
    scanf("%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--) {
        int type;
        scanf("%d", &type);
        switch (type) {
        case 1:
            scanf("%s", town_name);
            town* t = find_town(towns, towns_count, town_name);
            print_all_packages(*t);
            break;
        case 2:
            scanf("%s", town_name);
            town* source = find_town(towns, towns_count, town_name);
            int source_index;
            scanf("%d", &source_index);
            scanf("%s", town_name);
            town* target = find_town(towns, towns_count, town_name);
            int target_index;
            scanf("%d", &target_index);
            send_all_acceptable_packages(source, source_index, target, target_index);
            break;
        case 3:
            printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
            break;
        }
    }
    return 0;
}