#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <conio.h>

int t=0;
struct ogrenci
{
    char ad[30];
    char soyad[30];
    char numara[7];
    int  kayitSirasi;
    char ogretimTuru[2];
};
float getdiff(struct timeval endtv, struct timeval starttv)
{
   float diff=0;
   diff=(endtv.tv_sec-starttv.tv_sec)*1000000+(endtv.tv_usec-starttv.tv_usec);
   return diff;
}
int main()
{
    int birinci,*ikinci;

    struct ogrenci *eleman=(struct ogrenci*)malloc(600*sizeof(struct ogrenci));
    struct ogrenci *tut2=(struct ogrenci*)malloc(sizeof(struct ogrenci));

    int *tekrarIND=(int *)malloc(20*sizeof(int));
    int eleman_sayisi=atamaListe(eleman);
    ayniKisiBul(eleman,tekrarIND,eleman_sayisi);
    kayitSiralama(eleman,tut2,tekrarIND,eleman_sayisi);
    birinci=numara_atama(eleman,tut2,eleman_sayisi,&ikinci);
    //elemanlariEkranaYazdir(eleman,eleman_sayisi);
    esit_sinif_dagilimi(eleman,birinci,ikinci,eleman_sayisi);
    en_az_sinif_dagilimi(eleman,birinci,ikinci,eleman_sayisi);
    guncelleDosyayaYaz(eleman,eleman_sayisi);
    //free(eleman);
    //free(tut2);


    return 0;
}
void en_az_sinif_dagilimi(struct ogrenci *eleman,int baslangic,int bitis,int eleman_sayisi)
{
    struct timeval starttv,endtv;
    struct timezone starttz,endtz;
    gettimeofday(&starttv,&starttz);
    printf("*En Az Sinif Dagilimi*\n");
    int toplam_kapasite=0,eski[2]={0,0},i,j,k,m=0,l=0,p=0,o=0,temp,baslangic_yedek=baslangic,sinif_sayisi,ogrenci_sayisi;
    printf("Sinif sayisini giriniz:");
    scanf("%d",&sinif_sayisi);
    int sinif_sayisi_yedek=sinif_sayisi;
    int *sinif_kapasiteleri=(int *)malloc((sinif_sayisi)*sizeof(int));
    for(m=0;m<baslangic_yedek;m++)
        {
            if((eleman+m)->ogretimTuru[1]!=73)
            {
                eski[0]++;
            }
                else
            {
                eski[1]++;
            }
        }
    m=0;
    int ogrenci_sayilari[2];
    ogrenci_sayilari[0]=bitis-baslangic+eski[0];
    ogrenci_sayilari[1]=eleman_sayisi-ogrenci_sayilari[0]-t;
    printf("1.ogretim:%d\n",ogrenci_sayilari[0]);
    printf("2.ogretim:%d\n",ogrenci_sayilari[1]);
    FILE *files[sinif_sayisi];
    while(1)
    {
        printf("Sinif Kapasitelerini Giriniz:\n");
        for(i=0;i<sinif_sayisi;i++)
        {
            printf("%d.sinif:",i+1);
            scanf("%d",(sinif_kapasiteleri+i));
            toplam_kapasite+=sinif_kapasiteleri[i];
        }
        if(toplam_kapasite>=ogrenci_sayilari[0]&&toplam_kapasite>=ogrenci_sayilari[1])
            break;
        printf("Girilen kapasiteler yetersiz, lutfen tekrar deneyin.\n");
    }
     for(i=0;i<sinif_sayisi;i++)    //Girilen sinif kapasitelerini kucukten buyuge siralar(Bubble Sort)
    {
        for(j=0;j<sinif_sayisi-1;j++)
        {
            if(sinif_kapasiteleri[j]<sinif_kapasiteleri[j+1])
            {
                temp=sinif_kapasiteleri[j];
                sinif_kapasiteleri[j]=sinif_kapasiteleri[j+1];
                sinif_kapasiteleri[j+1]=temp;
            }
        }
    }
    int *sinif_mevcutlari=(int *)malloc((1)*sizeof(int));
    for(i=0;i<2;i++)
    {
        m=l=o=p=0;
        for(j=0;j<sinif_sayisi;j++)
        {
            char filename[40];
            sprintf(filename, "EnAzDagilim-sinif%dogr%d.txt",j+1,i+1);
            files[j] = fopen(filename, "w");
            sinif_mevcutlari=(int *)realloc(sinif_mevcutlari,(sinif_kapasiteleri[j])*sizeof(int));
            if(sinif_kapasiteleri[j]<=ogrenci_sayilari[i])
            {
                sinif_mevcutlari[j]=sinif_kapasiteleri[j];
            }
            else
            {
                sinif_mevcutlari[j]=ogrenci_sayilari[i];
            }
            ogrenci_sayilari[i]-=sinif_mevcutlari[j];
            for(m;m<baslangic_yedek;m++)
            {
                if((eleman+m)->ogretimTuru[1]!=73&&i==0)
                {
                    if(m<sinif_mevcutlari[j])
                    {
                        fprintf(files[j],"%s %s %s %d %s\n",(eleman+m)->numara,(eleman+m)->ad,(eleman+m)->soyad,(eleman+m)->kayitSirasi,(eleman+m)->ogretimTuru);
                        l++;
                    }
                }
                else if((eleman+m)->ogretimTuru[1]==73&&i==1)
                {
                    if(m<sinif_mevcutlari[j])
                    {
                        fprintf(files[j],"%s %s %s %d %s\n",(eleman+m)->numara,(eleman+m)->ad,(eleman+m)->soyad,(eleman+m)->kayitSirasi,(eleman+m)->ogretimTuru);
                        l++;
                    }
                }
            }
            o=l-p;
            p=l;
            for(k=baslangic;k<sinif_mevcutlari[j]+baslangic-o;k++)
            {
                fprintf(files[j],"%s %s %s %d %s\n",(eleman+k)->numara,(eleman+k)->ad,(eleman+k)->soyad,(eleman+k)->kayitSirasi,(eleman+k)->ogretimTuru);
            }
            baslangic=k;
            fclose(filename);
        }
    }

    gettimeofday(&endtv,&endtz);
    float fark7=getdiff(endtv,starttv);
    fark7=fark7/1000000;
    printf("sinif_dagilimi %lf saniye surmustur.\n",fark7);
}

