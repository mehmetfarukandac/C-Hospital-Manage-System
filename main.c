#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<locale.h>
#include<time.h>
#define g getch
struct Sprocess{
	char nameb[15];
	char surnameb[15];
	char IDb[15];
	char processb[20];
	char priceb[10];
};
struct patient{
    char name[15];
    char surname[15];
    char ID[15];
    char age[5];
    char roomnumber[10];
    char price[10];
};
int main(){
	
	
	setlocale(LC_ALL, "Turkish");
	system("title ******ISTANBUL AYDIN HOSPITAL******");
	char choice;
	int i,j;
	char newadmin;

		    struct patient *pt1=(struct patient*)malloc(sizeof(struct patient));
            struct patient *pt2=(struct patient*)malloc(sizeof(struct patient));
			struct Sprocess *pr=(struct Sprocess*)malloc(sizeof(struct Sprocess));
		
	FILE *processf=fopen("processf.txt","w");
	char usernames[20]={"admin"};
    char passwords[20]={"1234"};
		int exits; //kullanýcý adý veyya þifre hatasýndan sonra istenen adým (56.satýr);
   	char user[20];
   	char password[20];
   		login: for(i=0;i<1000;i++){
   			system("cls");
            system("color 37");
            printf("****||WELCOMEE TO ISTANBUL AYDIN HOSPITAL||****\n");
   			printf("*****LOGIN SCREEN*****\n");
   				printf("User name for login:"); scanf("%s",user);
				printf("Password for login:"); scanf("%s",password);
    			if(strcmp(password,passwords)==0 && strcmp(user,usernames)==0){
    					printf("\a \b********LOGIN SUCCESSFUL********\n");
    					break;
				}
				else{
						printf("\a\a---|||PASSWORD OR USERNAME ERROR|||---\n(press '1' to retry,\n'0' to exit)\n\n\n");
						scanf("%d",&exits);
						if(exits==0){
   							exit(0);
			   }
					goto login;
				}
			}
		FILE *patientf = NULL;
		system("color 71");

        	system("cls");
        do{
      turn: printf("\n------MENU------\n----------------\n1-Add New Patient\n2-List Of Patient\n3-Search Patient\n4-Edit Patient\n5-Delete Patient\n6-FEES\n7-Prepare Bill\n0-Exit\n----------------\n");
            printf("Your choice:");
            scanf("%s",&choice);
            switch(choice){
           		case '1':
        	        system("cls");
            	    start(patientf,pt2);
                  	goto proc; //Hastayy uygun doktora göndermeden önce çykartylacak i?lem ka?ydyna yönlendirmek için (case 7)
                  	goto turn; //case 1 bittikten sonra menü sekmesine dönmek için
                break;
                case '2':
     	            system("cls");
                    list(patientf,pt2); //Listeleme Fonksiyonu
			        goto turn;
      		 	break;
                case '3':
                    system("cls");
           			search(patientf,pt2); //Hasta bilgilerini Arama Fonksiyonu
				    goto turn;
                break;
                case '4':
               		system("cls");
               		edit(patientf,pt2); //Bilgileri düzenleme fonksiyonu
         			goto turn; //case 4 bittikten sonra menü sekmesine dönmek için
                break;
                case '5':
                	system("cls");
                	deletef(patientf,pt2); //Hasta silme fonksiyonu
                	goto turn; //case 5 bittikten sonra menü sekmesine dönmek için
           	    break;
        		case '6':
        			system("cls");
        			char insurance; //Ücretler fonksiyonu
						printf("\a\n\n   |-|-|***|FEE TABLE|***|-|-|\n\n");
						printf(" Does patient have an insurance?\n\t    (Y or N)");
						scanf("%s",&insurance);
        			int ascinsurance=insurance;
        			fees(ascinsurance);
        			goto turn;//case 6 bittikten sonra menü sekmesine dönmek için
        		break;
        		case '7':
            proc:
        		process(processf,pr); //i?lem ka?ydy fonksiyonu
       		break;
				case '0':
                	exit(0);
                break;
        	}
        }while(1);
		g();
    return 0;
}
void deletef(FILE *patientf,struct patient *pt2){
		system("color 75");
			patientf=fopen("patientf.txt","r+");
		char dname[11];	
			int sayac=0;
					while(!feof(patientf)){
						fread(pt2,sizeof(struct patient),1,patientf);
						sayac++;
					}
			printf("\nSearch Name: ");
     		scanf("%s",dname);
			int i;
       		printf("\n NAME \t SURNAME \t ID \t AGE \t ROOM NUMBER \t PRICE");
		  	for(i=0;i<(sayac-1);i++){
            		//fread(pt2,sizeof(struct patient),1,patientf);
         	            	if(strcmp((pt2)->name,dname)==0){
						   		printf("\n-----------------------------------------------------------\n");
						    	printf("%s     %s\t    %s  %s\t   %s\t\t %s\n\n\n",(pt2)->name,(pt2)->surname,(pt2)->ID,(pt2)->age,(pt2)->roomnumber,(pt2)->price);
            	         		break;
						 	}
                        	if(strcmp((pt2+i)->name,dname)!=0){
                        	printf("The user you requested could not be found");
                        	break;
							}
				}        fclose(patientf);

		patientf=fopen("patientf.txt","r");
		FILE *patientf2;
		patientf2=fopen("patientf2.txt","w");
		char dID[15];
			printf("\a***|DELETE PATIENT|***\n");
       		printf("\a*write ID of patient that you want to delete:");
       		scanf("%s",dID);
			rewind(patientf);

		while(!feof(patientf)){
   			fread(pt2,sizeof(struct patient),1,patientf);
			if(feof(patientf))
				break;
			if(strcmp(dID,pt2->ID)!=0){
				fwrite(pt2,sizeof(struct patient),1,patientf2);
			}
		}
			fclose(patientf);
			fclose(patientf2);
			remove("patientf.txt");
			rename("patientf2.txt","patientf.txt");
}
void edit(FILE *patientf,struct patient *pt2){
	int secim;
		system("color 71");
            		char isimdegistirme[15];
	    	        char sidegistirme[15];
					char IDdegistirme[15];
					char agedegistirme[15];
					char rnumberdegistirme[15];
					char pricedegistirme[15];
					printf("\a***|EDIT PATIENT|***\n");
						   printf("\a-------MENU-------\n1-Name\n2-Surname\n3-ID\n4-Age\n5-Room Number\n6-Price\n------------------\n");
						   printf("*what do you want to update? \n");
            			   scanf("%d", &secim);
               		patientf=fopen("patientf.txt","r+");
            		int sayac=0;
					while(!feof(patientf)){
						fread(pt2,sizeof(struct patient),1,patientf);
						sayac++;
					}
					if(secim==1){
            			printf("Write ID that you  want to make processes ");
              		   	   scanf("%s", isimdegistirme);
					int j;
					
		            	for(j=0;j<(sayac-1);j++){
                 	  		fread(pt2,sizeof(struct patient),1,patientf);
                 		if(strcmp(pt2->ID,isimdegistirme)==0){
                      	  printf("current name: %s \n",pt2->name);
                          printf("write to new name: ");
                 	char newname[15];
                    	scanf("%s",newname);
                   		 strcpy(pt2->name,newname);
      		              fseek(patientf,-1*sizeof(struct patient),SEEK_CUR); 
            		        fwrite(pt2,sizeof(struct patient),1,patientf);
            		        break;
                 }
              }
            fclose(patientf);
            }
            if(secim==2){
			  printf("Write ID that you want to make processes:");
              scanf("%s", sidegistirme);
			int j;
              for(j=0;j<(sayac-1);j++){
                 fread(pt2,sizeof(struct patient),1,patientf);
                 if(strcmp(pt2->ID,sidegistirme)==0){
                        printf("current surname: %s \n",pt2->surname);
                        printf("write to new surname: ");
                 char newsname[15];
                    scanf("%s",newsname);
                    strcpy(pt2->surname,newsname);
                    fseek(patientf,-1*sizeof(struct patient),SEEK_CUR);
                    fwrite(pt2,sizeof(struct patient),1,patientf);
                 	break;
				 }
              }
            fclose(patientf);
            }

			if(secim==3){
			  printf("Write ID that you want to make processes:");
              scanf("%s", IDdegistirme);
			int j;
              for(j=0;j<(sayac-1);j++){
                 fread(pt2,sizeof(struct patient),1,patientf);
                 if(strcmp(pt2->ID,IDdegistirme)==0){
                        printf("current ID: %s \n",pt2->ID);
                        printf("write to new ID: ");
                 char newID[15];
                    scanf("%s",newID);
                    strcpy(pt2->ID,newID);
                    fseek(patientf,-1*sizeof(struct patient),SEEK_CUR);
                    fwrite(pt2,sizeof(struct patient),1,patientf);
                 	break;
				 }
              }
            fclose(patientf);
            }
            
			if(secim==4){
			  printf("Write ID that you want to make processes:");
              scanf("%s", agedegistirme);
			int j;
              for(j=0;j<(sayac-1);j++){
                 fread(pt2,sizeof(struct patient),1,patientf);
                 if(strcmp(pt2->ID,agedegistirme)==0){
                        printf("current Age: %s \n",pt2->age);
                        printf("write to new Age: ");
                 char newage[15];
                    scanf("%s",newage);
                    strcpy(pt2->age,newage);
                    fseek(patientf,-1*sizeof(struct patient),SEEK_CUR);
                    fwrite(pt2,sizeof(struct patient),1,patientf);
                 	break;
				 }
              }
            fclose(patientf);
            }
             if(secim==5){
			  printf("Write ID that you want to make processes:");
              scanf("%s", rnumberdegistirme);
			int j;
              for(j=0;j<(sayac-1);j++){
                 fread(pt2,sizeof(struct patient),1,patientf);
                 if(strcmp(pt2->ID,rnumberdegistirme)==0){
                        printf("current Age: %s \n",pt2->roomnumber);
                        printf("write to new Age: ");
                 char newroom[15];
                    scanf("%s",newroom);
                    strcpy(pt2->roomnumber,newroom);
                    fseek(patientf,-1*sizeof(struct patient),SEEK_CUR);
                    fwrite(pt2,sizeof(struct patient),1,patientf);
                 	break;
				 }
              }
            fclose(patientf);
            }
			if(secim==6){
			  printf("Write ID that you want to make processes:");
              scanf("%s",pricedegistirme);
			int j;
              for(j=0;j<(sayac-1);j++){
                 fread(pt2,sizeof(struct patient),1,patientf);
                 if(strcmp(pt2->ID,pricedegistirme)==0){
                        printf("current Age: %s \n",pt2->price);
                        printf("write to new Age: ");
                 char newprice[15];
                    scanf("%s",newprice);
                    strcpy(pt2->price,newprice);
                    fseek(patientf,-1*sizeof(struct patient),SEEK_CUR);
                    fwrite(pt2,sizeof(struct patient),1,patientf);
                    break;
                 }
              }
            fclose(patientf);
            }
}

