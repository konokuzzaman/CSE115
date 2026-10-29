#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct user{

  char name[50];
  char email[50];
  char password[50];
  char phone[50];

};

struct Doctor {

    char name[50];
    char degree[50];
    char specialty[50];
    int doctor_id;

};

struct Appointment {

    int doctor_id;
    char date[11];
    char patient_name[50];
    char patient_contact[50];
    int serial_number;

};

void adddoc();
void bookapp();
void viewapp();
void viewdoc();
void editdoc();
void searchdoc();
void deldoc();

void logo();
void loading();
void loginmenu();
void adminloginmenu();
void adminmenu();
void userloginmenu();
void usermenu();
void takepass();

void deldoc() {

    system("color 9");

    FILE *fp;
    FILE *temp_fp;

    char name[50];
    int found = 0;

    printf("Enter the name of the doctor to delete: ");
    fflush(stdin);
    gets(name);

    fp = fopen("doctors.txt", "r");

    if (fp == NULL) {
        printf("Could not open file.\n");
        return;
    }

    temp_fp = fopen("temp.txt", "w");

    if (temp_fp == NULL) {
        printf("Could not create temporary file.\n");
        fclose(fp);
        return;
    }

    struct Doctor temp_doc;

    while (fread(&temp_doc, sizeof(struct Doctor), 1, fp)) {
        if (strcmp(temp_doc.name, name) == 0) {
            found = 1;
            printf("Doctor with name %s deleted.\n", temp_doc.name);
        } else {
            fwrite(&temp_doc, sizeof(struct Doctor), 1, temp_fp);
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (!found) {
        printf("Doctor with the name %s not found.\n", name);
    } else {
        remove("doctors.txt");
        rename("temp.txt", "doctors.txt");
    }

}

void adddoc() {

    system("color 9");

    FILE *fp;

    struct Doctor doctors;
    char choice = 'y';


    fp = fopen("doctors.txt", "a+");

    if (fp == NULL) {
        printf("Error opening file");
        return;
    }

    printf("\t\t\t\t\t-------Enter details for doctors-------\n\n");

    while (choice == 'y') {
        printf("Enter Doctor name: ");
        fflush(stdin);
        gets(doctors.name);

        printf("Enter doctor's degree: ");
        fflush(stdin);
        gets(doctors.degree);

        printf("Enter doctor's specialty: ");
        fflush(stdin);
        gets(doctors.specialty);

        printf("Enter doctor's id: ");
        fflush(stdin);
        scanf("%d", &doctors.doctor_id);

        fflush(stdin);

        fwrite(&doctors, sizeof(struct Doctor), 1, fp);

        printf("Do you want to add more doctors? (y/n): ");
        fflush(stdin);
        choice = getchar();

        if(choice=='n'){
            loading();
        }

        printf("\n\n");

        fflush(stdin);
    }

    fclose(fp);
}

void bookapp() {

    system("color 9");

    printf("Enter Appointment Information:\n");
    printf("==============================\n");

   FILE *fp_doctors;
   FILE *fp_appointments;

    struct Doctor doctor;
    struct Appointment app;
    static int serial_counter = 1;

    fp_doctors = fopen("doctors.txt", "r");

    if (fp_doctors == NULL) {
        printf("Error opening doctors file.\n");
        return;
    }

    fp_appointments = fopen("appointments.txt", "a");

    if (fp_appointments == NULL) {
        printf("Error opening file.\n");
        fclose(fp_doctors);
        return;
    }

    printf("Enter the doctor's ID: ");
    scanf("%d", &app.doctor_id);
    fflush(stdin);

    while (fread(&doctor, sizeof(struct Doctor), 1, fp_doctors)) {
        if (app.doctor_id == doctor.doctor_id) {
            fclose(fp_doctors);
            break;
        }
    }

    if (feof(fp_doctors)) {
        printf("Error: Doctor ID not found.\n");
        fclose(fp_appointments);
        fclose(fp_doctors);
        return;
    }

    rewind(fp_doctors);

    printf("Enter the appointment date (yyyy-mm-dd): ");
    scanf("%s", app.date);
    fflush(stdin);

    printf("Enter your name: ");
    scanf("%s", app.patient_name);
    fflush(stdin);

    printf("Enter your contact number: ");
    scanf("%s", app.patient_contact);
    fflush(stdin);

    app.serial_number = serial_counter++;

    fwrite(&app, sizeof(struct Appointment), 1, fp_appointments);
    fclose(fp_appointments);

    printf("Appointment booked successfully.\n");

    fclose(fp_doctors);

    Sleep(2000);

    loading();

}

void viewapp() {

    system("color 9");

    printf("View Appointment Information:\n");
    printf("==============================\n");

    FILE *fp_doctors;
    FILE *fp_appointments;

    struct Doctor doctor;
    struct Appointment app;
    char current_user[50];

    printf("Enter your name: ");
    scanf("%s", current_user);

    fp_doctors = fopen("doctors.txt", "r");

    if (fp_doctors == NULL) {
        printf("Error opening doctors file.\n");
        return;
    }

    fp_appointments = fopen("appointments.txt", "r");

    if (fp_appointments == NULL) {
        printf("Error opening appointments file.\n");
        fclose(fp_doctors);
        return;
    }

    printf("Appointments:\n");

    while (fread(&app, sizeof(struct Appointment), 1, fp_appointments)){
        if (strcmp(app.patient_name, current_user) == 0) {
            while (fread(&doctor, sizeof(struct Doctor), 1, fp_doctors)) {
                if (app.doctor_id == doctor.doctor_id) {
                    printf("Doctor's Name: %s\n", doctor.name);
                    break;
                }
            }
            rewind(fp_doctors);

            printf("Doctor's ID: %d\n", app.doctor_id);
            printf("Date: %s\n", app.date);
            printf("Time: Time will notify in your phone \n");
            printf("Patient Name: %s\n", app.patient_name);
            printf("Patient Contact Number: %s\n", app.patient_contact);
            printf("Serial Number: %d\n\n", app.serial_number);
        }
    }

    fclose(fp_doctors);
    fclose(fp_appointments);

    printf("Press enter to exit");
    getch();

    loading();
    usermenu();

}

void viewdoc() {

    system("color 9");

    FILE *fp;
    struct Doctor doctors;

    fp = fopen("doctors.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }

    printf("Doctor Information:\n");
    printf("====================\n");

    while (fread(&doctors, sizeof(struct Doctor), 1, fp)) {
        printf("Doctor Name: %s\n", doctors.name);
        printf("Degree: %s\n", doctors.degree);
        printf("Specialty: %s\n", doctors.specialty);
        printf("Doctor ID: %d\n", doctors.doctor_id);
        printf("\n");

    }

    printf("Press enter to exit");
    getch();

    loading();

    fclose(fp);
}

void editdoc() {

    system("color 9");

    FILE *fp;

    int targetId;
    struct Doctor doc;

    fflush(stdin);

    printf("Enter the doctor ID you want to edit: ");
    scanf("%d", &targetId);

    fp = fopen("doctors.txt", "r+");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    int found = 0;
    while (fread(&doc, sizeof(struct Doctor), 1, fp)) {
        if (doc.doctor_id == targetId) {
            printf("Doctor found! Editing details:\n");

            printf("Enter updated Doctor name: ");
            fflush(stdin);
            gets(doc.name);

            printf("Enter updated doctor's degree: ");
            gets(doc.degree);

            printf("Enter updated doctor's specialty: ");
            gets(doc.specialty);


            fseek(fp, -sizeof(struct Doctor), SEEK_CUR);
            fwrite(&doc, sizeof(struct Doctor), 1, fp);

            printf("Doctor information updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No doctor with ID %d found.\n", targetId);
    }

    fclose(fp);
}

void searchdoc(){

    system("color 9");

    FILE* fp;

    char search_name[100];
    struct Doctor doc;

    fflush(stdin);
    printf("Enter the name of the doctor you want to search for: ");

    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0';

    fp = fopen("doctors.txt", "rb");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    int found = 0;
    while (fread(&doc, sizeof(struct Doctor), 1, fp)) {

        if (strcmp(doc.name, search_name) == 0) {
            printf("Doctor found!\n");
            printf("Name: %s\n", doc.name);
            printf("Degree: %s\n", doc.degree);
            printf("Specialty: %s\n", doc.specialty);
            printf("ID: %d\n", doc.doctor_id);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Doctor not found.\n");
    }

    fclose(fp);
    printf("Press enter to exit");
    getch();

    loading();
    usermenu();

}


void takepass(char pass[50]){

    int i=0;
    char ch;

    while(1){
            ch=getch();
    if(ch == 13 ){
        pass[i]='\0';
        break;
    }else if(ch == 8){
        if(i>0){
            i--;
            printf("\b \b");
        }
    }else{

        printf("%c",ch);
        Sleep(300);
        printf("\b \b");

        pass[i++]=ch;
        printf("*");
    }
    }
}

void logo() {

    system("color 4");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t");
    printf("ARK Hospital Ltd.");

    Sleep(3000);
    loading();

}

void loading(){

    system("color 8");

    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t");

    for(int i=0;i<5;i++){
        printf(" . ");
        Sleep(300);
    }
    system("cls");

}

void userloginmenu(){

    system("color 2");

    FILE *fp;

    printf("\n\n\n\n\n\n\n\n\n");

    printf("\t\t\t\t\t|-------------------------------------------|\n");
    printf("\t\t\t\t\t|           --- Login(Patient) ---          |\n");
    printf("\t\t\t\t\t| 1.Singup                                  |\n");
    printf("\t\t\t\t\t| 2.Login                                   |\n");
    printf("\t\t\t\t\t| 3.Exit                                    |\n");
    printf("\t\t\t\t\t|-------------------------------------------|\n");

    int n,userfound=0;

    printf("\n\n\t\t\t\t\tEnter Your Choice: ");
    scanf("%d",&n);

    struct user user;
    char password2[50];

    switch(n){

    case 1:

        loading();

        system("color 9");

        printf("\t\t\t\t\t-------------Signup-------------\n\n");

        fflush(stdin);

        printf("\nEnter your full name    : ");
        gets(user.name);
        fflush(stdin);

        printf("\nEnter your email         : ");
        gets(user.email);
        fflush(stdin);

        printf("\nEnter your phone number  : ");
        gets(user.phone);
        fflush(stdin);


        printf("\nEnter your password      : ");
        takepass(user.password);
        fflush(stdin);

        while(1){

        printf("\n\nConfirm your password    : ");
        takepass(password2);
        fflush(stdin);

        if(!strcmp(user.password,password2)){

            fp=fopen("users.txt","a+");
            fwrite(&user,sizeof(struct user),1,fp);
            if(fwrite !=0){
                printf("\n\nuser registraion successful");
                Sleep(2000);

                fclose(fp);

                break;
            }else{
                printf("\n\nsometing went wrong");
                Sleep(2000);
                printf("\a");
            }

        }else{
            printf("\nPassword Not Matched");
            Sleep(2000);
            printf("\a");
        }

        }

        break;

    case 2:

        loading();

        system("color 9");

        char useremail[50],pas[50];
        struct user usr;

         printf("\n\n\n\n\n\n\n\n\n\n\n");

        fflush(stdin);
        printf("\t\t\t\t\tEnter your email id:");
        gets(useremail);

        fflush(stdin);
        printf("\n\n\t\t\t\t\tEnter your password :");
        takepass(pas);

        fp=fopen("users.txt","r");

        while(fread(&usr,sizeof(struct user),1,fp)){

            if(!strcmp(usr.email,useremail)){

                if(!strcmp(usr.password,pas)){
                    loading();
                    usermenu();
                }else{
                           system("cls");

                    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("\t\t\t\t\t    Invalid password!");
                    printf("\a");

                    Sleep(2000);

                    system("cls");
                    userloginmenu();
                }
                userfound=1;
            }
        }

        if(userfound==0){
                system("cls");

            printf("\n\n\n\n\n\n\n\n\n\n\n\n");

            printf("\t\t\t\t\t    User is not registered!");
            printf("\a");

            Sleep(2000);

            system("cls");
            userloginmenu();
        }

        fclose(fp);

        break;

        case 3:

            loading();
            loginmenu();

        break;

         default:

            printf("\n\t\t\t\t\tInvalid Choice .Wait 3 second to choice again.");
            Sleep(3000);

            loading();

            userloginmenu();

    }

    loading();


}

void usermenu(){


 while(1){

    printf("\n\n\n\n\n\n\n\n\n");

    system("color 9");

    printf("\t\t\t\t\t|--------------------------------------------|\n");
    printf("\t\t\t\t\t|             --- USER MENU ---              |\n");
    printf("\t\t\t\t\t| 1.View Doctor Information                  |\n");
    printf("\t\t\t\t\t| 2.Book Appointment                         |\n");
    printf("\t\t\t\t\t| 3.View Appointment                         |\n");
    printf("\t\t\t\t\t| 4.Search Doctor                            |\n");
    printf("\t\t\t\t\t| 5.Exit                                     |\n");
    printf("\t\t\t\t\t|--------------------------------------------|\n");

     int n;
        printf("\n\n\t\t\t\t\tEnter Your Choice : ");
         scanf("%d",&n);

    switch(n){

     case 1:
        loading();
        viewdoc();
        break;

     case 2:
       loading();
       bookapp();
       break;

     case 3:
        loading();
        viewapp();
        break;

     case 4:
        loading();
        searchdoc();
        break;

     case 5:
        loading();
        loginmenu();
        break;

    default:
        printf("\n\t\t\t\t\tInvalid Choice .Wait 3 second to choice again.");

        Sleep(3000);
        loading();
        usermenu();

    }

    }
}


void adminloginmenu(){

    FILE *cp;

    system("color 2");

    printf("\n\n\n\n\n\n\n\n\n");

    printf("\t\t\t\t\t|-------------------------------------------|\n");
    printf("\t\t\t\t\t|           --- Login(Admin) ---            |\n");
    printf("\t\t\t\t\t| 1.Login                                   |\n");
    printf("\t\t\t\t\t| 2.Exit                                    |\n");
    printf("\t\t\t\t\t|-------------------------------------------|\n");

    int n,userfound=0;

    printf("\n\n\t\t\t\t\tEnter your choice: ");
    scanf("%d",&n);

    switch(n){

    case 1:
        loading();

        system("color 9");

        char useremail[50],pas[50];
        struct user usr;

         printf("\n\n\n\n\n\n\n\n\n\n\n");

        fflush(stdin);
        printf("\t\t\t\t\tEnter your email id:");
        gets(useremail);

        fflush(stdin);
        printf("\n\n\t\t\t\t\tEnter your password :");
        takepass(pas);

        cp=fopen("admin.txt","r");

        while(fread(&usr,sizeof(struct user),1,cp)){

            if(!strcmp(usr.email,useremail)){

                if(!strcmp(usr.password,pas)){
                    loading();
                    adminmenu();
                }else{
                    system("cls");

                    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
                    printf("\t\t\t\t\t    Invalid password!");
                    printf("\a");

                    Sleep(2000);

                    system("cls");
                    adminloginmenu();
                }
                userfound=1;
            }
        }

        if(userfound==0){
          system("cls");

            printf("\n\n\n\n\n\n\n\n\n\n\n\n");

            printf("\t\t\t\t\t    User is not registered!");
            printf("\a");

            Sleep(2000);

            system("cls");
            adminloginmenu();
        }

        fclose(cp);

        break;

    case 2:
        loading();
        loginmenu();
        break;

    default:
        printf("\n\t\t\t\t\tInvalid Choice .Wait 3 second to choice again.");

        Sleep(3000);
        loading();
        adminloginmenu();

    }


}

void adminmenu(){

    while(1){

    system("cls");

    system("color 9");

    printf("\n\n\n\n\n\n\n\n\n");

    printf("\t\t\t\t\t|--------------------------------------------|\n");
    printf("\t\t\t\t\t|             --- ADMIN MENU ---             |\n");
    printf("\t\t\t\t\t| 1.Add Doctor Information                   |\n");
    printf("\t\t\t\t\t| 2.View Doctor Information                  |\n");
    printf("\t\t\t\t\t| 3.Edit Doctor Information                  |\n");
    printf("\t\t\t\t\t| 4.Delete  Doctor Information               |\n");
    printf("\t\t\t\t\t| 5.Exit                                     |\n");
    printf("\t\t\t\t\t|--------------------------------------------|\n");

     int n;
        printf("\n\n\t\t\t\t\tEnter Your Choice : ");
         scanf("%d",&n);

    switch(n){

     case 1:
        loading();
        adddoc();
        break;

     case 2:
        loading();
        viewdoc();
        break;

     case 3:
        loading();
        editdoc();
        break;

     case 4:
        loading();
        deldoc();
        break;

     case 5:
        loading();
        loginmenu();
        break;

    default:
        printf("\n\t\t\t\t\tInvalid Choice .Wait 3 second to choice again.");

        Sleep(3000);
        loading();
        adminmenu();

    }

    }

}

void loginmenu(){

    while(1){

    system("color 2");

    printf("\n\n\n\n\n\n\n\n\n");

    printf("\t\t\t\t\t|-------------------------------------------|\n");
    printf("\t\t\t\t\t|             --- Login MENU ---            |\n");
    printf("\t\t\t\t\t| 1.Administrator                           |\n");
    printf("\t\t\t\t\t| 2.User(Patient)                           |\n");
    printf("\t\t\t\t\t| 3.Exit                                    |\n");
    printf("\t\t\t\t\t|-------------------------------------------|\n");


    int n;
    printf("\n\n\t\t\t\t\tEnter Your Choice : ");
    scanf("%d",&n);


    switch(n){

    case 1:
        loading();
        adminloginmenu();
    break;

    case 2:
        loading();
        userloginmenu();
    break;

    case 3:
        system("cls");

        printf("\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t\t\t\t");
        printf(" Exiting");

        for(int i=0;i<4;i++){
            printf(" . ");
            Sleep(400);
        }

        system("cls");

        exit(1);

    break;

    default:
        printf("\n\t\t\t\t\tInvalid Choice .Wait 3 second to choice again.");
        Sleep(3000);
        system("cls");

    }
  }
}

void main() {

    logo();
    loginmenu();

}