void esit_sinif_dagilimi(struct ogrenci *eleman,int baslangic,int bitis,int eleman_sayisi) //50  +
{
    struct timeval starttv,endtv;
    struct timezone starttz,endtz;
    gettimeofday(&starttv,&starttz);
    printf("*Esit Dagilim*\n");
    int eski[2]={0,0},i,j,k,m=0,l=0,p=0,o=0,temp,baslangic_yedek=baslangic,sinif_sayisi,ogrenci_sayisi,ortalama;
    printf("Sinif sayisini giriniz:");
    scanf("%d",&sinif_sayisi);
    int sinif_sayisi_yedek=sinif_sayisi;
    int *sinif_kapasiteleri=(int *)malloc((sinif_sayisi)*sizeof(int));
    int ogrenci_sayisi_1,ogrenci_sayisi_2,toplam_kapasite=0;
    for(m;m<baslangic_yedek;m++)
            {
                if((eleman+m)->ogretimTuru[1]!=73)
                {
                    eski[0]++;
                }
                else
                {
                    eski[1]++;
                }
            }
            m=0;
    ogrenci_sayisi_1=bitis-baslangic+eski[0];
    ogrenci_sayisi_2=eleman_sayisi-ogrenci_sayisi_1-t;
    printf("1.ogretim:%d\n",ogrenci_sayisi_1);
    printf("2.ogretim:%d\n",ogrenci_sayisi_2);
    while(1)
    {
        printf("Sinif Kapasitelerini Giriniz:\n");
        for(i=0;i<sinif_sayisi;i++)
        {
            printf("%d.sinif:",i+1);
            scanf("%d",(sinif_kapasiteleri+i));
            toplam_kapasite+=sinif_kapasiteleri[i];
        }
        if(toplam_kapasite>=ogrenci_sayisi_1&&toplam_kapasite>=ogrenci_sayisi_2)
            break;
        printf("Girilen kapasiteler yetersiz, lutfen tekrar deneyin.\n");
    }
     for(i=0;i<sinif_sayisi;i++)    //Girilen sinif kapasitelerini kucukten buyuge siralar(Bubble Sort)
    {
        for(j=0;j<sinif_sayisi-1;j++)
        {
            if(sinif_kapasiteleri[j]>sinif_kapasiteleri[j+1])
            {
                temp=sinif_kapasiteleri[j];
                sinif_kapasiteleri[j]=sinif_kapasiteleri[j+1];
                sinif_kapasiteleri[j+1]=temp;
            }
        }
    }
    int *sinif_mevcutlari=(int *)malloc((1)*sizeof(int));
    FILE *files[sinif_sayisi];
    for(i=0;i<2;i++)
    {
        m=l=o=p=0;
        sinif_sayisi_yedek=sinif_sayisi;
        ogrenci_sayisi=bitis-baslangic+eski[i];
        for(j=0;j<sinif_sayisi;j++)
        {
            char filename[40];
            sprintf(filename, "EsitDagilim-sinif%dogr%d.txt",j+1,i+1);
            files[j] = fopen(filename, "w");
            sinif_mevcutlari=(int *)realloc(sinif_mevcutlari,(sinif_kapasiteleri[j])*sizeof(int));
            ortalama=ogrenci_sayisi/sinif_sayisi_yedek--;
            if(sinif_kapasiteleri[j]<ortalama)
            {
                sinif_mevcutlari[j]=sinif_kapasiteleri[j];
            }
            else
            {
                sinif_mevcutlari[j]=ortalama;
            }
            ogrenci_sayisi-=sinif_mevcutlari[j];
            m+=l;
            for(m;m<baslangic_yedek;m++)
            {
                if((eleman+m)->ogretimTuru[1]!=73&&i==0)
                {
                    if(m<sinif_mevcutlari[j])
                    {
                        fprintf(files[j],"%s %s %s %d %s\n",(eleman+m)->numara,(eleman+m)->ad,(eleman+m)->soyad,(eleman+m)->kayitSirasi,(eleman+m)->ogretimTuru);
                        l++;
                    }
                }
                else if((eleman+m)->ogretimTuru[1]==73&&i==1)
                {
                    if(m<sinif_mevcutlari[j])
                    {
                        fprintf(files[j],"%s %s %s %d %s\n",(eleman+m)->numara,(eleman+m)->ad,(eleman+m)->soyad,(eleman+m)->kayitSirasi,(eleman+m)->ogretimTuru);
                        l++;
                    }
                }
            }
            o=l-p;
            p=l;
            for(k=baslangic;k<sinif_mevcutlari[j]+baslangic-o;k++)
            {
                if(k==bitis)
                {
                    break;
                }
                fprintf(files[j],"%s %s %s %d %s\n",(eleman+k)->numara,(eleman+k)->ad,(eleman+k)->soyad,(eleman+k)->kayitSirasi,(eleman+k)->ogretimTuru);
            }
            baslangic=k;
            fclose(filename);
        }
        bitis=eleman_sayisi-t;
    }
    gettimeofday(&endtv,&endtz);
    float fark6=getdiff(endtv,starttv);
    fark6=fark6/1000000;
    printf("esit_sinif_dagilimi %lf saniye surmustur.\n",fark6);
}