void search(FILE *patientf,struct patient *pt2){
		system("color 75");
		printf("\a\n*-*|Patient Search Menu|*-*");
		patientf=fopen("patientf.txt","r+");
		char sname[11];
		int sayac=0;
					while(!feof(patientf)){
						fread(pt2,sizeof(struct patient),1,patientf);
						sayac++;
					}
			printf("\nSearch Name: ");
     		scanf("%s",sname);
			int i;
       		printf("\n NAME \t SURNAME \t ID \t AGE \t ROOM NUMBER \t PRICE");
			  	for(i=0;i<(sayac-1);i++){
            		fread(pt2,sizeof(struct patient),1,patientf);
					    
         	            	if(strcmp(pt2->name,sname)==0){
						   		printf("\n-----------------------------------------------------------\n");
						    	printf("%s     %s\t    %s  %s\t   %s\t\t %s\n\n\n",(pt2+i)->name,(pt2+i)->surname,(pt2+i)->ID,(pt2+i)->age,(pt2+i)->roomnumber,(pt2+i)->price);
						 	}
                        	if(strcmp(pt2->name,sname)!=0){
                        	printf("\nAThe user you requested could not be found");
							}
				}        fclose(patientf);
}
void list(FILE *patientf,struct patient *pt2){
		system("color 75");
		int counter=0;
        patientf=fopen("patientf.txt","r");
		printf("\a   ***|PATIENT LIST|***\n");
        printf("Name\tSurname\t\tID\tAge\tRoom Number\tPrice\n");
        printf("-------------------------------------------------------------\n");
			while(!feof(patientf)){
	            counter+=1;
				fread(pt2,sizeof(struct patient),1,patientf);
				if(feof(patientf))
				break;
          		printf("-------------------------------------------------------------\n");
				printf(" %s %s %s %s %s %s\n",pt2->name,pt2->surname,pt2->ID,pt2->age,pt2->roomnumber,pt2->price);
			}
			counter-=1;
			printf("\t\t\t\t\tTotal Patients:%d",counter);
			fclose(patientf);
}
void start(FILE *patientf,struct patient *pt1){
	system("color 70");
	patientf=fopen("patientf.txt","a");
    printf("-------|ADD NEW PATIENT|-------");
    printf("\a\nName:");
    scanf("%s",pt1->name);
    printf("Surname:");
    scanf("%s",pt1->surname);
    printf("ID:");
    scanf("%s",pt1->ID);
    printf("Age:");
    scanf("%s",pt1->age);
    printf("Room Number:");
    scanf("%s",pt1->roomnumber);
    printf("Price:");
    scanf("%s",pt1->price);
	printf("---------------------------------\n");
    printf("Registration Successful\n\n");
	    fwrite(pt1,sizeof(struct patient),1,patientf);
		fclose(patientf);
}
void fees(int ascinsurance){
	if(ascinsurance==89 || ascinsurance==121){
		printf("\a-------MENU-------\n1-examination\t\t :17$\n2-Examination By Profesor:56$\n3-Cataract\t\t :560$\n4-Cornea\t\t :840$\n5-Retina\t\t :455$\n6-Makula\t\t :367$\n7-Strabismus\t\t :350$\n8-Color Blindness\t :350$\n9-Allergic Conjunctivitis:140$\n10-Ektropium\t\t :119$\n------------------\n\n\n\n");
	}
	if(ascinsurance==78 || ascinsurance==110){
		printf("\a-------MENU-------\n1-examination\t\t :25$\n2-Examination By Profesor:80$\n3-Cataract\t\t :800$\n4-Cornea\t\t :1200$\n5-Retina\t\t :650$\n6-Makula\t\t :525$\n7-Strabismus\t\t :500$\n8-Color Blindness\t :500$\n9-Allergic Conjunctivitis:200$\n10-Ektropium\t\t :170$\n------------------\n\n\n\n");
		}
	}
