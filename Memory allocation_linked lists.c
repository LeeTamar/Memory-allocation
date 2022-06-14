//Author : Lee Tamar Zano, ID : 313612608
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// structures
typedef struct student {
	char *name;
	int  id;
	struct clist *courses;
} student;

typedef struct course {
	char *title;
	int  number;
	struct slist *students;
} course;

typedef struct slist {
	student      *info;
	struct slist *next;
} slist;

typedef struct clist {
	course       *info;
	struct clist *next;
} clist;


// prototypes
slist* add_student(slist *students, char *name, int id);
clist* add_course(clist *courses, char *title, int number);
void reg_student(slist *students, clist *courses, int id, int number);
void unreg_student(slist *students, int id, int number);
void print_students(slist *students);
void print_courses(clist *courses);
void free_all(slist *sl, clist *cl);
slist* add_std_to_sorted_slist(slist* students, slist* newstd);
clist* add_course_to_sorted_clist(clist* courses, clist* newcourse);


slist* add_std_to_sorted_slist(slist* sl, slist* newstd) {
	slist* current;
	//add the new studen to slist (adding by order!)
	//if the slist is empty:
	if (sl == NULL) {
		sl = newstd;
		sl->next = NULL;
		return sl;
	}
	//else the slist isnt empty:
	else {
		current = sl;
		//new student ID smaller than the ID of all the student in the list
		if ((newstd->info->id) < (sl->info->id)) {
			newstd->next = sl;
			sl = newstd;
			return sl;
		}
		//as long as the new student ID is larger than the current and next student ID and we didnt get to the end of the list, the current student is promoted
		while ((current->next) != NULL && ((newstd->info->id) > (current->info->id)) && ((newstd->info->id) > (current->next->info->id))) {
			current = current->next;
		}
		//new student ID larger than the ID of all the student in the list
		if ((newstd->info->id) > (current->info->id) && (current->next) == NULL) {
			current->next = newstd;
			newstd->next = NULL;
			return sl;
		}
		//new student ID larger than current student ID but smaller than next student ID, save the new student between them (cur,new,curnext)
		if ((newstd->info->id) > (current->info->id) && (newstd->info->id) < (current->next->info->id)) {
			newstd->next = current->next;
			current->next = newstd;
			return sl;
		}
	}
	//returns the address of the head of the students list
	//the head change only in case of a empty list or in case that the new student ID is the smallest
	return sl;
}

slist* add_student(slist *students, char *name, int id) {
	slist* newstd, *students_head;
	//create a pointer to a new student
	newstd = (slist*)malloc(sizeof(slist));
	//define newstd->info as a pointer to struct student and create a dynamic memory for the student info (name,id,courses)
	(newstd->info) = (student*)malloc(sizeof(student));
	(newstd->info->name) = (char*)malloc(sizeof(name)+1);
	//make sure the memory is allocated
	if (!newstd || !(newstd->info) || !(newstd->info->name))
		exit(1);
	//fill the student's information fields
	(newstd->info->id) = id;
	strcpy(newstd->info->name, name);
	(newstd->info->courses) = NULL;
	//add the new studen to slist (adding by order!)
	students_head = add_std_to_sorted_slist(students, newstd);
	//returns the address of the head of the students list
	return students_head;
}

clist* add_course_to_sorted_clist(clist* cl, clist* newcourse) {
	clist* current;
	//add the new course to clist (adding by order!)
	//if the clist is empty:
	if (cl == NULL) {
		cl = newcourse;
		cl->next = NULL;
		return cl;
	}
	//else the clist isnt empty:
	else {
		current = cl;
		//new course number smaller than the number of all the courses in the list
		if ((newcourse->info->number) < (cl->info->number)) {
			newcourse->next = cl;
			cl = newcourse;
			return cl;
		}
		//as long as the new course number is larger than the current and next course number and we didnt get to the end of the list, the current course is promoted
		while ((current->next) && (newcourse->info->number) > (current->info->number) && (newcourse->info->number) > (current->next->info->number)) {
			current = current->next;
		}
		//new course number larger than the number of all the courses in the list
		if ((newcourse->info->number) > (current->info->number) && (current->next) == NULL) {
			current->next = newcourse;
			newcourse->next = NULL;
			return cl;
		}
		//new course number larger than current course number but smaller than next course number, save the new course between them (cur,new,curnext)
		if ((newcourse->info->number) > (current->info->number) && (newcourse->info->number) < (current->next->info->number)) {
			newcourse->next = current->next;
			current->next = newcourse;
			return cl;
		}
	return cl;
	}
	//returns the address of the head of the courses list
	//the head change only in case of a empty list or in case that the new course number is the smallest
}