void elemanlariEkranaYazdir(struct ogrenci *eleman,int eleman_sayisi)
{
    struct timeval starttv,endtv;
    struct timezone starttz,endtz;
    gettimeofday(&starttv,&starttz);
    int i;
    for(i=0; i<eleman_sayisi-t; i++)
    {
        puts((eleman+i)->numara);
        puts((eleman+i)->ad);
        puts((eleman+i)->soyad);
        printf("%d\n",(eleman+i)->kayitSirasi);
        puts((eleman+i)->ogretimTuru);
        printf("\n");
    }
    gettimeofday(&endtv,&endtz);
    float fark1=getdiff(endtv,starttv);
    fark1=fark1/1000000;
    printf("elemanlariEkranaYazdir %lf saniye surmustur.\n",fark1);
}
int atamaListe(struct ogrenci *eleman)   // Dosyadaki satirlari ogrenci tipindeki structa ceker.
{
    struct timeval starttv,endtv;
    struct timezone starttz,endtz;
    gettimeofday(&starttv,&starttz);
    FILE *dosya;
    dosya = fopen("txt.txt","r");
    int i=-1;
    int l,test=1,deney=0,deney_2;
    char bos_dizi[15];
    while(!feof(dosya))
    {
        if(i==-1)
        {
            fscanf(dosya,"%s %s %s %s %s",(eleman+i)->numara,(eleman+i)->ad,(eleman+i)->soyad,bos_dizi,(eleman+i)->ogretimTuru);
        }
        fscanf(dosya,"%s %s %s %d %s",(eleman+i+1)->numara,(eleman+i+1)->ad,(eleman+i+1)->soyad,&(eleman+i+1)->kayitSirasi,(eleman+i+1)->ogretimTuru);
        if((eleman+i+1)->kayitSirasi!=0)
            deney++;
    i++;
    }


    while(test)
    {
        printf("Yeni kayit girmek icin 1 cikmak icin 0 giriniz:");
        scanf("%d",&test);
        if(!test)
        {
            break;
        }
        printf("Ogrenci Numarasi:");
        scanf("%s",(eleman+(i+1))->numara);
        printf("Ad:");
        scanf("%s",(eleman+(i+1))->ad);
        printf("Soyad:");
        scanf("%s",(eleman+(i+1))->soyad);
        while(1)
        {
        printf("Kayit Sirasi:");
        scanf("%d",&deney_2);
        if(deney_2>deney)
            {
                break;
            }
        printf("Var olan kayit sirasi girdiniz. Lutfen Tekrar Giriniz.\n");
        }
        (eleman+(i+1))->kayitSirasi=deney_2;
        printf("OgretimTuru:");
        scanf("%s",(eleman+(i+1))->ogretimTuru);
        i++;
    }
    l=i;
    gettimeofday(&endtv,&endtz);
    float fark2=getdiff(endtv,starttv);
    fark2=fark2/1000000;
    printf("atamaListe %lf saniye surmustur.\n",fark2);
    return l+1;
}
void ayniKisiBul(struct ogrenci *eleman,int *tekrarIND,int eleman_sayisi)    //struct icinde ayni ad soyadlari bulur.
{
    struct timeval starttv,endtv;
    struct timezone starttz,endtz;
    gettimeofday(&starttv,&starttz);
    printf("\n2 defa ismi gecen ogrencilerin tekrarlari silinmistir.\n");
    printf("isimler:\n");
    int i,j,k=0,test;
    for(i=0;i<eleman_sayisi-k-1;i++)
    {
        test=strcmp((eleman+i)->ad,(eleman+i+1)->ad);
        if(!test)
        {
            test=strcmp((eleman+i)->soyad,(eleman+i+1)->soyad);
            if(!test)
            {
                tekrarIND[k]=(eleman+i)->kayitSirasi;
                k++;
                printf("%s\t%s\n",(eleman+i)->ad,(eleman+i)->soyad);

                for(j=i;j<eleman_sayisi-k;j++)
                {
                    strcpy((eleman+j)->ad,((eleman+j+1)->ad));
                    (eleman+j)->kayitSirasi=(eleman+j+1)->kayitSirasi;
                    strcpy((eleman+j)->numara,((eleman+j+1)->numara));
                    strcpy((eleman+j)->ogretimTuru,((eleman+j+1)->ogretimTuru));
                    strcpy((eleman+j)->soyad,((eleman+j+1)->soyad));
                }
                i--;
            }
        }
    }
    t=k;
    gettimeofday(&endtv,&endtz);
    float fark3=getdiff(endtv,starttv);
    fark3=fark3/1000000;
    printf("ayniKisiBul %lf saniye surmustur.\n",fark3);
}
void guncelleDosyayaYaz(struct ogrenci *eleman,int eleman_sayisi)
{
    FILE *fp;
    fp=fopen("yeniDosya.txt","a");
    int i;
    for(i=0; i<(eleman_sayisi-t); i++)
    {
        fputs((eleman+i)->numara,fp);
        fprintf(fp," ");
        fputs((eleman+i)->ad,fp);
        fprintf(fp," ");
        fputs((eleman+i)->soyad,fp);
        fprintf(fp," ");
        fprintf(fp," %d ",(eleman+i)->kayitSirasi);
        fputs((eleman+i)->ogretimTuru,fp);
        fprintf(fp,"\n");
    }
    fclose(fp);

}
void kayitSiralama(struct ogrenci *eleman,struct ogrenci *tut2,int *tekrarIND,int eleman_sayisi)
{
    struct timeval starttv,endtv;
    struct timezone starttz,endtz;
    gettimeofday(&starttv,&starttz);
    printf("\nKayit siralari guncellenmistir.\n");
    int i,j,k;
    int tut;
    int sayac2=0;
    int k1=0;
    for(i=0; i<20; i++)
    {
        for(j=0; j<20-1; j++)
            if(tekrarIND[j]<tekrarIND[j+1])
            {
                tut=tekrarIND[j];
                tekrarIND[j]=tekrarIND[j+1];
                tekrarIND[j+1]=tut;
            }
    }
    for(i=0; i<eleman_sayisi-t; i++)
    {
        for(j=0; j<20; j++)
        {
            if(tekrarIND[j]!=0)
            {
                if((eleman+i)->kayitSirasi>tekrarIND[j])
                {
                    (eleman+i)->kayitSirasi--;
                }
            }
        }
    }
    for(i=0; i<eleman_sayisi-t; i++)
    {
        if((eleman+i)->kayitSirasi!=0)
        {
            for(j=0; j<eleman_sayisi-t-1; j++)
            {
                if ( (eleman+j)->kayitSirasi > (eleman+j+1)->kayitSirasi )
                {
                    strcpy(tut2->ad,(eleman+j)->ad);
                    tut2->kayitSirasi=(eleman+j)->kayitSirasi;
                    strcpy(tut2->numara,(eleman+j)->numara);
                    strcpy(tut2->ogretimTuru,(eleman+j)->ogretimTuru);
                    strcpy(tut2->soyad,(eleman+j)->soyad);

                    strcpy((eleman+j)->ad,(eleman+j+1)->ad);
                    (eleman+j)->kayitSirasi=(eleman+j+1)->kayitSirasi;
                    strcpy((eleman+j)->numara,(eleman+j+1)->numara);
                    strcpy((eleman+j)->ogretimTuru,(eleman+j+1)->ogretimTuru);
                    strcpy((eleman+j)->soyad,(eleman+j+1)->soyad);

                    strcpy((eleman+j+1)->ad,tut2->ad);
                    (eleman+j+1)->kayitSirasi=tut2->kayitSirasi;
                    strcpy((eleman+j+1)->numara,tut2->numara);
                    strcpy((eleman+j+1)->ogretimTuru,tut2->ogretimTuru);
                    strcpy((eleman+j+1)->soyad,tut2->soyad);
                }
            }
        }
    }
    gettimeofday(&endtv,&endtz);
    float fark4=getdiff(endtv,starttv);
    fark4=fark4/1000000;
    printf("kayitSiralama %lf saniye surmustur.\n",fark4);

}
int numara_atama(struct ogrenci *eleman,struct ogrenci *tut2,int eleman_sayisi,int *ikinci)
{
    struct timeval starttv,endtv;
    struct timezone starttz,endtz;
    gettimeofday(&starttv,&starttz);
    int value,i=0,j=0,sayac_1=0,sayac_2=0;
    int birinci;
    for(i=0; i<eleman_sayisi-t; i++)
    {
        if((eleman+i)->numara[0]==45)
        {
            if((eleman+i)->ogretimTuru[1]!=73)
            {
                value=1701001;
                value+=sayac_1;
                sprintf((eleman+i)->numara, "%d", value);
                sayac_1++;
                if(value==1701001)
                birinci=i;
            }
            else if((eleman+i)->ogretimTuru[1]==73)
            {
                value=1702001;
                value+=sayac_2;
                sprintf((eleman+i)->numara, "%d", value);
                sayac_2++;
                if(value==1702001)
                *ikinci=i;

            }
        }
    }
    for(i=0; i<eleman_sayisi-t; i++)
    {
        for(j=0; j<eleman_sayisi-t-1; j++)
        {
            if ( (eleman+j)->numara > (eleman+j+1)->numara )
            {
                    strcpy(tut2->ad,(eleman+j)->ad);
                    tut2->kayitSirasi=(eleman+j)->kayitSirasi;
                    strcpy(tut2->numara,(eleman+j)->numara);
                    strcpy(tut2->ogretimTuru,(eleman+j)->ogretimTuru);
                    strcpy(tut2->soyad,(eleman+j)->soyad);

                    strcpy((eleman+j)->ad,(eleman+j+1)->ad);
                    (eleman+j)->kayitSirasi=(eleman+j+1)->kayitSirasi;
                    strcpy((eleman+j)->numara,(eleman+j+1)->numara);
                    strcpy((eleman+j)->ogretimTuru,(eleman+j+1)->ogretimTuru);
                    strcpy((eleman+j)->soyad,(eleman+j+1)->soyad);

                    strcpy((eleman+j+1)->ad,tut2->ad);
                    (eleman+j+1)->kayitSirasi=tut2->kayitSirasi;
                    strcpy((eleman+j+1)->numara,tut2->numara);
                    strcpy((eleman+j+1)->ogretimTuru,tut2->ogretimTuru);
                    strcpy((eleman+j+1)->soyad,tut2->soyad);
            }
        }
    }
    gettimeofday(&endtv,&endtz);
    float fark5=getdiff(endtv,starttv);
    fark5=fark5/1000000;
    printf("\nnumara_atama %lf saniye surmustur.\n",fark5);

    return birinci;
}