void process(FILE *processf,struct Sprocess *pr) {
        printf("***PROCESS CARD PREPARATION***\n");

	time_t currentTime;
	time(&currentTime);
	int i;

	printf("Name:");
	scanf("%s", pr->nameb);
	printf("Surname:");
	scanf("%s", pr->surnameb);
	printf("ID:");
	scanf("%s", pr->IDb);
	printf("Procces:");
	scanf("%s", pr->processb);
	printf("Price:");
	scanf("%s", pr->priceb);
			fprintf(processf,"\%s",ctime(&currentTime));
			fprintf(processf,"\***ISTANBUL AYDIN HOSPÝTAL ***\n\n");
		fprintf(processf,"\|                               	                           ||||||\n");
	fprintf(processf,"--------------------------------------------------------------------------\n");
		fprintf(processf,"\| name:%s                               \n",pr->nameb);
		fprintf(processf,"\| surname:%s                             \n",pr->surnameb);
		fprintf(processf,"\| ID:%s                                   \n",pr->IDb);
		fprintf(processf,"\| Procces:%s                              \n",pr->processb);
		fprintf(processf,"\| Price:%s                                    \n",pr->priceb);
        fprintf(processf,"\|                             	                           ||||||\n",pr->priceb);
		fprintf(processf,"\|                                      		               ||||||\n",pr->priceb);
		fprintf(processf,"\|                                           	               ||||||\n",pr->priceb);
		fprintf(processf,"\|                                                  	       ||||||\n",pr->priceb);
		fprintf(processf,"\| Prof.Dr:Yaprak Yildirim & M.F.Andac/Room Number:76D       ||||||\n");
		fprintf(processf,"\|            Your ill is our responsibility                 ||||||\n");
		fprintf(processf,"\|     **********F**************************Y*********       ||||||\n");
		fprintf(processf,"\|   ---------**(|)ISTANBUL AYDIN HOSPÝTAL (|)**--------     ||||||\n");
		fprintf(processf,"\|     *********(|)************************(|)*******        ||||||\n");

	fprintf(processf,"-----------------------------------------------------------------------------\n");

		fprintf(processf,"\|                                                           ||||||\n");
		fprintf(processf,"\|                                                           ||||||\n");

			printf("\n\n%s\t",ctime(&currentTime));
			printf("\t\t***ISTANBUL AYDIN HOSPÝTAL***\n\n");
		printf("|                                                                   ||||||\n");
	printf("\------------------------------------------------------------------------------------------\n");
		printf("| name:%s                                              \n",pr->nameb);
		printf("| surname:%s                                            \n",pr->surnameb);
		printf("| ID:%s                                               \n",pr->IDb);
		printf("| Procces:%s                                           \n",pr->processb);
		printf("| Price:%s                                              \n",pr->priceb);
		printf("|                                                                   ||||||\n",pr->priceb);
		printf("|                                                                   ||||||\n",pr->priceb);
        printf("|                                                                   ||||||\n",pr->priceb);
        printf("|                                                                   ||||||\n",pr->priceb);
		printf("| Prof.Dr:Yaprak Yildirim & M.F.Andac/Room Number:76D               ||||||\n");
		printf("|            Your ill is our responsibility                         ||||||\n");
		printf("|     **********c**************************c*********               ||||||\n");
		printf("|   ---------**(|)ISTANBUL AYDIN HOSPÝTAL (|)**--------             ||||||\n");
		printf("|     *********(|)************************(|)*******                ||||||\n");

	printf("\t\t\t\t-----------------------------------------------------------------------------\n");

		printf("|                                                                   ||||||\n");
		printf("|                                                                   ||||||\n\n\n");
	fclose(processf);
	processf=fopen("processf.txt","r");
	system("notepad /P processf.txt");
		fclose(processf);
    }