clist* add_course(clist *courses, char *title, int number) {
	clist* newcourse, *courses_head;
	//create a pointer to a new student
	newcourse = (clist*)malloc(sizeof(clist));
	//define newcourse->info as a pointer to struct course and create a dynamic memory for the course info (titel,number,students)
	(newcourse->info) = (course*)malloc(sizeof(course));
	(newcourse->info->title) = (char*)malloc(sizeof(title) + 1);
	//make sure the memory is allocated
	if (!newcourse || !(newcourse->info) || !(newcourse->info->title))
		exit(1);
	//fill the course's information fields
	newcourse->info->number = number;
	strcpy(newcourse->info->title, title);
	newcourse->info->students = NULL;
	//add the new course to clist (adding by order!)
	courses_head = add_course_to_sorted_clist(courses, newcourse);
	//returns the address of the head of the courses list
	return courses_head;
	}

void reg_student(slist *students, clist *courses, int id, int number) {
	//allocate memory for the pointer
	clist* wanted_course = malloc(sizeof(clist));
	slist* relevant_std = malloc(sizeof(slist));
	if (!wanted_course || !relevant_std)
		exit(1);
	//looking for the pointer of the requested student
	while (students->info->id != id) {
		students = students->next;
	}
	relevant_std->info = students->info;
	//looking for the pointer of the requested student
	while (courses->info->number != number) {
		courses = courses->next;
		}
	wanted_course->info = courses->info;
	relevant_std->info->courses = add_course_to_sorted_clist(relevant_std->info->courses, wanted_course);
	wanted_course->info->students = add_std_to_sorted_slist(wanted_course->info->students, relevant_std);
}

void unreg_student(slist *students, int id, int number) {
	clist * un_wanted_course,*cours_to_free, *prev_un_wanted_course = NULL;
	slist * relevant_std, *std_p_in_course_slist, *std_to_free, *prev_std_p_in_course_slist = NULL;
	//Looking for the pointer of the requested student
	relevant_std = students;
	while (relevant_std->info->id != id) {
		relevant_std = relevant_std->next;
	}
	//course in student clict
	//Looking for the pointer of the un wanted course in the student's clist
	un_wanted_course = relevant_std->info->courses;
	while (un_wanted_course->info->number != number) {
		prev_un_wanted_course = un_wanted_course;
		un_wanted_course = un_wanted_course->next;
	}
	//student in course slist
	//remove the student from the course studen list
	std_p_in_course_slist = un_wanted_course->info->students;
	while (std_p_in_course_slist->info->id != id) {
		prev_std_p_in_course_slist = std_p_in_course_slist;
		std_p_in_course_slist = std_p_in_course_slist->next;
	}
	//if the student is the first in the course student list
	if (prev_std_p_in_course_slist == NULL) {
		std_to_free = std_p_in_course_slist; //->info
		std_p_in_course_slist = std_p_in_course_slist->next;
		free(std_to_free);
		un_wanted_course->info->students = std_p_in_course_slist;
	}
	//else the student is not the first in the course student list
	else {
		std_to_free = std_p_in_course_slist;
		prev_std_p_in_course_slist->next = std_p_in_course_slist->next;
		free(std_to_free);
	}
	//remove the course from the student course list
	//if the course is the first in the student course list
	if (prev_un_wanted_course == NULL) {
		cours_to_free = un_wanted_course;
		un_wanted_course = un_wanted_course->next;
		free(cours_to_free);
		relevant_std->info->courses = un_wanted_course;
	}
	else {
		cours_to_free = un_wanted_course;
		prev_un_wanted_course->next = un_wanted_course->next;
		free(cours_to_free);
	}
}

