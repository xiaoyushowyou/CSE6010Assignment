//
//  main.c
//  6010ClassDemo2
//
//  Created by Sunil Timalsina on 9/8/17.
//  Copyright © 2017 Learning. All rights reserved.
//





#include <stdio.h>
#include <string.h>





Person* newPerson(char name[],int ages) {
    if (name == NULL) {
        return NULL;}
    
    Person *p = malloc(sizeof(Person));
    setName(p, name);
    setAge(p, age);
    return p;

}

void deletePerson (Person *p) {



}





void setAge(struct Person *p,int age) {
    if (p == NULL) {
        return;}
    }

    if (age < 0 || age = 150) {
        printf("invalid");}

    p->age = age;
}


void setName(struct Person *p, char name[]) {
    if (p == NULL) {
        return;}
    
    strncpy(p->name,name,MAX_NAME_LEN)
}

void whoAmI(struct Person *p) {
    if (p == NULL) {
        return;}
    
    printf("I am %s, my age is %d. \n", p->name, p->age); //(*p).name

    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    
    //Person declare
    char name[MAX_NAME_LEN] = "Jo";
    
    int age = 25;
    struct Person p;
    
    strncpy(p.name,name,MAX_NAME_LEN);
    
    p.age = age;
    
    whoAmI(&p);
    
    return 0;
}
