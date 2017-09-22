//
//  person.h
//  6010ClassDemo2
//
//  Created by Sunil Timalsina on 9/8/17.
//  Copyright © 2017 Learning. All rights reserved.
//

#ifndef person_h
#define person_h
#define MAX_NAME_LEN 50

typedef int aga_Type;

typedef struct Person {
    char name[MAX_NAME_LEN];
    int age;
} Person;

//function prototypes
Person* newPerson()


#endif /* person_h */