void print_students(slist *students) {
	clist* std_courses_list;
	if (!students)
		printf("STUDENT LIST: EMPTY!\n");
	else
		printf("STUDENT LIST:\n");
	while (students) {
		std_courses_list = students->info->courses;
		printf("%d:%s\n", students->info->id,students->info->name);
		if (!std_courses_list)
			printf("student is not registered for courses.");
		else
			printf("courses:");
		while (std_courses_list) {
			if (std_courses_list->next == NULL)
				printf(" %d-%s", std_courses_list->info->number, std_courses_list->info->title);
			else
				printf(" %d-%s,", std_courses_list->info->number, std_courses_list->info->title);
			std_courses_list = std_courses_list->next;
		}
		printf("\n");
		students = students->next;
	}
}

void print_courses(clist *courses) {
	slist* course_students_list;
	if (!courses)
		printf("COURSE LIST: EMPTY!\n");
	else
		printf("COURSE LIST:\n");
	while (courses) {
		course_students_list = courses->info->students;
		printf("%d:%s\n", courses->info->number, courses->info->title);
		if (!course_students_list)
			printf("course has no students.");
		else
			printf("students:");
		while (course_students_list) {
			if (course_students_list->next == NULL)
				printf(" %d-%s", course_students_list->info->id, course_students_list->info->name);
			else
				printf(" %d-%s,", course_students_list->info->id, course_students_list->info->name);
			course_students_list = course_students_list->next;
		}
		printf("\n");
		courses = courses->next;
	}
}

void free_all(slist *sl, clist *cl) {
	clist* clist_to_free;
	slist* slist_to_free;
	while (sl) {
		while (sl->info->courses) {
			clist_to_free = sl->info->courses;
			sl->info->courses = sl->info->courses->next;
			free(clist_to_free);
		}
		free(sl->info->courses);
		free(sl->info->name);
		free(sl->info);
		slist_to_free = sl;
		sl = sl->next;
		free(slist_to_free);
	}
	free(sl);
	while (cl) {
		while (cl->info->students) {
			slist_to_free = cl->info->students;
			cl->info->students = cl->info->students->next;
			free(slist_to_free);
		}
		free(cl->info->title);
		free(cl->info);
		clist_to_free = cl;
		cl = cl->next;
		free(clist_to_free);
	}
	free(cl);
}
	
//DO NOT TOUCH THIS FUNCTION
static void getstring(char *buf, int length) {
	int len;
	buf = fgets(buf, length, stdin);
	len = (int)strlen(buf);
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
}

//DO NOT TOUCH THIS FUNCTION 
int main() {
	slist* students = 0;
	clist* courses = 0;
	char  c;
	char  buf[100];
	int   id, num;

	do {
		printf("Choose:\n"
			"    add (s)tudent\n"
			"    add (c)ourse\n"
			"    (r)egister student\n"
			"    (u)nregister student\n"
			"    (p)rint lists\n"
			"    (q)uit\n");

		while ((c = (char)getchar()) == '\n');
		getchar();

		switch (c) {
		case 's':
			printf("Adding new student.\n");

			printf("Student name: ");
			getstring(buf, 100);

			printf("Student ID: ");
			scanf("%d", &id);

			students = add_student(students, buf, id);

			break;

		case 'c':
			printf("Adding new course.\n");

			printf("Course name: ");
			getstring(buf, 100);

			printf("Course number: ");
			scanf("%d", &num);

			courses = add_course(courses, buf, num);

			break;

		case 'r':
			printf("Registering a student to a course.\n");

			printf("Student ID: ");
			scanf("%d", &id);

			printf("Course number: ");
			scanf("%d", &num);

			reg_student(students, courses, id, num);

			break;

		case 'u':
			printf("Unregistering a student from a course.\n");

			printf("Student ID: ");
			scanf("%d", &id);

			printf("Course number: ");
			scanf("%d", &num);

			unreg_student(students, id, num);

			break;

		case 'p':
			printf("Printing Information.\n");

			print_students(students);
			print_courses(courses);

			break;

		case 'q':
			printf("Quitting...\n");
			break;
		}

		if (c != 'q')
			printf("\n");
	} while (c != 'q');

	free_all(students, courses);
	return 0;
}