#include<stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include <math.h>
int veri_s[480][3],veri_sayi=0; // veri_sayi  deðeri elimizdeki sýnýflandýrýlmýþ element sayisini gösterir
void Load_sample(){
	int i,j,k,f,counter;
	FILE *veri_seti=fopen("test_veri_seti.txt","r");// hazýrladýðým veri seti açilir
	if(veri_seti==NULL){
		printf("cannot open veri seti");// veri seti açýlmaz ise error çiktisi
	}
	k=0;
	j=0;	
	f=0;
	char tmp[3];
	char veri[10];
	while(fgets(veri,sizeof(veri),veri_seti)!=NULL){ // bu döngüde deðerler satýr satýr çekilip
		i=0;											 // integer a çevirilir											 
			while(veri[f]!='\0'&&veri[f]!='\n'){
				
				while(veri[f]!=32&&veri[f]!='\0'){
					tmp[i]=veri[f];
					i++;
					f++;
				}
				i=0;
				if(veri[f]==32){
					f++;
				}
				veri_s[j][k]=atoi(tmp);
				if(veri_s[j][0]>100){
					veri_s[j][0]=veri_s[j][0]-veri_s[j][k]%10;
					veri_s[j][0]=veri_s[j][0]/10;
				}
			if(veri_s[j][1]>200){
				veri_s[j][k]=veri_s[j][k]-veri_s[j][k]%10;
				veri_s[j][k]=veri_s[j][k]/10;
			}
			k++;	
			}
		if(veri[f]!='\n'){
		f=0;
		k=0;
		j++;	
		}	
	}	
}
void Load_test(int test_int[][30]){ // bu fonksiyonda ise sýnýflandýrýlacak elementlerin veri seti ara belleðe alýnýyor
	int i,j,k,f;
	char test_dat[10];
	char tmp[3];
	FILE *test=fopen("kesif_veri_seti.txt","r");
	if(test==NULL){
		printf("test file cannot open");
	}
	k=0;
	i=0;
	j=0;
	f=0;
	while(fgets(test_dat,sizeof(test_dat),test)!=NULL){
		while(test_dat[f]!='\n'&&test_dat[f]!='\0'){
			while(test_dat[f]!=32&&test_dat[f]!='\0'){
				tmp[i]=test_dat[f];
				i++;
				f++;
			}
			if(test_dat[f]==32){
				f++;
			}
			i=0;
			test_int[j][k]=atoi(tmp);
			if(test_int[j][0]>100){
					test_int[j][0]=test_int[j][0]-test_int[j][k]%10;
					test_int[j][0]=test_int[j][0]/10;
				}
			if(test_int[j][1]>200){
				test_int[j][1]=test_int[j][1]-test_int[j][1]%10;
				test_int[j][1]=test_int[j][1]/10;
			}
			k++;
		}
		if(test_dat[f]!='\n'){
			f=0;
			k=0;
			j++;
		}	
	}
	/*for(i=0;i<30;i++){
		for(j=0;j<3;j++){
			printf("%d  ",test_int[i][j]);
		}
		printf("\n");
	}*/
}
int decision(int dist[][480],int k){ //bu fonksiyonda en yakýn mesafediki komþu elementler
	float strange,normal; 			  //k sayýsý kadar seçilip sýnýflandýrma iþlemi yapýlýr 	
	float percentage;
	int i,j;
	strange=0;
	normal=0;
	for(i=0;i<k;i++){
		if(veri_s[dist[1][i]][2]==0){
			strange++;
		}else if(veri_s[dist[1][i]][2]==1){
			normal++;
		}	
	}
	if(strange>normal){ //strange kararsýzlýðýný belirtiyor
		percentage=normal/k*100;
		printf("this element is a  radioactive element\n");
		printf("I am srure about %f  percentage\n",percentage);
		printf("strange vealude is %f normal value is %f",strange,normal);
		
		return 0;
	}else{
		percentage=normal/k*100;
		printf("this element is a non radioactive element\n");
		printf("I am srure about %f  percentage\n",percentage);
		printf("strange vealude is %f normal value is %f",strange,normal);
		return 1;
	}	
}
int distance(int p,int n,int k){	//bu fonksiyonda yeni elementin her bir eski elemente uxaklýðý belirlenir
	int i,j,min,ind_2,tmp,tmp_1;
	int dist[2][480];//2. satýr her bir elementin sýrasýný tutar
	for(i=0;i<480-1;i++){ //böylece en kýsa mesafenin hengi elemntler arasý olduðunu bulabiliriz
		dist[0][i]=(p-veri_s[i][0])*(p-veri_s[i][0])+(n-veri_s[i][1])*(n-veri_s[i][1]);//pisagor hesabý ile mesafe ölçümü 
		dist[1][i]=i;
	}
	//sýrada mesafeyi sýralamak var
	min=dist[0][0];
	for(i=0;i<479;i++){
		for(j=i+1;j<479;j++){
			if(dist[0][i]>dist[0][j]){
				tmp=dist[0][i];
				dist[0][i]=dist[0][j];
				dist[0][j]=tmp;
				tmp_1=dist[1][i];
				dist[1][i]=dist[1][j];
				dist[1][j]=tmp_1;		
			}
		}
	}
	i=decision(dist,k);
	return i;//karar verme fonksiyonuna gider	
} 
void time_graph(int test_int[][30],int k){//bu fonksiyonda çalýþma zamaný grafiði bastýrýlýyor
	int i,j,q,a;
	j=20;
	float counter,micro,d;
	struct timeval start,stop;
	printf("Siniflandirilacak 	test_elements 	iterasyon 	k 	Micro sec.      Accurracy\n");
	for(i=100;i<1000;i+=100){
		gettimeofday(&start,NULL);
		for(a=0;a<i;a++){
			for(q=0;q<j;q++){
			if(distance(test_int[q][0],test_int[q][1],k)){
		 	if(test_int[q][2]==1){
		 		counter++;
			 }}else{
		 	if(test_int[q][2]==0){
		 		counter++;
			 }	
			}
			}
		}
		gettimeofday(&stop,NULL);
	int total=(((stop.tv_sec-start.tv_sec)*1000000)+(stop.tv_usec-start.tv_usec));
	printf("%d\t\t\t  580 \t\t  %d \t\t%d \t %d \t%f\n",q,a,k,total,counter/(q*a)*100);
	if(i>800&&j==20){;
	i=100;
	j=25;
	}else if(i>800&&j==25){
	i=100;
	j=30;	
	}else if(i>800&&j==30&&k!=5){
		i=100;
		j=20;
		k=5;
	}
		counter=0;
	}
	printf("el X itr X k   Zaman Grafiði (tek birim yaklasik 0.1 sn)\n\n");
	for(i=100;i<1000;i+=100){
		gettimeofday(&start,NULL);
		for(a=0;a<i;a++){
			for(q=0;q<j;q++){
				if(distance(test_int[q][0],test_int[q][1],k)){
		 			if(test_int[q][2]==1){
		 				counter++;
					}	
				}else{
		 			if(test_int[q][2]==0){
		 		counter++;
			 		}	
				 }
			}
		}
		gettimeofday(&stop,NULL);
	int total=(((stop.tv_sec-start.tv_sec)*1000000)+(stop.tv_usec-start.tv_usec));
		micro=(float)total/1000000;
		total=round(micro);
		printf("%d X %d X %d = ",q,a,k);
		for(d=0;d<micro;d+=0.1){
			printf("#");
		}
		printf("\n");
		if(i>800&&j==20){;
		i=100;
		j=25;
		printf("\n");
		}else if(i>800&&j==25){
		i=100;
		j=30;
		printf("\n");	
		}else if(i>800&&j==30&&k!=5){
			i=100;
			j=20;
			k=5;
			printf("\n");
		}
		counter=0;
		
		}
	
}
int main(){
	int p,n,k;
	int i,j;
	int test_int[3][30];
	char graph[200][200];
	for(i=0;i<200;i++){
		for(j=0;j<200;j++){
			graph[i][j]=' ';	
		}
	}
	printf("k degerini giriniz");
	scanf("%d",&k);
	Load_sample(); // bu fonksiyonda hazýrlanan veri test seti ara belleðe alýnýyor
	Load_test(test_int);// bu fonksiyonda ise sýnýflandýrýlacak elementlerin veri seti ara belleðe alýnýyor
	//time_graph(test_int,k);//bu fonksiyonda ise zaman karmaþýklýðý için grafik bastýrýlýyor
	printf("yeni elemtin proton sayisini giriniz");
	scanf("%d",&p);
	printf("yini elementin notron sayisini giriniz");
	scanf("%d",&n);
	if(distance(p,n,k)){
		printf("this element is non radioactive\n");
	}else{
		printf("this element is radioactive \n");
	}	
	for(i=0;i<480;i++){
		if(veri_s[i][2]==0){						//atomlarýn kararlýlýk kusagý grafik haline getiriliyor
			graph[veri_s[i][1]][veri_s[i][0]]=48;
		}if(veri_s[i][2]==1){
			graph[veri_s[i][1]][veri_s[i][0]]=49;
		}
	}
	for(i=70;i>=0;i--){
		for(j=0;j<100;j++){
			if(i==n&&j==p){			//grafik bastýrýlýyor
				printf("E");
			}else{
				printf("%c ",graph[i][j]);
			}
			
		}
		printf("\n");
	} 
	
}
